#pragma once
#include "GUI_Common.h"

inline void Draw_Screen_Home(QLNV *QL)
{
    // 1. Khung nguồn: Lấy toàn bộ kích thước gốc của file ảnh
    static Texture2D a1;
    static bool isLoaded = false;
    if (!isLoaded)
    {
        a1 = LoadTexture("photo/icon/Asset-4.png");
        isLoaded = true;
    }
    Vector2 pa1 = {370.0f, 45.0f};
    float ra1 = 0.0f;
    float sa1 = 0.33f;
    DrawTextureEx(a1, pa1, ra1, sa1, WHITE);
    DrawTextEx(myFont, "Trang chủ", {pa1.x + 100, pa1.y}, 45, 1, WHITE);
    DrawTextEx(myFont, "Tổng quan hệ thống", {pa1.x + 100, pa1.y + 50}, 30, 1, WHITE);

    int screenW = GetScreenWidth();

    int startX = 330;
    int startY = 170;

    int contentW = screenW - startX - 35;

    // =====================================================
    // TIÊU ĐỀ
    // =====================================================
    DrawTextEx(myFont, "Quản lý thông tin nhân sự", {(float)startX + 20, (float)startY}, 28, 1, BLACK);

    // =====================================================
    // 4 CARD THỐNG KÊ
    // =====================================================
    int gap = 18;
    int cardW = (contentW - gap * 3) / 4;
    int cardH = 105;
    int cardY = startY + 50;

    Vector2 mousePos = GetMousePosition();

    // ---------- CARD NHÂN VIÊN ----------
    Rectangle rCard1 = {(float)startX, (float)cardY, (float)cardW, (float)cardH};
    bool hCard1 = CheckCollisionPointRec(mousePos, rCard1);
    DrawRectangleRounded({rCard1.x + 2, rCard1.y + 3, rCard1.width, rCard1.height}, 0.15f, 8, Fade(BLACK, 0.05f));
    DrawRectangleRounded(rCard1, 0.15f, 10, WHITE);
    DrawRectangleRoundedLinesEx(rCard1, 0.15f, 10, 1.2f, hCard1 ? Color{98, 70, 234, 255} : Color{225, 230, 242, 255});
    DrawCircle(startX + 48, cardY + cardH / 2, 28, Color{235, 240, 255, 255});
    DrawTextEx(myFont, "N", {(float)startX + 38, (float)cardY + cardH / 2 - 15}, 30, 1, Color{70, 105, 220, 255});
    DrawTextEx(myFont, "Nhân viên", {(float)startX + 92, (float)cardY + 18}, 20, 1, Color{110, 110, 120, 255});
    DrawTextEx(myFont, TextFormat("%d", QL->get_DB()->get_ListEmployee()->get_size()), {(float)startX + 92, (float)cardY + 48}, 28, 1, Color{40, 50, 75, 255});

    // ---------- CARD PHÒNG BAN ----------
    int x2 = startX + cardW + gap;
    Rectangle rCard2 = {(float)x2, (float)cardY, (float)cardW, (float)cardH};
    bool hCard2 = CheckCollisionPointRec(mousePos, rCard2);
    DrawRectangleRounded({rCard2.x + 2, rCard2.y + 3, rCard2.width, rCard2.height}, 0.15f, 8, Fade(BLACK, 0.05f));
    DrawRectangleRounded(rCard2, 0.15f, 10, WHITE);
    DrawRectangleRoundedLinesEx(rCard2, 0.15f, 10, 1.2f, hCard2 ? Color{98, 70, 234, 255} : Color{225, 230, 242, 255});
    DrawCircle(x2 + 48, cardY + cardH / 2, 28, Color{235, 240, 255, 255});
    DrawTextEx(myFont, "P", {(float)x2 + 38, (float)cardY + cardH / 2 - 15}, 30, 1, Color{70, 105, 220, 255});
    DrawTextEx(myFont, "Phòng ban", {(float)x2 + 92, (float)cardY + 18}, 20, 1, Color{110, 110, 120, 255});
    DrawTextEx(myFont, TextFormat("%d", QL->get_DB()->get_ListPB()->get_size()), {(float)x2 + 92, (float)cardY + 48}, 28, 1, Color{40, 50, 75, 255});

    // ---------- CARD CHỨC VỤ ----------
    int x3 = startX + (cardW + gap) * 2;
    Rectangle rCard3 = {(float)x3, (float)cardY, (float)cardW, (float)cardH};
    bool hCard3 = CheckCollisionPointRec(mousePos, rCard3);
    DrawRectangleRounded({rCard3.x + 2, rCard3.y + 3, rCard3.width, rCard3.height}, 0.15f, 8, Fade(BLACK, 0.05f));
    DrawRectangleRounded(rCard3, 0.15f, 10, WHITE);
    DrawRectangleRoundedLinesEx(rCard3, 0.15f, 10, 1.2f, hCard3 ? Color{98, 70, 234, 255} : Color{225, 230, 242, 255});
    DrawCircle(x3 + 48, cardY + cardH / 2, 28, Color{235, 240, 255, 255});
    DrawTextEx(myFont, "C", {(float)x3 + 38, (float)cardY + cardH / 2 - 15}, 30, 1, Color{70, 105, 220, 255});
    DrawTextEx(myFont, "Chức vụ", {(float)x3 + 92, (float)cardY + 18}, 20, 1, Color{110, 110, 120, 255});
    DrawTextEx(myFont, TextFormat("%d", QL->get_DB()->get_ListCV()->get_size()), {(float)x3 + 92, (float)cardY + 48}, 28, 1, Color{40, 50, 75, 255});

    // ---------- CARD VỊ TRÍ ----------
    int x4 = startX + (cardW + gap) * 3;
    Rectangle rCard4 = {(float)x4, (float)cardY, (float)cardW, (float)cardH};
    bool hCard4 = CheckCollisionPointRec(mousePos, rCard4);
    DrawRectangleRounded({rCard4.x + 2, rCard4.y + 3, rCard4.width, rCard4.height}, 0.15f, 8, Fade(BLACK, 0.05f));
    DrawRectangleRounded(rCard4, 0.15f, 10, WHITE);
    DrawRectangleRoundedLinesEx(rCard4, 0.15f, 10, 1.2f, hCard4 ? Color{98, 70, 234, 255} : Color{225, 230, 242, 255});
    DrawCircle(x4 + 48, cardY + cardH / 2, 28, Color{235, 240, 255, 255});
    DrawTextEx(myFont, "V", {(float)x4 + 38, (float)cardY + cardH / 2 - 15}, 30, 1, Color{70, 105, 220, 255});
    DrawTextEx(myFont, "Vị trí", {(float)x4 + 92, (float)cardY + 18}, 20, 1, Color{110, 110, 120, 255});
    DrawTextEx(myFont, TextFormat("%d", QL->get_DB()->get_ListVTVL()->get_size()), {(float)x4 + 92, (float)cardY + 48}, 28, 1, Color{40, 50, 75, 255});

    // =====================================================
    // KHUNG NHÂN VIÊN THEO PHÒNG BAN
    // =====================================================
    int boxY = cardY + cardH + 25;
    int boxH = 310;

    DrawRectangleRounded({(float)startX, (float)boxY, (float)contentW, (float)boxH}, 0.05f, 10, WHITE);
    DrawTextEx(myFont, "PHÂN BỐ NHÂN VIÊN THEO PHÒNG BAN", {(float)startX + 20, (float)boxY + 12}, 24, 1, Color{45, 55, 80, 255});
    DrawTextEx(myFont, "Số lượng nhân viên của từng phòng ban", {(float)startX + 20, (float)boxY + 44}, 18, 1, Color{145, 145, 155, 255});

    static int scrollPB = 0;
    Rectangle khuVucPB = {(float)startX, (float)boxY + 75, (float)contentW, (float)boxH - 75};

    if (CheckCollisionPointRec(GetMousePosition(), khuVucPB))
    {
        scrollPB -= GetMouseWheelMove() * 35;
    }

    int soPB = 0;
    if (QL != nullptr && QL->get_DB()->get_ListPB() != nullptr)
        soPB = QL->get_DB()->get_ListPB()->get_size();

    int contentH_PB = soPB * 50 + 15;
    int visibleH_PB = boxH - 75;
    int maxScrollPB = contentH_PB - visibleH_PB;

    if (maxScrollPB < 0)
        maxScrollPB = 0;
    if (scrollPB < 0)
        scrollPB = 0;
    if (scrollPB > maxScrollPB)
        scrollPB = maxScrollPB;

    BeginScissorMode(startX, boxY + 75, contentW, boxH - 75);

    if (QL != nullptr && QL->get_DB()->get_ListPB() != nullptr)
    {
        List<PhongBan> *listPB = QL->get_DB()->get_ListPB();
        Node<PhongBan> *p = listPB->get_header()->Next;
        int y = boxY + 90 - scrollPB;

        int maxNV = 1;
        float maxTenW = 0;

        Node<PhongBan> *temp = listPB->get_header()->Next;
        while (temp != nullptr)
        {
            if (temp->Data != nullptr)
            {
                int soNV = QL->DemNVThamChieuPB(temp->Data);
                if (soNV > maxNV)
                    maxNV = soNV;
                string ten = temp->Data->get_TenPhongBan();
                float w = MeasureTextEx(myFont, ten.c_str(), 22, 1).x;
                if (w > maxTenW)
                    maxTenW = w;
            }
            temp = temp->Next;
        }

        while (p != nullptr)
        {
            if (p->Data != nullptr)
            {
                string tenPB = p->Data->get_TenPhongBan();
                int soNV = QL->DemNVThamChieuPB(p->Data);

                DrawTextEx(myFont, tenPB.c_str(), {(float)startX + 20, (float)y}, 22, 1, Color{60, 65, 80, 255});

                int barX = startX + 20 + (int)maxTenW + 20;
                int barW = startX + contentW - 80 - barX;
                if (barW < 50)
                    barW = 50;
                DrawRectangleRounded({(float)barX, (float)y + 3, (float)barW, 15}, 0.5f, 10, Color{230, 235, 248, 255});

                float percent = (float)soNV / maxNV;
                DrawRectangleRounded({(float)barX, (float)y + 3, barW * percent, 15}, 0.5f, 10, Color{90, 125, 235, 255});
                DrawTextEx(myFont, TextFormat("%d", soNV), {(float)startX + contentW - 60, (float)y}, 20, 1, Color{70, 80, 100, 255});

                y += 50;
            }
            p = p->Next;
        }
    }
    EndScissorMode();

    // =========================================================
    // KHUNG PHÂN BỔ VỊ TRÍ VIỆC LÀM
    // =========================================================
    int vtBoxY = boxY + boxH + 25;
    int vtBoxH = 310;

    DrawRectangleRounded({(float)startX, (float)vtBoxY, (float)contentW, (float)vtBoxH}, 0.05f, 10, WHITE);
    DrawTextEx(myFont, "PHÂN BỐ VỊ TRÍ VIỆC LÀM", {(float)startX + 20, (float)vtBoxY + 12}, 24, 1, Color{45, 55, 80, 255});
    DrawTextEx(myFont, "Số lượng nhân viên đang đảm nhận từng vị trí", {(float)startX + 20, (float)vtBoxY + 44}, 18, 1, Color{145, 145, 155, 255});

    static int scrollVT = 0;
    Rectangle khuVucVT = {(float)startX, (float)vtBoxY + 75, (float)contentW, (float)vtBoxH - 75};

    if (CheckCollisionPointRec(GetMousePosition(), khuVucVT))
    {
        scrollVT -= GetMouseWheelMove() * 35;
    }

    int soVT = 0;
    if (QL != nullptr && QL->get_DB()->get_ListVTVL() != nullptr)
        soVT = QL->get_DB()->get_ListVTVL()->get_size();

    int contentH_VT = soVT * 50 + 15;
    int visibleH_VT = vtBoxH - 75;
    int maxScrollVT = contentH_VT - visibleH_VT;

    if (maxScrollVT < 0)
        maxScrollVT = 0;
    if (scrollVT < 0)
        scrollVT = 0;
    if (scrollVT > maxScrollVT)
        scrollVT = maxScrollVT;

    BeginScissorMode(startX, vtBoxY + 75, contentW, vtBoxH - 75);

    int maxNV_VT = 1;
    float maxTenW = 0;
    if (QL != nullptr && QL->get_DB()->get_ListVTVL() != nullptr)
    {
        Node<ViTriViecLam> *tempVT = QL->get_DB()->get_ListVTVL()->get_header()->Next;
        while (tempVT != nullptr)
        {
            if (tempVT->Data != nullptr)
            {
                int soNV = QL->DemNVThamChieuVT(tempVT->Data);
                if (soNV > maxNV_VT)
                    maxNV_VT = soNV;
                string ten = tempVT->Data->get_TenVTVL();
                float w = MeasureTextEx(myFont, ten.c_str(), 22, 1).x;
                if (w > maxTenW)
                    maxTenW = w;
            }
            tempVT = tempVT->Next;
        }
    }

    if (QL != nullptr && QL->get_DB()->get_ListVTVL() != nullptr)
    {
        List<ViTriViecLam> *listVT = QL->get_DB()->get_ListVTVL();
        Node<ViTriViecLam> *pVT = listVT->get_header()->Next;
        int y = vtBoxY + 90 - scrollVT;

        while (pVT != nullptr)
        {
            if (pVT->Data != nullptr)
            {
                string tenVT = pVT->Data->get_TenVTVL();
                int soNV = QL->DemNVThamChieuVT(pVT->Data);

                DrawTextEx(myFont, tenVT.c_str(), {(float)startX + 20, (float)y}, 22, 1, Color{60, 65, 80, 255});

                int barX = startX + 20 + (int)maxTenW + 20;
                int barW = startX + contentW - 80 - barX;
                if (barW < 50)
                    barW = 50;
                DrawRectangleRounded({(float)barX, (float)y + 3, (float)barW, 15}, 0.5f, 10, Color{230, 235, 248, 255});

                float percent = (float)soNV / maxNV_VT;
                DrawRectangleRounded({(float)barX, (float)y + 3, barW * percent, 15}, 0.5f, 10, Color{90, 125, 235, 255});
                DrawTextEx(myFont, TextFormat("%d", soNV), {(float)startX + contentW - 60, (float)y}, 20, 1, Color{70, 80, 100, 255});

                y += 50;
            }
            pVT = pVT->Next;
        }
    }

    EndScissorMode();
}
