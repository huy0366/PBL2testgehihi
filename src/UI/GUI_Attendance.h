#pragma once
#include "GUI_Common.h"

void Draw_Screen_CC_FullTime(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_CC_PartTime(Vector2 mousePos, bool Clicked, QLNV *QL);
void VeModalLichNhanVien(Vector2 mousePos, bool Clicked, QLNV *QL, bool &isOpenModalLich, Employee *&selectedLichEmp, int curMonth, int curYear, bool openedLichThisFrame = false);
void Draw_Screen_ChamCong(QLNV *QL);

void Draw_Screen_ChamCong(QLNV *QL)
{
    // =============== LẤY INPUT ===============
    Vector2 mousePos = GetMousePosition();
    bool Clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    // =============== BANNER TIÊU ĐỀ TRÊN CÙNG (giống Draw_Screen_Salary) ===============
    static Texture2D iconCC;
    static bool isIconLoaded = false;
    if (!isIconLoaded)
    {
        iconCC = LoadTexture("photo/icon/Asset.png");
        isIconLoaded = true;
    }
    Vector2 pIcon = {370.0f, 45.0f};
    DrawTextureEx(iconCC, pIcon, 0.0f, 0.33f, WHITE);
    DrawTextEx(myFont, "Quản Lý Chấm Công", {pIcon.x + 100, pIcon.y}, 45, 1, WHITE);
    DrawTextEx(myFont, "Điểm danh, theo dõi ngày công và đồng bộ bảng lương", {pIcon.x + 100, pIcon.y + 50}, 30, 1, WHITE);

    // =============== 2 TAB: FULLTIME / PARTTIME (giống Draw_Screen_BangLuong) ===============
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_menuGen);
    s_gen = g_menuGen;
    static bool isOpenFT = true;
    if (doReset)
        isOpenFT = true;
    static bool isOpenPT = false;
    if (doReset)
        isOpenPT = false;

    Rectangle panelTab = {330, 160, 1450.0f, 95.0f};
    DrawRectangleRounded({panelTab.x + 3, panelTab.y + 4, panelTab.width, panelTab.height}, 0.04f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelTab, 0.04f, 10, Color{242, 245, 252, 255});
    DrawRectangleRoundedLinesEx(panelTab, 0.04f, 10, 1.5f, Color{218, 226, 242, 255});

    float tabMargin = 10.0f;
    float tabGap = 10.0f;
    float tabW = (panelTab.width - 2 * tabMargin - tabGap) / 2.0f;
    float tabH = 75.0f;
    float tabY = panelTab.y + tabMargin;

    Rectangle TabFT = {panelTab.x + tabMargin, tabY, tabW, tabH};
    Rectangle TabPT = {panelTab.x + tabMargin + tabW + tabGap, tabY, tabW, tabH};

    bool hoverFT = CheckCollisionPointRec(mousePos, TabFT);
    bool hoverPT = CheckCollisionPointRec(mousePos, TabPT);

    Color cActiveBg = Color{55, 100, 235, 255};
    Color cActiveBorder = Color{40, 80, 210, 255};
    Color cInactiveBg = Color{230, 236, 247, 255};
    Color cHoverBg = Color{218, 226, 242, 255};
    Color cInactiveBorder = Color{200, 212, 230, 255};

    Color CTabFT = isOpenFT ? cActiveBg : (hoverFT ? cHoverBg : cInactiveBg);
    Color borderFT = isOpenFT ? cActiveBorder : cInactiveBorder;
    Color textFT = isOpenFT ? WHITE : Color{55, 65, 85, 255};

    Color CTabPT = isOpenPT ? cActiveBg : (hoverPT ? cHoverBg : cInactiveBg);
    Color borderPT = isOpenPT ? cActiveBorder : cInactiveBorder;
    Color textPT = isOpenPT ? WHITE : Color{55, 65, 85, 255};

    // Vẽ Tab FullTime
    if (isOpenFT)
        DrawRectangleRounded({TabFT.x + 2, TabFT.y + 3, TabFT.width, TabFT.height}, 0.25f, 8, Fade(BLACK, 0.12f));
    DrawRectangleRounded(TabFT, 0.25f, 8, CTabFT);
    DrawRectangleRoundedLinesEx(TabFT, 0.25f, 8, 1.5f, borderFT);
    float twFT = MeasureTextEx(myFont, "Full Time", 36, 1).x;
    DrawTextEx(myFont, "Full Time", {TabFT.x + (TabFT.width - twFT) / 2.0f, TabFT.y + (TabFT.height - 36) / 2.0f}, 36, 1, textFT);

    // Vẽ Tab PartTime
    if (isOpenPT)
        DrawRectangleRounded({TabPT.x + 2, TabPT.y + 3, TabPT.width, TabPT.height}, 0.25f, 8, Fade(BLACK, 0.12f));
    DrawRectangleRounded(TabPT, 0.25f, 8, CTabPT);
    DrawRectangleRoundedLinesEx(TabPT, 0.25f, 8, 1.5f, borderPT);
    float twPT = MeasureTextEx(myFont, "Part Time", 36, 1).x;
    DrawTextEx(myFont, "Part Time", {TabPT.x + (TabPT.width - twPT) / 2.0f, TabPT.y + (TabPT.height - 36) / 2.0f}, 36, 1, textPT);

    if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabFT))
    {
        if (!isOpenFT)
            g_resetGen++;
        isOpenFT = true;
        isOpenPT = false;
    }
    else if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabPT))
    {
        if (!isOpenPT)
            g_resetGen++;
        isOpenPT = true;
        isOpenFT = false;
    }

    // =============== GỌI HÀM CON TƯƠNG ỨNG TAB ===============
    if (isOpenFT)
    {
        Draw_Screen_CC_FullTime(mousePos, Clicked, QL);
    }
    else if (isOpenPT)
    {
        Draw_Screen_CC_PartTime(mousePos, Clicked, QL);
    }
}

