#include <vector>
// #include "spdlog/spdlog.h"
// #include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
// #include "spdlog/sinks/stdout_color_sinks.h" //support for console logging
#include "Oil_Level.h"
#include "Temperature.h"
#include "Vibration.h"
#include "Reporter.h"
#include "Status.h"
#include <unistd.h> //for sleep
#include <ctime>
#include <cstdio>

std::vector<std::pair<std::string, std::string>>(Vibration::vibrationFeatureList);

std::string OrgName("org-test");
std::string BucketName("bucket-test");

std::string Authorization("4OLhpnefenWAGp9QJ3x8qXTNzWSw6nVGgT1CM5r9yBp8uV6mZ8bSN3pV9aXUD3H9GTU0b5tam9YBFEBWsQSoCg==");
std::string QueryDataURL("http://localhost:8086/api/v2/query?org=" + OrgName);
std::string DataReportURL("192.168.2.181:8001/data/report");
std::string FaultDataReportURL("192.168.2.181:8001/fault/data/report");
std::string FaultRecordReportURL("192.168.2.181:8001/fault/record/report");

std::string PicturePath("/home/nvidia/Documents/Chengyi/pictures/result_pic.jpg");
// spdlog::logger* Logger;


int main(int argc, const char* argv[]){
	/*************************InitLogger*************************/
    // // console sink
    // auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    // console_sink->set_level(spdlog::level::warn);
    // console_sink->set_pattern("[%^%l%$] %v");

    // // file sink
    // auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/test.log");
    // file_sink->set_level(spdlog::level::trace);

    // // create logger based on console and file sink
    // spdlog::logger logger("main_logger", {console_sink, file_sink});
    // logger.set_level(spdlog::level::trace);  // set main_logger's log level
    // ::Logger = &logger;


    /************Init Vibration::vibrationFeatureList************/
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyZdz", "振动时域指标-最大值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyZxz", "振动时域指标-最小值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyFfz", "振动时域指标-峰峰值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyPjz", "振动时域指标-平均值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyJfz", "振动时域指标-均方值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyYxz", "振动时域指标-有效值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyQdzb", "振动时域指标-峭度指标"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyPdzb", "振动时域指标-偏度指标"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdSyYdzb", "振动时域指标-裕度指标"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdPyPpjz", "振动频域指标-频谱均值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdPyPlzx", "振动频域指标-频率重心"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdPyJfgpl", "振动频域指标-均方根频率"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdPyPpjfgz", "振动频域指标-频谱均方根值"));
    Vibration::vibrationFeatureList.push_back(std::pair<std::string, std::string>("zdPyBzcpl", "振动频域指标-标准差频率"));

    /************************Init Devices************************/
#ifdef device1
    Oil_Level* o_device = new Oil_Level("o_device1");
    Temperature* t_device = new Temperature("t_device1");
    Vibration* v_device_x = new Vibration("v_device1_x");
    Vibration* v_device_y = new Vibration("v_device1_y");
    Vibration* v_device_z = new Vibration("v_device1_z");
    Status* s_device = new Status("s_device1");
    // Reporter* reporter = new Reporter("RF896Z79XH");
    Reporter* reporter = new Reporter("I3EBZ6P7NG");
#endif

#ifdef device2
    Oil_Level* o_device = new Oil_Level("o_device2");
    Temperature* t_device = new Temperature("t_device2");
    Vibration* v_device_x = new Vibration("v_device2_x");
    Vibration* v_device_y = new Vibration("v_device2_y");
    Vibration* v_device_z = new Vibration("v_device2_z");
    Status* s_device = new Status("s_device2");
    Reporter* reporter = new Reporter("JYIP8ZZYKR");
#endif

#ifdef device3
    Oil_Level* o_device = new Oil_Level("o_device3");
    Temperature* t_device = new Temperature("t_device3");
    Vibration* v_device_x = new Vibration("v_device3_x");
    Vibration* v_device_y = new Vibration("v_device3_y");
    Vibration* v_device_z = new Vibration("v_device3_z");
    Status* s_device = new Status("s_device3");
    Reporter* reporter = new Reporter("JYIP8ZZYKR");
#endif
    // reporter->add(static_cast<Measurement*>(o_device));
    reporter->add(static_cast<Measurement*>(t_device));
    reporter->add(static_cast<Measurement*>(v_device_x));
    reporter->add(static_cast<Measurement*>(v_device_y));
    reporter->add(static_cast<Measurement*>(v_device_z));
    reporter->add(static_cast<Measurement*>(s_device));
    /**************************Process***************************/
    // reporter->queryData(1);
    // reporter->queryFaultData(10);
    // o_device1->show();
    // t_device1->show();
    // v_device1_x->show();
    // // reporter->dataReport();
    // // reporter->faultDataReport();
    // reporter->run(1, 0.5);

    // 1、2、3、4
    // while(1){
    //     reporter->queryData(1);
    //     reporter->dataReport();
    //     sleep(10);
    // }

    //5.高低频数据发送测试
    reporter->run2(10, 1);

    // test
    // while(1){
    //     std::string faultStartTime ="2022-04-17T12:54:26.00554275Z";
    //     reporter->queryFaultData(10);
    //     reporter->faultDataReport(faultStartTime);
    //     sleep(10);
    // }

    
    /***********************Free Resource************************/
    delete reporter;
    delete o_device;
    delete t_device;
    delete v_device_x;
    delete v_device_y;
    delete v_device_z;
    /****************************Quit****************************/
    return 0;
}
