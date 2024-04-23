#include"bmp.h"

double Xratio = 1.0;//图片长缩放比例
double Yratio = 1.0;//图片宽缩放比例 

void Reshape(int new_width,int new_height)
{
 int i=0,j=0;  //循环变量 
 int srcX,srcY;//缩放后图片的像素坐标所对应的原图像素坐标 
 char *new_file;//指向新图片数据的指针 
 char *old_file;//指向旧图片数据的指针 
  
 char *old_data=base->bmp_data;
 int old_width=base->info.biWidth;
 int old_height=base->info.biHeight;//获取base节点数据 
 
 BMP_node *new_node=(BMP_node*)CopyNode(base);//复制base节点的数据
 if(top!=NULL)
 {
 new_node->InitX=top->InitX;
 new_node->InitY=top->InitY;
 }//若已打开图片，则复制图片的起始位点，因为缩放不改变图片位置 
 free(new_node->bmp_data);
 new_node->bmp_data=(char*)malloc(new_width*new_height*3);//释放并重分配内存 
 
 new_node->head.bfSize=new_width*new_height*3+54;
 new_node->info.biWidth=new_width;
 new_node->info.biHeight=new_height;//构造新节点文件头与信息头 
 
 top=(BMP_node*)PushStack(top,new_node);//压栈 
 
 for(i=0;i<new_height;i++)
 {
  srcY=i*old_height/new_height;
  new_file=new_node->bmp_data+i*new_width*3;
  old_file=old_data+srcY*old_width*3;
  for(j=0;j<new_width;j++)
  {
   srcX=j*old_width/new_width;//依据长宽比例，构造一个缩放后图片与原图片之间的映射，一一获取新图片的像素数据 
   memcpy(new_file+j*3,old_file+srcX*3,3);//数据拷贝
  }
 }
} 

void Rotate(int mode)
{
 BMP_node* new_base=(BMP_node*)CopyNode(base);//新建旋转后的基准数据 
 int height=base->info.biHeight;
 int width=base->info.biWidth;//获取图片长宽 
 int i,j;
 if(mode==1||mode==2)//顺时针、逆时针旋转操作 
 {
   if(mode==1)
   { 
	for(i=0;i<height;i++)
	 {
		for(j=0;j<width;j++)
		{
		memcpy(new_base->bmp_data+(width-1-j)*height*3+i*3,
				   base->bmp_data+i*width*3+j*3,3);
		}
	 }
   }
   else
   {
   	for(i=0;i<height;i++)
	 {
		for(j=0;j<width;j++)
		{
		memcpy(new_base->bmp_data+j*height*3+(height-1-i)*3,
				   base->bmp_data+i*width*3+j*3,3);
		}
	 }
   }
	 new_base->info.biHeight=base->info.biWidth;
	 new_base->info.biWidth=base->info.biHeight;//交换旋转后图片的长宽值 
}
else if(mode==3)//左右翻转 
{
	for(i=0;i<height;i++)
	 {
		for(j=0;j<width;j++)
		{
		memcpy(new_base->bmp_data+i*width*3+j*3,
				   base->bmp_data+i*width*3+(width-1-j)*3,3);
		}
	 }
} 
else if(mode==4)//上下翻转 
{
	for(i=0;i<height;i++)
	 {
		for(j=0;j<width;j++)
		{
		memcpy(new_base->bmp_data+i*width*3+j*3,
				   base->bmp_data+(height-1-i)*width*3+j*3,3);
		}
	 }
} 
 base=(BMP_node *)PushStack(base,new_base);//压栈 
}

void CutImage(int InitX,int InitY,int width,int height)
{
 int baseX=InitX/Xratio;
 int baseY=InitY/Yratio;//基准起始裁剪位点 
 int base_width=width/Xratio; 
 int base_height=height/Yratio;//根据当前图片相对于基准的比例，逆向计算出在基准中所要裁减的长宽 
 
 if(baseX+base_width>base->info.biWidth)base_width=base->info.biWidth-baseX;
 if(baseY+base_height>base->info.biHeight)base_height=base->info.biWidth-baseY;//防止获取基准长宽数据时越界 
 
 BMP_node *new_base=(BMP_node*)CopyNode(base);//复制基准节点信息 
 free(new_base->bmp_data);
 new_base->bmp_data=(char*)malloc(base_width*base_height*3);//释放并重分配内存 
 char *new_file=new_base->bmp_data;//指向新图片数据的指针 
 char *old_file=base->bmp_data;//指向旧图片数据的指针 
 
 int i;//循环变量 
 old_file+=3*(baseY*base->info.biWidth+baseX);//先将指针移动到起始位点的位置 
 for(i=0;i<base_height;i++)
 {
 	memcpy(new_file,old_file,base_width*3);
 	old_file+=3*base->info.biWidth;
 	new_file+=3*base_width;//数据拷贝实现裁剪 
 }
 
 new_base->info.biHeight=base_height;
 new_base->info.biWidth=base_width;//构造新基准的长宽数据(无需构造biSize数据，因为在后续的Reshape函数中还会恢复当前图片的缩放比例并计算文件大小) 
 
 base=(BMP_node *)PushStack(base,new_base);//压栈 
 Reshape(width,height);//恢复长宽比例 
 top->changebase=TRUE;//标记基准发生改变 
}

