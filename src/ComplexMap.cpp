#include "../include/ComplexMap.h"

ComplexMap::ComplexMap():Base<fftw_complex>::Base(){

}

ComplexMap::ComplexMap(UINT in_width, UINT in_height, UINT in_channels):
Base<fftw_complex>::Base(in_width, in_height, in_channels){

}

ComplexMap::ComplexMap(fftw_complex* in_data, UINT in_width, UINT in_height, UINT in_channels):
Base<fftw_complex>::Base(in_data, in_width, in_height, in_channels){

}

ComplexMap::ComplexMap(const Base<uchar>& img):
ComplexMap(img.get_width(), img.get_height(), img.get_channels()){
    Base_assert(channels == 1);
    for(int i = 0; i < width*height*channels; ++i){
        data[i][0] = img.get_data_handle()[i];
    }
}

ComplexMap::ComplexMap(const Base<fftw_complex>& complex_base):Base<fftw_complex>::Base(complex_base){

}

void ComplexMap::info(){
    std:: cout << "Info: " << "<type: ComplexMap Width: " << width
                << " Height: " << height << " Channels: " << channels << ">\n";
}