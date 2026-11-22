#pragma once
#include "raylib.h"
#include <ctime>
#include "../Services/QLNV.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// ================= BIẾN VÀ CỜ TOÀN CỤC GIAO DIỆN =================
inline Font myFont;
inline bool g_isModalActive = false; // Chặn click nút nền khi có bất kỳ modal / pop-up nào mở

inline time_t now = time(0);
inline tm *t = localtime(&now);
inline int day = t->tm_mday;
inline int month = t->tm_mon + 1;
inline int year = t->tm_year + 1900;

// Hệ thống thông báo toast góc trên bên phải
inline string tbNoiDung = "";
inline bool tbLaLoi = true;
inline bool tbDangHien = false;
inline float tbThoiGian = 0.0f;
inline float tbX = 2000.0f;

// ================= RESET TRẠNG THÁI KHI CHUYỂN MỤC =================
// g_menuGen  : tăng khi đổi mục ở sidebar menu
// g_resetGen : tăng khi đổi mục ở sidebar menu HOẶC đổi tab con bên trong
inline int g_menuGen = 0;
inline int g_resetGen = 0;

enum Screen
{
    SCREEN_HOME,       // Trang Chủ
    SCREEN_EMPLOYEE,   // Nhân viên
    SCREEN_DEPARTMENT, // Bộ phận
    SCREEN_SALARY,     // Bảng lương
    SCREEN_ATTENDANCE, // Chấm công
    Exit,              // Thoát hệ thống
};

// ================= CÁC HÀM TIỆN ÍCH DÙNG CHUNG =================

inline string FormatSoTien(long long so)
{
    if (so < 0)
        return "-" + FormatSoTien(-so);
    string s = to_string(so);
    string kq = "";
    int dem = 0;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        kq = s[i] + kq;
        dem++;
        if (dem % 3 == 0 && i > 0)
            kq = "." + kq;
    }
    return kq;
}

inline bool XuatBangLuongThang(QLNV *QL, int thang, int nam)
{
    if (QL == nullptr)
        return false;
    return QL->XuatBangLuongThang(thang, nam);
}

// Kiểu nút chức năng chuẩn
enum class NutStyle
{
    Green,     // Nút Thêm, Xác nhận
    Blue,      // Nút Sửa, Lưu
    Red,       // Nút Xóa, Xác nhận xóa
    Secondary  // Nút Hủy, Hủy xóa
};