int ReadImage(const char* old_bmp_path)
{  
 FILE *fpr=fopen(old_bmp_path,"rb");

 base=(BMP_node *)InitList();//初始化栈 
 //读取原照片的头信息
 fread(&base->head,sizeof(BITMAPFILEHEADER),1,fpr);
 fread(&base->info,sizeof(BITMAPINFOHEADER),1,fpr);

 int old_width=base->info.biWidth;//获取原图片的宽
 int old_height=base->info.biHeight;//获取原图片的高
 
 int i;
 int bias=old_width%4; //计算相对于四字节的偏差值 
 base->bmp_data=(char*)malloc(old_width*old_height*3);
 char *data=(char*)malloc(old_width*old_height*3+old_height*bias);
 fseek(fpr,54,SEEK_SET);
  //获取原图片的位图数据
 fread(data,old_width*old_height*3+old_height*bias,1,fpr);
 for(i=0;i<old_height;i++)
 {
 	memcpy(base->bmp_data+i*old_width*3,data+i*(old_width*3+bias),old_width*3);//跳过非四倍数宽的图片的填充字符 
 }
 free(data);
 int width=(int)(old_width)/4*4;
 int height=(int)(old_height)/4*4;
 Reshape(width,height);//初始化top栈 

 Display();
 ShowImage();
 //关闭文件
 fclose(fpr);
 return 0;
}

int PutImage(const char *new_bmp_path)
{
 FILE *fpw=fopen(new_bmp_path,"wb+");
 
 //将修改过的头信息写进新照片
 fwrite(&top->head,sizeof(BITMAPFILEHEADER),1,fpw);
 fwrite(&top->info,sizeof(BITMAPINFOHEADER),1,fpw);
 fseek(fpw,54,SEEK_SET);
 fwrite(top->bmp_data,top->info.biWidth*top->info.biHeight*3,1,fpw);
 //关闭文件 
 fclose(fpw);
}

int ShowImage()//显示top的图像数据 
{
	int X=top->InitX;
	int Y=top->InitY;
	int Width=top->info.biWidth;
	int Height=top->info.biHeight;
	unsigned char *data=top->bmp_data;
	
	int xmove=0,ymove=0;
	int i;
 	for(i=0;i<Width*Height*3;i+=3,data+=3)
 	{
 		int blue = (int)*data;
 		int green = (int)*(data+1);
 		int red = (int)*(data+2);//获取颜色数据 
 		DrawPixel(X+xmove,Y-ymove,red,green,blue);//打点 
 		xmove++;
 		if(xmove==Width)
 		{
 			xmove=0;
 			ymove++;
 		}
 	}

}

void DrawBox(double x,double y,double lx,double ly)
{
	MovePen(x,y);
	DrawLine(lx,0);
	DrawLine(0,ly);
	DrawLine(-lx,0);
	DrawLine(0,-ly);
}
void DrawUI()
{
	SetPenColor("Black");
	MovePen(UI_X-0.7,UI_Y);
	DrawTextString("宽");
	MovePen(UI_X-0.5,UI_Y);
	int ratio=(int)((Xratio*1000+5)/10);//近似到个位 
	char number[3];
	DrawTextString(itoa(ratio,number,10));
	DrawTextString("%");
	MovePen(UI_X,UI_Y);
	DrawLine(UILenth,0);
	DrawBox(UI_X+UILenth/2-UI_Button_X/2+(Xratio-1),UI_Y-UI_Button_Y/2,UI_Button_X,UI_Button_Y);
	
	ratio=(int)((Yratio*1000+5)/10);
	MovePen(UI_X-0.7,UI_Y-UIInterval);
	DrawTextString("高");
	MovePen(UI_X-0.5,UI_Y-UIInterval);
	DrawTextString(itoa(ratio,number,10));
	DrawTextString("%");
	MovePen(UI_X,UI_Y-UIInterval);
	DrawLine(UILenth,0);
	DrawBox(UI_X+UILenth/2-UI_Button_X/2+(Yratio-1),UI_Y-UIInterval-UI_Button_Y/2,UI_Button_X,UI_Button_Y);
	
	if(IS_LOCK)//画锁 
	{
	DrawBox(UI_X-0.42,UI_Y-UIInterval/2-0.08,0.2,0.16);
	MovePen(UI_X-0.24,UI_Y-UIInterval/2-0.08+0.16);
	DrawArc(0.08,0,180);
	}
}

