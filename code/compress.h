#ifndef _compress_h
#define _compress_h

#include"bmpdef.h"
#include"bmp.h"

//ѹ��ͼ��ĳ��ͨ����R��G��B������ 
int Compress(unsigned char *source,unsigned int n); 

//��ͼ�����ݷ�Ϊ����ͨ�����������飬������ѹ������ļ� 
void SaveCompress(const unsigned char *source,const char *bmp_path);

//��ȡѹ�����ͼ�����ݣ������ú������н�ѹ��������ѹ���ͼ��չʾ��ͼ�ν����� 
void ReadCompressImage(const char* path);

//��ĳ��ͨ����ѹ��������ݽ��н�ѹ 
void Unzip(const unsigned char*compress,int n,unsigned char *unzip);

#endif	
	
	
	

