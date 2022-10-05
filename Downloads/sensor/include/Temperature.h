#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#include <vector>
#include "dataStructure.h"
#include "Measurement.h"

#define Temperature_Data_Flux   "from(bucket: \"%s\") \
                                    |> range(start: -1m)   \
                                    |> last()   \
                                    |> filter(fn: (r) => r._measurement == \"Temperature\" and r.device == \"%s\")    \
                                    |> filter(fn: (r) => r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\")  \
                                    |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])"

#define Temperature_Fault_Flux  "from(bucket: \"%s\") \
                                    |> range(start: -5m)   \
                                    |> sample(n:%d, pos: 0)  \
                                    |> filter(fn: (r) => r._measurement == \"Temperature\" and r.device == \"%s\")    \
                                    |> filter(fn: (r) => r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\")  \
                                    |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])"

class Temperature: public Measurement
{
public:
    Temperature(std::string);
    ~Temperature();
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
    Temperature_t info;
    std::string historyRawData;
    std::vector<Temperature_t> historyInfo;
};

#endif //__TEMPERATURE_H__