#include "../include/FilterCore.h"

FilterCore::FilterCore():Base<double>::Base(){

}

FilterCore::FilterCore(double* in_data, UINT in_width, UINT in_height, UINT in_channels):
Base<double>::Base(in_data, in_width, in_height, in_channels){

}

FilterCore::FilterCore(UINT in_width, UINT in_height, UINT in_channels):
Base<double>::Base(in_width, in_height, in_channels){
    
}

void FilterCore::info(){
    std:: cout << "Info: " << "<type: FilterCore Width: " << width
                << " Height: " << height << " Channels: " << channels << ">\n";
}