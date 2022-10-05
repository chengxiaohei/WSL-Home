#include "Reporter.h"

#include <regex>
#include <exception>
#include <curl/curl.h> //for communicate with influxdb
#include <cstdlib> //for atoi
#include <unistd.h> //for sleep
#include <cstring> //for memset
#include <ctime>
#include "Oil_Level.h"
#include "Temperature.h"
#include "Vibration.h"
#include "Status.h"

extern std::string DataReportURL;
extern std::string FaultDataReportURL;
extern std::string FaultRecordReportURL;

using json = nlohmann::json;

Reporter::Reporter(std::string deviceCode){
    this->deviceCode = deviceCode;
    this->devices.clear();
    this->faultID = -1;
    this->isNormal = true;
    this->abnormalPhenomenon = std::string();
}

Reporter::Reporter(std::string deviceCode, std::vector<Measurement*> devices){
    this->deviceCode = deviceCode;
    this->devices.clear();
    for(auto it=devices.begin(); it!=devices.end(); ++it){
        (*it)->cleanup();
        this->devices.push_back(*it);
    }
    this->faultID = -1;
    this->isNormal = true;
    this->abnormalPhenomenon = std::string();
}

Reporter::~Reporter(){}

int Reporter::add(Measurement* device){
    device->cleanup();
    this->devices.push_back(device);
}

int Reporter::add(std::vector<Measurement*> devices){
    for(auto it=devices.begin(); it!=devices.end(); ++it){
        (*it)->cleanup();
        this->devices.push_back(*it);
    }
}

int Reporter::queryData(float frequency){
    for(auto it=this->devices.begin(); it!=this->devices.end(); ++it){
        (*it)->queryData(frequency);
    }
    return 0;
}

int Reporter::queryFaultData(float frequency){
    for(auto it=this->devices.begin(); it!=this->devices.end(); ++it){
        (*it)->queryFaultData(frequency);
    }
    return 0;
}