// Hàm vẽ nút bấm hiện đại với icon sắc nét và hiệu ứng hover
inline void VeNutChucNang(Rectangle r, const char *text, NutStyle style, bool isHover, int iconType = 0)
{
    Color bg, border, txtColor;
    if (style == NutStyle::Green)
    {
        bg = isHover ? Color{40, 180, 100, 255} : Color{34, 160, 88, 255};
        border = isHover ? Color{50, 200, 115, 255} : Color{28, 140, 75, 255};
        txtColor = WHITE;
    }
    else if (style == NutStyle::Blue)
    {
        bg = isHover ? Color{70, 120, 245, 255} : Color{55, 105, 225, 255};
        border = isHover ? Color{90, 140, 255, 255} : Color{45, 90, 200, 255};
        txtColor = WHITE;
    }
    else if (style == NutStyle::Red)
    {
        bg = isHover ? Color{235, 68, 85, 255} : Color{220, 53, 69, 255};
        border = isHover ? Color{250, 90, 105, 255} : Color{190, 40, 55, 255};
        txtColor = WHITE;
    }
    else // Secondary
    {
        bg = isHover ? Color{235, 240, 248, 255} : Color{245, 247, 250, 255};
        border = isHover ? Color{150, 165, 185, 255} : Color{205, 215, 228, 255};
        txtColor = isHover ? Color{30, 40, 55, 255} : Color{60, 70, 85, 255};
    }

    if (isHover)
    {
        DrawRectangleRounded({r.x + 2, r.y + 3, r.width, r.height}, 0.25f, 8, Fade(BLACK, 0.12f));
    }
    DrawRectangleRounded(r, 0.25f, 8, bg);
    DrawRectangleRoundedLinesEx(r, 0.25f, 8, 1.5f, border);

    float textW = MeasureTextEx(myFont, text, 22, 1).x;
    float iconW = (iconType > 0) ? 22.0f : 0.0f;
    float gap = (iconType > 0) ? 8.0f : 0.0f;
    float totalW = iconW + gap + textW;

    float startX = r.x + (r.width - totalW) / 2.0f;
    float textY = r.y + (r.height - 22.0f) / 2.0f;

    if (iconType > 0)
    {
        float icX = startX + 10.0f;
        float icY = r.y + r.height / 2.0f;

        if (iconType == 1) // Plus (+)
        {
            DrawRectangle((int)icX - 7, (int)icY - 2, 14, 4, txtColor);
            DrawRectangle((int)icX - 2, (int)icY - 7, 4, 14, txtColor);
        }
        else if (iconType == 2) // Pencil
        {
            DrawLineEx({icX - 6, icY + 6}, {icX + 5, icY - 5}, 3.0f, txtColor);
            DrawCircle((int)icX + 5, (int)icY - 5, 2.5f, txtColor);
            DrawTriangle({icX - 7, icY + 4}, {icX - 4, icY + 7}, {icX - 9, icY + 9}, txtColor);
        }
        else if (iconType == 3) // Trash
        {
            DrawLineEx({icX - 7, icY - 5}, {icX + 7, icY - 5}, 2.0f, txtColor);
            DrawLineEx({icX - 3, icY - 7}, {icX + 3, icY - 7}, 1.5f, txtColor);
            DrawRectangleLinesEx({icX - 6, icY - 4, 12, 13}, 1.8f, txtColor);
            DrawLineEx({icX - 2, icY - 1}, {icX - 2, icY + 6}, 1.5f, txtColor);
            DrawLineEx({icX + 2, icY - 1}, {icX + 2, icY + 6}, 1.5f, txtColor);
        }
        else if (iconType == 4) // Checkmark (✓)
        {
            DrawLineEx({icX - 7, icY}, {icX - 2, icY + 6}, 2.5f, txtColor);
            DrawLineEx({icX - 2, icY + 6}, {icX + 7, icY - 6}, 2.5f, txtColor);
        }
        else if (iconType == 5) // Cross (✕)
        {
            DrawLineEx({icX - 5, icY - 5}, {icX + 5, icY + 5}, 2.2f, txtColor);
            DrawLineEx({icX + 5, icY - 5}, {icX - 5, icY + 5}, 2.2f, txtColor);
        }
    }

    DrawTextEx(myFont, text, {startX + iconW + gap, textY}, 22, 1, txtColor);
}

// Hộp thoại xác nhận (Xóa, Xác nhận thao tác)
inline bool XacNhan(const string &noiDung, bool &dangMo, const string &tieuDe = "Xác nhận", const string &nutOK = "Xóa")
{
    static bool daMoTruocDo = false;

    if (!dangMo)
    {
        daMoTruocDo = false;
        return false;
    }
    g_isModalActive = true;

    Vector2 mouse = GetMousePosition();
    bool click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    float textW = MeasureTextEx(myFont, noiDung.c_str(), 26, 1).x;
    float boxW = (textW + 80.0f > 520.0f) ? (textW + 80.0f) : 520.0f;
    float boxH = 240.0f;
    Rectangle box = {(sw - boxW) / 2.0f, (sh - boxH) / 2.0f, boxW, boxH};

    // Nền mờ + hộp
    DrawRectangle(0, 0, (int)sw, (int)sh, Fade(BLACK, 0.45f));
    DrawRectangleRounded({box.x + 4, box.y + 6, box.width, box.height}, 0.06f, 10, Fade(BLACK, 0.16f));
    DrawRectangleRounded(box, 0.06f, 10, WHITE);

    // Tiêu đề + nội dung
    DrawRectangleRounded({box.x + 30, box.y + 28, 7, 32}, 0.5f, 4, Color{230, 55, 60, 255});
    DrawTextEx(myFont, tieuDe.c_str(), {box.x + 48, box.y + 26}, 32, 1, Color{20, 25, 35, 255});
    DrawTextEx(myFont, noiDung.c_str(), {box.x + (box.width - textW) / 2.0f, box.y + 95}, 26, 1, Color{50, 60, 75, 255});

    // Nút Hủy / OK
    Rectangle btnHuy = {box.x + box.width - 250, box.y + box.height - 75, 105, 48};
    Rectangle btnOK = {box.x + box.width - 135, box.y + box.height - 75, 105, 48};
    bool hoverHuy = CheckCollisionPointRec(mouse, btnHuy);
    bool hoverOK = CheckCollisionPointRec(mouse, btnOK);

    VeNutChucNang(btnHuy, "Hủy", NutStyle::Secondary, hoverHuy, 5);
    VeNutChucNang(btnOK, nutOK.c_str(), NutStyle::Red, hoverOK, (nutOK == "Xóa" ? 3 : 4));

    if (!daMoTruocDo)
    {
        daMoTruocDo = true;
        return false;
    }

    bool dongY = (click && hoverOK) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER);
    bool huy = (click && (hoverHuy || !CheckCollisionPointRec(mouse, box))) || IsKeyPressed(KEY_ESCAPE);

    if (dongY || huy)
    {
        dangMo = false;
        daMoTruocDo = false;
        g_isModalActive = false;
        return dongY;
    }
    return false;
}

