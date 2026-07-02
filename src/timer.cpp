#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <mmsystem.h>
#include <shellapi.h>
#include <wchar.h>

#define TIMER1_ID 50



BOOL Cexit=false;
const char g_szClassName[] = "cWind";
int wchartoint(wchar_t* p){
	int res;
	swscanf(p,L"%d",&res);
	return res;
}


void plsound(){
	PlaySound("res/b2.wav", NULL, SND_SYNC);
}
int running=1;
DWORD WINAPI PLS( LPVOID lpParam ){
	while(running==1){
		PlaySound("res/b2.wav", NULL, SND_SYNC);
	}
	
	return 0;
}
HANDLE mthread;
DWORD thId=0;
HWND txtB,ssb,ed,minB,secB,ssB,rB;
unsigned char state=0;
HFONT font=CreateFont(100,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Calibri");
HFONT bfont=CreateFont(20,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Calibri");
int font_width,font_height;
int minu=0,sec=0;
int decr=0;
int decre=1;
int alert=0;
char str[] = "00:00";
char wstr[] = "Timer 00:00";

//std::thread plth(plsound);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
	// Install the low-level keyboard & mouse hooks
	// Keep this app running until we're told to stop
	//MessageBox(NULL,TEXT("All low level keys are disabled and they are shown on command line.\nClick OK to terminate program\n"),TEXT("Master Keyboard"), MB_OK|MB_ICONASTERISK);
	//while(!Cexit){
	//	Sleep(100);
	//}
	int argLength=0;
	wchar_t **args;
	args=CommandLineToArgvW(GetCommandLineW(),&argLength);
	argLength--;
	if(args!=NULL){
		if(argLength>0){
			args=&args[1];
			if(argLength>1){// M S
				minu=wchartoint(args[0]);
				sec=wchartoint(args[1]);
				
			}else if(argLength==1){// M
				minu=wchartoint(args[0]);
			}
		}
		
	}
	
	WNDCLASSEX wc;
	HWND hwnd,hwnd2;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,//Window styles (optional)
		g_szClassName,//Class name
		"Timer",//Window title
		WS_OVERLAPPEDWINDOW,//Window style
		CW_USEDEFAULT, //X position
		CW_USEDEFAULT, //Y position
		230, //Width
		206, //Height
		NULL, //Parent Window
		NULL, //Menu
		hInstance, //Instance handle
		NULL //Additional application data
		);
		

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	if(hwnd2 == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	ShowWindow(hwnd, SW_SHOW);
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	UpdateWindow(hwnd);
	
	// Step 3: The Message Loop
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	return Msg.wParam;
}


// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//printf("MESSAGE:%d WPARAM:%d LPARAM:%X\n",msg,wParam,lParam);
	
	switch(msg)
	{
		case WM_COMMAND:
			if(wParam==252){
					minu=0;
					sec=0;
					int decr=0;
					int decre=1;
					alert=0;
					KillTimer(hwnd,TIMER1_ID);
					sprintf(str,"%02d:%02d",minu,sec);
					SetWindowText(txtB,str);
				}
			if(wParam==253){
				minu++;
				if(minu==100){
					minu=0;
				}
				sprintf(str,"%02d:%02d",minu,sec);
				SetWindowText(txtB,str);
			}
			if(wParam==254){
				sec++;
				if(sec==60){
					sec=0;
				}
				sprintf(str,"%02d:%02d",minu,sec);
				SetWindowText(txtB,str);
			}
			if(wParam==255){
				if(alert==1){
					//plth.terminate();
					//system("timer");
					//DestroyWindow(hwnd);
					//TerminateThread(mthread,0);
					running=0;
					 //PostThreadMessage(thId, WM_QUIT, (WPARAM) NULL, (LPARAM) NULL);
						//WaitForSingleObject(mthread, 5000);
				}
				state=~state;
				if(state){
					//SetWindowText(ssB,"Stop");
					if(sec==minu&&sec==0){
						decre=0;
					}
					running=1;
					SetTimer(hwnd,TIMER1_ID,500,NULL);
					
				}else{
					KillTimer(hwnd,TIMER1_ID);
					
				}
				
			}
			
		break;
		case WM_CREATE:
			txtB=CreateWindow(
			"static",
			"00:00",
			WS_VISIBLE |WS_CHILD,
			20,20,
			250,100,
			hwnd, NULL, NULL, NULL);
			
			minB = CreateWindow(
			"BUTTON",	// Predefined class; Unicode assumed 
			"Min",		// Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,	// Styles 
			20,			// x position 
			40,		// y position 
			50,		// Button width
			25,			// Button height
			hwnd,		// Parent window
			(HMENU)253, // Assign appropriate control ID
			(HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE),
			NULL);		// Pointer not needed.
			secB = CreateWindow(
			"BUTTON",	// Predefined class; Unicode assumed 
			"Sec",		// Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,	// Styles 
			20,			// x position 
			40,		// y position 
			50,		// Button width
			25,			// Button height
			hwnd,		// Parent window
			(HMENU)254, // Assign appropriate control ID
			(HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE),
			NULL);		// Pointer not needed.
			ssB = CreateWindow(
			"BUTTON",	// Predefined class; Unicode assumed 
			"S/S",		// Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,	// Styles 
			20,			// x position 
			40,		// y position 
			50,		// Button width
			25,			// Button height
			hwnd,		// Parent window
			(HMENU)255, // Assign appropriate control ID
			(HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE),
			NULL);		// Pointer not needed.
			rB = CreateWindow(
			"BUTTON",	// Predefined class; Unicode assumed 
			"R",		// Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,	// Styles 
			20,			// x position 
			40,		// y position 
			50,		// Button width
			25,			// Button height
			hwnd,		// Parent window
			(HMENU)252, // Assign appropriate control ID
			(HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE),
			NULL);		// Pointer not needed.
			{
			HDC heDC = GetDC(NULL);
			LOGFONT logfont;
			GetObject(font, sizeof(LOGFONT), &logfont);
			HFONT hNewFont = CreateFontIndirect(&logfont);
			SelectObject(heDC, hNewFont);
			RECT re = { 0, 0, 0, 0 };
			char str[] = "00:00";
			sprintf(str,"%02d:%02d",minu,sec);
			DrawText(heDC, str, strlen(str), &re, DT_CALCRECT);
			//printf("%d %d\n",re.right,re.bottom);
			font_width=re.right;
			font_height=re.bottom;
			DeleteObject(hNewFont);
			SendMessage(txtB,WM_SETFONT,(WPARAM)font,MAKELPARAM(true,0));
			SendMessage(minB,WM_SETFONT,(WPARAM)bfont,MAKELPARAM(true,0));
			SendMessage(secB,WM_SETFONT,(WPARAM)bfont,MAKELPARAM(true,0));
			SendMessage(ssB,WM_SETFONT,(WPARAM)bfont,MAKELPARAM(true,0));
			SendMessage(rB,WM_SETFONT,(WPARAM)bfont,MAKELPARAM(true,0));
			sprintf(str,"%02d:%02d",minu,sec);
			SetWindowText(txtB,str);
			}
			
		break;
		case WM_CLOSE:
			//ShowWindow(hwnd, 2);
			
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			
			PostQuitMessage(0);
		
		break;
		
		case WM_SIZE:
			
			MoveWindow(txtB,LOWORD(lParam)/2-font_width/2,10,LOWORD(lParam),HIWORD(lParam)-80,true);
			MoveWindow(minB,1*LOWORD(lParam)/6-25,HIWORD(lParam)-50,50,25,true);
			MoveWindow(secB,3*LOWORD(lParam)/6-25,HIWORD(lParam)-50,50,25,true);
			MoveWindow(ssB,5*LOWORD(lParam)/6-25,HIWORD(lParam)-50,50,25,true);
			MoveWindow(rB,(3*LOWORD(lParam)/6+1*LOWORD(lParam)/6)/2-8,HIWORD(lParam)-50,15,25,true);
			
		break;
		case WM_CTLCOLORSTATIC:
			SetTextColor((HDC)wParam,RGB(0,0,0));
			SetBkMode((HDC)wParam,TRANSPARENT);
			
			return (LRESULT)GetStockObject(WHITE_BRUSH);
		case WM_CTLCOLOREDIT:
			SetTextColor((HDC)wParam,RGB(0,255,0));
			SetBkMode((HDC)wParam,TRANSPARENT);
			return (LRESULT)GetStockObject(BLACK_BRUSH);
		case WM_TIMER:
			if(decre==1){
				
				decr++;
				if(decr%2==1){
					sprintf(str,"%02d %02d",minu,sec);
					SetWindowText(txtB,str);
					
					break;
				}
				sec--;
				if(sec<0){
					sec=59;
					minu--;
					if(minu==-1){
						minu=0;
						sec=0;
						KillTimer(hwnd,TIMER1_ID);
						alert=1;
						//PlaySound("timer.wav", NULL, SND_ASYNC);

						mthread=CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            PLS,       // thread function name
            NULL,          // argument to thread function 
            0,                      // use default creation flags 
            &thId);   // returns the thread identifier
						
					}
				}
			}else{
				decr++;
				if(decr%2==1){
					sprintf(str,"%02d %02d",minu,sec);
					SetWindowText(txtB,str);
					break;
				}
				
				sec++;
				if(sec==60){
					sec=0;
					minu++;
					if(minu==100){
						minu=0;
					}
				}
			}
			sprintf(str,"%02d:%02d",minu,sec);
			SetWindowText(txtB,str);
			sprintf(wstr,"Timer %02d:%02d",minu,sec);
			SetWindowText(hwnd,wstr);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}