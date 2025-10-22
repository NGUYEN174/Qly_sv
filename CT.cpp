#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <windows.h>

#define MAX_SV 50
#define MAX_KHOA 9
#define MAX_LOP 3


struct SinhVien {
    char HoLot[20];
    char Ten[10];
    char GioiTinh[10];
    char NgaySinh[30];
    char DiaChi[30];
    int stt;
    char email[100];
    char MSSV[20];
    char MaKhoa[4];
    char TenKhoa[20];
    char Lop[10];
    char KhoaHoc[5]; 
    int check1; 
    int check2; 
};

struct Lop {
    char TenLop[10];
    SinhVien ds_SV[MAX_SV];
    int soLuongSV;
};

typedef struct SinhVien SinhVien;
typedef struct Lop LopHoc;


int TaoLop(SinhVien *sv, LopHoc ds_Lop[][MAX_KHOA][MAX_LOP]);
void XoaXuongDong(char s[]);
void PhanLoaiKhoa(SinhVien *sv);
void ThemSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP]);
void ThemSinhVienTuFile(LopHoc dsLop[][MAX_KHOA][MAX_LOP]);
void SapXepSinhVien_TheoLop(LopHoc *Lop);
void SapXepSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
int CapMSSV_TheoLop(LopHoc *Lop, LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam); 
void CapMSSV(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
int CapEmail_TheoLop(LopHoc *Lop);
void CapEmail(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
void TimKiemSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
void SuaThongTinSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
void XuatDanhSachSV_TheoLop(LopHoc Lop);
void XuatLopTheoYeuCau(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
void XuatDanhSachSV_ToanTruong(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
void XoaSinhVien_KhoiLop(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int *soLuongNam);
void LuuFileNhiPhan(const char *tenFile, LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
void LuuFileTheoLop(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam);
void SetColor(int color);

void XoaXuongDong(char s[]) {
    if (s[strlen(s)-1] == '\n')
        s[strlen(s)-1] = '\0';
}

void PhanLoaiKhoa(SinhVien *sv) {
    if(strcmp(sv->MaKhoa,"101")==0)
        strcpy(sv->TenKhoa,"Co khi");
    else if(strcmp(sv->MaKhoa,"102")==0)
        strcpy(sv->TenKhoa,"Cong nghe thong tin");
    else if(strcmp(sv->MaKhoa,"104")==0)
        strcpy(sv->TenKhoa,"Nhiet - Dien lanh");
    else if(strcmp(sv->MaKhoa,"105")==0)
        strcpy(sv->TenKhoa,"Dien");
    else if(strcmp(sv->MaKhoa,"106")==0)
        strcpy(sv->TenKhoa,"Dien tu - Vien thong");
    else if(strcmp(sv->MaKhoa,"107")==0)
        strcpy(sv->TenKhoa,"Hoa");
    else if(strcmp(sv->MaKhoa,"117")==0)
        strcpy(sv->TenKhoa,"Moi truong");
    else if(strcmp(sv->MaKhoa,"118")==0)
        strcpy(sv->TenKhoa,"Quan li du an");
    else if(strcmp(sv->MaKhoa,"121")==0)
        strcpy(sv->TenKhoa,"Kien truc");
    else {
        printf("MA KHOA KHONG HOP LE!\n");
    }
}

const char* lopCoKhi[3] = {"CDT1", "CDT2", "CDT3"};
const char* lopCNTT[3] = {"T_DT1", "T_DT2", "T_DT3"};
const char* lopNDL[3] = {"N1", "N2", "N3"};
const char* lopDTVT[3] = {"DT1", "DT2", "DT3"};
const char* lopDien[3] = {"D1", "D2", "D3"};
const char* lopHoa[3] = {"H1", "H2", "H3"};
const char* lopMT[3] = {"MT1", "MT2", "MT3"};
const char* lopQLDA[3] = {"QLDA1", "QLDA2", "QLDA3"};
const char* lopKT[3] = {"KT1", "KT2", "KT3"};

const int Nam_Hoc[] = {2020, 2021, 2022, 2023, 2024};
const int So_NHoc = sizeof(Nam_Hoc)/sizeof(Nam_Hoc[0]);

int KiemTraMaKhoaHopLe(const char* maKhoa) {
    const char* danhSachMaKhoa[] = {"101", "102", "104", "105", "106", "107", "117", "118", "121"};
    for (int i = 0; i < 9; i++) {
        if (strcmp(maKhoa, danhSachMaKhoa[i]) == 0) {
            return 1;
        }
    }
    SetColor(9);
    printf("\n\t\t\t╔════════════════════════════════════════════════╗\n");
    printf("\t\t\t║    MA KHOA KHONG HOP LE. VUI LONG NHAP LAI!    ║\n");
    printf("\t\t\t╚════════════════════════════════════════════════╝\n\n");
    return 0;
}

int KiemTraNamHocHopLe(const char* namHoc) {
    int nam = atoi(namHoc);
    for (int i = 0; i < So_NHoc; i++) {
        if (Nam_Hoc[i] == nam) {
            return 1;
        }
    }
    SetColor(9);
    printf("\n\t\t\t╔════════════════════════════════════════════════╗\n");
    printf("\t\t\t║    NAM HOC KHONG HOP LE. VUI LONG NHAP LAI!    ║\n"); 
    printf("\t\t\t╚════════════════════════════════════════════════╝\n\n");
    return 0;
}

void ChuanHoaTenLop(const char *tenNhap, char *tenChuan) {
    int idx = 0;
    for (int i = 0; tenNhap[i] != '\0'; i++) {
        if (tenNhap[i] == ' ' || tenNhap[i] == '-' || tenNhap[i] == '_') continue;
        tenChuan[idx] = toupper(tenNhap[i]);
        idx++;
    }
    tenChuan[idx] = '\0';
}
    
int Khoa_Idx(const char *maKhoa){
	if (strcmp(maKhoa, "101") == 0) return 0;
    if (strcmp(maKhoa, "102") == 0) return 1;
    if (strcmp(maKhoa, "104") == 0) return 2;
    if (strcmp(maKhoa, "105") == 0) return 3;
    if (strcmp(maKhoa, "106") == 0) return 4;
    if (strcmp(maKhoa, "107") == 0) return 5;
    if (strcmp(maKhoa, "117") == 0) return 6;
    if (strcmp(maKhoa, "118") == 0) return 7;
    if (strcmp(maKhoa, "121") == 0) return 8;
    return -1;
}

int TaoLop(SinhVien *sv, LopHoc ds_Lop[][MAX_KHOA][MAX_LOP]) {
    int namHoc = atoi(sv->KhoaHoc);
    int Nam_idx = -1;
 
    for(int i = 0; i < So_NHoc; i++) {
        if(Nam_Hoc[i] == namHoc) { 
            Nam_idx = i;
            break;
        }
    }
    
    if(Nam_idx == -1) {
        strcpy(sv->Lop, "KXD"); 
        return 0;
    }
    
    int Khoa_idx = Khoa_Idx(sv->MaKhoa);
    
    for (int i = 0; i < MAX_LOP; i++) {
        if (ds_Lop[Nam_idx][Khoa_idx][i].soLuongSV < MAX_SV) {
            if(strcmp(sv->MaKhoa, "101") == 0) {  
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopCoKhi[i]);
            }
            else if(strcmp(sv->MaKhoa, "102") == 0) {  
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopCNTT[i]);
            }
            else if(strcmp(sv->MaKhoa, "104") == 0) {
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopNDL[i]);
            }
            else if(strcmp(sv->MaKhoa, "105") == 0) {
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopDien[i]);
            }
            else if(strcmp(sv->MaKhoa, "106") == 0) {
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopDTVT[i]);  
            }
            else if(strcmp(sv->MaKhoa, "107") == 0) {
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopHoa[i]);  
            }
            else if(strcmp(sv->MaKhoa, "117") == 0) {
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopMT[i]);
            }
            else if(strcmp(sv->MaKhoa, "118") == 0) {
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopQLDA[i]);
            }
            else if(strcmp(sv->MaKhoa, "121") == 0) {
                sprintf(sv->Lop, "%02d%s", namHoc % 100, lopKT[i]);
            }
            else {
                sprintf(sv->Lop, "%02dKXD", namHoc % 100);
                return 0; 
            }
            
            ds_Lop[Nam_idx][Khoa_idx][i].ds_SV[ds_Lop[Nam_idx][Khoa_idx][i].soLuongSV] = *sv;
            ds_Lop[Nam_idx][Khoa_idx][i].soLuongSV++;
            strcpy(ds_Lop[Nam_idx][Khoa_idx][i].TenLop, sv->Lop);
            return 1;
        }
    }
    SetColor(9);
    printf("\n\n\t\t\t\t\t\t╔══════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t   Tat ca cac lop cho khoa %d da day. Khong the them sinh vien.\n", namHoc);
    printf("\t\t\t\t\t\t╚══════════════════════════════════════════════════════════════════════╝\n");
    strcpy(sv->Lop, "KXD");
    return 0; 
}

void ThemSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP]) {
	
    char another = 'y';
    
    while (another == 'y' || another == 'Y') {
        system("cls");

        SetColor(13);
        printf("\t\t\t\t\t\t╔══════════════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t\t║                THEM SINH VIEN MOI                ║\n");
        printf("\t\t\t\t\t\t╚══════════════════════════════════════════════════╝\n\n");
        
        SetColor(14);

        SinhVien sv;

        SetColor(11);
        printf("\t\t\t[→] Nhap thong tin sinh vien:\n\n");
        
        SetColor(14);
        printf("\t\t\tHo va ten lot: ");
        fgets(sv.HoLot, sizeof(sv.HoLot), stdin);
        XoaXuongDong(sv.HoLot);

        printf("\t\t\tTen: ");
        fgets(sv.Ten, sizeof(sv.Ten), stdin);
        XoaXuongDong(sv.Ten);

        printf("\t\t\tGioi tinh: ");
        fgets(sv.GioiTinh, sizeof(sv.GioiTinh), stdin);
        XoaXuongDong(sv.GioiTinh);

        printf("\t\t\tNgay sinh (dd/mm/yyyy): ");
        fgets(sv.NgaySinh, sizeof(sv.NgaySinh), stdin);
        XoaXuongDong(sv.NgaySinh);

        printf("\t\t\tDia chi: ");
        fgets(sv.DiaChi, sizeof(sv.DiaChi), stdin);
        XoaXuongDong(sv.DiaChi);
 
        do{
        	SetColor(6);
            printf("\t\t\t╔═════════════════════════════════════╗\n");
            printf("\t\t\t║         THONG TIN MA KHOA           ║\n");
            printf("\t\t\t╠─────────────────────────────────────╣\n");
            printf("\t\t\t║ MA KHOA  │     TEN KHOA             ║\n");
            printf("\t\t\t╠─────────────────────────────────────╣\n");
            printf("\t\t\t║   101    │ CO KHI                   ║\n");
            printf("\t\t\t║   102    │ CONG NGHE THONG TIN      ║\n");
            printf("\t\t\t║   104    │ NGHIET - DIEN LANH       ║\n");
            printf("\t\t\t║   105    │ DIEN                     ║\n");
            printf("\t\t\t║   106    │ DIEN TU - VIEN THONG     ║\n");
            printf("\t\t\t║   107    │ HOA                      ║\n");
            printf("\t\t\t║   117    │ MOI TRUONG               ║\n");
            printf("\t\t\t║   118    │ QUAN LI DU AN            ║\n");
            printf("\t\t\t║   121    │ KIEN TRUC                ║\n");
            printf("\t\t\t╚═════════════════════════════════════╝\n");

            SetColor(14);
            printf("\n\t\t\tMa khoa: ");
            fgets(sv.MaKhoa, sizeof(sv.MaKhoa), stdin);
            XoaXuongDong(sv.MaKhoa);
        }while(!KiemTraMaKhoaHopLe(sv.MaKhoa));

        PhanLoaiKhoa(&sv);
        
        do {
        	SetColor(14);
        	getchar();
            printf("\n\t\t\tKhoa hoc (VD: 2024): ");
            fgets(sv.KhoaHoc, sizeof(sv.KhoaHoc), stdin);
            XoaXuongDong(sv.KhoaHoc);
        } while(!KiemTraNamHocHopLe(sv.KhoaHoc));
        
        sv.check1 = 0;
        sv.check2 = 0;
        strcpy(sv.MSSV, "");
        strcpy(sv.email, "");

        if (!TaoLop(&sv, dsLop)) {
        	printf("\n\n\t\t\t\t\t╔════════════════════════════════╗\n");
            printf("\t\t\t\t\t║    KHONG THE THEM SINH VIEN    ║\n");
            printf("\t\t\t\t\t╚════════════════════════════════╝\n");
        } 
		else {
			SetColor(9);
			printf("\t\t\t╔══════════════════════════════════════════════════╗\n");
            printf("\t\t\t   DA THEM SINH VIEN THANH CONG VAO LOP %s!     \n", sv.Lop);
            printf("\t\t\t╚══════════════════════════════════════════════════╝\n");
        }

        SetColor(11);
        printf("\n\t\t\tBan co muon nhap them sinh vien khac? (y/n): ");
        scanf(" %c", &another);
        getchar(); 
    }
}

