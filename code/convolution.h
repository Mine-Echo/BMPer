#ifndef _convolution_h
#define _convolution_h

#include"bmpdef.h"

//对图片进行边缘填充 
unsigned char* fill();

//对图片进行卷积操作 
void convolution(double core[3][3]);

//将图片转换为灰度图 
void Gray();

//对图片进行二值化操作 
void Binarization(int n);

#endif 
