/*
这个文件定义了储存复数方正的类
作为快速傅里叶变换的输入和输出。
*/
#ifndef COMP_MAP_H
#define COMP_MAP_H
#include "fftw3.h"
#include "Base.h"

class ComplexMap:public Base<fftw_complex>{
    public:
    ComplexMap();
    
    ComplexMap(UINT in_width, UINT in_height, UINT in_channels);

    ComplexMap(fftw_complex* data, UINT in_width, UINT in_height, UINT in_channels);

    ComplexMap(const Base<uchar>& img);//用于生成in

    ComplexMap(const Base<fftw_complex>& complex_base);

    ~ComplexMap(){
        if(data){
            fftw_free(data); //内存泄漏
            data = nullptr;
        }
    }

    void info();


};

#endif