int Reporter::dataReport(){
    int o_deviceIdx = 0, t_deviceIdx = 0, v_deviceIdx = 0, s_deviceIdx = 0;
    char *record = new char[32];
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, DataReportURL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        struct curl_slist *headers = NULL;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_mime *mime;
        curl_mimepart *part;
        mime = curl_mime_init(curl);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "code");
        curl_mime_data(part, this->deviceCode.c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "faultID");
        curl_mime_data(part, std::to_string(this->faultID).c_str(), CURL_ZERO_TERMINATED);

        // part = curl_mime_addpart(mime);
        // curl_mime_name(part, "status");
        // curl_mime_data(part, std::to_string(this->status).c_str(), CURL_ZERO_TERMINATED);

        for(auto it=this->devices.begin(); it!=this->devices.end(); ++it){
            /****************************Oil_Level****************************/
            if((*it)->deviceName[0] == 'o' || (*it)->deviceName[0] == 'O'){
                Oil_Level *o_device = dynamic_cast<Oil_Level *>(*it);

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Yw", o_deviceIdx, "name");
                curl_mime_name(part, record);
                curl_mime_data(part, o_device->info.device.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Yw", o_deviceIdx, "time");
                curl_mime_name(part, record);
                curl_mime_data(part, o_device->info.time.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Yw", o_deviceIdx, "ywBfb");
                curl_mime_name(part, record);
                curl_mime_data(part, o_device->info.ywBfb.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Yw", o_deviceIdx, "ywTp");
                curl_mime_name(part, record);
                curl_mime_filedata(part, o_device->info.ywTp.c_str());
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Yw", o_deviceIdx, "ywZcxh");
                curl_mime_name(part, record);
                curl_mime_data(part, o_device->info.ywZcxh == 0 ? "0" : "1", CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                o_deviceIdx++;
            }
            /***************************Temperature***************************/
            else if((*it)->deviceName[0] == 't' || (*it)->deviceName[0] == 'T'){
                Temperature *t_device = dynamic_cast<Temperature *>(*it);

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Wd", t_deviceIdx, "name");
                curl_mime_name(part, record);
                curl_mime_data(part, t_device->info.device.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Wd", t_deviceIdx, "time");
                curl_mime_name(part, record);
                curl_mime_data(part, t_device->info.time.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Wd", t_deviceIdx, "wdSz");
                curl_mime_name(part, record);
                curl_mime_data(part, t_device->info.wdSz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Wd", t_deviceIdx, "wdSzAvg");
                curl_mime_name(part, record);
                curl_mime_data(part, t_device->info.wdSzAvg.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Wd", t_deviceIdx, "wdZcxh");
                curl_mime_name(part, record);
                curl_mime_data(part, t_device->info.wdZcxh == 0 ? "0" : "1", CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                t_deviceIdx++;
            }
            /****************************Vibration****************************/
            else if((*it)->deviceName[0] == 'v' || (*it)->deviceName[0] == 'V'){
                Vibration *v_device = dynamic_cast<Vibration *>(*it);

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "name");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.device.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "time");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.time.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyZdz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyZdz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyZxz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyZxz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyFfz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyFfz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyPjz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyPjz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyJfz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyJfz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyYxz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyYxz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyQdzb");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyQdzb.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyPdzb");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyPdzb.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdSyYdzb");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdSyYdzb.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdPyPpjz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdPyPpjz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdPyPlzx");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdPyPlzx.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdPyJfgpl");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdPyJfgpl.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdPyPpjfgz");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdPyPpjfgz.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdPyBzcpl");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdPyBzcpl.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdYssj");
                curl_mime_name(part, record);
                curl_mime_data(part, v_device->info.zdYssj.c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                part = curl_mime_addpart(mime);
                sprintf(record, DataReportFormat, "Zd", v_deviceIdx, "zdZcxh");
                curl_mime_name(part, record);
                curl_mime_data(part, std::to_string(v_device->info.zdZcxh).c_str(), CURL_ZERO_TERMINATED);
                memset(record, 0, sizeof(record));

                v_deviceIdx++;
            }
            else if((*it)->deviceName[0] == 's' || (*it)->deviceName[0] == 'S'){
                Status *s_device = dynamic_cast<Status *>(*it);
                
                part = curl_mime_addpart(mime);
                curl_mime_name(part, "status");
                curl_mime_data(part, std::to_string(s_device->info.opStatus).c_str(), CURL_ZERO_TERMINATED);

                s_deviceIdx++;
            }
            else{
                printf("无法识别的设备\n");
            }
        }
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->checkResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, nullptr);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return -1;
        }
        curl_slist_free_all(headers); /* free the header list*/
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    delete[] record;
    return 0;
}

size_t Reporter::checkResponse(void *response, size_t size, size_t nmemb, void *userData){
    // std::string responseString(reinterpret_cast<char *>(response));
    // auto j = json::parse(responseString);
    // if(j["code"] != 200){
    //     printf("report data error!\n");
    // }
    return size * nmemb;
}

int Reporter::faultDataReport(std::string faultOccurTime){
    int o_dataIdx = 0, t_dataIdx = 0, v_dataIdx = 0, s_dataIdx = 0;
    char *record = new char[64];
    CURL *curl;
    CURLcode resCode;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, FaultDataReportURL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        struct curl_slist *headers = NULL;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_mime *mime;
        curl_mimepart *part;
        mime = curl_mime_init(curl);

        part = curl_mime_addpart(mime);
        curl_mime_name(part,"code");
        curl_mime_data(part, this->deviceCode.c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "time");
        curl_mime_data(part, faultOccurTime.c_str(), CURL_ZERO_TERMINATED);

        for(auto it=this->devices.begin(); it!=this->devices.end(); ++it){
            /****************************Oil_Level****************************/
            if((*it)->deviceName[0] == 'o' || (*it)->deviceName[0] == 'O'){
                Oil_Level *o_device = dynamic_cast<Oil_Level *>(*it);

                for(int i=0; i<o_device->historyInfo.size(); i++){
                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Yw", o_dataIdx, "name");
                    curl_mime_name(part, record);
                    curl_mime_data(part, o_device->historyInfo[i].device.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Yw", o_dataIdx, "time");
                    curl_mime_name(part, record);
                    curl_mime_data(part, o_device->historyInfo[i].time.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));
                    
                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Yw", o_dataIdx, "ywBfb");
                    curl_mime_name(part, record);
                    curl_mime_data(part, o_device->historyInfo[i].ywBfb.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Yw", o_dataIdx, "ywTp");
                    curl_mime_name(part, record);
                    curl_mime_filedata(part, o_device->historyInfo[i].ywTp.c_str());
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Yw", o_dataIdx, "ywZcxh");
                    curl_mime_name(part, record);
                    curl_mime_data(part, o_device->historyInfo[i].ywZcxh == 0 ? "0" : "1", CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    o_dataIdx++;
                }
            }
            /***************************Temperature***************************/
            else if((*it)->deviceName[0] == 't' || (*it)->deviceName[0] == 'T'){
                Temperature *t_device = dynamic_cast<Temperature *>(*it);

                for(int i=0; i<t_device->historyInfo.size(); i++){
                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Wd", t_dataIdx, "name");
                    curl_mime_name(part, record);
                    curl_mime_data(part, t_device->historyInfo[i].device.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Wd", t_dataIdx, "time");
                    curl_mime_name(part, record);
                    curl_mime_data(part, t_device->historyInfo[i].time.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Wd", t_dataIdx, "wdSz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, t_device->historyInfo[i].wdSz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Wd", t_dataIdx, "wdSzAvg");
                    curl_mime_name(part, record);
                    curl_mime_data(part, t_device->historyInfo[i].wdSzAvg.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Wd", t_dataIdx, "wdZcxh");
                    curl_mime_name(part, record);
                    curl_mime_data(part, t_device->historyInfo[i].wdZcxh == 0 ? "0" : "1", CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    t_dataIdx++;
                }
            }
             /****************************Vibration****************************/
            else if((*it)->deviceName[0] == 'v' || (*it)->deviceName[0] == 'V'){
                Vibration *v_device = dynamic_cast<Vibration *>(*it);

                for(int i=0; i<v_device->historyInfo.size(); i++){
                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "name");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].device.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "time");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].time.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyZdz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyZdz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyZxz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyZxz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyFfz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyFfz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyPjz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyPjz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyJfz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyJfz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyYxz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyYxz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyQdzb");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyQdzb.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyPdzb");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyPdzb.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdSyYdzb");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdSyYdzb.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdPyPpjz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdPyPpjz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdPyPlzx");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdPyPlzx.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdPyJfgpl");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdPyJfgpl.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdPyPpjfgz");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdPyPpjfgz.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdPyBzcpl");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdPyBzcpl.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdYssj");
                    curl_mime_name(part, record);
                    curl_mime_data(part, v_device->historyInfo[i].zdYssj.c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    part = curl_mime_addpart(mime);
                    sprintf(record, FaultDataReportFormat, "Zd", v_dataIdx, "zdZcxh");
                    curl_mime_name(part, record);
                    curl_mime_data(part, std::to_string(v_device->historyInfo[i].zdZcxh).c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    v_dataIdx++;
                }
            }
            else if((*it)->deviceName[0] == 's' || (*it)->deviceName[0] == 'S'){
                Status *s_device = dynamic_cast<Status *>(*it);

                for(int i=0; i<s_device->historyInfo.size(); i++){
                    part = curl_mime_addpart(mime);
                    sprintf(record, "data.status[%d]", s_dataIdx);
                    curl_mime_name(part, record);
                    curl_mime_data(part, std::to_string(s_device->historyInfo[i].opStatus).c_str(), CURL_ZERO_TERMINATED);
                    memset(record, 0, sizeof(record));

                    s_dataIdx++;
                }
            }
            else{
                printf("无法识别的设备\n");
            }
        }
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->getFaultID);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&this->faultID);
        resCode = curl_easy_perform(curl);
        if(resCode != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resCode));
            return -1;
        }
        curl_slist_free_all(headers); /* free the header list*/
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    delete[] record;
    return 0;
}

