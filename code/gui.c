#include"gui.h"

void DrawMenu() //���˵��� 
{
	
	SetPenSize(2);
	//�˵����Ƽ������� 
	char *menuListFile[]=
	{
		"�ļ�",
		"��    Ctrl-O",
		"�ر�          ",
		"����    Ctrl-S",
		"�˳�    Ctrl-E" 
	 };
	 
	 char *menuListFunction2[]=
	{
		"��������",
		"���ҷ�ת Ctrl-A",
		"���·�ת Ctrl-D", 
		"ģ��           F1",
		"�Ҷ�ͼ       F2",
		"��ֵ��       F3",
		"������˹���� F4",
		"�Զ������� F5"
		
	 };
	 
	char *menuListFunction[]=
	{
		"��������",
		"�Ŵ�    Ctrl-L",
		"��С    Ctrl-R",
		"��ת(��)    <-",
		"��ת(˳)    ->",
		"�ü�    Ctrl-T",
		"ѹ��    Ctrl-P",
		"����    Ctrl-Z" 
	};
	
	char *menuListAbout[]=
	{
		"����",
		"���ڱ����",
		"ʹ�÷���" ,
		"��������" 
	};
	//��ͬ״̬���ֲ�ͬ�˵� 
	menuListFunction[5]= (IS_TAILOR ? "ȷ��  Ctrl-T" : "�ü�    Ctrl-T"); 
	menuListAbout[3]=(IS_PLAY? "�رձ�������":"�򿪱�������"); 
	//�趨�˵�λ�ü����С 
	double x=0; 
	double h=1.5*GetFontHeight(); 
	double y=WindowH-h;
	double w=1.0;
	double wlist=1.8;
	
	int selectionFile=menuList(GenUIID(0), x, y, w, wlist, h, menuListFile,sizeof(menuListFile)/sizeof(menuListFile[0]));
		  
	if(selectionFile>0){
		SelectFile(selectionFile);
	}
	
	
	int selectionFunction=menuList(GenUIID(0),x+w,y,w,wlist,h,menuListFunction,sizeof(menuListFunction)/sizeof(menuListFunction[0]));
	
	if(selectionFunction>0)
		SelectFunction(selectionFunction);
		
	int selectionFunction2=menuList(GenUIID(0),x+2*w,y,w,wlist,h,menuListFunction2,sizeof(menuListFunction2)/sizeof(menuListFunction2[0]));
	
	if(selectionFunction2>0)
		SelectFunction2(selectionFunction2);
		
	int selectionAbout=menuList(GenUIID(0),x+3*w,y,w,wlist,h,menuListAbout,sizeof(menuListAbout)/sizeof(menuListAbout[0]));
	
	if(selectionAbout>0)
		SelectAbout(selectionAbout);
		
	drawMenuBar(4*w,y,WindowW,h); 
}

