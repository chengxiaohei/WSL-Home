#include "Oil_Level.h"

#include <iostream>
#include <regex>
#include <cstring>  //for memset function
#include <cstdlib> //for atoi
#include <curl/curl.h> //for communicate with influxdb

// extern spdlog::logger* Logger;
extern std::string BucketName;
extern std::string Authorization;
extern std::string QueryDataURL;
extern std::string PicturePath;

Oil_Level::Oil_Level(std::string deviceName){
    memset(&this->info, 0, sizeof(Oil_Level_t));
    this->deviceName = deviceName;
    this->info.device = deviceName;
    this->info.ywTp = PicturePath;
    this->historyInfo.push_back(this->info);
}

Oil_Level::~Oil_Level(){}

int Oil_Level::queryData(float frequency){
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
        sprintf(data, Oil_Level_Data_Flux, BucketName.c_str(), this->info.device.c_str(), "ywBfb", "ywZcxh");
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

int Oil_Level::queryFaultData(float frequency){
    std::cout << this->info.device << " query fault data" << std::endl;
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
        sprintf(data, Oil_Level_Fault_Flux, BucketName.c_str(), (int)frequency, this->info.device.c_str(), "ywBfb", "ywZcxh");
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
    std::vector<Oil_Level_t> *o_dv = &this->historyInfo;

    if(v.empty() || v.size() % field_num != 0){
        if(v.empty())
            printf("未找到设备%s历史数据\n", o_dv->front().device.c_str());
        else 
            printf("%s设备数据格式错误\n", o_dv->front().device.c_str());
        return -1;
    }
    int field_index = 0, value_index = 0, time_index = 0;
    for(size_t i=0; i<field_num; i++){
        if(v[i] == "_field") field_index = i;
        if(v[i] == "_value") value_index = i;
        if(v[i] == "_time") time_index = i;
    }
    Oil_Level_t temp;
    temp.device = o_dv->front().device;
    temp.ywTp = PicturePath;
    o_dv->clear();
    for(int i=0; i<v.size()/(field_num*2); i++){  //record_num = v.size()/(field_num*2)
        int n = (i+1) * field_num;
        temp.time = v[time_index + n];
        o_dv->push_back(temp);
    }
    int recordIdx[2] = {0};
    for(size_t t=1; t<v.size()/field_num; t++){
        int n = t * field_num;
        if(v[field_index + n] == "_field"){
            continue;
        }else if(v[field_index + n] == "ywBfb"){
            (*o_dv)[recordIdx[0]].ywBfb = v[value_index + n];
            recordIdx[0]++;
        }else if(v[field_index + n] == "ywZcxh"){
            (*o_dv)[recordIdx[1]].ywZcxh = atoi(v[value_index + n].c_str());
            recordIdx[1]++;
        }else{
            printf("未找到指标信息(Fault Data)\n");
        }
    }
    return 0;
}

void Oil_Level::cleanup(){
    memset(&this->info, 0, sizeof(Oil_Level_t));
    this->info.device = this->deviceName;
    this->info.ywTp = PicturePath;
    this->historyInfo.clear();
    this->historyInfo.push_back(this->info);
}

int Oil_Level::write(){
    //向数据库写入数据
}

int Oil_Level::show(){
    std::cout <<  std::endl << "device:" << this->info.device << std::endl;
    std::cout << "time:" <<  this->info.time << std::endl;
    std::cout << "ywBfb:" <<  this->info.ywBfb << std::endl;
    std::cout << "ywTp:" <<  this->info.ywTp << std::endl;
    std::cout << "ywZcxh:" <<  (this->info.ywZcxh == 0 ? "正常" : "异常") << std::endl;
    for(int i=0; i<this->historyInfo.size(); i++){
        printf("**************historyInfo[%d]******************\n", i);
        std::cout << "device:" << this->historyInfo[i].device << std::endl;
        std::cout << "time:" <<  this->historyInfo[i].time << std::endl;
        std::cout << "ywBfb:" <<  this->historyInfo[i].ywBfb << std::endl;
        std::cout << "ywTp:" <<  this->historyInfo[i].ywTp << std::endl;
        std::cout << "ywZcxh:" <<  (this->historyInfo[i].ywZcxh == 0 ? "正常" : "异常") << std::endl;
    }
}

void Oil_Level::check(){
    if(this->info.ywZcxh != 0){
        this->isNormal = false;
        this->abnormalPhenomenon = "油位异常;";
    }else{
        this->isNormal = true;
    }
}

int Oil_Level::getStatus(){
    //检查返回当前运行状态, 0: 运行, 1: 启动, 2: 停止
    return -1;
}


std::string Oil_Level::getTime(){
    return this->info.time;
}

size_t Oil_Level::parseData(void *queriedData, size_t size, size_t nmemb, void *userData){
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
    Oil_Level_t *o_d = reinterpret_cast<Oil_Level_t *>(userData);
    if(v.empty() || v.size() % field_num != 0){
        if(v.empty())
            printf("未找到%s设备数据\n", o_d->device.c_str());
        else 
            printf("%s设备数据格式错误\n", o_d->device.c_str());
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
        }else if(v[field_index + n] == "ywBfb"){
            o_d->ywBfb = v[value_index + n];
        }else if(v[field_index + n] == "ywTp"){
            o_d->ywTp = v[value_index + n];
        }else if(v[field_index + n] == "ywZcxh"){
            o_d->ywZcxh = atoi(v[value_index + n].c_str());
        }else{
            printf("未找到指标信息\n");
        }
    }
    o_d->time = v[time_index + field_num];
    return realsize;
}

size_t Oil_Level::parseFaultData(void *queriedData, size_t size, size_t nmemb, void *userData){
    char buffer[10240];
    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, queriedData, nmemb);
    std::string bufferString(reinterpret_cast<char *>(buffer));
    std::string *historyRawData = reinterpret_cast<std::string *>(userData);
    (*historyRawData) += bufferString;
    return size * nmemb;
}