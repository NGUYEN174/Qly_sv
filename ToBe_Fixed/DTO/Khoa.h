#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "KhoaHoc.h"
using namespace std;

class Khoa {
private:
    string maKhoa;
    string tenKhoa;
    vector<KhoaHoc> danhSachKhoaHoc; // 2021..2025

public:
    Khoa() {}
    Khoa(const string& ma, const string& ten) : maKhoa(ma), tenKhoa(ten) {
        for (int y = 2021; y <= 2025; ++y) {
            danhSachKhoaHoc.emplace_back(to_string(y));
        }
    }

    string getMaKhoa() const { return maKhoa; }
    string getTenKhoa() const { return tenKhoa; }
    vector<KhoaHoc>& getDanhSachKhoaHoc() { return danhSachKhoaHoc; }

    KhoaHoc* timKhoaHoc(const string& nam) {
        for (auto& kh : danhSachKhoaHoc)
            if (kh.getNamKhoa() == nam) return &kh;
        return nullptr;
    }

    KhoaHoc* timKhoaHocTheoIndex(size_t idx) {
        if (idx < danhSachKhoaHoc.size()) return &danhSachKhoaHoc[idx];
        return nullptr;
    }
};