void SelectFile(int selection)             //�ļ��˵��� 
{
	if(selection==1)//��Ӧ�򿪰��� 
	{
		window=FindWindow(NULL,"BMPͼƬ�༭��");
		if(OPEN==FALSE)
		{
			InitConsole();
			printf("��������Ҫ�򿪵�BMPͼƬ����:\n");
			scanf("%s",FileName);
			printf("��رմ˴���\n"); 
			FreeConsole();     //�رտ���̨ʱ���ر��������� 
			Init();
			//����򿪳ɹ�����ʾͼƬ 
			if(fp=fopen(FileName,"rb"))
			{
				fclose(fp);
				OPEN=TRUE;
				int len=strlen(FileName);
				if(len>=3&&FileName[len-1]=='a'&&FileName[len-2]=='.')
				{ 
				ReadCompressImage(FileName);
				memcpy(name,FileName,len-2);
				name[len-2]='\0';
				MessageBox(
					window,
					TEXT("�ļ���ѹ�ɹ���"),
					TEXT("��ʾ"),
					MB_OK);
			    }
				else if(len>=5&&FileName[len-4]=='.'&&FileName[len-3]=='b'
				              &&FileName[len-2]=='m'&&FileName[len-1]=='p')
				{ 
				ReadImage(FileName);
				memcpy(name,FileName,len-4);
				name[len-4]='\0';
			    }
				else{
				MessageBox(
					window,
					TEXT("�ļ���ʧ��"),
					TEXT("��ʾ"),
					MB_ICONHAND | MB_OK);
			       }
				DisplayClear();
				Display();
				ShowImage();
			}
		    //����ʧ�ܣ���ʾ
			else{
				MessageBox(
					window,
					TEXT("�ļ���ʧ��"),
					TEXT("��ʾ"),
					MB_ICONHAND | MB_OK);
			}
		}
		else
			MessageBox(
					window,
					TEXT("�����ļ�����\n���ȹرյ�ǰ�ļ�\n�ٴ������ļ�"),
					TEXT("��ʾ"),
					MB_ICONHAND | MB_OK);
	}

	else if(selection==2)//�ر� 
	{
		if(OPEN==FALSE);            //����ļ�δ�������κ��� 
		else if(SAVE==TRUE) 
		{
			OPEN=FALSE;
			ClearList();
			DisplayClear();
			IS_TAILOR=FALSE;
			Xratio=1;
		    Yratio=1; 
			Display();
		}
		else
		{
			window=FindWindow(NULL,"BMPͼƬ�༭��");
			int choice=MessageBox(
				window,
				TEXT("�ļ���δ���棡\n�Ƿ񱣴��ļ���"),
				TEXT("��ʾ"),
				MB_ICONWARNING | MB_YESNOCANCEL); 
			ChoiceOfClose(choice); 
		}
	}
	else if(selection==3&&OPEN==TRUE)//���� 
	{
		if(SAVE==FALSE)
		{
			InitConsole();
			//PutImage("output.bmp");
			printf("��������Ҫ����Ϊ��BMP��ʽͼƬ����:\n");
			scanf("%s",FileName);
			printf("��رմ˴���\n"); 
			FreeConsole();
			window=FindWindow(NULL,"BMPͼƬ�༭��");
			PutImage(FileName);
			//�������ɹ�
			if(1)
			{
				MessageBox(
					window,
					TEXT("�ļ�����ɹ�"),
					TEXT("��ʾ"),
					MB_OK);
				SAVE=TRUE;
			}
			//������ʧ�ܣ���ʾ 
			else
			{
				MessageBox(
				window,
				TEXT("�ļ�����ʧ��"),
				TEXT("��ʾ"),
				MB_ICONHAND | MB_OK);
				SAVE=FALSE;
			}
		}
	}
	
	else if(selection==4)//�˳� 
	{
		if(SAVE==TRUE||OPEN==FALSE) 
		{
			exit(0);
		}
		else
		{
			window=FindWindow(NULL,"BMPͼƬ�༭��");
			int choice=MessageBox(
				window,
				TEXT("�ļ���δ���棡\n�Ƿ񱣴��ļ���"),
				TEXT("��ʾ"),
				MB_ICONWARNING | MB_YESNOCANCEL); 
			ChoiceOfExit(choice); 
		}
		
	}
}

void ChoiceOfClose(int choice)//����ر�ʱ����������ѡ�� 
{
	if(choice==IDYES)//ѡ���Ǳ����ļ� ���ڹر��ļ� 
	{
		SelectFile(3);
		OPEN=FALSE;
		ClearList();
		DisplayClear();
		IS_TAILOR=FALSE;
		Xratio=1;
		Yratio=1; 
		Display();
	}
	else if(choice==IDNO)//ѡ���ֱ�ӹر� 
	{
		OPEN=FALSE;
		ClearList();
		DisplayClear();
		IS_TAILOR=FALSE;
		Xratio=1;
		Yratio=1; 
		Display();
	}
}

