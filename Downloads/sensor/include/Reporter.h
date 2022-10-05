#ifndef __REPORTER_H__
#define __REPORTER_H__

#include <string>
#include <vector>

#include "json.hpp"
#include "dataStructure.h"
#include "Measurement.h"

// extern spdlog::logger* Logger;

#define DataReportFormat "data%s[%d].%s"
#define FaultDataReportFormat "data.data%s[%d].%s"

class Reporter
{
public:
    Reporter(std::string deviceCode);
    Reporter(std::string deviceCode, std::vector<Measurement*> devices);
    ~Reporter();
    int add(Measurement*);
    int add(std::vector<Measurement*>);
    int queryData(float);
    int queryFaultData(float);
    int dataReport();
    int faultDataReport(std::string);
    int faultRecordReport(int, std::string, std::string, int, std::string);
    void check();
    void getAbnormalPhenomenon();
    std::string getTime();
    int run(int normalInterval, int abnormalInterval);
    int run2(int normalInterval, int abnormalInterval);
    static size_t checkResponse(void *response, size_t size, size_t nmemb, void *userData);
    static size_t getFaultID(void *response, size_t size, size_t nmemb, void *userData);
private:
    std::string deviceCode;
    std::vector<Measurement*> devices;
    int faultID;
    int status;
    bool isNormal;
    std::string abnormalPhenomenon;
};

#endif //__REPORTER_H__