/*
定义滤波核心的类别。
*/
#ifndef FILTER_CORE_H
#define FILTER_CORE_H
#include "Base.h"

class FilterCore:public Base<double>{
    public:
    FilterCore();

    FilterCore(double * in_data, UINT in_width, UINT in_height, UINT in_channels);

    FilterCore(UINT in_width, UINT in_height, UINT in_channels);

    void info() const;

};
#endif