void ChoiceOfExit(int choice)//����˳�ʱ����������ѡ�� 
{
	if(choice==IDYES)//ѡ���Ǳ����ļ������˳� 
	{
		SelectFile(3);
		exit(0); 
	}
	else if(choice==IDNO)//ѡ���ֱ���˳� 
		exit(0);
	else ;
}

void Init()
{
	SAVE=TRUE;
	OPEN=FALSE;
}

void SelectFunction(selection)           //�������ܲ˵��� 
{
	static int width;
	static int height;

	//����������Ҫ�ļ��򿪲���ʹ�� 
	if(OPEN==TRUE)
	{
		switch(selection)
		{
			case 1 :           // �Ŵ� 
			     {
			     	if(Xratio*1.1<=2&&Yratio*1.1<=2)
						{
						SAVE=FALSE; 
			 		    Xratio*=1.1;
						Yratio*=1.1;
			 			width=(int)(base->info.biWidth*Xratio)/4*4;
			 			height=(int)(base->info.biHeight*Yratio)/4*4;
			 			Reshape(width,height);
			 			DisplayClear(); 
			 			Display();
			 			ShowImage();
						}
						break;
			     }
				
			case 2 :      //��С 
				{
					if(Xratio/1.1>=0.01&&Yratio/1.1>=0.01)
						{
						SAVE=FALSE; 
						Xratio/=1.1;
						Yratio/=1.1;
			 			width=(int)(base->info.biWidth*Xratio)/4*4;
			 			height=(int)(base->info.biHeight*Yratio)/4*4;
			 			Reshape(width,height);
			 			DisplayClear(); 
			 			Display();
			 			ShowImage();
			 		    }
						break;
				}
				
			case 3 :                 // ��ת��ʱ�� 
				{
					SAVE=FALSE; 
					IS_TAILOR=FALSE; 
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
				break;
			    }
			case 4 :            //��ת˳ʱ�� 
				{
					SAVE=FALSE; 
					IS_TAILOR=FALSE; 
		 			Rotate(1);
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
				break;
			    }
			case 5 :           //�ü� 
				{
	                     if(IS_TAILOR==FALSE)
						 {
						 dx1=0,dx2=0,dy1=0,dy2=0;
						 IS_TAILOR=TRUE;
						 }
			 	         else if(IS_TAILOR==TRUE&&dx1+dx2+dy1+dy2==0)
			 			 {
			 			 IS_TAILOR=FALSE;
			 			 }
			 			 else
						 {
						 SAVE=FALSE; 
						 IS_TAILOR=FALSE;
						 width=(int)(top->info.biWidth-dx1-dx2)/4*4;
			 			 height=(int)(top->info.biHeight-dy1-dy2)/4*4;
						 CutImage(dx1,dy1,width,height);
					     }
					    DisplayClear(); 
			 			Display();
			 			ShowImage();
				break;
				}
				
			case 6 :                       // ѹ�� 
				{
				char n[52];
				int len=strlen(name);
				strcpy(n,name);
				n[len]='.';
				n[len+1]='a';
				n[len+2]='\0';
				SaveCompress(top->bmp_data,n);	
				SAVE=TRUE; 
				window=FindWindow(NULL,"BMPͼƬ�༭��");
				MessageBox(
				window,
				TEXT("�ļ���ѹ��Ϊͬ��.a��ʽ�ļ�"),
				TEXT("��ʾ"),
				MB_OK);
				break;
				}
				
			case 7 :               // ���� 
			    {
			    	    if(top==NULL||top->next==NULL);
						else SAVE=FALSE; 
			    	    IS_TAILOR=FALSE;
			 			if(top->changebase==TRUE)
			 			{
			 				base=(BMP_node *)PopStack(base);
			 			}
						top=(BMP_node*)PopStack(top);
						double n=(double)(top->info.biWidth)/(double)(base->info.biWidth);
						Xratio=n;
						double m=(double)(top->info.biHeight)/(double)(base->info.biHeight);
			 			Yratio=m;
			 			DisplayClear(); 
						Display();
						ShowImage();
						break;
	 	    	}
		 }
	}
}