void VeModalLichNhanVien(Vector2 mousePos, bool Clicked, QLNV *QL, bool &isOpenModalLich, Employee *&selectedLichEmp, int curMonth, int curYear, bool openedLichThisFrame)
{
    if (!isOpenModalLich || selectedLichEmp == nullptr)
        return;

    static int viewMonth = curMonth;
    static int viewYear = curYear;
    static Employee *lastViewEmp = nullptr;

    if (openedLichThisFrame || lastViewEmp != selectedLichEmp)
    {
        viewMonth = curMonth;
        viewYear = curYear;
        lastViewEmp = selectedLichEmp;
    }

    // Nền mờ
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));

    // Hộp modal chính
    Rectangle mBox = {(GetScreenWidth() - 940) / 2.0f, (GetScreenHeight() - 740) / 2.0f, 940.0f, 740.0f};
    DrawRectangleRounded({mBox.x + 4, mBox.y + 6, mBox.width, mBox.height}, 0.03f, 8, Fade(BLACK, 0.25f));
    DrawRectangleRounded(mBox, 0.03f, 8, WHITE);
    bool isFT = (selectedLichEmp->get_LoaiNV() == "FullTime");
    DrawRectangleRoundedLinesEx(mBox, 0.03f, 8, 2.0f, isFT ? Color{55, 100, 235, 255} : Color{130, 60, 210, 255});

    // Các nút chuyển tháng và nút đóng
    Rectangle btnPrevM = {mBox.x + 575, mBox.y + 16, 36, 36};
    Rectangle boxM = {mBox.x + 617, mBox.y + 16, 210, 36};
    Rectangle btnNextM = {mBox.x + 833, mBox.y + 16, 36, 36};
    Rectangle btnCloseX = {mBox.x + mBox.width - 48, mBox.y + 16, 36, 36};

    bool hoverPrevM = CheckCollisionPointRec(mousePos, btnPrevM);
    bool hoverNextM = CheckCollisionPointRec(mousePos, btnNextM);
    bool hoverBoxM = CheckCollisionPointRec(mousePos, boxM);
    bool hoverCloseX = CheckCollisionPointRec(mousePos, btnCloseX);

    // Xử lý chuyển tháng (Click chuột hoặc phím mũi tên)
    if ((Clicked && hoverPrevM) || IsKeyPressed(KEY_LEFT))
    {
        viewMonth--;
        if (viewMonth < 1)
        {
            viewMonth = 12;
            viewYear--;
        }
    }
    else if ((Clicked && hoverNextM) || IsKeyPressed(KEY_RIGHT))
    {
        viewMonth++;
        if (viewMonth > 12)
        {
            viewMonth = 1;
            viewYear++;
        }
    }
    else if (Clicked && hoverBoxM && (viewMonth != curMonth || viewYear != curYear))
    {
        viewMonth = curMonth;
        viewYear = curYear;
    }
    else if ((Clicked && hoverCloseX) || IsKeyPressed(KEY_ESCAPE))
    {
        isOpenModalLich = false;
        return;
    }

    // Tiêu đề modal & Subtitle
    string tLich = "LỊCH CHẤM CÔNG & NGÀY CÔNG";
    DrawTextEx(myFont, tLich.c_str(), {mBox.x + 35, mBox.y + 18}, 24, 1, isFT ? Color{25, 55, 160, 255} : Color{100, 40, 180, 255});

    string subInfo = selectedLichEmp->get_mnv() + " - " + selectedLichEmp->get_name() +
                     " (" + (selectedLichEmp->get_PhongBan() ? selectedLichEmp->get_PhongBan()->get_TenPhongBan() : "") +
                     " | " + (selectedLichEmp->get_ViTri() ? selectedLichEmp->get_ViTri()->get_TenVTVL() : "") +
                     " | " + selectedLichEmp->get_LoaiNV() + ")";
    DrawTextEx(myFont, subInfo.c_str(), {mBox.x + 35, mBox.y + 50}, 19, 1, DARKGRAY);

    // Vẽ nút Lùi tháng [<]
    DrawRectangleRounded(btnPrevM, 0.3f, 4, hoverPrevM ? (isFT ? Color{225, 238, 255, 255} : Color{245, 235, 255, 255}) : Color{245, 247, 250, 255});
    DrawRectangleRoundedLinesEx(btnPrevM, 0.3f, 4, 1.2f, hoverPrevM ? (isFT ? Color{55, 100, 235, 255} : Color{130, 60, 210, 255}) : LIGHTGRAY);
    DrawTextEx(myFont, "<", {btnPrevM.x + 12, btnPrevM.y + 5}, 22, 1, hoverPrevM ? (isFT ? Color{25, 55, 160, 255} : Color{100, 40, 180, 255}) : DARKGRAY);

    // Vẽ Ô Tháng / Năm
    DrawRectangleRounded(boxM, 0.3f, 4, isFT ? (hoverBoxM ? Color{232, 242, 255, 255} : Color{242, 246, 255, 255}) : (hoverBoxM ? Color{248, 238, 255, 255} : Color{252, 245, 255, 255}));
    DrawRectangleRoundedLinesEx(boxM, 0.3f, 4, 1.5f, isFT ? Color{55, 100, 235, 255} : Color{130, 60, 210, 255});
    string strThang = "Tháng " + to_string(viewMonth) + " / " + to_string(viewYear);
    float wThang = MeasureTextEx(myFont, strThang.c_str(), 20, 1).x;
    DrawTextEx(myFont, strThang.c_str(), {boxM.x + (boxM.width - wThang) / 2.0f, boxM.y + 7}, 20, 1, isFT ? Color{25, 55, 160, 255} : Color{100, 40, 180, 255});

    // Vẽ nút Tiến tháng [>]
    DrawRectangleRounded(btnNextM, 0.3f, 4, hoverNextM ? (isFT ? Color{225, 238, 255, 255} : Color{245, 235, 255, 255}) : Color{245, 247, 250, 255});
    DrawRectangleRoundedLinesEx(btnNextM, 0.3f, 4, 1.2f, hoverNextM ? (isFT ? Color{55, 100, 235, 255} : Color{130, 60, 210, 255}) : LIGHTGRAY);
    DrawTextEx(myFont, ">", {btnNextM.x + 12, btnNextM.y + 5}, 22, 1, hoverNextM ? (isFT ? Color{25, 55, 160, 255} : Color{100, 40, 180, 255}) : DARKGRAY);

    // Vẽ nút Đóng [X]
    DrawRectangleRounded(btnCloseX, 0.3f, 4, hoverCloseX ? Color{255, 230, 230, 255} : Color{245, 245, 245, 255});
    DrawRectangleRoundedLinesEx(btnCloseX, 0.3f, 4, 1.0f, hoverCloseX ? RED : LIGHTGRAY);
    DrawTextEx(myFont, "X", {btnCloseX.x + 11, btnCloseX.y + 7}, 18, 1, hoverCloseX ? RED : DARKGRAY);

    DrawLine(mBox.x + 30, mBox.y + 85, mBox.x + mBox.width - 30, mBox.y + 85, Color{220, 225, 235, 255});

    // TÍNH TOÁN DỮ LIỆU CHẤM CÔNG THEO viewMonth & viewYear
    int cntDu = 0, cntNua = 0, cntPhep = 0, cntKP = 0, cntOT = 0;
    float sumGioChuan = 0.0f;
    float sumGioOT = 0.0f;
    string empMnv = selectedLichEmp->get_mnv();

    for (Node<ChamCong> *c = QL->get_DB()->get_ListCC()->get_header()->Next; c != nullptr; c = c->Next)
    {
        if (c->Data && c->Data->get_NV() && c->Data->get_NV()->get_mnv() == empMnv &&
            c->Data->get_Ngay().get_month() == viewMonth && c->Data->get_Ngay().get_year() == viewYear)
        {
            int tt = c->Data->get_TrangThai();
            if (tt == 1)
            {
                cntDu++;
                sumGioChuan += (float)c->Data->get_SoGio();
            }
            else if (tt == 2)
            {
                cntNua++;
                sumGioChuan += (float)c->Data->get_SoGio();
            }
            else if (tt == 3)
            {
                cntPhep++;
            }
            else if (tt == 4)
            {
                cntKP++;
            }
            else if (tt == 5)
            {
                cntOT++;
                sumGioOT += (float)c->Data->get_SoGio();
            }
        }
    }

    long long empLcb = QL->get_LuongCoBan(selectedLichEmp);
    if (empLcb < 0)
        empLcb = 0;
    long long tienOTUocTinh = 0;
    if (isFT)
        tienOTUocTinh = (long long)(sumGioOT * (empLcb / 208.0) * 1.5);
    else
        tienOTUocTinh = (long long)(sumGioOT * empLcb * 1.5);

    // 4 Thẻ KPI tóm tắt tháng của nhân viên
    float kpiY = mBox.y + 95;
    float kW = 205;
    float kH = 55;
    float kGap = 15;

    // Thẻ 1: Tổng công / ca
    Rectangle k1 = {mBox.x + 35, kpiY, kW, kH};
    DrawRectangleRounded(k1, 0.2f, 4, Color{240, 252, 244, 255});
    DrawRectangleRoundedLinesEx(k1, 0.2f, 4, 1.0f, Color{40, 170, 80, 255});
    DrawTextEx(myFont, isFT ? "Tổng ngày công" : "Tổng ca làm việc", {k1.x + 10, k1.y + 6}, 16, 1, Color{20, 120, 50, 255});
    double tongNgayCongFT = (double)cntDu * 1.0 + (double)cntNua * 0.5 + (double)cntOT * 1.0;
    ostringstream ossNCVal;
    if (tongNgayCongFT == (int)tongNgayCongFT) ossNCVal << (int)tongNgayCongFT;
    else ossNCVal << fixed << setprecision(1) << tongNgayCongFT;
    string sCong = isFT ? (ossNCVal.str() + " công (" + to_string(cntDu) + " đủ, " + to_string(cntNua) + " nửa)") : (to_string(cntDu + cntNua) + " ca (" + to_string((int)sumGioChuan) + "h)");
    DrawTextEx(myFont, sCong.c_str(), {k1.x + 10, k1.y + 26}, 20, 1, Color{10, 100, 40, 255});

    // Thẻ 2: Nghỉ phép
    Rectangle k2 = {k1.x + kW + kGap, kpiY, kW, kH};
    DrawRectangleRounded(k2, 0.2f, 4, Color{238, 246, 255, 255});
    DrawRectangleRoundedLinesEx(k2, 0.2f, 4, 1.0f, Color{50, 130, 240, 255});
    DrawTextEx(myFont, "Nghỉ phép (P)", {k2.x + 10, k2.y + 6}, 16, 1, Color{30, 90, 200, 255});
    DrawTextEx(myFont, (to_string(cntPhep) + " ngày").c_str(), {k2.x + 10, k2.y + 26}, 20, 1, Color{20, 80, 190, 255});

    // Thẻ 3: Vắng không phép
    Rectangle k3 = {k2.x + kW + kGap, kpiY, kW, kH};
    DrawRectangleRounded(k3, 0.2f, 4, Color{255, 240, 240, 255});
    DrawRectangleRoundedLinesEx(k3, 0.2f, 4, 1.0f, Color{230, 60, 60, 255});
    DrawTextEx(myFont, "Không phép (KP)", {k3.x + 10, k3.y + 6}, 16, 1, Color{200, 40, 40, 255});
    DrawTextEx(myFont, (to_string(cntKP) + " ngày").c_str(), {k3.x + 10, k3.y + 26}, 20, 1, Color{180, 20, 20, 255});

    // Thẻ 4: Tăng ca / OT
    Rectangle k4 = {k3.x + kW + kGap, kpiY, kW, kH};
    DrawRectangleRounded(k4, 0.2f, 4, Color{250, 240, 255, 255});
    DrawRectangleRoundedLinesEx(k4, 0.2f, 4, 1.0f, Color{180, 70, 230, 255});
    DrawTextEx(myFont, "Giờ OT (Tăng ca)", {k4.x + 10, k4.y + 6}, 16, 1, Color{130, 40, 180, 255});
    ostringstream ossOT;
    ossOT << fixed << setprecision(1) << sumGioOT << " giờ (" << FormatSoTien(tienOTUocTinh) << " đ)";
    DrawTextEx(myFont, ossOT.str().c_str(), {k4.x + 10, k4.y + 26}, 18, 1, Color{120, 30, 170, 255});

    // LƯỚI LỊCH THÁNG (Calendar Grid)
    float gridY = kpiY + kH + 18;
    string thuNames[] = {"Thứ 2", "Thứ 3", "Thứ 4", "Thứ 5", "Thứ 6", "Thứ 7", "Chủ Nhật"};
    float cellW = 118.0f;
    float cellH = 68.0f;
    float cellGap = 6.0f;
    float gridStartX = mBox.x + 35.0f;

    for (int i = 0; i < 7; i++)
    {
        Rectangle rH = {gridStartX + i * (cellW + cellGap), gridY, cellW, 28};
        Color cBg = (i == 6) ? Color{255, 240, 240, 255} : Color{235, 242, 255, 255};
        DrawRectangleRounded(rH, 0.2f, 4, cBg);
        float twT = MeasureTextEx(myFont, thuNames[i].c_str(), 18, 1).x;
        DrawTextEx(myFont, thuNames[i].c_str(), {rH.x + (cellW - twT) / 2.0f, rH.y + 5}, 18, 1, (i == 6) ? Color{210, 40, 40, 255} : Color{40, 80, 200, 255});
    }

    int startDayOfWeek = GetStartDay(viewMonth, viewYear);
    int totalDaysInMonth = GetDaysInMonth(viewMonth, viewYear);
    float cellsStartY = gridY + 34;
    string hoverInfo = "";

    for (int d = 1; d <= totalDaysInMonth; d++)
    {
        int slot = (d - 1 + startDayOfWeek);
        int col = slot % 7;
        int row = slot / 7;

        Rectangle cellR = {gridStartX + col * (cellW + cellGap), cellsStartY + row * (cellH + cellGap), cellW, cellH};
        bool isCellHover = CheckCollisionPointRec(mousePos, cellR);

        ChamCong *ccDay = QL->get_DB()->FindCC(empMnv, Date(d, viewMonth, viewYear));
        Color bgCell = WHITE;
        Color borderCell = Color{220, 225, 235, 255};
        string labelTT = "";
        Color textTT = DARKGRAY;

        if (ccDay == nullptr)
        {
            if (col == 6)
            {
                bgCell = Color{250, 248, 250, 255};
                labelTT = "- (CN)";
                textTT = LIGHTGRAY;
            }
            else
            {
                bgCell = WHITE;
                labelTT = "Chưa chấm";
                textTT = GRAY;
            }
        }
        else
        {
            int tt = ccDay->get_TrangThai();
            if (tt == 1)
            {
                bgCell = Color{235, 252, 240, 255};
                borderCell = Color{40, 170, 80, 255};
                labelTT = isFT ? "Đủ công" : ("Có ca (" + to_string((int)ccDay->get_SoGio()) + "h)");
                textTT = Color{20, 130, 50, 255};
            }
            else if (tt == 2)
            {
                bgCell = Color{255, 248, 235, 255};
                borderCell = Color{240, 150, 40, 255};
                labelTT = isFT ? "Nửa công" : ("Nửa ca (" + to_string((int)ccDay->get_SoGio()) + "h)");
                textTT = Color{200, 100, 10, 255};
            }
            else if (tt == 3)
            {
                bgCell = Color{238, 246, 255, 255};
                borderCell = Color{50, 130, 240, 255};
                labelTT = "Có phép";
                textTT = Color{30, 90, 210, 255};
            }
            else if (tt == 4)
            {
                bgCell = Color{255, 240, 240, 255};
                borderCell = Color{230, 60, 60, 255};
                labelTT = "Không phép";
                textTT = Color{200, 30, 30, 255};
            }
            else if (tt == 5)
            {
                bgCell = Color{250, 240, 255, 255};
                borderCell = Color{180, 70, 230, 255};
                ostringstream ossG;
                ossG << "OT " << ccDay->get_SoGio() << "h";
                labelTT = ossG.str();
                textTT = Color{130, 30, 180, 255};
            }
        }

        if (isCellHover)
        {
            borderCell = Color{40, 80, 220, 255};
            ostringstream ossH;
            ossH << "Ngày " << d << "/" << viewMonth << "/" << viewYear << ": " << labelTT;
            if (ccDay && !ccDay->get_GhiChu().empty())
                ossH << " | Ghi chú: " << ccDay->get_GhiChu();
            else if (ccDay == nullptr && col == 6)
                ossH << " (Chủ Nhật - Ngày nghỉ định kỳ)";
            hoverInfo = ossH.str();
        }

        DrawRectangleRounded(cellR, 0.15f, 4, bgCell);
        DrawRectangleRoundedLinesEx(cellR, 0.15f, 4, 1.2f, borderCell);
        DrawTextEx(myFont, to_string(d).c_str(), {cellR.x + 8, cellR.y + 6}, 18, 1, BLACK);
        float wL = MeasureTextEx(myFont, labelTT.c_str(), 16, 1).x;
        DrawTextEx(myFont, labelTT.c_str(), {cellR.x + (cellW - wL) / 2.0f, cellR.y + 36}, 16, 1, textTT);
    }

    // Dòng tooltip khi hover
    float bottomY = mBox.y + mBox.height - 75;
    DrawLine(mBox.x + 30, bottomY - 10, mBox.x + mBox.width - 30, bottomY - 10, Color{230, 235, 245, 255});
    if (!hoverInfo.empty())
        DrawTextEx(myFont, hoverInfo.c_str(), {mBox.x + 35, bottomY + 5}, 20, 1, Color{20, 60, 180, 255});
    else
        DrawTextEx(myFont, "Rê chuột vào từng ngày để xem chi tiết | Dùng nút < > để chuyển tháng xem", {mBox.x + 35, bottomY + 5}, 18, 1, GRAY);

    // Nút Đóng
    Rectangle btnDongModal = {mBox.x + mBox.width - 160, bottomY, 125, 42};
    bool hoverDong = CheckCollisionPointRec(mousePos, btnDongModal);
    DrawRectangleRounded(btnDongModal, 0.25f, 6, hoverDong ? Color{215, 60, 60, 255} : Color{235, 70, 70, 255});
    DrawTextEx(myFont, "Đóng", {btnDongModal.x + 36, btnDongModal.y + 8}, 22, 1, WHITE);
    if (Clicked && hoverDong)
        isOpenModalLich = false;

    // Click ra ngoài modal để đóng
    if (Clicked && !openedLichThisFrame && !CheckCollisionPointRec(mousePos, mBox))
    {
        isOpenModalLich = false;
    }
}

