#ifndef _menu_h
#define _menu_h
 
#include"bmpdef.h"
#include"bmp.h"
#include"callback.h"

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define WindowH 10  //窗口高度 
#define WindowW 16  //窗口宽度 
#define INTERVAL 1  

//需要打开或保存的文件名 
extern char FileName[50];
extern char name[50];
//文件指针 
extern FILE *fp;

//布尔变量 
extern bool OPEN;     //文件是否打开 
extern bool SAVE;      //文件是否保存 
extern bool IS_TAILOR;  //裁剪模式或选择模式 
extern bool IS_PLAY;   //背景音乐是否打开 
extern HWND window;   //窗口句柄 

//将图片、菜单、按钮等展示在图形界面中 
//void display();

//在图形界面画出菜单 
void DrawMenu();

//处理文件菜单栏的选择 
void SelectFile(int selection);

//选择关闭时进行一些判断
void ChoiceOfClose(int choice);

//选择退出时进行一些判断 
void ChoiceOfExit(int choice);

//打开文件时初始化一些变量
void Init(); 

//处理基础功能菜单的选择 
void SelectFunction(int selection);

//处理其他功能的选择 
void SelectFunction2(int selection); 

//处理关于菜单的选择 
void SelectAbout(int selection);

//在图形界面画出状态信息栏 
void DrawInformationBar(double x,double y,double w,double h,double w_rate,double h_rate);

//功能：在图形化界面画出按钮一栏 
void DrawButton();

#endif