void DrawCutUI(int dx1,int dx2,int dy1,int dy2)
{
	MovePen(InchesX(top->InitX+dx1),ScreenY-InchesY(top->InitY));
	DrawLine(0,InchesY(top->info.biHeight)+0.1);
	DrawBox(InchesX(top->InitX+dx1)-UI_Button_X/2,
	        ScreenY-InchesY(top->InitY)+InchesY(top->info.biHeight)+0.1,
	        UI_Button_X,UI_Button_Y);//左 
	MovePen(InchesX(top->InitX-dx2)+InchesX(top->info.biWidth),ScreenY-InchesY(top->InitY));
	DrawLine(0,InchesY(top->info.biHeight)+0.1);
	DrawBox(InchesX(top->InitX-dx2)-UI_Button_X/2+InchesX(top->info.biWidth),
	        ScreenY-InchesY(top->InitY)+InchesY(top->info.biHeight)+0.1,
			UI_Button_X,UI_Button_Y);//右 
	MovePen(InchesX(top->InitX),ScreenY-InchesY(top->InitY-dy1));
	DrawLine(InchesX(top->info.biWidth)+0.1,0);
	DrawBox(InchesX(top->InitX)+InchesX(top->info.biWidth)+0.1,
	        ScreenY-InchesY(top->InitY-dy1)-UI_Button_X/2,
			UI_Button_Y,UI_Button_X);//下 
	MovePen(InchesX(top->InitX),ScreenY-InchesY(top->InitY+dy2)+InchesX(top->info.biHeight));
	DrawLine(InchesX(top->info.biWidth)+0.1,0);
	DrawBox(InchesX(top->InitX)+InchesX(top->info.biWidth)+0.1,
	        ScreenY-InchesY(top->InitY+dy2)-UI_Button_X/2+InchesY(top->info.biHeight),
			UI_Button_Y,UI_Button_X);//上 
}

void ClearSpace(double x,double y,double width,double height)
{
	SetPenColor("White");
	MovePen(x-0.08,y-0.08);
	StartFilledRegion(0);
	DrawLine(width+0.16,0);
	DrawLine(0,height+0.16);
	DrawLine(-width-0.16,0);
	DrawLine(0,-height-0.16);
	EndFilledRegion();//将指定区域清空 
	SetPenColor("Black");
} 
void Display()//画面更新函数 
{
	SetPenColor("Light Gray");	
    MovePen(5,0);
    SetPenSize(5);
	DrawLine(0,10); 
	SetPenColor("Black");
	SetPenSize(2);	
	DrawUI();
	if(IS_TAILOR)DrawCutUI(dx1,dx2,dy1,dy2);
	DrawButton();    //图标工具栏 
	DrawMenu();       //菜单 
	if(OPEN)
	DrawInformationBar(InchesX(top->InitX)-5.105,ScreenY-InchesY(top->InitY)-0.355,top->info.biWidth,top->info.biHeight,Xratio,Yratio);  //状态信息栏 
}

void UpdateLocation(int X,int Y)
{
	ClearSpace(0,0,2,GetFontHeight());
	char location[20];
	sprintf(location,"位置：(%.2lf,%.2lf)",InchesX(X)-5.105,ScreenY-InchesY(Y)-0.355);
	double y=0.25*GetFontHeight();
	SetPenColor("Light Gray");	
	drawMenuBar(0,0,2.3,1.5*GetFontHeight());
	MovePen(0.3,y);
	SetPenColor("Black");
	DrawTextString(location);
} 

void UpdateSize(double width,double height)
{
	ClearSpace(3,0,5,GetFontHeight());
	char size[25];
	sprintf(size,"宽：%.lf    高：%.lf",width,height); 
	char hw_rate[30];
	sprintf(hw_rate,"缩放率：(%3d%%,%3d%%)",(int)((Xratio*1000+5)/10),(int)((Yratio*1000+5)/10));
	double y=0.25*GetFontHeight();
	SetPenColor("Light Gray");	
	drawMenuBar(2.5,0,5.7,1.5*GetFontHeight());
	SetPenColor("Black");
	MovePen(3,y);
	DrawTextString(size);
	MovePen(6,y);
	DrawTextString(hw_rate);
} 

