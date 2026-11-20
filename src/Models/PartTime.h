#pragma once
#include <iostream>
#include "ChucVu.h"
#include "Date.h"
#include "Employee.h"
#include "PhongBan.h"
using namespace std;
class PartTime : public Employee
{
private:
    double Time_Work;

public:
    PartTime(const string &, const string &, const Date &, const string &,
             ChucVu * = nullptr, ViTriViecLam * = nullptr, PhongBan * = nullptr,
             const Date & = Date(), const int & = 1, const int & = 0, const double & = 80.0);
    double get_TimeWork() const;
    void set_TimeWork(const double &);
    long long get_ThucLinh(const long long &) override;
    string get_LoaiNV() override;
    virtual ~PartTime();
};

PartTime::PartTime(const string &mnv, const string &ten, const Date &ngay_sinh, const string &gioitinh,
                   ChucVu *cv, ViTriViecLam *vt, PhongBan *pb, const Date &ngay_lam, const int &bac,
                   const int &thuong, const double &time)
    : Employee(mnv, ten, ngay_sinh, gioitinh, cv, vt, pb, ngay_lam, bac, thuong)
{
    this->Time_Work = time;
}
double PartTime::get_TimeWork() const
{
    return this->Time_Work;
}
void PartTime::set_TimeWork(const double &time)
{
    this->Time_Work = time;
}
// double PartTime::get_ThucLinh(DataBase *bl)
// {
//     MucLuong *ml = bl->FindML(this->get_ViTri()->get_MaVTVL(), this->get_BacViTri(), "PartTime");
//     return (this->Time_Work * ml->get_Luong()) + this->get_ChucVu()->get_PhuCap();
// }

string PartTime::get_LoaiNV()
{
    return "PartTime";
}
PartTime::~PartTime()
{
}