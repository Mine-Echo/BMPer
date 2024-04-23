#include "callback.h"

int dx1=0,dx2=0,dy1=0,dy2=0;
bool IS_LOCK=FALSE;

void KeyboardEventProcess(int key,int event)
{
	 int width=0;
	 int height=0;
	 
	 uiGetKeyboard(key,event);
	
	 Display();
	if(OPEN)
	switch(event)
	{
	 case KEY_DOWN:
	 	{
	 		if(key==38)//�Ŵ�10% 
	 		{   	 			
	 		    SAVE=FALSE; 
			    IS_TAILOR=FALSE; 
	 		    if(Xratio*1.1<=2&&Yratio*1.1<=2)
				{
	 		    Xratio*=1.1;
				Yratio*=1.1;
	 			width=(int)(base->info.biWidth*Xratio)/4*4;
	 			height=(int)(base->info.biHeight*Yratio)/4*4;
	 			Reshape(width,height);
	 			DisplayClear(); 
	 			Display();
	 			ShowImage();
				}
	 		}
	 		else if(key==39||key==37)//��ת 
	 		{
	 			SAVE=FALSE; 
	 			IS_TAILOR=FALSE; 
	 			if(key==39)
	 			Rotate(1);
	 			else
	 			Rotate(2);
	 			double temp=Xratio;
	 			Xratio=Yratio;
	 			Yratio=temp;
	 			width=(int)(base->info.biWidth*Xratio)/4*4;
	 			height=(int)(base->info.biHeight*Yratio)/4*4;
	 			Reshape(width,height);
	 			top->changebase=TRUE;
	 			DisplayClear(); 
	 			Display();
	 			ShowImage();
	 		}
	 		else if(key==40)//��С10% 
	 		{
	 			SAVE=FALSE; 
	 			if(Xratio/1.1>=0.01&&Yratio/1.1>=0.01)
				{
				IS_TAILOR=FALSE; 
				Xratio/=1.1;
				Yratio/=1.1;
	 			width=(int)(base->info.biWidth*Xratio)/4*4;
	 			height=(int)(base->info.biHeight*Yratio)/4*4;
	 			Reshape(width,height);
	 			DisplayClear(); 
	 			Display();
	 			ShowImage();
	 		    }
	 		}
	 		else if(key==32)//�������� 
	 		{
	 			SAVE=FALSE; 
	 			IS_TAILOR=FALSE;
	 			if(top->changebase==TRUE)
	 			{
	 				base=(BMP_node *)PopStack(base);
	 			}
				top=(BMP_node*)PopStack(top);//����ջ���ڵ� 
				double n=(double)(top->info.biWidth)/(double)(base->info.biWidth);
				Xratio=n;
				double m=(double)(top->info.biHeight)/(double)(base->info.biHeight);
	 			Yratio=m;//���¼����ȡ������� 
	 			DisplayClear(); 
				Display();
				ShowImage();
	 		}
			else if(key==112)//��˹ģ�� F1
	 		{
	 		SAVE=FALSE; 
	 		double core[3][3]={0.0625,0.125,0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625};
	 		convolution(core);
	        DisplayClear();
	        Display();
	        ShowImage();
			}
			else if(key==113)//�Ҷ�ͼ F2
	 		{
	 		SAVE=FALSE; 
	 		Gray();
	        DisplayClear();
	        Display();
	        ShowImage();
			}	
			else if(key==114)//��ֵ�� F3
	 		{
	 		SAVE=FALSE; 
	 		Binarization(128);//��ֵ����ֵ 
	        DisplayClear();
	        Display();
	        ShowImage();
			}
			else if(key==115)//������˹���� F4 
	 		{
	 		SAVE=FALSE; 
	 	    Binarization(128); 
	 		double core[3][3]={0,-1,0,-1,4,-1,0,-1,0};
	 		convolution(core);
	        DisplayClear();
	        Display();
	        ShowImage();
			}
			else if(key==116)//F5
			{
			SAVE=FALSE; 
	 		double core[3][3]={0,0,0,0,0,0,0,0,0};
	 		int i,j;
	 		InitConsole();
	 		printf("������������(3*3)��С�ľ���ˣ�������;�رմ��ڣ����򽫵��³��������\n����0.11 0.11 0.11\n    0.11 0.11 0.11\n    0.11 0.11 0.11\n(ģ�������)\n");
			for(i=0;i<3;i++)
			   {
			   	for(j=0;j<3;j++)
			   	 {
			   	 	scanf("%lf",&core[i][j]);
			   	 }
			   } 
			printf("��رմ���\n");
			FreeConsole();
	 		convolution(core);
	        DisplayClear();
	        Display();
	        ShowImage();
			} 
		 }
	 break; 
	 case KEY_UP:break;
	}
}

