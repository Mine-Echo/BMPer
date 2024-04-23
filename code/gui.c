#include"gui.h"

void DrawMenu() //画菜单栏 
{
	
	SetPenSize(2);
	//菜单名称及其内容 
	char *menuListFile[]=
	{
		"文件",
		"打开    Ctrl-O",
		"关闭          ",
		"保存    Ctrl-S",
		"退出    Ctrl-E" 
	 };
	 
	 char *menuListFunction2[]=
	{
		"其他功能",
		"左右翻转 Ctrl-A",
		"上下翻转 Ctrl-D", 
		"模糊           F1",
		"灰度图       F2",
		"二值化       F3",
		"拉普拉斯算子 F4",
		"自定义卷积核 F5"
		
	 };
	 
	char *menuListFunction[]=
	{
		"基础功能",
		"放大    Ctrl-L",
		"缩小    Ctrl-R",
		"旋转(逆)    <-",
		"旋转(顺)    ->",
		"裁剪    Ctrl-T",
		"压缩    Ctrl-P",
		"撤销    Ctrl-Z" 
	};
	
	char *menuListAbout[]=
	{
		"关于",
		"关于本软件",
		"使用方法" ,
		"背景音乐" 
	};
	//不同状态呈现不同菜单 
	menuListFunction[5]= (IS_TAILOR ? "确认  Ctrl-T" : "裁剪    Ctrl-T"); 
	menuListAbout[3]=(IS_PLAY? "关闭背景音乐":"打开背景音乐"); 
	//设定菜单位置及其大小 
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

void SelectFile(int selection)             //文件菜单栏 
{
	if(selection==1)//对应打开按键 
	{
		window=FindWindow(NULL,"BMP图片编辑器");
		if(OPEN==FALSE)
		{
			InitConsole();
			printf("请输入想要打开的BMP图片名称:\n");
			scanf("%s",FileName);
			printf("请关闭此窗口\n"); 
			FreeConsole();     //关闭控制台时不关闭整个程序 
			Init();
			//如果打开成功，显示图片 
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
					TEXT("文件解压成功！"),
					TEXT("提示"),
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
					TEXT("文件打开失败"),
					TEXT("提示"),
					MB_ICONHAND | MB_OK);
			       }
				DisplayClear();
				Display();
				ShowImage();
			}
		    //若打开失败，提示
			else{
				MessageBox(
					window,
					TEXT("文件打开失败"),
					TEXT("提示"),
					MB_ICONHAND | MB_OK);
			}
		}
		else
			MessageBox(
					window,
					TEXT("已有文件被打开\n请先关闭当前文件\n再打开其他文件"),
					TEXT("提示"),
					MB_ICONHAND | MB_OK);
	}

	else if(selection==2)//关闭 
	{
		if(OPEN==FALSE);            //如果文件未打开则不做任何事 
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
			window=FindWindow(NULL,"BMP图片编辑器");
			int choice=MessageBox(
				window,
				TEXT("文件尚未保存！\n是否保存文件？"),
				TEXT("提示"),
				MB_ICONWARNING | MB_YESNOCANCEL); 
			ChoiceOfClose(choice); 
		}
	}
	else if(selection==3&&OPEN==TRUE)//保存 
	{
		if(SAVE==FALSE)
		{
			InitConsole();
			//PutImage("output.bmp");
			printf("请输入想要保存为的BMP格式图片名称:\n");
			scanf("%s",FileName);
			printf("请关闭此窗口\n"); 
			FreeConsole();
			window=FindWindow(NULL,"BMP图片编辑器");
			PutImage(FileName);
			//如果保存成功
			if(1)
			{
				MessageBox(
					window,
					TEXT("文件保存成功"),
					TEXT("提示"),
					MB_OK);
				SAVE=TRUE;
			}
			//若保存失败，提示 
			else
			{
				MessageBox(
				window,
				TEXT("文件保存失败"),
				TEXT("提示"),
				MB_ICONHAND | MB_OK);
				SAVE=FALSE;
			}
		}
	}
	
	else if(selection==4)//退出 
	{
		if(SAVE==TRUE||OPEN==FALSE) 
		{
			exit(0);
		}
		else
		{
			window=FindWindow(NULL,"BMP图片编辑器");
			int choice=MessageBox(
				window,
				TEXT("文件尚未保存！\n是否保存文件？"),
				TEXT("提示"),
				MB_ICONWARNING | MB_YESNOCANCEL); 
			ChoiceOfExit(choice); 
		}
		
	}
}