void ThemSinhVienTuFile(LopHoc dsLop[][MAX_KHOA][MAX_LOP]) {
	system("cls");
	SetColor(13);
    printf("\t\t\t\t\t\t╔══════════════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║          THEM SINH VIEN MOI TU FILE              ║\n");
    printf("\t\t\t\t\t\t╚══════════════════════════════════════════════════╝\n\n");
    char tenFile[100];
    SetColor(14);
    printf("\n\t\t[→] Nhap ten file can doc: ");
    scanf("%s", tenFile);
    getchar();

    FILE *f = fopen(tenFile, "r");
    if (!f) {
    	SetColor(9);
    	printf("\n\n\t\t\t\t\t╔════════════════════════════════╗\n");
        printf("\t\t\t\t\t║       KHONG THE MO FILE!       ║\n");
        printf("\t\t\t\t\t╚════════════════════════════════╝\n");
        SetColor(0);
        system("pause");
        return;
    }

    int soLuongSVMoi = 0;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        SinhVien sv;
        char *token = strtok(line, "|");
        if (!token) continue; strcpy(sv.HoLot, token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(sv.Ten, token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(sv.GioiTinh, token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(sv.NgaySinh, token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(sv.DiaChi, token);

        token = strtok(NULL, "|");
        if (!token || !KiemTraMaKhoaHopLe(token)) continue;
        strcpy(sv.MaKhoa, token);
        PhanLoaiKhoa(&sv);

        token = strtok(NULL, "|");
        if (!token || !KiemTraNamHocHopLe(token)) continue;
        strcpy(sv.KhoaHoc, token);
        XoaXuongDong(sv.KhoaHoc);

        sv.check1 = 0;
        sv.check2 = 0;
        strcpy(sv.MSSV, "");
        strcpy(sv.email, "");
        sv.stt = 0;

        if (!TaoLop(&sv, dsLop)) {
        	SetColor(9);
            printf("Khong the them sinh vien: %s %s\n", sv.HoLot, sv.Ten);
            SetColor(0);
            system("pause");
        } else {
        	soLuongSVMoi++; //dem so luong sinh vien moi duoc them vao
        }
    }
    if(soLuongSVMoi > 0){
    	SetColor(9);
        printf("\n\n\t\t\t\t╔══════════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t\t   DA THEM %d SINH VIEN TU FILE VAO CAC LOP THANH CONG!        \n", soLuongSVMoi);
        printf("\t\t\t\t╚══════════════════════════════════════════════════════════════╝\n\n");
	}
    fclose(f);
    SetColor(0);
    system("pause");
}


LopHoc* ChonLopTheoNamVaKhoa(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    int namHoc;
    char maKhoa[4];
    SetColor(14);
    printf("\t\t\t\tNhap nam hoc: ");
    scanf("%d", &namHoc);
    getchar();

    SetColor(6);
    printf("\t\t\t\t\t\t╔═════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║         THONG TIN MA KHOA           ║\n");
    printf("\t\t\t\t\t\t╠─────────────────────────────────────╣\n");
    printf("\t\t\t\t\t\t║ MA KHOA  │     TEN KHOA             ║\n");
    printf("\t\t\t\t\t\t╠─────────────────────────────────────╣\n");
    printf("\t\t\t\t\t\t║   101    │ CO KHI                   ║\n");
    printf("\t\t\t\t\t\t║   102    │ CONG NGHE THONG TIN      ║\n");
    printf("\t\t\t\t\t\t║   104    │ NGHIET - DIEN LANH       ║\n");
    printf("\t\t\t\t\t\t║   105    │ DIEN                     ║\n");
    printf("\t\t\t\t\t\t║   106    │ DIEN TU - VIEN THONG     ║\n");
    printf("\t\t\t\t\t\t║   107    │ HOA                      ║\n");
    printf("\t\t\t\t\t\t║   117    │ MOI TRUONG               ║\n");
    printf("\t\t\t\t\t\t║   118    │ QUAN LI DU AN            ║\n");
    printf("\t\t\t\t\t\t║   121    │ KIEN TRUC                ║\n");
    printf("\t\t\t\t\t\t╚═════════════════════════════════════╝\n");
    SetColor(14);
    printf("\n\t\t\t\tNhap ma khoa: ");
    fgets(maKhoa, sizeof(maKhoa), stdin);
    XoaXuongDong(maKhoa);

    int namIdx = -1;
    for (int i = 0; i < soLuongNam; i++) {
        if (Nam_Hoc[i] == namHoc) {
            namIdx = i;
            break;
        }
    }

    int khoaIdx = Khoa_Idx(maKhoa);

    if (namIdx == -1 || khoaIdx == -1) {
    	printf("\n\n\t\t\t\t\t╔═════════════════════════════════════╗\n");
        printf("\t\t\t\t\t║  NAM HOC HOAC MA KHOA KHONG HOP LE! ║\n");
        printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");
        return NULL;
    }
    SetColor(11);
    printf("\n\t\t\t\t\t\t╔═════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║       --- DANH SACH CAC LOP ---     ║\n");
    printf("\t\t\t\t\t\t╚═════════════════════════════════════╝\n");
    int dem = 0;
    for (int i = 0; i < MAX_LOP; i++) {
        if (dsLop[namIdx][khoaIdx][i].soLuongSV > 0) {
        	SetColor(14);
            printf("\t\t\t\t\t\t%d. %s (%d sinh vien)\n", dem + 1, dsLop[namIdx][khoaIdx][i].TenLop, dsLop[namIdx][khoaIdx][i].soLuongSV);
            dem++;
        }
    }

    if (dem == 0) {
    	printf("\n\n\t\t\t\t\t╔══════════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t║  KHONG CO LOP NAO TRONG KHOA VA NAM HOC NAY! ║\n");
        printf("\t\t\t\t\t╚══════════════════════════════════════════════╝\n");
        return NULL;
    }

    int chon;
    printf("\t\t\t\t\t\t[→] Chon lop (1-%d): ", dem);
    scanf("%d", &chon);
    getchar();

    if (chon < 1 || chon > dem) {
    	printf("\n\n\t\t\t\t\t╔══════════════════════════════╗\n");
        printf("\t\t\t\t\t║   LUA CHON KHONG HOP LE!     ║\n");
        printf("\t\t\t\t\t╚══════════════════════════════╝\n");
        return NULL;
    }

    return &dsLop[namIdx][khoaIdx][chon - 1];
}


void SapXepSinhVien_TheoLop(LopHoc *Lop) {
	
    for(int i = 0; i < Lop->soLuongSV -1; i++) {
        for(int j = i+1; j < Lop->soLuongSV; j++) {
            int cmp = strcmp(Lop->ds_SV[i].Ten, Lop->ds_SV[j].Ten);
            if(cmp > 0 || (cmp == 0 && strcmp(Lop->ds_SV[i].HoLot, Lop->ds_SV[j].HoLot) > 0)) {
                SinhVien temp = Lop->ds_SV[i];
                Lop->ds_SV[i] = Lop->ds_SV[j];
                Lop->ds_SV[j] = temp;
            }
        }
    }
    for(int i = 0; i < Lop->soLuongSV; i++) {
        Lop->ds_SV[i].stt = i+1;
        Lop->ds_SV[i].check1 = 1;
    }
}

void SapXepSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    system("cls");
    SetColor(13); 
    printf("\t\t\t\t\t\t╔══════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║       SAP XEP SINH VIEN          ║  \n");
    printf("\t\t\t\t\t\t╚══════════════════════════════════╝\n\n");
    printf("\n");
    LopHoc *lop = ChonLopTheoNamVaKhoa(dsLop, soLuongNam);
    if (!lop){
    	SetColor(0);
    	system("pause");
    	return;
	}
    
    SapXepSinhVien_TheoLop(lop);
    
    SetColor(9);
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t╔═════════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t      DA SAP XEP LOP %s THANH CONG!             \n",lop->TenLop);
    printf("\t\t\t\t\t\t╚═════════════════════════════════════════════╝\n\n");
    SetColor(0);
    system("pause");
}

int DemSVDaCo_TheoKhoa(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam, const char *maKhoa) {
    int tong = 0;
    for (int i = 0; i < soLuongNam; i++) {
        for (int j = 0; j < MAX_KHOA; j++) {
            for (int k = 0; k < MAX_LOP; k++) {
                for (int sv = 0; sv < dsLop[i][j][k].soLuongSV; sv++) {
                    if (strcmp(dsLop[i][j][k].ds_SV[sv].MaKhoa, maKhoa) == 0 &&
                        dsLop[i][j][k].ds_SV[sv].check2 == 1) {
                        tong++;
                    }
                }
            }
        }
    }
    return tong;
}

int CapMSSV_TheoLop(LopHoc *Lop, LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    for (int i = 0; i < Lop->soLuongSV; i++) {
        if (Lop->ds_SV[i].check1 == 0) {
        	SetColor(9);
        	printf("\n\n\t\t\t\t\t\t╔════════════════════════════════════════════════════════════╗\n");
        	printf("\t\t\t\t\t\t    LOP %s CHUA DUOC SAP XEP, KHONG THE CAP MSSV!           \n", Lop->TenLop);
        	printf("\t\t\t\t\t\t╚════════════════════════════════════════════════════════════╝\n\n");
            return 0;
        }
    }

    for (int i = 0; i < Lop->soLuongSV; i++) {
        if (Lop->ds_SV[i].check2 == 0) {
            int NamHoc = atoi(Lop->ds_SV[i].KhoaHoc);
            int soLuongDaCo = DemSVDaCo_TheoKhoa(dsLop, soLuongNam, Lop->ds_SV[i].MaKhoa);
            int stt = soLuongDaCo + 1;

            sprintf(Lop->ds_SV[i].MSSV, "%s%02d%04d",
                    Lop->ds_SV[i].MaKhoa,
                    NamHoc % 100,
                    stt);

            Lop->ds_SV[i].check2 = 1;
        }
    }
    return 1;
}

void CapMSSV(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    system("cls");
    SetColor(13); 
    printf("\t\t\t\t\t\t╔══════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║    CAP MA SO SINH VIEN(MSSV)     ║  \n");
    printf("\t\t\t\t\t\t╚══════════════════════════════════╝\n\n");
    printf("\n");
    LopHoc *lop = ChonLopTheoNamVaKhoa(dsLop, soLuongNam);
    if (!lop){
    	SetColor(0);
    	system("pause");
    	return;
	}

    if(CapMSSV_TheoLop(lop, dsLop, soLuongNam)==0){
    	SetColor(0);
    	system("pause");
    	return;
	} 
    else{
        SetColor(9);
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\t╔═════════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t\t    DA CAP MSSV CHO LOP %s THANH CONG!             \n",lop->TenLop);
        printf("\t\t\t\t\t\t╚═════════════════════════════════════════════╝\n\n");
        SetColor(0);
        system("pause");
    }
}

int CapEmail_TheoLop(LopHoc *Lop) {
    for (int i = 0; i < Lop->soLuongSV; i++) {
        if (Lop->ds_SV[i].check2 == 0) {
            SetColor(9);
            printf("\n\n\t\t\t\t\t\t╔═════════════════════════════════════════════════════════════════════════╗\n");
            printf("\t\t\t\t\t\t     SINH VIEN TRONG LOP %s CHUA DUOC CAP MSSV. KHONG THE CAP EMAIL!   \n", Lop->TenLop);
            printf("\t\t\t\t\t\t╚═════════════════════════════════════════════════════════════════════════╝\n\n");
            return 0;
        }
    }

    for (int i = 0; i < Lop->soLuongSV; i++) {
        if (strcmp(Lop->ds_SV[i].KhoaHoc, "2024") == 0)
            sprintf(Lop->ds_SV[i].email, "%s@sv1.dut.udn.vn", Lop->ds_SV[i].MSSV);
        else if (strcmp(Lop->ds_SV[i].KhoaHoc, "2023") == 0)
            sprintf(Lop->ds_SV[i].email, "%s@sv2.dut.udn.vn", Lop->ds_SV[i].MSSV);
        else if (strcmp(Lop->ds_SV[i].KhoaHoc, "2022") == 0)
            sprintf(Lop->ds_SV[i].email, "%s@sv3.dut.udn.vn", Lop->ds_SV[i].MSSV);
        else if (strcmp(Lop->ds_SV[i].KhoaHoc, "2021") == 0)
            sprintf(Lop->ds_SV[i].email, "%s@sv4.dut.udn.vn", Lop->ds_SV[i].MSSV);
        else if (strcmp(Lop->ds_SV[i].KhoaHoc, "2020") == 0)
            sprintf(Lop->ds_SV[i].email, "%s@sv5.dut.udn.vn", Lop->ds_SV[i].MSSV);
        else
            sprintf(Lop->ds_SV[i].email, "%s@sv.dut.udn.vn", Lop->ds_SV[i].MSSV);
    }

    return 1;
}


void CapEmail(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    system("cls");
    SetColor(13); 
    printf("\t\t\t\t\t\t╔═════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║          CAP EMAIL          ║  \n");
    printf("\t\t\t\t\t\t╚═════════════════════════════╝\n\n");
    printf("\n");
    LopHoc *lop = ChonLopTheoNamVaKhoa(dsLop, soLuongNam);
    if (!lop){
    	SetColor(0);
    	system("pause");
    	return;
	}

    if(CapEmail_TheoLop(lop)==0){
    	SetColor(0);
    	system("pause");
    	return;
	}
	else{
        SetColor(9);
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\t╔═════════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t\t      DA CAP EMAIL LOP %s THANH CONG!             \n",lop->TenLop);
        printf("\t\t\t\t\t\t╚═════════════════════════════════════════════╝\n\n");
        SetColor(0);
        system("pause");
    }
}

void TimKiemSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam){
	
	system("cls");
	
	char MSSV_TimKiem[20];
	SetColor(13);
	printf("\t\t\t\t\t\t╔═════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║           TIM KIEM SINH VIEN            ║\n");
    printf("\t\t\t\t\t\t╚═════════════════════════════════════════╝\n\n");
	SetColor(14);
	printf("\t[→] Nhap MSSV cua sinh vien can tim:");
	scanf("%s",MSSV_TimKiem);
	getchar();
	
	int found = 0;
	
	for( int i = 0; i < soLuongNam; i++){
		for(int j = 0; j < MAX_KHOA; j++){
			for(int k = 0; k < MAX_LOP; k++){
				for(int m = 0; m < dsLop[i][j][k].soLuongSV; m++){
				    if(strcmp(dsLop[i][j][k].ds_SV[m].MSSV, MSSV_TimKiem) == 0){
			            found = 1;
			            SetColor(11);
			            printf("\t\t\t\t\t\t╔═══════════════════════════════════╗\n");
                        printf("\t\t\t\t\t\t║       SINH VIEN CAN TIM           ║\n");
                        printf("\t\t\t\t\t\t╚═══════════════════════════════════╝\n\n");  
                        SetColor(14);
                        printf("  ╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
			            printf("    MSSV       │    Ho va ten               │ Gioi tinh│ Ngay sinh    │ Dia chi         │ Email\n");
                        printf("  ╠────────────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n"); 
                        printf("    %-10s │ %-18s %-6s  │ %-8s │ %-12s │ %-15s │ %s\n", 
                            dsLop[i][j][k].ds_SV[m].MSSV, 
                            dsLop[i][j][k].ds_SV[m].HoLot, 
                            dsLop[i][j][k].ds_SV[m].Ten,
                            dsLop[i][j][k].ds_SV[m].GioiTinh, 
                            dsLop[i][j][k].ds_SV[m].NgaySinh, 
                            dsLop[i][j][k].ds_SV[m].DiaChi, 
                            dsLop[i][j][k].ds_SV[m].email);
                        printf("  ╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
                
                        SetColor(0);
                        system("pause");
                        break;
                    }
                }
            }
		}		
	}
	
	if(found == 0){
		printf("\n\n\t\t\t\t\t\t╔════════════════════════════════════════════════╗\n");
		printf("\t\t\t\t\t\t    KHONG TIM THAY SINH VIEN CO MSSV %s! \n",MSSV_TimKiem);
		printf("\t\t\t\t\t\t╚═════════════════════════════════════════════════╝\n\n");
		SetColor(0);
		system("pause");
	}
}

void SuaThongTinSinhVien(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    system("cls");

    char tenLop[20], tenLopChuan[20], tenLopDSChuan[20];
    char hoLot[30], ten[15];
    int found = 0;

    SetColor(13);
    printf("\t\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t\t║        SUA THONG TIN SINH VIEN         ║\n");
    printf("\t\t\t\t╚════════════════════════════════════════╝\n\n");

    SetColor(14);
    printf("\nSinh vien can sua thong tin:\n");
    printf("\n\t\t\tTen lop: ");
    fgets(tenLop, sizeof(tenLop), stdin);
    XoaXuongDong(tenLop);
    ChuanHoaTenLop(tenLop, tenLopChuan); // chuan hoa ten lop nhap vao

    printf("\n\t\t\tHo va ten lot: ");
    fgets(hoLot, sizeof(hoLot), stdin);
    XoaXuongDong(hoLot);

    printf("\t\t\tTen: ");
    fgets(ten, sizeof(ten), stdin);
    XoaXuongDong(ten);

    for (int i = 0; i < soLuongNam; i++) {
        for (int j = 0; j < MAX_KHOA; j++) {
            for (int k = 0; k < MAX_LOP; k++) {
                LopHoc *lop = &dsLop[i][j][k];
                if (lop->soLuongSV > 0) {
                    ChuanHoaTenLop(lop->TenLop, tenLopDSChuan); // chuan hoa ten lop trong dsLop
                    if (strcmp(tenLopChuan, tenLopDSChuan) == 0) {
                        for (int m = 0; m < lop->soLuongSV; m++) {
                            SinhVien *sv = &lop->ds_SV[m];
                            if (strcmp(sv->HoLot, hoLot) == 0 && strcmp(sv->Ten, ten) == 0) {
                            	printf("\t\t╔═══════════════════════════════════════════════════════════════════════╗\n");
			                    printf("\t\t       Ho va ten           │ Gioi tinh│ Ngay sinh    │ Dia chi   \n");
                                printf("\t\t╠───────────────────────────────────────────────────────────────────────╣\n");
                                printf("\t\t      %s %-6s    │ %-8s │ %-12s │ %-15s \n", 
                                    dsLop[i][j][k].ds_SV[m].HoLot, 
                                    dsLop[i][j][k].ds_SV[m].Ten,
                                    dsLop[i][j][k].ds_SV[m].GioiTinh, 
                                    dsLop[i][j][k].ds_SV[m].NgaySinh, 
                                    dsLop[i][j][k].ds_SV[m].DiaChi); 
                                printf("\t\t╚═══════════════════════════════════════════════════════════════════════╝\n");    
                                found = 1;
                                if (sv->check2 == 1) {
                                    SetColor(9);
                                    printf("\n\n\t\t\t\t╔════════════════════════════════════════════════════╗\n");
                                    printf("\t\t\t\t║     SINH VIEN DA DUOC CAP MSSV KHONG DUOC SUA!     ║\n");
                                    printf("\t\t\t\t╚════════════════════════════════════════════════════╝\n");
                                } else {
                                    SetColor(11);
                                    printf("\n\t\t\t[→] NHAP THONG TIN MOI:\n");

                                    printf("\n\t\t\tHo va ten lot: ");
                                    fgets(sv->HoLot, sizeof(sv->HoLot), stdin);
                                    XoaXuongDong(sv->HoLot);

                                    printf("\t\t\tTen: ");
                                    fgets(sv->Ten, sizeof(sv->Ten), stdin);
                                    XoaXuongDong(sv->Ten);

                                    printf("\t\t\tGioi tinh: ");
                                    fgets(sv->GioiTinh, sizeof(sv->GioiTinh), stdin);
                                    XoaXuongDong(sv->GioiTinh);

                                    printf("\t\t\tNgay sinh (dd/mm/yyyy): ");
                                    fgets(sv->NgaySinh, sizeof(sv->NgaySinh), stdin);
                                    XoaXuongDong(sv->NgaySinh);

                                    printf("\t\t\tDia chi: ");
                                    fgets(sv->DiaChi, sizeof(sv->DiaChi), stdin);
                                    XoaXuongDong(sv->DiaChi);

                                    SetColor(10);
                                    printf("\n\n\t\t\t\t╔════════════════════════════════════════════╗\n");
                                    printf("\t\t\t\t║     DA CAP NHAT THONG TIN THANH CONG!      ║\n");
                                    printf("\t\t\t\t╚════════════════════════════════════════════╝\n");
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if (!found) {
        SetColor(9);
        printf("\n\t\t\t╔════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║   KHONG TIM THAY SINH VIEN TRONG LOP %s!        ║\n", tenLop);
        printf("\t\t\t╚════════════════════════════════════════════════════╝\n");
    }

    SetColor(0);
    system("pause");
}



void XuatDanhSachSV_TheoLop(LopHoc Lop) {
	
	SetColor(11);
	printf("\t\t\t\t\t\t╔═══════════════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t        ██████ DANH SACH LOP %s ██████           \n",  Lop.TenLop);
    printf("\t\t\t\t\t\t╚═══════════════════════════════════════════════════╝\n");
    SetColor(14);
    printf("\t\t  ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    SetColor(6);
    printf("\t\t    STT  │ MSSV       │    Ho va ten               │ Gioi tinh│ Ngay sinh    │ Dia chi            │ Email\n");
    SetColor(14);
    printf("\t\t  ╠──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
    
    for (int i = 0; i < Lop.soLuongSV; i++) {
        printf("\t\t     %-3d │ %-10s │ %-18s %-6s  │ %-8s │ %-12s │ %-18s │ %s\n", 
                Lop.ds_SV[i].stt, 
                Lop.ds_SV[i].MSSV, 
                Lop.ds_SV[i].HoLot, 
                Lop.ds_SV[i].Ten,
                Lop.ds_SV[i].GioiTinh, 
                Lop.ds_SV[i].NgaySinh, 
                Lop.ds_SV[i].DiaChi, 
                Lop.ds_SV[i].email);
    printf("\t\t  ╠──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");    
    };
}

void XuatLopTheoYeuCau(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    system("cls");

    int coDuLieu = 0;
    for (int i = 0; i < soLuongNam; i++) {
        for (int j = 0; j < MAX_KHOA; j++) {
            for (int k = 0; k < MAX_LOP; k++) {
                if (dsLop[i][j][k].soLuongSV > 0) {
                    coDuLieu = 1;
                    break;
                }
            }
        }
    }

    if (!coDuLieu) {
        SetColor(9);
        printf("\n\n\t\t\t\t\t\t╔════════════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t\t║     KHONG CO DU LIEU SINH VIEN DE HIEN THI!    ║ \n");
        printf("\t\t\t\t\t\t╚════════════════════════════════════════════════╝\n");
        SetColor(0);
        system("pause");
        return;
    }

    SetColor(13);
    printf("\n\n\t\t\t\t\t\t╔════════════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║        XUAT DANH SACH SINH VIEN TUNG LOP       ║\n");
    printf("\t\t\t\t\t\t╚════════════════════════════════════════════════╝\n");

    char tenLopNhap[20];
    SetColor(14);
    printf("\t\t\tNhap ten lop: ");
    fgets(tenLopNhap, sizeof(tenLopNhap), stdin);
    XoaXuongDong(tenLopNhap);

    char tenLopChuan[20];
    ChuanHoaTenLop(tenLopNhap, tenLopChuan);

    int found = 0;
    for (int i = 0; i < soLuongNam; i++) {
        for (int j = 0; j < MAX_KHOA; j++) {
            for (int k = 0; k < MAX_LOP; k++) {
                if (dsLop[i][j][k].soLuongSV > 0) {
                    char tenLopDS[20];
                    ChuanHoaTenLop(dsLop[i][j][k].TenLop, tenLopDS);

                    if (strcmp(tenLopChuan, tenLopDS) == 0) {
                        system("cls");
                        SetColor(13);
                        printf("\n\n\t\t\t\t\t\tTRUONG DAI HOC BACH KHOA - DAI HOC DA NANG\n");
                        printf("\t\t\t\t\t\tKHOA: %s\n", dsLop[i][j][k].ds_SV[0].TenKhoa);
                        printf("\t\t\t\t\t\tDANH SACH LOP %s - Khoa hoc %s\n\n", dsLop[i][j][k].TenLop, dsLop[i][j][k].ds_SV[0].KhoaHoc);
                        XuatDanhSachSV_TheoLop(dsLop[i][j][k]);
                        found = 1;
                        break;
                    }
                }
            }
        }
    }

    if (!found) {
        SetColor(9);
        printf("\n\n\t\t\t\t\t\t╔═════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t\t     KHONG TIM THAY LOP %s!                  \n", tenLopNhap);
        printf("\t\t\t\t\t\t╚═════════════════════════════════════════╝\n");
    }

    SetColor(0);
    system("pause");
}


void XuatDanhSachSV_ToanTruong(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
	
    system("cls");
    SetColor(12);
    printf("\n\t\t\t\t\t╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t║     ██████  TRUONG DAI HOC BACH KHOA - DAI HOC DA NANG  ██████    ║ \n");
    printf("\t\t\t\t\t║                          DANH SACH SINH VIEN                      ║ \n");
    printf("\t\t\t\t\t╚═══════════════════════════════════════════════════════════════════╝\n\n");
    
    int coDuLieu = 0;
    for(int i = 0; i < soLuongNam; i++) {
        for(int j = 0; j < MAX_KHOA; j++) {
        	for(int k = 0; k < MAX_LOP; k++){
                if(dsLop[i][j][k].soLuongSV > 0) {
                    XuatDanhSachSV_TheoLop(dsLop[i][j][k]);
                    printf("\n");
                    coDuLieu = 1;
                }
            }
        }
    }
    
    if(!coDuLieu) {
    	SetColor(9);
    	printf("\n\n\t\t\t\t\t╔══════════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t║   KHONG CO DU LIEU SINH VIEN DE HIEN THI!    ║\n");
        printf("\t\t\t\t\t╚══════════════════════════════════════════════╝\n");
    }
    SetColor(0);
    system("pause");
}

void XoaSinhVien_KhoiLop(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int *soLuongNam) {
	
    system("cls");
    
    int coDuLieu = 0;
    for(int i = 0; i < *soLuongNam; i++) {
        for(int j = 0; j < MAX_KHOA; j++) {
        	for(int k = 0; k < MAX_LOP; k++){
                if(dsLop[i][j][k].soLuongSV > 0) {
                    coDuLieu = 1;
                    break;
                }
            }
        }
    }
    
    if(!coDuLieu) {
    	SetColor(9);
    	printf("\n\n\t\t\t\t\t╔═════════════════════════╗\n");
        printf("\t\t\t\t\t║  DANH SACH LOP TRONG!   ║\n");
        printf("\t\t\t\t\t╚═════════════════════════╝\n");
        
        SetColor(0);
        system("pause");
        return;
    }
    
    char MSSV_Delete[20];

    SetColor(13);
    printf("\t\t\t\t\t╔════════════════════════════════╗\n");
    printf("\t\t\t\t\t║          XOA SINH VIEN         ║ \n");
    printf("\t\t\t\t\t╚════════════════════════════════╝\n");
    SetColor(14);
    printf("Nhap MSSV can xoa: ");
    scanf("%s", MSSV_Delete);
    getchar();

    int found = 0;
    int lop_i = -1, lop_j = -1, lop_k = -1, sv_idx = -1;
        
    for(int i = 0; i < *soLuongNam; i++) {
           for(int j = 0; j < MAX_KHOA; j++) {
            for(int k = 0; k < MAX_LOP; k++){
                for(int m = 0; m < dsLop[i][j][k].soLuongSV; m++) {
                    if(strcmp(dsLop[i][j][k].ds_SV[m].MSSV, MSSV_Delete) == 0) {
                        lop_i = i;
                        lop_j = j;
                        lop_k = k;
                        sv_idx = m;
                        found = 1;
                        break;
                    }
                }
            }
            if(found) break;
        }
        if(found) break;
    }
        
    if(!found) {
        printf("\n\n\t\t\t\t\t╔════════════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t   KHONG TIM THAY SINH VIEN CO MSSV %s  !\n", MSSV_Delete);
        printf("\t\t\t\t\t╚════════════════════════════════════════════════╝\n");
    }
    else {
        SinhVien sv = dsLop[lop_i][lop_j][lop_k].ds_SV[sv_idx];
        SetColor(11);
        printf("\n\n\t\t\t\t\t╔═══════════════════════════════════╗\n");
        printf("\t\t\t\t\t║   THONG TIN SINH VIEN TIM DUOC    ║\n");
        printf("\t\t\t\t\t╚═══════════════════════════════════╝\n");
        SetColor(14);
        printf("  ╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
		printf("    MSSV       │    Ho va ten               │ Gioi tinh│ Ngay sinh    │ Dia chi            │ Email\n");
        printf("  ╠────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╣\n");
        printf("    %-10s │ %-18s %-6s  │ %-8s │ %-12s │ %-18s │ %s\n", 
                    sv.MSSV, 
                    sv.HoLot, 
                    sv.Ten,
                    sv.GioiTinh, 
                    sv.NgaySinh, 
                    sv.DiaChi, 
                    sv.email);
        printf("  ╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");

        char xacNhan;
        SetColor(11);
        printf("\nBan co chac muon xoa sinh vien nay? (y/n): ");
        scanf(" %c", &xacNhan);
        getchar();

        if (xacNhan == 'y' || xacNhan == 'Y') {
            for (int m = sv_idx; m < dsLop[lop_i][lop_j][lop_k].soLuongSV - 1; m++) {
                dsLop[lop_i][lop_j][lop_k].ds_SV[m] = dsLop[lop_i][lop_j][lop_k].ds_SV[m + 1];
            }
            dsLop[lop_i][lop_j][lop_k].soLuongSV--;

            for (int m = 0; m < dsLop[lop_i][lop_j][lop_k].soLuongSV; m++) {
                dsLop[lop_i][lop_j][lop_k].ds_SV[m].stt = m + 1;
            }

            SetColor(10);
            printf("\n\t\t\t\t\t╔══════════════════════════════════════════════════════════╗\n");
            printf("\t\t\t\t\t    DA XOA SINH VIEN CO MSSV %s KHOI LOP %s!         \n", sv.MSSV, dsLop[lop_i][lop_j][lop_k].TenLop);
            printf("\t\t\t\t\t╚══════════════════════════════════════════════════════════╝\n");
        } else {
        	SetColor(10);
        	printf("\n\n\t\t\t\t\t╔═══════════════════════════╗\n");
            printf("\t\t\t\t\t║   HUY BO XOA SINH VIEN    ║ \n");
            printf("\t\t\t\t\t╚═══════════════════════════╝\n");
        }
    }
    SetColor(0);
    system("pause"); 
}

void LuuFileNhiPhan(const char *tenFile, LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
    FILE *f = fopen(tenFile, "wb");
    if (!f) {
        return;
    }


    fwrite(&soLuongNam, sizeof(int), 1, f);
    int soLopMoiNam = MAX_KHOA * MAX_LOP;
    fwrite(&soLopMoiNam, sizeof(int), 1, f);

    for (int i = 0; i < soLuongNam; i++) {
        for (int j = 0; j < MAX_KHOA; j++) {
        	for(int k = 0; k < MAX_LOP; k++){
                fwrite(&dsLop[i][j][k], sizeof(LopHoc), 1, f);
            }
        }
    }

    fclose(f);
}

int DocFileNhiPhan(const char *tenFile, LopHoc dsLop[][MAX_KHOA][MAX_LOP], int *soLuongNam) {
    FILE *f = fopen(tenFile, "rb");
    if (!f) {
        return 0;
    }

    int soLopMoiNam;
    fread(soLuongNam, sizeof(int), 1, f);
    fread(&soLopMoiNam, sizeof(int), 1, f);

    if (soLopMoiNam != MAX_KHOA * MAX_LOP) {
        fclose(f);
        return 0;
    }

    for (int i = 0; i < *soLuongNam; i++) {
        for (int j = 0; j < MAX_KHOA; j++) {
            for (int k = 0; k < MAX_LOP; k++) {
                fread(&dsLop[i][j][k], sizeof(LopHoc), 1, f);
            }
        }
    }

    fclose(f);
    return 1;
}




void LuuFileTheoLop(LopHoc dsLop[][MAX_KHOA][MAX_LOP], int soLuongNam) {
	
    system("cls");
    
    int coDuLieu = 0;
    for(int i = 0; i < soLuongNam; i++) {
        for(int j = 0; j < MAX_KHOA; j++) {
        	for(int k = 0; k < MAX_LOP; k++){
                if(dsLop[i][j][k].soLuongSV > 0) {
                    coDuLieu = 1;
                    break;
                }
            }
        }
    }
    
    if(!coDuLieu) {
        return;
    }
    
    for(int i = 0; i < soLuongNam; i++) {
        for(int j = 0; j < MAX_KHOA; j++) {
        	for(int k = 0; k < MAX_LOP; k++){
                if(dsLop[i][j][k].soLuongSV > 0) {
                    char tenFile[50];
                    sprintf(tenFile, "%s.txt", dsLop[i][j][k].TenLop);
                
                    FILE *f = fopen(tenFile, "w");
                    if(!f) {
                        continue;
                    }
                    fprintf(f,"\n\t\t\t\tTRUONG DAI HOC BACH KHOA - DAI HOC DA NANG\n");
                    fprintf(f,"\t\t\t\tKHOA: %s\n", dsLop[i][j][k].ds_SV[0].TenKhoa);
                    fprintf(f,"\t\t\t\tDANH SACH LOP %s - Khoa hoc %s\n\n", dsLop[i][j][k].TenLop, dsLop[i][j][k].ds_SV[0].KhoaHoc);
                
                    fprintf(f, "\t\t\t\t\t\tDANH SACH LOP %s\n", dsLop[i][j][k].TenLop);
                    fprintf(f, "STT  | MSSV       |    Ho va ten               | Gioi tinh| Ngay sinh    | Dia chi            | Email\n");
                    fprintf(f, "---------------------------------------------------------------------------------------------------------------------\n");
                
                    for(int m = 0; m < dsLop[i][j][k].soLuongSV; m++) {
                        fprintf(f, " %-3d | %-10s | %-18s %-6s  | %-8s | %-12s | %-18s | %s\n", 
                            dsLop[i][j][k].ds_SV[m].stt, 
                            dsLop[i][j][k].ds_SV[m].MSSV, 
                            dsLop[i][j][k].ds_SV[m].HoLot, 
                            dsLop[i][j][k].ds_SV[m].Ten,
                            dsLop[i][j][k].ds_SV[m].GioiTinh, 
                            dsLop[i][j][k].ds_SV[m].NgaySinh, 
                            dsLop[i][j][k].ds_SV[m].DiaChi, 
                            dsLop[i][j][k].ds_SV[m].email);
                    }
                
                    fclose(f);
                }
            }
        }
    }
}


void XuatFile_TXT() {
    system("cls");
    char tenFile[256];
    FILE *f = NULL;

    SetColor(13);
    printf("\n\n\t\t\t\t\t╔═════════════════════════════════╗\n");
    printf("\t\t\t\t\t║      XUAT LOP THEO FILE TXT     ║\n");
    printf("\t\t\t\t\t╚═════════════════════════════════╝\n\n");

    while (1) {
        SetColor(14);
        printf("\t\t\t Nhap ten file can mo: ");
        scanf("%s", tenFile);

        char tenFileGoc[256];
        strcpy(tenFileGoc, tenFile);
        char *dot = strrchr(tenFileGoc, '.');
        if (dot && strcmp(dot, ".txt") == 0) {
            *dot = '\0'; 
        }

        char tenFileChuan[256];
        ChuanHoaTenLop(tenFileGoc, tenFileChuan);
        sprintf(tenFile, "%s.txt", tenFileChuan); 

        f = fopen(tenFile, "r");
        if (f) {
            fclose(f);
            break;
        } else {
            SetColor(9);
            printf("\n\n\t\t\t╔═════════════════════════════════════════════════════╗\n");
            printf("\t\t\t   FILE \"%s\" KHONG TON TAI. VUI LONG NHAP LAI!\n", tenFile);
            printf("\t\t\t╚═════════════════════════════════════════════════════╝\n\n");
        }
    }

    char lenh[300];
    sprintf(lenh, "start %s", tenFile);
    system(lenh);
}



void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void XinChao(){
	
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	
	SetColor(4);
	printf("\n\t\t\t\t\t   ██╗  ██╗ ██╗ ███╗   ██╗       ██████╗ ██╗  ██╗  █████╗   ██████╗  ");
    printf("\n\t\t\t\t\t   ╚██╗██╔╝ ██║ ████╗  ██║      ██╔════╝ ██║  ██║ ██╔══██╗ ██╔═══██╗ ");
    printf("\n\t\t\t\t\t    ╚███╔╝  ██║ ██╔██╗ ██║      ██║      ███████║ ███████║ ██║   ██║ ");
    printf("\n\t\t\t\t\t    ██╔██╗  ██║ ██║╚██╗██║      ██║      ██╔══██║ ██╔══██║ ██║   ██║ ");
    printf("\n\t\t\t\t\t   ██╔╝ ██╗ ██║ ██║ ╚████║      ╚██████╗ ██║  ██║ ██║  ██║ ╚██████╔╝ ");
    printf("\n\t\t\t\t\t   ╚═╝  ╚═╝ ╚═╝ ╚═╝  ╚═══╝       ╚═════╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝  ╚═════╝  \n");
    
    SetColor(0);
    system("pause");
}

void HienThiTieuDe() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    SetColor(11);
    printf("\t\t\t\t\t   ╭───────────────────────────────────────────────────────────╮\n");
    printf("\t\t\t\t\t   │                                                           │\n");
    printf("\t\t\t\t\t   │             DAI HOC BACH KHOA - DAI HOC DA NANG           │\n");
    printf("\t\t\t\t\t   │                 KHOA CONG NGHE THONG TIN                  │\n");
    printf("\t\t\t\t\t   │                                                           │\n");
    
    SetColor(12);
    printf("\t\t\t\t\t   │   ░▒▓██████████████████████████████████████████████▓▒░    │\n");
    printf("\t\t\t\t\t   │                                                           │\n");
    
    SetColor(11);
    printf("\t\t\t\t\t   │               DO AN LAP TRINH TINH TOAN                   │\n");
    printf("\t\t\t\t\t   │      DE TAI: XAY DUNG UNG DUNG QUAN LI SINH VIEN          │\n");
    printf("\t\t\t\t\t   │      SINH VIEN THUC HIEN: LE THI HIEN & HUYNH HIEU NGHIA  │\n");
    printf("\t\t\t\t\t   │      GIANG VIEN HUONG DAN: ThS.NGUYEN THI MINH HY         │\n");
    printf("\t\t\t\t\t   │      LOP: 24T_DT3            NHOM: 4                      │\n");
    
    SetColor(12);
    printf("\t\t\t\t\t   │                                                           │\n");
    printf("\t\t\t\t\t   │   ░▒▓██████████████████████████████████████████████▓▒░    │\n");
    
    SetColor(11);
    printf("\t\t\t\t\t   │                                                           │\n");
    printf("\t\t\t\t\t   │                                                           │\n");
    printf("\t\t\t\t\t   ╰───────────────────────────────────────────────────────────╯\n");
    
    SetColor(0);
    system("pause");
}

int main() {
	SetConsoleOutputCP(65001);
	LopHoc dsLop[5][MAX_KHOA][MAX_LOP];
	int soLuongNam = So_NHoc;
    if (!DocFileNhiPhan("sinhvien.dat", dsLop, &soLuongNam)) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < MAX_KHOA; j++){
                for(int k = 0; k < MAX_LOP; k++){
                    dsLop[i][j][k].soLuongSV = 0;
                    strcpy(dsLop[i][j][k].TenLop, "");
                }
            }
        }
    }
    
    SinhVien ds[MAX_SV]; 
    int soLuongSV = 0; 
    XinChao();
    
    HienThiTieuDe();
    
    int chon;
    
    do {
        system("cls");
        
        SetColor(12);
        printf("\n\t\t\t\t\t           ███╗   ███╗███████╗███╗   ██╗██╗   ██╗          ");
        printf("\n\t\t\t\t\t           ████╗ ████║██╔════╝████╗  ██║██║   ██║          ");
        printf("\n\t\t\t\t\t           ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║          ");
        printf("\n\t\t\t\t\t           ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║          ");
        printf("\n\t\t\t\t\t           ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝          ");
        printf("\n\t\t\t\t\t           ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝           ");
        
        
        SetColor(14);
        printf("\n\t\t\t\t\t  ╔══════════════════════════════════════════════════════╗");
        printf("\n\t\t\t\t\t  ║  ┌───┬────────────────────────────────────────────┐  ║");
        printf("\n\t\t\t\t\t  ║  │ 1 │ Them sinh vien moi                         │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 2 │ Them sinh vien moi tu file                 │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 3 │ Sap xep danh sach sinh vien                │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 4 │ Sua thong tin sinh vien                    │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 5 │ Cap ma so sinh vien (MSSV)                 │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 6 │ Cap Email                                  │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 7 │ Tim kiem sinh vien                         │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 8 │ Xoa sinh vien                              │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 9 │ Xuat danh sach sinh vien theo lop          │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │10 │ Xuat danh sach sinh vien toan truong       │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │11 │ Xuat file lop(.txt)                        │  ║");
        printf("\n\t\t\t\t\t  ║  ├───┼────────────────────────────────────────────┤  ║");
        printf("\n\t\t\t\t\t  ║  │ 0 │ Thoat chuong trinh                         │  ║");
        printf("\n\t\t\t\t\t  ║  └───┴────────────────────────────────────────────┘  ║");
        printf("\n\t\t\t\t\t  ╠══════════════════════════════════════════════════════╣");
        SetColor(13);
        printf("\n\t\t\t\t\t  ║  [→] Nhap lua chon: _                                ║");
        SetColor(14);
        printf("\n\t\t\t\t\t  ╚══════════════════════════════════════════════════════╝");
        printf("\033[34;65H"); 
        scanf("%d", &chon);
        getchar();

        switch (chon) {
            case 1:
                ThemSinhVien(dsLop);
                LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
                LuuFileTheoLop(dsLop, soLuongNam);
                break;
            case 2:
                ThemSinhVienTuFile(dsLop);
                LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
                LuuFileTheoLop(dsLop, soLuongNam);
                break;
            case 3:
                SapXepSinhVien(dsLop, soLuongNam);
            	LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
            	LuuFileTheoLop(dsLop, soLuongNam);
            	break;
            case 4:
            	SuaThongTinSinhVien(dsLop, soLuongNam);
                LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
                LuuFileTheoLop(dsLop, soLuongNam);
                break;
            case 5:
                CapMSSV(dsLop, soLuongNam);
                LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
                LuuFileTheoLop(dsLop, soLuongNam);
                break;
            case 6:
            	CapEmail(dsLop, soLuongNam);
                LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
                LuuFileTheoLop(dsLop, soLuongNam);
                break;
            case 7:
                TimKiemSinhVien(dsLop, soLuongNam);
            	break;;
            case 8:
                XoaSinhVien_KhoiLop(dsLop, &soLuongNam);
                LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
                LuuFileTheoLop(dsLop, soLuongNam);
                break;
            case 9:
            	XuatLopTheoYeuCau(dsLop, soLuongNam);
                break;
            case 10:
            	XuatDanhSachSV_ToanTruong(dsLop, soLuongNam);
            	break;
            case 11:
                XuatFile_TXT();
                break;
            case 0:
            	LuuFileNhiPhan("sinhvien.dat", dsLop, soLuongNam);
            	LuuFileTheoLop(dsLop, soLuongNam);
            	SetColor(11);
            	system("cls");
            	printf("\n");
            	printf("\n");
            	printf("\n");
                printf("\n\t\t\t\t\t     ██████╗  █████╗   ███╗   ███╗     ██████╗  ███╗   ██╗");
                printf("\n\t\t\t\t\t    ██╔════╝ ██╔══██╗  ████╗ ████║    ██╔═══██╗ ████╗  ██║");
                printf("\n\t\t\t\t\t    ██║      ███████║  ██╔████╔██║    ██║   ██║ ██╔██╗ ██║");
                printf("\n\t\t\t\t\t    ██║      ██╔══██║  ██║╚██╔╝██║    ██║   ██║ ██║╚██╗██║");
                printf("\n\t\t\t\t\t    ╚██████╗ ██║  ██║  ██║ ╚═╝ ██║    ╚██████╔╝ ██║ ╚████║");
                printf("\n\t\t\t\t\t     ╚═════╝ ╚═╝  ╚═╝  ╚═╝     ╚═╝     ╚═════╝  ╚═╝  ╚═══╝ ");
                printf("\n");
                printf("\n");
                printf("\n");
                printf("\n");
                SetColor(14);
                printf("\t\t\t\t\t  ╭─────────────────────────────────────────────────────╮\n");
                printf("\t\t\t\t\t  │                                                     │\n");
    
                SetColor(12);
                printf("\t\t\t\t\t  │   ░▒▓████████████████████████████████████████▓▒░    │\n");
                printf("\t\t\t\t\t  │   █                                            █    │\n");
    
                SetColor(14);
                printf("\t\t\t\t\t  │   █     CAM ON BAN DA SU DUNG CHUONG TRINH     █    │\n");
    
                SetColor(12);
                printf("\t\t\t\t\t  │   █                                            █    │\n");
                printf("\t\t\t\t\t  │   ░▒▓████████████████████████████████████████▓▒░    │\n");
    
                SetColor(14);
                printf("\t\t\t\t\t  │                                                     │\n");
                printf("\t\t\t\t\t  ╰─────────────────────────────────────────────────────╯\n");
                break;
            default:
            	SetColor(12);
                printf("Lua chon khong hop le!\n");
                SetColor(0);
                system("pause");
        }
    } while (chon != 0);
    
    SetColor(0);
    return 0;
}
