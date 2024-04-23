#ifndef _compress_h
#define _compress_h

#include"bmpdef.h"
#include"bmp.h"

//压缩图像某个通道（R、G、B）数据 
int Compress(unsigned char *source,unsigned int n); 

//将图像数据分为三个通道的数据数组，并保存压缩后的文件 
void SaveCompress(const unsigned char *source,const char *bmp_path);

//读取压缩后的图像数据，并调用函数进行解压，并将解压后的图像展示在图形界面上 
void ReadCompressImage(const char* path);

//将某个通道的压缩后的数据进行解压 
void Unzip(const unsigned char*compress,int n,unsigned char *unzip);

#endif	
	
	
	

