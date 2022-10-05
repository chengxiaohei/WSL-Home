#ifndef __DATA_STRUCTURE_H__
#define __DATA_STRUCTURE_H__

#include <string>

typedef struct {
    std::string device; // String   所属设备名称
    std::string time;   // String   数据生成时间
    std::string ywBfb;  // Float    油位百分比(String)
    std::string ywTp;   // String   油位图片
    int ywZcxh;         // Int      油位是否正常(0: 正常, 1: 不正常)
} Oil_Level_t;

typedef struct {
    std::string device; // String   所属设备名称
    std::string time;   // String   数据生成时间
    std::string wdSz;   // Float    温度数值(String)
    std::string wdSzAvg;// Float    前一分钟内温度数值平均值
    int wdZcxh;         // Int      温度是否正常(0: 正常, 1: 不正常)
} Temperature_t;

typedef struct {
    std::string device;     // String   所属设备名称
    std::string time;       // String   数据生成时间
    std::string zdSyZdz;	// Float	振动时域指标-最大值。(String)
    std::string zdSyZxz;	// Float	振动时域指标-最小值。(String)
    std::string zdSyFfz;	// Float	振动时域指标-峰峰值。(String)
    std::string zdSyPjz;	// Float	振动时域指标-平均值。(String)
    std::string zdSyJfz;	// Float	振动时域指标-均方值。(String)
    std::string zdSyYxz;	// Float	振动时域指标-有效值。(String)
    std::string zdSyQdzb;	// Float	振动时域指标-峭度指标。(String)
    std::string zdSyPdzb;	// Float	振动时域指标-偏度指标。(String)
    std::string zdSyYdzb;	// Float	振动时域指标-裕度指标。(String)
    std::string zdPyPpjz;	// Float	振动频域指标-频谱均值。(String)
    std::string zdPyPlzx;	// Float	振动频域指标-频率重心。(String)
    std::string zdPyJfgpl;	// Float	振动频域指标-均方根频率。(String)
    std::string zdPyPpjfgz;	// Float	振动频域指标-频谱均方根值。(String)
    std::string zdPyBzcpl;	// Float	振动频域指标-标准差频率。(String)
    std::string zdYssj;	    // Float	振动原始数据。(String)
    int  zdZcxh;	        // Int	    振动是否正常。(0: 正常, 其他: 对应指标异常)
} Vibration_t;

typedef struct {
    std::string device;     // String   所属设备名称
    std::string time;       // String   数据生成时间
    int opStatus;           // Int      设备运行状态。(0: 运行, 1: 启动, 2: 停止)
} Status_t;

#endif //__DATA_STRUCTURE_H__