#ifndef _convolution_h
#define _convolution_h

#include"bmpdef.h"

//��ͼƬ���б�Ե��� 
unsigned char* fill();

//��ͼƬ���о������ 
void convolution(double core[3][3]);

//��ͼƬת��Ϊ�Ҷ�ͼ 
void Gray();

//��ͼƬ���ж�ֵ������ 
void Binarization(int n);

#endif 
