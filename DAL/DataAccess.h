#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "../DTO/Lop.h"
using namespace std;

class DataAccess {
public:
    static Lop docFileLop(const string& fileName) {
        Lop lop(fileName, "Chua xac dinh", "2025");
        ifstream file(fileName);
        if (!file.is_open()) return lop;

        string line;
        getline(file, line); // bỏ dòng tiêu đề
        while (getline(file, line)) {
            stringstream ss(line);
            string mssv, hoten, gt, ns, dc, email;

            getline(ss, mssv, '|');
            getline(ss, hoten, '|');
            getline(ss, gt, '|');
            getline(ss, ns, '|');
            getline(ss, dc, '|');
            getline(ss, email, '|');

            SinhVien sv;
            sv.Set_MSSV(mssv);
            size_t pos = hoten.find_last_of(' ');
            if (pos != string::npos) {
                sv.Set_HoLot(hoten.substr(0, pos));
                sv.Set_Ten(hoten.substr(pos + 1));
            } else sv.Set_Ten(hoten);

            sv.Set_GioiTinh(gt);
            sv.Set_NgaySinh(ns);
            sv.Set_DiaChi(dc);
            sv.Set_Email(email);

            lop.addSinhVien(sv);
        }
        file.close();
        return lop;
    }

    static void ghiFileLop(const string& fileName, const Lop& lop) {
        ofstream file(fileName);
        file << "MSSV|Ho va ten|Gioi tinh|Ngay sinh|Dia chi|Email\n";
        for (const auto& sv : lop.getDanhSach()) {
            file << sv.toFileLine() << "\n";
        }
        file.close();
    }
};
