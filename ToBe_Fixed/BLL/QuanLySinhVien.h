#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits> // cho numeric_limits
#include "../DTO/Khoa.h"
#include "../DAL/DataAccess.h"
using namespace std;

class QuanLySinhVien {
private:
    vector<Khoa> danhSachKhoa;

public:
    QuanLySinhVien() {
        // 9 khoa cố định theo hình bạn gửi
        danhSachKhoa.emplace_back("101", "CO KHI");
        danhSachKhoa.emplace_back("102", "CONG NGHE THONG TIN");
        danhSachKhoa.emplace_back("104", "NHIET - DIEN LANH");
        danhSachKhoa.emplace_back("105", "DIEN");
        danhSachKhoa.emplace_back("106", "DIEN TU - VIEN THONG");
        danhSachKhoa.emplace_back("107", "HOA");
        danhSachKhoa.emplace_back("117", "MOI TRUONG");
        danhSachKhoa.emplace_back("118", "QUAN LI DU AN");
        danhSachKhoa.emplace_back("121", "KIEN TRUC");
    }

    void intro() {
        system("cls");
        cout << "============================================================\n";
        cout << "         CHAO MUNG DEN VOI HE THONG QUAN LY SINH VIEN \n";
        cout << "                 TRUONG DAI HOC ABC - CONSOLE APP\n";
        cout << "============================================================\n";
        cout << "  Tac gia: Huynh Hieu Nghia 24T_DT3 & Mai Nguyen Dat Nguyen 24T_DT4\n";
        cout << "\t\t Mo ta : Quan ly sinh vien \n";
        cout << "============================================================\n";
        cout << " Bam Enter de tiep tuc...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // --- Chức năng ---
    void themSinhVien() {
        system("cls");
        cout << "=== THEM SINH VIEN MOI ===\n";
        Khoa* khoa = chonKhoa();
        if (!khoa) return;
        cout << "Chon nam khoa (2021-2025): ";
        string nam; getline(cin, nam);
        KhoaHoc* khoahoc = khoa->timKhoaHoc(nam);
        if (!khoahoc) { cout << "Nam khoa khong hop le.\n"; system("pause"); return; }

        cout << "Nhap ten lop: ";
        string tenLop; getline(cin, tenLop);
        //normalization(ex: 24T_DT4 == 24t_dt4)
        for (auto &x : tenLop){
                    x = toupper(x);
        }
        Lop* lop = khoahoc->timLop(tenLop);
        if (!lop) {
            // tao lop neu co the
            cout << "Lop chua ton tai. Ban co muon tao (y/n)? ";
            string c; getline(cin, c);
            if (c != "y" && c != "Y") return;
            Lop newLop(tenLop, khoa->getMaKhoa(), nam);
            if (!khoahoc->themLop(newLop)) { system("pause"); return; }
            lop = &khoahoc->getDanhSachLop().back();
        }

        if (lop->soLuongSV() >= Lop::MAX_SV) {
            cout << "Lop da day.\n"; system("pause"); return;
        }

        string ho, ten, gt, ns, dc;
        cout << "Ho va ten lot: "; getline(cin, ho);
        cout << "Ten: "; getline(cin, ten);
        cout << "Gioi tinh: "; getline(cin, gt);
        cout << "Ngay sinh: "; getline(cin, ns);
        cout << "Dia chi: "; getline(cin, dc);

        SinhVien sv(ho, ten, gt, ns, dc, khoa->getMaKhoa(), nam);
        if (lop->addSinhVien(sv)) cout << " Da them sinh vien.\n";
        system("pause");
    }

    void themSinhVienTuFile() {
        system("cls");
        cout << "=== THEM SINH VIEN TU FILE ===\n";
        string file; cout << "Nhap duong dan file: "; getline(cin, file);
        vector<SinhVien> ds = DataAccess::docDanhSachTuFile(file);
        if (ds.empty()) { cout << "Khong co du lieu.\n"; system("pause"); return; }

        Khoa* khoa = chonKhoa(); if (!khoa) return;
        cout << "Chon nam khoa (2021-2025): "; string nam; getline(cin, nam);
        KhoaHoc* khoahoc = khoa->timKhoaHoc(nam); if (!khoahoc) { cout << "Nam khoa khong hop le.\n"; system("pause"); return; }

        cout << "Nhap ten lop (se tao neu chua co): "; string tenLop; getline(cin, tenLop);
        Lop* lop = khoahoc->timLop(tenLop);
        if (!lop) {
            Lop newLop(tenLop, khoa->getMaKhoa(), nam);
            if (!khoahoc->themLop(newLop)) { system("pause"); return; }
            lop = &khoahoc->getDanhSachLop().back();
        }

        size_t added = lop->addDanhSachTuFile(ds);
        cout << " Da them " << added << " sinh vien tu file.\n";
        system("pause");
    }

    void sapXepDanhSach() {
        system("cls");
        Khoa* k = chonKhoa(); if (!k) return;
        cout << "Chon nam khoa: "; string nam; getline(cin, nam);
        KhoaHoc* kh = k->timKhoaHoc(nam); if (!kh) { cout << "Nam khong hop le.\n"; system("pause"); return; }
        Lop* l = chonLop(*kh); if (!l) return;
        l->sapXepTheoTenHo();
        cout << " Da sap xep theo ten -> ho lot.\n"; system("pause");
    }

    void suaThongTin() {
        system("cls");
        Khoa* k = chonKhoa(); if (!k) return;
        cout << "Chon nam khoa: "; string nam; getline(cin, nam);
        KhoaHoc* kh = k->timKhoaHoc(nam); if (!kh) { cout << "Nam khong hop le.\n"; system("pause"); return; }
        Lop* l = chonLop(*kh); if (!l) return;

        string ho, ten;
        cout << "Nhap ho: "; getline(cin, ho);
        cout << "Nhap ten: "; getline(cin, ten);
        SinhVien* sv = l->timSinhVienTheoTen(ho, ten);
        if (!sv) { cout << "Khong tim thay!\n"; system("pause"); return; }

        string ns, dc; 
        cout << "Ngay sinh moi (de trong neu khong doi): "; getline(cin, ns);
        cout << "Dia chi moi (de trong neu khong doi): "; getline(cin, dc);
        if (!ns.empty()) sv->Set_NgaySinh(ns);
        if (!dc.empty()) sv->Set_DiaChi(dc);
        cout << " Da cap nhat.\n"; system("pause");
    }

    void capMSSV() {
        system("cls");
        cout << "=== CAP MSSV TOAN TRUONG ===\n";
        cout << "Nhap nam de lam MSSV (vd 2025): ";
        string nam; getline(cin, nam);
        if (nam.empty()) { cout << "Nam khong hop le.\n"; system("pause"); return; }

        for (auto& k : danhSachKhoa) {
            // cap per khoa-per-nam: counter reset cho mỗi (khoa, nam)
            for (auto& kh : k.getDanhSachKhoaHoc()) {
                if (kh.getNamKhoa() != nam) continue;
                int counter = 0;
                for (auto& l : kh.getDanhSachLop()) {
                    l.sapXepTheoTenHo();
                    l.capMSSV(counter, nam, k.getMaKhoa());
                }
            }
        }
        cout << " Da cap MSSV.\n"; system("pause");
    }

    void capEmail() {
        system("cls");
        for (auto& k : danhSachKhoa)
            for (auto& kh : k.getDanhSachKhoaHoc())
                for (auto& l : kh.getDanhSachLop())
                    l.capEmail();
        cout << " Da cap email (email = MSSV@student.edu.vn khi MSSV co san).\n";
        system("pause");
    }

    void timKiem() {
        system("cls");
        cout << "Nhap MSSV can tim: "; string mssv; getline(cin, mssv);
        for (auto& k : danhSachKhoa)
            for (auto& kh : k.getDanhSachKhoaHoc())
                for (auto& l : kh.getDanhSachLop()) {
                    SinhVien* sv = l.timSinhVienTheoMSSV(mssv);
                    if (sv) {
                        cout << "Khoa: " << k.getTenKhoa() << " (" << k.getMaKhoa() << ") - Nam: " << kh.getNamKhoa() << " - Lop: " << l.getTenLop() << "\n";
                        sv->Print_SinhVien();
                        system("pause");
                        return;
                    }
                }
        cout << "Khong tim thay MSSV: " << mssv << "\n"; system("pause");
    }

    void xoaSinhVien() {
        system("cls");
        cout << "Nhap MSSV can xoa: "; string mssv; getline(cin, mssv);
        for (auto& k : danhSachKhoa)
            for (auto& kh : k.getDanhSachKhoaHoc())
                for (auto& l : kh.getDanhSachLop())
                    if (l.xoaSinhVienTheoMSSV(mssv)) {
                        cout << " Da xoa.\n"; system("pause"); return;
                    }
        cout << "Khong tim thay.\n"; system("pause");
    }

    void xuatTheoLop() {
        system("cls");
        Khoa* k = chonKhoa(); if (!k) return;
        cout << "Chon nam khoa: "; string nam; getline(cin, nam);
        KhoaHoc* kh = k->timKhoaHoc(nam); if (!kh) { cout << "Nam khong hop le.\n"; system("pause"); return; }
        Lop* l = chonLop(*kh); if (!l) return;
        cout << "\nLop: " << l->getTenLop() << " | Khoa: " << k->getTenKhoa() << " | Nam: " << nam << "\n";
        l->xuatDanhSach(); system("pause");
    }

    void xuatToanTruong() {
        system("cls");
        for (auto& k : danhSachKhoa) {
            cout << "\n==== Khoa: " << k.getTenKhoa() << " (" << k.getMaKhoa() << ") ====\n";
            for (auto& kh : k.getDanhSachKhoaHoc()) {
                cout << "\n--- Nam khoa: " << kh.getNamKhoa() << " ---\n";
                for (auto& l : kh.getDanhSachLop()) {
                    cout << "\nLop: " << l.getTenLop() << " | SL: " << l.soLuongSV() << "\n";
                    l.xuatDanhSach();
                }
            }
        }
        system("pause");
    }

    void xuatFileLop() {
        system("cls");
        Khoa* k = chonKhoa(); if (!k) return;
        cout << "Chon nam khoa: "; string nam; getline(cin, nam);
        KhoaHoc* kh = k->timKhoaHoc(nam); if (!kh) { cout << "Nam khong hop le.\n"; system("pause"); return; }
        Lop* l = chonLop(*kh); if (!l) return;
        cout << "Nhap ten file xuat (vd: lopA.txt): "; string file; getline(cin, file);
        DataAccess::ghiFileLop(file, *l);
        cout << "Da xuat file: " << file << "\n"; system("pause");
    }

    // Menu
    void menu() {
        int chon = -1;
        do {
            system("cls");
            cout << "\n===============================================\n";
            cout << "    CHUONG TRINH QUAN LY SINH VIEN\n";
            cout << "===============================================\n";
            cout << " 1 | Them sinh vien moi\n";
            cout << " 2 | Them sinh vien tu file\n";
            cout << " 3 | Sap xep danh sach sinh vien (lop)\n";
            cout << " 4 | Sua thong tin sinh vien\n";
            cout << " 5 | Cap MSSV (toan truong)\n";
            cout << " 6 | Cap Email (toan truong)\n";
            cout << " 7 | Tim kiem sinh vien\n";
            cout << " 8 | Xoa sinh vien\n";
            cout << " 9 | Xuat danh sach theo lop\n";
            cout << "10 | Xuat danh sach toan truong\n";
            cout << "11 | Xuat file lop (.txt)\n";
            cout << " 0 | Thoat\n";
            cout << "===============================================\n";
            cout << "Nhap lua chon: ";
            if (!(cin >> chon)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                chon = -1;
            } else cin.ignore();
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
    Khoa* timKhoa(const string& ma) {
        for (auto& k : danhSachKhoa) if (k.getMaKhoa() == ma) return &k;
        return nullptr;
    }

    Khoa* chonKhoa() {
        cout << "Danh sach khoa:\n";
        for (const auto& k : danhSachKhoa) cout << "  " << k.getMaKhoa() << " | " << k.getTenKhoa() << "\n";
        cout << "Nhap ma khoa: ";
        string ma; getline(cin, ma);
        return timKhoa(ma);
    }

    Lop* chonLop(KhoaHoc& kh) {
        if (kh.getDanhSachLop().empty()) {
            cout << "Khong co lop trong khoa hoc. Ban co muon tao lop? (y/n): ";
            string c; getline(cin, c);
            if (c != "y" && c != "Y") return nullptr;
            cout << "Nhap ten lop: "; string ten; getline(cin, ten);
            cout << "Nhap nam khoa: "; string nam; getline(cin, nam);
            if (nam.empty()) nam = kh.getNamKhoa();
            Lop newLop(ten, "000", nam); // maKhoa will be set when inserted from caller
            if (!kh.themLop(newLop)) return nullptr;
            return &kh.getDanhSachLop().back();
        }
        cout << "Danh sach lop:\n";
        for (auto& l : kh.getDanhSachLop())
            cout << "  " << l.getTenLop() << " | Nam: " << l.getNamKhoa() << " | SL: " << l.soLuongSV() << "\n";
        cout << "Nhap ten lop: "; string ten; getline(cin, ten);
        return kh.timLop(ten);
    }
};