void SelectFunction2(int selection)          //�������ܲ˵��� 
{
	if(OPEN==TRUE)
	switch(selection)
	{
		case 3:         //ģ�� 
			{
			SAVE=FALSE; 
	 		double core[3][3]={0.0625,0.125,0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625};
	 		convolution(core);
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}
			
		case 4:            //�Ҷ�ͼ 
			{
			SAVE=FALSE; 
	 		Gray();
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}
		case 5:              //��ֵ�� 
			{
			SAVE=FALSE; 
	 		Binarization(128);//��ֵ����ֵ 
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}
		case 6:            //������˹���� 
			{
			SAVE=FALSE;
			Binarization(128); 
	 		double core[3][3]={0,-1,0,-1,4,-1,0,-1,0};
	 		convolution(core);
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}
		case 7:               // �Զ������� 
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
				break;
			}	
		case 1:                 // ���ҷ�ת 
			{
			SAVE=FALSE; 
			IS_TAILOR=FALSE; 
	 		Rotate(3);
	 		int width=(int)(base->info.biWidth*Xratio)/4*4;
	 		int height=(int)(base->info.biHeight*Yratio)/4*4;
	 		Reshape(width,height);
	 		top->changebase=TRUE;
	 		DisplayClear(); 
	 		Display();
	 		ShowImage();
			    break;
			}
		case 2:          // ���·�ת 
			{
			SAVE=FALSE; 
			IS_TAILOR=FALSE; 
	 		Rotate(4);
	 		int width=(int)(base->info.biWidth*Xratio)/4*4;
	 		int height=(int)(base->info.biHeight*Yratio)/4*4;
	 		Reshape(width,height);
	 		top->changebase=TRUE;
	 		DisplayClear(); 
	 		Display();
	 		ShowImage();
			    break;
			} 
	}
}

