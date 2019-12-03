#include "CvImg.h"
#include "ComplexMap.h"

int main(){
    CvImg b("../img/lena.jpeg");//读取图片
    //b(1,1,0) = 10;
    //CvImg a("../img/lena.jpeg");
    //a.stick(b, {1,1});
    Const_CvImgView a(b, {1,1,256,256});
    //std::cout << a.get_height() <<" "<< a.get_width() <<std::endl;
    auto region = a.get_region();
    for(UINT x = region[0]; x <= region[2]; ++x){
        for(UINT y = region[1]; y <= region[3]; ++y){
            a(x, y, 0) = 0;
        }
    }

    //a.set_region({257, 257,500,500});
    //std::cout << a.get_height() <<" "<< a.get_width() <<std::endl;
    //auto region = a.get_region();
    //for(UINT x = region[0]; x <= region[2]; ++x){
        //for(UINT y = region[1]; y <= region[3]; ++y){
            //a(x, y, 0) = 0;
        ///}
    //}



    //a.flip();
    //a.add_show_list();
    //b.add_show_list();

    //return CvImg::imshow();
}