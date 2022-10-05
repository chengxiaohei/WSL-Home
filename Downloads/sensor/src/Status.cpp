#include "Status.h"

#include <iostream>
#include <regex>
#include <cstring>  //for memset function
#include <cstdlib> //for atoi
#include <curl/curl.h> //for communicate with influxdb

// extern spdlog::logger* Logger;
extern std::string BucketName;
extern std::string Authorization;
extern std::string QueryDataURL;

Status::Status(std::string deviceName){
    memset(&this->info, 0, sizeof(Oil_Level_t));
    this->deviceName = deviceName;
    this->info.device = deviceName;
    this->historyInfo.push_back(this->info);
}

Status::~Status(){}

int Status::queryData(float frequency){
    //从数据库中读取数据
    // Logger->info("{} query data with {}Hz", this->info.device, frequency);
    std::cout << this->info.device << " query data" << std::endl;
    CURL *curl;
    CURLcode resCode;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, QueryDataURL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/vnd.flux");
        headers = curl_slist_append(headers, std::string("Authorization: Token " + Authorization).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        char *data = new char[1024];
        sprintf(data, Status_Data_Flux, BucketName.c_str(), this->info.device.c_str(), "opStatus");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->parseData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&this->info);
        resCode = curl_easy_perform(curl);
        if(resCode != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resCode));
        }
        curl_slist_free_all(headers); /* free the header list*/
        delete[] data;
    }
    curl_easy_cleanup(curl);
    return 0;
}

int Status::queryFaultData(float frequency){
    std::cout << this->info.device << "query fault data" << std::endl;
    CURL *curl;
    CURLcode resCode;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, QueryDataURL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/vnd.flux");
        headers = curl_slist_append(headers, std::string("Authorization: Token " + Authorization).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        char *data = new char[1024];
        sprintf(data, Status_Fault_Flux, BucketName.c_str(), (int)frequency, this->info.device.c_str(), "opStatus");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->parseFaultData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&this->historyRawData);
        resCode = curl_easy_perform(curl);
        if(resCode != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resCode));
        }
        curl_slist_free_all(headers); /* free the header list*/
        delete[] data;
    }
    curl_easy_cleanup(curl);
    /*************************start parse*********************************/
    // std::cout << this->historyRawData << std::endl;
    int field_num = 5;
    std::regex line_re("[\n\r,]");
    std::vector<std::string> v(std::sregex_token_iterator(this->historyRawData.begin(), this->historyRawData.end(), line_re, -1), std::sregex_token_iterator());
    for(size_t i=0; i<v.size(); i++){
        if(v[i].empty())
            v.erase(v.begin()+i--);
    }
    // for(auto&& s: v){
    //     std::cout << "***";
    //     std::cout << s <<  "***" << s.length() << std::endl;
    // }
    std::vector<Status_t> *s_dv = &this->historyInfo;

    if(v.empty() || v.size() % field_num != 0){
        if(v.empty())
            printf("未找到设备%s历史数据\n", s_dv->front().device.c_str());
        else 
            printf("%s设备数据格式错误\n", s_dv->front().device.c_str());
        return -1;
    }
    int field_index = 0, value_index = 0, time_index = 0;
    for(size_t i=0; i<field_num; i++){
        if(v[i] == "_field") field_index = i;
        if(v[i] == "_value") value_index = i;
        if(v[i] == "_time") time_index = i;
    }
    Status_t temp;
    temp.device = s_dv->front().device;
    temp.opStatus = 0;
    s_dv->clear();
    for(int i=0; i<v.size()/(field_num*2); i++){  //record_num = v.size()/(field_num*2)
        int n = (i+1) * field_num;
        temp.time = v[time_index + n];
        s_dv->push_back(temp);
    }
    int recordIdx[2] = {0};
    for(size_t t=1; t<v.size()/field_num; t++){
        int n = t * field_num;
        if(v[field_index + n] == "_field"){
            continue;
        }else if(v[field_index + n] == "opStatus"){
            (*s_dv)[recordIdx[0]].opStatus = atoi(v[value_index + n].c_str());
            recordIdx[0]++;
        }else{
            printf("未找到指标信息(Fault Data)\n");
        }
    }
    return 0;
}

