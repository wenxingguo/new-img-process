#include "CvImg.h"
#include "ComplexMap.h"

int main(){
    CvImg b("../img/cat.png");//读取图片
    b.add_show_list();
    return CvImg::imshow();
}