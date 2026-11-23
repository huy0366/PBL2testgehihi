#include "raylib.h"
#include <ctime>
#include <iostream>
#include <cstring>
#include "src/Services/QLNV.h"

// ================= GIAO DIỆN CÁC PHÂN HỆ =================
#include "src/UI/GUI_Common.h"
#include "src/UI/GUI_Home.h"
#include "src/UI/GUI_Employee.h"
#include "src/UI/GUI_Department.h"
#include "src/UI/GUI_Salary.h"
#include "src/UI/GUI_Attendance.h"

using namespace std;

// ================= ĐIỀU PHỐI MÀN HÌNH CHÍNH =================
void DrawMainContent(int &currentScreen, QLNV *QL)
{
    if (currentScreen == SCREEN_HOME)
    {
        Draw_Screen_Home(QL);
    }
    else if (currentScreen == SCREEN_EMPLOYEE)
    {
        Draw_Screen_Employee(QL);
    }
    else if (currentScreen == SCREEN_DEPARTMENT)
    {
        Draw_Screen_Deparment(QL);
    }
    else if (currentScreen == SCREEN_SALARY)
    {
        Draw_Screen_Salary(QL);
    }
    else if (currentScreen == SCREEN_ATTENDANCE)
    {
        Draw_Screen_ChamCong(QL);
    }
}

// ================= HÀM MAIN CHÍNH =================
int main()
{
    // 1. Khởi tạo cửa sổ Raylib
    InitWindow(1792, 1008, "PBL2 - Quản Lý Nhân Sự");
    SetTargetFPS(60);

    // 2. Tải font chữ tiếng Việt có dấu
    int codepoints[8000];
    for (int i = 0; i < 8000; i++)
        codepoints[i] = 32 + i;
    myFont = LoadFontEx("font/times.ttf", 32, codepoints, 8000);
    SetTextureFilter(myFont.texture, TEXTURE_FILTER_BILINEAR);

    // 3. Khởi tạo đối tượng Quản Lý Nhân Sự
    QLNV *QL = new QLNV;

    int currentScreen = SCREEN_HOME;

    // 4. Vòng lặp giao diện chính
    while (!WindowShouldClose())
    {
        if (currentScreen == Exit)
        {
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawSidebar(currentScreen);
        if (currentScreen != Exit)
        {
            DrawMainContent(currentScreen, QL);
            VeThongBao();
        }

        EndDrawing();
    }

    // 5. Giải phóng tài nguyên và đóng cửa sổ
    delete QL;
    UnloadFont(myFont);
    CloseWindow();

    return 0;
}