// Bật thông báo
inline void HienThongBao(const string &noiDung, bool laLoi = true)
{
    tbNoiDung = noiDung;
    tbLaLoi = laLoi;
    tbDangHien = true;
    tbThoiGian = 0.0f;
    tbX = (float)GetScreenWidth() + 20.0f;
}

// Vẽ thông báo toast trượt
inline void VeThongBao()
{
    if (!tbDangHien)
        return;

    float dt = GetFrameTime();
    tbThoiGian += dt;

    float textW = MeasureTextEx(myFont, tbNoiDung.c_str(), 22, 1).x;
    float boxW = (textW + 65.0f > 360.0f) ? (textW + 65.0f) : 360.0f;
    float boxH = 72.0f;
    float boxY = 25.0f;

    float dichX;
    if (tbThoiGian < 3.5f)
        dichX = (float)GetScreenWidth() - boxW - 25.0f;
    else
        dichX = (float)GetScreenWidth() + 30.0f;

    tbX += (dichX - tbX) * 10.0f * dt;

    if (tbThoiGian >= 3.5f && tbX >= (float)GetScreenWidth() + 5.0f)
    {
        tbDangHien = false;
        return;
    }

    Rectangle box = {tbX, boxY, boxW, boxH};
    DrawRectangleRounded({box.x + 3, box.y + 4, box.width, box.height}, 0.2f, 8, Fade(BLACK, 0.15f));
    DrawRectangleRounded(box, 0.2f, 8, WHITE);

    Color mauChuDao = tbLaLoi ? Color{230, 55, 60, 255} : Color{34, 190, 90, 255};
    DrawRectangleRoundedLinesEx(box, 0.2f, 8, 1.5f, mauChuDao);
    DrawRectangleRounded({box.x + 8, box.y + 10, 6, box.height - 20}, 0.5f, 4, mauChuDao);

    const char *tieuDeTB = tbLaLoi ? "Thông báo lỗi" : "Thành công";
    DrawTextEx(myFont, tieuDeTB, {box.x + 26, box.y + 10}, 22, 1, mauChuDao);
    DrawTextEx(myFont, tbNoiDung.c_str(), {box.x + 26, box.y + 38}, 22, 1, Color{40, 45, 55, 255});
}

