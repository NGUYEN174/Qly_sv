#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "SinhVien.h"
using namespace std;

class Lop {
private:
    string tenLop;
    string maKhoa;
    string namKhoa; // khoá (ví dụ "2023")
    vector<SinhVien> danhSachSV;

public:
    static const size_t MAX_SV = 50;
    Lop() {}
    Lop(const string& ten, const string& maK, const string& nam)
        : tenLop(ten), maKhoa(maK), namKhoa(nam) {}

    const string& getTenLop() const { return tenLop; }
    const string& getMaKhoa() const { return maKhoa; }
    const string& getNamKhoa() const { return namKhoa; }
    vector<SinhVien>& getDanhSach() { return danhSachSV; }
    const vector<SinhVien>& getDanhSach() const { return danhSachSV; }
    size_t soLuongSV() const { return danhSachSV.size(); }

    bool addSinhVien(const SinhVien& sv) {
        if (danhSachSV.size() >= MAX_SV) {
            cout << "❌ Lop " << tenLop << " da dat toi da " << MAX_SV << " sinh vien.\n";
            return false;
        }
        SinhVien tmp = sv;
        tmp.Set_MaKhoa(maKhoa);
        tmp.Set_NamKhoa(namKhoa);
        danhSachSV.push_back(tmp);
        return true;
    }

    size_t addDanhSachTuFile(const vector<SinhVien>& list) {
        size_t added = 0;
        for (const auto& sv : list) {
            if (danhSachSV.size() >= MAX_SV) break;
            SinhVien tmp = sv;
            tmp.Set_MaKhoa(maKhoa);
            tmp.Set_NamKhoa(namKhoa);
            danhSachSV.push_back(tmp);
            ++added;
        }
        return added;
    }

    void sapXepTheoTenHo() {
        sort(danhSachSV.begin(), danhSachSV.end(),
             [](const SinhVien& a, const SinhVien& b) {
                 if (a.Get_Ten() != b.Get_Ten()) return a.Get_Ten() < b.Get_Ten();
                 return a.Get_HoLot() < b.Get_HoLot();
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
                            [&](const SinhVien& sv) { return sv.Get_MSSV() == mssv; });
        if (it != danhSachSV.end()) {
            danhSachSV.erase(it, danhSachSV.end());
            return true;
        }
        return false;
    }

    // capMSSV: counter passed by reference (per khoa+nam)
    void capMSSV(int& counter, const string& nam, const string& maK) {
        for (auto& sv : danhSachSV) {
            ++counter;
            char buf[10];
            sprintf(buf, "%03d", counter);
            string mssv = nam + maK + string(buf); // ex: 2025101001
            sv.Set_MSSV(mssv);
            sv.Set_MaKhoa(maK);
            sv.Set_NamKhoa(nam);
        }
    }

    void capEmail() {
        for (auto& sv : danhSachSV) {
            if (!sv.Get_MSSV().empty()) {
                sv.Set_Email(sv.Get_MSSV() + "@student.edu.vn");
            } else {
                string email = sv.Get_Ten() + "." + sv.Get_HoLot();
                for (auto& c : email) if (c == ' ') c = '.';
                email += "@student.edu.vn";
                sv.Set_Email(email);
            }
        }
    }

    void xuatDanhSach() const {
        cout << left << setw(12) << "MSSV"
             << setw(25) << "Ho va ten"
             << setw(10) << "Gioi tinh"
             << setw(15) << "Ngay sinh"
             << setw(20) << "Dia chi"
             << setw(25) << "Email" << endl;
        cout << string(107, '-') << endl;
        for (const auto& sv : danhSachSV) sv.Print_SinhVien();
    }
};