void Status::cleanup(){
    memset(&this->info, 0, sizeof(Status_t));
    this->info.device = this->deviceName;
    this->info.opStatus = -1;
    this->historyInfo.clear();
    this->historyInfo.push_back(this->info);
}

int Status::write(){
    //向数据库写入数据
}

int Status::show(){
    std::cout <<  std::endl << "device:" << this->info.device << std::endl;
    std::cout << "time:" <<  this->info.time << std::endl;
    if(this->info.opStatus == 0)
        std::cout << "opStatus: 启动" << std::endl;
    else if(this->info.opStatus == 1)
        std::cout << "opStatus: 运行" << std::endl;
    else if(this->info.opStatus = 2)
        std::cout << "opStatus: 停止" << std::endl;

    for(int i=0; i<this->historyInfo.size(); i++){
        printf("**************historyInfo[%d]******************\n", i);
        std::cout << "device:" << this->historyInfo[i].device << std::endl;
        std::cout << "time:" <<  this->historyInfo[i].time << std::endl;
        if(this->historyInfo[i].opStatus == 0)
            std::cout << "opStatus: 启动" << std::endl;
        else if(this->historyInfo[i].opStatus == 1)
            std::cout << "opStatus: 运行" << std::endl;
        else if(this->historyInfo[i].opStatus = 2)
            std::cout << "opStatus: 停止" << std::endl;
    }
}

void Status::check(){
    
}

int Status::getStatus(){
    //检查返回当前运行状态, 0: 运行, 1: 启动, 2: 停止
    return this->info.opStatus;
}

std::string Status::getTime(){
    return this->info.time;
}

size_t Status::parseData(void *queriedData, size_t size, size_t nmemb, void *userData){
    // queriedData points to the delivered data, and the size of that data is nmemb; size is always 1.
    size_t realsize = size * nmemb;
    std::string data = std::string(reinterpret_cast<char *>(queriedData), realsize);
    // std::cout << data << std::endl;
    int field_num = 5;
    std::regex line_re("[\n\r,]");
    std::vector<std::string> v(std::sregex_token_iterator(data.begin(), data.end(), line_re, -1), std::sregex_token_iterator());
    for(size_t i=0; i<v.size(); i++){
        if(v[i].empty())
            v.erase(v.begin()+i--);
    }
    Status_t *s_d = reinterpret_cast<Status_t *>(userData);
    if(v.empty() || v.size() % field_num != 0){
        if(v.empty())
            printf("未找到%s设备数据\n", s_d->device.c_str());
        else 
            printf("%s设备数据格式错误\n", s_d->device.c_str());
        return realsize;
    }
    int field_index = 0, value_index = 0, time_index = 0;
    for(size_t i=0; i<field_num; i++){
        if(v[i] == "_field") field_index = i;
        if(v[i] == "_value") value_index = i;
        if(v[i] == "_time") time_index = i;
    }
    
    // for(auto&& s: v){
    //     std::cout << "***";
    //     std::cout << s <<  "***" << s.length() << std::endl;
    // }
    for(size_t t=1; t<v.size()/field_num; t++){
        int n = t * field_num;
        if(v[field_index + n] == "_field"){
            continue;
        }else if(v[field_index + n] == "opStatus"){
            s_d->opStatus = atoi(v[value_index + n].c_str());
        }else{
            printf("未找到指标信息\n");
        }
    }
    s_d->time = v[time_index + field_num];
    return realsize;
}

size_t Status::parseFaultData(void *queriedData, size_t size, size_t nmemb, void *userData){
    char buffer[10240];
    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, queriedData, nmemb);
    std::string bufferString(reinterpret_cast<char *>(buffer));
    std::string *historyRawData = reinterpret_cast<std::string *>(userData);
    (*historyRawData) += bufferString;
    return size * nmemb;
}