// Thanh menu điều hướng bên trái
inline void DrawSidebar(int &currentScreen)
{
    static bool isLoaded = false;
    static Texture2D anhmenu;
    static Texture2D a21;
    static Texture2D a2;
    static Texture2D a7;
    static Texture2D iconmenu[6];
    if (!isLoaded)
    {
        anhmenu = LoadTexture("photo/anhto/Asset-3.png");
        a21 = LoadTexture("photo/icon/Asset-21.png");
        a2 = LoadTexture("photo/anhto/Asset-2.png");
        a7 = LoadTexture("photo/anhto/Asset-7.png");
        iconmenu[0] = LoadTexture("photo/icon/Asset-6.png");
        iconmenu[1] = LoadTexture("photo/icon/Asset-7.png");
        iconmenu[2] = LoadTexture("photo/icon/Asset-8.png");
        iconmenu[3] = LoadTexture("photo/icon/Asset-9.png");
        iconmenu[4] = LoadTexture("photo/icon/Asset-10.png");
        iconmenu[5] = LoadTexture("photo/icon/Asset-12.png");
        isLoaded = true;
    }
    Vector2 panhmenu = {-80.0f, -47.0f};
    float ranhmenu = 0.0f;
    float sanhmenu = 1.96f;
    Vector2 pa21 = {40.0f, 70.0f};
    float ra21 = 0.0f;
    float sa21 = 0.2f;
    Vector2 pa2 = {30.0f, 650.0f};
    float ra2 = 0.0f;
    float sa2 = 0.54f;

    DrawTextureEx(anhmenu, panhmenu, ranhmenu, sanhmenu, WHITE);
    DrawTextureEx(a7, {290.f, -20.f}, 0, 1.25, WHITE);
    DrawTextureEx(a21, pa21, ra21, sa21, WHITE);
    DrawTextEx(myFont, "PBL2", {130.f, 65.f}, 35, 1, BLACK);
    DrawTextEx(myFont, "Quản lí nhân sự", {130.f, 100.f}, 25, 1, BLACK);
    DrawTextureEx(a2, pa2, ra2, sa2, WHITE);

    const char *menu[] = {"Trang chủ", "Nhân viên", "Phòng ban", "Tiền lương", "Chấm công", "Thoát"};
    int startY = 220;
    int spacing = 58;
    int sizeword = 22;

    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < 6; i++)
    {
        int currentY = startY + (i * spacing);
        Rectangle button_Rect{18.0f, (float)currentY - 6, 264.0f, 46.0f};
        bool Hover = CheckCollisionPointRec(mousePos, button_Rect);

        if (!g_isModalActive && Hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (currentScreen != i)
            {
                g_menuGen++;
                g_resetGen++;
            }
            currentScreen = i;
        }

        bool isActive = (i == currentScreen);
        if (isActive)
        {
            DrawRectangleRounded(button_Rect, 0.35f, 8, Color{236, 232, 255, 255});
            DrawRectangleRoundedLinesEx(button_Rect, 0.35f, 8, 1.5f, Color{165, 145, 245, 255});
            DrawRectangleRounded({button_Rect.x + 2, button_Rect.y + 7, 5, button_Rect.height - 14}, 0.5f, 4, Color{98, 70, 234, 255});
        }
        else if (Hover)
        {
            DrawRectangleRounded(button_Rect, 0.35f, 8, Color{244, 242, 255, 200});
            DrawRectangleRoundedLinesEx(button_Rect, 0.35f, 8, 1.0f, Color{210, 200, 245, 180});
        }

        // Vẽ Icon: kích thước gốc 59x55 -> scale 0.52f = 30.6 x 28.6px, căn giữa hoàn hảo
        float icScale = 0.52f;
        float icW = 59.0f * icScale;
        float icH = 55.0f * icScale;
        float icX = button_Rect.x + 14.0f;
        float icY = button_Rect.y + (button_Rect.height - icH) / 2.0f;
        DrawTextureEx(iconmenu[i], {icX, icY}, 0, icScale, WHITE);

        // Vẽ Chữ
        float txtX = icX + icW + 14.0f;
        float txtY = button_Rect.y + (button_Rect.height - sizeword) / 2.0f;
        Color txtColor = isActive ? Color{80, 45, 210, 255} : (Hover ? Color{98, 70, 234, 255} : Color{45, 50, 65, 255});
        DrawTextEx(myFont, menu[i], {txtX, txtY}, sizeword, 1, txtColor);
    }
}

inline void HieuUngGo(bool &active, Rectangle &btn, char input[], int fSize = 28)
{
    float yOffset = btn.y + (btn.height - fSize) / 2.0f;
    if (active && ((int)(GetTime() * 2) % 2 == 0))
    {
        float textWidth = MeasureTextEx(myFont, input, fSize, 1).x;
        DrawTextEx(myFont, "_", {btn.x + 10 + textWidth, yOffset}, fSize, 1, Color{50, 100, 220, 255});
    }
    DrawTextEx(myFont, input, {btn.x + 10, yOffset}, fSize, 1, BLACK);
}

inline int GetDaysInMonth(const int &m, const int &y)
{
    if (m == 2)
        return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 29 : 28;
    return (m == 4 || m == 6 || m == 9 || m == 11) ? 30 : 31;
}