size_t Reporter::getFaultID(void *response, size_t size, size_t nmemb, void *userData){
    // printf("---%s---\n", reinterpret_cast<char *>(response));
    std::string responseString(reinterpret_cast<char *>(response));
    std::regex line_re("[\n\r]");
    std::vector<std::string> v(std::sregex_token_iterator(responseString.begin(), responseString.end(), line_re, -1), std::sregex_token_iterator());
    auto j = json::parse(v[0]);
    // printf("***%s***\n", responseString.c_str());
    // auto j = json::parse(responseString);
    try{
        if(j["code"] == 200){
            (*reinterpret_cast<int *>(userData)) = j["data"];
        }
    }catch(std::exception e){
        printf("parse response failed!");
        (*reinterpret_cast<int *>(userData)) = -1;
    }
    
    return size * nmemb;
}


int Reporter::faultRecordReport(int faultID, std::string faultStartTime, std::string faultEndTime, int duration, std::string phenomenon){
    CURL *curl;
    CURLcode resCode;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, FaultRecordReportURL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        struct curl_slist *headers = NULL;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_mime *mime;
        curl_mimepart *part;
        mime = curl_mime_init(curl);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "code");
        curl_mime_data(part, this->deviceCode.c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "faultId");
        curl_mime_data(part, std::to_string(faultID).c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "time");
        curl_mime_data(part, faultEndTime.c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "duration");
        curl_mime_data(part, std::to_string(duration).c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "note");
        curl_mime_data(part, phenomenon.c_str(), CURL_ZERO_TERMINATED);

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
        resCode = curl_easy_perform(curl);
        if(resCode != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resCode));
        }
        curl_mime_free(mime);
        curl_slist_free_all(headers); /* free the header list*/
    }
    curl_easy_cleanup(curl);
    return 0;
}

