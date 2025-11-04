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
    string NamHoc;

public:
    SinhVien() {}

    SinhVien(string ho, string ten, string gioiTinh, string ngaySinh,
             string diaChi, string maKhoa, string namHoc)
        : HoLot(ho), Ten(ten), GioiTinh(gioiTinh),
          NgaySinh(ngaySinh), DiaChi(diaChi),
          MaKhoa(maKhoa), NamHoc(namHoc) {}

    // Getter - Setter
    string Get_MSSV() const { return MSSV; }
    string Get_HoLot() const { return HoLot; }
    string Get_Ten() const { return Ten; }
    string Get_GioiTinh() const { return GioiTinh; }
    string Get_NgaySinh() const { return NgaySinh; }
    string Get_DiaChi() const { return DiaChi; }
    string Get_Email() const { return Email; }

    void Set_MSSV(const string& mssv) { MSSV = mssv; }
    void Set_HoLot(const string& ho) { HoLot = ho; }
    void Set_Ten(const string& ten) { Ten = ten; }
    void Set_GioiTinh(const string& gt) { GioiTinh = gt; }
    void Set_NgaySinh(const string& ns) { NgaySinh = ns; }
    void Set_DiaChi(const string& dc) { DiaChi = dc; }
    void Set_Email(const string& email) { Email = email; }

    string HoVaTen() const { return HoLot + " " + Ten; }

    // Hiển thị sinh viên
    void Print_SinhVien() const {
        cout << left << setw(12) << MSSV
             << setw(25) << HoVaTen()
             << setw(10) << GioiTinh
             << setw(15) << NgaySinh
             << setw(20) << DiaChi
             << setw(30) << Email << endl;
    }

    // Dòng ghi file
    string toFileLine() const {
        return MSSV + "|" + HoVaTen() + "|" + GioiTinh + "|" +
               NgaySinh + "|" + DiaChi + "|" + Email;
    }
};
