#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

int X_start,X_end,Y_start,Y_end,X_left,Y_top,X_right,Y_bottom,rr;
int Num_of_Points=0;
int choice;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};


void drawfour(HDC hdc,int x,int y,int xc,int yc){
SetPixel(hdc,xc+x,yc+y,RGB(100,0,0));
SetPixel(hdc,xc-x,yc+y,RGB(100,0,0));
SetPixel(hdc,xc-y,yc+x,RGB(100,0,0));
SetPixel(hdc,xc+y,yc+x,RGB(100,0,0));

}

void draweight(HDC hdc,int x,int y,int xc,int yc){
SetPixel(hdc,xc+x,yc+y,RGB(100,0,0));
SetPixel(hdc,xc-x,yc+y,RGB(100,0,0));
SetPixel(hdc,xc+x,yc-y,RGB(100,0,0));
SetPixel(hdc,xc-x,yc-y,RGB(100,0,0));

SetPixel(hdc,xc-y,yc+x,RGB(100,0,0));
SetPixel(hdc,xc+y,yc-x,RGB(100,0,0));
SetPixel(hdc,xc+y,yc+x,RGB(100,0,0));
SetPixel(hdc,xc-y,yc-x,RGB(100,0,0));
}
void midpoint(HDC hdc,int xc,int yc,int r){
int x=0;
int y=r;
double d=1-r;
while(x<y){
    if(d<=0){
        d=d+2*x+3;
        x++;
    }
    else{
        d=d+2*(x-y)+5;
        x++;
        y--;
    }
    drawfour(hdc,x,y,xc,yc);
}
}

void takeInput(){
cout<<"\t1 -> For the line drawing, please enter 2 mouse clicks.\n\t2 -> For the circle drawing, please enter 2 mouse clicks.";
cout<<"\n\t2 -> For half circles drawing, please enter 2 mouse clicks.";
cout<<"\n\t4 -> For a new window (Circle) drawing, please enter 2 mouse clicks.\n\t5 -> Close the Window App.\n";
cout<<"choice : ";
cin>>choice;
}
void isInsideCircle(int cx, int cy, int r, int x, int y) {
   int dist = (x - cx) * (x - cx) + (y - cy) * (y - cy);
   if ( dist <= r * r){
    SetPixel(hdc,x,y,RGB(30,144,255));
   }
   else
    SetPixel(hdc,x,y,RGB(220,20,60));

}

void parametricline(HDC hdc,int x1,int y1,int x2,int y2,int cx,int cy,int r){
double dx=x2-x1;
double dy=y2-y1;
for(double t=0;t<1;t+=0.001){
    int x=x1+(dx*t);
    int y=y1+(dy*t);
    isInsideCircle(c1)
    
}



int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
    case WM_LBUTTONDBLCLK:
                    cout<<Num_of_Points;

        if(Num_of_Points==0)
        {
            X_left=LOWORD(lParam);
            Y_top=HIWORD(lParam);
            Num_of_Points++;
        }
        else if (Num_of_Points==1)
        {
            X_right=LOWORD(lParam);
            Y_bottom=HIWORD(lParam);
            rr=sqrt(pow((X_right-X_left),2)+pow((Y_bottom-Y_top),2));
            midpoint(hdc,X_left,Y_top,rr);
            Num_of_Points++;
        }
        else if(Num_of_Points==2)
        {
            X_start=LOWORD(lParam);
            Y_start=HIWORD(lParam);
            Num_of_Points++;
        }
       /* else if (Num_of_Points==3)
        {
            X_end=LOWORD(lParam);
            Y_end=HIWORD(lParam);
            //CohenSuth(hdc,X_start,Y_start,X_end,Y_end,X_left,Y_top,X_right,Y_bottom);

        }*/
        break;

    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
