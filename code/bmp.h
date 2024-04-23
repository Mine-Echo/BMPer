#ifndef _bmp_h
#define _bmp_h

#include"bmpdef.h"

#define UI_X 2.8       //缩放条UI的起始X坐标
#define UI_Y 2.0       //缩放条UI的起始Y坐标
#define UILenth 2      //缩放条的长度
#define UIInterval 0.5   //长、宽缩放条UI的间距
#define UI_Button_X 0.1 //拖动按钮的宽度
#define UI_Button_Y 0.4 //拖动按钮的高度
#define ScreenY 10     //窗口的高度

extern int dx1,dx2,dy1,dy2;//裁剪偏移量 

//对图片进行缩放操作 
void Reshape(int new_width,int new_height);

//对图片进行旋转以及镜像翻转操作 
void Rotate(int mode);

//对图片进行裁剪 
void CutImage(int InitX,int InitY,int width,int height);

//图片读入 
int ReadImage(const char* old_bmp_path);

//图片保存 
int PutImage(const char *new_bmp_path);

//画裁剪模式下的UI与按键 
void DrawCutUI(int dx1,int dx2,int dy1,int dy2);

//将图片显示在窗口 
int ShowImage();

//刷新窗口，更新菜单栏、侧边栏、下方信息栏的状态 
void Display();

//将指定区域清空 
void ClearSpace(double x,double y,double width,double height);

//更新下方信息栏的位置信息 
void UpdateLocation(int X,int Y);

//更新下方信息栏的长宽与比例信息 
void UpdateSize(double width,double height);
#endif
