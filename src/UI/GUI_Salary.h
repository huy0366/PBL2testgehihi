#pragma once
#include "GUI_Common.h"

void Draw_Screen_ML_FullTime(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_ML_PartTime(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_BL_FullTime(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_BL_PartTime(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_MucLuong(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_BangLuong(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_Salary(QLNV *QL);

void Draw_Screen_BangLuong(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_menuGen);
    s_gen = g_menuGen;
    static bool isOpenFT = true;
    static bool isOpenPT = false;
    if (doReset)
    {
        isOpenFT = true;
        isOpenPT = false;
    }

    // Khung chứa dài hết cỡ chiều ngang (1450px)
    Rectangle panelBang = {330, 230, 1450.0f, 95.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.04f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.04f, 10, Color{242, 245, 252, 255});
    DrawRectangleRoundedLinesEx(panelBang, 0.04f, 10, 1.5f, Color{218, 226, 242, 255});

    // 2 Tab chia đều dài hết cỡ theo chiều ngang
    float tabMargin = 10.0f;
    float tabGap = 10.0f;
    float tabW = (panelBang.width - 2 * tabMargin - tabGap) / 2.0f; // 710px mỗi tab
    float tabH = 75.0f;
    float tabY = panelBang.y + tabMargin;

    Rectangle TabFT = {panelBang.x + tabMargin, tabY, tabW, tabH};
    Rectangle TabPT = {panelBang.x + tabMargin + tabW + tabGap, tabY, tabW, tabH};

    bool hoverFT = CheckCollisionPointRec(mousePos, TabFT);
    bool hoverPT = CheckCollisionPointRec(mousePos, TabPT);

    // Màu sắc nổi bật, không dùng màu trắng để nhìn rõ ràng
    Color cActiveBg = Color{55, 100, 235, 255}; // Xanh dương nổi bật khi chọn
    Color cActiveBorder = Color{40, 80, 210, 255};
    Color cInactiveBg = Color{230, 236, 247, 255}; // Màu xám xanh nhẹ rõ nét khi chưa chọn
    Color cHoverBg = Color{218, 226, 242, 255};    // Màu khi rê chuột
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

    if (isOpenFT)
    {
        Draw_Screen_BL_FullTime(mousePos, Clicked, QL);
    }
    else if (isOpenPT)
    {
        Draw_Screen_BL_PartTime(mousePos, Clicked, QL);
    }
}

void Draw_Screen_MucLuong(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_menuGen);
    s_gen = g_menuGen;
    static bool isOpenFT = true;
    static bool isOpenPT = false;
    if (doReset)
    {
        isOpenFT = true;
        isOpenPT = false;
    }

    // Khung chứa dài hết cỡ chiều ngang (1450px)
    Rectangle panelBang = {330, 230, 1450.0f, 95.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.04f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.04f, 10, Color{242, 245, 252, 255});
    DrawRectangleRoundedLinesEx(panelBang, 0.04f, 10, 1.5f, Color{218, 226, 242, 255});

    // 2 Tab chia đều dài hết cỡ theo chiều ngang
    float tabMargin = 10.0f;
    float tabGap = 10.0f;
    float tabW = (panelBang.width - 2 * tabMargin - tabGap) / 2.0f; // 710px mỗi tab
    float tabH = 75.0f;
    float tabY = panelBang.y + tabMargin;

    Rectangle TabFT = {panelBang.x + tabMargin, tabY, tabW, tabH};
    Rectangle TabPT = {panelBang.x + tabMargin + tabW + tabGap, tabY, tabW, tabH};

    bool hoverFT = CheckCollisionPointRec(mousePos, TabFT);
    bool hoverPT = CheckCollisionPointRec(mousePos, TabPT);

    // Màu sắc nổi bật, không dùng màu trắng để nhìn rõ ràng
    Color cActiveBg = Color{55, 100, 235, 255}; // Xanh dương nổi bật khi chọn
    Color cActiveBorder = Color{40, 80, 210, 255};
    Color cInactiveBg = Color{230, 236, 247, 255}; // Màu xám xanh nhẹ rõ nét khi chưa chọn
    Color cHoverBg = Color{218, 226, 242, 255};    // Màu khi rê chuột
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

    if (isOpenFT)
    {
        Draw_Screen_ML_FullTime(mousePos, Clicked, QL);
    }
    else if (isOpenPT)
    {
        Draw_Screen_ML_PartTime(mousePos, Clicked, QL);
    }
}

void Draw_Screen_ML_FullTime(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static bool isMaVTActive = false;
    static bool isBacActive = false;
    static bool isLuongActive = false;
    static bool needfill = false;
    static List<MucLuong> *dsXoa = nullptr;
    static string selectedMLKey = "";
    static bool hoiXoa = false;

    // --- Combobox Mã VTVL ---
    static bool isDropVT = false; // dropdown đang mở?
    static char searchVT[50] = "\0"; // ô search
    static int letterSearchVT = 0;
    static string selectedMaVT = ""; // giá trị đã chọn

    // --- Combobox Bậc ---
    static bool isDropBac = false;
    static int selectedBac = 0; // 0 = chưa chọn

    static char MaVTInput[50] = "\0";
    static int letterCount_Ma = 0;
    static char BacInput[50] = "\0";
    static int letterCount_Bac = 0;
    static char LuongInput[50] = "\0";
    static int letterCount_Luong = 0;
    static bool OpenThem = false;
    static bool OpenSua = false;
    static bool OpenXoa = false;
    static float scrollY = 0.0f;

    if (doReset)
    {
        isMaVTActive = false;
        isBacActive = false;
        isLuongActive = false;
        needfill = false;
        if (OpenXoa)
            delete dsXoa;
        dsXoa = nullptr;
        selectedMLKey = "";
        hoiXoa = false;
        isDropVT = false;
        searchVT[0] = '\0';
        letterSearchVT = 0;
        selectedMaVT = "";
        isDropBac = false;
        selectedBac = 0;
        MaVTInput[0] = '\0';
        letterCount_Ma = 0;
        BacInput[0] = '\0';
        letterCount_Bac = 0;
        LuongInput[0] = '\0';
        letterCount_Luong = 0;
        OpenThem = false;
        OpenSua = false;
        OpenXoa = false;
        scrollY = 0.0f;
    }

    // =========== BẢNG 1: THÔNG TIN MỨC LƯƠNG FULLTIME ===========
    Rectangle panelBang1 = {330, 335, 1450.0f, 250.0f};
    DrawRectangleRounded({panelBang1.x + 3, panelBang1.y + 4, panelBang1.width, panelBang1.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang1, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang1, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    DrawTextEx(myFont, "Thông tin mức lương FullTime", {360.0f, 345.0f}, 28, 1, Color{20, 25, 35, 255});

    static Texture2D iconML_FT;
    static bool isIconLoaded_FT = false;
    if (!isIconLoaded_FT)
    {
        iconML_FT = LoadTexture("photo/anhto/vtri.png");
        isIconLoaded_FT = true;
    }
    DrawTextureEx(iconML_FT, {360.0f, 385.0f}, 0.0f, 0.6f, WHITE);

    // Ô nhập Mã vị trí
    Rectangle textMaVT = {870, 400, 300, 40};
    DrawTextEx(myFont, "Mã vị trí:", {textMaVT.x - 190, textMaVT.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool maActive = OpenThem && isMaVTActive;
    DrawRectangleRounded(textMaVT, 0.3f, 6, maActive ? Color{248, 250, 252, 255} : (OpenSua ? Color{240, 243, 246, 255} : WHITE));
    DrawRectangleRoundedLinesEx(textMaVT, 0.3f, 6, 1.5f, maActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    ViTriViecLam *vtFound = QL->get_DB()->FindVTVL(MaVTInput);
    if (vtFound != nullptr)
    {
        DrawTextEx(myFont, vtFound->get_TenVTVL().c_str(), {textMaVT.x + 320, textMaVT.y + 9}, 22, 1, DARKGREEN);
    }
    else if (letterCount_Ma > 0)
    {
        DrawTextEx(myFont, "(Chưa có vị trí)", {textMaVT.x + 320, textMaVT.y + 9}, 20, 1, MAROON);
    }

    // Ô nhập Bậc
    Rectangle textBac = {textMaVT.x, textMaVT.y + 55, 300, 40};
    DrawTextEx(myFont, "Bậc vị trí:", {textBac.x - 190, textBac.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool bacActive = OpenThem && isBacActive;
    DrawRectangleRounded(textBac, 0.3f, 6, bacActive ? Color{248, 250, 252, 255} : (OpenSua ? Color{240, 243, 246, 255} : WHITE));
    DrawRectangleRoundedLinesEx(textBac, 0.3f, 6, 1.5f, bacActive ? Color{50, 100, 220, 255} : LIGHTGRAY);
    DrawTextEx(myFont, "(1, 2, 3, 4, 5)", {textBac.x + 320, textBac.y + 9}, 20, 1, DARKGRAY);

    // Ô nhập Lương
    Rectangle textLuong = {textBac.x, textBac.y + 55, 300, 40};
    DrawTextEx(myFont, "Lương tháng:", {textLuong.x - 190, textLuong.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool luongActive = (OpenThem || OpenSua) && isLuongActive;
    DrawRectangleRounded(textLuong, 0.3f, 6, luongActive ? Color{248, 250, 252, 255} : WHITE);
    DrawRectangleRoundedLinesEx(textLuong, 0.3f, 6, 1.5f, luongActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    if (letterCount_Luong > 0)
    {
        long long valLuong = atoll(LuongInput);
        if (valLuong > 0)
        {
            string fmt = FormatSoTien(valLuong) + " đ/tháng";
            DrawTextEx(myFont, fmt.c_str(), {textLuong.x + 320, textLuong.y + 9}, 22, 1, Color{40, 80, 200, 255});
        }
    }

    if (!OpenThem && !OpenSua)
    {
        isMaVTActive = false;
        isBacActive = false;
        isLuongActive = false;
    }
    else if (Clicked)
    {
        if (OpenThem)
        {
            if (CheckCollisionPointRec(mousePos, textMaVT))
            {
                isMaVTActive = true;
                isBacActive = isLuongActive = false;
            }
            else if (CheckCollisionPointRec(mousePos, textBac))
            {
                isBacActive = true;
                isMaVTActive = isLuongActive = false;
            }
            else if (CheckCollisionPointRec(mousePos, textLuong))
            {
                isLuongActive = true;
                isMaVTActive = isBacActive = false;
            }
            else
            {
                isMaVTActive = isBacActive = isLuongActive = false;
            }
        }
        else if (OpenSua)
        {
            isMaVTActive = false;
            isBacActive = false; // Mã vị trí & Bậc không được sửa
            if (CheckCollisionPointRec(mousePos, textLuong))
            {
                isLuongActive = true;
            }
            else
            {
                isLuongActive = false;
            }
        }
    }

    // =========== BẢNG 2: DANH SÁCH MỨC LƯƠNG FULLTIME ===========
    Rectangle panelBang2 = {330, 595, 1450.0f, 330.0f};
    DrawRectangleRounded({panelBang2.x + 3, panelBang2.y + 4, panelBang2.width, panelBang2.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang2, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang2, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    float scrollSpeed = 30.0f;
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        scrollY += wheel * scrollSpeed;
    }
    if (scrollY > 0.0f)
        scrollY = 0.0f;

    int startX = panelBang2.x + 20; // Lề trái
    int startY = panelBang2.y + 20; // Lề trên
    int rowHeight = 60;
    int fontSize = 24;

    int colX[] = {350, 520, 850, 1060, 1370};

    float lech = OpenXoa ? 30.f : 0.f;
    DrawTextEx(myFont, "Mã Vị Trí", {colX[0] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Tên Vị Trí", {colX[1] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Bậc", {colX[2] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Lương Tháng", {colX[3] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Số Nhân Viên", {colX[4] + lech, (float)startY}, fontSize, 1, DARKGRAY);

    DrawLine(startX, startY + 35, 1750, startY + 35, LIGHTGRAY);

    int listStartY = startY + 60;
    int listHeight = GetScreenHeight() - listStartY - 90;

    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    bool canHover = CheckCollisionPointRec(mousePos, listArea);

    float currentY = listStartY + scrollY;

    Node<MucLuong> *current = QL->get_DB()->get_ListML()->get_header()->Next;
    int totalRows = 0;
    MucLuong *selML = nullptr;

    while (current != nullptr)
    {
        if (current->Data && current->Data->get_Loai_NV() == "FullTime")
        {
            MucLuong *ml = current->Data;
            string mvt = ml->get_VTVL() ? ml->get_Ma_VTVL() : "N/A";
            string tenVT = ml->get_VTVL() ? ml->get_VTVL()->get_TenVTVL() : "";
            int bac = ml->get_Bac_VTVL();
            long long luong = (long long)ml->get_Luong();
            int soNV = QL->DemNVThamChieuML(mvt, bac, "FullTime");
            string key = mvt + "_" + to_string(bac);

            Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
            bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
            if (isHover && Clicked && !hoiXoa)
            {
                if (OpenXoa && dsXoa != nullptr)
                {
                    Node<MucLuong> *nd = dsXoa->find_ptr(current->Data);
                    if (nd != nullptr)
                    {
                        dsXoa->remove_item(nd);
                        if (selectedMLKey == key)
                        {
                            if (dsXoa->get_size() > 0)
                            {
                                Node<MucLuong> *last = dsXoa->get_header()->Next;
                                while (last->Next != nullptr)
                                    last = last->Next;
                                string lmvt = last->Data->get_VTVL() ? last->Data->get_Ma_VTVL() : "N/A";
                                selectedMLKey = lmvt + "_" + to_string(last->Data->get_Bac_VTVL());
                                needfill = true;
                            }
                            else
                            {
                                selectedMLKey = "";
                                MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
                                letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
                            }
                        }
                    }
                    else
                    {
                        dsXoa->insert(current->Data);
                        selectedMLKey = key;
                        needfill = true;
                    }
                }
                else
                {
                    selectedMLKey = key;
                    needfill = true;
                }
            }

            bool isSelected = (key == selectedMLKey);
            if (isSelected)
                selML = ml;

            if (OpenXoa && dsXoa != nullptr)
            {
                if (dsXoa->find_ptr(current->Data))
                {
                    DrawRectangleRec(rowRect, Color{255, 230, 230, 255});
                }
                else if (isHover)
                {
                    DrawRectangleRec(rowRect, Color{245, 245, 250, 255});
                }

                Rectangle box = {(float)colX[0] + 2, currentY + 4, 20, 20};
                DrawRectangleRec(box, WHITE);
                DrawRectangleLinesEx(box, 2, DARKGRAY);
                if (dsXoa->find_ptr(current->Data))
                {
                    DrawRectangleRec({box.x + 4, box.y + 4, box.width - 8, box.height - 8}, DARKGREEN);
                }
            }
            else if (isSelected)
            {
                DrawRectangleRec(rowRect, isHover ? Color{180, 195, 230, 255} : Color{200, 210, 235, 255});
            }
            else if (isHover)
            {
                DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
            }

            DrawTextEx(myFont, mvt.c_str(), {colX[0] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, tenVT.c_str(), {colX[1] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, to_string(bac).c_str(), {colX[2] + lech, currentY}, fontSize, 1, BLACK);

            string strLuong = FormatSoTien(luong) + " đ";
            DrawTextEx(myFont, strLuong.c_str(), {colX[3] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, to_string(soNV).c_str(), {colX[4] + lech, currentY}, fontSize, 1, BLACK);
            DrawLine(startX, currentY + 30, GetScreenWidth() - 20, currentY + 30, Fade(LIGHTGRAY, 0.5f));

            currentY += rowHeight;
            totalRows++;
        }
        current = current->Next;
    }

    float totalListHeight = totalRows * rowHeight;
    float maxScroll = listHeight - totalListHeight;
    if (totalListHeight > listHeight && scrollY < maxScroll)
    {
        scrollY = maxScroll;
    }
    else if (totalListHeight <= listHeight)
    {
        scrollY = 0.0f;
    }

    EndScissorMode();

    if (needfill && selML != nullptr)
    {
        strncpy(MaVTInput, selML->get_Ma_VTVL().c_str(), 49);
        letterCount_Ma = strlen(MaVTInput);
        MaVTInput[letterCount_Ma] = '\0';

        strncpy(BacInput, to_string(selML->get_Bac_VTVL()).c_str(), 49);
        letterCount_Bac = strlen(BacInput);
        BacInput[letterCount_Bac] = '\0';

        snprintf(LuongInput, sizeof(LuongInput), "%lld", (long long)selML->get_Luong());
        letterCount_Luong = strlen(LuongInput);

        needfill = false;
    }

    if (OpenThem)
    {
        Typing(isMaVTActive, MaVTInput, letterCount_Ma, mousePos, textMaVT);
        HieuUngGo(isMaVTActive, textMaVT, MaVTInput, 28);

        Typing(isBacActive, BacInput, letterCount_Bac, mousePos, textBac);
        HieuUngGo(isBacActive, textBac, BacInput, 28);

        Typing(isLuongActive, LuongInput, letterCount_Luong, mousePos, textLuong);
        HieuUngGo(isLuongActive, textLuong, LuongInput, 22);
    }
    else if (OpenSua && selML != nullptr)
    {
        DrawTextEx(myFont, MaVTInput, {textMaVT.x + 10, textMaVT.y + 9}, 22, 1, DARKGRAY);
        DrawTextEx(myFont, BacInput, {textBac.x + 10, textBac.y + 9}, 22, 1, DARKGRAY);

        Typing(isLuongActive, LuongInput, letterCount_Luong, mousePos, textLuong);
        HieuUngGo(isLuongActive, textLuong, LuongInput, 22);
    }
    else if (selML != nullptr || MaVTInput[0] != '\0')
    {
        DrawTextEx(myFont, MaVTInput, {textMaVT.x + 10, textMaVT.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, BacInput, {textBac.x + 10, textBac.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, LuongInput, {textLuong.x + 10, textLuong.y + 9}, 22, 1, BLACK);
    }

    // =========== CÁC NÚT ĐIỀU KHIỂN DƯỚI CÙNG ===========
    Rectangle btnThemMucLuong = {350, 940, 280, 50};
    Rectangle btnSuaMucLuong = {660, 940, 280, 50};
    Rectangle btnXoaMucLuong = {970, 940, 280, 50};

    Rectangle btnXacNhan = {350, 940, 230, 50};
    Rectangle btnHuy = {610, 940, 230, 50};

    Rectangle btnHuyXoa = {350, 940, 230, 50};
    Rectangle btnXacNhanXoa = {610, 940, 230, 50};
    if (OpenXoa)
    {
        bool hoverHuy = CheckCollisionPointRec(mousePos, btnHuyXoa);
        VeNutChucNang(btnHuyXoa, "Hủy xóa", NutStyle::Secondary, hoverHuy, 5);

        bool hoverXN = CheckCollisionPointRec(mousePos, btnXacNhanXoa);
        VeNutChucNang(btnXacNhanXoa, "Xác nhận xoá", NutStyle::Red, hoverXN, 3);
    }
    else if (OpenSua || OpenThem)
    {
        bool hoverXN = CheckCollisionPointRec(mousePos, btnXacNhan);
        VeNutChucNang(btnXacNhan, "Xác nhận", NutStyle::Green, hoverXN, 4);

        bool hoverHuy = CheckCollisionPointRec(mousePos, btnHuy);
        VeNutChucNang(btnHuy, "Hủy", NutStyle::Secondary, hoverHuy, 5);
    }
    else
    {
        bool hoverThem = CheckCollisionPointRec(mousePos, btnThemMucLuong);
        VeNutChucNang(btnThemMucLuong, "Thêm Mức Lương", NutStyle::Green, hoverThem, 1);

        bool hoverSua = CheckCollisionPointRec(mousePos, btnSuaMucLuong);
        VeNutChucNang(btnSuaMucLuong, "Sửa Mức Lương", NutStyle::Blue, hoverSua, 2);

        bool hoverXoa = CheckCollisionPointRec(mousePos, btnXoaMucLuong);
        VeNutChucNang(btnXoaMucLuong, "Xóa Mức Lương", NutStyle::Red, hoverXoa, 3);
    }
    if (OpenXoa)
    {
        if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnHuyXoa))
        {
            delete dsXoa;
            dsXoa = nullptr;
            OpenXoa = false;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
        else if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnXacNhanXoa))
        {
            if (dsXoa == nullptr || dsXoa->get_size() == 0)
                HienThongBao("Chưa chọn mức lương nào để xóa!", true);
            else
                hoiXoa = true;
        }
    }
    else if (Clicked && OpenThem || OpenSua)
    {
        if (Clicked && CheckCollisionPointRec(mousePos, btnXacNhan))
        {
            if (OpenThem)
            {
                ViTriViecLam *vt = QL->get_DB()->FindVTVL(MaVTInput);
                if (vt == nullptr)
                {
                    HienThongBao("Mã vị trí không tồn tại trong hệ thống!", true);
                }
                else
                {
                    int bac = atoi(BacInput);
                    double luong = atof(LuongInput);
                    if (bac <= 0)
                    {
                        HienThongBao("Bậc vị trí phải lớn hơn 0!", true);
                    }
                    else if (luong <= 0)
                    {
                        HienThongBao("Mức lương phải lớn hơn 0!", true);
                    }
                    else
                    {
                        MucLuong *mlNew = new MucLuong_FullTime(vt, bac, luong);
                        try
                        {
                            QL->ThemMucLuong(mlNew);
                            QL->get_DB()->SaveFileML();
                            OpenThem = false;
                            isMaVTActive = isBacActive = isLuongActive = false;
                            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
                            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
                            HienThongBao("Thêm mức lương mới thành công!", false);
                        }
                        catch (const string &loi)
                        {
                            delete mlNew;
                            HienThongBao(loi, true);
                        }
                    }
                }
            }
            else if (OpenSua && selML != nullptr)
            {
                double luong = atof(LuongInput);
                if (luong <= 0)
                {
                    HienThongBao("Mức lương phải lớn hơn 0!", true);
                }
                else
                {

                    MucLuong *tam = new MucLuong_FullTime(selML->get_VTVL(), selML->get_Bac_VTVL(), luong);
                    try
                    {
                        QL->SuaMucLuong(tam);
                        QL->get_DB()->SaveFileML();
                        OpenSua = false;
                        isMaVTActive = isBacActive = isLuongActive = false;
                        MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
                        letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
                        HienThongBao("Cập nhật mức lương thành công!", false);
                    }
                    catch (const string &loi)
                    {
                        HienThongBao(loi, true);
                    }
                    delete tam;
                }
            }
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnHuy))
        {
            OpenThem = OpenSua = false;
            isMaVTActive = isBacActive = isLuongActive = false;
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
    }
    else
    {
        if (Clicked && CheckCollisionPointRec(mousePos, btnThemMucLuong))
        {
            OpenThem = true;
            isMaVTActive = true;
            isBacActive = isLuongActive = false;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnSuaMucLuong))
        {
            if (selML == nullptr)
            {
                HienThongBao("Vui lòng chọn 1 mức lương trong danh sách để sửa!", true);
            }
            else
            {
                OpenSua = true;
                isMaVTActive = isBacActive = false;
                isLuongActive = true;
            }
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnXoaMucLuong))
        {
            OpenXoa = true;
            dsXoa = new List<MucLuong>;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
            isMaVTActive = isBacActive = isLuongActive = false;
        }
    }

    DrawTextEx(myFont, ("Tổng mức lương: " + to_string(totalRows)).c_str(), {1520, 955}, 20, 1, DARKGRAY);

    if (OpenXoa && dsXoa != nullptr)
    {
        if (XacNhan("Bạn có chắc muốn xóa " + to_string(dsXoa->get_size()) + " mức lương đã chọn?", hoiXoa))
        {
            int dem = 0;
            string loiCuoi = "";
            for (Node<MucLuong> *p = dsXoa->get_header()->Next; p != nullptr; p = p->Next)
            {
                try
                {
                    QL->XoaMucLuong(p->Data);
                    dem++;
                }
                catch (const string &loi)
                {
                    loiCuoi = loi;
                }
            }

            if (dem > 0)
            {
                QL->get_DB()->SaveFileML();
                if (loiCuoi.empty())
                    HienThongBao("Đã xóa " + to_string(dem) + " mức lương thành công!", false);
                else
                    HienThongBao("Đã xóa " + to_string(dem) + " mức lương. " + loiCuoi, true);
            }
            else
                HienThongBao(loiCuoi.empty() ? "Xóa không thành công!" : loiCuoi, true);

            delete dsXoa;
            dsXoa = nullptr;
            OpenXoa = false;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
    }
    g_isModalActive = hoiXoa;
}

void Draw_Screen_ML_PartTime(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static bool isMaVTActive = false;
    static bool isBacActive = false;
    static bool isLuongActive = false;
    static bool needfill = false;
    static List<MucLuong> *dsXoa = nullptr;
    static string selectedMLKey = "";
    static bool hoiXoa = false;
    static char MaVTInput[50] = "\0";
    static int letterCount_Ma = 0;
    static char BacInput[50] = "\0";
    static int letterCount_Bac = 0;
    static char LuongInput[50] = "\0";
    static int letterCount_Luong = 0;
    static bool OpenThem = false;
    static bool OpenSua = false;
    static bool OpenXoa = false;
    static float scrollY = 0.0f;

    if (doReset)
    {
        isMaVTActive = false;
        isBacActive = false;
        isLuongActive = false;
        needfill = false;
        if (OpenXoa)
            delete dsXoa;
        dsXoa = nullptr;
        selectedMLKey = "";
        hoiXoa = false;
        MaVTInput[0] = '\0';
        letterCount_Ma = 0;
        BacInput[0] = '\0';
        letterCount_Bac = 0;
        LuongInput[0] = '\0';
        letterCount_Luong = 0;
        OpenThem = false;
        OpenSua = false;
        OpenXoa = false;
        scrollY = 0.0f;
    }

    // =========== BẢNG 1: THÔNG TIN MỨC LƯƠNG PARTTIME ===========
    Rectangle panelBang1 = {330, 335, 1450.0f, 250.0f};
    DrawRectangleRounded({panelBang1.x + 3, panelBang1.y + 4, panelBang1.width, panelBang1.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang1, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang1, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    DrawTextEx(myFont, "Thông tin mức lương PartTime", {360.0f, 345.0f}, 28, 1, Color{20, 25, 35, 255});

    static Texture2D iconML_PT;
    static bool isIconLoaded_PT = false;
    if (!isIconLoaded_PT)
    {
        iconML_PT = LoadTexture("photo/anhto/vtri.png");
        isIconLoaded_PT = true;
    }
    DrawTextureEx(iconML_PT, {360.0f, 385.0f}, 0.0f, 0.6f, WHITE);

    // Ô nhập Mã vị trí
    Rectangle textMaVT = {870, 400, 300, 40};
    DrawTextEx(myFont, "Mã vị trí:", {textMaVT.x - 190, textMaVT.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool maActive = OpenThem && isMaVTActive;
    DrawRectangleRounded(textMaVT, 0.3f, 6, maActive ? Color{248, 250, 252, 255} : (OpenSua ? Color{240, 243, 246, 255} : WHITE));
    DrawRectangleRoundedLinesEx(textMaVT, 0.3f, 6, 1.5f, maActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    ViTriViecLam *vtFound = QL->get_DB()->FindVTVL(MaVTInput);
    if (vtFound != nullptr)
    {
        DrawTextEx(myFont, vtFound->get_TenVTVL().c_str(), {textMaVT.x + 320, textMaVT.y + 9}, 22, 1, DARKGREEN);
    }
    else if (letterCount_Ma > 0)
    {
        DrawTextEx(myFont, "(Chưa có vị trí)", {textMaVT.x + 320, textMaVT.y + 9}, 20, 1, MAROON);
    }

    // Ô nhập Bậc
    Rectangle textBac = {textMaVT.x, textMaVT.y + 55, 300, 40};
    DrawTextEx(myFont, "Bậc vị trí:", {textBac.x - 190, textBac.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool bacActive = OpenThem && isBacActive;
    DrawRectangleRounded(textBac, 0.3f, 6, bacActive ? Color{248, 250, 252, 255} : (OpenSua ? Color{240, 243, 246, 255} : WHITE));
    DrawRectangleRoundedLinesEx(textBac, 0.3f, 6, 1.5f, bacActive ? Color{50, 100, 220, 255} : LIGHTGRAY);
    DrawTextEx(myFont, "(1, 2, 3, 4, 5)", {textBac.x + 320, textBac.y + 9}, 20, 1, DARKGRAY);

    // Ô nhập Lương
    Rectangle textLuong = {textBac.x, textBac.y + 55, 300, 40};
    DrawTextEx(myFont, "Lương giờ:", {textLuong.x - 190, textLuong.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool luongActive = (OpenThem || OpenSua) && isLuongActive;
    DrawRectangleRounded(textLuong, 0.3f, 6, luongActive ? Color{248, 250, 252, 255} : WHITE);
    DrawRectangleRoundedLinesEx(textLuong, 0.3f, 6, 1.5f, luongActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    if (letterCount_Luong > 0)
    {
        long long valLuong = atoll(LuongInput);
        if (valLuong > 0)
        {
            string fmt = FormatSoTien(valLuong) + " đ/h";
            DrawTextEx(myFont, fmt.c_str(), {textLuong.x + 320, textLuong.y + 9}, 22, 1, Color{40, 80, 200, 255});
        }
    }

    if (!OpenThem && !OpenSua)
    {
        isMaVTActive = false;
        isBacActive = false;
        isLuongActive = false;
    }
    else if (Clicked)
    {
        if (OpenThem)
        {
            if (CheckCollisionPointRec(mousePos, textMaVT))
            {
                isMaVTActive = true;
                isBacActive = isLuongActive = false;
            }
            else if (CheckCollisionPointRec(mousePos, textBac))
            {
                isBacActive = true;
                isMaVTActive = isLuongActive = false;
            }
            else if (CheckCollisionPointRec(mousePos, textLuong))
            {
                isLuongActive = true;
                isMaVTActive = isBacActive = false;
            }
            else
            {
                isMaVTActive = isBacActive = isLuongActive = false;
            }
        }
        else if (OpenSua)
        {
            isMaVTActive = false;
            isBacActive = false; // Mã vị trí & Bậc không được sửa
            if (CheckCollisionPointRec(mousePos, textLuong))
            {
                isLuongActive = true;
            }
            else
            {
                isLuongActive = false;
            }
        }
    }

    // =========== BẢNG 2: DANH SÁCH MỨC LƯƠNG PARTTIME ===========
    Rectangle panelBang2 = {330, 595, 1450.0f, 330.0f};
    DrawRectangleRounded({panelBang2.x + 3, panelBang2.y + 4, panelBang2.width, panelBang2.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang2, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang2, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    float scrollSpeed = 30.0f;
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        scrollY += wheel * scrollSpeed;
    }
    if (scrollY > 0.0f)
        scrollY = 0.0f;

    int startX = panelBang2.x + 20; // Lề trái
    int startY = panelBang2.y + 20; // Lề trên
    int rowHeight = 60;
    int fontSize = 24;

    int colX[] = {350, 520, 850, 1060, 1370};

    float lech = OpenXoa ? 30.f : 0.f;
    DrawTextEx(myFont, "Mã Vị Trí", {colX[0] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Tên Vị Trí", {colX[1] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Bậc", {colX[2] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Lương Theo Giờ", {colX[3] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Số Nhân Viên", {colX[4] + lech, (float)startY}, fontSize, 1, DARKGRAY);

    DrawLine(startX, startY + 35, 1750, startY + 35, LIGHTGRAY);

    int listStartY = startY + 60;
    int listHeight = GetScreenHeight() - listStartY - 90;

    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    bool canHover = CheckCollisionPointRec(mousePos, listArea);

    float currentY = listStartY + scrollY;

    Node<MucLuong> *current = QL->get_DB()->get_ListML()->get_header()->Next;
    int totalRows = 0;
    MucLuong *selML = nullptr;

    while (current != nullptr)
    {
        if (current->Data && current->Data->get_Loai_NV() == "PartTime")
        {
            MucLuong *ml = current->Data;
            string mvt = ml->get_VTVL() ? ml->get_Ma_VTVL() : "N/A";
            string tenVT = ml->get_VTVL() ? ml->get_VTVL()->get_TenVTVL() : "";
            int bac = ml->get_Bac_VTVL();
            long long luong = (long long)ml->get_Luong();
            int soNV = QL->DemNVThamChieuML(mvt, bac, "PartTime");
            string key = mvt + "_" + to_string(bac);

            Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
            bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
            if (isHover && Clicked && !hoiXoa)
            {
                if (OpenXoa && dsXoa != nullptr)
                {
                    Node<MucLuong> *nd = dsXoa->find_ptr(current->Data);
                    if (nd != nullptr)
                    {
                        dsXoa->remove_item(nd);
                        if (selectedMLKey == key)
                        {
                            if (dsXoa->get_size() > 0)
                            {
                                Node<MucLuong> *last = dsXoa->get_header()->Next;
                                while (last->Next != nullptr)
                                    last = last->Next;
                                string lmvt = last->Data->get_VTVL() ? last->Data->get_Ma_VTVL() : "N/A";
                                selectedMLKey = lmvt + "_" + to_string(last->Data->get_Bac_VTVL());
                                needfill = true;
                            }
                            else
                            {
                                selectedMLKey = "";
                                MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
                                letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
                            }
                        }
                    }
                    else
                    {
                        dsXoa->insert(current->Data);
                        selectedMLKey = key;
                        needfill = true;
                    }
                }
                else
                {
                    selectedMLKey = key;
                    needfill = true;
                }
            }

            bool isSelected = (key == selectedMLKey);
            if (isSelected)
                selML = ml;

            if (OpenXoa && dsXoa != nullptr)
            {
                if (dsXoa->find_ptr(current->Data))
                {
                    DrawRectangleRec(rowRect, Color{255, 230, 230, 255});
                }
                else if (isHover)
                {
                    DrawRectangleRec(rowRect, Color{245, 245, 250, 255});
                }

                Rectangle box = {(float)colX[0] + 2, currentY + 4, 20, 20};
                DrawRectangleRec(box, WHITE);
                DrawRectangleLinesEx(box, 2, DARKGRAY);
                if (dsXoa->find_ptr(current->Data))
                {
                    DrawRectangleRec({box.x + 4, box.y + 4, box.width - 8, box.height - 8}, DARKGREEN);
                }
            }
            else if (isSelected)
            {
                DrawRectangleRec(rowRect, isHover ? Color{180, 195, 230, 255} : Color{200, 210, 235, 255});
            }
            else if (isHover)
            {
                DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
            }

            DrawTextEx(myFont, mvt.c_str(), {colX[0] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, tenVT.c_str(), {colX[1] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, to_string(bac).c_str(), {colX[2] + lech, currentY}, fontSize, 1, BLACK);

            string strLuong = FormatSoTien(luong) + " đ/h";
            DrawTextEx(myFont, strLuong.c_str(), {colX[3] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, to_string(soNV).c_str(), {colX[4] + lech, currentY}, fontSize, 1, BLACK);
            DrawLine(startX, currentY + 30, GetScreenWidth() - 20, currentY + 30, Fade(LIGHTGRAY, 0.5f));

            currentY += rowHeight;
            totalRows++;
        }
        current = current->Next;
    }

    float totalListHeight = totalRows * rowHeight;
    float maxScroll = listHeight - totalListHeight;
    if (totalListHeight > listHeight && scrollY < maxScroll)
    {
        scrollY = maxScroll;
    }
    else if (totalListHeight <= listHeight)
    {
        scrollY = 0.0f;
    }

    EndScissorMode();

    if (needfill && selML != nullptr)
    {
        strncpy(MaVTInput, selML->get_Ma_VTVL().c_str(), 49);
        letterCount_Ma = strlen(MaVTInput);
        MaVTInput[letterCount_Ma] = '\0';

        strncpy(BacInput, to_string(selML->get_Bac_VTVL()).c_str(), 49);
        letterCount_Bac = strlen(BacInput);
        BacInput[letterCount_Bac] = '\0';

        snprintf(LuongInput, sizeof(LuongInput), "%lld", (long long)selML->get_Luong());
        letterCount_Luong = strlen(LuongInput);

        needfill = false;
    }

    if (OpenThem)
    {
        Typing(isMaVTActive, MaVTInput, letterCount_Ma, mousePos, textMaVT);
        HieuUngGo(isMaVTActive, textMaVT, MaVTInput, 22);

        Typing(isBacActive, BacInput, letterCount_Bac, mousePos, textBac);
        HieuUngGo(isBacActive, textBac, BacInput, 22);

        Typing(isLuongActive, LuongInput, letterCount_Luong, mousePos, textLuong);
        HieuUngGo(isLuongActive, textLuong, LuongInput, 22);
    }
    else if (OpenSua && selML != nullptr)
    {
        DrawTextEx(myFont, MaVTInput, {textMaVT.x + 10, textMaVT.y + 9}, 22, 1, DARKGRAY);
        DrawTextEx(myFont, BacInput, {textBac.x + 10, textBac.y + 9}, 22, 1, DARKGRAY);

        Typing(isLuongActive, LuongInput, letterCount_Luong, mousePos, textLuong);
        HieuUngGo(isLuongActive, textLuong, LuongInput, 22);
    }
    else if (selML != nullptr || MaVTInput[0] != '\0')
    {
        DrawTextEx(myFont, MaVTInput, {textMaVT.x + 10, textMaVT.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, BacInput, {textBac.x + 10, textBac.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, LuongInput, {textLuong.x + 10, textLuong.y + 9}, 22, 1, BLACK);
    }

    // =========== CÁC NÚT ĐIỀU KHIỂN DƯỚI CÙNG ===========
    Rectangle btnThemMucLuong = {350, 940, 280, 50};
    Rectangle btnSuaMucLuong = {660, 940, 280, 50};
    Rectangle btnXoaMucLuong = {970, 940, 280, 50};

    Rectangle btnXacNhan = {350, 940, 230, 50};
    Rectangle btnHuy = {610, 940, 230, 50};

    Rectangle btnHuyXoa = {350, 940, 230, 50};
    Rectangle btnXacNhanXoa = {610, 940, 230, 50};

    if (OpenXoa)
    {
        bool hoverHuy = CheckCollisionPointRec(mousePos, btnHuyXoa);
        VeNutChucNang(btnHuyXoa, "Hủy xóa", NutStyle::Secondary, hoverHuy, 5);

        bool hoverXN = CheckCollisionPointRec(mousePos, btnXacNhanXoa);
        VeNutChucNang(btnXacNhanXoa, "Xác nhận xoá", NutStyle::Red, hoverXN, 3);
    }
    else if (OpenSua || OpenThem)
    {
        bool hoverXN = CheckCollisionPointRec(mousePos, btnXacNhan);
        VeNutChucNang(btnXacNhan, "Xác nhận", NutStyle::Green, hoverXN, 4);

        bool hoverHuy = CheckCollisionPointRec(mousePos, btnHuy);
        VeNutChucNang(btnHuy, "Hủy", NutStyle::Secondary, hoverHuy, 5);
    }
    else
    {
        bool hoverThem = CheckCollisionPointRec(mousePos, btnThemMucLuong);
        VeNutChucNang(btnThemMucLuong, "Thêm Mức Lương", NutStyle::Green, hoverThem, 1);

        bool hoverSua = CheckCollisionPointRec(mousePos, btnSuaMucLuong);
        VeNutChucNang(btnSuaMucLuong, "Sửa Mức Lương", NutStyle::Blue, hoverSua, 2);

        bool hoverXoa = CheckCollisionPointRec(mousePos, btnXoaMucLuong);
        VeNutChucNang(btnXoaMucLuong, "Xóa Mức Lương", NutStyle::Red, hoverXoa, 3);
    }
    if (OpenXoa)
    {
        if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnHuyXoa))
        {
            delete dsXoa;
            dsXoa = nullptr;
            OpenXoa = false;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
        else if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnXacNhanXoa))
        {
            if (dsXoa == nullptr || dsXoa->get_size() == 0)
                HienThongBao("Chưa chọn mức lương nào để xóa!", true);
            else
                hoiXoa = true;
        }
    }
    else if (Clicked && OpenThem || OpenSua)
    {
        if (Clicked && CheckCollisionPointRec(mousePos, btnXacNhan))
        {
            if (OpenThem)
            {
                ViTriViecLam *vt = QL->get_DB()->FindVTVL(MaVTInput);
                if (vt == nullptr)
                {
                    HienThongBao("Mã vị trí không tồn tại trong hệ thống!", true);
                }
                else
                {
                    int bac = atoi(BacInput);
                    double luong = atof(LuongInput);
                    if (bac <= 0)
                    {
                        HienThongBao("Bậc vị trí phải lớn hơn 0!", true);
                    }
                    else if (luong <= 0)
                    {
                        HienThongBao("Mức lương phải lớn hơn 0!", true);
                    }
                    else
                    {
                        MucLuong *mlNew = new MucLuong_PartTime(vt, bac, luong);
                        try
                        {
                            QL->ThemMucLuong(mlNew);
                            QL->get_DB()->SaveFileML();
                            OpenThem = false;
                            isMaVTActive = isBacActive = isLuongActive = false;
                            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
                            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
                            HienThongBao("Thêm mức lương mới thành công!", false);
                        }
                        catch (const string &loi)
                        {
                            delete mlNew;
                            HienThongBao(loi, true);
                        }
                    }
                }
            }
            else if (OpenSua && selML != nullptr)
            {
                double luong = atof(LuongInput);
                if (luong <= 0)
                {
                    HienThongBao("Mức lương phải lớn hơn 0!", true);
                }
                else
                {

                    MucLuong *tam = new MucLuong_PartTime(selML->get_VTVL(), selML->get_Bac_VTVL(), luong);
                    try
                    {
                        QL->SuaMucLuong(tam);
                        QL->get_DB()->SaveFileML();
                        OpenSua = false;
                        isMaVTActive = isBacActive = isLuongActive = false;
                        MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
                        letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
                        HienThongBao("Cập nhật mức lương thành công!", false);
                    }
                    catch (const string &loi)
                    {
                        HienThongBao(loi, true);
                    }
                    delete tam;
                }
            }
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnHuy))
        {
            OpenThem = OpenSua = false;
            isMaVTActive = isBacActive = isLuongActive = false;
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
    }
    else
    {
        if (Clicked && CheckCollisionPointRec(mousePos, btnThemMucLuong))
        {
            OpenThem = true;
            isMaVTActive = true;
            isBacActive = isLuongActive = false;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnSuaMucLuong))
        {
            if (selML == nullptr)
            {
                HienThongBao("Vui lòng chọn 1 mức lương trong danh sách để sửa!", true);
            }
            else
            {
                OpenSua = true;
                isMaVTActive = isBacActive = false;
                isLuongActive = true;
            }
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnXoaMucLuong))
        {
            OpenXoa = true;
            dsXoa = new List<MucLuong>;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
            isMaVTActive = isBacActive = isLuongActive = false;
        }
    }

    DrawTextEx(myFont, ("Tổng mức lương: " + to_string(totalRows)).c_str(), {1520, 955}, 20, 1, DARKGRAY);

    if (OpenXoa && dsXoa != nullptr)
    {
        if (XacNhan("Bạn có chắc muốn xóa " + to_string(dsXoa->get_size()) + " mức lương đã chọn?", hoiXoa))
        {
            int dem = 0;
            string loiCuoi = "";
            for (Node<MucLuong> *p = dsXoa->get_header()->Next; p != nullptr; p = p->Next)
            {
                try
                {
                    QL->XoaMucLuong(p->Data);
                    dem++;
                }
                catch (const string &loi)
                {
                    loiCuoi = loi;
                }
            }

            if (dem > 0)
            {
                QL->get_DB()->SaveFileML();
                if (loiCuoi.empty())
                    HienThongBao("Đã xóa " + to_string(dem) + " mức lương thành công!", false);
                else
                    HienThongBao("Đã xóa " + to_string(dem) + " mức lương. " + loiCuoi, true);
            }
            else
                HienThongBao(loiCuoi.empty() ? "Xóa không thành công!" : loiCuoi, true);

            delete dsXoa;
            dsXoa = nullptr;
            OpenXoa = false;
            selectedMLKey = "";
            MaVTInput[0] = BacInput[0] = LuongInput[0] = '\0';
            letterCount_Ma = letterCount_Bac = letterCount_Luong = 0;
        }
    }
    g_isModalActive = hoiXoa;
}
// Hàm format số có dấu chấm phân cách hàng nghìn (VD: 8450000 -> "8.450.000")

// ================= HỆ THỐNG XUẤT VÀ TRA CỨU BẢNG LƯƠNG THEO THÁNG =================
static int salaryMonth = month;
static int salaryYear = year;

void Draw_Screen_BL_FullTime(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static long long tongluong = 0;
    static bool isChucVuOpen1 = false;
    static int selectedChucVuIndex1 = 0;
    static bool isPhongOpen1 = false;
    static int selectedPhongIndex1 = 0;
    static bool isHoTenActive1 = false;
    static char hoTenInput1[50] = "\0";
    static int letterCount1 = 0;
    static bool isSortOpen1 = false;
    static int selectedSortIndex1 = 0;
    static string selectedMNV_FT = "";
    static bool isOpenChiTiet = false;
    static bool isEditingThuong = false;
    static bool isThuongActive = false;
    static char thuongInput[20] = "";
    static int thuongLetterCount = 0;
    static string lastSelectedMNV = "";
    static string tieuchi_CV = "";
    static string tieuchi_PB = "";
    static float scrollY = 0.0f;

    if (doReset)
    {
        tongluong = 0;
        isChucVuOpen1 = false;
        selectedChucVuIndex1 = 0;
        isPhongOpen1 = false;
        selectedPhongIndex1 = 0;
        isHoTenActive1 = false;
        hoTenInput1[0] = '\0';
        letterCount1 = 0;
        isSortOpen1 = false;
        selectedSortIndex1 = 0;
        selectedMNV_FT = "";
        isOpenChiTiet = false;
        isEditingThuong = false;
        isThuongActive = false;
        thuongInput[0] = '\0';
        thuongLetterCount = 0;
        scrollY = 0.0f;
    }

    Rectangle panelBang = {330, 345, 1450.0f, 640.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});
    string default_choice = "Tất cả";

    // =========== COMBO CHỨC VỤ ===========
    Rectangle comboChucVu1 = {350, 400, 250, 45};

    // =========== COMBO PHÒNG BAN ===========
    Rectangle comboPhong1 = {620, 400, 250, 45};

    // =========== Ô TÌM KIẾM ===========
    Rectangle textHoTen1 = {890, 400, 350, 45};

    // =========== COMBO SẮP XẾP LƯƠNG (CHỈ TĂNG HOẶC GIẢM) ===========
    Rectangle comboSort1 = {1290, 400, 260, 45};
    string dsSort[] = {"...", "Lương tăng dần", "Lương giảm dần"};
    int nSort = 2;

    // =========== TRẠNG THÁI CHỌN NHÂN VIÊN & CHI TIẾT ===========
    bool openedThisFrame = false; // Cờ chống nháy khi vừa bấm mở modal
    if (lastSelectedMNV != selectedMNV_FT)
    {
        lastSelectedMNV = selectedMNV_FT;
        isEditingThuong = false;
        isThuongActive = false;
    }

    // =========== CẤU HÌNH BẢNG ===========
    float scrollSpeed = 30.0f;

    if (selectedChucVuIndex1 != 0)
    {
        tieuchi_CV = (*QL->get_DB()->get_ListCV())[selectedChucVuIndex1 - 1]->Data->get_MaChucVu();
        scrollY = 0.0f;
        tongluong = 0;
    }
    else
    {
        tieuchi_CV = "";
        tongluong = 0;
    }

    if (selectedPhongIndex1 != 0)
    {
        tieuchi_PB = (*QL->get_DB()->get_ListPB())[selectedPhongIndex1 - 1]->Data->get_MaPhongBan();
        scrollY = 0.0f;
        tongluong = 0;
    }
    else
    {
        tongluong = 0;
        tieuchi_PB = "";
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
        scrollY += wheel * scrollSpeed;
    if (scrollY > 0.0f)
        scrollY = 0.0f;

    int startX = 350;
    int startY = 480;
    int rowHeight = 60;
    int fontSize = 24;

    float colX[] = {350.f, 470.f, 730.f, 890.f, 1100.f, 1350.f, 1450.f, 1600.f};

    // =========== HEADER ===========
    DrawTextEx(myFont, "Mã NV", {colX[0], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Họ tên", {colX[1], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Phòng ban", {colX[2], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Chức vụ", {colX[3], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Vị trí", {colX[4], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Hệ số", {colX[5], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Ngày công", {colX[6], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Tổng lương", {colX[7], (float)startY}, fontSize, 1, DARKGRAY);
    DrawLine(startX, startY + 30, 1780, startY + 30, LIGHTGRAY);

    // =========== THU THẬP VÀ SẮP XẾP DANH SÁCH FULLTIME ===========

    // Sắp xếp lương theo yêu cầu (1: Tăng dần, 2: Giảm dần)
    if (selectedSortIndex1 == 1)
    {
        QL->SapXep(TieuChiSapXep::LUONGFT_TANG);
    }
    else if (selectedSortIndex1 == 2)
    {
        QL->SapXep(TieuChiSapXep::LUONGFT_GIAM);
    }

    // =========== VẼ DANH SÁCH NHÂN VIÊN ===========
    int listStartY = startY + 35;
    int listHeight = GetScreenHeight() - listStartY - 90;

    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    bool canHover = !isOpenChiTiet && !isChucVuOpen1 && !isPhongOpen1 && !isSortOpen1 && CheckCollisionPointRec(mousePos, listArea);

    float currentY = listStartY + scrollY;
    int totalRows = 0;
    Employee *selEmp = nullptr;

    if (!selectedMNV_FT.empty())
        selEmp = QL->TimTheoMa(selectedMNV_FT);

    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next;
    while (p != nullptr)
    {
        if (p->Data->get_LoaiNV() == "FullTime" && CheckEmployee(p->Data, tieuchi_CV, tieuchi_PB, hoTenInput1))
        {
            FullTime *ft = dynamic_cast<FullTime *>(p->Data);
            string mnv = ft->get_mnv();
            string name = ft->get_name();
            string phong = ft->get_PhongBan() ? ft->get_PhongBan()->get_TenPhongBan() : "";
            string cv = ft->get_ChucVu() ? ft->get_ChucVu()->get_TenChucVu() : "";
            string vitri = ft->get_ViTri() ? ft->get_ViTri()->get_TenVTVL() : "";

            ostringstream oss;
            oss << ft->get_HeSo();

            // Tính ngày công, OT và lương theo salaryMonth / salaryYear qua QLNV
            double ncDung = 0.0;
            double gioOTThang = 0.0;
            long long tienOT = 0;
            long long luong = QL->TinhLuongThang(ft, salaryMonth, salaryYear, ncDung, gioOTThang, tienOT);
            tongluong += luong;

            string strHeSo = oss.str();
            ostringstream ossNC;
            if (ncDung == (int)ncDung)
                ossNC << (int)ncDung;
            else
                ossNC << fixed << setprecision(1) << ncDung;
            string strNgayCong = ossNC.str();
            string strLuong = FormatSoTien(luong);

            // ----- HOVER + CHỌN DÒNG -----
            Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
            bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
            if (isHover && Clicked && !isOpenChiTiet)
            {
                selectedMNV_FT = mnv;
                selEmp = ft;
            }
            bool isSelected = (mnv == selectedMNV_FT);

            if (isSelected)
            {
                DrawRectangleRec(rowRect, isHover ? Color{180, 195, 230, 255} : Color{200, 210, 235, 255});
                selEmp = ft;
            }
            else if (isHover)
            {
                DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
            }

            DrawTextEx(myFont, mnv.c_str(), {colX[0], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, name.c_str(), {colX[1], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, phong.c_str(), {colX[2], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, cv.c_str(), {colX[3], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, vitri.c_str(), {colX[4], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, strHeSo.c_str(), {colX[5], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, (strNgayCong + "/26").c_str(), {colX[6], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, strLuong.c_str(), {colX[7], currentY}, fontSize, 1, BLACK);
            DrawLine(startX, currentY + 30, GetScreenWidth() - 20, currentY + 30, Fade(LIGHTGRAY, 0.5f));
            currentY += rowHeight;
            totalRows++;
        }
        p = p->Next;
    }
    EndScissorMode();

    // =========== CHẶN SCROLL ===========
    float totalListHeight = totalRows * rowHeight;
    float maxScroll = listHeight - totalListHeight;
    if (totalListHeight > listHeight && scrollY < maxScroll)
        scrollY = maxScroll;
    else if (totalListHeight <= listHeight)
        scrollY = 0.0f;

    // vẽ tổng lương
    string strtongluong = FormatSoTien(tongluong);
    Rectangle luong = {1350, 930, 220, 48};
    // DrawRectangleRounded(luong, 0.04f, 10, LIGHTGRAY);
    DrawTextEx(myFont, "Tổng lương: ", {1400, 930}, fontSize + 1, 1, BLACK);
    DrawTextEx(myFont, strtongluong.c_str(), {1600, 930}, fontSize + 1, 1, BLACK);

    // =========== VẼ LABEL + COMBO CHỨC VỤ ===========
    DrawTextEx(myFont, "Chức Vụ", {350, 365}, 22, 1, Color{60, 70, 85, 255});
    int nCV = QL->get_DB()->get_ListCV()->get_size();
    string dsCVFilter[nCV + 1];
    dsCVFilter[0] = default_choice;
    for (int i = 0; i < nCV; i++)
        dsCVFilter[i + 1] = (*QL->get_DB()->get_ListCV())[i]->Data->get_TenChucVu();

    VeDanhSachCombo(comboChucVu1, isChucVuOpen1, dsCVFilter, nCV + 1, mousePos, 22);
    if (selectedChucVuIndex1 == 0)
        DrawTextEx(myFont, default_choice.c_str(), {comboChucVu1.x + 15, comboChucVu1.y + 11}, 22, 1, DARKGRAY);
    else
        DrawTextEx(myFont, (*QL->get_DB()->get_ListCV())[selectedChucVuIndex1 - 1]->Data->get_TenChucVu().c_str(), {comboChucVu1.x + 15, comboChucVu1.y + 11}, 22, 1, DARKGRAY);

    if (Clicked && !isOpenChiTiet)
        XuLyCombo(comboChucVu1, isChucVuOpen1, selectedChucVuIndex1, nCV + 1, mousePos, Clicked);

    // =========== VẼ LABEL + COMBO PHÒNG BAN ===========
    DrawTextEx(myFont, "Phòng Ban", {620, 365}, 22, 1, Color{60, 70, 85, 255});
    int nPB = QL->get_DB()->get_ListPB()->get_size();
    string dsPBFilter[nPB + 1];
    dsPBFilter[0] = default_choice;
    for (int i = 0; i < nPB; i++)
        dsPBFilter[i + 1] = (*QL->get_DB()->get_ListPB())[i]->Data->get_TenPhongBan();

    VeDanhSachCombo(comboPhong1, isPhongOpen1, dsPBFilter, nPB + 1, mousePos, 22);
    if (selectedPhongIndex1 == 0)
        DrawTextEx(myFont, default_choice.c_str(), {comboPhong1.x + 15, comboPhong1.y + 11}, 22, 1, DARKGRAY);
    else
        DrawTextEx(myFont, (*QL->get_DB()->get_ListPB())[selectedPhongIndex1 - 1]->Data->get_TenPhongBan().c_str(), {comboPhong1.x + 15, comboPhong1.y + 11}, 22, 1, DARKGRAY);

    if (Clicked && !isOpenChiTiet)
        XuLyCombo(comboPhong1, isPhongOpen1, selectedPhongIndex1, nPB + 1, mousePos, Clicked);

    // =========== VẼ Ô TÌM KIẾM ===========
    if (!isOpenChiTiet)
        Typing(isHoTenActive1, hoTenInput1, letterCount1, mousePos, textHoTen1);
    DrawTextEx(myFont, "Tìm kiếm", {890, 365}, 22, 1, Color{60, 70, 85, 255});
    DrawRectangleRounded(textHoTen1, 0.3f, 6, Color{248, 250, 252, 255});
    DrawRectangleRoundedLinesEx(textHoTen1, 0.3f, 6, 1.5f, isHoTenActive1 ? Color{50, 100, 220, 255} : LIGHTGRAY);
    if (hoTenInput1[0] == '\0')
    {
        DrawTextEx(myFont, "Tìm tên hoặc mã NV...", {textHoTen1.x + 15, textHoTen1.y + 10}, 22, 1, GRAY);
    }
    else
    {
        DrawTextEx(myFont, hoTenInput1, {textHoTen1.x + 15, textHoTen1.y + 10}, 24, 1, BLACK);
    }
    if (!isOpenChiTiet && isHoTenActive1 && hoTenInput1[0] != '\0' && ((int)(GetTime() * 2) % 2 == 0))
    {
        Vector2 textSize = MeasureTextEx(myFont, hoTenInput1, 24, 1);
        float cursorX = textHoTen1.x + 15 + textSize.x + 2;
        if (cursorX < textHoTen1.x + textHoTen1.width - 15)
        {
            DrawTextEx(myFont, "_", {cursorX, textHoTen1.y + 10}, 24, 1, Color{50, 100, 220, 255});
        }
    }

    // =========== VẼ COMBO SẮP XẾP LƯƠNG ===========
    DrawTextEx(myFont, "Sắp xếp theo:", {1290, 365}, 22, 1, Color{60, 70, 85, 255});
    VeDanhSachCombo(comboSort1, isSortOpen1, dsSort, nSort + 1, mousePos, 22);
    if (selectedSortIndex1 == 0)
        DrawTextEx(myFont, dsSort[0].c_str(), {comboSort1.x + 15, comboSort1.y + 11}, 22, 1, DARKGRAY);
    else
        DrawTextEx(myFont, dsSort[selectedSortIndex1].c_str(), {comboSort1.x + 15, comboSort1.y + 11}, 22, 1, DARKGRAY);

    if (Clicked && !isOpenChiTiet)
        XuLyCombo(comboSort1, isSortOpen1, selectedSortIndex1, nSort + 1, mousePos, Clicked);

    // =========== NÚT CHI TIẾT GÓC DƯỚI BÊN PHẢI KHI CHỌN NHÂN VIÊN ===========
    if (selEmp != nullptr && !selectedMNV_FT.empty())
    {
        Rectangle btnChiTiet = {350, 930, 220, 48};
        bool hoverChiTiet = !isOpenChiTiet && CheckCollisionPointRec(mousePos, btnChiTiet);
        VeNutChucNang(btnChiTiet, "Xem chi tiết lương", NutStyle::Blue, hoverChiTiet, 0);

        if (Clicked && !isOpenChiTiet && hoverChiTiet)
        {
            isOpenChiTiet = true;
            openedThisFrame = true; // Ngăn chặn sự kiện click này tự đóng modal ngay lập tức
        }
    }

    // =========== MODAL CHI TIẾT TÍNH LƯƠNG (GIỐNG HÌNH ẢNH) ===========
    if (isOpenChiTiet && selEmp != nullptr)
    {
        FullTime *ft = dynamic_cast<FullTime *>(selEmp);
        if (ft != nullptr)
        {
            float screenW = GetScreenWidth();
            float screenH = GetScreenHeight();

            // Overlay mờ che nền
            DrawRectangle(0, 0, screenW, screenH, Fade(BLACK, 0.45f));

            // Kích thước modal (được tăng to hơn rõ ràng, rộng rãi)
            float modalW = 580.0f;
            float modalH = 720.0f;
            Rectangle modal = {(screenW - modalW) / 2.0f, (screenH - modalH) / 2.0f, modalW, modalH};

            // Đổ bóng mờ nhẹ
            DrawRectangleRounded({modal.x + 4, modal.y + 6, modal.width, modal.height}, 0.04f, 10, Fade(BLACK, 0.16f));
            // Hộp trắng chính bo góc
            DrawRectangleRounded(modal, 0.04f, 10, WHITE);
            DrawRectangleRoundedLinesEx(modal, 0.04f, 10, 1.5f, Color{225, 220, 245, 255});

            // Vạch điểm nhấn màu tím góc trái tiêu đề
            DrawRectangleRounded({modal.x + 36, modal.y + 26, 7, 30}, 0.5f, 4, Color{110, 65, 240, 255});

            // Tiêu đề
            DrawTextEx(myFont, "Chi tiết tính lương", {modal.x + 54, modal.y + 24}, 30, 1, Color{50, 30, 140, 255});

            // Tên và mã nhân viên nhỏ bên dưới tiêu đề
            string infoNV = selEmp->get_name() + " (" + selEmp->get_mnv() + ") - Tháng " + to_string(salaryMonth) + "/" + to_string(salaryYear);
            DrawTextEx(myFont, infoNV.c_str(), {modal.x + 36, modal.y + 64}, 22, 1, Color{120, 130, 145, 255});

            // Nút đóng [X]
            Rectangle btnDong = {modal.x + modal.width - 54, modal.y + 22, 34, 34};
            bool hoverX = CheckCollisionPointRec(mousePos, btnDong);
            DrawRectangleRounded(btnDong, 0.3f, 6, hoverX ? Color{254, 226, 226, 255} : Color{245, 246, 250, 255});
            DrawRectangleRoundedLinesEx(btnDong, 0.3f, 6, 1.2f, hoverX ? Color{248, 113, 113, 255} : Color{225, 230, 240, 255});
            Color colX = hoverX ? Color{220, 38, 38, 255} : DARKGRAY;
            DrawLineEx({btnDong.x + 10, btnDong.y + 10}, {btnDong.x + 24, btnDong.y + 24}, 2.0f, colX);
            DrawLineEx({btnDong.x + 24, btnDong.y + 10}, {btnDong.x + 10, btnDong.y + 24}, 2.0f, colX);

            // Đường gạch ngang phân cách
            DrawLine(modal.x + 36, modal.y + 98, modal.x + modal.width - 36, modal.y + 98, Color{235, 240, 248, 255});

            // Lấy các chỉ số tính lương theo salaryMonth / salaryYear
            string pb = ft->get_PhongBan() ? ft->get_PhongBan()->get_TenPhongBan() : "";
            string cv = ft->get_ChucVu() ? ft->get_ChucVu()->get_TenChucVu() : "";
            string vt = ft->get_ViTri() ? ft->get_ViTri()->get_TenVTVL() : "";
            string bac = to_string(ft->get_BacViTri());
            double lcb = QL->get_LuongCoBan(ft);
            if (lcb < 0)
                lcb = 0;
            double heso = ft->get_HeSo();
            double phucap = (ft->get_ChucVu() != nullptr) ? ft->get_ChucVu()->get_PhuCap() : 0.0;
            double thuong = ft->get_Thuong();

            double ncDung = 0.0;
            double gioOTThang = 0.0;
            long long tienOT = 0;
            long long thuclinh = QL->TinhLuongThang(ft, salaryMonth, salaryYear, ncDung, gioOTThang, tienOT);

            float leftX = modal.x + 38;
            float rightX = modal.x + modal.width - 38;
            float rowY = modal.y + 112;
            float rowSpacing = 44;
            int labelSize = 24;
            int valSize = 30;
            Color labelColor = Color{45, 55, 72, 255};
            Color valColor = Color{25, 30, 45, 255};

            DrawTextEx(myFont, "Phòng Ban", {leftX, rowY}, labelSize, 1, labelColor);
            float wpb = MeasureTextEx(myFont, pb.c_str(), valSize, 1).x;
            DrawTextEx(myFont, pb.c_str(), {rightX - wpb, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            DrawTextEx(myFont, "Chức Vụ", {leftX, rowY}, labelSize, 1, labelColor);
            float wcv = MeasureTextEx(myFont, cv.c_str(), valSize, 1).x;
            DrawTextEx(myFont, cv.c_str(), {rightX - wcv, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            DrawTextEx(myFont, "Vị Trí Việc Làm", {leftX, rowY}, labelSize, 1, labelColor);
            float wvt = MeasureTextEx(myFont, vt.c_str(), valSize, 1).x;
            DrawTextEx(myFont, vt.c_str(), {rightX - wvt, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            DrawTextEx(myFont, "Bậc vị trí", {leftX, rowY}, labelSize, 1, labelColor);
            float wbac = MeasureTextEx(myFont, bac.c_str(), valSize, 1).x;
            DrawTextEx(myFont, bac.c_str(), {rightX - wbac, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;
            // 1. Lương cơ bản
            DrawTextEx(myFont, "Lương cơ bản", {leftX, rowY}, labelSize, 1, labelColor);
            string sLCB = FormatSoTien((long long)lcb) + " đ";
            float wLCB = MeasureTextEx(myFont, sLCB.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sLCB.c_str(), {rightX - wLCB, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 2. Hệ số lương
            DrawTextEx(myFont, "Hệ số lương", {leftX, rowY}, labelSize, 1, labelColor);
            ostringstream ossHS;
            ossHS << fixed << setprecision(1) << heso;
            string sHS = ossHS.str();
            float wHS = MeasureTextEx(myFont, sHS.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sHS.c_str(), {rightX - wHS, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 3. Ngày công thực tế
            DrawTextEx(myFont, "Ngày công thực tế", {leftX, rowY}, labelSize, 1, labelColor);
            ostringstream ossNC;
            if (ncDung == (int)ncDung)
                ossNC << (int)ncDung;
            else
                ossNC << fixed << setprecision(1) << ncDung;
            string sNC = ossNC.str() + " / 26 ngày";
            float wNC = MeasureTextEx(myFont, sNC.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sNC.c_str(), {rightX - wNC, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 3b. Tăng ca / Giờ OT
            DrawTextEx(myFont, "Tăng ca (OT)", {leftX, rowY}, labelSize, 1, labelColor);
            ostringstream ossOTRow;
            ossOTRow << fixed << setprecision(1) << gioOTThang << "h (+" << FormatSoTien(tienOT) << " đ)";
            string sOT = ossOTRow.str();
            float wOT = MeasureTextEx(myFont, sOT.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sOT.c_str(), {rightX - wOT, rowY}, valSize, 1, (gioOTThang > 0) ? Color{130, 40, 180, 255} : valColor);
            rowY += rowSpacing;

            // 4. Phụ cấp
            DrawTextEx(myFont, "Phụ cấp", {leftX, rowY}, labelSize, 1, labelColor);
            string sPC = FormatSoTien((long long)phucap) + " đ";
            float wPC = MeasureTextEx(myFont, sPC.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sPC.c_str(), {rightX - wPC, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 5. Thưởng (Có chức năng xem và chỉnh sửa trực tiếp)
            DrawTextEx(myFont, "Thưởng", {leftX, rowY}, labelSize, 1, labelColor);

            if (!isEditingThuong)
            {
                // Nút "Sửa" nhỏ bên cạnh chữ Thưởng
                Rectangle btnSuaThuong = {leftX + 85, rowY - 2, 54, 28};
                bool hoverSua = CheckCollisionPointRec(mousePos, btnSuaThuong);
                DrawRectangleRounded(btnSuaThuong, 0.3f, 6, hoverSua ? Color{225, 218, 255, 255} : Color{242, 238, 255, 255});
                DrawRectangleRoundedLinesEx(btnSuaThuong, 0.3f, 6, 1.2f, Color{160, 140, 230, 255});
                DrawTextEx(myFont, "Sửa", {btnSuaThuong.x + 12, btnSuaThuong.y + 3}, 18, 1, Color{98, 70, 234, 255});

                string sThuong = FormatSoTien((long long)thuong) + " đ";
                float wThuong = MeasureTextEx(myFont, sThuong.c_str(), valSize, 1).x;
                Rectangle recThuongVal = {rightX - wThuong - 4, rowY - 2, wThuong + 8, 30};
                bool hoverVal = CheckCollisionPointRec(mousePos, recThuongVal);

                DrawTextEx(myFont, sThuong.c_str(), {rightX - wThuong, rowY}, valSize, 1, hoverVal ? Color{98, 70, 234, 255} : valColor);

                if (Clicked && (hoverSua || hoverVal))
                {
                    isEditingThuong = true;
                    isThuongActive = true;
                    snprintf(thuongInput, sizeof(thuongInput), "%lld", (long long)thuong);
                    thuongLetterCount = (int)strlen(thuongInput);
                }
            }
            else
            {
                Rectangle boxThuong = {rightX - 250, rowY - 4, 130, 34};
                Rectangle btnLuuThuong = {rightX - 112, rowY - 4, 54, 34};
                Rectangle btnHuyThuong = {rightX - 52, rowY - 4, 48, 34};

                bool hoverLuu = CheckCollisionPointRec(mousePos, btnLuuThuong);
                bool hoverHuy = CheckCollisionPointRec(mousePos, btnHuyThuong);

                if (Clicked)
                {
                    if (CheckCollisionPointRec(mousePos, boxThuong))
                        isThuongActive = true;
                    else if (!hoverLuu && !hoverHuy)
                        isThuongActive = false;
                }

                if (isThuongActive)
                {
                    int key = GetCharPressed();
                    while (key > 0)
                    {
                        if (key >= '0' && key <= '9' && thuongLetterCount < 11)
                        {
                            thuongInput[thuongLetterCount++] = (char)key;
                            thuongInput[thuongLetterCount] = '\0';
                        }
                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
                    {
                        if (thuongLetterCount > 0)
                        {
                            thuongLetterCount--;
                            thuongInput[thuongLetterCount] = '\0';
                        }
                    }
                }

                // Vẽ ô nhập số tiền thưởng
                DrawRectangleRounded(boxThuong, 0.25f, 6, isThuongActive ? WHITE : Color{245, 246, 250, 255});
                DrawRectangleRoundedLinesEx(boxThuong, 0.25f, 6, 1.5f, isThuongActive ? Color{98, 70, 234, 255} : LIGHTGRAY);
                DrawTextEx(myFont, thuongInput, {boxThuong.x + 8, boxThuong.y + 6}, 20, 1, BLACK);

                // Con trỏ nhấp nháy
                if (isThuongActive && ((int)(GetTime() * 2) % 2 == 0))
                {
                    float tw = MeasureTextEx(myFont, thuongInput, 20, 1).x;
                    DrawLineEx({boxThuong.x + 8 + tw + 2, boxThuong.y + 6}, {boxThuong.x + 8 + tw + 2, boxThuong.y + 28}, 1.5f, Color{98, 70, 234, 255});
                }

                // Nút Lưu
                DrawRectangleRounded(btnLuuThuong, 0.25f, 6, hoverLuu ? Color{80, 50, 215, 255} : Color{98, 70, 234, 255});
                DrawTextEx(myFont, "Lưu", {btnLuuThuong.x + 12, btnLuuThuong.y + 8}, 18, 1, WHITE);

                // Nút Hủy
                DrawRectangleRounded(btnHuyThuong, 0.25f, 6, hoverHuy ? Color{225, 230, 238, 255} : Color{240, 242, 246, 255});
                DrawRectangleRoundedLinesEx(btnHuyThuong, 0.25f, 6, 1.0f, Color{200, 205, 215, 255});
                DrawTextEx(myFont, "Hủy", {btnHuyThuong.x + 11, btnHuyThuong.y + 8}, 18, 1, DARKGRAY);

                // Xử lý Lưu: click Lưu hoặc nhấn Enter
                bool doSave = (Clicked && hoverLuu) || (isThuongActive && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)));
                if (doSave)
                {
                    int newT = 0;
                    if (strlen(thuongInput) > 0)
                    {
                        try
                        {
                            long long val = stoll(thuongInput);
                            if (val < 0)
                                val = 0;
                            if (val > 2000000000LL)
                                val = 2000000000LL;
                            newT = (int)val;
                        }
                        catch (...)
                        {
                            newT = 0;
                        }
                    }
                    ft->set_Thuong(newT);
                    thuclinh = QL->TinhLuongThang(ft, salaryMonth, salaryYear, ncDung, gioOTThang, tienOT);
                    if (thuclinh < 0)
                        thuclinh = 0;
                    HienThongBao("Cập nhật tiền thưởng thành công!", false);
                    isEditingThuong = false;
                    isThuongActive = false;
                }

                // Xử lý Hủy: click Hủy hoặc nhấn Escape
                if ((Clicked && hoverHuy) || IsKeyPressed(KEY_ESCAPE))
                {
                    isEditingThuong = false;
                    isThuongActive = false;
                }
            }
            rowY += rowSpacing + 10;
            /*
                        // 6. Box Tổng thu nhập (Hộp xanh nhạt bo góc với icon máy tính)
                        Rectangle boxTongThuNhap = {leftX, rowY, modal.width - 76, 58};
                        DrawRectangleRounded(boxTongThuNhap, 0.25f, 8, Color{242, 246, 255, 255});
                        DrawRectangleRoundedLinesEx(boxTongThuNhap, 0.25f, 8, 1.2f, Color{220, 230, 252, 255});

                        // Vẽ icon máy tính nhỏ
                        Rectangle iconCalc = {leftX + 16, rowY + 16, 22, 26};
                        DrawRectangleRounded(iconCalc, 0.2f, 4, Color{50, 90, 220, 255});
                        DrawRectangle(iconCalc.x + 3, iconCalc.y + 4, 16, 4, WHITE);
                        DrawCircle(iconCalc.x + 6, iconCalc.y + 13, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 11, iconCalc.y + 13, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 16, iconCalc.y + 13, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 6, iconCalc.y + 20, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 11, iconCalc.y + 20, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 16, iconCalc.y + 20, 1.5f, WHITE);

                        DrawTextEx(myFont, "Tổng thu nhập", {leftX + 50, rowY + 16}, 24, 1, Color{40, 75, 215, 255});
                        string sTong = FormatSoTien((long long)thuclinh) + " đ";
                        float wTong = MeasureTextEx(myFont, sTong.c_str(), 26, 1).x;
                        DrawTextEx(myFont, sTong.c_str(), {rightX - wTong - 16, rowY + 15}, 26, 1, Color{30, 60, 200, 255});
                        rowY += 72;
            */
            // 8. Box Thực lĩnh (Hộp tím nhạt bo góc với icon checkmark tím)
            Rectangle boxThucLinh = {leftX, rowY, modal.width - 76, 62};
            DrawRectangleRounded(boxThucLinh, 0.25f, 8, Color{246, 242, 255, 255});
            DrawRectangleRoundedLinesEx(boxThucLinh, 0.25f, 8, 1.2f, Color{225, 215, 250, 255});

            // Icon tròn tím có dấu checkmark
            DrawCircle(leftX + 20, rowY + 31, 13, Color{98, 70, 234, 255});
            DrawLineEx({leftX + 14, rowY + 31}, {leftX + 19, rowY + 36}, 2.4f, WHITE);
            DrawLineEx({leftX + 19, rowY + 36}, {leftX + 27, rowY + 24}, 2.4f, WHITE);

            DrawTextEx(myFont, "Thực lĩnh", {leftX + 50, rowY + 18}, 26, 1, Color{98, 70, 234, 255});
            string sTL = FormatSoTien((long long)thuclinh) + " đ";
            float wTL = MeasureTextEx(myFont, sTL.c_str(), 28, 1).x;
            DrawTextEx(myFont, sTL.c_str(), {rightX - wTL - 16, rowY + 17}, 28, 1, Color{98, 70, 234, 255});

            // Xử lý đóng modal: click [X] hoặc click ra ngoài modal (chỉ khi không phải vừa mở ở frame này)
            if (Clicked && !openedThisFrame)
            {
                if (hoverX || !CheckCollisionPointRec(mousePos, modal))
                {
                    isOpenChiTiet = false;
                    isEditingThuong = false;
                    isThuongActive = false;
                }
            }
        }
    }

    openedThisFrame = false;
    if (isOpenChiTiet)
        g_isModalActive = true;
    else
        g_isModalActive = false;
}

void Draw_Screen_BL_PartTime(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static long long tongluong = 0;
    static bool isChucVuOpen2 = false;
    static int selectedChucVuIndex2 = 0;
    static bool isPhongOpen2 = false;
    static int selectedPhongIndex2 = 0;
    static bool isHoTenActive2 = false;
    static char hoTenInput2[50] = "\0";
    static int letterCount2 = 0;
    static bool isSortOpen2 = false;
    static int selectedSortIndex2 = 0;
    static string selectedMNV_PT = "";
    static bool isOpenChiTiet2 = false;
    static bool isEditingThuong2 = false;
    static bool isThuongActive2 = false;
    static char thuongInput2[20] = "";
    static int thuongLetterCount2 = 0;
    static string lastSelectedMNV2 = "";
    static string tieuchi_CV = "";
    static string tieuchi_PB = "";
    static float scrollY = 0.0f;

    if (doReset)
    {
        tongluong = 0;
        isChucVuOpen2 = false;
        selectedChucVuIndex2 = 0;
        isPhongOpen2 = false;
        selectedPhongIndex2 = 0;
        isHoTenActive2 = false;
        hoTenInput2[0] = '\0';
        letterCount2 = 0;
        isSortOpen2 = false;
        selectedSortIndex2 = 0;
        selectedMNV_PT = "";
        isOpenChiTiet2 = false;
        isEditingThuong2 = false;
        isThuongActive2 = false;
        thuongInput2[0] = '\0';
        thuongLetterCount2 = 0;
        scrollY = 0.0f;
    }

    Rectangle panelBang = {330, 345, 1450.0f, 640.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});
    string default_choice = "Tất cả";

    // =========== COMBO CHỨC VỤ ===========
    Rectangle comboChucVu2 = {350, 400, 250, 45};

    // =========== COMBO PHÒNG BAN ===========
    Rectangle comboPhong2 = {620, 400, 250, 45};

    // =========== Ô TÌM KIẾM ===========
    Rectangle textHoTen2 = {890, 400, 350, 45};

    // =========== COMBO SẮP XẾP LƯƠNG (CHỈ TĂNG HOẶC GIẢM) ===========
    Rectangle comboSort2 = {1290, 400, 260, 45};
    string dsSort[] = {"...", "Lương tăng dần", "Lương giảm dần"};
    int nSort = 2;

    // =========== TRẠNG THÁI CHỌN NHÂN VIÊN & CHI TIẾT ===========
    bool openedThisFrame2 = false; // Cờ chống nháy khi vừa bấm mở modal
    if (lastSelectedMNV2 != selectedMNV_PT)
    {
        lastSelectedMNV2 = selectedMNV_PT;
        isEditingThuong2 = false;
        isThuongActive2 = false;
    }

    // =========== CẤU HÌNH BẢNG ===========
    float scrollSpeed = 30.0f;
    if (selectedChucVuIndex2 != 0)
    {
        tieuchi_CV = (*QL->get_DB()->get_ListCV())[selectedChucVuIndex2 - 1]->Data->get_MaChucVu();
        scrollY = 0.0f;
        tongluong = 0;
    }
    else
    {
        tongluong = 0;
        tieuchi_CV = "";
    }

    if (selectedPhongIndex2 != 0)
    {
        tieuchi_PB = (*QL->get_DB()->get_ListPB())[selectedPhongIndex2 - 1]->Data->get_MaPhongBan();
        scrollY = 0.0f;
        tongluong = 0;
    }
    else
    {
        tongluong = 0;
        tieuchi_PB = "";
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
        scrollY += wheel * scrollSpeed;
    if (scrollY > 0.0f)
        scrollY = 0.0f;

    int startX = 350;
    int startY = 480;
    int rowHeight = 60;
    int fontSize = 24;

    float colX[] = {350.f, 470.f, 730.f, 890.f, 1100.f, 1390.f, 1600.f};

    // =========== HEADER ===========
    DrawTextEx(myFont, "Mã NV", {colX[0], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Họ tên", {colX[1], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Phòng ban", {colX[2], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Chức vụ", {colX[3], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Vị trí", {colX[4], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Số giờ làm", {colX[5], (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Tổng lương", {colX[6], (float)startY}, fontSize, 1, DARKGRAY);
    DrawLine(startX, startY + 30, 1780, startY + 30, LIGHTGRAY);

    // =========== THU THẬP VÀ SẮP XẾP DANH SÁCH PARTTIME ===========

    // Sắp xếp lương theo yêu cầu (1: Tăng dần, 2: Giảm dần)
    if (selectedSortIndex2 == 1)
    {
        QL->SapXep(TieuChiSapXep::LUONGPT_TANG);
    }
    else if (selectedSortIndex2 == 2)
    {
        QL->SapXep(TieuChiSapXep::LUONGPT_GIAM);
    }

    // =========== VẼ DANH SÁCH NHÂN VIÊN ===========
    int listStartY = startY + 35;
    int listHeight = GetScreenHeight() - listStartY - 120;

    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    bool canHover = !isOpenChiTiet2 && !isChucVuOpen2 && !isPhongOpen2 && !isSortOpen2 && CheckCollisionPointRec(mousePos, listArea);

    float currentY = listStartY + scrollY;
    int totalRows = 0;
    Employee *selEmp = nullptr;
    if (!selectedMNV_PT.empty())
        selEmp = QL->TimTheoMa(selectedMNV_PT);

    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Node<Employee> *p = QL->get_DB()->get_ListEmployee()->get_header()->Next;
    while (p != nullptr)
    {
        if (p->Data->get_LoaiNV() == "PartTime" && CheckEmployee(p->Data, tieuchi_CV, tieuchi_PB, hoTenInput2))
        {
            PartTime *pt = dynamic_cast<PartTime *>(p->Data);
            string mnv = pt->get_mnv();
            string name = pt->get_name();
            string phong = pt->get_PhongBan() ? pt->get_PhongBan()->get_TenPhongBan() : "";
            string cv = pt->get_ChucVu() ? pt->get_ChucVu()->get_TenChucVu() : "";
            string vitri = pt->get_ViTri() ? pt->get_ViTri()->get_TenVTVL() : "";

            double gioChuan = 0.0;
            double gioOTThang = 0.0;
            long long tienOT = 0;
            long long luong = QL->TinhLuongThang(pt, salaryMonth, salaryYear, gioChuan, gioOTThang, tienOT);
            tongluong += luong;
            double tongGio = gioChuan + gioOTThang;

            string strBac = "Bậc " + to_string(pt->get_BacViTri());
            ostringstream ossG;
            if (tongGio == (int)tongGio)
                ossG << (int)tongGio << "h";
            else
                ossG << fixed << setprecision(1) << tongGio << "h";
            string strGio = ossG.str();
            string strLuong = FormatSoTien(luong);

            // ----- HOVER + CHỌN DÒNG -----
            Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
            bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
            if (isHover && Clicked && !isOpenChiTiet2)
            {
                selectedMNV_PT = mnv;
                selEmp = pt;
            }
            bool isSelected = (mnv == selectedMNV_PT);

            if (isSelected)
            {
                DrawRectangleRec(rowRect, isHover ? Color{180, 195, 230, 255} : Color{200, 210, 235, 255});
                selEmp = pt;
            }
            else if (isHover)
            {
                DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
            }

            DrawTextEx(myFont, mnv.c_str(), {colX[0], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, name.c_str(), {colX[1], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, phong.c_str(), {colX[2], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, cv.c_str(), {colX[3], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, vitri.c_str(), {colX[4], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, strGio.c_str(), {colX[5], currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, strLuong.c_str(), {colX[6], currentY}, fontSize, 1, BLACK);
            DrawLine(startX, currentY + 30, GetScreenWidth() - 20, currentY + 30, Fade(LIGHTGRAY, 0.5f));
            currentY += rowHeight;
            totalRows++;
        }
        p = p->Next;
    }
    EndScissorMode();

    // =========== CHẶN SCROLL ===========
    float totalListHeight = totalRows * rowHeight;
    float maxScroll = listHeight - totalListHeight;
    if (totalListHeight > listHeight && scrollY < maxScroll)
        scrollY = maxScroll;
    else if (totalListHeight <= listHeight)
        scrollY = 0.0f;

    // vẽ tổng lương
    string strtongluong = FormatSoTien(tongluong);
    Rectangle luong = {1350, 930, 220, 48};
    // DrawRectangleRounded(luong, 0.04f, 10, LIGHTGRAY);
    DrawTextEx(myFont, "Tổng lương: ", {1400, 930}, fontSize + 1, 1, BLACK);
    DrawTextEx(myFont, strtongluong.c_str(), {1600, 930}, fontSize + 1, 1, BLACK);

    // =========== VẼ LABEL + COMBO CHỨC VỤ ===========
    DrawTextEx(myFont, "Chức Vụ", {350, 365}, 22, 1, Color{60, 70, 85, 255});
    int nCV = QL->get_DB()->get_ListCV()->get_size();
    string dsCVFilter[nCV + 1];
    dsCVFilter[0] = default_choice;
    for (int i = 0; i < nCV; i++)
        dsCVFilter[i + 1] = (*QL->get_DB()->get_ListCV())[i]->Data->get_TenChucVu();

    VeDanhSachCombo(comboChucVu2, isChucVuOpen2, dsCVFilter, nCV + 1, mousePos, 22);
    if (selectedChucVuIndex2 == 0)
        DrawTextEx(myFont, default_choice.c_str(), {comboChucVu2.x + 15, comboChucVu2.y + 11}, 22, 1, DARKGRAY);
    else
        DrawTextEx(myFont, (*QL->get_DB()->get_ListCV())[selectedChucVuIndex2 - 1]->Data->get_TenChucVu().c_str(), {comboChucVu2.x + 15, comboChucVu2.y + 11}, 22, 1, DARKGRAY);

    if (Clicked && !isOpenChiTiet2)
        XuLyCombo(comboChucVu2, isChucVuOpen2, selectedChucVuIndex2, nCV + 1, mousePos, Clicked);

    // =========== VẼ LABEL + COMBO PHÒNG BAN ===========
    DrawTextEx(myFont, "Phòng Ban", {620, 365}, 22, 1, Color{60, 70, 85, 255});
    int nPB = QL->get_DB()->get_ListPB()->get_size();
    string dsPBFilter[nPB + 1];
    dsPBFilter[0] = default_choice;
    for (int i = 0; i < nPB; i++)
        dsPBFilter[i + 1] = (*QL->get_DB()->get_ListPB())[i]->Data->get_TenPhongBan();

    VeDanhSachCombo(comboPhong2, isPhongOpen2, dsPBFilter, nPB + 1, mousePos, 22);
    if (selectedPhongIndex2 == 0)
        DrawTextEx(myFont, default_choice.c_str(), {comboPhong2.x + 15, comboPhong2.y + 11}, 22, 1, DARKGRAY);
    else
        DrawTextEx(myFont, (*QL->get_DB()->get_ListPB())[selectedPhongIndex2 - 1]->Data->get_TenPhongBan().c_str(), {comboPhong2.x + 15, comboPhong2.y + 11}, 22, 1, DARKGRAY);

    if (Clicked && !isOpenChiTiet2)
        XuLyCombo(comboPhong2, isPhongOpen2, selectedPhongIndex2, nPB + 1, mousePos, Clicked);

    // =========== VẼ Ô TÌM KIẾM ===========
    if (!isOpenChiTiet2)
        Typing(isHoTenActive2, hoTenInput2, letterCount2, mousePos, textHoTen2);
    DrawTextEx(myFont, "Tìm kiếm", {890, 365}, 22, 1, Color{60, 70, 85, 255});
    DrawRectangleRounded(textHoTen2, 0.3f, 6, Color{248, 250, 252, 255});
    DrawRectangleRoundedLinesEx(textHoTen2, 0.3f, 6, 1.5f, isHoTenActive2 ? Color{50, 100, 220, 255} : LIGHTGRAY);
    if (hoTenInput2[0] == '\0')
    {
        DrawTextEx(myFont, "Tìm tên hoặc mã NV...", {textHoTen2.x + 15, textHoTen2.y + 10}, 22, 1, GRAY);
    }
    else
    {
        DrawTextEx(myFont, hoTenInput2, {textHoTen2.x + 15, textHoTen2.y + 10}, 24, 1, BLACK);
    }
    if (!isOpenChiTiet2 && isHoTenActive2 && hoTenInput2[0] != '\0' && ((int)(GetTime() * 2) % 2 == 0))
    {
        Vector2 textSize = MeasureTextEx(myFont, hoTenInput2, 24, 1);
        float cursorX = textHoTen2.x + 15 + textSize.x + 2;
        if (cursorX < textHoTen2.x + textHoTen2.width - 15)
        {
            DrawTextEx(myFont, "_", {cursorX, textHoTen2.y + 10}, 24, 1, Color{50, 100, 220, 255});
        }
    }

    // =========== VẼ COMBO SẮP XẾP LƯƠNG ===========
    DrawTextEx(myFont, "Sắp xếp theo:", {1290, 365}, 22, 1, Color{60, 70, 85, 255});
    VeDanhSachCombo(comboSort2, isSortOpen2, dsSort, nSort + 1, mousePos, 22);
    if (selectedSortIndex2 == 0)
        DrawTextEx(myFont, dsSort[0].c_str(), {comboSort2.x + 15, comboSort2.y + 11}, 22, 1, DARKGRAY);
    else
        DrawTextEx(myFont, dsSort[selectedSortIndex2].c_str(), {comboSort2.x + 15, comboSort2.y + 11}, 22, 1, DARKGRAY);

    if (Clicked && !isOpenChiTiet2)
        XuLyCombo(comboSort2, isSortOpen2, selectedSortIndex2, nSort + 1, mousePos, Clicked);

    // =========== NÚT CHI TIẾT GÓC DƯỚI BÊN PHẢI KHI CHỌN NHÂN VIÊN ===========
    if (selEmp != nullptr && !selectedMNV_PT.empty())
    {
        Rectangle btnChiTiet = {350, 930, 220, 48};
        bool hoverChiTiet = !isOpenChiTiet2 && CheckCollisionPointRec(mousePos, btnChiTiet);
        VeNutChucNang(btnChiTiet, "Xem chi tiết lương", NutStyle::Blue, hoverChiTiet, 0);

        if (Clicked && !isOpenChiTiet2 && hoverChiTiet)
        {
            isOpenChiTiet2 = true;
            openedThisFrame2 = true;
        }
    }

    // =========== MODAL CHI TIẾT TÍNH LƯƠNG PARTTIME ===========
    if (isOpenChiTiet2 && selEmp != nullptr)
    {
        PartTime *pt = dynamic_cast<PartTime *>(selEmp);
        if (pt != nullptr)
        {
            float screenW = GetScreenWidth();
            float screenH = GetScreenHeight();

            // Overlay mờ che nền
            DrawRectangle(0, 0, screenW, screenH, Fade(BLACK, 0.45f));

            // Kích thước modal (được tăng to hơn rõ ràng, rộng rãi)
            float modalW = 580.0f;
            float modalH = 720.0f;
            Rectangle modal = {(screenW - modalW) / 2.0f, (screenH - modalH) / 2.0f, modalW, modalH};

            // Đổ bóng mờ nhẹ
            DrawRectangleRounded({modal.x + 4, modal.y + 6, modal.width, modal.height}, 0.04f, 10, Fade(BLACK, 0.16f));
            // Hộp trắng chính bo góc
            DrawRectangleRounded(modal, 0.04f, 10, WHITE);
            DrawRectangleRoundedLinesEx(modal, 0.04f, 10, 1.5f, Color{225, 220, 245, 255});

            // Vạch điểm nhấn màu tím góc trái tiêu đề
            DrawRectangleRounded({modal.x + 36, modal.y + 26, 7, 30}, 0.5f, 4, Color{110, 65, 240, 255});

            // Tiêu đề
            DrawTextEx(myFont, "Chi tiết tính lương", {modal.x + 54, modal.y + 24}, 30, 1, Color{50, 30, 140, 255});

            // Tên và mã nhân viên nhỏ bên dưới tiêu đề
            string infoNV = selEmp->get_name() + " (" + selEmp->get_mnv() + ") - Tháng " + to_string(salaryMonth) + "/" + to_string(salaryYear);
            DrawTextEx(myFont, infoNV.c_str(), {modal.x + 36, modal.y + 64}, 22, 1, Color{120, 130, 145, 255});

            // Nút đóng [X]
            Rectangle btnDong = {modal.x + modal.width - 54, modal.y + 22, 34, 34};
            bool hoverX = CheckCollisionPointRec(mousePos, btnDong);
            DrawRectangleRounded(btnDong, 0.3f, 6, hoverX ? Color{254, 226, 226, 255} : Color{245, 246, 250, 255});
            DrawRectangleRoundedLinesEx(btnDong, 0.3f, 6, 1.2f, hoverX ? Color{248, 113, 113, 255} : Color{225, 230, 240, 255});
            Color colX = hoverX ? Color{220, 38, 38, 255} : DARKGRAY;
            DrawLineEx({btnDong.x + 10, btnDong.y + 10}, {btnDong.x + 24, btnDong.y + 24}, 2.0f, colX);
            DrawLineEx({btnDong.x + 24, btnDong.y + 10}, {btnDong.x + 10, btnDong.y + 24}, 2.0f, colX);

            // Đường gạch ngang phân cách
            DrawLine(modal.x + 36, modal.y + 98, modal.x + modal.width - 36, modal.y + 98, Color{235, 240, 248, 255});

            // Lấy các chỉ số tính lương PartTime theo salaryMonth / salaryYear
            string pb = pt->get_PhongBan() ? pt->get_PhongBan()->get_TenPhongBan() : "";
            string cv = pt->get_ChucVu() ? pt->get_ChucVu()->get_TenChucVu() : "";
            string vt = pt->get_ViTri() ? pt->get_ViTri()->get_TenVTVL() : "";
            string bac = to_string(pt->get_BacViTri());
            double lcb = QL->get_LuongCoBan(pt);
            if (lcb < 0)
                lcb = 0;
            double phucap = (pt->get_ChucVu() != nullptr) ? pt->get_ChucVu()->get_PhuCap() : 0.0;
            double thuong = pt->get_Thuong();

            double gioChuanThang = 0.0;
            double gioOTThang = 0.0;
            long long tienOT = 0;
            long long thuclinh = QL->TinhLuongThang(pt, salaryMonth, salaryYear, gioChuanThang, gioOTThang, tienOT);
            double tongGio = gioChuanThang + gioOTThang;

            float leftX = modal.x + 38;
            float rightX = modal.x + modal.width - 38;
            float rowY = modal.y + 112;
            float rowSpacing = 44;
            int labelSize = 24;
            int valSize = 30;
            Color labelColor = Color{45, 55, 72, 255};
            Color valColor = Color{25, 30, 45, 255};

            DrawTextEx(myFont, "Phòng Ban", {leftX, rowY}, labelSize, 1, labelColor);
            float wpb = MeasureTextEx(myFont, pb.c_str(), valSize, 1).x;
            DrawTextEx(myFont, pb.c_str(), {rightX - wpb, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            DrawTextEx(myFont, "Chức Vụ", {leftX, rowY}, labelSize, 1, labelColor);
            float wcv = MeasureTextEx(myFont, cv.c_str(), valSize, 1).x;
            DrawTextEx(myFont, cv.c_str(), {rightX - wcv, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            DrawTextEx(myFont, "Vị Trí Việc Làm", {leftX, rowY}, labelSize, 1, labelColor);
            float wvt = MeasureTextEx(myFont, vt.c_str(), valSize, 1).x;
            DrawTextEx(myFont, vt.c_str(), {rightX - wvt, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            DrawTextEx(myFont, "Bậc vị trí", {leftX, rowY}, labelSize, 1, labelColor);
            float wbac = MeasureTextEx(myFont, bac.c_str(), valSize, 1).x;
            DrawTextEx(myFont, bac.c_str(), {rightX - wbac, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 1. Lương theo giờ
            DrawTextEx(myFont, "Lương theo giờ", {leftX, rowY}, labelSize, 1, labelColor);
            string sLCB = FormatSoTien((long long)lcb) + " đ/h";
            float wLCB = MeasureTextEx(myFont, sLCB.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sLCB.c_str(), {rightX - wLCB, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 3. Số giờ làm việc thực tế
            DrawTextEx(myFont, "Giờ làm chuẩn", {leftX, rowY}, labelSize, 1, labelColor);
            ostringstream ossGC;
            if (gioChuanThang == (int)gioChuanThang)
                ossGC << (int)gioChuanThang;
            else
                ossGC << fixed << setprecision(1) << gioChuanThang;
            string sGio = ossGC.str() + " giờ";
            float wGio = MeasureTextEx(myFont, sGio.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sGio.c_str(), {rightX - wGio, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 3b. Tăng ca / Giờ OT
            DrawTextEx(myFont, "Tăng ca (OT)", {leftX, rowY}, labelSize, 1, labelColor);
            ostringstream ossOTRow;
            ossOTRow << fixed << setprecision(1) << gioOTThang << "h (+" << FormatSoTien(tienOT) << " đ)";
            string sOT = ossOTRow.str();
            float wOT = MeasureTextEx(myFont, sOT.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sOT.c_str(), {rightX - wOT, rowY}, valSize, 1, (gioOTThang > 0) ? Color{130, 40, 180, 255} : valColor);
            rowY += rowSpacing;

            // 4. Phụ cấp
            DrawTextEx(myFont, "Phụ cấp", {leftX, rowY}, labelSize, 1, labelColor);
            string sPC = FormatSoTien((long long)phucap) + " đ";
            float wPC = MeasureTextEx(myFont, sPC.c_str(), valSize, 1).x;
            DrawTextEx(myFont, sPC.c_str(), {rightX - wPC, rowY}, valSize, 1, valColor);
            rowY += rowSpacing;

            // 5. Thưởng (Có chức năng xem và chỉnh sửa trực tiếp)
            DrawTextEx(myFont, "Thưởng", {leftX, rowY}, labelSize, 1, labelColor);

            if (!isEditingThuong2)
            {
                // Nút "Sửa" nhỏ bên cạnh chữ Thưởng
                Rectangle btnSuaThuong = {leftX + 85, rowY - 2, 54, 28};
                bool hoverSua = CheckCollisionPointRec(mousePos, btnSuaThuong);
                DrawRectangleRounded(btnSuaThuong, 0.3f, 6, hoverSua ? Color{225, 218, 255, 255} : Color{242, 238, 255, 255});
                DrawRectangleRoundedLinesEx(btnSuaThuong, 0.3f, 6, 1.2f, Color{160, 140, 230, 255});
                DrawTextEx(myFont, "Sửa", {btnSuaThuong.x + 12, btnSuaThuong.y + 3}, 18, 1, Color{98, 70, 234, 255});

                string sThuong = FormatSoTien((long long)thuong) + " đ";
                float wThuong = MeasureTextEx(myFont, sThuong.c_str(), valSize, 1).x;
                Rectangle recThuongVal = {rightX - wThuong - 4, rowY - 2, wThuong + 8, 30};
                bool hoverVal = CheckCollisionPointRec(mousePos, recThuongVal);

                DrawTextEx(myFont, sThuong.c_str(), {rightX - wThuong, rowY}, valSize, 1, hoverVal ? Color{98, 70, 234, 255} : valColor);

                if (Clicked && (hoverSua || hoverVal))
                {
                    isEditingThuong2 = true;
                    isThuongActive2 = true;
                    snprintf(thuongInput2, sizeof(thuongInput2), "%lld", (long long)thuong);
                    thuongLetterCount2 = (int)strlen(thuongInput2);
                }
            }
            else
            {
                Rectangle boxThuong = {rightX - 250, rowY - 4, 130, 34};
                Rectangle btnLuuThuong = {rightX - 112, rowY - 4, 54, 34};
                Rectangle btnHuyThuong = {rightX - 52, rowY - 4, 48, 34};

                bool hoverLuu = CheckCollisionPointRec(mousePos, btnLuuThuong);
                bool hoverHuy = CheckCollisionPointRec(mousePos, btnHuyThuong);

                if (Clicked)
                {
                    if (CheckCollisionPointRec(mousePos, boxThuong))
                        isThuongActive2 = true;
                    else if (!hoverLuu && !hoverHuy)
                        isThuongActive2 = false;
                }

                if (isThuongActive2)
                {
                    int key = GetCharPressed();
                    while (key > 0)
                    {
                        if (key >= '0' && key <= '9' && thuongLetterCount2 < 11)
                        {
                            thuongInput2[thuongLetterCount2++] = (char)key;
                            thuongInput2[thuongLetterCount2] = '\0';
                        }
                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
                    {
                        if (thuongLetterCount2 > 0)
                        {
                            thuongLetterCount2--;
                            thuongInput2[thuongLetterCount2] = '\0';
                        }
                    }
                }

                // Vẽ ô nhập số tiền thưởng
                DrawRectangleRounded(boxThuong, 0.25f, 6, isThuongActive2 ? WHITE : Color{245, 246, 250, 255});
                DrawRectangleRoundedLinesEx(boxThuong, 0.25f, 6, 1.5f, isThuongActive2 ? Color{98, 70, 234, 255} : LIGHTGRAY);
                DrawTextEx(myFont, thuongInput2, {boxThuong.x + 8, boxThuong.y + 6}, 20, 1, BLACK);

                // Con trỏ nhấp nháy
                if (isThuongActive2 && ((int)(GetTime() * 2) % 2 == 0))
                {
                    float tw = MeasureTextEx(myFont, thuongInput2, 20, 1).x;
                    DrawLineEx({boxThuong.x + 8 + tw + 2, boxThuong.y + 6}, {boxThuong.x + 8 + tw + 2, boxThuong.y + 28}, 1.5f, Color{98, 70, 234, 255});
                }

                // Nút Lưu
                DrawRectangleRounded(btnLuuThuong, 0.25f, 6, hoverLuu ? Color{80, 50, 215, 255} : Color{98, 70, 234, 255});
                DrawTextEx(myFont, "Lưu", {btnLuuThuong.x + 12, btnLuuThuong.y + 8}, 18, 1, WHITE);

                // Nút Hủy
                DrawRectangleRounded(btnHuyThuong, 0.25f, 6, hoverHuy ? Color{225, 230, 238, 255} : Color{240, 242, 246, 255});
                DrawRectangleRoundedLinesEx(btnHuyThuong, 0.25f, 6, 1.0f, Color{200, 205, 215, 255});
                DrawTextEx(myFont, "Hủy", {btnHuyThuong.x + 11, btnHuyThuong.y + 8}, 18, 1, DARKGRAY);

                // Xử lý Lưu: click Lưu hoặc nhấn Enter
                bool doSave = (Clicked && hoverLuu) || (isThuongActive2 && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)));
                if (doSave)
                {
                    int newT = 0;
                    if (strlen(thuongInput2) > 0)
                    {
                        try
                        {
                            long long val = stoll(thuongInput2);
                            if (val < 0)
                                val = 0;
                            if (val > 2000000000LL)
                                val = 2000000000LL;
                            newT = (int)val;
                        }
                        catch (...)
                        {
                            newT = 0;
                        }
                    }
                    pt->set_Thuong(newT);
                    thuclinh = QL->TinhLuongThang(pt, salaryMonth, salaryYear, gioChuanThang, gioOTThang, tienOT);
                    if (thuclinh < 0)
                        thuclinh = 0;
                    HienThongBao("Cập nhật tiền thưởng thành công!", false);
                    isEditingThuong2 = false;
                    isThuongActive2 = false;
                }

                // Xử lý Hủy: click Hủy hoặc nhấn Escape
                if ((Clicked && hoverHuy) || IsKeyPressed(KEY_ESCAPE))
                {
                    isEditingThuong2 = false;
                    isThuongActive2 = false;
                }
            }
            rowY += rowSpacing + 10;
            /*
                        // 6. Box Tổng thu nhập (Hộp xanh nhạt bo góc với icon máy tính)
                        Rectangle boxTongThuNhap = {leftX, rowY, modal.width - 76, 58};
                        DrawRectangleRounded(boxTongThuNhap, 0.25f, 8, Color{242, 246, 255, 255});
                        DrawRectangleRoundedLinesEx(boxTongThuNhap, 0.25f, 8, 1.2f, Color{220, 230, 252, 255});

                        // Vẽ icon máy tính nhỏ
                        Rectangle iconCalc = {leftX + 16, rowY + 16, 22, 26};
                        DrawRectangleRounded(iconCalc, 0.2f, 4, Color{50, 90, 220, 255});
                        DrawRectangle(iconCalc.x + 3, iconCalc.y + 4, 16, 4, WHITE);
                        DrawCircle(iconCalc.x + 6, iconCalc.y + 13, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 11, iconCalc.y + 13, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 16, iconCalc.y + 13, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 6, iconCalc.y + 20, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 11, iconCalc.y + 20, 1.5f, WHITE);
                        DrawCircle(iconCalc.x + 16, iconCalc.y + 20, 1.5f, WHITE);

                        DrawTextEx(myFont, "Tổng thu nhập", {leftX + 50, rowY + 16}, 24, 1, Color{40, 75, 215, 255});
                        string sTong = FormatSoTien((long long)thuclinh) + " đ";
                        float wTong = MeasureTextEx(myFont, sTong.c_str(), 26, 1).x;
                        DrawTextEx(myFont, sTong.c_str(), {rightX - wTong - 16, rowY + 15}, 26, 1, Color{30, 60, 200, 255});
                        rowY += 72;

                        // 7. Khấu trừ (Icon tròn đỏ có dấu trừ)
            */
            // 8. Box Thực lĩnh (Hộp tím nhạt bo góc với icon checkmark tím)
            Rectangle boxThucLinh = {leftX, rowY, modal.width - 76, 62};
            DrawRectangleRounded(boxThucLinh, 0.25f, 8, Color{246, 242, 255, 255});
            DrawRectangleRoundedLinesEx(boxThucLinh, 0.25f, 8, 1.2f, Color{225, 215, 250, 255});

            // Icon tròn tím có dấu checkmark
            DrawCircle(leftX + 20, rowY + 31, 13, Color{98, 70, 234, 255});
            DrawLineEx({leftX + 14, rowY + 31}, {leftX + 19, rowY + 36}, 2.4f, WHITE);
            DrawLineEx({leftX + 19, rowY + 36}, {leftX + 27, rowY + 24}, 2.4f, WHITE);

            DrawTextEx(myFont, "Thực lĩnh", {leftX + 50, rowY + 18}, 26, 1, Color{98, 70, 234, 255});
            string sTL = FormatSoTien((long long)thuclinh) + " đ";
            float wTL = MeasureTextEx(myFont, sTL.c_str(), 28, 1).x;
            DrawTextEx(myFont, sTL.c_str(), {rightX - wTL - 16, rowY + 17}, 28, 1, Color{98, 70, 234, 255});

            // Xử lý đóng modal: click [X] hoặc click ra ngoài modal (chỉ khi không phải vừa mở ở frame này)
            if (Clicked && !openedThisFrame2)
            {
                if (hoverX || !CheckCollisionPointRec(mousePos, modal))
                {
                    isOpenChiTiet2 = false;
                    isEditingThuong2 = false;
                    isThuongActive2 = false;
                }
            }
        }
    }

    openedThisFrame2 = false;
    if (isOpenChiTiet2)
        g_isModalActive = true;
    else
        g_isModalActive = false;
}

void Draw_Screen_Salary(QLNV *QL)
{
    static Texture2D a1;
    static bool isLoaded = false;
    if (!isLoaded)
    {
        a1 = LoadTexture("photo/icon/Asset-3.png");
        isLoaded = true;
    }
    Vector2 pa1 = {370.0f, 45.0f}; // Tọa độ (x, y) postion
    float ra1 = 0.0f;              // Góc xoay (0 độ) rotation
    float sa1 = 0.33f;
    DrawTextureEx(a1, pa1, ra1, sa1, WHITE);
    DrawTextEx(myFont, "Quản Lý Lương & Mức Lương", {pa1.x + 100, pa1.y}, 45, 1, WHITE);
    DrawTextEx(myFont, "Bảng lương nhân sự và định mức lương theo bậc của công ty", {pa1.x + 100, pa1.y + 50}, 30, 1, WHITE);

    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_menuGen);
    s_gen = g_menuGen;
    static bool isOpenBL = true;
    static bool isOpenML = false;
    if (doReset)
    {
        isOpenBL = true;
        isOpenML = false;
    }
    Vector2 mousePos = GetMousePosition();
    bool Clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    float TabX = 330.0f;
    float TabY = 160.0f;
    float TabH = 90.0f;
    Rectangle TabBL = {TabX, TabY, 300.0f, TabH};
    Rectangle TabML = {TabX + 310.0f, TabY, 300.0f, TabH};
    bool hoverPB = CheckCollisionPointRec(mousePos, TabBL);
    bool hoverCV = CheckCollisionPointRec(mousePos, TabML);
    Color CTabBL = isOpenBL == 1 ? BLUE : WHITE;
    Color CTabVT = isOpenML == 1 ? BLUE : WHITE;
    if (isOpenBL == true && hoverCV)
        CTabVT = Fade(BLUE, 0.4);
    if (isOpenML == true && hoverPB)
        CTabBL = Fade(BLUE, 0.4);
    DrawRectangleRounded(TabBL, 0.3f, 10, CTabBL);
    DrawRectangleRoundedLinesEx(TabBL, 0.3f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Bảng lương", {TabBL.x + 70.0f, TabBL.y + 18.0f}, 36, 1, BLACK);

    DrawRectangleRounded(TabML, 0.3f, 10, CTabVT);
    DrawRectangleRoundedLinesEx(TabBL, 0.3f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Mức lương", {TabML.x + 90.0f, TabML.y + 18.0f}, 36, 1, BLACK);

    // =========== BỘ CHỌN THÁNG/NĂM TRA CỨU BẢNG LƯƠNG ===========
    if (isOpenBL)
    {
        bool daChotLuong = QL->DaChotLuongThang(salaryMonth, salaryYear);

        // Nút lùi 1 tháng [<]
        Rectangle btnPrevM = {1260, 180, 42, 45};
        bool hoverPrevM = !g_isModalActive && CheckCollisionPointRec(mousePos, btnPrevM);
        DrawRectangleRounded(btnPrevM, 0.3f, 6, hoverPrevM ? Color{225, 238, 255, 255} : Color{242, 245, 252, 255});
        DrawRectangleRoundedLinesEx(btnPrevM, 0.3f, 6, 1.5f, hoverPrevM ? Color{55, 100, 235, 255} : LIGHTGRAY);
        DrawTextEx(myFont, "<", {btnPrevM.x + 14, btnPrevM.y + 8}, 24, 1, hoverPrevM ? Color{30, 60, 180, 255} : DARKGRAY);
        if (hoverPrevM && Clicked)
        {
            salaryMonth--;
            if (salaryMonth < 1)
            {
                salaryMonth = 12;
                salaryYear--;
            }
        }

        // Ô hiển thị Tháng/Năm
        Rectangle boxM = {1310, 180, 230, 45};
        DrawRectangleRounded(boxM, 0.3f, 6, WHITE);
        DrawRectangleRoundedLinesEx(boxM, 0.3f, 6, 1.5f, Color{55, 100, 235, 255});
        string strM = "Tháng " + to_string(salaryMonth) + " / " + to_string(salaryYear);
        DrawTextEx(myFont, strM.c_str(), {boxM.x + 25, boxM.y + 8}, 24, 1, Color{30, 60, 180, 255});

        // Nút tiến 1 tháng [>]
        Rectangle btnNextM = {1548, 180, 42, 45};
        bool hoverNextM = !g_isModalActive && CheckCollisionPointRec(mousePos, btnNextM);
        DrawRectangleRounded(btnNextM, 0.3f, 6, hoverNextM ? Color{225, 238, 255, 255} : Color{242, 245, 252, 255});
        DrawRectangleRoundedLinesEx(btnNextM, 0.3f, 6, 1.5f, hoverNextM ? Color{55, 100, 235, 255} : LIGHTGRAY);
        DrawTextEx(myFont, ">", {btnNextM.x + 14, btnNextM.y + 8}, 24, 1, hoverNextM ? Color{30, 60, 180, 255} : DARKGRAY);
        if (hoverNextM && Clicked)
        {
            salaryMonth++;
            if (salaryMonth > 12)
            {
                salaryMonth = 1;
                salaryYear++;
            }
        }

        // Nút "Chốt / Xuất Bảng Lương" hoặc Badge "Đã chốt"
        Rectangle btnXuatBL = {1600, 180, 175, 45};
        bool hoverXuat = !g_isModalActive && CheckCollisionPointRec(mousePos, btnXuatBL);
        if (daChotLuong)
        {
            DrawRectangleRounded(btnXuatBL, 0.3f, 6, hoverXuat ? Color{220, 248, 230, 255} : Color{235, 252, 240, 255});
            DrawRectangleRoundedLinesEx(btnXuatBL, 0.3f, 6, 1.5f, Color{40, 170, 80, 255});
            DrawTextEx(myFont, "Đã chốt (Lưu lại)", {btnXuatBL.x + 10, btnXuatBL.y + 11}, 19, 1, Color{20, 140, 60, 255});
            if (hoverXuat && Clicked)
            {
                XuatBangLuongThang(QL, salaryMonth, salaryYear);
                HienThongBao("Đã cập nhật file Bảng Lương tháng " + to_string(salaryMonth) + "/" + to_string(salaryYear) + "!", false);
            }
        }
        else
        {
            DrawRectangleRounded(btnXuatBL, 0.3f, 6, hoverXuat ? Color{70, 120, 245, 255} : Color{55, 100, 235, 255});
            DrawTextEx(myFont, "Chốt lương tháng", {btnXuatBL.x + 12, btnXuatBL.y + 10}, 20, 1, WHITE);
            if (hoverXuat && Clicked)
            {
                XuatBangLuongThang(QL, salaryMonth, salaryYear);
                HienThongBao("Đã chốt và xuất file Bảng Lương tháng " + to_string(salaryMonth) + "/" + to_string(salaryYear) + "!", false);
            }
        }
    }

    if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabBL))
    {
        if (!isOpenBL)
            g_resetGen++;
        isOpenBL = true;
        isOpenML = false;
    }
    else if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabML))
    {
        if (!isOpenML)
            g_resetGen++;
        isOpenML = true;
        isOpenBL = false;
    }

    if (isOpenBL)
    {
        Draw_Screen_BangLuong(mousePos, Clicked, QL);
    }
    else if (isOpenML)
    {
        Draw_Screen_MucLuong(mousePos, Clicked, QL);
    }
}
