#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "SinhVien.h"
using namespace std;

class Lop {
private:
    string tenLop;
    string khoa;
    string khoaHoc;
    vector<SinhVien> danhSachSV;

public:
    Lop() {}
    Lop(string tenLop, string khoa, string khoaHoc)
        : tenLop(tenLop), khoa(khoa), khoaHoc(khoaHoc) {}

    // ===== Thao tác sinh viên =====
    void addSinhVien(const SinhVien& sv) {
        danhSachSV.push_back(sv);
    }

    void sapXepTheoTen() {
        sort(danhSachSV.begin(), danhSachSV.end(),
             [](const SinhVien& a, const SinhVien& b) {
                 return a.Get_Ten() < b.Get_Ten();
             });
    }

    SinhVien* timSinhVienTheoTen(const string& ho, const string& ten) {
        for (auto& sv : danhSachSV)
            if (sv.Get_HoLot() == ho && sv.Get_Ten() == ten)
                return &sv;
        return nullptr;
    }

    SinhVien* timSinhVienTheoMSSV(const string& mssv) {
        for (auto& sv : danhSachSV)
            if (sv.Get_MSSV() == mssv)
                return &sv;
        return nullptr;
    }

    bool xoaSinhVienTheoMSSV(const string& mssv) {
        auto it = remove_if(danhSachSV.begin(), danhSachSV.end(),
                            [&](const SinhVien& sv) {
                                return sv.Get_MSSV() == mssv;
                            });
        if (it != danhSachSV.end()) {
            danhSachSV.erase(it, danhSachSV.end());
            return true;
        }
        return false;
    }

    void capMSSV(int& count) {
        for (auto& sv : danhSachSV) {
            if (sv.Get_MSSV().empty()) {
                sv.Set_MSSV("SV" + to_string(++count));
            }
        }
    }

    void capEmail() {
        for (auto& sv : danhSachSV) {
            string email = sv.Get_Ten() + "." + sv.Get_HoLot();
            for (auto& c : email)
                if (c == ' ') c = '.';
            email += "@student.edu.vn";
            sv.Set_Email(email);
        }
    }

    // ===== Xuất danh sách =====
    void xuatDanhSach() const {
        cout << left << setw(12) << "MSSV"
             << setw(25) << "Ho va ten"
             << setw(10) << "Gioi tinh"
             << setw(15) << "Ngay sinh"
             << setw(20) << "Dia chi"
             << setw(30) << "Email" << endl;
        cout << string(112, '-') << endl;
        for (auto& sv : danhSachSV)
            sv.Print_SinhVien();
    }

    // Getter
    const string& getTenLop() const { return tenLop; }
    vector<SinhVien>& getDanhSach() { return danhSachSV; }
    const vector<SinhVien>& getDanhSach() const { return danhSachSV; }
};
