#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <map>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <windows.h>
using namespace std;

//constants
static const int MAX_SV = 50;
static const int MAX_KHOA = 9;
static const int MAX_LOP = 3;

//Khoa -> Lop
struct KhoaLookUp{
    string TenKhoa;
    array <string, 3> PostFix_Lop;
};

class SinhVien{
    //attributes
    private:
        string HoLot;
        string Ten;
        string GioiTinh;
        string NgaySinh;
        string DiaChi;
        int Stt;
        string Email;
        string MSSV;
        string MaKhoa;
        string TenKhoa;
        string Lop;
        string NamHoc;  
        bool checkSort; 
        bool checkMSSV; 
        bool checkEmail;

    public:
        SinhVien(string ho, string ten, string gioitinh, string ngaysinh, string diachi, string makhoa, string nam) :
            HoLot(ho),
            Ten(ten),
            GioiTinh(gioitinh),
            NgaySinh(ngaysinh),
            DiaChi(diachi),
            MaKhoa(makhoa),
            NamHoc(nam),
            
            Stt(0),
            Email(""),
            MSSV(""),
            TenKhoa(""), 
            Lop(""),
            checkSort(false),
            checkMSSV(false),
            checkEmail(false) {}
        
        void Assign_TenKhoa(const map<string, KhoaLookUp> &Khoa_To_Lop_Map){
            auto KhoaCode = Khoa_To_Lop_Map.find(MaKhoa);

            if (KhoaCode != Khoa_To_Lop_Map.end()){
                TenKhoa = KhoaCode->second.TenKhoa;
            }
            else{
                cout << "Ma khoa khong hop le.";
                TenKhoa = "Invalid";
            }
        }

        //setters
        void Set_checkSort(bool status) {checkSort = status;}
        void Set_MSSV(const string &newMssv){
            MSSV = newMssv;
            checkMSSV = true;
        }
        void Set_Email(const string &newEmail){
            Email = newEmail;
            checkEmail = true;
        }

        void Set_HoLot(const string& ho) { HoLot = ho; }
        void Set_Ten(const string& ten) { Ten = ten; }
        void Set_GioiTinh(const string& gt) { GioiTinh = gt; }
        void Set_NgaySinh(const string& ns) { NgaySinh = ns; }
        void Set_DiaChi(const string& dc) { DiaChi = dc; }


        //getters
        string Get_MaKhoa() const {return MaKhoa;}
        string Get_NamHoc() const {return NamHoc;}
        string Get_MSSV() const {return MSSV;}
        string Get_Ten() const {return Ten;}
        string Get_HoLot() const {return HoLot;}
        string Get_GioiTinh() const {return GioiTinh;}
        string Get_DiaChi() const {return DiaChi;}
        string Get_NgaySinh() const {return NgaySinh;}


        bool Is_Sorted() const {return checkSort;}
        bool Has_MSSV() const {return checkMSSV;}
        bool Has_Email() const {return checkEmail;}

        //printer
        void Print_SinhVien() const {
            cout << left; 
            cout << setw(5) << Stt;
            cout << setw(12) << MSSV;
            cout << setw(20) << HoLot;
            cout << setw(10) << Ten;
            cout << setw(10) << GioiTinh;
            cout << setw(15) << NgaySinh;
            cout << setw(35) << Email << endl;
        }
};

class Lop{
    //attributes
    private:
        string TenLop;
        string TenKhoa;
        string NamHoc;
        vector<SinhVien> ds_SV; 
    
    //methods
    public:
        bool Assign_MSSV_To_Lop(int StartCount){
            for (const SinhVien &sv: ds_SV){
                if (sv.Is_Sorted() == false)
                {   
                    cout << "Lop chua duoc sap xep, chua the cap MSSV.";
                    return false;
                }
            }

            for (SinhVien &sv : ds_SV){
                if (sv.Has_MSSV() == true){
                    continue;
                }
                
                StartCount++;

                string MaKhoa = sv.Get_MaKhoa();
                string NamHoc = sv.Get_NamHoc();
                string NamHoc_Formatted = NamHoc.substr(2,2);

                char FormattedCount[5];
                sprintf_s(FormattedCount, "%04d", StartCount);

                string NewMSSV = MaKhoa + NamHoc_Formatted + FormattedCount;
                sv.Set_MSSV(NewMSSV);
            }
            return true;
        }

