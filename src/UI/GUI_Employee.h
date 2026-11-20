#pragma once
#include "GUI_Common.h"

void Draw_Screen_NhanVien(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_VTVL(Vector2 mousePos, bool Clicked, QLNV *QL);
void Draw_Screen_Employee(QLNV *QL);

void Draw_Screen_NhanVien(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    // ============ 1. KHAI BÁO BIẾN STATIC ============
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static bool clickThem = false;
    if (doReset)
        clickThem = false;
    static bool clickSua = false;
    if (doReset)
        clickSua = false;
    static bool isOpenDelete = false;
    static bool isOpenTable = false;
    if (doReset)
        isOpenTable = false;
    static bool needFill = false;
    if (doReset)
        needFill = false;
    static bool hoiXoa = false;
    if (doReset)
        hoiXoa = false;
    static bool openedTableThisFrame = false;
    if (doReset)
        openedTableThisFrame = false;
    bool blockBackground = isOpenTable || hoiXoa;

    static List<Employee> *dsXoa = nullptr;
    if (doReset)
    {
        if (isOpenDelete)
            delete dsXoa;
        dsXoa = nullptr;
        isOpenDelete = false;
    }
    static string selectedMNV = "";
    if (doReset)
        selectedMNV = "";
    string default_choice = "Tất cả";
    // MeNu

    Rectangle comboChucVu = {350, 290, 250, 45};
    static bool isChucVuOpen = false;
    if (doReset)
        isChucVuOpen = false;
    static int selectedChucVuIndex = 0;
    if (doReset)
        selectedChucVuIndex = 0;

    Rectangle comboPhong = {620, 290, 250, 45};
    static bool isPhongOpen = false;
    if (doReset)
        isPhongOpen = false;
    static int selectedPhongIndex = 0;
    if (doReset)
        selectedPhongIndex = 0;

    Rectangle textHoTen = {890, 290, 350, 45};
    // Các biến cho ô nhập liệu Họ Tên
    static bool isHoTenActive = false; // Trạng thái: ô có đang được click vào không
    if (doReset)
        isHoTenActive = false;
    static char hoTenInput[50] = "\0"; // Chuỗi lưu ký tự người dùng gõ
    if (doReset)
        hoTenInput[0] = '\0';
    static int letterCount = 0;
    if (doReset)
        letterCount = 0;

    static int lastSortIdx = 0, lastSortTTIdx = 0;
    if (doReset)
    {
        lastSortIdx = 0;
        lastSortTTIdx = 0;
    }
    static bool needSort = false;
    if (doReset)
        needSort = false;
    Rectangle comboSort = {1290, 290, 250, 45};
    static bool isSortOpen = false;
    if (doReset)
        isSortOpen = false;
    static int selectedSortIndex = 0;
    if (doReset)
        selectedSortIndex = 0;
    string dsSort[] = {"...", "Mã NV", "Họ và Tên", "Ngày Sinh"};
    int nSort = 3;

    Rectangle comboSortTT = {1560, 290, 200, 45}; // thứ tự (a->z, z->a, tuổi ...)
    static bool isSortTTOpen = false;
    if (doReset)
        isSortTTOpen = false;
    static int selectedSortTTIndex = 0;
    if (doReset)
        selectedSortTTIndex = 0;
    string dsSortTT[] = {"...", "tăng dần", "giảm dần"};
    int nSortTT = 2;

    static float scrollY = 0.0f;
    if (doReset)
        scrollY = 0.0f; // 1. TẠO BIẾN CUỘN (Dùng 'static' để giữ nguyên giá trị qua mỗi khung hình)

    // ============ 2. TÍNH TOÁN (chưa vẽ gì) ============
    float scrollSpeed = 30.0f; // Tốc độ cuộn mỗi nấc chuột

    // Lấy thao tác lăn chuột và cộng dồn vào scrollY
    float wheel = GetMouseWheelMove(); // Lăn chuột xuống trả về -1 ngược lại lên
    if (!blockBackground && wheel != 0.0f)
    {
        scrollY += wheel * scrollSpeed;
    }

    // Chặn cuộn quá đà lên trên (danh sách không bị tụt xuống dưới tiêu đề)
    if (scrollY > 0.0f)
        scrollY = 0.0f;
    // Cấu hình khoảng cách và kích thước chữ
    float startX = 350.f; // Lề trái
    float startY = 400.f; // Lề trên
    int rowHeight = 60;   // Chiều cao mỗi dòng
    int fontSize = 24;    // Kích thước chữ chuẩn đồng bộ với Chấm Công

    // Tọa độ X của từng cột (Bạn cần tinh chỉnh các số này cho vừa với màn hình)
    float colX[] = {350.f, 470.f, 790.f, 930.f, 1055.f, 1290.f, 1490.f, 1700.f};
    // lấy tiêu chí so sánh khi in

    int nPB = QL->get_DB()->get_ListPB()->get_size();
    string dsPBFilter[nPB + 1];
    dsPBFilter[0] = default_choice; // Mục đầu tiên: "Tất cả"
    for (int i = 0; i < nPB; i++)
    {
        dsPBFilter[i + 1] = (*QL->get_DB()->get_ListPB())[i]->Data->get_TenPhongBan();
    }
    int nCV = QL->get_DB()->get_ListCV()->get_size();
    string dsCVFilter[nCV + 1];
    dsCVFilter[0] = default_choice; // Mục đầu tiên: "Tất cả"
    for (int i = 0; i < nCV; i++)
    {
        dsCVFilter[i + 1] = (*QL->get_DB()->get_ListCV())[i]->Data->get_TenChucVu();
    }

    static string tieuchi1 = "";
    static string tieuchi2 = "";
    if (selectedChucVuIndex != 0)
    {
        tieuchi1 = (*QL->get_DB()->get_ListCV())[selectedChucVuIndex - 1]->Data->get_MaChucVu();
    }
    else
    {
        tieuchi1 = "";
    }

    if (selectedPhongIndex != 0)
    {
        tieuchi2 = (*QL->get_DB()->get_ListPB())[selectedPhongIndex - 1]->Data->get_MaPhongBan();
    }
    else
    {
        tieuchi2 = "";
    }

    if (needSort)
    {
        needSort = false;
        if (selectedSortIndex == 1)
            if (selectedSortTTIndex == 1)
                QL->SapXep(TieuChiSapXep::MNV_TANG);
            else
                QL->SapXep(TieuChiSapXep::MNV_GIAM);
        else if (selectedSortIndex == 2)
            if (selectedSortTTIndex == 1)
                QL->SapXep(TieuChiSapXep::TEN_TANG);
            else
                QL->SapXep(TieuChiSapXep::TEN_GIAM);
        else if (selectedSortIndex == 3)
            if (selectedSortTTIndex == 1)
                QL->SapXep(TieuChiSapXep::NGAYSINH_TANG);
            else
                QL->SapXep(TieuChiSapXep::NGAYSINH_GIAM);
    }

    // 1. VẼ TIÊU ĐỀ CỘT (Header)

    // ============ 3. VẼ BẢNG DANH SÁCH ============
    float lech = isOpenDelete ? 30.f : 0.f;
    DrawTextEx(myFont, "Mã NV", {colX[0] + lech, startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Họ và tên", {colX[1] + lech, startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Ngày sinh", {colX[2] + lech, startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Giới tính", {colX[3] + lech, startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Phòng ban", {colX[4] + lech, startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Chức vụ", {colX[5] + lech, startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Vị trí", {colX[6] + lech, startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Bậc", {colX[7] + lech, startY}, fontSize, 1, DARKGRAY);

    // Kẻ đường gạch ngang dưới tiêu đề
    DrawLine(startX, startY + 30, 1900, startY + 30, LIGHTGRAY);

    // 4. KHU VỰC VẼ DANH SÁCH BỊ CẮT (Scissor Mode)
    int listStartY = startY + 60;                         // Điểm bắt đầu vẽ dữ liệu (ngay dưới đường kẻ)
    int listHeight = GetScreenHeight() - listStartY - 80; // Chiều cao khu vực hiển thị dữ liệu

    // Bật chế độ Scissor: Bất cứ thứ gì vẽ bên ngoài hình chữ nhật này sẽ bị ẩn đi

    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    // Chỉ hover khi bảng thông tin đóng, không có combo lọc đang mở, và chuột nằm trong vùng danh sách
    bool canHover = !hoiXoa && !isOpenTable && !isChucVuOpen && !isPhongOpen && CheckCollisionPointRec(mousePos, listArea);

    // Tọa độ Y hiện tại bắt đầu = Tọa độ gốc + Độ lệch cuộn
    float currentY = listStartY + scrollY;

    // Đếm tổng số lượng dòng để chặn cuộn quá đà xuống dưới (tùy chọn nâng cao)
    int totalRows = 0;

    Employee *selEmp = nullptr;
    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Node<Employee> *current = QL->get_DB()->get_ListEmployee()->get_header()->Next;
    while (current != nullptr)
    {
        if (CheckEmployee(current->Data, tieuchi1, tieuchi2, hoTenInput))
        {
            string mnv = current->Data->get_mnv();
            string name = current->Data->get_name();
            string Ngaysinh = current->Data->get_NgaySinh().ToString();
            string mpb = current->Data->get_PhongBan()->get_TenPhongBan();
            string sex = current->Data->get_sex();
            string chucvu = current->Data->get_ChucVu()->get_TenChucVu();
            string vitri = current->Data->get_ViTri()->get_TenVTVL();
            string bac = to_string(current->Data->get_BacViTri());

            // ----- HOVER + CHỌN DÒNG -----
            Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
            bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
            if (isHover && Clicked && !blockBackground)
            {
                if (isOpenDelete)
                {
                    Node<Employee> *nd = dsXoa->find_ptr(current->Data);
                    if (nd != nullptr)
                        dsXoa->remove_item(nd);
                    else
                        dsXoa->insert(current->Data);
                }
                else
                {
                    selectedMNV = mnv;
                }
            }
            bool isSelected = (mnv == selectedMNV);

            if (isOpenDelete)
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
            else
            {
                if (isSelected)
                {
                    // đã chọn: đậm hơn; vừa chọn vừa rê chuột: đậm thêm chút
                    DrawRectangleRec(rowRect, isHover ? Color{180, 195, 230, 255} : Color{200, 210, 235, 255});
                    // lưu nhân viên đang chọn
                    selEmp = current->Data;
                }
                else if (isHover)
                {
                    DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
                }
            }
            // ------------------------------
            DrawTextEx(myFont, mnv.c_str(), {colX[0] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, name.c_str(), {colX[1] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, Ngaysinh.c_str(), {colX[2] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, sex.c_str(), {colX[3] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, mpb.c_str(), {colX[4] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, chucvu.c_str(), {colX[5] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, vitri.c_str(), {colX[6] + lech, currentY}, fontSize, 1, BLACK);
            DrawTextEx(myFont, bac.c_str(), {colX[7] + lech, currentY}, fontSize, 1, BLACK);
            DrawLine(startX, currentY + 30, GetScreenWidth() - 20, currentY + 30, Fade(LIGHTGRAY, 0.5f));
            currentY += rowHeight;
            totalRows++;
        }
        current = current->Next;
    }
    EndScissorMode();
    DrawTextEx(myFont, "Chức Vụ", {350, 255}, 22, 1, Color{60, 70, 85, 255});

    // ============ 4. VẼ TÌM KIẾM/ COMBO / SẮP XẾP ============

    // combo cv và pb
    VeDanhSachCombo(comboChucVu, isChucVuOpen, dsCVFilter, nCV + 1, mousePos, 22);
    if (selectedChucVuIndex == 0)
    {
        DrawTextEx(myFont, default_choice.c_str(), {comboChucVu.x + 15, comboChucVu.y + 11}, 22, 1, DARKGRAY);
    }
    else
    {
        DrawTextEx(myFont, (*QL->get_DB()->get_ListCV())[selectedChucVuIndex - 1]->Data->get_TenChucVu().c_str(), {comboChucVu.x + 15, comboChucVu.y + 11}, 22, 1, DARKGRAY);
    }

    if (Clicked && !blockBackground)
    {
        XuLyCombo(comboChucVu, isChucVuOpen, selectedChucVuIndex, nCV + 1, mousePos, Clicked);
    }
    DrawTextEx(myFont, "Phòng Ban", {620, 255}, 22, 1, Color{60, 70, 85, 255});

    VeDanhSachCombo(comboPhong, isPhongOpen, dsPBFilter, nPB + 1, mousePos, 22);
    if (selectedPhongIndex == 0)
    {
        DrawTextEx(myFont, default_choice.c_str(), {comboPhong.x + 15, comboPhong.y + 11}, 22, 1, DARKGRAY);
    }
    else
    {
        DrawTextEx(myFont, (*QL->get_DB()->get_ListPB())[selectedPhongIndex - 1]->Data->get_TenPhongBan().c_str(), {comboPhong.x + 15, comboPhong.y + 11}, 22, 1, DARKGRAY);
    }
    if (Clicked && !blockBackground)
    {
        XuLyCombo(comboPhong, isPhongOpen, selectedPhongIndex, nPB + 1, mousePos, Clicked);
    }

    // 3. Cụm "Họ Tên" / Tìm kiếm
    DrawTextEx(myFont, "Tìm kiếm", {890, 255}, 22, 1, Color{60, 70, 85, 255});
    if (!blockBackground)
    {
        Typing(isHoTenActive, hoTenInput, letterCount, mousePos, textHoTen);
    }
    DrawRectangleRounded(textHoTen, 0.3f, 6, Color{248, 250, 252, 255});
    DrawRectangleRoundedLinesEx(textHoTen, 0.3f, 6, 1.5f, isHoTenActive ? Color{50, 100, 220, 255} : LIGHTGRAY);
    if (hoTenInput[0] == '\0')
    {
        DrawTextEx(myFont, "Tìm tên hoặc mã NV...", {textHoTen.x + 15, textHoTen.y + 10}, 22, 1, GRAY);
    }
    else
    {
        DrawTextEx(myFont, hoTenInput, {textHoTen.x + 15, textHoTen.y + 10}, 24, 1, BLACK);
    }
    if (!blockBackground && isHoTenActive && hoTenInput[0] != '\0' && ((int)(GetTime() * 2) % 2 == 0))
    {
        Vector2 textSize = MeasureTextEx(myFont, hoTenInput, 24, 1);
        float cursorX = textHoTen.x + 15 + textSize.x + 2;
        if (cursorX < textHoTen.x + textHoTen.width - 15)
        {
            DrawTextEx(myFont, "_", {cursorX, textHoTen.y + 10}, 24, 1, Color{50, 100, 220, 255});
        }
    }

    // vẽ sort
    DrawTextEx(myFont, "Sắp xếp theo:", {1290, 255}, 22, 1, Color{60, 70, 85, 255});
    VeDanhSachCombo(comboSort, isSortOpen, dsSort, nSort + 1, mousePos, 22);
    if (selectedSortIndex == 0)
    {
        DrawTextEx(myFont, dsSort[0].c_str(), {comboSort.x + 15, comboSort.y + 11}, 22, 1, DARKGRAY);
    }
    else
    {
        DrawTextEx(myFont, dsSort[selectedSortIndex].c_str(), {comboSort.x + 15, comboSort.y + 11}, 22, 1, DARKGRAY);
    }
    if (Clicked && !blockBackground)
    {
        XuLyCombo(comboSort, isSortOpen, selectedSortIndex, nSort + 1, mousePos, Clicked);
    }

    // sort theo thứ tự tăng/giảm
    VeDanhSachCombo(comboSortTT, isSortTTOpen, dsSortTT, nSortTT + 1, mousePos, 22);
    if (selectedSortTTIndex == 0)
    {
        DrawTextEx(myFont, dsSortTT[0].c_str(), {comboSortTT.x + 15, comboSortTT.y + 11}, 22, 1, DARKGRAY);
    }
    else
    {
        DrawTextEx(myFont, dsSortTT[selectedSortTTIndex].c_str(), {comboSortTT.x + 15, comboSortTT.y + 11}, 22, 1, DARKGRAY);
    }
    if (Clicked && !blockBackground)
    {
        XuLyCombo(comboSortTT, isSortTTOpen, selectedSortTTIndex, nSort + 1, mousePos, Clicked);
    }
    if (selectedSortIndex != 0 && selectedSortTTIndex != 0 &&
        (selectedSortIndex != lastSortIdx || selectedSortTTIndex != lastSortTTIdx))
    {
        needSort = true;
        lastSortIdx = selectedSortIndex;
        lastSortTTIdx = selectedSortTTIndex;
    }

    // Tính toán chiều cao tổng của danh sách để chặn cuộn quá đáy
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

    // ============ 5. VẼ NÚT CHỨC NĂNG ============
    if (!isOpenDelete)
    {
        Rectangle btnThemNhanSu = {350, 940, 230, 50};
        bool hoverThem = !blockBackground && CheckCollisionPointRec(mousePos, btnThemNhanSu);
        VeNutChucNang(btnThemNhanSu, "Thêm nhân sự", NutStyle::Green, hoverThem, 1);

        Rectangle btnSuaNhanSu = {610, 940, 230, 50};
        bool hoverSua = !blockBackground && CheckCollisionPointRec(mousePos, btnSuaNhanSu);
        VeNutChucNang(btnSuaNhanSu, "Sửa nhân sự", NutStyle::Blue, hoverSua, 2);

        Rectangle btnXoaNhanSu = {870, 940, 230, 50};
        bool hoverXoa = !blockBackground && CheckCollisionPointRec(mousePos, btnXoaNhanSu);
        VeNutChucNang(btnXoaNhanSu, "Xóa nhân sự", NutStyle::Red, hoverXoa, 3);

        if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnThemNhanSu))
        {
            clickThem = true;
            openedTableThisFrame = true;
            isHoTenActive = false; // Ngắt focus ô tìm kiếm
        }

        if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnSuaNhanSu))
        {
            clickSua = true;
            needFill = true;
            openedTableThisFrame = true;
            isHoTenActive = false;
        } // Ngắt focus ô tìm kiếm}

        if (Clicked && !blockBackground && CheckCollisionPointRec(mousePos, btnXoaNhanSu))
        {
            isOpenDelete = true;
            dsXoa = new List<Employee>;
        }

        if (clickSua || clickThem)
        {
            isOpenTable = true;
        }
    }

    if (isOpenTable)
    {
        // ================= 1. KHAI BÁO BIẾN LƯU TRẠNG THÁI FORM =================
        static int s_gen2 = 0; // reset trạng thái khi chuyển mục
        bool doReset2 = (s_gen2 != g_resetGen);
        s_gen2 = g_resetGen;
        static char MaNhanVienInput[50] = "";
        if (doReset2)
            MaNhanVienInput[0] = '\0';
        static char HovaTenInput[50] = "";
        if (doReset2)
            HovaTenInput[0] = '\0';
        static int letterCountHovaTen = 0;
        if (doReset2)
            letterCountHovaTen = 0;
        static bool isHovaTenActive = false;
        if (doReset2)
            isHovaTenActive = false;

        // Trạng thái đóng/mở của 6 ô Combobox
        static bool openGT = false;
        if (doReset2)
            openGT = false;
        static bool openPB = false;
        if (doReset2)
            openPB = false;
        static bool openCV = false;
        if (doReset2)
            openCV = false;
        static bool openLoai = false;
        if (doReset2)
            openLoai = false;
        static bool openVT = false;
        if (doReset2)
            openVT = false;

        // Vị trí mục đang chọn trong Combobox (-1 là chưa chọn)
        static int selGT = -1;
        if (doReset2)
            selGT = -1;
        static int selPB = -1;
        if (doReset2)
            selPB = -1;
        static int selCV = -1;
        if (doReset2)
            selCV = -1;
        static int selLoai = -1;
        if (doReset2)
            selLoai = -1;
        static int loaiGoc = -1;
        if (doReset2)
            loaiGoc = -1;
        static int selVT = -1;
        if (doReset2)
            selVT = -1;

        // Trạng thái và dữ liệu của 2 bảng Lịch (Ngày sinh & Ngày vào làm)
        static bool isOpenCalendarNS = false;
        if (doReset2)
            isOpenCalendarNS = false;
        static bool isOpenCalendarNVL = false;
        if (doReset2)
            isOpenCalendarNVL = false;
        static bool changeNS = false;
        if (doReset2)
            changeNS = false;
        static bool changeNVL = false;
        if (doReset2)
            changeNVL = false;
        static int dayNS = day, monthNS = month, yearNS = year;
        if (doReset2)
        {
            dayNS = day;
            monthNS = month;
            yearNS = year;
        }
        static int dayNVL = day, monthNVL = month, yearNVL = year;
        if (doReset2)
        {
            dayNVL = day;
            monthNVL = month;
            yearNVL = year;
        }

        static bool daSinhMa = false;
        if (doReset2)
            daSinhMa = false;
        static string thongBaoLoi = "";
        if (doReset2)
            thongBaoLoi = "";
        bool dongBang = false; // Cờ đánh dấu khi cần đóng và reset bảng
        bool hienLoai = clickThem || (clickSua && loaiGoc == 1);

        // ================= 2. LẤY DỮ LIỆU TỪ DATABASE CHO COMBOBOX =================
        int nCV = QL->get_DB()->get_ListCV()->get_size();
        int nPB = QL->get_DB()->get_ListPB()->get_size();
        int nVT = QL->get_DB()->get_ListVTVL()->get_size();
        int nBac = 3;

        string dsCV[nCV], dsPB[nPB], dsVT[nVT];
        for (int i = 0; i < nCV; i++)
            dsCV[i] = (*QL->get_DB()->get_ListCV())[i]->Data->get_TenChucVu();
        for (int i = 0; i < nPB; i++)
            dsPB[i] = (*QL->get_DB()->get_ListPB())[i]->Data->get_TenPhongBan();
        for (int i = 0; i < nVT; i++)
            dsVT[i] = (*QL->get_DB()->get_ListVTVL())[i]->Data->get_TenVTVL();

        string dsGT[2] = {"Nam", "Nữ"};
        string dsLoai[2] = {"FullTime", "PartTime"};

        // ================= 3. KHỞI TẠO DỮ LIỆU KHI MỞ BẢNG (THÊM / SỬA) =================
        // Trường hợp THÊM: Tự động tạo mã nhân viên tăng dần (VD: NV016)
        if (clickThem && !daSinhMa)
        {
            int maxSo = 0;
            List<Employee> *ds = QL->get_DB()->get_ListEmployee();
            for (int i = 0; i < ds->get_size(); i++)
            {
                string ma = (*ds)[i]->Data->get_mnv();
                if (ma.length() > 2)
                {
                    int so = atoi(ma.substr(2).c_str());
                    if (so > maxSo)
                        maxSo = so;
                }
            }
            string maMoi = "NV";
            if (maxSo + 1 < 10)
                maMoi += "00";
            else if (maxSo + 1 < 100)
                maMoi += "0";
            maMoi += to_string(maxSo + 1);

            strcpy(MaNhanVienInput, maMoi.c_str());
            daSinhMa = true;
        }

        // Trường hợp SỬA: Đổ thông tin của nhân viên đang chọn vào các ô
        if (needFill)
        {
            needFill = false;

            if (selEmp != nullptr)
            {
                strcpy(MaNhanVienInput, selEmp->get_mnv().c_str());
                strcpy(HovaTenInput, selEmp->get_name().c_str());
                letterCountHovaTen = strlen(HovaTenInput);

                selCV = TimIndex(dsCV, nCV, selEmp->get_ChucVu()->get_TenChucVu());
                selPB = TimIndex(dsPB, nPB, selEmp->get_PhongBan()->get_TenPhongBan());
                selGT = TimIndex(dsGT, 2, selEmp->get_sex());
                selVT = TimIndex(dsVT, nVT, selEmp->get_ViTri()->get_TenVTVL());
                selLoai = (dynamic_cast<FullTime *>(selEmp) != nullptr) ? 0 : 1;
                loaiGoc = selLoai;
                sscanf(selEmp->get_NgaySinh().ToString().c_str(), "%d/%d/%d", &dayNS, &monthNS, &yearNS);
                changeNS = true;

                sscanf(selEmp->get_NgayLamViec().ToString().c_str(), "%d/%d/%d", &dayNVL, &monthNVL, &yearNVL);
                changeNVL = true;
            }
        }

        // ================= 4. VẼ KHUNG NỀN MODAL & TIÊU ĐỀ =================
        float screenW = GetScreenWidth();
        float screenH = GetScreenHeight();

        // Lớp phủ mờ toàn màn hình phía sau
        DrawRectangle(0, 0, screenW, screenH, Fade(BLACK, 0.45f));

        // Khung trắng chính giữa màn hình
        Rectangle Table = {(screenW - 840) / 2, (screenH - 670) / 2, 840, 670};
        DrawRectangleRounded({Table.x + 3, Table.y + 5, Table.width, Table.height}, 0.04f, 10, Fade(BLACK, 0.15f));
        DrawRectangleRounded(Table, 0.04f, 10, WHITE);

        // Tiêu đề & dòng mô tả phụ
        DrawTextEx(myFont, "Thông tin nhân viên", {Table.x + 36, Table.y + 26}, 28, 1, Color{20, 25, 35, 255});
        if (clickSua)
            DrawTextEx(myFont, "Chỉnh sửa thông tin nhân viên", {Table.x + 36, Table.y + 64}, 22, 1, Color{110, 118, 130, 255});
        else
            DrawTextEx(myFont, "Nhập thông tin nhân viên mới", {Table.x + 36, Table.y + 64}, 22, 1, Color{110, 118, 130, 255});

        // Nút [X] góc phải trên
        Rectangle btnDong = {Table.x + Table.width - 60, Table.y + 26, 36, 36};
        bool hoverX = CheckCollisionPointRec(mousePos, btnDong);
        DrawRectangleRounded(btnDong, 0.3f, 8, hoverX ? Color{254, 226, 226, 255} : Color{243, 245, 249, 255});
        DrawRectangleRoundedLinesEx(btnDong, 0.3f, 8, 1.2f, hoverX ? Color{248, 113, 113, 255} : Color{225, 230, 240, 255});
        Color xColor = hoverX ? Color{220, 38, 38, 255} : DARKGRAY;
        DrawLineEx({btnDong.x + 11, btnDong.y + 11}, {btnDong.x + 25, btnDong.y + 25}, 2.0f, xColor);
        DrawLineEx({btnDong.x + 25, btnDong.y + 11}, {btnDong.x + 11, btnDong.y + 25}, 2.0f, xColor);

        // ================= 5. TỌA ĐỘ 10 Ô NHẬP LIỆU (5 HÀNG x 2 CỘT) =================
        float boxW = 370.0f;
        float boxH = 45.0f;
        float col1X = Table.x + 36.0f;  // Cột trái
        float col2X = Table.x + 434.0f; // Cột phải

        float row1Y = Table.y + 125.0f; // Hàng 1
        float row2Y = Table.y + 207.0f; // Hàng 2
        float row3Y = Table.y + 289.0f; // Hàng 3
        float row4Y = Table.y + 371.0f; // Hàng 4
        float row5Y = Table.y + 453.0f; // Hàng 5

        Rectangle fMa = {col1X, row1Y, boxW, boxH};
        Rectangle fTen = {col2X, row1Y, boxW, boxH};

        Rectangle fNS = {col1X, row2Y, boxW, boxH};
        Rectangle fGT = {col2X, row2Y, boxW, boxH};

        Rectangle fPB = {col1X, row3Y, boxW, boxH};
        Rectangle fCV = {col2X, row3Y, boxW, boxH};

        Rectangle fVT = {col1X, row4Y, boxW, boxH};

        Rectangle fNVL = {col2X, row4Y, boxW, boxH};
        Rectangle fLoai = {col1X, row5Y, boxW, boxH};

        // ================= 6. VẼ NHÃN (LABEL) VÀ CÁC Ô TRÊN FORM =================
        Color labelColor = Color{50, 60, 75, 255};
        Color placeColor = Color{150, 158, 170, 255};
        Color textColor = Color{31, 41, 55, 255};

        // --- HÀNG 1: Mã nhân viên & Họ và tên ---
        DrawTextEx(myFont, "Mã nhân viên", {fMa.x, fMa.y - 26}, 20, 1, labelColor);
        VeOInput(fMa, MaNhanVienInput, false, true, "");

        DrawTextEx(myFont, "Họ và tên", {fTen.x, fTen.y - 26}, 20, 1, labelColor);
        Typing(isHovaTenActive, HovaTenInput, letterCountHovaTen, mousePos, fTen);
        VeOInput(fTen, HovaTenInput, isHovaTenActive, false, "Nhập họ và tên");

        // --- HÀNG 2: Ngày sinh & Giới tính ---
        DrawTextEx(myFont, "Ngày sinh", {fNS.x, fNS.y - 26}, 20, 1, labelColor);
        string txtNS = changeNS ? TextFormat("%02d/%02d/%04d", dayNS, monthNS, yearNS) : "";
        VeODate(fNS, txtNS.c_str(), isOpenCalendarNS, mousePos, "mm/dd/yyyy");

        DrawTextEx(myFont, "Giới tính", {fGT.x, fGT.y - 26}, 20, 1, labelColor);
        VeDanhSachCombo(fGT, false, dsGT, 2, mousePos, 24);
        DrawTextEx(myFont, (selGT == -1) ? "Chọn giới tính" : dsGT[selGT].c_str(),
                   {fGT.x + 16, fGT.y + 11}, 24, 1, (selGT == -1) ? placeColor : textColor);

        // --- HÀNG 3: Phòng ban & Chức vụ ---
        DrawTextEx(myFont, "Phòng ban", {fPB.x, fPB.y - 26}, 20, 1, labelColor);
        VeDanhSachCombo(fPB, false, dsPB, nPB, mousePos, 24);
        DrawTextEx(myFont, (selPB == -1) ? "Chọn phòng ban" : dsPB[selPB].c_str(),
                   {fPB.x + 16, fPB.y + 11}, 24, 1, (selPB == -1) ? placeColor : textColor);

        DrawTextEx(myFont, "Chức vụ", {fCV.x, fCV.y - 26}, 20, 1, labelColor);
        VeDanhSachCombo(fCV, false, dsCV, nCV, mousePos, 24);
        DrawTextEx(myFont, (selCV == -1) ? "Chọn chức vụ" : dsCV[selCV].c_str(),
                   {fCV.x + 16, fCV.y + 11}, 24, 1, (selCV == -1) ? placeColor : textColor);

        // --- HÀNG 4:  Ngày làm việc & Vị trí việc làm ---

        DrawTextEx(myFont, "Vị trí việc làm", {fVT.x, fVT.y - 26}, 20, 1, labelColor);
        VeDanhSachCombo(fVT, false, dsVT, nVT, mousePos, 24);
        DrawTextEx(myFont, (selVT == -1) ? "Chọn vị trí" : dsVT[selVT].c_str(),
                   {fVT.x + 16, fVT.y + 11}, 24, 1, (selVT == -1) ? placeColor : textColor);
        DrawTextEx(myFont, "Ngày vào làm", {fNVL.x, fNVL.y - 26}, 20, 1, labelColor);
        string txtNVL = changeNVL ? TextFormat("%02d/%02d/%04d", dayNVL, monthNVL, yearNVL) : "";
        VeODate(fNVL, txtNVL.c_str(), isOpenCalendarNVL, mousePos, "mm/dd/yyyy");
        // --- HÀNG 5: Loại nhân viên ---

        if (hienLoai)
        {
            DrawTextEx(myFont, "Loại nhân viên", {fLoai.x, fLoai.y - 26}, 20, 1, labelColor);
            VeDanhSachCombo(fLoai, false, dsLoai, 2, mousePos, 24);
            DrawTextEx(myFont, (selLoai == -1) ? "Chọn loại nhân viên" : dsLoai[selLoai].c_str(),
                       {fLoai.x + 16, fLoai.y + 11}, 24, 1, (selLoai == -1) ? placeColor : textColor);
        }

        // ================= 7. VẼ NÚT "HỦY" VÀ NÚT "THÊM / SỬA" =================
        DrawLine(Table.x + 36, Table.y + 575, Table.x + Table.width - 36, Table.y + 575, Color{235, 240, 245, 255});

        Rectangle btnHuy = {Table.x + Table.width - 235, Table.y + 595, 95, 45};
        bool hoverHuy = CheckCollisionPointRec(mousePos, btnHuy);
        DrawRectangleRounded(btnHuy, 0.25f, 8, WHITE);
        DrawRectangleRoundedLinesEx(btnHuy, 0.25f, 8, 1.5f, hoverHuy ? Color{180, 190, 205, 255} : Color{225, 230, 240, 255});
        DrawTextEx(myFont, "Hủy", {btnHuy.x + 28, btnHuy.y + 11}, 22, 1, Color{50, 60, 75, 255});

        Rectangle btnLuu = {Table.x + Table.width - 125, Table.y + 595, 95, 45};
        bool hoverLuu = CheckCollisionPointRec(mousePos, btnLuu);
        DrawRectangleRounded(btnLuu, 0.25f, 8, hoverLuu ? Color{35, 80, 220, 255} : Color{45, 96, 235, 255});
        if (clickSua)
            DrawTextEx(myFont, "Sửa", {btnLuu.x + 28, btnLuu.y + 11}, 22, 1, WHITE);
        else
            DrawTextEx(myFont, "Thêm", {btnLuu.x + 22, btnLuu.y + 11}, 22, 1, WHITE);

        if (!thongBaoLoi.empty())
        {
            DrawTextEx(myFont, ("* Lỗi: " + thongBaoLoi).c_str(), {Table.x + 36, Table.y + 605}, 22, 1, RED);
        }

        // ================= 8. XỬ LÝ DANH SÁCH XỔ XUỐNG, LỊCH & SỰ KIỆN CLICK =================
        // Nếu đang có 1 Combobox hoặc Lịch mở -> Vẽ đè lên trên cùng và chỉ xử lý tương tác cho ô đó
        if (openGT)
        {
            VeDanhSachCombo(fGT, true, dsGT, 2, mousePos, 24);
            DrawTextEx(myFont, (selGT == -1) ? "Chọn giới tính" : dsGT[selGT].c_str(), {fGT.x + 16, fGT.y + 11}, 24, 1, (selGT == -1) ? placeColor : textColor);
            XuLyCombo(fGT, openGT, selGT, 2, mousePos, Clicked);
        }
        else if (openPB)
        {
            VeDanhSachCombo(fPB, true, dsPB, nPB, mousePos, 24);
            DrawTextEx(myFont, (selPB == -1) ? "Chọn phòng ban" : dsPB[selPB].c_str(), {fPB.x + 16, fPB.y + 11}, 24, 1, (selPB == -1) ? placeColor : textColor);
            XuLyCombo(fPB, openPB, selPB, nPB, mousePos, Clicked);
        }
        else if (openCV)
        {
            VeDanhSachCombo(fCV, true, dsCV, nCV, mousePos, 24);
            DrawTextEx(myFont, (selCV == -1) ? "Chọn chức vụ" : dsCV[selCV].c_str(), {fCV.x + 16, fCV.y + 11}, 24, 1, (selCV == -1) ? placeColor : textColor);
            XuLyCombo(fCV, openCV, selCV, nCV, mousePos, Clicked);
        }
        else if (openLoai)
        {
            VeDanhSachCombo(fLoai, true, dsLoai, 2, mousePos, 24);
            DrawTextEx(myFont, (selLoai == -1) ? "Chọn loại nhân viên" : dsLoai[selLoai].c_str(), {fLoai.x + 16, fLoai.y + 11}, 24, 1, (selLoai == -1) ? placeColor : textColor);
            XuLyCombo(fLoai, openLoai, selLoai, 2, mousePos, Clicked);
        }
        else if (openVT)
        {
            VeDanhSachCombo(fVT, true, dsVT, nVT, mousePos, 24);
            DrawTextEx(myFont, (selVT == -1) ? "Chọn vị trí" : dsVT[selVT].c_str(), {fVT.x + 16, fVT.y + 11}, 24, 1, (selVT == -1) ? placeColor : textColor);
            XuLyCombo(fVT, openVT, selVT, nVT, mousePos, Clicked);
        }
        else if (isOpenCalendarNS)
        {
            if (DrawCalendar(mousePos, dayNS, monthNS, yearNS, fNS, isOpenCalendarNS))
                changeNS = true;
        }
        else if (isOpenCalendarNVL)
        {
            if (DrawCalendar(mousePos, dayNVL, monthNVL, yearNVL, fNVL, isOpenCalendarNVL))
                changeNVL = true;
        }
        // Khi không có danh sách xổ xuống hay lịch nào mở -> Kiểm tra click mở ô hoặc bấm nút
        else if (Clicked)
        {
            if (CheckCollisionPointRec(mousePos, fGT))
                openGT = true;
            else if (CheckCollisionPointRec(mousePos, fPB))
                openPB = true;
            else if (CheckCollisionPointRec(mousePos, fCV))
                openCV = true;
            else if (hienLoai && CheckCollisionPointRec(mousePos, fLoai))
                openLoai = true;
            else if (CheckCollisionPointRec(mousePos, fVT))
                openVT = true;
            else if (CheckCollisionPointRec(mousePos, fNS))
                isOpenCalendarNS = true;
            else if (CheckCollisionPointRec(mousePos, fNVL))
                isOpenCalendarNVL = true;
            else if (hoverX || hoverHuy || (!openedTableThisFrame && !CheckCollisionPointRec(mousePos, Table)))
            {
                dongBang = true;
            }
            else if (hoverLuu)
            {
                Employee *nv = nullptr;
                try
                {
                    if (strlen(HovaTenInput) == 0)
                        throw string("Vui lòng nhập họ và tên!");
                    if (!changeNS)
                        throw string("Vui lòng chọn ngày sinh!");
                    if (selGT == -1)
                        throw string("Vui lòng chọn giới tính!");
                    if (selPB == -1)
                        throw string("Vui lòng chọn phòng ban!");
                    if (selCV == -1)
                        throw string("Vui lòng chọn chức vụ!");
                    if (selLoai == -1)
                        throw string("Vui lòng chọn loại nhân viên!");
                    if (selVT == -1)
                        throw string("Vui lòng chọn vị trí việc làm!");
                    if (!changeNVL)
                        throw string("Vui lòng chọn ngày vào làm!");
                    Date ngaySinh(dayNS, monthNS, yearNS);
                    Date ngayVaoLam(dayNVL, monthNVL, yearNVL);

                    string mnv = MaNhanVienInput;
                    string ten = HovaTenInput;
                    string gioiTinh = dsGT[selGT];
                    ChucVu *cv = (*QL->get_DB()->get_ListCV())[selCV]->Data;
                    PhongBan *pb = (*QL->get_DB()->get_ListPB())[selPB]->Data;
                    ViTriViecLam *vt = (*QL->get_DB()->get_ListVTVL())[selVT]->Data;

                    // Employee *oldEmp = QL->TimTheoMa(mnv);
                    // int oldThuong = (oldEmp != nullptr) ? oldEmp->get_Thuong() : 0;
                    // int oldSNC = 0;
                    // if (oldEmp != nullptr)
                    // {
                    //     FullTime *oldFT = dynamic_cast<FullTime *>(oldEmp);
                    //     if (oldFT != nullptr)
                    //         oldSNC = oldFT->get_SoNgayCong();
                    // }

                    // if (selLoai == 0)
                    //     nv = new FullTime(mnv, ten, ngaySinh, gioiTinh, cv, vt, pb, ngayVaoLam, 1, oldThuong, oldSNC);
                    // else
                    // {
                    //     int oldTime = 80;
                    //     if (oldEmp != nullptr)
                    //     {
                    //         PartTime *oldPT = dynamic_cast<PartTime *>(oldEmp);
                    //         if (oldPT != nullptr)
                    //             oldTime = oldPT->get_TimeWork();
                    //     }
                    //     nv = new PartTime(mnv, ten, ngaySinh, gioiTinh, cv, vt, pb, ngayVaoLam, 1, oldThuong, oldTime);
                    // }

                    // if (clickThem)
                    // {
                    //     QL->ThemEmployee(nv);
                    //     HienThongBao("Thêm nhân viên mới thành công!", false); // false = Màu xanh
                    // }
                    // else
                    // {
                    //     QL->SuaEmployee(nv);
                    //     delete nv;
                    //     nv = nullptr;
                    //     HienThongBao("Cập nhật thông tin thành công!", false); // false = Màu xanh
                    // }

                    // dongBang = true;
                    Employee *oldEmp = QL->TimTheoMa(mnv);
                    if (clickSua && oldEmp == nullptr)
                        throw string("Không tìm thấy nhân viên cần sửa!");

                    bool oldLaFT = (dynamic_cast<FullTime *>(oldEmp) != nullptr);
                    if (clickSua && oldLaFT && selLoai == 1)
                        throw string("Không thể chuyển FullTime xuống PartTime!");

                    int oldThuong = (oldEmp != nullptr) ? oldEmp->get_Thuong() : 0;
                    int oldBac = (oldEmp != nullptr) ? oldEmp->get_BacViTri() : 1;
                    int oldSNC = 0, oldTime = 80;
                    if (FullTime *f = dynamic_cast<FullTime *>(oldEmp))
                        oldSNC = f->get_SoNgayCong();
                    else if (PartTime *p = dynamic_cast<PartTime *>(oldEmp))
                        oldTime = p->get_TimeWork();

                    if (selLoai == 0)
                        nv = new FullTime(mnv, ten, ngaySinh, gioiTinh, cv, vt, pb, ngayVaoLam, oldBac, oldThuong, oldSNC);
                    else
                        nv = new PartTime(mnv, ten, ngaySinh, gioiTinh, cv, vt, pb, ngayVaoLam, oldBac, oldThuong, oldTime);

                    if (clickThem)
                    {
                        QL->ThemEmployee(nv);
                        HienThongBao("Thêm nhân viên mới thành công!", false);
                    }
                    else
                    {
                        bool doiLoai = (!oldLaFT && selLoai == 0); // PartTime -> FullTime
                        if (doiLoai)
                        {
                            int tuoi = yearNVL - yearNS;
                            if (year - yearNS < 18 || year - yearNS > 60)
                                throw string("Tuổi nhân viên không hợp lệ!");
                            if (tuoi < 18)
                                throw string("Tuổi tính đến ngày vào làm chưa đủ 18!");
                            if (ngayVaoLam > Date::DateHienTai())
                                throw string("Ngày vào làm không được lớn hơn ngày hiện tại!");

                            QL->XoaEmployee(oldEmp);
                            QL->ThemEmployee(nv); // KHÔNG delete nv
                        }
                        else
                        {
                            QL->SuaEmployee(nv);
                            delete nv;
                        }
                        nv = nullptr;
                        QL->get_DB()->SaveFileEmployee();
                        HienThongBao("Cập nhật thông tin thành công!", false);
                    }
                    dongBang = true;
                }
                catch (const string &loi)
                {
                    HienThongBao(loi, true); // true = Báo lỗi màu đỏ trượt ra
                    if (nv != nullptr)
                        delete nv;
                }
                catch (const char *loi)
                {
                    HienThongBao(string(loi), true);
                    if (nv != nullptr)
                        delete nv;
                }
            }
        }

        // ================= 9. ĐÓNG BẢNG & RESET BIẾN KHI HOÀN TẤT / HỦY =================
        if (dongBang)
        {
            isOpenTable = false;
            clickThem = false;
            clickSua = false;

            openGT = openPB = openCV = openLoai = openVT = false;
            selGT = selPB = selCV = selLoai = selVT = -1;

            isOpenCalendarNS = isOpenCalendarNVL = false;
            changeNS = changeNVL = false;

            MaNhanVienInput[0] = '\0';
            HovaTenInput[0] = '\0';
            letterCountHovaTen = 0;
            isHovaTenActive = false;

            daSinhMa = false;
            thongBaoLoi = "";
        }
    }

    if (isOpenDelete)
    {
        Rectangle btnHuyXoa = {350, 940, 230, 50};
        bool hoverHuyXoa = CheckCollisionPointRec(mousePos, btnHuyXoa);
        VeNutChucNang(btnHuyXoa, "Hủy xóa", NutStyle::Secondary, hoverHuyXoa, 5);

        Rectangle btnXacNhanXoa = {610, 940, 230, 50};
        bool hoverXNXoa = CheckCollisionPointRec(mousePos, btnXacNhanXoa);
        VeNutChucNang(btnXacNhanXoa, "Xác nhận xoá", NutStyle::Red, hoverXNXoa, 3);

        if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnHuyXoa))
        {
            delete dsXoa;
            isOpenDelete = false;
        }
        else if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnXacNhanXoa))
        {
            if (dsXoa->get_size() == 0)
                HienThongBao("Chưa chọn nhân viên nào để xóa!", true);
            else
                hoiXoa = true; // chỉ mở hộp hỏi, CHƯA xóa
        }
        int dem = dsXoa->get_size();
        if (XacNhan("Bạn có chắc muốn xóa " + to_string(dem) + " nhân viên đã chọn?", hoiXoa))
        {
            for (Node<Employee> *p = dsXoa->get_header()->Next; p != nullptr; p = p->Next)
                QL->XoaEmployee(p->Data);

            while (dsXoa->get_size() > 0)
                dsXoa->remove_item(dsXoa->get_header()->Next);

            QL->get_DB()->SaveFileEmployee();
            HienThongBao("Đã xóa " + to_string(dem) + " nhân viên thành công!", false);
            delete dsXoa;
            dsXoa = nullptr;
            isOpenDelete = false;
            selectedMNV = "";
        }
    }
    DrawTextEx(myFont, ("Tổng nhân viên: " + to_string(QL->get_DB()->get_ListEmployee()->get_size())).c_str(), {1550, 960}, 20, 1, DARKGRAY);

    openedTableThisFrame = false;
    g_isModalActive = (isOpenTable || hoiXoa);
}

void Draw_Screen_VTVL(Vector2 mousePos, bool Clicked, QLNV *QL)
{
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_resetGen);
    s_gen = g_resetGen;

    static bool isMaVTActive = false;  // Trạng thái: ô có đang được click vào không
    if (doReset)
        isMaVTActive = false;
    static bool isTenVTActive = false; // Trạng thái: ô có đang được click vào không
    if (doReset)
        isTenVTActive = false;
    static bool OpenThem = false;
    if (doReset)
        OpenThem = false;
    static bool OpenSua = false;
    if (doReset)
        OpenSua = false;
    static List<ViTriViecLam> *dsXoa = nullptr;
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

    Rectangle panelBang1 = {330, 230, 1450.0f, 280.0f};
    DrawRectangleRounded({panelBang1.x + 3, panelBang1.y + 4, panelBang1.width, panelBang1.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang1, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang1, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Thông tin vị trí việc làm", {360.0f, 250.0f}, 28, 1, Color{20, 25, 35, 255});

    static Texture2D a1;
    static bool isLoaded = false;
    if (!isLoaded)
    {
        a1 = LoadTexture("photo/anhto/vtri.png");
        isLoaded = true;
    }
    Vector2 pa1 = {360.0f, 300.0f}; // Tọa độ (x, y) postion
    float ra1 = 0.0f;               // Góc xoay (0 độ) rotation
    float sa1 = 0.6f;
    DrawTextureEx(a1, pa1, ra1, sa1, WHITE);

    Rectangle textMaVT = {850, 350, 300, 40};
    static char MaVTInput[50] = "\0"; // Chuỗi lưu ký tự người dùng gõ
    if (doReset)
        MaVTInput[0] = '\0';
    static int letterCount_Ma = 0;
    if (doReset)
        letterCount_Ma = 0;
    DrawTextEx(myFont, "Mã vị trí:", {700.0f, 357.0f}, 22, 1, Color{50, 60, 75, 255});
    bool maActive = OpenThem && isMaVTActive;
    DrawRectangleRounded(textMaVT, 0.3f, 6, maActive ? Color{248, 250, 252, 255} : (OpenSua ? Color{240, 243, 246, 255} : WHITE));
    DrawRectangleRoundedLinesEx(textMaVT, 0.3f, 6, 1.5f, maActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    Rectangle textTenVT = {850, 420, 300, 40};
    static char TenVTInput[50] = "\0"; // Chuỗi lưu ký tự người dùng gõ
    if (doReset)
        TenVTInput[0] = '\0';
    static int letterCount_Ten = 0;
    if (doReset)
        letterCount_Ten = 0;
    DrawTextEx(myFont, "Tên vị trí:", {700.0f, 427.0f}, 22, 1, Color{50, 60, 75, 255});
    bool tenActive = (OpenThem || OpenSua) && isTenVTActive;
    DrawRectangleRounded(textTenVT, 0.3f, 6, tenActive ? Color{248, 250, 252, 255} : WHITE);
    DrawRectangleRoundedLinesEx(textTenVT, 0.3f, 6, 1.5f, tenActive ? Color{50, 100, 220, 255} : LIGHTGRAY);

    if (!OpenThem && !OpenSua)
    {
        isMaVTActive = false;
        isTenVTActive = false;
    }
    else if (Clicked)
    {
        if (OpenThem)
        {
            if (CheckCollisionPointRec(mousePos, textMaVT))
            {
                isMaVTActive = true;
                isTenVTActive = false;
            }
            else if (CheckCollisionPointRec(mousePos, textTenVT))
            {
                isTenVTActive = true;
                isMaVTActive = false;
            }
            else
            {
                isMaVTActive = isTenVTActive = false;
            }
        }
        else if (OpenSua)
        {
            isMaVTActive = false; // Mã không được sửa
            if (CheckCollisionPointRec(mousePos, textTenVT))
            {
                isTenVTActive = true;
            }
            else
            {
                isTenVTActive = false;
            }
        }
    }

    Rectangle btnThemViTri = {350, 940, 230, 50};
    Rectangle btnSuaViTri = {610, 940, 230, 50};
    Rectangle btnXoaViTri = {870, 940, 230, 50};

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
        bool hoverThem = CheckCollisionPointRec(mousePos, btnThemViTri);
        VeNutChucNang(btnThemViTri, "Thêm vị trí", NutStyle::Green, hoverThem, 1);

        bool hoverSua = CheckCollisionPointRec(mousePos, btnSuaViTri);
        VeNutChucNang(btnSuaViTri, "Sửa vị trí", NutStyle::Blue, hoverSua, 2);

        bool hoverXoa = CheckCollisionPointRec(mousePos, btnXoaViTri);
        VeNutChucNang(btnXoaViTri, "Xóa vị trí", NutStyle::Red, hoverXoa, 3);
    }

    // bảng 2
    Rectangle panelBang2 = {330, 530, 1450.0f, 390.0f};
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
    int colX[] = {350, 600, 900};

    // 1. VẼ TIÊU ĐỀ CỘT (Header)
    float lech = OpenXoa ? 30.f : 0.f;
    DrawTextEx(myFont, "Mã Vị Trí", {colX[0] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Tên Vị Trí", {colX[1] + lech, (float)startY}, fontSize, 1, DARKGRAY);
    DrawTextEx(myFont, "Số Lượng", {colX[2] + lech, (float)startY}, fontSize, 1, DARKGRAY);

    // Kẻ đường gạch ngang dưới tiêu đề
    DrawLine(startX, startY + 30, 1900, startY + 30, LIGHTGRAY);

    // 4. KHU VỰC VẼ DANH SÁCH BỊ CẮT (Scissor Mode)
    int listStartY = startY + 60;                         // Điểm bắt đầu vẽ dữ liệu (ngay dưới đường kẻ)
    int listHeight = GetScreenHeight() - listStartY - 80; // Chiều cao khu vực hiển thị dữ liệu

    // Bật chế độ Scissor: Bất cứ thứ gì vẽ bên ngoài hình chữ nhật này sẽ bị ẩn đi
    BeginScissorMode(startX, listStartY, GetScreenWidth() - startX, listHeight);
    Rectangle listArea = {(float)startX, (float)listStartY, (float)(GetScreenWidth() - startX), (float)listHeight};
    // Chỉ hover khi chuột nằm trong vùng danh sách
    bool canHover = !hoiXoa && CheckCollisionPointRec(mousePos, listArea);

    // Tọa độ Y hiện tại bắt đầu = Tọa độ gốc + Độ lệch cuộn
    float currentY = listStartY + scrollY;

    Node<ViTriViecLam> *current = QL->get_DB()->get_ListVTVL()->get_header()->Next;

    // Đếm tổng số lượng dòng để chặn cuộn quá đà xuống dưới (tùy chọn nâng cao)
    int totalRows = 0;

    ViTriViecLam *selVT = nullptr;
    static string selectedPhongBan = "";
    if (doReset)
        selectedPhongBan = "";
    while (current != nullptr)
    {
        string mpb = current->Data->get_MaVTVL();
        string name = current->Data->get_TenVTVL();
        int size = current->Data->get_ListNV()->get_size();
        string vt_size = to_string(size);

        // ----- HOVER + CHỌN DÒNG -----
        Rectangle rowRect = {(float)startX, currentY - 5, (float)(GetScreenWidth() - startX - 20), 35};
        bool isHover = canHover && CheckCollisionPointRec(mousePos, rowRect);
        if (isHover && Clicked)
        {
            if (OpenXoa)
            {
                Node<ViTriViecLam> *nd = dsXoa->find_ptr(current->Data);
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
            // lưu nhân viên đang chọn
            selVT = current->Data;
        }
        else if (isHover)
        {
            DrawRectangleRec(rowRect, Color{235, 235, 240, 255});
        }
        // ------------------------------

        DrawTextEx(myFont, mpb.c_str(), {colX[0] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, name.c_str(), {colX[1] + lech, currentY}, fontSize, 1, BLACK);
        DrawTextEx(myFont, vt_size.c_str(), {colX[2] + lech, currentY}, fontSize, 1, BLACK);
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
        if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnHuyXoa))
        {
            delete dsXoa;
            OpenXoa = false;
        }
        else if (Clicked && !hoiXoa && CheckCollisionPointRec(mousePos, btnXacNhanXoa))
        {
            if (dsXoa->get_size() == 0)
                HienThongBao("Chưa chọn vị trí nào để xóa!", true);
            else
                hoiXoa = true;
        }
        if (OpenXoa && dsXoa != nullptr)
        {
            if (XacNhan("Bạn có chắc muốn xóa " + to_string(dsXoa->get_size()) + " vị trí đã chọn?", hoiXoa))
            {
                int dem = 0;
                string loiCuoi = "";
                for (Node<ViTriViecLam> *p = dsXoa->get_header()->Next; p != nullptr; p = p->Next)
                {
                    try
                    {
                        QL->XoaViTri(p->Data);
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
                        HienThongBao("Đã xóa " + to_string(dem) + " vị trí thành công!", false);
                    else
                        HienThongBao("Đã xóa " + to_string(dem) + " vị trí. " + loiCuoi, true);
                }
                else
                    HienThongBao(loiCuoi.empty() ? "Xóa không thành công!" : loiCuoi, true);

                delete dsXoa;
                dsXoa = nullptr;
                OpenXoa = false;
                MaVTInput[0] = '\0';
                TenVTInput[0] = '\0';
                letterCount_Ma = letterCount_Ten = 0;
            }
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
        if (Clicked && CheckCollisionPointRec(mousePos, btnThemViTri))
        {
            OpenThem = true;
            MaVTInput[0] = '\0';
            TenVTInput[0] = '\0';
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            isMaVTActive = true;
            isTenVTActive = false;
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnSuaViTri))
        {
            OpenSua = true;
            isMaVTActive = false;
            isTenVTActive = true;
        }
        else if (Clicked && CheckCollisionPointRec(mousePos, btnXoaViTri))
        {
            OpenXoa = true;
            dsXoa = new List<ViTriViecLam>;
            isMaVTActive = isTenVTActive = false;
        }
    }

    if (needfill && selVT != nullptr)
    {
        strncpy(MaVTInput, selVT->get_MaVTVL().c_str(), 49);
        letterCount_Ma = strlen(MaVTInput);
        MaVTInput[letterCount_Ma] = '\0';

        strncpy(TenVTInput, selVT->get_TenVTVL().c_str(), 49);
        letterCount_Ten = strlen(TenVTInput);
        TenVTInput[letterCount_Ten] = '\0';

        needfill = false;
    }

    if (OpenThem)
    {
        Typing(isMaVTActive, MaVTInput, letterCount_Ma, mousePos, textMaVT);
        HieuUngGo(isMaVTActive, textMaVT, MaVTInput, 28);

        Typing(isTenVTActive, TenVTInput, letterCount_Ten, mousePos, textTenVT);
        HieuUngGo(isTenVTActive, textTenVT, TenVTInput, 28);
    }
    else if (OpenSua && selVT != nullptr)
    { // Ô nhập chữ chế độ sửa
        DrawTextEx(myFont, MaVTInput, {textMaVT.x + 10, textMaVT.y + 6}, 28, 1, BLACK);
        Typing(isTenVTActive, TenVTInput, letterCount_Ten, mousePos, textTenVT);
        HieuUngGo(isTenVTActive, textTenVT, TenVTInput, 22);
    }
    else if (selVT != nullptr || MaVTInput[0] != '\0')
    {
        // Khi click vào 1 đối tượng trong danh sách (chế độ xem)
        DrawTextEx(myFont, MaVTInput, {textMaVT.x + 10, textMaVT.y + 9}, 22, 1, BLACK);
        DrawTextEx(myFont, TenVTInput, {textTenVT.x + 10, textTenVT.y + 9}, 22, 1, BLACK);
    }

    if (isXacNhan)
    {
        if (OpenThem)
        {
            ViTriViecLam *VTnew = new ViTriViecLam(MaVTInput, TenVTInput);
            try
            {
                QL->ThemViTri(VTnew);
                HienThongBao("Thêm vị trí mới thành công!", false);
            }
            catch (const string &loi)
            {
                HienThongBao(loi, true); // true màu đỏ
            }
            needfill = false;
            letterCount_Ma = 0;
            letterCount_Ten = 0;
            OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
            MaVTInput[0] = '\0';
            TenVTInput[0] = '\0';
        }
        else if (OpenSua && selVT != nullptr)
        {
            ViTriViecLam *VTtam = new ViTriViecLam(selVT->get_MaVTVL(), TenVTInput);
            try
            {
                QL->SuaVTVL(VTtam);
                HienThongBao("Cập nhật vị trí thành công!", false);
            }
            catch (const string &loi)
            {
                HienThongBao(loi, true); // true màu đỏ
            }
            delete VTtam;
            OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
            isMaVTActive = isTenVTActive = false;
            MaVTInput[0] = '\0';
            TenVTInput[0] = '\0';
            letterCount_Ma = 0;
            letterCount_Ten = 0;
        }
    }

    if (isHuy && CheckCollisionPointRec(mousePos, btnHuy))
    {
        OpenSua = OpenThem = OpenXoa = isHuy = isXacNhan = false;
        isMaVTActive = isTenVTActive = false;
        MaVTInput[0] = '\0';
        TenVTInput[0] = '\0';
        letterCount_Ma = 0;
        letterCount_Ten = 0;
    }

    DrawTextEx(myFont, ("Tổng vị trí: " + to_string(QL->get_DB()->get_ListVTVL()->get_size())).c_str(), {1550, 960}, 20, 1, DARKGRAY);
}

void Draw_Screen_Employee(QLNV *QL)
{
    static Texture2D a1;
    static bool isLoaded = false;
    if (!isLoaded)
    {
        a1 = LoadTexture("photo/icon/Asset-1.png");
        isLoaded = true;
    }
    Vector2 pa1 = {370.0f, 45.0f}; // Tọa độ (x, y) postion
    float ra1 = 0.0f;              // Góc xoay (0 độ) rotation
    float sa1 = 0.33f;
    DrawTextureEx(a1, pa1, ra1, sa1, WHITE);
    DrawTextEx(myFont, "Quản Lý Nhân Sự & Vị Trí Việc Làm", {pa1.x + 100, pa1.y}, 45, 1, WHITE);
    DrawTextEx(myFont, "Danh sách và thông tin nhân sự và vị trí của công ty", {pa1.x + 100, pa1.y + 50}, 30, 1, WHITE);
    static int s_gen = 0; // reset trạng thái khi chuyển mục
    bool doReset = (s_gen != g_menuGen);
    s_gen = g_menuGen;
    static bool isOpenNV = true;
    if (doReset)
        isOpenNV = true;
    static bool isOpenVT = false;
    if (doReset)
        isOpenVT = false;
    Vector2 mousePos = GetMousePosition();
    bool Clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    float TabX = 330.0f;
    float TabY = 160.0f;
    float TabH = 90.0f;
    Rectangle TabNV = {TabX, TabY, 300.0f, TabH};
    Rectangle TabVTVL = {TabX + 310.0f, TabY, 400.0f, TabH};
    bool hoverNV = CheckCollisionPointRec(mousePos, TabNV);
    bool hoverVTVL = CheckCollisionPointRec(mousePos, TabVTVL);
    Color CTabNV = isOpenNV == 1 ? BLUE : WHITE;
    Color CTabVT = isOpenVT == 1 ? BLUE : WHITE;
    if (isOpenNV == true && hoverVTVL)
        CTabVT = Fade(BLUE, 0.4);
    if (isOpenVT == true && hoverNV)
        CTabNV = Fade(BLUE, 0.4);
    DrawRectangleRounded(TabNV, 0.3f, 10, CTabNV);
    DrawRectangleRoundedLinesEx(TabNV, 0.3f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Nhân viên", {TabNV.x + 70.0f, TabNV.y + 15.0f}, 36, 1, BLACK);

    DrawRectangleRounded(TabVTVL, 0.3f, 10, CTabVT);
    DrawRectangleRoundedLinesEx(TabNV, 0.3f, 10, 1.5f, Color{225, 230, 240, 255});
    DrawTextEx(myFont, "Vị trí việc làm", {TabVTVL.x + 90.0f, TabVTVL.y + 15.0f}, 36, 1, BLACK);

    Rectangle panelBang = {330, 230, 1450.0f, 690.0f};
    DrawRectangleRounded({panelBang.x + 3, panelBang.y + 4, panelBang.width, panelBang.height}, 0.03f, 10, Fade(BLACK, 0.08f));
    DrawRectangleRounded(panelBang, 0.03f, 10, WHITE);
    DrawRectangleRoundedLinesEx(panelBang, 0.03f, 10, 1.5f, Color{225, 230, 240, 255});

    if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabNV))
    {
        if (!isOpenNV)
            g_resetGen++;
        isOpenNV = true;
        isOpenVT = false;
    }
    else if (!g_isModalActive && Clicked && CheckCollisionPointRec(mousePos, TabVTVL))
    {
        if (!isOpenVT)
            g_resetGen++;
        isOpenVT = true;
        isOpenNV = false;
    }

    if (isOpenNV)
    {
        Draw_Screen_NhanVien(mousePos, Clicked, QL);
    }
    else if (isOpenVT)
    {
        Draw_Screen_VTVL(mousePos, Clicked, QL);
    }
}

