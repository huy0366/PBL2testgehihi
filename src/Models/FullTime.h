#pragma once
#include <iostream>
#include "ChucVu.h"
#include "Date.h"
#include "Employee.h"
#include "PhongBan.h"
#include "MucLuong.h"

using namespace std;
class FullTime : public Employee
{
private:
    double SoNgayCong;
    double HeSo;

public:
    FullTime();
    FullTime(const string &, const string &, const Date &, const string &, ChucVu * = nullptr,
             ViTriViecLam * = nullptr, PhongBan * = nullptr, const Date & = Date(),
             const int & = 1, const int & = 0, const double & = 0.0, const double & = 1.0);
    double get_SoNgayCong() const;
    void set_SoNgayCong(const double &);
    double get_HeSo() const;
    long long get_ThucLinh(const long long &) override;
    long long get_ThucLinh(const long long &lcb, double ngayCong, double gioOT, long long &tienOT) override;
    string get_LoaiNV() override;
    double tinhHS(const Date &);
    virtual ~FullTime();
};

FullTime::FullTime(const string &mnv, const string &ten, const Date &ngay_sinh, const string &gioitinh,
                   ChucVu *cv, ViTriViecLam *vt, PhongBan *pb, const Date &ngay_lam, const int &bac,
                   const int &thuong, const double &songaycong, const double &heso)
    : Employee(mnv, ten, ngay_sinh, gioitinh, cv, vt, pb, ngay_lam, bac, thuong)
{
    this->SoNgayCong = songaycong;
    this->HeSo = (heso > 0.0) ? heso : tinhHS(ngay_lam);
}
double FullTime::get_SoNgayCong() const
{
    return this->SoNgayCong;
}
void FullTime::set_SoNgayCong(const double &snc)
{
    this->SoNgayCong = snc;
}

double FullTime::get_HeSo() const
{
    return this->HeSo;
}

string FullTime::get_LoaiNV()
{
    return "FullTime";
}

double FullTime::tinhHS(const Date &d)
{
    int thamNien = Date::DateHienTai().get_year() - d.get_year();
    return (1.0 + ((thamNien / 3) * 0.3));
}

FullTime::~FullTime()
{
}