inline int GetStartDay(const int &m, const int &y)
{
    tm t = {0};
    t.tm_year = y - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = 1;
    mktime(&t);
    return (t.tm_wday + 6) % 7;
}

inline bool DrawCalendar(Vector2 mousepos, int &selDay, int &month, int &year, Rectangle &Calendar, bool &isOpenCalendar)
{
    bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool change = false;
    static bool Year = false;
    static int s_genCal = 0;
    if (s_genCal != g_resetGen)
    {
        s_genCal = g_resetGen;
        Year = false;
    }
    Rectangle btnCalendar = {
        Calendar.x + 60,
        Calendar.y + 50,
        100,
        25,
    };

    Rectangle Pattern = {Calendar.x, Calendar.y + 30.0f, 250.0f, 240.0f};
    DrawRectangle(Calendar.x, Calendar.y + 30, 250, 240, RAYWHITE);
    DrawRectangleLines(Calendar.x, Calendar.y + 30, 250, 240, DARKGRAY);
    DrawRectangle(btnCalendar.x, btnCalendar.y, btnCalendar.width, btnCalendar.height, RAYWHITE);

    if ((!CheckCollisionPointRec(mousepos, Pattern) && !CheckCollisionPointRec(mousepos, Calendar)) && clicked)
    {
        Year = false;
        isOpenCalendar = false;
    }

    if (CheckCollisionPointRec(mousepos, btnCalendar) && clicked)
    {
        Year = !Year;
    }
    if (Year)
    {
        DrawTextEx(myFont, TextFormat("Năm %d", year), {Calendar.x + 85, Calendar.y + 50}, 18, 1, BLACK);
        static int yearOffset = 0;
        Rectangle btnPrevYear = {Calendar.x + 10, Calendar.y + 50, 30, 22};
        DrawRectangleRec(btnPrevYear, WHITE);
        DrawTextEx(myFont, "<<", {btnPrevYear.x + 8, btnPrevYear.y + 3}, 16, 1, BLACK);
        if (clicked && CheckCollisionPointRec(mousepos, btnPrevYear))
        {
            yearOffset -= 12;
        }

        Rectangle btnNextYear = {Calendar.x + 210, Calendar.y + 50, 30, 22};
        DrawRectangleRec(btnNextYear, WHITE);
        DrawTextEx(myFont, ">>", {btnNextYear.x + 8, btnNextYear.y + 3}, 16, 1, BLACK);
        if (clicked && CheckCollisionPointRec(mousepos, btnNextYear))
        {
            yearOffset += 12;
        }

        int startDisplayYear = year - 5 + yearOffset;

        for (int i = 0; i < 12; i++)
        {
            int col = i % 4;
            int row = i / 4;
            int displayYear = startDisplayYear + i;

            Rectangle cellYear = {Calendar.x + 15 + col * 55, Calendar.y + 90 + row * 45, 50, 30};

            if (displayYear == year)
                DrawRectangleRec(cellYear, SKYBLUE);
            else if (CheckCollisionPointRec(mousepos, cellYear))
                DrawRectangleRec(cellYear, LIGHTGRAY);

            DrawTextEx(myFont, TextFormat("%d", displayYear), {cellYear.x + 5, cellYear.y + 8}, 16, 1, BLACK);

            if (clicked && CheckCollisionPointRec(mousepos, cellYear))
            {
                year = displayYear;
                Year = false;
                yearOffset = 0;
                change = true;
            }
        }
    }
    else
    {
        DrawTextEx(myFont, TextFormat("Tháng %d / %d", month, year), {Calendar.x + 45, Calendar.y + 50}, 18, 1, BLACK);
        Rectangle btnPrev = {Calendar.x + 10, Calendar.y + 50, 30, 22};
        DrawRectangleRec(btnPrev, WHITE);
        DrawTextEx(myFont, "<", {btnPrev.x + 10, btnPrev.y + 3}, 16, 1, BLACK);
        if (clicked && CheckCollisionPointRec(mousepos, btnPrev))
        {
            if (--month < 1)
            {
                month = 12;
                year--;
            }
        }

        Rectangle btnNext = {Calendar.x + 210, Calendar.y + 50, 30, 22};
        DrawRectangleRec(btnNext, WHITE);
        DrawTextEx(myFont, ">", {btnNext.x + 10, btnNext.y + 3}, 16, 1, BLACK);
        if (clicked && CheckCollisionPointRec(mousepos, btnNext))
        {
            if (++month > 12)
            {
                month = 1;
                year++;
            }
        }

        const char *days[] = {"T2", "T3", "T4", "T5", "T6", "T7", "CN"};
        for (int i = 0; i < 7; i++)
        {
            DrawTextEx(myFont, days[i], {Calendar.x + 12 + i * 34, Calendar.y + 80}, 14, 1, DARKGRAY);
        }

        int startOffset = GetStartDay(month, year);
        int totalDays = GetDaysInMonth(month, year);

        for (int d = 1; d <= totalDays; d++)
        {
            int idx = d - 1 + startOffset;
            int col = idx % 7;
            int row = idx / 7;

            Rectangle cell = {Calendar.x + 8 + col * 34, Calendar.y + 100 + row * 28, 30, 24};

            if (d == selDay)
                DrawRectangleRec(cell, SKYBLUE);
            else if (CheckCollisionPointRec(mousepos, cell))
                DrawRectangleRec(cell, LIGHTGRAY);

            DrawTextEx(myFont, TextFormat("%d", d), {cell.x + (d < 10 ? 10 : 6), cell.y + 4}, 14, 1, BLACK);

            if (clicked && CheckCollisionPointRec(mousepos, cell))
            {
                change = true;
                selDay = d;
                isOpenCalendar = false;
            }
        }
    }
    return change;
}