        bool Assign_Email_To_Lop(){
            for (const SinhVien &sv: ds_SV){
                if (sv.Has_MSSV() == false)
                {   
                    cout << "Lop chua duoc cap MSSV, chua the cap Email.";
                    return false;
                }
            }

            for (SinhVien &sv : ds_SV){
                if (sv.Has_Email() == true){
                    continue;
                }

                string MSSV = sv.Get_MSSV();
                string NamHoc = sv.Get_NamHoc();

                if (NamHoc == "2025"){
                    string NewEmail = MSSV + "@sv1.dut.udn.vn";
                    sv.Set_Email(NewEmail);
                }
                else if (NamHoc == "2024"){
                    string NewEmail = MSSV + "@sv2.dut.udn.vn";
                    sv.Set_Email(NewEmail);
                }
                else if (NamHoc == "2023"){
                    string NewEmail = MSSV + "@sv3.dut.udn.vn";
                    sv.Set_Email(NewEmail);
                }
                else if (NamHoc == "2022"){
                    string NewEmail = MSSV + "@sv4.dut.udn.vn";
                    sv.Set_Email(NewEmail);
                }
                else if (NamHoc == "2021"){
                    string NewEmail = MSSV + "@sv5.dut.udn.vn";
                    sv.Set_Email(NewEmail);
                }
            }
            return true;
        }

        bool Add_SinhVien(const SinhVien &sv){
            if (ds_SV.size() < MAX_SV){
                ds_SV.push_back(sv);
                return true;
            }
            else{
                cout << "Max sinh vien limit reached, unable to add more.";
                return false;
            }

        }

        bool Delete_SinhVien_By_MSSV(const string& mssv) {
        
        //find where SinhVien
        auto sinhvien = std::find_if(ds_SV.begin(), ds_SV.end(), [&](const SinhVien& tempsv) 
        {
            return tempsv.Get_MSSV() == mssv;
        });

        //check if found
        if (sinhvien != ds_SV.end()) {
            ds_SV.erase(sinhvien);
            return true; 
        }

        //not found
        return false; 
    }

        void Sort_SinhVien_In_Lop_By_Ten(){
            sort(ds_SV.begin(), ds_SV.end(), [](const SinhVien &a, const SinhVien &b) {
                if (a.Get_Ten() != b.Get_Ten())
                    return a.Get_Ten() < b.Get_Ten();
                
                return a.Get_HoLot() < b.Get_HoLot();
            });
            
            for (SinhVien& sv : ds_SV) {
                sv.Set_checkSort(true);
            }
        }

        //getters
        int Get_SoLuongSV() const {return ds_SV.size();}
        string Get_TenKhoa() const {return TenKhoa;}
        string Get_TenLop() const {return TenLop;}
        string Get_NamHoc() const {return NamHoc;}

        //find SinhVien by name
        SinhVien *Select_SinhVien_By_Name(const string &holot, const string &ten){
            for (SinhVien& sv : ds_SV) {
                if (sv.Get_HoLot() == holot && sv.Get_Ten() == ten) {
                    return &sv; 
                }
            }
        return nullptr;
        }

        //find the SinhVien based on MSSV
        SinhVien* Find_SinhVien_By_MSSV(const string& mssv) {
            //loop to find
            for (SinhVien& sv : ds_SV) {
                if (sv.Get_MSSV() == mssv) {
                    return &sv; 
                }
            }
            //not found
            return nullptr; 
        }

        //show all SinhVien within a Lop
        void Xuat_ds_SV() const{
            cout << ("\n\n\t\t\t\t\t\tTRUONG DAI HOC BACH KHOA - DAI HOC DA NANG\n");
            string TenKhoa = Get_TenKhoa();
            string TenLop = Get_TenLop();
            string NamHoc = Get_NamHoc();
            cout << "\n\n\t\t\t\t\t\tKHOA: " << TenKhoa << "\n";
            cout << "\n\n\t\t\t\t\t\tDANH SACH LOP: " << TenKhoa << " - " << "Khoa hoc " << NamHoc << "\n";

            cout << left;
            cout << setw(5) << "STT";
            cout << setw(12) << "MSSV";
            cout << setw(20) << "Ho Lot";
            cout << setw(10) << "Ten";
            cout << setw(10) << "Gioi Tinh";
            cout << setw(15) << "Ngay Sinh";
            cout << setw(35) << "Email" << endl;
            cout << string(107, '-') << endl;

            for (const SinhVien &sv: ds_SV){ 
                sv.Print_SinhVien();
            }
        }

