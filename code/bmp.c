#include"bmp.h"

double Xratio = 1.0;//ͼƬ�����ű���
double Yratio = 1.0;//ͼƬ�����ű��� 

void Reshape(int new_width,int new_height)
{
 int i=0,j=0;  //ѭ������ 
 int srcX,srcY;//���ź�ͼƬ��������������Ӧ��ԭͼ�������� 
 char *new_file;//ָ����ͼƬ���ݵ�ָ�� 
 char *old_file;//ָ���ͼƬ���ݵ�ָ�� 
  
 char *old_data=base->bmp_data;
 int old_width=base->info.biWidth;
 int old_height=base->info.biHeight;//��ȡbase�ڵ����� 
 
 BMP_node *new_node=(BMP_node*)CopyNode(base);//����base�ڵ������
 if(top!=NULL)
 {
 new_node->InitX=top->InitX;
 new_node->InitY=top->InitY;
 }//���Ѵ�ͼƬ������ͼƬ����ʼλ�㣬��Ϊ���Ų��ı�ͼƬλ�� 
 free(new_node->bmp_data);
 new_node->bmp_data=(char*)malloc(new_width*new_height*3);//�ͷŲ��ط����ڴ� 
 
 new_node->head.bfSize=new_width*new_height*3+54;
 new_node->info.biWidth=new_width;
 new_node->info.biHeight=new_height;//�����½ڵ��ļ�ͷ����Ϣͷ 
 
 top=(BMP_node*)PushStack(top,new_node);//ѹջ 
 
 for(i=0;i<new_height;i++)
 {
  srcY=i*old_height/new_height;
  new_file=new_node->bmp_data+i*new_width*3;
  old_file=old_data+srcY*old_width*3;
  for(j=0;j<new_width;j++)
  {
   srcX=j*old_width/new_width;//���ݳ������������һ�����ź�ͼƬ��ԭͼƬ֮���ӳ�䣬һһ��ȡ��ͼƬ���������� 
   memcpy(new_file+j*3,old_file+srcX*3,3);//���ݿ���
  }
 }
} 

void Rotate(int mode)
{
 BMP_node* new_base=(BMP_node*)CopyNode(base);//�½���ת��Ļ�׼���� 
 int height=base->info.biHeight;
 int width=base->info.biWidth;//��ȡͼƬ���� 
 int i,j;
 if(mode==1||mode==2)//˳ʱ�롢��ʱ����ת���� 
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
	 new_base->info.biWidth=base->info.biHeight;//������ת��ͼƬ�ĳ���ֵ 
}
else if(mode==3)//���ҷ�ת 
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
else if(mode==4)//���·�ת 
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
 base=(BMP_node *)PushStack(base,new_base);//ѹջ 
}

void CutImage(int InitX,int InitY,int width,int height)
{
 int baseX=InitX/Xratio;
 int baseY=InitY/Yratio;//��׼��ʼ�ü�λ�� 
 int base_width=width/Xratio; 
 int base_height=height/Yratio;//���ݵ�ǰͼƬ����ڻ�׼�ı��������������ڻ�׼����Ҫ�ü��ĳ��� 
 
 if(baseX+base_width>base->info.biWidth)base_width=base->info.biWidth-baseX;
 if(baseY+base_height>base->info.biHeight)base_height=base->info.biWidth-baseY;//��ֹ��ȡ��׼��������ʱԽ�� 
 
 BMP_node *new_base=(BMP_node*)CopyNode(base);//���ƻ�׼�ڵ���Ϣ 
 free(new_base->bmp_data);
 new_base->bmp_data=(char*)malloc(base_width*base_height*3);//�ͷŲ��ط����ڴ� 
 char *new_file=new_base->bmp_data;//ָ����ͼƬ���ݵ�ָ�� 
 char *old_file=base->bmp_data;//ָ���ͼƬ���ݵ�ָ�� 
 
 int i;//ѭ������ 
 old_file+=3*(baseY*base->info.biWidth+baseX);//�Ƚ�ָ���ƶ�����ʼλ���λ�� 
 for(i=0;i<base_height;i++)
 {
 	memcpy(new_file,old_file,base_width*3);
 	old_file+=3*base->info.biWidth;
 	new_file+=3*base_width;//���ݿ���ʵ�ֲü� 
 }
 
 new_base->info.biHeight=base_height;
 new_base->info.biWidth=base_width;//�����»�׼�ĳ�������(���蹹��biSize���ݣ���Ϊ�ں�����Reshape�����л���ָ���ǰͼƬ�����ű����������ļ���С) 
 
 base=(BMP_node *)PushStack(base,new_base);//ѹջ 
 Reshape(width,height);//�ָ�������� 
 top->changebase=TRUE;//��ǻ�׼�����ı� 
}

int ReadImage(const char* old_bmp_path)
{  
 FILE *fpr=fopen(old_bmp_path,"rb");

 base=(BMP_node *)InitList();//��ʼ��ջ 
 //��ȡԭ��Ƭ��ͷ��Ϣ
 fread(&base->head,sizeof(BITMAPFILEHEADER),1,fpr);
 fread(&base->info,sizeof(BITMAPINFOHEADER),1,fpr);

 int old_width=base->info.biWidth;//��ȡԭͼƬ�Ŀ�
 int old_height=base->info.biHeight;//��ȡԭͼƬ�ĸ�
 
 int i;
 int bias=old_width%4; //������������ֽڵ�ƫ��ֵ 
 base->bmp_data=(char*)malloc(old_width*old_height*3);
 char *data=(char*)malloc(old_width*old_height*3+old_height*bias);
 fseek(fpr,54,SEEK_SET);
  //��ȡԭͼƬ��λͼ����
 fread(data,old_width*old_height*3+old_height*bias,1,fpr);
 for(i=0;i<old_height;i++)
 {
 	memcpy(base->bmp_data+i*old_width*3,data+i*(old_width*3+bias),old_width*3);//�������ı������ͼƬ������ַ� 
 }
 free(data);
 int width=(int)(old_width)/4*4;
 int height=(int)(old_height)/4*4;
 Reshape(width,height);//��ʼ��topջ 

 Display();
 ShowImage();
 //�ر��ļ�
 fclose(fpr);
 return 0;
}

