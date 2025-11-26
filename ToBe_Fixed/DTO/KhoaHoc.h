#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Lop.h"
using namespace std;

class KhoaHoc {
private:
    string namKhoa; // "2021", "2022", ...
    vector<Lop> danhSachLop; // tối đa 3

public:
    static const size_t MAX_LOP = 3;
    KhoaHoc() {}
    KhoaHoc(const string& nam) : namKhoa(nam) {}

    const string& getNamKhoa() const { return namKhoa; }
    vector<Lop>& getDanhSachLop() { return danhSachLop; }

    bool themLop(const Lop& lop) {
        if (danhSachLop.size() >= MAX_LOP) {
            cout << " Moi khoa hoc chi duoc toi da " << MAX_LOP << " lop.\n";
            return false;
        }
        danhSachLop.push_back(lop);
        return true;
    }

    Lop* timLop(const string& tenLop) {
        for (auto& l : danhSachLop)
            if (l.getTenLop() == tenLop) return &l;
        return nullptr;
    }
};
