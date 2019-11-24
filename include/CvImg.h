/*
这个文件定义了储存图片数据的类
包括一些方法
显示
读写图片
对图片像素的操作
*/

#ifndef CVIMG_H
#define CVIMG_H
#include <string>
#include <cstdlib>
#include "Base.h"
#include <cmath>
#include "fftw3.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/fl_ask.H>

class CvImg:public Base<uchar>
{
    public:
    enum COLORTYPE{
        C3 = 16,
        C2 = 8,
        C1 = 0
    };

    CvImg();

    CvImg(UINT in_width, UINT in_height, UINT in_channels);

    CvImg(uchar* in_data, UINT in_width, UINT in_height, UINT in_channels);

    CvImg(const Base<uchar>& img_base);
    
    //包含将值映射到0~255的线性映射
    CvImg(const Base<fftw_complex>& complex_map, double (*f)(const fftw_complex&) = CvImg::log_amplitude); //将傅里叶变换后的数据转化为图像
    //0是灰度图
    CvImg(const char* filename, int flag = 1);

    void add_show_list(const char* s = "Untitled") const;

    void img_save(const char* file_name,  COLORTYPE colortype);

    void info();

    static int imshow();

    private:
    //保存需要显示的图片的指针
    static std::vector<const CvImg*> show_list; //这里需要常量指针，处理常量CvImg对象。
    //定义显示图片的名字
    static std::vector<std::string> show_img_name;
    //从opencv Mat中获取数据，其中包括将通道反转
    void get_data_from_mat(const cv::Mat& mat);
    //还需定义两个默认的由傅里叶结果到图片的函数/(辐值)(辐角) double (*f)(const fftw_complex&)
    static double log_amplitude(const fftw_complex& complex);

};

#endif