void MouseEventProcess(int x, int y, int button, int event)
{
	static int originX=-1,originY=-1;//����������һ״̬������λ�� 
	static int InitX,InitY;//������¼��ʼ����ƶ� 
	static bool IsMove=FALSE; //�ж��Ƿ����϶� 
	static bool XIsZoom=FALSE; //�Ƿ������ſ�� 
	static bool YIsZoom=FALSE; //�Ƿ������Ÿ߶� 
	static bool x1move=FALSE,x2move=FALSE,y1move=FALSE,y2move=FALSE;//�Ƿ����϶��ü���ť 
	static double Init_Xratio,Init_Yratio;//��¼��ʼ����ʱ�ĳ������ 
	
	uiGetMouse(x,y,button,event);

	if((IsMove|XIsZoom|YIsZoom|x1move|x2move|y1move|y2move)==FALSE)
	{
	ClearSpace(0,0,5,10);
	Display();
    }
	
	if(OPEN)
	switch(event)
	{
	case BUTTON_DOWN:
		{
 			if(button==LEFT_BUTTON&&x>=top->InitX&&x<=top->InitX+(int)(top->info.biWidth)
			                      &&y<=top->InitY&&y>=top->InitY-(int)(top->info.biHeight))
			{
				if(IS_TAILOR==TRUE)
				{
			    ClearSpace(InchesX(top->InitX)-UI_Button_X/2,ScreenY-InchesX(top->InitY)-UI_Button_X/2,
				           InchesX(top->info.biWidth)+0.1+UI_Button_Y,InchesX(top->info.biHeight)+0.1+UI_Button_Y);
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),InchesX(top->info.biWidth),InchesY(top->info.biHeight));

				}//��ͼƬ���ü�UIͿ�� 
				IsMove=TRUE;
				originX=x;
				originY=y;
				InitX=top->InitX;
				InitY=top->InitY;//��ʼ���϶�λ�� 
			}                   
			else if(button==LEFT_BUTTON&&x>=ScaleX(UI_X+UILenth/2-UI_Button_X/2+(Xratio-1))
			                           &&y<=ScaleY(UI_Y-UI_Button_Y/2)
									   &&x<=ScaleX(UI_X+UILenth/2+UI_Button_X/2+(Xratio-1))
									   &&y>=ScaleY(UI_Y+UI_Button_Y/2)
									   )
			{
				SAVE=FALSE; 
				if(IS_TAILOR==TRUE)
				{IS_TAILOR=FALSE;
			    ClearSpace(InchesX(top->InitX)-UI_Button_X/2,ScreenY-InchesX(top->InitY)-UI_Button_X/2,
				           InchesX(top->info.biWidth)+0.1+UI_Button_Y,InchesX(top->info.biHeight)+0.1+UI_Button_Y);
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
				        InchesX(top->info.biWidth*Xratio),InchesY(top->info.biHeight));//��ղü�UI 
				}
                XIsZoom=TRUE;
				originX=x;
				Init_Xratio=Xratio;
				Init_Yratio=Yratio;				
			}
			else if(button==LEFT_BUTTON&&x>=ScaleX(UI_X+UILenth/2-UI_Button_X/2+(Yratio-1))
			                           &&y<=ScaleY(UI_Y-UI_Button_Y/2-UIInterval)
									   &&x<=ScaleX(UI_X+UILenth/2+UI_Button_X/2+(Yratio-1))
									   &&y>=ScaleY(UI_Y+UI_Button_Y/2-UIInterval)
									   )
			{
				SAVE=FALSE; 
				if(IS_TAILOR==TRUE)
				{IS_TAILOR=FALSE;
			    ClearSpace(InchesX(top->InitX)-UI_Button_X/2,ScreenY-InchesX(top->InitY)-UI_Button_X/2,
				           InchesX(top->info.biWidth)+0.1+UI_Button_Y,InchesX(top->info.biHeight)+0.1+UI_Button_Y);
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
				        InchesX(top->info.biWidth),InchesY(top->info.biHeight));//��ղü�UI 
				} 
                YIsZoom=TRUE;
				originX=x;
				Init_Xratio=Xratio;
				Init_Yratio=Yratio;					
			}   
			else if(button==LEFT_BUTTON&&IS_TAILOR==TRUE)//�ü���ť�ж���Χ 
			{                           
				      if( x>=top->InitX+dx1-ScaleX(UI_Button_X/2)
		                &&y<=top->InitY-top->info.biHeight-ScaleX(0.1)
					    &&x<=top->InitX+dx1+ScaleX(UI_Button_X/2)
						&&y>=top->InitY-top->info.biHeight-ScaleX(0.1+UI_Button_Y))						   
						{
							x1move=TRUE;
							originX=x;
						}
				 else if( x>=top->InitX+top->info.biWidth-dx2-ScaleX(UI_Button_X/2)
		                &&y<=top->InitY-top->info.biHeight-ScaleX(0.1)
					    &&x<=top->InitX+top->info.biWidth-dx2+ScaleX(UI_Button_X/2)
						&&y>=top->InitY-top->info.biHeight-ScaleX(0.1+UI_Button_Y))						   
						{
							x2move=TRUE;
							originX=x;
						}
				 else if( x>=top->InitX+top->info.biWidth+ScaleX(0.1)
		                &&y<=top->InitY-dy1+ScaleX(UI_Button_X/2)
					    &&x<=top->InitX+top->info.biWidth+ScaleX(0.1+UI_Button_Y)
						&&y>=top->InitY-dy1-ScaleX(UI_Button_X/2))						   
						{
							y1move=TRUE;
							originY=y;
						}
			   	 else if( x>=top->InitX+top->info.biWidth+ScaleX(0.1)
		                &&y<=top->InitY-top->info.biHeight+dy2+ScaleX(UI_Button_X/2)
					    &&x<=top->InitX+top->info.biWidth+ScaleX(0.1+UI_Button_Y)
						&&y>=top->InitY-top->info.biHeight+dy2-ScaleX(UI_Button_X/2))						   
						{
							y2move=TRUE;
							originY=y;
						}
		    }
			break;                                 
		}
	case MOUSEMOVE:
		{
			if(IsMove==TRUE)
			{
			    ClearSpace(InchesX(InitX),ScreenY-InchesX(InitY),InchesX(top->info.biWidth),InchesX(top->info.biHeight));	    
				if(InchesX(InitX+x-originX)>5.1&&InchesX(InitX+x-originX+top->info.biWidth)<15.9)//�����϶���Χ 
				{
				InitX=InitX+x-originX;
				originX=x;
	            }
	            if(ScreenY-InchesX(InitY+y-originY)>0.35&&ScreenY-InchesX(InitY+y-originY-top->info.biHeight)<9.65)
				{
				InitY=InitY+y-originY;//���������ƶ���ͬ���ƶ���ʼ���λ�� 
				originY=y;	
	            }
	            UpdateLocation(InitX,InitY);
				DrawBox(InchesX(InitX),ScreenY-InchesY(InitY),InchesX(top->info.biWidth),InchesY(top->info.biHeight));
			}
			else if(XIsZoom==TRUE)
			{
				ClearSpace(InchesX(top->InitX),ScreenY-InchesX(top->InitY),
				InchesX((int)(base->info.biWidth*Xratio)/4*4),InchesY((int)(base->info.biHeight*Yratio)/4*4));
	     		ClearSpace(UI_X-0.5,UI_Y-UI_Button_Y/2-UIInterval,UILenth+0.5,UI_Button_Y+UIInterval);
				if(Xratio+InchesX(x-originX)>=0&&Xratio+InchesX(x-originX)<=2)
				{
					if(IS_LOCK==FALSE)
				      Xratio=Xratio+InchesX(x-originX);
			        else
			        {
			        	double temp=Init_Yratio/Init_Xratio*(Xratio+InchesX(x-originX));//��������������ݱ����ȱȼ��㳤�� 
			        	if(temp>=0&&temp<=2)
			        	{
			        		Xratio=Xratio+InchesX(x-originX);
			        		Yratio=temp;
			        	}
			        }
				}
				originX=x;
				DrawUI();
				UpdateSize((int)(base->info.biWidth*Xratio)/4*4,(int)(base->info.biHeight*Yratio)/4*4);
			  DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
			          InchesX((int)(base->info.biWidth*Xratio)/4*4),InchesY((int)(base->info.biHeight*Yratio)/4*4));
			}
			else if(YIsZoom==TRUE)
			{
				ClearSpace(InchesX(top->InitX),ScreenY-InchesX(top->InitY),
				InchesX((int)(base->info.biWidth*Xratio)/4*4),InchesY((int)(base->info.biHeight*Yratio)/4*4));
	     		ClearSpace(UI_X-0.5,UI_Y-UI_Button_Y/2-UIInterval,UILenth+0.5,UI_Button_Y+UIInterval);
				if(Yratio+InchesX(x-originX)>=0&&Yratio+InchesX(x-originX)<=2)
				{
					if(IS_LOCK==FALSE)
				      Yratio=Yratio+InchesX(x-originX);
     		        else
			        {
			        	double temp=Init_Xratio/Init_Yratio*(Yratio+InchesX(x-originX));//��������������ݱ����ȱȼ��㳤�� 
			        	if(temp>=0&&temp<=2)
			        	{
			        		Yratio=Yratio+InchesX(x-originX);
			        		Xratio=temp;
			        	}
			        }
				}
				originX=x;
				DrawUI();
				UpdateSize((int)(base->info.biWidth*Xratio)/4*4,(int)(base->info.biHeight*Yratio)/4*4);
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
				        InchesX((int)(base->info.biWidth*Xratio)/4*4),InchesY((int)(base->info.biHeight*Yratio)/4*4));
			}
			else if(x1move==TRUE)//�Բü���ť���϶� 
			{
				ClearSpace(InchesX(top->InitX)-UI_Button_X/2,ScreenY-InchesX(top->InitY)-UI_Button_X/2,
				           InchesX(top->info.biWidth)+0.1+UI_Button_Y,InchesX(top->info.biHeight)+0.1+UI_Button_Y);
				if(dx1+x-originX>=0&&dx1+x-originX<top->info.biWidth-dx2-ScaleX(UI_Button_X))
				dx1=dx1+x-originX;
				originX=x;
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
				        InchesX(top->info.biWidth),InchesY(top->info.biHeight));
				DrawCutUI(dx1,dx2,dy1,dy2);
			}
			else if(x2move==TRUE)
			{
				ClearSpace(InchesX(top->InitX)-UI_Button_X/2,ScreenY-InchesX(top->InitY)-UI_Button_X/2,
				           InchesX(top->info.biWidth)+0.1+UI_Button_Y,InchesX(top->info.biHeight)+0.1+UI_Button_Y);
				if(dx2-x+originX>=0&&dx2-x+originX<top->info.biWidth-dx1-ScaleX(UI_Button_X))
				dx2=dx2-x+originX;
				originX=x;
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
				        InchesX(top->info.biWidth),InchesY(top->info.biHeight));
				DrawCutUI(dx1,dx2,dy1,dy2);
			}
			else if(y1move==TRUE)
			{
				ClearSpace(InchesX(top->InitX)-UI_Button_X/2,ScreenY-InchesX(top->InitY)-UI_Button_X/2,
				           InchesX(top->info.biWidth)+0.1+UI_Button_Y,InchesX(top->info.biHeight)+0.1+UI_Button_Y);
				if(dy1-y+originY>=0&&dy1-y+originY<top->info.biHeight-dy2-ScaleX(UI_Button_X))
				dy1=dy1-y+originY;
				originY=y;
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
				        InchesX(top->info.biWidth),InchesY(top->info.biHeight));
				DrawCutUI(dx1,dx2,dy1,dy2);
			}
			else if(y2move==TRUE)
			{
				ClearSpace(InchesX(top->InitX)-UI_Button_X/2,ScreenY-InchesX(top->InitY)-UI_Button_X/2,
				           InchesX(top->info.biWidth)+0.1+UI_Button_Y,InchesX(top->info.biHeight)+0.1+UI_Button_Y);
				if(dy2+y-originY>=0&&dy2+y-originY<top->info.biHeight-dy1-ScaleX(UI_Button_X))
				dy2=dy2+y-originY;
				originY=y;
				DrawBox(InchesX(top->InitX),ScreenY-InchesY(top->InitY),
				        InchesX(top->info.biWidth),InchesY(top->info.biHeight));
				DrawCutUI(dx1,dx2,dy1,dy2);
			}
			break;
		}
	case BUTTON_UP:
		{		
		    if(IsMove==TRUE)
		    {
			BMP_node *new_node=(BMP_node*)CopyNode(top);
			new_node->InitX=InitX;
			new_node->InitY=InitY;
			top=(BMP_node*)PushStack(top,new_node);
			DisplayClear(); 
			ShowImage();
			Display();
			IsMove=FALSE;
		    }
		    else if((YIsZoom|XIsZoom)==TRUE)
		    {
		    int	width=(int)(base->info.biWidth*Xratio)/4*4;
	 		int	height=(int)(base->info.biHeight*Yratio)/4*4;
	 		Reshape(width,height);
	 		DisplayClear(); 
	 		Display();
	 		ShowImage();
	 		XIsZoom=FALSE;
	 		YIsZoom=FALSE;//���ò������� 
		    }
		    else if((x1move|x2move|y1move|y2move)==TRUE)
		    {
		    DisplayClear(); 
			ShowImage();
		    Display();
			x1move=FALSE;
			x2move=FALSE;
			y1move=FALSE;
			y2move=FALSE;//��ʼ���������� 
		    }
		    
		}
			break;
	 
	}
}

