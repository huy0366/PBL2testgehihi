#pragma once
#include "GUI_Common.h"

void Draw_Screen_PhongBan(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_ChucVu(Vector2 mousepos, bool Clicked, QLNV *QL);
void Draw_Screen_Deparment(QLNV *QL);

void Draw_Screen_PhongBan(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    // Vẽ tiêu đề
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;
    static bool isMaPhongBanActive = false; // Trạng thái: ô có đang được click vào không
    if (doReset)
        isMaPhongBanActive = false;
    static bool isTenPhongBanActive = false; // Trạng thái: ô có đang được click vào không
    if (doReset)
        isTenPhongBanActive = false;
    static bool isOpenCalendar = false;
    if (doReset)
        isOpenCalendar = false;
    static bool OpenThem = false;
    if (doReset)
        OpenThem = false;
    static bool OpenSua = false;
    if (doReset)
        OpenSua = false;
    static List<PhongBan> *dsXoa = nullptr;
    static bool OpenXoa = false;
    if (doReset)
    {
        if (OpenXoa)
            delete dsXoa;
        dsXoa = nullptr;
        OpenXoa = false;
    }
    static bool needfill = false;
    if (doReset)
        needfill = false;
    static bool hoiXoa = false;
    if (doReset)
        hoiXoa = false;

    Rectangle panelBang1 = {330, 230, 1450.0f, 300.0f};
    DrawRectangleRounded({panelBang1.x + 3, panelBang1.y + 4, panelBang1.width, panelBang1.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang1, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang1, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Thông tin phòng ban", {360.0f, 250.0f}, 28, 1, Color{20, 25, 35, 255});

    static Texture2D a1;
    static bool isLoaded = false;
    if (!isLoaded)
    {
        a1 = LoadTexture("photo/anhto/pban.png");
        isLoaded = true;
    }
    Vector2 pa1 = {360.0f, 310.0f}; // Tọa độ (x, y) postion
    float ra1 = 0.0f;               // Góc xoay (0 độ) rotation
    float sa1 = 0.6f;
    DrawTextureEx(a1, pa1, ra1, sa1, WHITE);

    Rectangle textMaPhongBan = {930, 330, 300, 40};
    static char MaPhongBanInput[50] = "\0"; // Chuỗi lưu ký tự người dùng gõ
    if (doReset)
        MaPhongBanInput[0] = '\0';
    static int letterCount_Ma = 0;
    if (doReset)
        letterCount_Ma = 0;
    DrawTextEx(myFont, "Mã Phòng Ban:", {700.0f, textMaPhongBan.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool maActive = OpenThem && isMaPhongBanActive;
    DrawRectangleRounded(textMaPhongBan, 0.3f, 6, maActive ? Color{248, 250, 252, 255} : (OpenSua ? Color{240, 243, 246, 255} : WHITE));
    DrawRectangleRoundedLinesEx(textMaPhongBan, 0.3f, 6, 1.5f, maActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    Rectangle textTenPhongBan = {textMaPhongBan.x, textMaPhongBan.y + 60, 300, 40};
    static char TenPhongBanInput[50] = "\0"; // Chuỗi lưu ký tự người dùng gõ
    if (doReset)
        TenPhongBanInput[0] = '\0';
    static int letterCount_Ten = 0;
    if (doReset)
        letterCount_Ten = 0;
    DrawTextEx(myFont, "Tên Phòng Ban:", {700.0f, textTenPhongBan.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool tenActive = (OpenThem || OpenSua) && isTenPhongBanActive;
    DrawRectangleRounded(textTenPhongBan, 0.3f, 6, tenActive ? Color{248, 250, 252, 255} : WHITE);
    DrawRectangleRoundedLinesEx(textTenPhongBan, 0.3f, 6, 1.5f, tenActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    Rectangle textNgayThanhLap = {textTenPhongBan.x, textTenPhongBan.y + 60, 300, 40};
    static int day1 = day, month1 = month, year1 = year;
    if (doReset)
    {
        day1 = day;
        month1 = month;
        year1 = year;
    }
    DrawTextEx(myFont, "Ngày thành lập:", {700.0f, textNgayThanhLap.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool calActive = (OpenThem || OpenSua) && isOpenCalendar;
    DrawRectangleRounded(textNgayThanhLap, 0.3f, 6, calActive ? Color{248, 250, 252, 255} : WHITE);
    DrawRectangleRoundedLinesEx(textNgayThanhLap, 0.3f, 6, 1.5f, calActive ? Color{50, 100, 220, 255} : LIGHTGRAY);
    string textCalendar = to_string(day1) + '/' + to_string(month1) + '/' + to_string(year1);
    if (day1 < 10)
    {
        textCalendar = '0' + textCalendar;
    }
    if (month1 < 10)
    {
        textCalendar.insert(3, "0");
    }

    if (!OpenThem && !OpenSua)
    {
        isMaPhongBanActive = false;
        isTenPhongBanActive = false;
        isOpenCalendar = false;
    }
    else if (Clicked)
    {
        if (OpenThem)
        {
            if (CheckCollisionPointRec(mousePos, textMaPhongBan))
            {
                isMaPhongBanActive = true;
                isTenPhongBanActive = isOpenCalendar = false;
            }
            else if (CheckCollisionPointRec(mousePos, textTenPhongBan))
            {
                isTenPhongBanActive = true;
                isMaPhongBanActive = isOpenCalendar = false;
            }
            else if (CheckCollisionPointRec(mousePos, textNgayThanhLap))
            {
                isOpenCalendar = true;
                isMaPhongBanActive = isTenPhongBanActive = false;
            }
            else
            {
                isMaPhongBanActive = isTenPhongBanActive = false;
            }
        }
        else if (OpenSua)
        {
            isMaPhongBanActive = false; // Mã không được sửa
            if (CheckCollisionPointRec(mousePos, textTenPhongBan))
            {
                isTenPhongBanActive = true;
                isOpenCalendar = false;
            }
            else if (CheckCollisionPointRec(mousePos, textNgayThanhLap))
            {
                isOpenCalendar = true;
                isTenPhongBanActive = false;
            }
            else
            {
                isTenPhongBanActive = false;
            }
        }
    }

    // Vẽ nút chức năng để ở trên để không bị che
    Rectangle btnThemPhongBan = {350, 940, 280, 50};
    Rectangle btnSuaPhongBan = {660, 940, 280, 50};
    Rectangle btnXoaPhongBan = {970, 940, 280, 50};

    Rectangle btnXacNhan = {350, 940, 230, 50};
    static bool isXacNhan = false;
    if (doReset)
        isXacNhan = false;
    Rectangle btnHuy = {610, 940, 230, 50};
    static bool isHuy = false;
    if (doReset)
        isHuy = false;

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
        bool hoverThem = CheckCollisionPointRec(mousePos, btnThemPhongBan);
        VeNutChucNang(btnThemPhongBan, "Thêm Phòng Ban", NutStyle::Green, hoverThem, 1);

        bool hoverSua = CheckCollisionPointRec(mousePos, btnSuaPhongBan);
        VeNutChucNang(btnSuaPhongBan, "Sửa Phòng Ban", NutStyle::Blue, hoverSua, 2);

        bool hoverXoa = CheckCollisionPointRec(mousePos, btnXoaPhongBan);
        VeNutChucNang(btnXoaPhongBan, "Xóa Phòng Ban", NutStyle::Red, hoverXoa, 3);
    }

    // Bảng 2
    Rectangle panelBang2 = {330, panelBang1.y + panelBang1.height + 30, 1450.0f, 370.0f};
    DrawRectangleRounded({panelBang2.x + 3, panelBang2.y + 4, panelBang2.width, panelBang2.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang2, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang2, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});
    static float scrollY = 0.0f;
    if (doReset)
        scrollY = 0.0f;
    float scrollSpeed = 30.0f; // Tốc độ cuộn mỗi nấc chuột

    // Lấy thao tác lăn chuột và cộng dồn vào scrollY
    float wheel = GetMouseWheelMove(); // Lăn chuột xuống trả về -1 ngược lại lên
    if (wheel != 0.0f)
    {
        scrollY += wheel * scrollSpeed;
    }

    // Chặn cuộn quá đà lên trên (danh sách không bị tụt xuống dưới tiêu đề)
    if (scrollY > 0.0f)
        scrollY = 0.0f;
    // Cấu hình khoảng cách và kích thước chữ
    int startX = panelBang2.x + 20; // Lề trái
    int startY = panelBang2.y + 20; // Lề trên
    int rowHeight = 60;             // Chiều cao mỗi dòng
    int fontSize = 24;              // Kích thước chữ chuẩn đồng bộ với Chấm Công

    // Tọa độ X của từng cột (Bạn cần tinh chỉnh các số này cho vừa với màn hình)
    int colX[] = {350, 600, 900, 1250, 1400, 1500};

    // 1. VẼ TIÊU ĐỀ CỘT (Header)
    float lech = OpenXoa ? 30.f : 0.f;
    DrawTextEx(myFont, "Mã Phòng Ban", {colX[0] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Tên Phòng Ban", {colX[1] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Ngày Thành Lập", {colX[2] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Số Lượng", {colX[3] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Nam", {colX[4] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Nữ", {colX[5] + lech, (float)startY}, fontSize, 1, DARKGRAY);

    // Kẻ đường gạch ngang dưới tiêu đề
    DrawLine(startX, startY + 30, 1900, startY + 30, LIGHTGRAY);

    // 4. KHU VỰC VẼ DANH SÁCH BỊ CẮT (Scissor Mode)
    int listStartY = startY + 60;                         // Điểm bắt đầu vẽ dữ liệu (ngay dưới đường kẻ)
    int listHeight = GetScreenHeight() - listStartY - 90; // Chiều cao khu vực hiển thị dữ liệu

    // Bật chế độ Scissor: Bất cứ thứ gì vẽ bên ngoài hình chữ nhật này sẽ bị ẩn đi
    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    // Chỉ hover khi chuột nằm trong vùng danh sách
    bool canHover = CheckCollisionPointRec(mousePos, listArea);

    // Tọa độ Y hiện tại bắt đầu = Tọa độ gốc + Độ lệch cuộn
    float currentY = listStartY + scrollY;

    Node<PhongBan> *current = QL->get_DB()->get_ListPB()->get_header()->Next;

    // Đếm tổng số lượng dòng để chặn cuộn quá đà xuống dưới (tùy chọn nâng cao)
    int totalRows = 0;

    PhongBan *selPB = nullptr;
    static string selectedPhongBan = "";
    if (doReset)
        selectedPhongBan = "";
    while (current != nullptr)
    {
        string mpb = current->Data->get_MaPhongBan();
        string name = current->Data->get_TenPhongBan();
        string NTL = current->Data->get_NgayThanhLap().ToString();
        int size = current->Data->get_ListNV()->get_size();
        string pb_size = to_string(size);
        string nam = to_string(current->Data->get_nam());
        string nu = to_string(current->Data->get_nu());
        // ----- HOVER + CHỌN DÒNG -----
        Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
        bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
        if (isHover && Clicked)
        {
            if (OpenXoa)
            {
                Node<PhongBan> *nd = dsXoa->find_ptr(current->Data);
                if (nd != nullptr)
                    dsXoa->remove_item(nd);
                else
                    dsXoa->insert(current->Data);
            }
            else
            {
                selectedPhongBan = mpb;
                needfill = true;
            }
        }
        bool isSelected = (mpb == selectedPhongBan);

        if (OpenXoa)
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
            // đã chọn: đậm hơn; vừa chọn vừa rê chuột: đậm thêm chút
            DrawRectangleRec(rowRect, isHover ? Color{180, 195, 230, 255} : Color{200, 210, 235, 255});
            // lưu phòng ban đang chọn
            selPB = current->Data;
        }
        else if (isHover)
        {
            DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
        }
        // ------------------------------

        DrawTextEx(myFont, mpb.c_str(), {colX[0] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, name.c_str(), {colX[1] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, NTL.c_str(), {colX[2] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, pb_size.c_str(), {colX[3] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, nam.c_str(), {colX[4] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, nu.c_str(), {colX[5] + lech, currentY}, fontSize, 1, BLACK);
        DrawLine(startX, currentY + 30, GetScreenWidth() - 20, currentY + 30, Fade(LIGHTGRAY, 0.5f));

        currentY += rowHeight;
        totalRows++;

        current = current->Next;
    }

    // Tính toán chiều cao tổng của danh sách để chặn cuộn quá đáy
    float totalListHeight = totalRows * rowHeight;
    float maxScroll = listHeight - totalListHeight;
    // Nếu danh sách dài hơn màn hình và cuộn quá mức dưới, ép nó về mức tối đa
    if (totalListHeight > listHeight && scrollY < maxScroll)
    {
        scrollY = maxScroll;
    }
    // Nếu danh sách ngắn hơn màn hình, không cho cuộn
    else if (totalListHeight <= listHeight)
    {
        scrollY = 0.0f;
    }

    // Tắt chế độ Scissor để các phần vẽ sau (nếu có) không bị ảnh hưởng
    EndScissorMode();

    if (OpenXoa)
    {
        if (Clicked && CheckCollisionPointRec(mousePos, btnHuyXoa))
        {
            delete dsXoa;
            OpenXoa = false;
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnXacNhanXoa))
        {
            if (dsXoa->get_size() == 0)
                HienThongBao("Chưa chọn phòng ban nào để xóa!", true);
            else
                hoiXoa = true;
        }
    }
    if (OpenXoa && dsXoa != nullptr)
    {
        if (XacNhan("Bạn có chắc muốn xóa " + to_string(dsXoa->get_size()) + " phòng ban đã chọn?", hoiXoa))
        {
            int dem = 0;
            string loiCuoi = "";
            for (Node<PhongBan> *p = dsXoa->get_header()->Next; p != nullptr; p = p->Next)
            {
                try
                {
                    QL->XoaPhongBan(p->Data);
                    dem++;
                }
                catch (const string &loi)
                {
                    loiCuoi = loi;
                }
            }

            if (dem > 0)
            {
                if (loiCuoi.empty())
                    HienThongBao("Đã xóa " + to_string(dem) + " phòng ban thành công!", false);
                else
                    HienThongBao("Đã xóa " + to_string(dem) + " phòng ban. " + loiCuoi, true);
            }
            else
                HienThongBao(loiCuoi.empty() ? "Xóa không thành công!" : loiCuoi, true);

            delete dsXoa;
            dsXoa = nullptr;
            OpenXoa = false;
            MaPhongBanInput[0] = '\0';
            TenPhongBanInput[0] = '\0';
            textCalendar = "";
            letterCount_Ma = letterCount_Ten = 0;
        }
    }
    else if (Clicked && (OpenThem || OpenSua))
    {
        // Chỉ xử lý Xác nhận
        if (Clicked && CheckCollisionPointRec(mousePos, btnXacNhan))
        {
            isXacNhan = true;
        }
        // Chỉ xử lý Hủy
        else if (Clicked && CheckCollisionPointRec(mousePos, btnHuy))
        {
            isHuy = true;
        }
    }
    else
    {
        if (Clicked && CheckCollisionPointRec(mousePos, btnThemPhongBan))
        {
            OpenThem = true;
            MaPhongBanInput[0] = '\0';
            TenPhongBanInput[0] = '\0';
            textCalendar = "";
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            isMaPhongBanActive = true;
            isTenPhongBanActive = false;
            isOpenCalendar = false;
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnSuaPhongBan))
        {
            OpenSua = true;
            isMaPhongBanActive = false;
            isTenPhongBanActive = true;
            isOpenCalendar = false;
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnXoaPhongBan))
        {
            OpenXoa = true;
            dsXoa = new List<PhongBan>;
            isMaPhongBanActive = isTenPhongBanActive = isOpenCalendar = false;
        }
    }
    if (needfill && selPB != nullptr)
    {
        strncpy(MaPhongBanInput, selPB->get_MaPhongBan().c_str(), 49);
        letterCount_Ma = strlen(MaPhongBanInput);
        MaPhongBanInput[letterCount_Ma] = '\0';

        strncpy(TenPhongBanInput, selPB->get_TenPhongBan().c_str(), 49);
        letterCount_Ten = strlen(TenPhongBanInput);
        TenPhongBanInput[letterCount_Ten] = '\0';

        textCalendar = selPB->get_NgayThanhLap().ToString();
        needfill = false;
    }

    if (OpenThem)
    {
        Typing(isMaPhongBanActive, MaPhongBanInput, letterCount_Ma, mousePos, textMaPhongBan);
        HieuUngGo(isMaPhongBanActive, textMaPhongBan, MaPhongBanInput, 22);

        Typing(isTenPhongBanActive, TenPhongBanInput, letterCount_Ten, mousePos, textTenPhongBan);
        HieuUngGo(isTenPhongBanActive, textTenPhongBan, TenPhongBanInput, 22);
        DrawTextEx(myFont, textCalendar.c_str(), {textNgayThanhLap.x + 10, textNgayThanhLap.y + 9}, 22, 1, BLACK);
        if (isOpenCalendar)
        {
            DrawCalendar(mousePos, day1, month1, year1, textNgayThanhLap, isOpenCalendar);
        }
    }
    else if (OpenSua && selPB != nullptr)
    { // Ô nhập chữ chế độ sửa
        DrawTextEx(myFont, MaPhongBanInput, {textMaPhongBan.x + 10, textMaPhongBan.y + 9}, 22, 1, BLACK);
        Typing(isTenPhongBanActive, TenPhongBanInput, letterCount_Ten, mousePos, textTenPhongBan);
        HieuUngGo(isTenPhongBanActive, textTenPhongBan, TenPhongBanInput, 22);
        DrawTextEx(myFont, textCalendar.c_str(), {textNgayThanhLap.x + 10, textNgayThanhLap.y + 9}, 22, 1, BLACK);
        if (isOpenCalendar)
        {
            DrawCalendar(mousePos, day1, month1, year1, textNgayThanhLap, isOpenCalendar);
        }
    }
    else if (selPB != nullptr || MaPhongBanInput[0] != '\0')
    {
        // Khi click vào 1 đối tượng trong danh sách (chế độ xem)
        DrawTextEx(myFont, MaPhongBanInput, {textMaPhongBan.x + 10, textMaPhongBan.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, TenPhongBanInput, {textTenPhongBan.x + 10, textTenPhongBan.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, textCalendar.c_str(), {textNgayThanhLap.x + 10, textNgayThanhLap.y + 9}, 22, 1, BLACK);
    }

    if (isXacNhan)
    {
        if (OpenThem)
        {
            PhongBan *Pbnew = new PhongBan(MaPhongBanInput, TenPhongBanInput, Date(textCalendar));
            try
            {
                QL->ThemPhongBan(Pbnew);
                HienThongBao("Thêm phòng ban mới thành công!", false); // true màu đỏ
            }
            catch (const string &loi)
            {
                HienThongBao(loi, true); // true màu đỏ
            }
            needfill = false;
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
            isMaPhongBanActive = isTenPhongBanActive = isOpenCalendar = false;
            MaPhongBanInput[0] = '\0';
            TenPhongBanInput[0] = '\0';
            day1 = day, month1 = month, year1 = year;
        }
        else if (OpenSua && selPB != nullptr)
        {
            PhongBan *PBtam = new PhongBan(selPB->get_MaPhongBan(), TenPhongBanInput, Date(textCalendar));
            try
            {
                QL->SuaPhongBan(PBtam);
                HienThongBao("Cập nhật phòng ban thành công!", false);
            }
            catch (const string &e)
            {
                HienThongBao(e, true);
            }
            delete PBtam;
            OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
            isMaPhongBanActive = isTenPhongBanActive = isOpenCalendar = false;
            MaPhongBanInput[0] = '\0';
            TenPhongBanInput[0] = '\0';
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            day1 = day, month1 = month, year1 = year;
        }
    }

    if (isHuy && CheckCollisionPointRec(mousePos, btnHuy))
    {
        OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
        isMaPhongBanActive = isTenPhongBanActive = isOpenCalendar = false;
        MaPhongBanInput[0] = '\0';
        TenPhongBanInput[0] = '\0';
        letterCount_Ma = 0;
        letterCount_Ten = 0;
        day1 = day, month1 = month, year1 = year;
    }

    DrawTextEx(myFont, ("Tổng phòng ban: " + to_string(QL->get_DB()->get_ListPB()->get_size())).c_str(), {1550, 960}, 20, 1, DARKGRAY);
}

void Draw_Screen_ChucVu(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    Vector2 mousepos = mousePos;
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static bool isMaChucVuActive = false;
    if (doReset)
        isMaChucVuActive = false;
    static bool isTenChucVuActive = false;
    if (doReset)
        isTenChucVuActive = false;
    static bool isPhucCapActive = false;
    if (doReset)
        isPhucCapActive = false;
    static bool OpenThem = false;
    if (doReset)
        OpenThem = false;
    static bool OpenSua = false;
    if (doReset)
        OpenSua = false;
    static List<ChucVu> *dsXoa = nullptr;
    static bool OpenXoa = false;
    if (doReset)
    {
        if (OpenXoa)
            delete dsXoa;
        dsXoa = nullptr;
        OpenXoa = false;
    }
    static bool needfill = false;
    if (doReset)
        needfill = false;
    static bool hoiXoa = false;
    if (doReset)
        hoiXoa = false;

    Rectangle panelBang1 = {330, 230, 1450.0f, 300.0f};
    DrawRectangleRounded({panelBang1.x + 3, panelBang1.y + 4, panelBang1.width, panelBang1.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang1, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang1, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Thông tin chức vụ", {360.0f, 250.0f}, 28, 1, Color{20, 25, 35, 255});

    static Texture2D a1;
    static bool isLoaded = false;
    if (!isLoaded)
    {
        a1 = LoadTexture("photo/anhto/cvu.png");
        isLoaded = true;
    }
    Vector2 pa1 = {360.0f, 310.0f}; // Tọa độ (x, y) postion
    float ra1 = 0.0f;               // Góc xoay (0 độ) rotation
    float sa1 = 0.6f;
    DrawTextureEx(a1, pa1, ra1, sa1, WHITE);

    Rectangle MaChucVu = {930, 330, 300, 40};
    static char MaChucVuInput[50] = "\0"; // Chuỗi lưu ký tự người dùng gõ
    if (doReset)
        MaChucVuInput[0] = '\0';
    static int letterCount_Ma = 0;
    if (doReset)
        letterCount_Ma = 0;
    DrawTextEx(myFont, "Mã Chức Vụ:", {700.0f, MaChucVu.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool maActive = OpenThem && isMaChucVuActive;
    DrawRectangleRounded(MaChucVu, 0.3f, 6, maActive ? Color{248, 250, 252, 255} : (OpenSua ? Color{240, 243, 246, 255} : WHITE));
    DrawRectangleRoundedLinesEx(MaChucVu, 0.3f, 6, 1.5f, maActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    Rectangle TenChucVu = {MaChucVu.x, MaChucVu.y + 60, 300, 40};
    static char TenChucVuInput[50] = "\0";
    if (doReset)
        TenChucVuInput[0] = '\0';
    static int letterCount_Ten = 0;
    if (doReset)
        letterCount_Ten = 0;
    DrawTextEx(myFont, "Tên Chức Vụ:", {700.0f, TenChucVu.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool tenActive = (OpenThem || OpenSua) && isTenChucVuActive;
    DrawRectangleRounded(TenChucVu, 0.3f, 6, tenActive ? Color{248, 250, 252, 255} : WHITE);
    DrawRectangleRoundedLinesEx(TenChucVu, 0.3f, 6, 1.5f, tenActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    Rectangle PhucCap = {TenChucVu.x, TenChucVu.y + 60, 300, 40};
    static char PhuCapInput[50] = "\0";
    if (doReset)
        PhuCapInput[0] = '\0';
    static int letterCount_PhuCap = 0;
    if (doReset)
        letterCount_PhuCap = 0;
    DrawTextEx(myFont, "Phụ Cấp:", {700.0f, PhucCap.y + 7}, 22, 1, Color{50, 60, 75, 255});
    bool pcActive = (OpenThem || OpenSua) && isPhucCapActive;
    DrawRectangleRounded(PhucCap, 0.3f, 6, pcActive ? Color{248, 250, 252, 255} : WHITE);
    DrawRectangleRoundedLinesEx(PhucCap, 0.3f, 6, 1.5f, pcActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    if (letterCount_PhuCap > 0)
    {
        long long valPC = atoll(PhuCapInput);
        if (valPC > 0)
        {
            string fmt = FormatSoTien(valPC) + " đ/tháng";
            DrawTextEx(myFont, fmt.c_str(), {PhucCap.x + 320, PhucCap.y + 9}, 22, 1, Color{40, 80, 200, 255});
        }
    }

    if (!OpenThem && !OpenSua)
    {
        isMaChucVuActive = false;
        isTenChucVuActive = false;
        isPhucCapActive = false;
    }
    else if (Clicked)
    {
        if (OpenThem)
        {
            if (CheckCollisionPointRec(mousepos, MaChucVu))
            {
                isMaChucVuActive = true;
                isTenChucVuActive = isPhucCapActive = false;
            }
            else if (CheckCollisionPointRec(mousepos, TenChucVu))
            {
                isTenChucVuActive = true;
                isMaChucVuActive = isPhucCapActive = false;
            }
            else if (CheckCollisionPointRec(mousepos, PhucCap))
            {
                isPhucCapActive = true;
                isMaChucVuActive = isTenChucVuActive = false;
            }
            else
            {
                isMaChucVuActive = isTenChucVuActive = isPhucCapActive = false;
            }
        }
        else if (OpenSua)
        {
            isMaChucVuActive = false; // Mã không được sửa
            if (CheckCollisionPointRec(mousepos, TenChucVu))
            {
                isTenChucVuActive = true;
                isPhucCapActive = false;
            }
            else if (CheckCollisionPointRec(mousepos, PhucCap))
            {
                isPhucCapActive = true;
                isTenChucVuActive = false;
            }
            else
            {
                isTenChucVuActive = isPhucCapActive = false;
            }
        }
    }

    Rectangle btnThemChucVu = {350, 940, 280, 50};
    Rectangle btnSuaChucVu = {660, 940, 280, 50};
    Rectangle btnXoa = {970, 940, 280, 50};

    Rectangle btnXacNhan = {350, 940, 230, 50};
    static bool isXacNhan = false;
    if (doReset)
        isXacNhan = false;
    Rectangle btnHuy = {610, 940, 230, 50};
    static bool isHuy = false;
    if (doReset)
        isHuy = false;

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
        bool hoverThem = CheckCollisionPointRec(mousePos, btnThemChucVu);
        VeNutChucNang(btnThemChucVu, "Thêm Chức Vụ", NutStyle::Green, hoverThem, 1);

        bool hoverSua = CheckCollisionPointRec(mousePos, btnSuaChucVu);
        VeNutChucNang(btnSuaChucVu, "Sửa Chức Vụ", NutStyle::Blue, hoverSua, 2);

        bool hoverXoa = CheckCollisionPointRec(mousePos, btnXoa);
        VeNutChucNang(btnXoa, "Xóa Chức Vụ", NutStyle::Red, hoverXoa, 3);
    }

    Rectangle panelBang2 = {330, panelBang1.y + panelBang1.height + 30, 1450.0f, 370.0f};
    DrawRectangleRounded({panelBang2.x + 3, panelBang2.y + 4, panelBang2.width, panelBang2.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang2, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang2, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});
    // 1. TẠO BIẾN CUỘN (Dùng 'static' để giữ nguyên giá trị qua mỗi khung hình)
    static float scrollY = 0.0f;
    if (doReset)
        scrollY = 0.0f;
    float scrollSpeed = 30.0f; // Tốc độ cuộn mỗi nấc chuột

    // Lấy thao tác lăn chuột và cộng dồn vào scrollY
    float wheel = GetMouseWheelMove(); // Lăn chuột xuống trả về -1 ngược lại lên
    if (wheel != 0.0f)
    {
        scrollY += wheel * scrollSpeed;
    }

    // Chặn cuộn quá đà lên trên (danh sách không bị tụt xuống dưới tiêu đề)
    if (scrollY > 0.0f)
        scrollY = 0.0f;
    // Cấu hình khoảng cách và kích thước chữ
    int startX = panelBang2.x + 20; // Lề trái
    int startY = panelBang2.y + 20; // Lề trên
    int rowHeight = 60;             // Chiều cao mỗi dòng
    int fontSize = 24;              // Kích thước chữ chuẩn đồng bộ với Chấm Công

    // Tọa độ X của từng cột (Bạn cần tinh chỉnh các số này cho vừa với màn hình)
    int colX[] = {350, 600, 900, 1250};

    // 1. VẼ TIÊU ĐỀ CỘT (Header)
    float lech = OpenXoa ? 30.f : 0.f;
    DrawTextEx(myFont, "Mã Chức Vụ", {colX[0] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Tên Chức Vụ", {colX[1] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Phụ Cấp", {colX[2] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Số lượng", {colX[3] + lech, (float)startY}, fontSize, 1, DARKGRAY);

    // Kẻ đường gạch ngang dưới tiêu đề
    DrawLine(startX, startY + 30, 1900, startY + 30, LIGHTGRAY);

    // 4. KHU VỰC VẼ DANH SÁCH BỊ CẮT (Scissor Mode)
    int listStartY = startY + 60;                         // Điểm bắt đầu vẽ dữ liệu (ngay dưới đường kẻ)
    int listHeight = GetScreenHeight() - listStartY - 80; // Chiều cao khu vực hiển thị dữ liệu

    // Bật chế độ Scissor: Bất cứ thứ gì vẽ bên ngoài hình chữ nhật này sẽ bị ẩn đi
    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    // Chỉ hover khi chuột nằm trong vùng danh sách
    bool canHover = CheckCollisionPointRec(mousepos, listArea);

    // Tọa độ Y hiện tại bắt đầu = Tọa độ gốc + Độ lệch cuộn
    float currentY = listStartY + scrollY;

    Node<ChucVu> *current = QL->get_DB()->get_ListCV()->get_header()->Next;

    // Đếm tổng số lượng dòng để chặn cuộn quá đà xuống dưới (tùy chọn nâng cao)
    int totalRows = 0;

    ChucVu *selCV = nullptr;
    static string selectedMCV = "";
    if (doReset)
        selectedMCV = "";
    while (current != nullptr)
    {
        string mcv = current->Data->get_MaChucVu();
        string name = current->Data->get_TenChucVu();
        string pc = FormatSoTien(current->Data->get_PhuCap());
        int size = current->Data->get_ListNV()->get_size();
        string cv_size = to_string(size);

        // ----- HOVER + CHỌN DÒNG -----
        Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
        bool isHover = canHover && CheckCollisionPointRec(mousepos, rowRect);
        if (isHover && Clicked)
        {
            if (OpenXoa)
            {
                Node<ChucVu> *nd = dsXoa->find_ptr(current->Data);
                if (nd != nullptr)
                    dsXoa->remove_item(nd);
                else
                    dsXoa->insert(current->Data);
            }
            else
            {
                selectedMCV = mcv;
                needfill = true;
            }
        }
        bool isSelected = (mcv == selectedMCV);

        if (OpenXoa)
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
            // đã chọn: đậm hơn; vừa chọn vừa rê chuột: đậm thêm chút
            DrawRectangleRec(rowRect, isHover ? Color{180, 195, 230, 255} : Color{200, 210, 235, 255});
            // lưu chức vụ đang chọn
            selCV = current->Data;
        }
        else if (isHover)
        {
            DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
        }
        // ------------------------------

        DrawTextEx(myFont, mcv.c_str(), {colX[0] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, name.c_str(), {colX[1] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, pc.c_str(), {colX[2] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, cv_size.c_str(), {colX[3] + lech, currentY}, fontSize, 1, BLACK);
        DrawLine(startX, currentY + 30, GetScreenWidth() - 20, currentY + 30, Fade(LIGHTGRAY, 0.5f));

        currentY += rowHeight;
        totalRows++;

        current = current->Next;
    }

    // Tính toán chiều cao tổng của danh sách để chặn cuộn quá đáy
    float totalListHeight = totalRows * rowHeight;
    float maxScroll = listHeight - totalListHeight;
    // Nếu danh sách dài hơn màn hình và cuộn quá mức dưới, ép nó về mức tối đa
    if (totalListHeight > listHeight && scrollY < maxScroll)
    {
        scrollY = maxScroll;
    }
    // Nếu danh sách ngắn hơn màn hình, không cho cuộn
    else if (totalListHeight <= listHeight)
    {
        scrollY = 0.0f;
    }

    // Tắt chế độ Scissor để các phần vẽ sau (nếu có) không bị ảnh hưởng
    EndScissorMode();
    if (OpenXoa)
    {
        if (Clicked && CheckCollisionPointRec(mousepos, btnHuyXoa))
        {
            delete dsXoa;
            OpenXoa = false;
        }
        else if (Clicked && CheckCollisionPointRec(mousepos, btnXacNhanXoa))
        {
            if (dsXoa->get_size() == 0)
                HienThongBao("Chưa chọn chức vụ nào để xóa!", true);
            else
                hoiXoa = true;
        }
        if (OpenXoa && dsXoa != nullptr)
        {
            if (XacNhan("Bạn có chắc muốn xóa " + to_string(dsXoa->get_size()) + " chức vụ đã chọn?", hoiXoa))
            {
                int dem = 0;
                string loiCuoi = "";
                for (Node<ChucVu> *p = dsXoa->get_header()->Next; p != nullptr; p = p->Next)
                {
                    try
                    {
                        QL->XoaChucVu(p->Data);
                        dem++;
                    }
                    catch (const string &loi)
                    {
                        loiCuoi = loi;
                    }
                }

                if (dem > 0)
                {
                    if (loiCuoi.empty())
                        HienThongBao("Đã xóa " + to_string(dem) + " chức vụ thành công!", false);
                    else
                        HienThongBao("Đã xóa " + to_string(dem) + " chức vụ. " + loiCuoi, true);
                }
                else
                    HienThongBao(loiCuoi.empty() ? "Xóa không thành công!" : loiCuoi, true);

                delete dsXoa;
                dsXoa = nullptr;
                OpenXoa = false;
                MaChucVuInput[0] = '\0';
                TenChucVuInput[0] = '\0';
                PhuCapInput[0] = '\0';
                letterCount_Ma = letterCount_Ten = letterCount_PhuCap = 0;
            }
        }
    }
    else if (Clicked && (OpenThem || OpenSua))
    {
        // Chỉ xử lý Xác nhận
        if (Clicked && CheckCollisionPointRec(mousepos, btnXacNhan))
        {
            isXacNhan = true;
        }
        // Chỉ xử lý Hủy
        else if (Clicked && CheckCollisionPointRec(mousepos, btnHuy))
        {
            isHuy = true;
        }
    }
    else
    {
        if (Clicked && CheckCollisionPointRec(mousepos, btnThemChucVu))
        {
            OpenThem = true;
            MaChucVuInput[0] = '\0';
            TenChucVuInput[0] = '\0';
            PhuCapInput[0] = '\0';
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            letterCount_PhuCap = 0;
            isMaChucVuActive = true;
            isTenChucVuActive = false;
            isPhucCapActive = false;
        }
        else if (Clicked && CheckCollisionPointRec(mousepos, btnSuaChucVu))
        {
            OpenSua = true;
            isMaChucVuActive = false;
            isTenChucVuActive = true;
            isPhucCapActive = false;
        }
        else if (Clicked && CheckCollisionPointRec(mousepos, btnXoa))
        {
            OpenXoa = true;
            dsXoa = new List<ChucVu>;
            isMaChucVuActive = isTenChucVuActive = isPhucCapActive = false;
        }
    }
    if (needfill && selCV != nullptr)
    {
        strncpy(MaChucVuInput, selCV->get_MaChucVu().c_str(), 49);
        letterCount_Ma = strlen(MaChucVuInput);
        MaChucVuInput[letterCount_Ma] = '\0';

        strncpy(TenChucVuInput, selCV->get_TenChucVu().c_str(), 49);
        letterCount_Ten = strlen(TenChucVuInput);
        TenChucVuInput[letterCount_Ten] = '\0';

        snprintf(PhuCapInput, sizeof(PhuCapInput), "%lld", (long long)selCV->get_PhuCap());
        letterCount_PhuCap = strlen(PhuCapInput);

        needfill = false;
    }

    if (OpenThem)
    {
        Typing(isMaChucVuActive, MaChucVuInput, letterCount_Ma, mousepos, MaChucVu);
        HieuUngGo(isMaChucVuActive, MaChucVu, MaChucVuInput, 28);

        Typing(isTenChucVuActive, TenChucVuInput, letterCount_Ten, mousepos, TenChucVu);
        HieuUngGo(isTenChucVuActive, TenChucVu, TenChucVuInput, 28);

        Typing(isPhucCapActive, PhuCapInput, letterCount_PhuCap, mousepos, PhucCap);
        HieuUngGo(isPhucCapActive, PhucCap, PhuCapInput, 28);
    }
    else if (OpenSua && selCV != nullptr)
    { // Ô nhập chữ chế độ sửa
        DrawTextEx(myFont, MaChucVuInput, {MaChucVu.x + 10, MaChucVu.y + 9}, 22, 1, BLACK);

        Typing(isTenChucVuActive, TenChucVuInput, letterCount_Ten, mousepos, TenChucVu);
        HieuUngGo(isTenChucVuActive, TenChucVu, TenChucVuInput, 22);

        Typing(isPhucCapActive, PhuCapInput, letterCount_PhuCap, mousepos, PhucCap);
        HieuUngGo(isPhucCapActive, PhucCap, PhuCapInput, 22);
    }
    else if (selCV != nullptr || MaChucVuInput[0] != '\0')
    {
        // Khi click vào 1 đối tượng trong danh sách (chế độ xem)
        DrawTextEx(myFont, MaChucVuInput, {MaChucVu.x + 10, MaChucVu.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, TenChucVuInput, {TenChucVu.x + 10, TenChucVu.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, PhuCapInput, {PhucCap.x + 10, PhucCap.y + 9}, 22, 1, BLACK);
    }

    if (isXacNhan)
    {
        if (OpenThem)
        {
            double pc = 0.0;
            try
            {
                pc = stod(PhuCapInput);
            }
            catch (...)
            {
                HienThongBao("Nhập sai loại kí tự không phải số", true);
                pc = 0.0;
            }
            ChucVu *CVnew = new ChucVu(MaChucVuInput, TenChucVuInput, pc);
            try
            {
                QL->ThemChucVu(CVnew);
                HienThongBao("Thêm chức vụ mới thành công!", false);
            }
            catch (const string &loi)
            {
                HienThongBao(loi, true);
            }
            needfill = false;
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            letterCount_PhuCap = 0;
            OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
            isMaChucVuActive = isTenChucVuActive = isPhucCapActive = false;
            MaChucVuInput[0] = '\0';
            TenChucVuInput[0] = '\0';
            PhuCapInput[0] = '\0';
        }
        else if (OpenSua && selCV != nullptr)
        {
            ChucVu *CVtam = new ChucVu(selCV->get_MaChucVu(), TenChucVuInput, atoll(PhuCapInput));
            try
            {
                QL->SuaChucVu(CVtam);
                HienThongBao("Cập nhật chức vụ thành công!", false);
            }
            catch (const string &e)
            {
                HienThongBao(e, true);
            }
            delete CVtam;
            OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
            isMaChucVuActive = isTenChucVuActive = isPhucCapActive = false;
            MaChucVuInput[0] = '\0';
            TenChucVuInput[0] = '\0';
            PhuCapInput[0] = '\0';
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            letterCount_PhuCap = 0;
        }
    }

    if (isHuy && CheckCollisionPointRec(mousepos, btnHuy))
    {
        OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
        isMaChucVuActive = isTenChucVuActive = isPhucCapActive = false;
        MaChucVuInput[0] = '\0';
        TenChucVuInput[0] = '\0';
        PhuCapInput[0] = '\0';
        letterCount_Ma = 0;
        letterCount_Ten = 0;
        letterCount_PhuCap = 0;
    }

    DrawTextEx(myFont, ("Tổng chức vụ: " + to_string(QL->get_DB()->get_ListCV()->get_size())).c_str(), {1550, 960}, 20, 1, DARKGRAY);
}

void Draw_Screen_Deparment(QLNV *QL)
{
    static Texture2D a1;
    static bool isLoaded = false;
    if (!isLoaded)
    {
        a1 = LoadTexture("photo/icon/Asset-2.png");
        isLoaded = true;
    }
    Vector2 pa1 = {370.0f, 45.0f}; // Tọa độ (x, y) postion
    float ra1 = 0.0f;              // Góc xoay (0 độ) rotation
    float sa1 = 0.33f;
    DrawTextureEx(a1, pa1, ra1, sa1, WHITE);
    DrawTextEx(myFont, "Quản Lý Phòng Ban & Chức Vụ", {pa1.x + 100, pa1.y}, 45, 1, WHITE);
    DrawTextEx(myFont, "Danh sách và thông tin phòng ban & chức vụ của công ty", {pa1.x + 100, pa1.y + 50}, 30, 1, WHITE);
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_menuGen);
    s_gen = g_menuGen;
    static bool isOpenPB = true;
    if (doReset)
        isOpenPB = true;
    static bool isOpenCV = false;
    if (doReset)
        isOpenCV = false;
    Vector2 mousePos = GetMousePosition();
    bool Clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    float TabX = 330.0f;
    float TabY = 160.0f;
    float TabH = 90.0f;
    Rectangle TabPB = {TabX, TabY, 300.0f, TabH};
    Rectangle TabCV = {TabX + 310.0f, TabY, 300.0f, TabH};
    bool hoverPB = CheckCollisionPointRec(mousePos, TabPB);
    bool hoverCV = CheckCollisionPointRec(mousePos, TabCV);
    Color CTabPB = isOpenPB == 1 ? BLUE : WHITE;
    Color CTabVT = isOpenCV == 1 ? BLUE : WHITE;
    if (isOpenPB == true && hoverCV)
        CTabVT = Fade(BLUE, 0.4);
    if (isOpenCV == true && hoverPB)
        CTabPB = Fade(BLUE, 0.4);
    DrawRectangleRounded(TabPB, 0.3f, 10, CTabPB);
    DrawRectangleRoundedLinesEx(TabPB, 0.3f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Phòng ban", {TabPB.x + 70.0f, TabPB.y + 15.0f}, 36, 1, BLACK);

    DrawRectangleRounded(TabCV, 0.3f, 10, CTabVT);
    DrawRectangleRoundedLinesEx(TabPB, 0.3f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Chức vụ", {TabCV.x + 90.0f, TabCV.y + 15.0f}, 36, 1, BLACK);

    Rectangle panelBang = {330, 230, 1450.0f, 690.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabPB))
    {
        if (!isOpenPB)
            g_resetGen++;
        isOpenPB = true;
        isOpenCV = false;
    }
    else if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabCV))
    {
        if (!isOpenCV)
            g_resetGen++;
        isOpenCV = true;
        isOpenPB = false;
    }

    if (isOpenPB)
    {
        Draw_Screen_PhongBan(mousePos, Clicked, QL);
    }
    else if (isOpenCV)
    {
        Draw_Screen_ChucVu(mousePos, Clicked, QL);
    }
}

