#ifndef __OIL_LEVEL_H__
#define __OIL_LEVEL_H__

#include <vector>
#include "dataStructure.h"
#include "Measurement.h"  //for parent class Measurement


#define Oil_Level_Data_Flux "from(bucket: \"%s\") \
                                |> range(start: -1m)   \
                                |> last()   \
                                |> filter(fn: (r) => r._measurement == \"Oil_Level\" and r.device == \"%s\")    \
                                |> filter(fn: (r) => r._field == \"%s\" or r._field == \"%s\")    \
                                |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])"

#define Oil_Level_Fault_Flux    "from(bucket: \"%s\") \
                                    |> range(start: -5m)   \
                                    |> sample(n:%d, pos: 0)   \
                                    |> filter(fn: (r) => r._measurement == \"Oil_Level\" and r.device == \"%s\")    \
                                    |> filter(fn: (r) => r._field == \"%s\" or r._field == \"%s\")    \
                                    |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])"

class Oil_Level: public Measurement
{
public:
    Oil_Level(std::string deviceName);
    ~Oil_Level();
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
    Oil_Level_t info;
    std::string historyRawData;
    std::vector<Oil_Level_t> historyInfo;
};


#endif //__OIL_LEVEL_H__