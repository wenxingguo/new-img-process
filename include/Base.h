/*
这个文件定义了储存数据的抽象基类，以及一些公共方法
*/
#ifndef BASE_H
#define BASE_H
 /*  --------------------------------------------x
     |
     |
     |
     |
     |
     |                  base x，y从1开始
     |
     |
     |
     |
     |
     |
     |
     |
     |
     y
     
*/
#include <iostream>
#include <vector>
#include <assert.h>
#define Base_assert assert

typedef unsigned int UINT;
typedef std::vector<UINT> REGION; //[x1, y1, x2, y2]
typedef std::vector<UINT> POINT;//[x1,y1]
typedef unsigned char uchar;

template<class DataType>
class Base{
    typedef DataType* DataTypep;
    protected:
    UINT width;

    UINT height;

    UINT channels;
    
    DataTypep data;
    
    public: 
    Base():width(0),height(0),channels(0),data(nullptr){}

    Base(DataTypep in_data, int in_width, int in_height, int in_channals);

    Base(int in_width, int in_height, int in_channels);

    Base(const Base<DataType>& other_Base); //拷贝构造函数

    DataType& operator()(UINT x, UINT y, UINT j = 0);

    DataType& operator()(UINT x, UINT y, UINT j = 0) const; //访问常量对象;

    Base<DataType>& operator=(const Base<DataType>& r_base);

    virtual void info() = 0;
    
    UINT get_width() const{
        return width;
    }

    void set_width(UINT in_width){
        width = in_width;
    }
    
    UINT get_height() const{
        return height;
    }

    void set_height(int in_height) {
        height = in_height;
    }
    
    UINT get_channels() const{
        return channels;
    }

    void set_channels(int in_channels){
        channels = in_channels;
    }
    
    DataTypep get_data_handle() const{
        return data;
    }
    
    ~Base(){
        if(data){
            delete [] data; //有可能还会造成内存泄漏
            data = nullptr;
        }
    }

    void flip(); //反转

    void stick(const Base<DataType>& sub_Base, POINT point);

    void sub_Base(Base<DataType>& subBase, REGION domain); //获得一个Base的子图
};

template<class DataType>
Base<DataType>::Base(DataTypep in_data, int in_width, int in_height, int in_channels)
:data(in_data),width(in_width),height(in_height),channels(in_channels){
}

template<class DataType>
Base<DataType>::Base(int in_width, int in_height, int in_channels):width(in_width),height(in_height),
channels(in_channels){
    data = new DataType[width*height*channels]();
}

template<class DataType>
Base<DataType>::Base(const Base<DataType>& other_base):width(other_base.get_width()),height(other_base.get_height()),
channels(other_base.get_channels()){
    data = new DataType[width*height*channels]; //申请内存
    memcpy(data, other_base.get_data_handle(), sizeof(DataType)*width*height*channels); //直接拷贝内存
}

template<class DataType>
DataType& Base<DataType>::operator()(UINT x, UINT y, UINT j){
    Base_assert(0 < x && x <= width && 0 < y && y <= height && 0 <= j && j < channels);
    return data[((y-1)*width+x-1)*channels+ j];
}

template<class DataType>
DataType& Base<DataType>::operator()(UINT x, UINT y, UINT j) const{ //需要对常量对象访问
    Base_assert(0 < x && x <= width && 0 < y && y <= height && 0 <= j && j < channels);
    return data[((y-1)*width+x-1)*channels+ j];
}

template<class DataType>
Base<DataType>& Base<DataType>::operator=(const Base<DataType>& r_base){
    channels = r_base.get_channels();
    width = r_base.get_width();
    height = r_base.get_height();
    if(data != nullptr) delete [] data; // 内存泄漏
    data = new DataType[width*channels*height];
    memcpy(data, r_base.get_data_handle(), sizeof(DataType)*width*channels*height);
    return *this;
    
}

template<class DataType>
void Base<DataType>::flip(){
    DataType* buffer = new DataType[width*height*channels];
    UINT pose = 0;
    for(UINT x = width; x >= 1; --x){
        for(UINT y = height; y >= 1; --y){
            for(UINT j = 0; j < channels; ++j){
                buffer[pose++] = (*this)(x, y, j); 
            }
        }
    }
    //交换内存
    delete [] data; //这里有可能会造成内存泄露，因为DataType不一定是简单类型
    data = buffer;
    std::swap(height, width);
}

template<class DataType>
void Base<DataType>::stick(const Base<DataType>& sub_Base, POINT position){
    Base_assert(sub_Base.get_channels() == channels);
    Base_assert(position.size() == 2);
    int y_pose = 1;
    for(int y = position[1]; y <= position[1]+sub_Base.get_height()-1; ){
        //拷贝内存
        memcpy(&(*this)(position[0], y++, 0), &sub_Base(1, y_pose++, 0), sub_Base.get_width()*channels*sizeof(DataType));
    }

}

template<class DataType>
void Base<DataType>::sub_Base(Base<DataType>& sub_Base, REGION domain){
    Base_assert(domain.size() == 4);
    Base_assert(sub_Base.get_channels() == channels);
    int pose = 1;
    for(int y = domain[1]; y <= domain[3]; ++y){
        //拷贝内存
        memcpy(&sub_Base(1, pose++, 0), &(*this)(domain[0], y, 0), sub_Base.get_width()*channels*sizeof(DataType));
    }
}

#endif