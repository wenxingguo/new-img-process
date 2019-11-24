#include "../include/CvImg.h"

std::vector<const CvImg*> CvImg::show_list;

std::vector<std::string> CvImg::show_img_name;

CvImg::CvImg():Base<uchar>::Base(){

}

CvImg::CvImg(UINT in_width, UINT in_height, UINT in_channels):Base<uchar>::Base(in_width, in_height, in_channels){

}

CvImg::CvImg(uchar* in_data, UINT in_width, UINT in_height, UINT in_channels)
:Base<uchar>::Base(in_data, in_width, in_height, in_channels){

}

CvImg::CvImg(const Base<uchar>& img_base):Base<uchar>::Base(img_base){

}

CvImg::CvImg(const Base<fftw_complex>& complex_map, double (*f)(const fftw_complex&)):
CvImg(complex_map.get_width(), complex_map.get_height(), complex_map.get_channels()){
    Base_assert(channels == 1);
    double max = 0, min = 0;
    for(int i = 0; i < width*height*channels; ++i){
        data[i] = f(complex_map.get_data_handle()[i]);
        min = min > data[i]? data[i]:min;
        max = max < data[i]? data[i]:max;
    }

    max = max -min;
    for (int i = 0; i < width*height*channels; ++i){
        data[i] = (data[i] - min)/max*255;
    }
}

CvImg::CvImg(const char* filename, int flag){
    cv::Mat img_ = cv::imread(filename, flag);
    get_data_from_mat(img_);

}

void CvImg::add_show_list(const char* s) const{
    //将当前指针加入显示列表
    show_list.push_back(this);
    show_img_name.push_back(s);
}

void CvImg::img_save(const char* file_name, COLORTYPE flag){
    if(channels == 1){
        cv::imwrite(file_name, cv::Mat(height, width, 0, data));
    }
    cv::Mat temp(height, width, flag);
    cv::cvtColor(cv::Mat(height, width, flag, data), temp, cv::COLOR_RGB2BGR);
    cv::imwrite(file_name, temp);
}

void CvImg::info(){
    std:: cout << "Info: " << "<type: CvImg Width: " << width
                << " Height: " << height << " Channels: " << channels << ">\n";
}

int CvImg::imshow(){
    if(show_list.size()==0){
        fl_alert("No img to display!!");
        return 0;
    }
    Fl_Window** windows_list = new Fl_Window*[show_list.size()];
    for(int i = 0; i < show_list.size(); ++i){
        windows_list[i] = new Fl_Window(show_list[i]->get_width(), show_list[i]->get_height(), show_img_name[i].data());
        Fl_Box* b = new Fl_Box(0,0,show_list[i]->get_width(), show_list[i]->get_height());
        Fl_RGB_Image *img = new Fl_RGB_Image(show_list[i]->get_data_handle(), show_list[i]->get_width(), show_list[i]->get_height(), show_list[i]->get_channels());
        b -> image(img);
        windows_list[i]->end();
        windows_list[i]->show();
    }
    delete [] windows_list; //ok
    return Fl::run();
}

void CvImg::get_data_from_mat(const cv::Mat& mat){
    if(!mat.data){
        fl_alert("data error !!!");
        std::exit(-1);
    }
    width = mat.cols;
    height = mat.rows;
    channels = mat.channels();
    data = new uchar[width*height*channels];
    //opencv默认读取的图片通道是BGR， 转化为RGB
    if(channels != 1) cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    memcpy(data, mat.data, sizeof(uchar)*width*channels*height);
}

double CvImg::log_amplitude(const fftw_complex& complex){
    return std::log(std::sqrt(complex[0]*complex[0]+complex[1]*complex[1]));
}