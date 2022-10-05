#ifndef __VIBRATION_H__
#define __VIBRATION_H__

#include <vector>
#include "dataStructure.h"
#include "Measurement.h"

#define Vibration_Data_Flux "from(bucket: \"%s\") \
                                |> range(start: -1m)   \
                                |> last()   \
                                |> filter(fn: (r) => r._measurement == \"Vibration\" and r.device == \"%s\")    \
                                |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])    \
                                |> filter(fn: (r) => \
                                    r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or \
                                    r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or \
                                    r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or \
                                    r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\")"

#define Vibration_Fault_Flux    "from(bucket: \"%s\") \
                                    |> range(start: -5m)  \
                                    |> sample(n:%d, pos: 0)  \
                                    |> filter(fn: (r) => r[\"_measurement\"] == \"Vibration\" and r.device == \"%s\")   \
                                    |> drop(columns: [\"_start\", \"_stop\", \"_measurement\", \"device\"])   \
                                    |> filter(fn: (r) =>    \
                                        r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or \
                                        r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or \
                                        r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or \
                                        r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\" or r._field == \"%s\")"

class Vibration: public Measurement
{
public:
    Vibration(std::string);
    ~Vibration();
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
    static std::vector<std::pair<std::string, std::string>> vibrationFeatureList;
    Vibration_t info;
    std::string historyRawData;
    std::vector<Vibration_t> historyInfo;
};
#endif //__VIBRATION_H__