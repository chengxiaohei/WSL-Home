#include "Measurement.h"

Measurement::Measurement(){
    this->isNormal = true;
    this->abnormalPhenomenon = std::string();
}

Measurement::~Measurement(){}

int Measurement::queryData(float frequency){
    //从数据库中读取数据
}

int Measurement::queryFaultData(float frequency){
    //从数据库中读取历史数据
}

void Measurement::cleanup(){
    //清除设备info结构体中当前数据
}

int Measurement::write(){
    //向数据库写入数据
}

int Measurement::show(){
    //显示当前设备信息（调试用）
}

void Measurement::check(){
    //检查当前设备健康状况
}

int Measurement::getStatus(){
    //检查返回当前运行状态, 0: 运行, 1: 启动, 2: 停止
}

std::string Measurement::getTime(){
    //获取当前时间信息
}