void Draw_Screen_CC_FullTime(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    // ================= 1. TRẠNG THÁI & BIẾN CỤC BỘ =================
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static int curDay = day;
    static int curMonth = month;
    static int curYear = year;
    if (doReset)
    {
        curDay = day;
        curMonth = month;
        curYear = year;
    }
    static bool isOpenMainCalendar = false;
    if (doReset)
        isOpenMainCalendar = false;
    Date dateHienTai(curDay, curMonth, curYear);

    static char searchNV[50] = "";
    if (doReset)
        searchNV[0] = '\0';
    static int letterSearchNV = 0;
    if (doReset)
        letterSearchNV = 0;
    static bool isSearchNVActive = false;
    if (doReset)
        isSearchNVActive = false;

    static float scrollY = 0.0f;
    if (doReset)
        scrollY = 0.0f;
    float scrollSpeed = 30.0f;

    static bool isOpenModal = false;
    if (doReset)
        isOpenModal = false;
    static Employee *selectedEmp = nullptr;
    if (doReset)
        selectedEmp = nullptr;
    static bool isOpenModalLich = false;
    if (doReset)
        isOpenModalLich = false;
    static Employee *selectedLichEmp = nullptr;
    if (doReset)
        selectedLichEmp = nullptr;
    static bool openedThisFrame = false;
    static bool openedLichThisFrame = false;
    static bool openedCalThisFrame = false;
    bool blockBackground = isOpenModal || isOpenModalLich || isOpenMainCalendar;

    // ================= 2. KHUNG NỀN TRẮNG CHÍNH =================
    Rectangle panelBang = {330, 270, 1450.0f, 715.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    // ================= 3. THANH TOOLBAR =================
    // Nút Lịch chọn ngày
    Rectangle btnMainCal = {350, 285, 230, 42};
    DrawRectangleRounded(btnMainCal, 0.3f, 6, isOpenMainCalendar ? Color{230, 240, 255, 255} : Color{245, 247, 250, 255});
    DrawRectangleRoundedLinesEx(btnMainCal, 0.3f, 6, 1.5f, isOpenMainCalendar ? Color{50, 100, 220, 255} : LIGHTGRAY);
    string strMainDate = "Ngày: " + dateHienTai.ToString() + "  v";
    DrawTextEx(myFont, strMainDate.c_str(), {btnMainCal.x + 18, btnMainCal.y + 8}, 22, 1, BLACK);
    if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnMainCal))
    {
        isOpenMainCalendar = !isOpenMainCalendar;
        openedCalThisFrame = true;
    }

    // Ô tìm kiếm NV FullTime
    Rectangle boxSearch = {600, 285, 300, 42};
    DrawRectangleRounded(boxSearch, 0.3f, 6, Color{248, 250, 252, 255});
    DrawRectangleRoundedLinesEx(boxSearch, 0.3f, 6, 1.5f, isSearchNVActive ? Color{50, 100, 220, 255} : LIGHTGRAY);
    if (Clicked && !blockBackground)
        isSearchNVActive = CheckCollisionPointRec(mousePos, boxSearch);
    if (isSearchNVActive && !blockBackground)
        Typing(isSearchNVActive, searchNV, letterSearchNV, mousePos, boxSearch);
    if (searchNV[0] == '\0')
        DrawTextEx(myFont, "Tìm tên hoặc mã NV...", {boxSearch.x + 15, boxSearch.y + 8}, 22, 1, GRAY);
    else
        DrawTextEx(myFont, searchNV, {boxSearch.x + 15, boxSearch.y + 8}, 24, 1, BLACK);
    if (!blockBackground && isSearchNVActive && searchNV[0] != '\0' && ((int)(GetTime() * 2) % 2 == 0))
    {
        Vector2 textSize = MeasureTextEx(myFont, searchNV, 24, 1);
        float cursorX = boxSearch.x + 15 + textSize.x + 2;
        if (cursorX < boxSearch.x + boxSearch.width - 15)
        {
            DrawTextEx(myFont, "_", {cursorX, boxSearch.y + 8}, 24, 1, Color{50, 100, 220, 255});
        }
    }

    // Nút "Điểm danh tất cả Có Mặt" (Full-Time: mặc định 1 công = 8.0 giờ)
    Rectangle btnAllDu = {920, 285, 230, 42};
    DrawRectangleRounded(btnAllDu, 0.3f, 6, Color{34, 150, 80, 255});
    DrawTextEx(myFont, "Điểm danh tất cả", {btnAllDu.x + 28, btnAllDu.y + 8}, 22, 1, WHITE);
    if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnAllDu))
    {
        for (Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next; p != nullptr; p = p->Next)
        {
            if (!p->Data || p->Data->get_LoaiNV() != "FullTime")
                continue;
            ChamCong *cc = QL->get_DB()->FindCC(p->Data->get_mnv(), dateHienTai);
            if (cc)
            {
                cc->set_TrangThai(1);
                cc->set_SoGio(8.0);
            }
            else
            {
                QL->get_DB()->Insert(new ChamCong(p->Data, dateHienTai, 1, 8.0, "Đúng giờ"));
            }
        }
        QL->get_DB()->SaveFileChamCong();
        QL->DongBoChamCong(curMonth, curYear);
        QL->get_DB()->SaveFileEmployee();
        HienThongBao("Đã điểm danh tất cả Full-Time Có Mặt!", false);
    }

    // Nút "Chốt công -> Bảng Lương"
    Rectangle btnChotCong = {1170, 285, 270, 42};
    DrawRectangleRounded(btnChotCong, 0.3f, 6, Color{40, 100, 220, 255});
    DrawTextEx(myFont, "Chốt công vào Bảng Lương", {btnChotCong.x + 16, btnChotCong.y + 8}, 22, 1, WHITE);
    if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnChotCong))
    {
        XuatBangLuongThang(QL, curMonth, curYear);
        HienThongBao("Đã chốt công & xuất file Bảng Lương tháng " + to_string(curMonth) + "/" + to_string(curYear) + "!", false);
    }

    // ================= 4. 4 THẺ THỐNG KÊ KPI FULL-TIME =================
    int demTongNV = 0, demCoMat = 0, demNghiPhep = 0, demVang = 0;
    for (Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next; p != nullptr; p = p->Next)
    {
        if (!p->Data || p->Data->get_LoaiNV() != "FullTime")
            continue;
        demTongNV++;
        ChamCong *cc = QL->get_DB()->FindCC(p->Data->get_mnv(), dateHienTai);
        if (cc)
        {
            int tt = cc->get_TrangThai();
            if (tt == 1 || tt == 2 || tt == 5)
                demCoMat++;
            else if (tt == 3)
                demNghiPhep++;
            else if (tt == 4)
                demVang++;
        }
    }

    float cardY = 345.0f;
    float cardW = 325.0f;
    float cardH = 65.0f;
    float cardGap = 30.0f;

    Rectangle card1 = {360.0f, cardY, cardW, cardH};
    DrawRectangleRounded(card1, 0.15f, 6, WHITE);
    DrawRectangleRoundedLinesEx(card1, 0.15f, 6, 1.5f, DARKGRAY);
    DrawTextEx(myFont, "Tổng FullTime", {card1.x + 15, card1.y + 8}, 20, 1, DARKGRAY);
    DrawTextEx(myFont, to_string(demTongNV).c_str(), {card1.x + 15, card1.y + 32}, 28, 1, BLACK);

    Rectangle card2 = {card1.x + cardW + cardGap, cardY, cardW, cardH};
    DrawRectangleRounded(card2, 0.15f, 6, Color{240, 252, 244, 255});
    DrawRectangleRoundedLinesEx(card2, 0.15f, 6, 1.5f, Color{46, 180, 90, 255});
    DrawTextEx(myFont, "Có mặt", {card2.x + 15, card2.y + 8}, 20, 1, Color{30, 140, 70, 255});
    DrawTextEx(myFont, to_string(demCoMat).c_str(), {card2.x + 15, card2.y + 32}, 28, 1, Color{20, 130, 60, 255});

    Rectangle card3 = {card2.x + cardW + cardGap, cardY, cardW, cardH};
    DrawRectangleRounded(card3, 0.15f, 6, Color{240, 248, 255, 255});
    DrawRectangleRoundedLinesEx(card3, 0.15f, 6, 1.5f, Color{60, 130, 240, 255});
    DrawTextEx(myFont, "Nghỉ phép", {card3.x + 15, card3.y + 8}, 20, 1, Color{40, 100, 220, 255});
    DrawTextEx(myFont, to_string(demNghiPhep).c_str(), {card3.x + 15, card3.y + 32}, 28, 1, Color{30, 90, 210, 255});

    Rectangle card4 = {card3.x + cardW + cardGap, cardY, cardW, cardH};
    DrawRectangleRounded(card4, 0.15f, 6, Color{255, 242, 242, 255});
    DrawRectangleRoundedLinesEx(card4, 0.15f, 6, 1.5f, Color{240, 80, 80, 255});
    DrawTextEx(myFont, "Vắng mặt", {card4.x + 15, card4.y + 8}, 20, 1, Color{200, 40, 40, 255});
    DrawTextEx(myFont, to_string(demVang).c_str(), {card4.x + 15, card4.y + 32}, 28, 1, Color{190, 30, 30, 255});

    // ================= 5. HEADER BẢNG =================
    float startY = 425.0f;
    float colX[] = {360.f, 480.f, 720.f, 900.f, 1070.f, 1310.f, 1620.f};

    DrawTextEx(myFont, "Mã NV", {colX[0], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Họ và tên", {colX[1], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Phòng ban", {colX[2], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Vị trí", {colX[3], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Trạng thái", {colX[4], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Ghi chú", {colX[5], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Thao tác", {colX[6], startY}, 24, 1, DARKGRAY);
    DrawLine(360, startY + 30, 1750, startY + 30, LIGHTGRAY);

    // ================= 6. DANH SÁCH CUỘN (SCROLL TABLE) =================
    int listStartY = (int)(startY + 40);
    int listHeight = (int)(panelBang.y + panelBang.height - listStartY - 65);
    Rectangle listArea = {350.0f, (float)listStartY, 1420.0f, (float)listHeight};
    bool canHover = !blockBackground && CheckCollisionPointRec(mousePos, listArea);

    if (canHover)
        scrollY += GetMouseWheelMove() * scrollSpeed;
    if (scrollY > 0.0f)
        scrollY = 0.0f;

    BeginScissorMode((int)listArea.x, (int)listArea.y, (int)listArea.width, (int)listArea.height);

    float currentY = listStartY + scrollY;
    int totalRows = 0;
    string searchLower = ToLower(searchNV);

    for (Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next; p != nullptr; p = p->Next)
    {
        if (!p->Data || p->Data->get_LoaiNV() != "FullTime")
            continue;
        Employee *emp = p->Data;

        if (!searchLower.empty())
        {
            if (ToLower(emp->get_mnv()).find(searchLower) == string::npos &&
                ToLower(emp->get_name()).find(searchLower) == string::npos)
                continue;
        }

        Rectangle rowRect = {360.0f, currentY - 3, 1390.0f, 44.0f};
        bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
        bool isSelected = (selectedLichEmp == emp);
        if (isSelected)
        {
            DrawRectangleRounded(rowRect, 0.1f, 4, Color{225, 238, 255, 255});
            DrawRectangleRoundedLinesEx(rowRect, 0.1f, 4, 1.2f, Color{60, 120, 240, 255});
        }
        else if (isHover)
        {
            DrawRectangleRounded(rowRect, 0.1f, 4, Color{245, 248, 255, 255});
        }

        DrawTextEx(myFont, emp->get_mnv().c_str(), {colX[0], currentY + 5}, 24, 1, BLACK);
        DrawTextEx(myFont, emp->get_name().c_str(), {colX[1], currentY + 5}, 24, 1, BLACK);

        string tenPB = emp->get_PhongBan() ? emp->get_PhongBan()->get_TenPhongBan() : "";
        string tenVT = emp->get_ViTri() ? emp->get_ViTri()->get_TenVTVL() : "";
        DrawTextEx(myFont, tenPB.c_str(), {colX[2], currentY + 5}, 22, 1, DARKGRAY);
        DrawTextEx(myFont, tenVT.c_str(), {colX[3], currentY + 5}, 22, 1, DARKGRAY);

        // Badge trạng thái FullTime
        ChamCong *cc = QL->get_DB()->FindCC(emp->get_mnv(), dateHienTai);
        Rectangle badgeRec = {colX[4], currentY + 1, 180.0f, 32.0f};

        if (cc == nullptr)
        {
            DrawRectangleRounded(badgeRec, 0.3f, 6, Color{240, 240, 240, 255});
            DrawRectangleRoundedLinesEx(badgeRec, 0.3f, 6, 1.0f, LIGHTGRAY);
            DrawTextEx(myFont, "Chưa chấm", {badgeRec.x + 35, badgeRec.y + 4}, 20, 1, GRAY);
        }
        else
        {
            int tt = cc->get_TrangThai();
            Color bgBadge, borderBadge, txtBadge;
            string labelBadge = "";

            if (tt == 1)
            {
                bgBadge = Color{235, 252, 240, 255};
                borderBadge = Color{40, 170, 80, 255};
                txtBadge = Color{20, 140, 60, 255};
                labelBadge = "Đủ công (1)";
            }
            else if (tt == 2)
            {
                bgBadge = Color{255, 248, 235, 255};
                borderBadge = Color{240, 150, 40, 255};
                txtBadge = Color{210, 110, 10, 255};
                labelBadge = "Nửa công (0.5)";
            }
            else if (tt == 3)
            {
                bgBadge = Color{238, 246, 255, 255};
                borderBadge = Color{50, 130, 240, 255};
                txtBadge = Color{20, 90, 210, 255};
                labelBadge = "Nghỉ phép (P)";
            }
            else if (tt == 4)
            {
                bgBadge = Color{255, 240, 240, 255};
                borderBadge = Color{230, 60, 60, 255};
                txtBadge = Color{200, 30, 30, 255};
                labelBadge = "Không phép (KP)";
            }
            else
            {
                bgBadge = Color{250, 240, 255, 255};
                borderBadge = Color{180, 70, 230, 255};
                txtBadge = Color{140, 30, 190, 255};
                ostringstream ossBadge;
                if (cc->get_SoGio() == (int)cc->get_SoGio())
                    ossBadge << (int)cc->get_SoGio();
                else
                    ossBadge << fixed << setprecision(1) << cc->get_SoGio();
                labelBadge = "Tăng ca (" + ossBadge.str() + "h)";
            }

            DrawRectangleRounded(badgeRec, 0.3f, 6, bgBadge);
            DrawRectangleRoundedLinesEx(badgeRec, 0.3f, 6, 1.2f, borderBadge);
            float lw = MeasureTextEx(myFont, labelBadge.c_str(), 20, 1).x;
            DrawTextEx(myFont, labelBadge.c_str(), {badgeRec.x + (badgeRec.width - lw) / 2.0f, badgeRec.y + 4}, 20, 1, txtBadge);
        }

        string gc = cc ? cc->get_GhiChu() : "-";
        DrawTextEx(myFont, gc.c_str(), {colX[5], currentY + 5}, 22, 1, DARKGRAY);

        // Nút Sửa (duy nhất, không còn nút Lịch bên cạnh)
        Rectangle btnSuaRow = {colX[6] + 20, currentY + 1, 75.0f, 32.0f};
        bool isHoverSua = canHover && CheckCollisionPointRec(mousePos, btnSuaRow);
        DrawRectangleRounded(btnSuaRow, 0.3f, 6, isHoverSua ? Color{225, 238, 255, 255} : WHITE);
        DrawRectangleRoundedLinesEx(btnSuaRow, 0.3f, 6, 1.2f, isHoverSua ? Color{40, 110, 220, 255} : LIGHTGRAY);
        DrawTextEx(myFont, "Sửa", {btnSuaRow.x + 20, btnSuaRow.y + 4}, 20, 1, Color{30, 90, 210, 255});

        if (Clicked && canHover)
        {
            if (isHoverSua)
            {
                selectedEmp = emp;
                selectedLichEmp = emp;
                isOpenModal = true;
                openedThisFrame = true;
            }
            else if (isHover)
            {
                selectedLichEmp = emp;
            }
        }

        DrawLine(360, currentY + 40, 1750, currentY + 40, Fade(LIGHTGRAY, 0.5f));
        currentY += 48;
        totalRows++;
    }

    float totalH = totalRows * 48.0f;
    float maxScroll = listHeight - totalH;
    if (totalH > listHeight && scrollY < maxScroll)
        scrollY = maxScroll;
    if (totalH <= listHeight)
        scrollY = 0.0f;

    EndScissorMode();

    // ================= 7. THANH THAO TÁC DƯỚI BẢNG =================
    float botY = panelBang.y + panelBang.height - 52.0f;
    Rectangle btnChiTietBot = {360, botY, 180, 42};
    bool isHoverBotCT = !blockBackground && CheckCollisionPointRec(mousePos, btnChiTietBot);

    if (selectedLichEmp != nullptr)
    {
        DrawRectangleRounded(btnChiTietBot, 0.25f, 6, isHoverBotCT ? Color{35, 95, 215, 255} : Color{50, 115, 235, 255});
        float wCT = MeasureTextEx(myFont, "Xem chi tiết", 22, 1).x;
        DrawTextEx(myFont, "Xem chi tiết", {btnChiTietBot.x + (btnChiTietBot.width - wCT) / 2.0f, btnChiTietBot.y + 9}, 22, 1, WHITE);
        if (Clicked && !blockBackground && isHoverBotCT)
        {
            isOpenModalLich = true;
            openedLichThisFrame = true;
        }

        string strSel = "Đang chọn: " + selectedLichEmp->get_mnv() + " - " + selectedLichEmp->get_name();
        DrawTextEx(myFont, strSel.c_str(), {560, botY + 9}, 22, 1, Color{30, 90, 210, 255});
    }
    else
    {
        DrawRectangleRounded(btnChiTietBot, 0.25f, 6, Color{242, 244, 248, 255});
        DrawRectangleRoundedLinesEx(btnChiTietBot, 0.25f, 6, 1.2f, LIGHTGRAY);
        float wCT = MeasureTextEx(myFont, "Xem chi tiết", 22, 1).x;
        DrawTextEx(myFont, "Xem chi tiết", {btnChiTietBot.x + (btnChiTietBot.width - wCT) / 2.0f, btnChiTietBot.y + 9}, 22, 1, GRAY);
        if (Clicked && !blockBackground && isHoverBotCT)
        {
            HienThongBao("Vui lòng click chọn 1 nhân viên trong bảng để xem chi tiết!", true);
        }

        DrawTextEx(myFont, "Click chọn 1 nhân viên trong bảng rồi bấm 'Xem chi tiết'", {560, botY + 9}, 20, 1, GRAY);
    }

    DrawTextEx(myFont, ("Tổng NV FullTime: " + to_string(totalRows)).c_str(), {1490, botY + 9}, 22, 1, DARKGRAY);

    // ================= 7. POPUP LỊCH CHÍNH =================
    if (isOpenMainCalendar && !isOpenModal && !isOpenModalLich)
    {
        Rectangle calRec = {btnMainCal.x, btnMainCal.y + 12, btnMainCal.width, btnMainCal.height};
        DrawCalendar(mousePos, curDay, curMonth, curYear, calRec, isOpenMainCalendar);
    }

    // ================= 8. MODAL SỬA CHẤM CÔNG FULL-TIME =================
    if (isOpenModal && selectedEmp != nullptr)
    {
        static int modalDay = curDay;
        static int modalMonth = curMonth;
        static int modalYear = curYear;
        static bool isOpenModalCalendar = false;
        static int modalTrangThai = 1;
        static char modalGioOT[50] = "2.0";
        static int letterModalGioOT = 3;
        static bool isModalGioOTActive = false;
        static char modalGhiChu[100] = "";
        static int letterModalGhiChu = 0;
        static bool isModalGhiChuActive = false;
        static Employee *lastModalEmp = nullptr;

        if (lastModalEmp != selectedEmp)
        {
            lastModalEmp = selectedEmp;
            modalDay = curDay;
            modalMonth = curMonth;
            modalYear = curYear;
            isOpenModalCalendar = false;

            Date d(modalDay, modalMonth, modalYear);
            ChamCong *ccLoad = QL->get_DB()->FindCC(selectedEmp->get_mnv(), d);
            if (ccLoad)
            {
                modalTrangThai = ccLoad->get_TrangThai();
                strncpy(modalGhiChu, ccLoad->get_GhiChu().c_str(), 99);
                if (modalTrangThai == 5 && ccLoad->get_SoGio() > 0.0)
                {
                    ostringstream ossG;
                    if (ccLoad->get_SoGio() == (int)ccLoad->get_SoGio())
                        ossG << (int)ccLoad->get_SoGio() << ".0";
                    else
                        ossG << fixed << setprecision(1) << ccLoad->get_SoGio();
                    strncpy(modalGioOT, ossG.str().c_str(), 9);
                }
                else
                {
                    strncpy(modalGioOT, "2.0", 9);
                }
            }
            else
            {
                modalTrangThai = 1;
                modalGhiChu[0] = '\0';
                strncpy(modalGioOT, "2.0", 9);
            }
            letterModalGioOT = strlen(modalGioOT);
            letterModalGhiChu = strlen(modalGhiChu);
            isModalGioOTActive = false;
            isModalGhiChuActive = false;
        }

        Date modalDate(modalDay, modalMonth, modalYear);

        // Nền mờ
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.45f));

        // Khung modal riêng của FullTime
        Rectangle modalBox = {(GetScreenWidth() - 680) / 2.0f, (GetScreenHeight() - 630) / 2.0f, 680, 630};
        DrawRectangleRounded({modalBox.x + 4, modalBox.y + 5, modalBox.width, modalBox.height}, 0.03f, 8, Fade(BLACK, 0.3f));
        DrawRectangleRounded(modalBox, 0.03f, 8, WHITE);
        DrawRectangleRoundedLinesEx(modalBox, 0.03f, 8, 2.5f, Color{55, 100, 235, 255}); // Viền xanh dương FullTime

        // Tiêu đề
        string tieuDe = "CHỈNH SỬA CHẤM CÔNG - FULL TIME";
        float titleW = MeasureTextEx(myFont, tieuDe.c_str(), 28, 1).x;
        DrawTextEx(myFont, tieuDe.c_str(), {modalBox.x + (modalBox.width - titleW) / 2.0f, modalBox.y + 25}, 28, 1, Color{20, 60, 160, 255});

        string subTitle = selectedEmp->get_mnv() + " - " + selectedEmp->get_name();
        if (selectedEmp->get_PhongBan())
            subTitle += " (" + selectedEmp->get_PhongBan()->get_TenPhongBan() + ")";
        float subW = MeasureTextEx(myFont, subTitle.c_str(), 22, 1).x;
        DrawTextEx(myFont, subTitle.c_str(), {modalBox.x + (modalBox.width - subW) / 2.0f, modalBox.y + 60}, 22, 1, DARKGRAY);

        DrawLine(modalBox.x + 30, modalBox.y + 92, modalBox.x + modalBox.width - 30, modalBox.y + 92, Color{220, 225, 235, 255});

        // Chọn ngày cần sửa
        DrawTextEx(myFont, "Chọn ngày cần sửa:", {modalBox.x + 35, modalBox.y + 108}, 24, 1, BLACK);

        Rectangle btnModalCal = {modalBox.x + 250, modalBox.y + 102, 220, 38};
        DrawRectangleRounded(btnModalCal, 0.3f, 6, isOpenModalCalendar ? Color{235, 245, 255, 255} : Color{248, 250, 252, 255});
        DrawRectangleRoundedLinesEx(btnModalCal, 0.3f, 6, 1.5f, isOpenModalCalendar ? Color{50, 110, 230, 255} : LIGHTGRAY);
        DrawTextEx(myFont, modalDate.ToString().c_str(), {btnModalCal.x + 20, btnModalCal.y + 7}, 24, 1, BLACK);

        if (Clicked && !isOpenModalCalendar && CheckCollisionPointRec(mousePos, btnModalCal))
            isOpenModalCalendar = true;

        // Dữ liệu cũ
        ChamCong *ccCu = QL->get_DB()->FindCC(selectedEmp->get_mnv(), modalDate);
        string strCu = "* Dữ liệu hiện tại: ";
        if (!ccCu)
            strCu += "[Chưa có dữ liệu]";
        else
        {
            int t = ccCu->get_TrangThai();
            if (t == 1)
                strCu += "[Đang là: Có mặt (1 công)]";
            else if (t == 2)
                strCu += "[Đang là: Nửa công (0.5 công)]";
            else if (t == 3)
                strCu += "[Đang là: Nghỉ có phép (P)]";
            else if (t == 4)
                strCu += "[Đang là: Nghỉ không phép (KP)]";
            else
            {
                ostringstream ossCu;
                if (ccCu->get_SoGio() == (int)ccCu->get_SoGio())
                    ossCu << (int)ccCu->get_SoGio();
                else
                    ossCu << fixed << setprecision(1) << ccCu->get_SoGio();
                strCu += "[Đang là: Tăng ca (OT " + ossCu.str() + "h)]";
            }
        }
        DrawTextEx(myFont, strCu.c_str(), {modalBox.x + 35, modalBox.y + 150}, 20, 1, Color{180, 50, 30, 255});

        DrawLine(modalBox.x + 30, modalBox.y + 178, modalBox.x + modalBox.width - 30, modalBox.y + 178, Color{230, 235, 245, 255});

        // 5 Radio Trạng thái (Full-Time)
        DrawTextEx(myFont, "1. Đổi sang trạng thái:", {modalBox.x + 35, modalBox.y + 192}, 24, 1, BLACK);

        string dsTenTT[] = {
            "1. Có mặt (1 công)",
            "2. Nửa công (0.5 công)",
            "3. Nghỉ có phép (P)",
            "4. Nghỉ không phép (KP)",
            "5. Tăng ca (OT)"};

        for (int i = 1; i <= 5; i++)
        {
            float optY = modalBox.y + 220 + (i - 1) * 36.0f;
            float optW = (i == 5 && modalTrangThai == 5) ? 175.0f : 400.0f;
            Rectangle optRec = {modalBox.x + 55, optY, optW, 30};
            bool isHoverOpt = !isOpenModalCalendar && CheckCollisionPointRec(mousePos, optRec);
            bool isSel = (modalTrangThai == i);

            Vector2 center = {optRec.x + 10, optRec.y + 15};
            DrawCircleV(center, 8, WHITE);
            DrawCircleLines(center.x, center.y, 8, isSel ? (i == 5 ? Color{140, 50, 220, 255} : Color{40, 110, 230, 255}) : DARKGRAY);
            if (isSel)
                DrawCircleV(center, 4, (i == 5 ? Color{140, 50, 220, 255} : Color{40, 110, 230, 255}));

            DrawTextEx(myFont, dsTenTT[i - 1].c_str(), {optRec.x + 28, optRec.y + 3}, 22, 1, isSel ? (i == 5 ? Color{120, 30, 180, 255} : Color{20, 60, 160, 255}) : BLACK);

            if (Clicked && !isOpenModalCalendar && isHoverOpt)
            {
                modalTrangThai = i;
                if (i == 5)
                {
                    isModalGioOTActive = true;
                    isModalGhiChuActive = false;
                }
            }
        }

        // HỘP NHẬP SỐ GIỜ OT (CHỈ HIỆN RA KHI BẤM CHỌN "5. Tăng ca (OT)")
        Rectangle boxOTInput = {0, 0, 0, 0};
        if (modalTrangThai == 5)
        {
            float optY5 = modalBox.y + 220 + 4 * 36.0f;
            Rectangle boxOTWrap = {modalBox.x + 235, optY5 - 5, 410, 40};
            DrawRectangleRounded(boxOTWrap, 0.25f, 6, Color{248, 243, 255, 255});
            DrawRectangleRoundedLinesEx(boxOTWrap, 0.25f, 6, 1.2f, Color{180, 130, 240, 255});

            DrawTextEx(myFont, "Số giờ OT:", {boxOTWrap.x + 12, boxOTWrap.y + 8}, 22, 1, Color{120, 30, 180, 255});

            boxOTInput = {boxOTWrap.x + 125, boxOTWrap.y + 4, 85, 32};
            DrawRectangleRounded(boxOTInput, 0.25f, 4, WHITE);
            DrawRectangleRoundedLinesEx(boxOTInput, 0.25f, 4, 1.5f, isModalGioOTActive ? Color{130, 40, 220, 255} : LIGHTGRAY);

            if (isModalGioOTActive)
                TypingNumber(modalGioOT, letterModalGioOT, 9);

            if (modalGioOT[0] == '\0')
                DrawTextEx(myFont, "0.0", {boxOTInput.x + 15, boxOTInput.y + 5}, 22, 1, GRAY);
            else
                DrawTextEx(myFont, modalGioOT, {boxOTInput.x + 15, boxOTInput.y + 5}, 22, 1, BLACK);

            if (isModalGioOTActive && ((int)(GetTime() * 2) % 2 == 0))
            {
                float w = MeasureTextEx(myFont, modalGioOT, 22, 1).x;
                DrawTextEx(myFont, "_", {boxOTInput.x + 15 + w, boxOTInput.y + 5}, 22, 1, Color{130, 40, 220, 255});
            }

            DrawTextEx(myFont, "giờ", {boxOTWrap.x + 220, boxOTWrap.y + 8}, 22, 1, DARKGRAY);
            DrawTextEx(myFont, "(+1.5x lương)", {boxOTWrap.x + 265, boxOTWrap.y + 9}, 18, 1, Color{140, 50, 210, 255});
        }

        // Nhập Lý do / Ghi chú
        float yGC = modalBox.y + 410;
        DrawTextEx(myFont, "2. Lý do / Ghi chú:", {modalBox.x + 35, yGC}, 24, 1, BLACK);
        Rectangle boxGC = {modalBox.x + 35, yGC + 32, modalBox.width - 70, 42};
        DrawRectangleRounded(boxGC, 0.2f, 6, Color{248, 250, 252, 255});
        DrawRectangleRoundedLinesEx(boxGC, 0.2f, 6, 1.5f, isModalGhiChuActive ? Color{50, 110, 230, 255} : LIGHTGRAY);

        if (Clicked && !isOpenModalCalendar)
        {
            if (CheckCollisionPointRec(mousePos, boxGC))
            {
                isModalGhiChuActive = true;
                isModalGioOTActive = false;
            }
            else if (modalTrangThai == 5 && (CheckCollisionPointRec(mousePos, boxOTInput) || CheckCollisionPointRec(mousePos, {modalBox.x + 55, modalBox.y + 220 + 4 * 36.0f, 175.0f, 30.0f})))
            {
                isModalGioOTActive = true;
                isModalGhiChuActive = false;
            }
            else
            {
                isModalGhiChuActive = false;
                isModalGioOTActive = false;
            }
        }

        if (isModalGhiChuActive)
            TypingKeys(modalGhiChu, letterModalGhiChu, 99);
        if (modalGhiChu[0] == '\0')
            DrawTextEx(myFont, "Nhập lý do hoặc ghi chú...", {boxGC.x + 15, boxGC.y + 8}, 20, 1, GRAY);
        else
            DrawTextEx(myFont, modalGhiChu, {boxGC.x + 15, boxGC.y + 8}, 22, 1, BLACK);

        if (isModalGhiChuActive && ((int)(GetTime() * 2) % 2 == 0))
        {
            float w = MeasureTextEx(myFont, modalGhiChu, 22, 1).x;
            DrawTextEx(myFont, "_", {boxGC.x + 15 + w, boxGC.y + 8}, 22, 1, Color{50, 110, 230, 255});
        }

        // Nút Cập nhật & Hủy
        float btnY = modalBox.y + modalBox.height - 70;

        Rectangle btnSubmit = {modalBox.x + 150, btnY, 170, 48};
        bool hSub = CheckCollisionPointRec(mousePos, btnSubmit);
        VeNutChucNang(btnSubmit, "Cập nhật", NutStyle::Green, hSub, 4);

        Rectangle btnCancel = {modalBox.x + 360, btnY, 170, 48};
        bool hCan = CheckCollisionPointRec(mousePos, btnCancel);
        VeNutChucNang(btnCancel, "Hủy", NutStyle::Secondary, hCan, 5);

        // Xử lý Cập nhật (Full-Time: số giờ mặc định 8.0h, nửa công 4.0h, nghỉ phép/vắng 0.0h, OT lấy từ modalGioOT)
        if (Clicked && !isOpenModalCalendar && CheckCollisionPointRec(mousePos, btnSubmit))
        {
            double g = 8.0;
            if (modalTrangThai == 2)
                g = 4.0;
            else if (modalTrangThai == 3 || modalTrangThai == 4)
                g = 0.0;
            else if (modalTrangThai == 5)
            {
                g = atof(modalGioOT);
                if (g <= 0.0)
                    g = 2.0;
            }
            Date dCanSua(modalDay, modalMonth, modalYear);
            ChamCong *ccCurrent = QL->get_DB()->FindCC(selectedEmp->get_mnv(), dCanSua);
            if (ccCurrent)
            {
                ccCurrent->set_TrangThai(modalTrangThai);
                ccCurrent->set_SoGio(g);
                ccCurrent->set_GhiChu(modalGhiChu);
            }
            else
            {
                QL->get_DB()->Insert(new ChamCong(selectedEmp, dCanSua, modalTrangThai, g, modalGhiChu));
            }
            QL->get_DB()->SaveFileChamCong();
            QL->DongBoChamCong(dCanSua.get_month(), dCanSua.get_year());
            QL->get_DB()->SaveFileEmployee();
            HienThongBao("Cập nhật chấm công Full-Time thành công!", false);
            isOpenModal = false;
            lastModalEmp = nullptr;
            isModalGioOTActive = false;
            isModalGhiChuActive = false;
        }

        // Xử lý Hủy
        if (Clicked && !openedThisFrame && !isOpenModalCalendar && (CheckCollisionPointRec(mousePos, btnCancel) || !CheckCollisionPointRec(mousePos, modalBox)))
        {
            isOpenModal = false;
            lastModalEmp = nullptr;
            isModalGioOTActive = false;
            isModalGhiChuActive = false;
        }

        // Lịch con Modal
        if (isOpenModalCalendar)
        {
            Rectangle modalCalRec = {btnModalCal.x, btnModalCal.y + 12, btnModalCal.width, btnModalCal.height};
            bool changed = DrawCalendar(mousePos, modalDay, modalMonth, modalYear, modalCalRec, isOpenModalCalendar);
            if (changed)
            {
                ChamCong *ccNew = QL->get_DB()->FindCC(selectedEmp->get_mnv(), Date(modalDay, modalMonth, modalYear));
                if (ccNew)
                {
                    modalTrangThai = ccNew->get_TrangThai();
                    strncpy(modalGhiChu, ccNew->get_GhiChu().c_str(), 99);
                    if (modalTrangThai == 5 && ccNew->get_SoGio() > 0.0)
                    {
                        ostringstream ossG;
                        if (ccNew->get_SoGio() == (int)ccNew->get_SoGio())
                            ossG << (int)ccNew->get_SoGio() << ".0";
                        else
                            ossG << fixed << setprecision(1) << ccNew->get_SoGio();
                        strncpy(modalGioOT, ossG.str().c_str(), 9);
                    }
                    else
                    {
                        strncpy(modalGioOT, "2.0", 9);
                    }
                }
                else
                {
                    modalTrangThai = 1;
                    modalGhiChu[0] = '\0';
                    strncpy(modalGioOT, "2.0", 9);
                }
                letterModalGioOT = strlen(modalGioOT);
                letterModalGhiChu = strlen(modalGhiChu);
                isModalGioOTActive = false;
                isModalGhiChuActive = false;
            }
        }
    }

    // ================= 9. MODAL XEM CHI TIẾT LỊCH ĐI LÀM CỦA NHÂN VIÊN =================
    if (isOpenModalLich && selectedLichEmp != nullptr)
    {
        VeModalLichNhanVien(mousePos, Clicked, QL, isOpenModalLich, selectedLichEmp, curMonth, curYear, openedLichThisFrame);
    }

    openedThisFrame = false;
    openedLichThisFrame = false;
    openedCalThisFrame = false;
    g_isModalActive = (isOpenModal || isOpenModalLich || isOpenMainCalendar);
}
void Draw_Screen_CC_PartTime(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    // ================= 1. TRẠNG THÁI & BIẾN CỤC BỘ =================
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static int curDay = day;
    static int curMonth = month;
    static int curYear = year;
    if (doReset)
    {
        curDay = day;
        curMonth = month;
        curYear = year;
    }
    static bool isOpenMainCalendar = false;
    if (doReset)
        isOpenMainCalendar = false;
    Date dateHienTai(curDay, curMonth, curYear);

    static char searchNV[50] = "";
    if (doReset)
        searchNV[0] = '\0';
    static int letterSearchNV = 0;
    if (doReset)
        letterSearchNV = 0;
    static bool isSearchNVActive = false;
    if (doReset)
        isSearchNVActive = false;

    static float scrollY = 0.0f;
    if (doReset)
        scrollY = 0.0f;
    float scrollSpeed = 30.0f;

    static bool isOpenModal = false;
    if (doReset)
        isOpenModal = false;
    static Employee *selectedEmp = nullptr;
    if (doReset)
        selectedEmp = nullptr;
    static bool isOpenModalLich = false;
    if (doReset)
        isOpenModalLich = false;
    static Employee *selectedLichEmp = nullptr;
    if (doReset)
        selectedLichEmp = nullptr;
    static bool openedThisFrame = false;
    static bool openedLichThisFrame = false;
    static bool openedCalThisFrame = false;
    bool blockBackground = isOpenModal || isOpenModalLich || isOpenMainCalendar;

    // ================= 2. KHUNG NỀN TRẮNG CHÍNH =================
    Rectangle panelBang = {330, 270, 1450.0f, 715.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    // ================= 3. THANH TOOLBAR =================
    // Nút Lịch chọn ngày
    Rectangle btnMainCal = {350, 285, 230, 42};
    DrawRectangleRounded(btnMainCal, 0.3f, 6, isOpenMainCalendar ? Color{245, 235, 255, 255} : Color{248, 247, 250, 255});
    DrawRectangleRoundedLinesEx(btnMainCal, 0.3f, 6, 1.5f, isOpenMainCalendar ? Color{130, 60, 210, 255} : LIGHTGRAY);
    string strMainDate = "Ngày: " + dateHienTai.ToString() + "  v";
    DrawTextEx(myFont, strMainDate.c_str(), {btnMainCal.x + 18, btnMainCal.y + 8}, 22, 1, BLACK);
    if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnMainCal))
    {
        isOpenMainCalendar = !isOpenMainCalendar;
        openedCalThisFrame = true;
    }

    // Ô tìm kiếm NV PartTime
    Rectangle boxSearch = {600, 285, 300, 42};
    DrawRectangleRounded(boxSearch, 0.3f, 6, Color{248, 250, 252, 255});
    DrawRectangleRoundedLinesEx(boxSearch, 0.3f, 6, 1.5f, isSearchNVActive ? Color{130, 60, 210, 255} : LIGHTGRAY);
    if (Clicked && !blockBackground)
        isSearchNVActive = CheckCollisionPointRec(mousePos, boxSearch);
    if (isSearchNVActive && !blockBackground)
        Typing(isSearchNVActive, searchNV, letterSearchNV, mousePos, boxSearch);
    if (searchNV[0] == '\0')
        DrawTextEx(myFont, "Tìm tên hoặc mã NV...", {boxSearch.x + 15, boxSearch.y + 8}, 22, 1, GRAY);
    else
        DrawTextEx(myFont, searchNV, {boxSearch.x + 15, boxSearch.y + 8}, 24, 1, BLACK);
    if (!blockBackground && isSearchNVActive && searchNV[0] != '\0' && ((int)(GetTime() * 2) % 2 == 0))
    {
        Vector2 textSize = MeasureTextEx(myFont, searchNV, 24, 1);
        float cursorX = boxSearch.x + 15 + textSize.x + 2;
        if (cursorX < boxSearch.x + boxSearch.width - 15)
        {
            DrawTextEx(myFont, "_", {cursorX, boxSearch.y + 8}, 24, 1, Color{130, 60, 210, 255});
        }
    }

    // Nút "Điểm danh tất cả Có Mặt" (Part-Time: mặc định ca chuẩn 4.0 giờ)
    Rectangle btnAllDu = {920, 285, 230, 42};
    DrawRectangleRounded(btnAllDu, 0.3f, 6, Color{34, 150, 80, 255});
    DrawTextEx(myFont, "Điểm danh tất cả", {btnAllDu.x + 28, btnAllDu.y + 8}, 22, 1, WHITE);
    if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnAllDu))
    {
        for (Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next; p != nullptr; p = p->Next)
        {
            if (!p->Data || p->Data->get_LoaiNV() != "PartTime")
                continue;
            ChamCong *cc = QL->get_DB()->FindCC(p->Data->get_mnv(), dateHienTai);
            if (cc)
            {
                cc->set_TrangThai(1);
                cc->set_SoGio(4.0);
            }
            else
            {
                QL->get_DB()->Insert(new ChamCong(p->Data, dateHienTai, 1, 4.0, "Đúng giờ"));
            }
        }
        QL->get_DB()->SaveFileChamCong();
        QL->DongBoChamCong(curMonth, curYear);
        QL->get_DB()->SaveFileEmployee();
        HienThongBao("Đã điểm danh tất cả Part-Time Có Mặt (4.0h)!", false);
    }

    // Nút "Chốt giờ -> Bảng Lương"
    Rectangle btnChotCong = {1170, 285, 270, 42};
    DrawRectangleRounded(btnChotCong, 0.3f, 6, Color{130, 60, 210, 255});
    DrawTextEx(myFont, "Chốt giờ vào Bảng Lương", {btnChotCong.x + 22, btnChotCong.y + 8}, 22, 1, WHITE);
    if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnChotCong))
    {
        XuatBangLuongThang(QL, curMonth, curYear);
        HienThongBao("Đã chốt giờ & xuất file Bảng Lương tháng " + to_string(curMonth) + "/" + to_string(curYear) + "!", false);
    }

    // ================= 4. 4 THẺ THỐNG KÊ KPI PART-TIME =================
    int demTongNV = 0, demCoMat = 0, demNghiPhep = 0, demVang = 0;
    for (Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next; p != nullptr; p = p->Next)
    {
        if (!p->Data || p->Data->get_LoaiNV() != "PartTime")
            continue;
        demTongNV++;
        ChamCong *cc = QL->get_DB()->FindCC(p->Data->get_mnv(), dateHienTai);
        if (cc)
        {
            int tt = cc->get_TrangThai();
            if (tt == 1 || tt == 2 || tt == 5)
                demCoMat++;
            else if (tt == 3)
                demNghiPhep++;
            else if (tt == 4)
                demVang++;
        }
    }

    float cardY = 345.0f;
    float cardW = 325.0f;
    float cardH = 65.0f;
    float cardGap = 30.0f;

    Rectangle card1 = {360.0f, cardY, cardW, cardH};
    DrawRectangleRounded(card1, 0.15f, 6, WHITE);
    DrawRectangleRoundedLinesEx(card1, 0.15f, 6, 1.5f, DARKGRAY);
    DrawTextEx(myFont, "Tổng PartTime", {card1.x + 15, card1.y + 8}, 20, 1, DARKGRAY);
    DrawTextEx(myFont, to_string(demTongNV).c_str(), {card1.x + 15, card1.y + 32}, 28, 1, BLACK);

    Rectangle card2 = {card1.x + cardW + cardGap, cardY, cardW, cardH};
    DrawRectangleRounded(card2, 0.15f, 6, Color{240, 252, 244, 255});
    DrawRectangleRoundedLinesEx(card2, 0.15f, 6, 1.5f, Color{46, 180, 90, 255});
    DrawTextEx(myFont, "Có ca làm", {card2.x + 15, card2.y + 8}, 20, 1, Color{30, 140, 70, 255});
    DrawTextEx(myFont, to_string(demCoMat).c_str(), {card2.x + 15, card2.y + 32}, 28, 1, Color{20, 130, 60, 255});

    Rectangle card3 = {card2.x + cardW + cardGap, cardY, cardW, cardH};
    DrawRectangleRounded(card3, 0.15f, 6, Color{240, 248, 255, 255});
    DrawRectangleRoundedLinesEx(card3, 0.15f, 6, 1.5f, Color{60, 130, 240, 255});
    DrawTextEx(myFont, "Nghỉ phép", {card3.x + 15, card3.y + 8}, 20, 1, Color{40, 100, 220, 255});
    DrawTextEx(myFont, to_string(demNghiPhep).c_str(), {card3.x + 15, card3.y + 32}, 28, 1, Color{30, 90, 210, 255});

    Rectangle card4 = {card3.x + cardW + cardGap, cardY, cardW, cardH};
    DrawRectangleRounded(card4, 0.15f, 6, Color{255, 242, 242, 255});
    DrawRectangleRoundedLinesEx(card4, 0.15f, 6, 1.5f, Color{240, 80, 80, 255});
    DrawTextEx(myFont, "Vắng mặt", {card4.x + 15, card4.y + 8}, 20, 1, Color{200, 40, 40, 255});
    DrawTextEx(myFont, to_string(demVang).c_str(), {card4.x + 15, card4.y + 32}, 28, 1, Color{190, 30, 30, 255});

    // ================= 5. HEADER BẢNG =================
    float startY = 425.0f;
    float colX[] = {360.f, 480.f, 720.f, 900.f, 1070.f, 1310.f, 1620.f};

    DrawTextEx(myFont, "Mã NV", {colX[0], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Họ và tên", {colX[1], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Phòng ban", {colX[2], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Vị trí", {colX[3], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Trạng thái / Giờ làm", {colX[4], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Ghi chú", {colX[5], startY}, 24, 1, DARKGRAY);
    DrawTextEx(myFont, "Thao tác", {colX[6], startY}, 24, 1, DARKGRAY);
    DrawLine(360, startY + 30, 1750, startY + 30, LIGHTGRAY);

    // ================= 6. DANH SÁCH CUỘN (SCROLL TABLE) =================
    int listStartY = (int)(startY + 40);
    int listHeight = (int)(panelBang.y + panelBang.height - listStartY - 65);
    Rectangle listArea = {350.0f, (float)listStartY, 1420.0f, (float)listHeight};
    bool canHover = !blockBackground && CheckCollisionPointRec(mousePos, listArea);

    if (canHover)
        scrollY += GetMouseWheelMove() * scrollSpeed;
    if (scrollY > 0.0f)
        scrollY = 0.0f;

    BeginScissorMode((int)listArea.x, (int)listArea.y, (int)listArea.width, (int)listArea.height);

    float currentY = listStartY + scrollY;
    int totalRows = 0;
    string searchLower = ToLower(searchNV);

    for (Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next; p != nullptr; p = p->Next)
    {
        if (!p->Data || p->Data->get_LoaiNV() != "PartTime")
            continue;
        Employee *emp = p->Data;

        if (!searchLower.empty())
        {
            if (ToLower(emp->get_mnv()).find(searchLower) == string::npos &&
                ToLower(emp->get_name()).find(searchLower) == string::npos)
                continue;
        }

        Rectangle rowRect = {360.0f, currentY - 3, 1390.0f, 44.0f};
        bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
        bool isSelected = (selectedLichEmp == emp);
        if (isSelected)
        {
            DrawRectangleRounded(rowRect, 0.1f, 4, Color{246, 236, 255, 255});
            DrawRectangleRoundedLinesEx(rowRect, 0.1f, 4, 1.2f, Color{130, 60, 210, 255});
        }
        else if (isHover)
        {
            DrawRectangleRounded(rowRect, 0.1f, 4, Color{250, 245, 255, 255});
        }

        DrawTextEx(myFont, emp->get_mnv().c_str(), {colX[0], currentY + 5}, 24, 1, BLACK);
        DrawTextEx(myFont, emp->get_name().c_str(), {colX[1], currentY + 5}, 24, 1, BLACK);

        string tenPB = emp->get_PhongBan() ? emp->get_PhongBan()->get_TenPhongBan() : "";
        string tenVT = emp->get_ViTri() ? emp->get_ViTri()->get_TenVTVL() : "";
        DrawTextEx(myFont, tenPB.c_str(), {colX[2], currentY + 5}, 22, 1, DARKGRAY);
        DrawTextEx(myFont, tenVT.c_str(), {colX[3], currentY + 5}, 22, 1, DARKGRAY);

        // Badge trạng thái PartTime kèm số giờ
        ChamCong *cc = QL->get_DB()->FindCC(emp->get_mnv(), dateHienTai);
        Rectangle badgeRec = {colX[4], currentY + 1, 180.0f, 32.0f};

        if (cc == nullptr)
        {
            DrawRectangleRounded(badgeRec, 0.3f, 6, Color{240, 240, 240, 255});
            DrawRectangleRoundedLinesEx(badgeRec, 0.3f, 6, 1.0f, LIGHTGRAY);
            DrawTextEx(myFont, "Chưa chấm", {badgeRec.x + 35, badgeRec.y + 4}, 20, 1, GRAY);
        }
        else
        {
            int tt = cc->get_TrangThai();
            Color bgBadge, borderBadge, txtBadge;
            string labelBadge = "";

            if (tt == 1)
            {
                bgBadge = Color{235, 252, 240, 255};
                borderBadge = Color{40, 170, 80, 255};
                txtBadge = Color{20, 140, 60, 255};
                labelBadge = "Có ca (" + to_string((int)cc->get_SoGio()) + "h)";
            }
            else if (tt == 2)
            {
                bgBadge = Color{255, 248, 235, 255};
                borderBadge = Color{240, 150, 40, 255};
                txtBadge = Color{210, 110, 10, 255};
                labelBadge = "Nửa ca (" + to_string((int)cc->get_SoGio()) + "h)";
            }
            else if (tt == 3)
            {
                bgBadge = Color{238, 246, 255, 255};
                borderBadge = Color{50, 130, 240, 255};
                txtBadge = Color{20, 90, 210, 255};
                labelBadge = "Nghỉ phép (P)";
            }
            else if (tt == 4)
            {
                bgBadge = Color{255, 240, 240, 255};
                borderBadge = Color{230, 60, 60, 255};
                txtBadge = Color{200, 30, 30, 255};
                labelBadge = "Không phép (KP)";
            }
            else
            {
                bgBadge = Color{250, 240, 255, 255};
                borderBadge = Color{180, 70, 230, 255};
                txtBadge = Color{140, 30, 190, 255};
                labelBadge = "Tăng ca (" + to_string((int)cc->get_SoGio()) + "h)";
            }

            DrawRectangleRounded(badgeRec, 0.3f, 6, bgBadge);
            DrawRectangleRoundedLinesEx(badgeRec, 0.3f, 6, 1.2f, borderBadge);
            float lw = MeasureTextEx(myFont, labelBadge.c_str(), 20, 1).x;
            DrawTextEx(myFont, labelBadge.c_str(), {badgeRec.x + (badgeRec.width - lw) / 2.0f, badgeRec.y + 4}, 20, 1, txtBadge);
        }

        string gc = cc ? cc->get_GhiChu() : "-";
        DrawTextEx(myFont, gc.c_str(), {colX[5], currentY + 5}, 22, 1, DARKGRAY);

        // Nút Sửa (duy nhất, không còn nút Lịch bên cạnh)
        Rectangle btnSuaRow = {colX[6] + 20, currentY + 1, 75.0f, 32.0f};
        bool isHoverSua = canHover && CheckCollisionPointRec(mousePos, btnSuaRow);
        DrawRectangleRounded(btnSuaRow, 0.3f, 6, isHoverSua ? Color{245, 235, 255, 255} : WHITE);
        DrawRectangleRoundedLinesEx(btnSuaRow, 0.3f, 6, 1.2f, isHoverSua ? Color{130, 60, 210, 255} : LIGHTGRAY);
        DrawTextEx(myFont, "Sửa", {btnSuaRow.x + 20, btnSuaRow.y + 4}, 20, 1, Color{120, 40, 200, 255});

        if (Clicked && canHover)
        {
            if (isHoverSua)
            {
                selectedEmp = emp;
                selectedLichEmp = emp;
                isOpenModal = true;
                openedThisFrame = true;
            }
            else if (isHover)
            {
                selectedLichEmp = emp;
            }
        }

        DrawLine(360, currentY + 40, 1750, currentY + 40, Fade(LIGHTGRAY, 0.5f));
        currentY += 48;
        totalRows++;
    }

    float totalH = totalRows * 48.0f;
    float maxScroll = listHeight - totalH;
    if (totalH > listHeight && scrollY < maxScroll)
        scrollY = maxScroll;
    if (totalH <= listHeight)
        scrollY = 0.0f;

    EndScissorMode();

    // ================= 7. THANH THAO TÁC DƯỚI BẢNG =================
    float botY = panelBang.y + panelBang.height - 52.0f;
    Rectangle btnChiTietBot = {360, botY, 180, 42};
    bool isHoverBotCT = !blockBackground && CheckCollisionPointRec(mousePos, btnChiTietBot);

    if (selectedLichEmp != nullptr)
    {
        DrawRectangleRounded(btnChiTietBot, 0.25f, 6, isHoverBotCT ? Color{115, 45, 195, 255} : Color{130, 60, 210, 255});
        float wCT = MeasureTextEx(myFont, "Xem chi tiết", 22, 1).x;
        DrawTextEx(myFont, "Xem chi tiết", {btnChiTietBot.x + (btnChiTietBot.width - wCT) / 2.0f, btnChiTietBot.y + 9}, 22, 1, WHITE);
        if (Clicked && !blockBackground && isHoverBotCT)
        {
            isOpenModalLich = true;
            openedLichThisFrame = true;
        }

        string strSel = "Đang chọn: " + selectedLichEmp->get_mnv() + " - " + selectedLichEmp->get_name();
        DrawTextEx(myFont, strSel.c_str(), {570, botY + 9}, 22, 1, Color{120, 40, 200, 255});
    }
    else
    {
        DrawRectangleRounded(btnChiTietBot, 0.25f, 6, Color{242, 244, 248, 255});
        DrawRectangleRoundedLinesEx(btnChiTietBot, 0.25f, 6, 1.2f, LIGHTGRAY);
        float wCT = MeasureTextEx(myFont, "Xem chi tiết", 22, 1).x;
        DrawTextEx(myFont, "Xem chi tiết", {btnChiTietBot.x + (btnChiTietBot.width - wCT) / 2.0f, btnChiTietBot.y + 9}, 22, 1, GRAY);
        if (Clicked && !blockBackground && isHoverBotCT)
        {
            HienThongBao("Vui lòng click chọn 1 nhân viên trong bảng để xem chi tiết!", true);
        }

        DrawTextEx(myFont, "Click chọn 1 nhân viên trong bảng rồi bấm 'Xem chi tiết'", {570, botY + 9}, 20, 1, GRAY);
    }

    DrawTextEx(myFont, ("Tổng NV PartTime: " + to_string(totalRows)).c_str(), {1490, botY + 9}, 22, 1, DARKGRAY);

    // ================= 7. POPUP LỊCH CHÍNH =================
    if (isOpenMainCalendar && !isOpenModal && !isOpenModalLich)
    {
        Rectangle calRec = {btnMainCal.x, btnMainCal.y + 12, btnMainCal.width, btnMainCal.height};
        DrawCalendar(mousePos, curDay, curMonth, curYear, calRec, isOpenMainCalendar);
    }

    // ================= 8. MODAL SỬA CHẤM CÔNG PART-TIME =================
    if (isOpenModal && selectedEmp != nullptr)
    {
        static int modalDay = curDay;
        static int modalMonth = curMonth;
        static int modalYear = curYear;
        static bool isOpenModalCalendar = false;
        static int modalTrangThai = 1;
        static char modalGio[20] = "4.0";
        static int letterModalGio = 3;
        static bool isModalGioActive = false;
        static char modalGhiChu[100] = "";
        static int letterModalGhiChu = 0;
        static bool isModalGhiChuActive = false;
        static Employee *lastModalEmp = nullptr;

        if (lastModalEmp != selectedEmp)
        {
            lastModalEmp = selectedEmp;
            modalDay = curDay;
            modalMonth = curMonth;
            modalYear = curYear;
            isOpenModalCalendar = false;

            Date d(modalDay, modalMonth, modalYear);
            ChamCong *ccLoad = QL->get_DB()->FindCC(selectedEmp->get_mnv(), d);
            if (ccLoad)
            {
                modalTrangThai = ccLoad->get_TrangThai();
                snprintf(modalGio, sizeof(modalGio), "%.1f", ccLoad->get_SoGio());
                strncpy(modalGhiChu, ccLoad->get_GhiChu().c_str(), 99);
            }
            else
            {
                modalTrangThai = 1;
                snprintf(modalGio, sizeof(modalGio), "4.0");
                modalGhiChu[0] = '\0';
            }
            letterModalGio = strlen(modalGio);
            letterModalGhiChu = strlen(modalGhiChu);
        }

        Date modalDate(modalDay, modalMonth, modalYear);

        // Nền mờ
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.45f));

        // Khung modal riêng của PartTime (có thêm ô nhập số giờ)
        Rectangle modalBox = {(GetScreenWidth() - 700) / 2.0f, (GetScreenHeight() - 700) / 2.0f, 700, 700};
        DrawRectangleRounded({modalBox.x + 4, modalBox.y + 5, modalBox.width, modalBox.height}, 0.03f, 8, Fade(BLACK, 0.3f));
        DrawRectangleRounded(modalBox, 0.03f, 8, WHITE);
        DrawRectangleRoundedLinesEx(modalBox, 0.03f, 8, 2.5f, Color{130, 60, 210, 255}); // Viền tím PartTime

        // Tiêu đề
        string tieuDe = "CHỈNH SỬA CHẤM CÔNG - PART TIME";
        float titleW = MeasureTextEx(myFont, tieuDe.c_str(), 28, 1).x;
        DrawTextEx(myFont, tieuDe.c_str(), {modalBox.x + (modalBox.width - titleW) / 2.0f, modalBox.y + 25}, 28, 1, Color{100, 40, 180, 255});

        string subTitle = selectedEmp->get_mnv() + " - " + selectedEmp->get_name();
        if (selectedEmp->get_PhongBan())
            subTitle += " (" + selectedEmp->get_PhongBan()->get_TenPhongBan() + ")";
        float subW = MeasureTextEx(myFont, subTitle.c_str(), 22, 1).x;
        DrawTextEx(myFont, subTitle.c_str(), {modalBox.x + (modalBox.width - subW) / 2.0f, modalBox.y + 60}, 22, 1, DARKGRAY);

        DrawLine(modalBox.x + 30, modalBox.y + 92, modalBox.x + modalBox.width - 30, modalBox.y + 92, Color{220, 225, 235, 255});

        // Chọn ngày cần sửa
        DrawTextEx(myFont, "Chọn ngày cần sửa:", {modalBox.x + 35, modalBox.y + 108}, 24, 1, BLACK);

        Rectangle btnModalCal = {modalBox.x + 250, modalBox.y + 102, 220, 38};
        DrawRectangleRounded(btnModalCal, 0.3f, 6, isOpenModalCalendar ? Color{245, 235, 255, 255} : Color{248, 250, 252, 255});
        DrawRectangleRoundedLinesEx(btnModalCal, 0.3f, 6, 1.5f, isOpenModalCalendar ? Color{130, 60, 210, 255} : LIGHTGRAY);
        DrawTextEx(myFont, modalDate.ToString().c_str(), {btnModalCal.x + 20, btnModalCal.y + 7}, 24, 1, BLACK);

        if (Clicked && !isOpenModalCalendar && CheckCollisionPointRec(mousePos, btnModalCal))
            isOpenModalCalendar = true;

        // Dữ liệu cũ
        ChamCong *ccCu = QL->get_DB()->FindCC(selectedEmp->get_mnv(), modalDate);
        string strCu = "* Dữ liệu hiện tại: ";
        if (!ccCu)
            strCu += "[Chưa có dữ liệu]";
        else
        {
            int t = ccCu->get_TrangThai();
            if (t == 1)
                strCu += "[Đang là: Có ca - " + to_string((int)ccCu->get_SoGio()) + "h]";
            else if (t == 2)
                strCu += "[Đang là: Nửa ca - " + to_string((int)ccCu->get_SoGio()) + "h]";
            else if (t == 3)
                strCu += "[Đang là: Nghỉ có phép (P)]";
            else if (t == 4)
                strCu += "[Đang là: Nghỉ không phép (KP)]";
            else
                strCu += "[Đang là: Tăng ca - " + to_string((int)ccCu->get_SoGio()) + "h]";
        }
        DrawTextEx(myFont, strCu.c_str(), {modalBox.x + 35, modalBox.y + 150}, 20, 1, Color{180, 50, 30, 255});

        DrawLine(modalBox.x + 30, modalBox.y + 178, modalBox.x + modalBox.width - 30, modalBox.y + 178, Color{230, 235, 245, 255});

        // 5 Radio Trạng thái (Part-Time)
        DrawTextEx(myFont, "1. Đổi sang trạng thái:", {modalBox.x + 35, modalBox.y + 192}, 24, 1, BLACK);

        string dsTenTT[] = {
            "1. Có ca làm việc (Đủ giờ)",
            "2. Nửa ca làm việc",
            "3. Nghỉ có phép (P)",
            "4. Nghỉ không phép (KP)",
            "5. Tăng ca (OT)"};

        for (int i = 1; i <= 5; i++)
        {
            float optY = modalBox.y + 220 + (i - 1) * 36.0f;
            Rectangle optRec = {modalBox.x + 55, optY, 400, 30};
            bool isHoverOpt = !isOpenModalCalendar && CheckCollisionPointRec(mousePos, optRec);
            bool isSel = (modalTrangThai == i);

            Vector2 center = {optRec.x + 10, optRec.y + 15};
            DrawCircleV(center, 8, WHITE);
            DrawCircleLines(center.x, center.y, 8, isSel ? Color{130, 60, 210, 255} : DARKGRAY);
            if (isSel)
                DrawCircleV(center, 4, Color{130, 60, 210, 255});

            DrawTextEx(myFont, dsTenTT[i - 1].c_str(), {optRec.x + 28, optRec.y + 3}, 22, 1, isSel ? Color{100, 40, 180, 255} : BLACK);

            if (Clicked && !isOpenModalCalendar && isHoverOpt)
            {
                modalTrangThai = i;
                // Tự động gợi ý số giờ tương ứng
                if (i == 1)
                    snprintf(modalGio, sizeof(modalGio), "4.0");
                else if (i == 2)
                    snprintf(modalGio, sizeof(modalGio), "2.0");
                else if (i == 3 || i == 4)
                    snprintf(modalGio, sizeof(modalGio), "0.0");
                else if (i == 5)
                {
                    snprintf(modalGio, sizeof(modalGio), "2.0");
                    isModalGioActive = true;
                }
                letterModalGio = strlen(modalGio);
            }
        }

        // Ô NHẬP SỐ GIỜ LÀM (ĐẶC THÙ RIÊNG CỦA PART-TIME)
        float yGio = modalBox.y + 410;
        string lblGio = (modalTrangThai == 5) ? "2. Số giờ tăng ca (OT):" : "2. Số giờ làm thực tế:";
        Color colLblGio = (modalTrangThai == 5) ? Color{120, 30, 180, 255} : BLACK;
        DrawTextEx(myFont, lblGio.c_str(), {modalBox.x + 35, yGio}, 24, 1, colLblGio);
        Rectangle boxGio = {modalBox.x + 300, yGio - 5, 110, 38};
        DrawRectangleRounded(boxGio, 0.3f, 6, Color{248, 250, 252, 255});
        DrawRectangleRoundedLinesEx(boxGio, 0.3f, 6, 1.5f, isModalGioActive ? (modalTrangThai == 5 ? Color{140, 50, 220, 255} : Color{130, 60, 210, 255}) : LIGHTGRAY);

        float yGC = yGio + 50;
        Rectangle boxGC = {modalBox.x + 35, yGC + 32, modalBox.width - 70, 42};

        if (Clicked && !isOpenModalCalendar)
        {
            if (CheckCollisionPointRec(mousePos, boxGio) || (modalTrangThai == 5 && CheckCollisionPointRec(mousePos, {modalBox.x + 55, modalBox.y + 220 + 4 * 36.0f, 400.0f, 30.0f})))
            {
                isModalGioActive = true;
                isModalGhiChuActive = false;
            }
            else if (CheckCollisionPointRec(mousePos, boxGC))
            {
                isModalGhiChuActive = true;
                isModalGioActive = false;
            }
            else
            {
                isModalGioActive = false;
                isModalGhiChuActive = false;
            }
        }
        if (isModalGioActive)
            TypingNumber(modalGio, letterModalGio, 9);
        DrawTextEx(myFont, modalGio, {boxGio.x + 15, boxGio.y + 7}, 24, 1, BLACK);
        if (isModalGioActive && ((int)(GetTime() * 2) % 2 == 0))
        {
            float w = MeasureTextEx(myFont, modalGio, 24, 1).x;
            DrawTextEx(myFont, "_", {boxGio.x + 15 + w, boxGio.y + 7}, 24, 1, Color{130, 60, 210, 255});
        }
        if (modalTrangThai == 5)
            DrawTextEx(myFont, "tiếng (Hệ số OT 1.5x)", {boxGio.x + 125, yGio}, 22, 1, Color{130, 40, 210, 255});
        else
            DrawTextEx(myFont, "tiếng / ca", {boxGio.x + 125, yGio}, 22, 1, DARKGRAY);

        // Nhập Lý do / Ghi chú
        DrawTextEx(myFont, "3. Lý do / Ghi chú:", {modalBox.x + 35, yGC}, 24, 1, BLACK);
        DrawRectangleRounded(boxGC, 0.2f, 6, Color{248, 250, 252, 255});
        DrawRectangleRoundedLinesEx(boxGC, 0.2f, 6, 1.5f, isModalGhiChuActive ? Color{130, 60, 210, 255} : LIGHTGRAY);
        if (isModalGhiChuActive)
            TypingKeys(modalGhiChu, letterModalGhiChu, 99);
        if (modalGhiChu[0] == '\0')
            DrawTextEx(myFont, "Nhập lý do hoặc ghi chú...", {boxGC.x + 15, boxGC.y + 8}, 20, 1, GRAY);
        else
            DrawTextEx(myFont, modalGhiChu, {boxGC.x + 15, boxGC.y + 8}, 22, 1, BLACK);
        if (isModalGhiChuActive && ((int)(GetTime() * 2) % 2 == 0))
        {
            float w = MeasureTextEx(myFont, modalGhiChu, 22, 1).x;
            DrawTextEx(myFont, "_", {boxGC.x + 15 + w, boxGC.y + 8}, 22, 1, Color{130, 60, 210, 255});
        }

        // Nút Cập nhật & Hủy
        float btnY = modalBox.y + modalBox.height - 70;

        Rectangle btnSubmit = {modalBox.x + 160, btnY, 170, 48};
        bool hSub = CheckCollisionPointRec(mousePos, btnSubmit);
        VeNutChucNang(btnSubmit, "Cập nhật", NutStyle::Green, hSub, 4);

        Rectangle btnCancel = {modalBox.x + 370, btnY, 170, 48};
        bool hCan = CheckCollisionPointRec(mousePos, btnCancel);
        VeNutChucNang(btnCancel, "Hủy", NutStyle::Secondary, hCan, 5);

        // Xử lý Cập nhật (Part-Time: lấy số giờ từ ô nhập atof(modalGio), nghỉ phép/vắng 0.0h)
        if (Clicked && !isOpenModalCalendar && CheckCollisionPointRec(mousePos, btnSubmit))
        {
            double g = (modalTrangThai == 3 || modalTrangThai == 4) ? 0.0 : atof(modalGio);
            Date dCanSua(modalDay, modalMonth, modalYear);
            ChamCong *ccCurrent = QL->get_DB()->FindCC(selectedEmp->get_mnv(), dCanSua);
            if (ccCurrent)
            {
                ccCurrent->set_TrangThai(modalTrangThai);
                ccCurrent->set_SoGio(g);
                ccCurrent->set_GhiChu(modalGhiChu);
            }
            else
            {
                QL->get_DB()->Insert(new ChamCong(selectedEmp, dCanSua, modalTrangThai, g, modalGhiChu));
            }
            QL->get_DB()->SaveFileChamCong();
            QL->DongBoChamCong(dCanSua.get_month(), dCanSua.get_year());
            QL->get_DB()->SaveFileEmployee();
            HienThongBao("Cập nhật chấm công Part-Time thành công!", false);
            isOpenModal = false;
            lastModalEmp = nullptr;
        }

        // Xử lý Hủy
        if (Clicked && !openedThisFrame && !isOpenModalCalendar && (CheckCollisionPointRec(mousePos, btnCancel) || !CheckCollisionPointRec(mousePos, modalBox)))
        {
            isOpenModal = false;
            lastModalEmp = nullptr;
        }

        // Lịch con Modal
        if (isOpenModalCalendar)
        {
            Rectangle modalCalRec = {btnModalCal.x, btnModalCal.y + 12, btnModalCal.width, btnModalCal.height};
            bool changed = DrawCalendar(mousePos, modalDay, modalMonth, modalYear, modalCalRec, isOpenModalCalendar);
            if (changed)
            {
                ChamCong *ccNew = QL->get_DB()->FindCC(selectedEmp->get_mnv(), Date(modalDay, modalMonth, modalYear));
                if (ccNew)
                {
                    modalTrangThai = ccNew->get_TrangThai();
                    snprintf(modalGio, sizeof(modalGio), "%.1f", ccNew->get_SoGio());
                    strncpy(modalGhiChu, ccNew->get_GhiChu().c_str(), 99);
                }
                else
                {
                    modalTrangThai = 1;
                    snprintf(modalGio, sizeof(modalGio), "4.0");
                    modalGhiChu[0] = '\0';
                }
                letterModalGio = strlen(modalGio);
                letterModalGhiChu = strlen(modalGhiChu);
            }
        }
    }

    // ================= 9. MODAL XEM CHI TIẾT LỊCH ĐI LÀM CỦA NHÂN VIÊN =================
    if (isOpenModalLich && selectedLichEmp != nullptr)
    {
        VeModalLichNhanVien(mousePos, Clicked, QL, isOpenModalLich, selectedLichEmp, curMonth, curYear, openedLichThisFrame);
    }

    openedThisFrame = false;
    openedLichThisFrame = false;
    openedCalThisFrame = false;
    g_isModalActive = (isOpenModal || isOpenModalLich || isOpenMainCalendar);
}
