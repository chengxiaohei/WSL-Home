#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

#include <string>

class Measurement
{
public:
    Measurement();
    ~Measurement();
    virtual int queryData(float frequency);
    virtual int queryFaultData(float frequency);
    virtual void cleanup();
    int write();
    virtual int show();
    virtual void check();
    virtual int getStatus();
    virtual std::string getTime();

    std::string deviceName;
    bool isNormal;
    std::string abnormalPhenomenon;
};


#endif //__MEASUREMENT_H__