        int Count_Assigned_SinhVien(const string& maKhoa) {
        int count = 0;
        for (const SinhVien& sv : ds_SV) {
            if (sv.Get_MaKhoa() == maKhoa && sv.Has_MSSV()) {
                count++;
            }
        }
        return count;
    }

    //setters
    void Set_TenLop(const string& ten) { TenLop = ten; }
    void Set_TenKhoa(const string& ten) { TenKhoa = ten; }
    void Set_NamHoc(const string& nam) { NamHoc = nam; }
};

class QuanLySinhVien{
    //attributes
    private:
        Lop ds_Lop[5][MAX_KHOA][MAX_LOP];

        static const map<string, KhoaLookUp> Khoa_To_Lop_Map; 
        static const vector<string> Nam_Hoc_List;

            //helpers
            static void SetColor(int color) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            }

            static bool Check_MaKhoa(const string MaKhoa){
                return Khoa_To_Lop_Map.find(MaKhoa) != Khoa_To_Lop_Map.end();
            };

            static bool Check_NamHoc(const string NamHoc){
                return std::find(Nam_Hoc_List.begin(), Nam_Hoc_List.end(), NamHoc) != Nam_Hoc_List.end();
            };

            static void Normalize_TenLop(string &TenLop){
                for (auto &x : TenLop){
                    x = toupper(x);
                }
            }

            int Get_KhoaPrefix(const string& maKhoa) {
                if (maKhoa == "101") return 0;
                if (maKhoa == "102") return 1;
                if (maKhoa == "104") return 2;
                if (maKhoa == "105") return 3;
                if (maKhoa == "106") return 4;
                if (maKhoa == "107") return 5;
                if (maKhoa == "117") return 6;
                if (maKhoa == "118") return 7;
                if (maKhoa == "121") return 8;
                return -1; 
            }

            //find class user need
            Lop *Select_Lop(){

        
                SetColor(14);
                string namhoc, makhoa;

                //find NamHoc
                do{
                    cout << "\t\t Nhap nam hoc (format: 20XX): \n";
                    getline(cin, namhoc);
                }
                while (!(Check_NamHoc(namhoc)));

                //find MaKhoa
                do{
                    cout << "\t\t Nhap ma khoa (format: 101, etc.): \n";
                    getline(cin, makhoa);
                }
                while(!Check_MaKhoa(makhoa));

                //find correct place
                int namID = -1;
                for (int i = 0; i < Nam_Hoc_List.size(); ++i) {
                    if (Nam_Hoc_List[i] == namhoc) {
                        namID = i;
                        break;
                    }
                }
                int khoaID = -1;
                khoaID = Get_KhoaPrefix(makhoa);

                //cant find
                if (namID == -1 || khoaID == -1) {
                    cout << "Khong tim thay nam hoc/khoa hoc.\n";
                    return nullptr;
                } 

                /*SHOW*/

                //show all classes
                SetColor(11);
                cout << "\n\t\t\t--- DANH SACH CAC LOP ---\n";
                vector<int> lopArrayIndex; 
                for (int k = 0; k < MAX_LOP; ++k) {
                    if (ds_Lop[namID][khoaID][k].Get_SoLuongSV() > 0) {
                        cout << "\t\t\t" << (lopArrayIndex.size() + 1) << ". "
                            << ds_Lop[namID][khoaID][k].Get_TenLop() << "\n";
                        lopArrayIndex.push_back(k);
                    }
                }

                //no class found
                if (lopArrayIndex.empty()) {
                cout << "\t\t\tKhong co lop nao de hien thi.\n";
                return nullptr;
                }

                //user's choice
                int choice;
                cout << "\t\t\tChon lop (1-" << lopArrayIndex.size() << "): ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice < 1 || choice > lopArrayIndex.size()) {
                    cout << "\t\t\tLua chon khong hop le.\n";
                    return nullptr;
                }

                //return pointer to class
                int k_index = lopArrayIndex[choice - 1];
                return &ds_Lop[namID][khoaID][k_index];
            }

            //find SinhVien by MSSV
            SinhVien *Select_SinhVien(){
                SetColor(14);
                string mssv;
                cout << "Nhap MSSV can tim";
                getline(cin, mssv);

                for (int i = 0; i < Nam_Hoc_List.size(); i++){
                    for (int j = 0; j < MAX_KHOA; j++){
                        for (int k = 0; k < MAX_LOP; k++){
                            SinhVien* foundSV = ds_Lop[i][j][k].Find_SinhVien_By_MSSV(mssv);
                        
                            //found
                            if (foundSV != nullptr) {
                                return foundSV; 
                            }
                        }
                    }            
                }

                //not found
                SetColor(14);
                cout << "Khong tim thay sinh vien";
                return nullptr;
            }


            //let user type in SinhVien
            SinhVien Create_SinhVien(){
                SetColor(14);
                string ho, ten, gt, ns, dc, mk, nh;
                
                cout << "\t\t Ho va ten lot: "; getline(cin, ho);
                cout << "\t\t Ten: "; getline(cin, ten);
                cout << "\t\t Gioi tinh: "; getline(cin, gt);
                cout << "\t\t Ngay sinh (dd/mm/yyyy): "; getline(cin, ns);
                cout << "\t\t Dia chi: "; getline(cin, dc);

                do{
                    cout << "\t\t Ma khoa(101,102...): ";
                    getline(cin, mk);
                }while (!(Check_MaKhoa(mk)));

                do{
                    cout << "\t\t Nam hoc(2025,2024...): ";
                    getline(cin, nh);
                }while(!(Check_NamHoc(nh)));

                return(SinhVien(ho, ten, gt, ns, dc, mk, nh));
            }

            int Count_SinhVien_In_Khoa(const string& maKhoa) {
            int count = 0;
            //loop to find class
            for (int i = 0; i < 5; ++i) { 
                for (int j = 0; j < MAX_KHOA; ++j) { 
                    for (int k = 0; k < MAX_LOP; ++k) { 
                        //lop coun its SinhVien
                        count += ds_Lop[i][j][k].Count_Assigned_SinhVien(maKhoa);
                    }
                }
            }
            return count;
        }
        //real

        void Handle_Them_SinhVien() {
        system("cls");
        SetColor(13);
        cout << "\t\t\t\t\t\t--- THEM SINH VIEN MOI ---\n\n";

        SinhVien sinhvien = Create_SinhVien(); 

        sinhvien.Assign_TenKhoa(Khoa_To_Lop_Map);

        //find correct Nam and Khoa ID
        int namID = -1;
        for (int i = 0; i < Nam_Hoc_List.size(); ++i) {
            if (Nam_Hoc_List[i] == sinhvien.Get_NamHoc()) {
                namID = i;
                break;
            }
        }
        int khoaID = Get_KhoaPrefix(sinhvien.Get_MaKhoa()); 

        //cant find
        if (namID == -1 || khoaID == -1) {
            SetColor(12); 
            cout << "Khong tim thay lop\n";
            system("pause");
            return;
        }

        //add to next available slot
        for (int k = 0; k < MAX_LOP; ++k) {
            //get pointer to the Lop
            Lop* lop = &ds_Lop[namID][khoaID][k]; 

            if (lop->Add_SinhVien(sinhvien)) {

                //create new Lop
                if (lop->Get_SoLuongSV() == 1) {
                    //find Khoa info
                    auto it = Khoa_To_Lop_Map.find(sinhvien.Get_MaKhoa());
                    if (it != Khoa_To_Lop_Map.end()) {
                        //make Lop's name
                        string namHocShort = sinhvien.Get_NamHoc().substr(2, 2); 
                        string tenLop = namHocShort + it->second.PostFix_Lop[k];

                        //set Lop's details
                        lop->Set_TenLop(tenLop);
                        lop->Set_TenKhoa(it->second.TenKhoa);
                        lop->Set_NamHoc(sinhvien.Get_NamHoc());
                    } else {
                        //not found in map
                        SetColor(12);
                        cout << "\n\t\t Khong tim thay thong tin khoa\n";
                        // Continue anyway, but Lop info might be incomplete
                    }
                }

                //success
                SetColor(10); 
                cout << "\n\t\t Da them sinh vien vao lop " << lop->Get_TenLop() << "!\n";
                system("pause");
                return; 
            }
        } 

        //all Lop full
        SetColor(12);
        cout << "\n\t\t Tat ca cac lop cho khoa nay trong nam hoc "
             << sinhvien.Get_NamHoc() << " da day\n";
        system("pause");
    }

        void Handle_Sua_SinhVien(){
            system("cls");
        SetColor(13);
        cout << "\t\t\t\t\t\t--- SUA THONG TIN SINH VIEN (CHUA CAP MSSV) ---\n\n";
        
        SetColor(14);
        string tenLop, hoLot, ten;
        
        cout << "\t\t Nhap Ten Lop cua sinh vien: ";
        getline(cin, tenLop);
        Normalize_TenLop(tenLop); 
        
        cout << "\t\t Nhap Ho Lot cua sinh vien: ";
        getline(cin, hoLot);
        
        cout << "\t\t Nhap Ten cua sinh vien: ";
        getline(cin, ten);

        //loop to find Lop
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < MAX_KHOA; ++j) {
                for (int k = 0; k < MAX_LOP; ++k) {
                    Lop* currentLop = &ds_Lop[i][j][k];
                    
                    //found
                    if (currentLop->Get_TenLop() == tenLop) {
                        
                        //find SinhVien by name
                        SinhVien* sv = currentLop->Select_SinhVien_By_Name(hoLot, ten);
                        
                        if (sv != nullptr) {
                            //found SinhVien, but have MSSV
                            if (sv->Has_MSSV()) {
                                SetColor(12);
                                cout << "\n\t\t Loi: Sinh vien nay da duoc cap MSSV, khong the sua.\n";
                                system("pause");
                                return;
                            }
                            
                            //found SinhVien, no MSSV
                            SetColor(10);
                            cout << "\n\t\t Da tim thay sinh vien. Nhap thong tin moi (de trong de giu nguyen):\n";
                            
                            string newHo, newTen, newGt, newNs, newDc;
                            cout << "\t\t Ho va ten lot moi [" << sv->Get_HoLot() << "]: "; getline(cin, newHo);
                            cout << "\t\t Ten moi [" << sv->Get_Ten() << "]: "; getline(cin, newTen);
                            cout << "\t\t Gioi tinh moi [" << sv->Get_GioiTinh() << "]: "; getline(cin, newGt);
                            cout << "\t\t Dia chi moi [" << sv->Get_DiaChi() << "]: "; getline(cin, newDc);
                            cout << "\t\t Ngay sinh moi [" << sv->Get_NgaySinh() << "]: "; getline(cin, newNs);

                            
                            // Use the setters
                            if (!newHo.empty()) sv->Set_HoLot(newHo);
                            if (!newTen.empty()) sv->Set_Ten(newTen);
                            if (!newGt.empty()) sv->Set_GioiTinh(newGt);
                            if (!newDc.empty()) sv->Set_DiaChi(newDc);
                            if (!newNs.empty()) sv->Set_NgaySinh(newNs);


                            //success
                            SetColor(10);
                            cout << "\n\t\t Cap nhat thong tin thanh cong!\n";
                            system("pause");
                            return; 
                        }
                    }
                }
            }
        }
        
        //not found
        SetColor(12); 
        cout << "\n\t\t Khong tim thay sinh vien voi ten '" << hoLot << " " << ten 
             << "' trong lop '" << tenLop << "'.\n";
        system("pause");
        }

        void Handle_Xoa_SinhVien(){
            system("cls");
            SetColor(13);
            cout << "Xoa sinh vien";

            string mssv;
            cout << "Nhap MSSV can xoa";
            getline(cin, mssv);

            for (int i = 0; i < 5; ++i) { 
                for (int j = 0; j < MAX_KHOA; ++j) { 
                    for (int k = 0; k < MAX_LOP; ++k) { 
                        if (ds_Lop[i][j][k].Delete_SinhVien_By_MSSV(mssv)) {
                            
                            SetColor(10); 
                            cout << "\n\t\t\tDA XOA SINH VIEN CO MSSV " << mssv << ".\n";
                            system("pause");
                            return; 
                        }
                    }
                }
            }

            //not found
            SetColor(9);
            cout << "Khong tim thay sinh vien voi MSSV " << mssv;
            system("pause");
        }
        
        void Handle_Tim_SinhVien(){
            system("cls");
            SetColor(13);
            cout << "Tim sinh vien";

            SinhVien *sinhvien = Select_SinhVien();
            
            //report success
            if (sinhvien != nullptr){
                SetColor(9);
                cout << "Da tim thay sinh vien \n";
                sinhvien->Print_SinhVien();
            }
            system("pause");
        }

        void Handle_SapXepLop(){
            system("cls");
            SetColor(13);
            cout << "Sap xep sinh vien.";

            Lop *lop = Select_Lop();

            //cant find
            if (lop == nullptr){
                SetColor(4);
                cout << "Khong tim thay lop.";
                system("pause");
                return;
            }

            //sap xep sinh vien
            lop->Sort_SinhVien_In_Lop_By_Ten();

            //report success
            SetColor(9);
            cout << "Da xep lop " << lop->Get_TenLop() << " thanh cong";
            system("pause");
        }

        void Handle_CapMSSV(){
            system("cls");
            SetColor(13);
            cout << "Cap MSSV.";

            Lop *lop = Select_Lop();

            //cant find
            if (lop == nullptr){
                SetColor(4);
                cout << "Khong tim thay lop.";
                system("pause");
                return;
            }

            //cap mssv
            int count = Count_SinhVien_In_Khoa(lop->Get_TenKhoa()); 
            lop->Assign_MSSV_To_Lop(count);

            //report success
            SetColor(9);
            cout << "Da cap MSSV cho lop " << lop->Get_TenLop() << " thanh cong";
            system("pause");
        }

        void Handle_CapEmail(){
            system("cls");
            SetColor(13);
            cout << "Cap Email sinh vien.";

            Lop *lop = Select_Lop();

            //cant find
            if (lop == nullptr){
                SetColor(4);
                cout << "Khong tim thay lop.";
                system("pause");
                return;
            }

            //sort itself
            lop->Assign_Email_To_Lop();

            //report success
            SetColor(9);
            cout << "Da cap Email cho lop " << lop->Get_TenLop() << " thanh cong";
            system("pause");
        }
   
   
        //main menu
        public:
            void Run() {
            
            int chon;
            do {
                system("cls");
                SetColor(14);
            cout << "\n\t\t\t\t\t    1   Them sinh vien moi                           ";
            cout << "\n\t\t\t\t\t    2  Sap xep danh sach sinh vien                   ";
            cout << "\n\t\t\t\t\t    3   Sua thong tin sinh vien                      ";
            cout << "\n\t\t\t\t\t    4   Cap ma so sinh vien (MSSV)                   ";
            cout << "\n\t\t\t\t\t    5   Cap Email                                    ";
            cout << "\n\t\t\t\t\t    6   Tim kiem sinh vien                           ";
            cout << "\n\t\t\t\t\t    7   Xoa sinh vien                                ";
            cout << "\n\t\t\t\t\t    0   Thoat chuong trinh                           ";
                SetColor(13);
                cout << "\n\t\t\t\t\t  [->] Nhap lua chon: ";
                
                cin >> chon;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (chon) {
                    case 1: Handle_Them_SinhVien(); break;
                    case 2: Handle_SapXepLop(); break;
                    case 3: Handle_Sua_SinhVien(); break;
                    case 4: Handle_CapMSSV(); break;
                    case 5: Handle_CapEmail(); break;
                    case 6: Handle_Tim_SinhVien(); break;
                    case 7: Handle_Xoa_SinhVien(); break;
                    case 0:
                        cout << "\n\t\t\tDang thoat...\n";
                        break;
                    default:
                        cout << "\n\t\t\tLua chon khong hop le!\n";
                        system("pause");
                }

            } while (chon != 0);
        }
};

// mappers
const map<string, KhoaLookUp> QuanLySinhVien::Khoa_To_Lop_Map = {
    { "101", { "Co khi",              { "CDT1", "CDT2", "CDT3" } } },
    { "102", { "Cong nghe thong tin", { "T_DT1", "T_DT2", "T_DT3" } } },
    { "104", { "Nhiet - Dien lanh",   { "N1", "N2", "N3" } } },
    { "105", { "Dien",                { "D1", "D2", "D3" } } },
    { "106", { "Dien tu - Vien thong",{ "DT1", "DT2", "DT3" } } },
    { "107", { "Hoa",                 { "H1", "H2", "H3" } } },
    { "117", { "Moi truong",          { "MT1", "MT2", "MT3" } } },
    { "118", { "Quan li du an",       { "QLDA1", "QLDA2", "QLDA3" } } },
    { "121", { "Kien truc",           { "KT1", "KT2", "KT3" } } }
};

const vector<string> QuanLySinhVien::Nam_Hoc_List = {"2021", "2022", "2023", "2024", "2025"};

int main(){
    QuanLySinhVien QLSV;
    QLSV.Run();
    return 0;
}