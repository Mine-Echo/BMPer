#ifndef _bmpdef_h
#define _bmpdef_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"graphics.h"
#include "extgraph.h" 
#include"boolean.h"
#include"genlib.h"
#include "exception.h"
#include "strlib.h"
#include "imgui.h"
#include "gcalloc.h"
#include "simpio.h"
#include "gui.h"

#pragma pack(1)//�ṹ���и���Ա�ڴ水1�ֽڶ���
/*typedef struct tagBITMAPFILEHEADER
{
 unsigned short bfType; //����ͼƬ���͡� 'BM'
 unsigned int bfSize; //λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ��3-6�ֽڣ���λ��ǰ��
 unsigned short bfReserved1;//λͼ�ļ������֣�����Ϊ0(7-8�ֽڣ�
 unsigned short bfReserved2;//λͼ�ļ������֣�����Ϊ0(9-10�ֽڣ� 
 unsigned int bfOffBits;   //RGB����ƫ�Ƶ�ַ,λͼ���ݵ���ʼλ�ã��������λͼ��11-14�ֽڣ���λ��ǰ��
}BITMAPFILEHEADER;
 
typedef struct tagBITMAPINFOHEADER
{
 unsigned int biSize;	//���ṹ��ռ���ֽ�����15-18�ֽڣ�
 unsigned int biWidth;	//λͼ�Ŀ�ȣ�������Ϊ��λ��19-22�ֽڣ�
 unsigned int biHeight;	//λͼ�ĸ߶ȣ�������Ϊ��λ��23-26�ֽڣ�
 unsigned short biPlanes;	//Ŀ���豸�ļ��𣬱���Ϊ1(27-28�ֽڣ�
 unsigned short biBitCount;	//ÿ�����������λ����������1��˫ɫ����29-30�ֽڣ�,4(16ɫ����8(256ɫ��16(�߲�ɫ)��24�����ɫ��֮һ
 unsigned int biCompression;//λͼѹ�����ͣ�������0����ѹ��������31-34�ֽڣ�
//1(BI_RLE8ѹ�����ͣ���2(BI_RLE4ѹ�����ͣ�֮һ
 
 unsigned int biSizeImage;	//λͼ�Ĵ�С(���а�����Ϊ�˲���������4�ı�������ӵĿ��ֽ�)�����ֽ�Ϊ��λ��35-38�ֽڣ�
 unsigned int biXPelsPerMeter;//λͼˮƽ�ֱ��ʣ�ÿ����������39-42�ֽڣ�
 unsigned int biYPelsPerMeter;//λͼ��ֱ�ֱ��ʣ�ÿ����������43-46�ֽ�)
 unsigned int biClrUsed;	//λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ�
 unsigned int biClrImportant;	//λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ�
}BITMAPINFOHEADER;
*/
//ͼƬ��Ϣ�ṹ��
typedef struct node
{
 BITMAPFILEHEADER head;
 BITMAPINFOHEADER info;
 unsigned char *bmp_data;//ͼƬ���� 
 int InitX;
 int InitY;//ͼƬ��ʼ�㣬���½� 
 struct node *next;
 bool changebase;
}BMP_node;

 extern BMP_node *top;  //����ջ 
 extern BMP_node *base; //��׼ջ 
 
 extern double Xratio;
 extern double Yratio;//���ű��� 
 extern bool IS_LOCK;

#endif