inline int CodepointToUTF8(int codepoint, char *out)
{
    if (codepoint <= 0x7F)
    {
        out[0] = (char)codepoint;
        return 1;
    }
    else if (codepoint <= 0x7FF)
    {
        out[0] = (char)(0xC0 | (codepoint >> 6));
        out[1] = (char)(0x80 | (codepoint & 0x3F));
        return 2;
    }
    else if (codepoint <= 0xFFFF)
    {
        out[0] = (char)(0xE0 | (codepoint >> 12));
        out[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
        out[2] = (char)(0x80 | (codepoint & 0x3F));
        return 3;
    }
    return 0;
}

inline int RemoveLastUTF8Char(char *str, int len)
{
    if (len <= 0)
        return 0;
    int i = len - 1;
    while (i > 0 && (str[i] & 0xC0) == 0x80)
        i--;
    str[i] = '\0';
    return i;
}

inline void TypingKeys(char *Input, int &letterCount, int maxLen = 49)
{
    int bsCount = 0;
    int k = GetKeyPressed();
    while (k > 0)
    {
        if (k == KEY_BACKSPACE)
            bsCount++;
        k = GetKeyPressed();
    }
    if (IsKeyPressedRepeat(KEY_BACKSPACE))
        bsCount++;

    for (int i = 0; i < bsCount; i++)
        letterCount = RemoveLastUTF8Char(Input, letterCount);

    int key = GetCharPressed();
    while (key > 0)
    {
        if (key >= 32)
        {
            char utf8[4] = {};
            int bytes = CodepointToUTF8(key, utf8);
            if (letterCount + bytes < maxLen)
            {
                for (int b = 0; b < bytes; b++)
                    Input[letterCount + b] = utf8[b];
                letterCount += bytes;
                Input[letterCount] = '\0';
            }
        }
        key = GetCharPressed();
    }
}

inline void TypingNumber(char *Input, int &letterCount, int maxLen = 9)
{
    int bsCount = 0;
    int k = GetKeyPressed();
    while (k > 0)
    {
        if (k == KEY_BACKSPACE)
            bsCount++;
        k = GetKeyPressed();
    }
    if (IsKeyPressedRepeat(KEY_BACKSPACE))
        bsCount++;

    for (int i = 0; i < bsCount; i++)
        letterCount = RemoveLastUTF8Char(Input, letterCount);

    int key = GetCharPressed();
    while (key > 0)
    {
        if ((key >= '0' && key <= '9') || key == '.')
        {
            if (key == '.' && strchr(Input, '.') != nullptr)
            {
                key = GetCharPressed();
                continue;
            }
            if (letterCount < maxLen)
            {
                Input[letterCount] = (char)key;
                letterCount++;
                Input[letterCount] = '\0';
            }
        }
        key = GetCharPressed();
    }
}

inline void Typing(bool &isActive, char *Input, int &letterCount, Vector2 &mousePos, Rectangle vung_go)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, vung_go))
            isActive = true;
        else
            isActive = false;
    }

    if (isActive)
    {
        TypingKeys(Input, letterCount, 49);
    }
}

