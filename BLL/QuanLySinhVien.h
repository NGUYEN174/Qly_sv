#pragma once
#include <iostream>
#include <vector>
#include "../DAL/DataAccess.h"
using namespace std;

class QuanLySinhVien {
private:
    vector<Lop> danhSachLop;

public:
    // 1. Thêm sinh viên mới
    void themSinhVien() {
        system("cls");
        cout << "=== THEM SINH VIEN MOI ===\n";
        string tenLop;
        cout << "Nhap ten lop: ";
        getline(cin, tenLop);

        Lop* lop = timLop(tenLop);
        if (!lop) {
            Lop newLop(tenLop, "CNTT", "2025");
            danhSachLop.push_back(newLop);
            lop = &danhSachLop.back();
        }

        string ho, ten, gt, ns, dc, makhoa, namhoc;
        cout << "Ho va ten lot: "; getline(cin, ho);
        cout << "Ten: "; getline(cin, ten);
        cout << "Gioi tinh: "; getline(cin, gt);
        cout << "Ngay sinh: "; getline(cin, ns);
        cout << "Dia chi: "; getline(cin, dc);
        cout << "Ma khoa: "; getline(cin, makhoa);
        cout << "Nam hoc: "; getline(cin, namhoc);

        SinhVien sv(ho, ten, gt, ns, dc, makhoa, namhoc);
        lop->addSinhVien(sv);

        cout << "\n✅ Da them sinh vien vao lop " << tenLop << endl;
        system("pause");
    }

    // 2. Thêm từ file
    void themSinhVienTuFile() {
        system("cls");
        cout << "=== THEM SINH VIEN TU FILE ===\n";
        string fileName;
        cout << "Nhap ten file: ";
        getline(cin, fileName);

        auto lop = DataAccess::docFileLop(fileName);
        danhSachLop.push_back(lop);
        cout << "\n✅ Da them du lieu tu file!\n";
        system("pause");
    }

    // 3. Sắp xếp
    void sapXepDanhSach() {
        system("cls");
        Lop* lop = chonLop();
        if (!lop) return;
        lop->sapXepTheoTen();
        cout << "✅ Da sap xep!\n";
        system("pause");
    }

    // 4. Sửa thông tin
    void suaThongTin() {
        system("cls");
        Lop* lop = chonLop();
        if (!lop) return;
        string ho, ten;
        cout << "Nhap ho: "; getline(cin, ho);
        cout << "Nhap ten: "; getline(cin, ten);

        SinhVien* sv = lop->timSinhVienTheoTen(ho, ten);
        if (!sv) { cout << "Khong tim thay!\n"; system("pause"); return; }

        string ns, dc;
        cout << "Ngay sinh moi: "; getline(cin, ns);
        cout << "Dia chi moi: "; getline(cin, dc);
        if (!ns.empty()) sv->Set_NgaySinh(ns);
        if (!dc.empty()) sv->Set_DiaChi(dc);

        cout << "✅ Da cap nhat!\n";
        system("pause");
    }

    // 5. Cấp MSSV
    void capMSSV() {
        system("cls");
        int count = 0;
        for (auto& lop : danhSachLop)
            lop.capMSSV(count);
        cout << "✅ Da cap MSSV!\n";
        system("pause");
    }

    // 6. Cấp email
    void capEmail() {
        system("cls");
        for (auto& lop : danhSachLop)
            lop.capEmail();
        cout << "✅ Da cap email!\n";
        system("pause");
    }

    // 7. Tìm kiếm
    void timKiem() {
        system("cls");
        string mssv;
        cout << "Nhap MSSV: ";
        getline(cin, mssv);
        for (auto& lop : danhSachLop) {
            SinhVien* sv = lop.timSinhVienTheoMSSV(mssv);
            if (sv) {
                sv->Print_SinhVien();
                system("pause");
                return;
            }
        }
        cout << "Khong tim thay!\n";
        system("pause");
    }

    // 8. Xóa sinh viên
    void xoaSinhVien() {
        system("cls");
        string mssv;
        cout << "Nhap MSSV: ";
        getline(cin, mssv);
        for (auto& lop : danhSachLop)
            if (lop.xoaSinhVienTheoMSSV(mssv)) {
                cout << "✅ Da xoa!\n";
                system("pause");
                return;
            }
        cout << "Khong tim thay!\n";
        system("pause");
    }

    // 9. Xuất theo lớp
    void xuatTheoLop() {
        system("cls");
        Lop* lop = chonLop();
        if (lop) lop->xuatDanhSach();
        system("pause");
    }

    // 10. Xuất toàn trường
    void xuatToanTruong() {
        system("cls");
        for (auto& lop : danhSachLop) {
            cout << "\nLop: " << lop.getTenLop() << endl;
            lop.xuatDanhSach();
        }
        system("pause");
    }

    // 11. Xuất file
    void xuatFileLop() {
        system("cls");
        Lop* lop = chonLop();
        if (!lop) return;
        string file;
        cout << "Nhap ten file xuat: ";
        getline(cin, file);
        DataAccess::ghiFileLop(file, *lop);
        cout << "✅ Da xuat file!\n";
        system("pause");
    }

    // Menu
    void menu() {
        int chon;
        do {
            system("cls");
            cout << "\n========================================\n";
            cout << "    CHUONG TRINH QUAN LY SINH VIEN\n";
            cout << "========================================\n";
            cout << " 1 | Them sinh vien moi\n";
            cout << " 2 | Them sinh vien moi tu file\n";
            cout << " 3 | Sap xep danh sach sinh vien\n";
            cout << " 4 | Sua thong tin sinh vien\n";
            cout << " 5 | Cap MSSV\n";
            cout << " 6 | Cap Email\n";
            cout << " 7 | Tim kiem sinh vien\n";
            cout << " 8 | Xoa sinh vien\n";
            cout << " 9 | Xuat danh sach theo lop\n";
            cout << "10 | Xuat danh sach toan truong\n";
            cout << "11 | Xuat file lop (.txt)\n";
            cout << " 0 | Thoat\n";
            cout << "========================================\n";
            cout << "Nhap lua chon: ";
            cin >> chon;
            cin.ignore();
            switch (chon) {
                case 1: themSinhVien(); break;
                case 2: themSinhVienTuFile(); break;
                case 3: sapXepDanhSach(); break;
                case 4: suaThongTin(); break;
                case 5: capMSSV(); break;
                case 6: capEmail(); break;
                case 7: timKiem(); break;
                case 8: xoaSinhVien(); break;
                case 9: xuatTheoLop(); break;
                case 10: xuatToanTruong(); break;
                case 11: xuatFileLop(); break;
                case 0: cout << "Thoat...\n"; break;
                default: cout << "Lua chon khong hop le!\n"; system("pause"); break;
            }
        } while (chon != 0);
    }

private:
    Lop* timLop(const string& tenLop) {
        for (auto& lop : danhSachLop)
            if (lop.getTenLop() == tenLop)
                return &lop;
        return nullptr;
    }

    Lop* chonLop() {
        cout << "Nhap ten lop: ";
        string tenLop;
        getline(cin, tenLop);
        return timLop(tenLop);
    }
};
