#pragma once
#include <iostream>
#include <string>
#include "Date.h"
#include "Employee.h"

using namespace std;

class ChamCong
{
private:
    Employee *NV; // Con trỏ trỏ trực tiếp đến nhân viên (FullTime hoặc PartTime)
    Date Ngay;
    int TrangThai; // 1: Đủ, 2: Nửa, 3: Phép, 4: Không phép, 5: Tăng ca
    double SoGio;
    string GhiChu;

public:
    ChamCong(Employee *, const Date &, const int &,
             const double &, const string &);
    Employee *get_NV() const;
    void set_NV(Employee *);

    Date get_Ngay() const;
    void set_Ngay(const Date &);

    int get_TrangThai() const;
    void set_TrangThai(const int &);

    double get_SoGio() const;
    void set_SoGio(const double &);

    string get_GhiChu() const;
    void set_GhiChu(const string &);

    static bool KiemTraNgayHopLe(const Date &);
};

inline bool ChamCong::KiemTraNgayHopLe(const Date &d)
{
    Date now = Date::DateHienTai();
    if (d > now)
    {
        throw string("Không thể chấm công cho ngày trong tương lai (sau ngày hiện tại: " + now.ToString() + ")!");
    }
    int prevMonth = now.get_month() - 1;
    int prevYear = now.get_year();
    if (prevMonth < 1)
    {
        prevMonth = 12;
        prevYear--;
    }
    Date minDate(1, prevMonth, prevYear);
    if (d < minDate)
    {
        throw string("Chỉ được phép chấm công trong tháng này (tháng " + to_string(now.get_month()) + ") và tháng trước (tháng " + to_string(prevMonth) + ")!");
    }
    return true;
}

ChamCong::ChamCong(Employee *nv = nullptr, const Date &ngay = Date(), const int &tt = 1,
                   const double &gio = 8.0, const string &gc = "")
    : NV(nv), Ngay(ngay), TrangThai(tt), SoGio(gio), GhiChu(gc) {}

Employee *ChamCong::get_NV() const { return this->NV; }
void ChamCong::set_NV(Employee *nv) { this->NV = nv; }

Date ChamCong::get_Ngay() const { return this->Ngay; }
void ChamCong::set_Ngay(const Date &d)
{
    KiemTraNgayHopLe(d);
    this->Ngay = d;
}

int ChamCong::get_TrangThai() const { return this->TrangThai; }
void ChamCong::set_TrangThai(const int &tt) { this->TrangThai = tt; }

double ChamCong::get_SoGio() const { return this->SoGio; }
void ChamCong::set_SoGio(const double &g) { this->SoGio = g; }

string ChamCong::get_GhiChu() const { return this->GhiChu; }
void ChamCong::set_GhiChu(const string &gc) { this->GhiChu = gc; }