inline string ToLower(string s)
{
    for (size_t i = 0; i < s.size(); i++)
        s[i] = tolower((unsigned char)s[i]);
    return s;
}

inline bool CheckName(const string &input, const string &name)
{
    if (input.empty())
        return true;
    string trimmed = input;
    size_t start = trimmed.find_first_not_of(" \t");
    size_t end = trimmed.find_last_not_of(" \t");
    if (start == string::npos)
        return true;
    trimmed = trimmed.substr(start, end - start + 1);
    return ToLower(name).find(ToLower(trimmed)) != string::npos;
}

inline bool CheckEmployee(Employee *emp, const string &maCV, const string &maPB, const string &keyword)
{
    if (!emp)
        return false;
    if (!maCV.empty() && emp->get_MaChucVu() != maCV)
        return false;
    if (!maPB.empty() && emp->get_MaPhongBan() != maPB)
        return false;
    if (keyword.empty())
        return true;
    string trimmed = keyword;
    size_t start = trimmed.find_first_not_of(" \t");
    if (start == string::npos)
        return true;
    size_t end = trimmed.find_last_not_of(" \t");
    trimmed = trimmed.substr(start, end - start + 1);
    string kwLower = ToLower(trimmed);
    if (ToLower(emp->get_name()).find(kwLower) == string::npos &&
        ToLower(emp->get_mnv()).find(kwLower) == string::npos)
        return false;
    return true;
}

inline void XuLyCombo(Rectangle combo, bool &isOpen, int &selected, int count,
                      Vector2 mousePos, bool Clicked)
{
    if (!Clicked)
        return;

    if (isOpen)
    {
        bool clickedInsideList = false;
        for (int i = 0; i < count; i++)
        {
            Rectangle itemRect = {combo.x, combo.y + combo.height + (i * combo.height), combo.width, combo.height};
            if (CheckCollisionPointRec(mousePos, itemRect))
            {
                selected = i;
                isOpen = false;
                clickedInsideList = true;
                break;
            }
        }
        isOpen = false;
        if (!clickedInsideList && !CheckCollisionPointRec(mousePos, combo))
        {
            isOpen = false;
        }
    }
    else if (CheckCollisionPointRec(mousePos, combo))
    {
        isOpen = true;
    }
}

inline void VeCombo(Rectangle combo, int selected, string items[], int count)
{
    DrawRectangleRounded(combo, 0.2f, 10, WHITE);
    if (selected >= 0 && selected < count)
    {
        DrawTextEx(myFont, items[selected].c_str(), {combo.x + 5, combo.y + 5}, 18, 1, DARKGRAY);
    }
    Vector2 p1 = {combo.x + combo.width - 15, combo.y + 12};
    Vector2 p2 = {combo.x + combo.width - 5, combo.y + 12};
    Vector2 p3 = {combo.x + combo.width - 10, combo.y + 20};
    DrawTriangle(p1, p3, p2, DARKGRAY);
}