int PutImage(const char *new_bmp_path)
{
 FILE *fpw=fopen(new_bmp_path,"wb+");
 
 //���޸Ĺ���ͷ��Ϣд������Ƭ
 fwrite(&top->head,sizeof(BITMAPFILEHEADER),1,fpw);
 fwrite(&top->info,sizeof(BITMAPINFOHEADER),1,fpw);
 fseek(fpw,54,SEEK_SET);
 fwrite(top->bmp_data,top->info.biWidth*top->info.biHeight*3,1,fpw);
 //�ر��ļ� 
 fclose(fpw);
}

int ShowImage()//��ʾtop��ͼ������ 
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
 		int red = (int)*(data+2);//��ȡ��ɫ���� 
 		DrawPixel(X+xmove,Y-ymove,red,green,blue);//��� 
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
	DrawTextString("��");
	MovePen(UI_X-0.5,UI_Y);
	int ratio=(int)((Xratio*1000+5)/10);//���Ƶ���λ 
	char number[3];
	DrawTextString(itoa(ratio,number,10));
	DrawTextString("%");
	MovePen(UI_X,UI_Y);
	DrawLine(UILenth,0);
	DrawBox(UI_X+UILenth/2-UI_Button_X/2+(Xratio-1),UI_Y-UI_Button_Y/2,UI_Button_X,UI_Button_Y);
	
	ratio=(int)((Yratio*1000+5)/10);
	MovePen(UI_X-0.7,UI_Y-UIInterval);
	DrawTextString("��");
	MovePen(UI_X-0.5,UI_Y-UIInterval);
	DrawTextString(itoa(ratio,number,10));
	DrawTextString("%");
	MovePen(UI_X,UI_Y-UIInterval);
	DrawLine(UILenth,0);
	DrawBox(UI_X+UILenth/2-UI_Button_X/2+(Yratio-1),UI_Y-UIInterval-UI_Button_Y/2,UI_Button_X,UI_Button_Y);
	
	if(IS_LOCK)//���� 
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
	        UI_Button_X,UI_Button_Y);//�� 
	MovePen(InchesX(top->InitX-dx2)+InchesX(top->info.biWidth),ScreenY-InchesY(top->InitY));
	DrawLine(0,InchesY(top->info.biHeight)+0.1);
	DrawBox(InchesX(top->InitX-dx2)-UI_Button_X/2+InchesX(top->info.biWidth),
	        ScreenY-InchesY(top->InitY)+InchesY(top->info.biHeight)+0.1,
			UI_Button_X,UI_Button_Y);//�� 
	MovePen(InchesX(top->InitX),ScreenY-InchesY(top->InitY-dy1));
	DrawLine(InchesX(top->info.biWidth)+0.1,0);
	DrawBox(InchesX(top->InitX)+InchesX(top->info.biWidth)+0.1,
	        ScreenY-InchesY(top->InitY-dy1)-UI_Button_X/2,
			UI_Button_Y,UI_Button_X);//�� 
	MovePen(InchesX(top->InitX),ScreenY-InchesY(top->InitY+dy2)+InchesX(top->info.biHeight));
	DrawLine(InchesX(top->info.biWidth)+0.1,0);
	DrawBox(InchesX(top->InitX)+InchesX(top->info.biWidth)+0.1,
	        ScreenY-InchesY(top->InitY+dy2)-UI_Button_X/2+InchesY(top->info.biHeight),
			UI_Button_Y,UI_Button_X);//�� 
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
	EndFilledRegion();//��ָ��������� 
	SetPenColor("Black");
} 
void Display()//������º��� 
{
	SetPenColor("Light Gray");	
    MovePen(5,0);
    SetPenSize(5);
	DrawLine(0,10); 
	SetPenColor("Black");
	SetPenSize(2);	
	DrawUI();
	if(IS_TAILOR)DrawCutUI(dx1,dx2,dy1,dy2);
	DrawButton();    //ͼ�깤���� 
	DrawMenu();       //�˵� 
	if(OPEN)
	DrawInformationBar(InchesX(top->InitX)-5.105,ScreenY-InchesY(top->InitY)-0.355,top->info.biWidth,top->info.biHeight,Xratio,Yratio);  //״̬��Ϣ�� 
}

void UpdateLocation(int X,int Y)
{
	ClearSpace(0,0,2,GetFontHeight());
	char location[20];
	sprintf(location,"λ�ã�(%.2lf,%.2lf)",InchesX(X)-5.105,ScreenY-InchesY(Y)-0.355);
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
	sprintf(size,"��%.lf    �ߣ�%.lf",width,height); 
	char hw_rate[30];
	sprintf(hw_rate,"�����ʣ�(%3d%%,%3d%%)",(int)((Xratio*1000+5)/10),(int)((Yratio*1000+5)/10));
	double y=0.25*GetFontHeight();
	SetPenColor("Light Gray");	
	drawMenuBar(2.5,0,5.7,1.5*GetFontHeight());
	SetPenColor("Black");
	MovePen(3,y);
	DrawTextString(size);
	MovePen(6,y);
	DrawTextString(hw_rate);
} 

