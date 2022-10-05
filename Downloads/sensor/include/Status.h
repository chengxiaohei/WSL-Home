#ifndef __STATUS_H__
#define __STATUS_H__

#include <vector>
#include "dataStructure.h"
#include "Measurement.h"  //for parent class Measurement


#define Status_Data_Flux    "from(bucket: \"%s\") \
                                |> range(start: -1m)   \
                                |> last()   \
                                |> filter(fn: (r) => r._measurement == \"Status\" and r.device == \"%s\")    \
                                |> filter(fn: (r) => r._field == \"%s\")     \
                                |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])"

#define Status_Fault_Flux   "from(bucket: \"%s\") \
                                    |> range(start: -5m)   \
                                    |> sample(n:%d, pos: 0)   \
                                    |> filter(fn: (r) => r._measurement == \"Status\" and r.device == \"%s\")    \
                                    |> filter(fn: (r) => r._field == \"%s\")    \
                                    |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])"

class Status: public Measurement
{
public:
    Status(std::string deviceName);
    ~Status();
    int queryData(float frequency);
    int queryFaultData(float frequency);
    void cleanup();
    int write();
    int show();
    void check();
    int getStatus();
    std::string getTime();
    static size_t parseData(void *queriedData, size_t size, size_t nmemb, void *userData);
    static size_t parseFaultData(void *queriedData, size_t size, size_t nmemb, void *userData);
    Status_t info;
    std::string historyRawData;
    std::vector<Status_t> historyInfo;
};


#endif //__STATUS_H__