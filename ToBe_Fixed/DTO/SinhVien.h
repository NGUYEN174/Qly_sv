#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class SinhVien {
private:
    string MSSV;
    string HoLot;
    string Ten;
    string GioiTinh;
    string NgaySinh;
    string DiaChi;
    string Email;
    string MaKhoa;
    string NamKhoa; // khoá (ví dụ "2023")

public:
    SinhVien() {}
    SinhVien(const string& ho, const string& ten, const string& gioiTinh,
             const string& ngaySinh, const string& diaChi,
             const string& maKhoa, const string& namKhoa)
        : HoLot(ho), Ten(ten), GioiTinh(gioiTinh),
          NgaySinh(ngaySinh), DiaChi(diaChi),
          MaKhoa(maKhoa), NamKhoa(namKhoa) {}

    // Getters
    string Get_MSSV() const { return MSSV; }
    string Get_HoLot() const { return HoLot; }
    string Get_Ten() const { return Ten; }
    string Get_GioiTinh() const { return GioiTinh; }
    string Get_NgaySinh() const { return NgaySinh; }
    string Get_DiaChi() const { return DiaChi; }
    string Get_Email() const { return Email; }
    string Get_MaKhoa() const { return MaKhoa; }
    string Get_NamKhoa() const { return NamKhoa; }

    // Setters
    void Set_MSSV(const string& m) { MSSV = m; }
    void Set_HoLot(const string& h) { HoLot = h; }
    void Set_Ten(const string& t) { Ten = t; }
    void Set_GioiTinh(const string& g) { GioiTinh = g; }
    void Set_NgaySinh(const string& n) { NgaySinh = n; }
    void Set_DiaChi(const string& d) { DiaChi = d; }
    void Set_Email(const string& e) { Email = e; }
    void Set_MaKhoa(const string& mk) { MaKhoa = mk; }
    void Set_NamKhoa(const string& nk) { NamKhoa = nk; }

    string HoVaTen() const {
        if (HoLot.empty()) return Ten;
        return HoLot + " " + Ten;
    }

    void Print_SinhVien() const {
        cout << left << setw(12) << MSSV
             << setw(25) << HoVaTen()
             << setw(10) << GioiTinh
             << setw(15) << NgaySinh
             << setw(20) << DiaChi
             << setw(25) << Email << endl;
    }

    // line for file: MSSV|Ho va ten|Gioi tinh|Ngay sinh|Dia chi|Email|MaKhoa|NamKhoa
    string toFileLine() const {
        return MSSV + "|" + HoVaTen() + "|" + GioiTinh + "|" +
               NgaySinh + "|" + DiaChi + "|" + Email + "|" +
               MaKhoa + "|" + NamKhoa;
    }
};
