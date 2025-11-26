#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../DTO/Lop.h"
#include "../DTO/SinhVien.h"
using namespace std;

class DataAccess {
public:
    // Đọc file trả về vector<SinhVien>
    // Dòng: MSSV|Ho va ten|Gioi tinh|Ngay sinh|Dia chi|Email|MaKhoa|NamKhoa
    static vector<SinhVien> docDanhSachTuFile(const string& fileName) {
        vector<SinhVien> res;
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << " Khong mo duoc file: " << fileName << endl;
            return res;
        }
        string line;
        bool firstLine = true;
        while (getline(file, line)) {
            if (line.empty()) continue;
            // nếu dòng header chứa "MSSV" thì bỏ qua
            if (firstLine && line.find("MSSV") != string::npos) { firstLine = false; continue; }
            firstLine = false;
            stringstream ss(line);
            string mssv, hoten, gt, ns, dc, email, makhoa, namkhoa;
            getline(ss, mssv, '|');
            getline(ss, hoten, '|');
            getline(ss, gt, '|');
            getline(ss, ns, '|');
            getline(ss, dc, '|');
            getline(ss, email, '|');
            getline(ss, makhoa, '|');
            getline(ss, namkhoa, '|');

            string ho, ten;
            size_t pos = hoten.find_last_of(' ');
            if (pos != string::npos) {
                ho = hoten.substr(0, pos);
                ten = hoten.substr(pos + 1);
            } else {
                ten = hoten;
            }
            SinhVien sv(ho, ten, gt, ns, dc, makhoa, namkhoa);
            if (!mssv.empty()) sv.Set_MSSV(mssv);
            if (!email.empty()) sv.Set_Email(email);
            res.push_back(sv);
        }
        file.close();
        return res;
    }

    // Ghi 1 lớp ra file
    static void ghiFileLop(const string& fileName, const Lop& lop) {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << " Khong mo duoc file de ghi: " << fileName << endl;
            return;
        }
        file << "MSSV|Ho va ten|Gioi tinh|Ngay sinh|Dia chi|Email|MaKhoa|NamKhoa\n";
        for (const auto& sv : lop.getDanhSach()) {
            file << sv.toFileLine() << "\n";
        }
        file.close();
    }
};
