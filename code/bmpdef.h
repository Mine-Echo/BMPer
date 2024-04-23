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

#pragma pack(1)//结构体中各成员内存按1字节对齐
/*typedef struct tagBITMAPFILEHEADER
{
 unsigned short bfType; //保存图片类型。 'BM'
 unsigned int bfSize; //位图文件的大小，以字节为单位（3-6字节，低位在前）
 unsigned short bfReserved1;//位图文件保留字，必须为0(7-8字节）
 unsigned short bfReserved2;//位图文件保留字，必须为0(9-10字节） 
 unsigned int bfOffBits;   //RGB数据偏移地址,位图数据的起始位置，以相对于位图（11-14字节，低位在前）
}BITMAPFILEHEADER;
 
typedef struct tagBITMAPINFOHEADER
{
 unsigned int biSize;	//本结构所占用字节数（15-18字节）
 unsigned int biWidth;	//位图的宽度，以像素为单位（19-22字节）
 unsigned int biHeight;	//位图的高度，以像素为单位（23-26字节）
 unsigned short biPlanes;	//目标设备的级别，必须为1(27-28字节）
 unsigned short biBitCount;	//每个像素所需的位数，必须是1（双色）（29-30字节）,4(16色），8(256色）16(高彩色)或24（真彩色）之一
 unsigned int biCompression;//位图压缩类型，必须是0（不压缩），（31-34字节）
//1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
 
 unsigned int biSizeImage;	//位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
 unsigned int biXPelsPerMeter;//位图水平分辨率，每米像素数（39-42字节）
 unsigned int biYPelsPerMeter;//位图垂直分辨率，每米像素数（43-46字节)
 unsigned int biClrUsed;	//位图实际使用的颜色表中的颜色数（47-50字节）
 unsigned int biClrImportant;	//位图显示过程中重要的颜色数（51-54字节）
}BITMAPINFOHEADER;
*/
//图片信息结构体
typedef struct node
{
 BITMAPFILEHEADER head;
 BITMAPINFOHEADER info;
 unsigned char *bmp_data;//图片数据 
 int InitX;
 int InitY;//图片起始点，左下角 
 struct node *next;
 bool changebase;
}BMP_node;

 extern BMP_node *top;  //操作栈 
 extern BMP_node *base; //基准栈 
 
 extern double Xratio;
 extern double Yratio;//缩放比例 
 extern bool IS_LOCK;

#endif