void SelectAbout(int selection)         // ���ڲ˵��� 
{
	window=FindWindow(NULL,"BMPͼƬ�༭��");
	if(selection==1)            //���ڱ���� 
	{	
		MessageBox(
			window,
			TEXT("��ӭʹ��BMPer--BMPͼƬ�༭�������������ɱ�С�������������������ѹ��\\��ѹ��24λBMP���ͼƬ�������Զ�����з�������ת���ü���ģ�����ҶȵȲ�����ͼƬ�༭���ǵý��б���Ŷ��\n\nף��ʹ����죡��\n"),
			TEXT("���ڱ����"),
			MB_OK);
	}
	if(selection==2)        // ʹ�÷��� 
	{
		MessageBox(
			window,
			TEXT("����ʹ�ã�\n���ȵ���򿪰�����������ȷ���ļ������Դ�һ��24λ���BMPͼƬ\n\nȻ������Ե���˵��еĻ������ܣ����еķŴ���С����ת���ü���ѹ���������������Գ��ԣ������Щ���ܻ���������ʹ�ã��������Ե���˵��е��������ܣ���ת��ģ�����Ҷ�ͼ����ֵ����������˹���ӡ��Զ������ˣ���ʵ�ָ����ͼƬ�༭������\n\n���ͼƬ���϶����Ըı�ͼƬ��λ�ã��϶��϶�����������ı�ͼƬ�Ĵ�С�����ͼ�������е������������������\n\nѹ���Ժ���ν�ѹ������򿪰�����ѹ�����ͼƬ�����Զ���ѹ�ˣ��ٵ��������ܽ���ѹ���ͼƬ����Ϊ�ļ���\n\n�����С�Ľ����˴���Ĳ��������õ��ģ��������������ͼƬ��������һ����״̬�����Ծ������ͼƬ�༭�ɣ�����\n\nע�⣺\n����ü������ü�ģʽ����ʱ������ĳЩ������ֱ���˳��ü�ģʽ���ü������ȷ�ϾͿ��Ժ�Ĳü����ͼƬ�ˡ�\n\n���ͼƬ�ı༭��Ҫ�ǵñ��棬���Ǽ�ʹ�����Ǳ���ֱ�ӵ���˹رջ��˳����������Ҳ�ᵯ���������������棬��������ѱ������δ�༭ͼƬ���򲻻ᵯ���������ѡ�\n\n���ڲ˵��п��Դ򿪱������֣�������������\n\n��������������п�ݼ�����Ϥ���ǿ��Դ�󷽱����Ĳ���������"),
			TEXT("ʹ�÷���"),
			MB_OK);
	}
	else if(selection==3)           //�������� 
	{ 
		IS_PLAY = ! IS_PLAY;
		if (IS_PLAY == TRUE)
		{ 
			if(!PlaySound (TEXT("..\\��������.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))
				MessageBox(
					window,
					TEXT("���ֲ���ʧ��"),
					TEXT("��ʾ"),
					MB_ICONHAND | MB_OK);
		}		
		else 
			PlaySound (NULL, NULL, SND_FILENAME | SND_ASYNC);
		 
	} 
}

void DrawInformationBar(double x,double y,double w,double h,double w_rate,double h_rate)       //��״̬��Ϣ������ͼƬʱ�Ż���ʾ�� 
{
	char location[20];
	sprintf(location,"λ�ã�(%.2lf,%.2lf)",x,y);
	char size[25];
	sprintf(size,"��%.lf    �ߣ�%.lf",w,h); 
	char hw_rate[30];
	sprintf(hw_rate,"�����ʣ�(%3d%%,%3d%%)",(int)((w_rate*1000+5)/10),(int)((h_rate*1000+5)/10));
	SetPenColor("Light Gray");	
	drawMenuBar(0,0,WindowW,1.5*GetFontHeight());
	double Y=0.25*GetFontHeight();
	MovePen(0.3,Y);
	SetPenColor("Black");
	DrawTextString(location);
	MovePen(3,Y);
	DrawTextString(size);
	
	MovePen(6,Y);
	DrawTextString(hw_rate);
	
	MovePen(9.5,Y);
	if(IS_TAILOR==FALSE)
	{
		DrawTextString("��ǰģʽ��ѡ��");
	}
	else
	{
		DrawTextString("��ǰģʽ���ü�");
	}
	
	MovePen(12.5,Y);
	DrawTextString("�ļ�����");
	DrawTextString(name);
}

void DrawButton()            //��ͼ�깤������ť 
{
	double y=WindowH-3;
	double x=0.4; 
	double w=1;
	double h=0.4; 
	//�Զ�����ɫ 
	DefineColor("LL Gray",231.0/255,231.0/255,231.0/255);
	SetPenColor("LL Gray");
	drawRectangle(0,0,w+2*x,WindowH,1); 
	SetPenColor("Black");
	drawLabel(x,WindowH-1.5,"ͼ�깤����"); 
	//��ť 
	if(button(GenUIID(0),x,y,w,h,"��"))
	{
		SelectFile(1);
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"�ر�"))
	{
		SelectFile(2);
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"����")&&OPEN==TRUE)
	{
		SelectFile(3);
	}
	
	if(IS_TAILOR==FALSE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"�ü�"))
	{
		SelectFunction(5);
	}
	if(IS_TAILOR==TRUE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"ȷ��"))
	{
		SelectFunction(5);
	}
	
	if(IS_LOCK==FALSE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"����"))           //����ͼƬ����� 
	{
		IS_LOCK=!IS_LOCK;
		ClearSpace(0,0,5,10);
		Display();
	}
	if(IS_LOCK==TRUE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"����"))           // ���� 
	{
		IS_LOCK=!IS_LOCK;
		ClearSpace(0,0,5,10);
		Display(); 
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"����"))
	{
		SAVE=FALSE; 
		SelectFunction(7);
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"�˳�"))
	{
		SelectFile(4);
	}
	
}