inline void VeDanhSachCombo(Rectangle combo, bool isOpen, string items[], int count, Vector2 mousePos, int wordsize)
{
    Vector2 p1 = {combo.x + combo.width - 15, combo.y + 12};
    Vector2 p2 = {combo.x + combo.width - 5, combo.y + 12};
    Vector2 p3 = {combo.x + combo.width - 10, combo.y + 20};
    bool isHoverCombo = CheckCollisionPointRec(mousePos, combo);
    Color borderColor = Color{205, 215, 230, 255};
    if (isOpen)
    {
        borderColor = Color{98, 70, 234, 255};
    }
    else if (isHoverCombo)
    {
        borderColor = Color{140, 165, 210, 255};
    }

    DrawRectangleRounded(combo, 0.35f, 8, WHITE);
    DrawRectangleRoundedLinesEx(combo, 0.35f, 8, 1.5f, borderColor);
    DrawTriangle(p1, p3, p2, DARKGRAY);
    if (!isOpen || count <= 0)
        return;

    float itemHeight = combo.height;
    float startY = combo.y + combo.height + 3.0f;
    float totalHeight = count * itemHeight;

    Rectangle menuBox = {combo.x, startY, combo.width, totalHeight};

    DrawRectangleRounded({menuBox.x + 2, menuBox.y + 3, menuBox.width, menuBox.height}, 0.15f, 6, Fade(BLACK, 0.08f));
    DrawRectangleRounded(menuBox, 0.15f, 6, WHITE);
    DrawRectangleRoundedLinesEx(menuBox, 0.15f, 6, 1.2f, Color{210, 218, 230, 255});

    for (int i = 0; i < count; i++)
    {
        Rectangle itemRect = {combo.x, startY + (i * itemHeight), combo.width, itemHeight};
        bool isHover = CheckCollisionPointRec(mousePos, itemRect);

        if (isHover)
        {
            DrawRectangleRounded(itemRect, 0.12f, 4, Color{242, 240, 255, 255});
        }

        Color textColor = isHover ? Color{98, 70, 234, 255} : Color{50, 50, 60, 255};
        DrawTextEx(myFont, items[i].c_str(), {itemRect.x + 14, itemRect.y + 6}, wordsize, 1, textColor);

        if (i < count - 1)
        {
            DrawLine(itemRect.x + 8, itemRect.y + itemHeight, itemRect.x + itemRect.width - 8, itemRect.y + itemHeight, Color{240, 243, 248, 255});
        }
    }
}

inline int TimIndex(string ds[], int n, const string &key)
{
    for (int i = 0; i < n; i++)
    {
        if (ds[i] == key)
            return i;
    }
    return -1;
}

inline void VeOInput(Rectangle r, const char *input, bool active, bool readOnly, const char *placeholder)
{
    Color nen = readOnly ? Color{241, 244, 249, 255} : WHITE;
    Color vien = readOnly ? nen : (active ? Color{98, 70, 234, 255} : Color{225, 230, 240, 255});
    DrawRectangleRounded(r, 0.25f, 8, nen);
    DrawRectangleRoundedLinesEx(r, 0.25f, 8, 1.5f, vien);
    if (input[0] == '\0')
        DrawTextEx(myFont, placeholder, {r.x + 16, r.y + 11}, 24, 1, Color{150, 158, 170, 255});
    else
        DrawTextEx(myFont, input, {r.x + 16, r.y + 11}, 24, 1, Color{31, 41, 55, 255});
    if (active && ((int)(GetTime() * 2) % 2 == 0))
    {
        float w = MeasureTextEx(myFont, input, 24, 1).x;
        DrawRectangle(r.x + 18 + w, r.y + 10, 2, 27, Color{98, 70, 234, 255});
    }
}

inline void VeODate(Rectangle r, const char *text, bool open, Vector2 mousePos, const char *placeholder)
{
    bool hover = CheckCollisionPointRec(mousePos, r);
    Color vien = open ? Color{98, 70, 234, 255} : (hover ? Color{140, 165, 210, 255} : Color{225, 230, 240, 255});
    DrawRectangleRounded(r, 0.25f, 8, WHITE);
    DrawRectangleRoundedLinesEx(r, 0.25f, 8, 1.5f, vien);
    if (text[0] == '\0')
        DrawTextEx(myFont, placeholder, {r.x + 16, r.y + 11}, 24, 1, Color{107, 114, 128, 255});
    else
        DrawTextEx(myFont, text, {r.x + 16, r.y + 11}, 24, 1, Color{31, 41, 55, 255});
    float ix = r.x + r.width - 34, iy = r.y + 14;
    DrawRectangleLinesEx({ix, iy + 2, 18, 17}, 1.8f, DARKGRAY);
    DrawLineEx({ix, iy + 8}, {ix + 18, iy + 8}, 1.8f, DARKGRAY);
    DrawLineEx({ix + 5, iy}, {ix + 5, iy + 4}, 1.8f, DARKGRAY);
    DrawLineEx({ix + 13, iy}, {ix + 13, iy + 4}, 1.8f, DARKGRAY);
}