void Reporter::check(){
    this->isNormal = true;
    printf("各设备状态:\n");
    for(auto it=this->devices.begin(); it!=this->devices.end(); ++it){ //检查所有设备，是否存在异常
        (*it)->check();
        printf("%s\n", (*it)->isNormal ? "Normal" : "Abnormal");
        this->isNormal = this->isNormal && (*it)->isNormal;
        // int status = (*it)->getStatus();
        // if(status != -1)
        //     this->status = status;
    }
    printf("\ncheck result: %s\n", this->isNormal ? "Normal" : "Abnormal");
}

void Reporter::getAbnormalPhenomenon(){
    for(auto it=this->devices.begin(); it!=this->devices.end(); ++it){
        (*it)->check();
        this->abnormalPhenomenon += (*it)->abnormalPhenomenon;
    }
}

std::string Reporter::getTime(){
    std::string res;
    for(auto it=this->devices.begin(); it!=this->devices.end(); ++it){
        res = (*it)->getTime() > res ? (*it)->getTime() : res;
    }
    return res;
}

int Reporter::run(int normalInterval, int abnormalInterval){
    int faultStatus = 0;  //0:错误还未发生，1:错误还在持续，2:错误已经结束
    time_t sTime;
    clock_t cTime;
    std::string faultStartTime, faultEndTime;
    int currentFaultID = -1;
    std::string currentAbnormalPhenomenon;
    while(true){
        this->queryData(1);
        this->check();
        //发生故障，高频发送前后各15分钟数据
        if(!this->isNormal){
            sleep(abnormalInterval);
            this->queryData(1);
            this->check();
            if(!this->isNormal){
                faultStartTime = this->getTime();
                cTime = clock();
                this->getAbnormalPhenomenon();
                currentAbnormalPhenomenon = this->abnormalPhenomenon;
                faultStatus = 1;
                this->queryFaultData(10);
                this->faultDataReport(faultStartTime); //这里report之后，this->faultID会改变
                currentFaultID = this->faultID;
                sTime = time(NULL);
                
                while(difftime(time(NULL), sTime) < 15 * 60){  //15分钟高频发送
                    sleep(abnormalInterval);
                    this->queryData(1);
                    this->check();
                    if(this->isNormal && faultStatus == 1){
                        faultEndTime = this->getTime();
                        faultStatus = 2;
                        this->faultID = -1;
                    }
                    this->dataReport();
                }
            }
        }else{
            this->dataReport();
        }
        //故障刚刚结束，上报故障记录详情
        if(this->isNormal && faultStatus == 1){
            sleep(normalInterval);
            this->queryData(1);
            this->check();
            if(this->isNormal && faultStatus == 1){
                faultEndTime = this->getTime();
                this->faultRecordReport(currentFaultID, faultStartTime, faultEndTime, (int)(clock()-cTime)*CLOCKS_PER_SEC, currentAbnormalPhenomenon);
                this->faultID = -1;
                currentFaultID = -1;
                currentAbnormalPhenomenon.clear();
                faultStatus = 0;
            }
        }
        //故障在15分钟高频上报时就已经结束，现在上报故障记录详情
        else if(this->isNormal && faultStatus == 2){
            sleep(normalInterval);
            this->queryData(1);
            this->check();
            if(this->isNormal && faultStatus == 2){
                this->faultRecordReport(currentFaultID, faultStartTime, faultEndTime, (int)(clock()-cTime)*CLOCKS_PER_SEC, currentAbnormalPhenomenon);
                currentFaultID = -1;
                currentAbnormalPhenomenon.clear();
                faultStatus = 0;
            }
        }
        sleep(normalInterval);
    }
    return 0;
}


