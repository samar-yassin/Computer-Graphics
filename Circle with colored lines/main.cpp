#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<iostream>
using namespace std;
#include<math.h>
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

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
           1000,                 /* The programs width */
           700,                 /* and height in pixels */
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


void parametricline(HDC hdc,int x1,int y1,int x2,int y2,COLORREF color){
double dx=x2-x1;
double dy=y2-y1;
for(double t=0;t<1;t+=0.001){
    int x=x1+(dx*t);
    int y=y1+(dy*t);
    SetPixel(hdc,x,y,color);
}
}

void draweight(HDC hdc,int x,int y,int xc,int yc){
parametricline(hdc,xc+x,yc+y,xc,yc,RGB(0,255,255));
parametricline(hdc,xc-x,yc+y,xc,yc,RGB(0,128,0));
parametricline(hdc,xc+x,yc-y,xc,yc,RGB(25,25,112));
parametricline(hdc,xc-x,yc-y,xc,yc,RGB(0,0,255));
parametricline(hdc,xc-y,yc+x,xc,yc,RGB(255,0,0));
parametricline(hdc,xc+y,yc-x,xc,yc,RGB(255,255,0));
parametricline(hdc,xc+y,yc+x,xc,yc,RGB(255,127,80));
parametricline(hdc,xc-y,yc-x,xc,yc,RGB(255,255,0));

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
    draweight(hdc,x,y,xc,yc);
}
}
/*  This function is called by the Windows function DispatchMessage()  */

int rr,x_c,y_c,x_2,y_2;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{   HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
    case WM_LBUTTONUP:
        x_c=LOWORD(lParam);
        y_c=HIWORD(lParam);
        break;
    case WM_RBUTTONUP:
        x_2=LOWORD(lParam);
        y_2=HIWORD(lParam);
        rr=sqrt(pow((x_2-x_c),2)+pow((y_2-y_c),2));
        midpoint(hdc,x_c,y_c,rr);
        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