void ChoiceOfClose(int choice)//点击关闭时跳出弹窗的选择 
{
	if(choice==IDYES)//选择是保存文件 ，在关闭文件 
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
	else if(choice==IDNO)//选择否直接关闭 
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

void ChoiceOfExit(int choice)//点击退出时跳出弹窗的选择 
{
	if(choice==IDYES)//选择是保存文件，再退出 
	{
		SelectFile(3);
		exit(0); 
	}
	else if(choice==IDNO)//选择否直接退出 
		exit(0);
	else ;
}

void Init()
{
	SAVE=TRUE;
	OPEN=FALSE;
}

void SelectFunction(selection)           //基础功能菜单栏 
{
	static int width;
	static int height;

	//其他功能需要文件打开才能使用 
	if(OPEN==TRUE)
	{
		switch(selection)
		{
			case 1 :           // 放大 
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
				
			case 2 :      //缩小 
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
				
			case 3 :                 // 旋转逆时针 
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
			case 4 :            //旋转顺时针 
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
			case 5 :           //裁剪 
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
				
			case 6 :                       // 压缩 
				{
				char n[52];
				int len=strlen(name);
				strcpy(n,name);
				n[len]='.';
				n[len+1]='a';
				n[len+2]='\0';
				SaveCompress(top->bmp_data,n);	
				SAVE=TRUE; 
				window=FindWindow(NULL,"BMP图片编辑器");
				MessageBox(
				window,
				TEXT("文件已压缩为同名.a格式文件"),
				TEXT("提示"),
				MB_OK);
				break;
				}
				
			case 7 :               // 撤销 
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

void SelectFunction2(int selection)          //其他功能菜单栏 
{
	if(OPEN==TRUE)
	switch(selection)
	{
		case 3:         //模糊 
			{
			SAVE=FALSE; 
	 		double core[3][3]={0.0625,0.125,0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625};
	 		convolution(core);
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}
			
		case 4:            //灰度图 
			{
			SAVE=FALSE; 
	 		Gray();
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}
		case 5:              //二值化 
			{
			SAVE=FALSE; 
	 		Binarization(128);//二值化阈值 
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}
		case 6:            //拉普拉斯算子 
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
		case 7:               // 自定义卷积核 
			{
			SAVE=FALSE; 
	 		double core[3][3]={0,0,0,0,0,0,0,0,0};
	 		int i,j;
	 		InitConsole();
	 		printf("请输入完整的(3*3)大小的卷积核，请勿中途关闭窗口，否则将导致程序崩溃！\n例：0.11 0.11 0.11\n    0.11 0.11 0.11\n    0.11 0.11 0.11\n(模糊卷积核)\n");
			for(i=0;i<3;i++)
			   {
			   	for(j=0;j<3;j++)
			   	 {
			   	 	scanf("%lf",&core[i][j]);
			   	 }
			   } 
			printf("请关闭窗口\n");
			FreeConsole();
	 		convolution(core);
	        DisplayClear();
	        Display();
	        ShowImage();
				break;
			}	
		case 1:                 // 左右翻转 
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
		case 2:          // 上下翻转 
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

void SelectAbout(int selection)         // 关于菜单栏 
{
	window=FindWindow(NULL,"BMP图片编辑器");
	if(selection==1)            //关于本软件 
	{	
		MessageBox(
			window,
			TEXT("欢迎使用BMPer--BMP图片编辑器软件，本软件由本小组合力开发，不仅可以压缩\\解压缩24位BMP真彩图片，还可以对其进行放缩、旋转、裁剪、模糊、灰度等操作，图片编辑完后记得进行保存哦！\n\n祝您使用愉快！！\n"),
			TEXT("关于本软件"),
			MB_OK);
	}
	if(selection==2)        // 使用方法 
	{
		MessageBox(
			window,
			TEXT("初次使用：\n请先点击打开按键并输入正确的文件名称以打开一张24位真彩BMP图片\n\n然后你可以点击菜单中的基本功能，其中的放大、缩小、旋转、裁剪、压缩、撤销您都可以尝试；如果这些功能还不够您的使用，您还可以点击菜单中的其他功能（翻转、模糊、灰度图、二值化、拉普拉斯算子、自定义卷积核）来实现更多的图片编辑操作。\n\n点击图片并拖动可以改变图片的位置，拖动拖动条可以随意改变图片的大小，点击图表工具栏中的锁定可以锁定长宽比\n\n压缩以后如何解压？点击打开按键打开压缩后的图片就能自动解压了，再点击保存就能将解压后的图片保存为文件了\n\n如果不小心进行了错误的操作，不用担心，点击撤销可以让图片返回至上一步的状态。所以尽情进行图片编辑吧！！！\n\n注意：\n点击裁剪会进入裁剪模式，此时若进行某些操作会直接退出裁剪模式，裁剪完后点击确认就可以后的裁剪后的图片了。\n\n完成图片的编辑后要记得保存，但是即使您忘记保存直接点击了关闭或退出按键，软件也会弹出弹窗提醒您保存，而如果你已保存或者未编辑图片，则不会弹出弹窗提醒。\n\n关于菜单中可以打开背景音乐，让您心情愉悦\n\n绝大多数按键都有快捷键，熟悉他们可以大大方便您的操作！！！"),
			TEXT("使用方法"),
			MB_OK);
	}
	else if(selection==3)           //背景音乐 
	{ 
		IS_PLAY = ! IS_PLAY;
		if (IS_PLAY == TRUE)
		{ 
			if(!PlaySound (TEXT("..\\背景音乐.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))
				MessageBox(
					window,
					TEXT("音乐播放失败"),
					TEXT("提示"),
					MB_ICONHAND | MB_OK);
		}		
		else 
			PlaySound (NULL, NULL, SND_FILENAME | SND_ASYNC);
		 
	} 
}

void DrawInformationBar(double x,double y,double w,double h,double w_rate,double h_rate)       //画状态信息栏（打开图片时才会显示） 
{
	char location[20];
	sprintf(location,"位置：(%.2lf,%.2lf)",x,y);
	char size[25];
	sprintf(size,"宽：%.lf    高：%.lf",w,h); 
	char hw_rate[30];
	sprintf(hw_rate,"缩放率：(%3d%%,%3d%%)",(int)((w_rate*1000+5)/10),(int)((h_rate*1000+5)/10));
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
		DrawTextString("当前模式：选择");
	}
	else
	{
		DrawTextString("当前模式：裁剪");
	}
	
	MovePen(12.5,Y);
	DrawTextString("文件名：");
	DrawTextString(name);
}

void DrawButton()            //画图标工具栏按钮 
{
	double y=WindowH-3;
	double x=0.4; 
	double w=1;
	double h=0.4; 
	//自定义颜色 
	DefineColor("LL Gray",231.0/255,231.0/255,231.0/255);
	SetPenColor("LL Gray");
	drawRectangle(0,0,w+2*x,WindowH,1); 
	SetPenColor("Black");
	drawLabel(x,WindowH-1.5,"图标工具栏"); 
	//按钮 
	if(button(GenUIID(0),x,y,w,h,"打开"))
	{
		SelectFile(1);
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"关闭"))
	{
		SelectFile(2);
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"保存")&&OPEN==TRUE)
	{
		SelectFile(3);
	}
	
	if(IS_TAILOR==FALSE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"裁剪"))
	{
		SelectFunction(5);
	}
	if(IS_TAILOR==TRUE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"确认"))
	{
		SelectFunction(5);
	}
	
	if(IS_LOCK==FALSE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"锁定"))           //锁定图片长宽比 
	{
		IS_LOCK=!IS_LOCK;
		ClearSpace(0,0,5,10);
		Display();
	}
	if(IS_LOCK==TRUE&&button(GenUIID(0),x,y=y-INTERVAL,w,h,"解锁"))           // 解锁 
	{
		IS_LOCK=!IS_LOCK;
		ClearSpace(0,0,5,10);
		Display(); 
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"撤销"))
	{
		SAVE=FALSE; 
		SelectFunction(7);
	}
	
	if(button(GenUIID(0),x,y=y-INTERVAL,w,h,"退出"))
	{
		SelectFile(4);
	}
	
}