int Reporter::run2(int normalInterval, int abnormalInterval){ // 10, 1: 正常情况10秒一次数据, 异常情况1秒一次数据
    int faultStatus = 0;  //0:错误还未发生，1:错误还在持续，2:错误已经结束
    time_t sTime;
    clock_t cTime;
    std::string faultStartTime, faultEndTime;
    int currentFaultID = -1;
    std::string currentAbnormalPhenomenon;
    while(true){
        this->isNormal = true;
        this->queryData(1);
        this->check();
        //发生故障，高频发送前5分钟、后1分钟数据
        if(!this->isNormal){
            sleep(1 * abnormalInterval);
            this->queryData(1);
            this->check();
            if(!this->isNormal){ //此时确认:确实发生了故障
                printf("此时确认发生了故障\n");
                faultStartTime = this->getTime();
                cTime = clock();
                this->getAbnormalPhenomenon();
                currentAbnormalPhenomenon = this->abnormalPhenomenon;
                faultStatus = 1;
                this->queryFaultData(10);
                this->faultDataReport(faultStartTime); //这里report之后，this->faultID会改变
                currentFaultID = this->faultID;
                sTime = time(NULL);
                printf("高频1分钟发送数据中。。。\n");
                while(difftime(time(NULL), sTime) < 1 * 60){  //1分钟高频发送
                    sleep(abnormalInterval);
                    this->queryData(1);
                    this->check();
                    if(this->isNormal && faultStatus == 1){
                        sleep(abnormalInterval);
                        this->queryData(1);
                        this->check();
                        if(this->isNormal && faultStatus == 1){
                            printf("此时确认异常已消失\n");
                            faultEndTime = this->getTime();
                            faultStatus = 2;
                            this->faultID = -1;
                        }
                    }
                    this->dataReport();
                }
            }else{
                this->dataReport();
            }
        }else{
            this->dataReport();
        }
        //故障刚刚结束，上报故障记录详情
        if(this->isNormal && faultStatus == 1){
            printf("故障刚刚结束,上报故障记录详情\n");
            sleep(1 * abnormalInterval);
            this->queryData(1);
            this->check();
            if(this->isNormal && faultStatus == 1){
                faultEndTime = this->getTime();
                this->faultRecordReport(currentFaultID, faultStartTime, faultEndTime, (int)(clock()-cTime)*CLOCKS_PER_SEC, currentAbnormalPhenomenon);
                this->faultID = -1;
                currentFaultID = -1;
                currentAbnormalPhenomenon.clear();
                faultStatus = 0;
            }
        }
        //故障在15分钟高频上报时就已经结束，现在上报故障记录详情
        else if(this->isNormal && faultStatus == 2){
            printf("//故障在15分钟高频上报时就已经结束,现在上报故障记录详情\n");
            sleep(1 * abnormalInterval);
            this->queryData(1);
            this->check();
            if(this->isNormal && faultStatus == 2){
                this->faultRecordReport(currentFaultID, faultStartTime, faultEndTime, (int)(clock()-cTime)*CLOCKS_PER_SEC, currentAbnormalPhenomenon);
                currentFaultID = -1;
                currentAbnormalPhenomenon.clear();
                faultStatus = 0;
            }
        }else{
            printf("error,未上报异常记录\n");
            currentFaultID = -1;
        }
        sleep(normalInterval);
    }
    return 0;
}