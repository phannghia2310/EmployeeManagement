#include <iostream>
#include<fstream>
#include<iomanip>
#include <windows.h>
#include<conio.h>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;

struct Date {
    int ngay, thang, nam;
};

class NhanVien {
    private:
        string MaNV;
        string HoTen;
        string NoiSinh;
        Date NgaySinh;
        long LuongCoBan;
    public:
        NhanVien();
        ~NhanVien();
        virtual void doc_File(ifstream& filein);
        virtual void Nhap();
        virtual void Xuat();
        virtual long TinhLuong() = 0;
        long getLuong();
        string getMaNV();
        string getTen();
        string getNoiSinh();
        int getNamSinh();
        long getLuongCoBan();
        virtual void xuat_File(ofstream& fileout);
};

class NhanVienSanXuat : public NhanVien {
    private:
        float GiaMotSP;
        int SoSP;
    public:
        NhanVienSanXuat();
        ~NhanVienSanXuat();
        void doc_File(ifstream& filein);
        void Nhap();
        void Xuat();
       	long TinhLuong();
        void xuat_File(ofstream& fileout);
};

class NhanVienVanPhong : public NhanVien {
     private:
        float HeSoLuong;
        int SoNgayLam;
     public:
        NhanVienVanPhong();
        ~NhanVienVanPhong();
        void doc_File(ifstream& filein);
        void Nhap();
        void Xuat();
        long TinhLuong();
        void xuat_File(ofstream& fileout);
};

class QuanLyNhanVien {
	private:
		NhanVien *nv[1000];
		int n;
	public:
		void doc_File(ifstream& filein);
		void Xuat_DS_NVSX();
        void Xuat_DS_NVVP();
		void ThemNV();
		void XoaNV();
		void SapXep();
		void TimKiem();
        void xuat_File(ofstream& fileout);
};

struct Menu {
    Menu();
    int phimDiChuyen();
};

void doc_Ngay(ifstream& filein, Date &NgaySinh) {
	filein >> NgaySinh.ngay;
	filein.ignore();
	filein >> NgaySinh.thang;
	filein.ignore();
	filein >> NgaySinh.nam;
	filein.ignore();
}

//Nhan vien
NhanVien::NhanVien() {
	MaNV = "";
	HoTen = "";
	NoiSinh = "";
	NgaySinh.ngay = 0;
	NgaySinh.thang = 0;
	NgaySinh.nam = 0;
	LuongCoBan = 0;
}

NhanVien::~NhanVien() {
}

void NhanVien::doc_File(ifstream& filein) {
	getline(filein, MaNV, ',');
	filein.ignore();
	getline(filein, HoTen, ',');
	filein.ignore();
	getline(filein, NoiSinh, ',');
    filein.ignore();
	doc_Ngay(filein, NgaySinh);
	filein >> LuongCoBan;
	filein.ignore();
}

void NhanVien::Nhap() {
	cout << "Nhap ma nhan vien: ";
	cin.ignore();
	getline(cin, MaNV);
	cout << "Nhap ho ten: ";
	getline(cin, HoTen);
	cout << "Nhap noi sinh: ";
	getline(cin, NoiSinh);
	cout << "Nhap ngay sinh: ";
	cin >> NgaySinh.ngay >> NgaySinh.thang >> NgaySinh.nam;
	cin.ignore();
	cout << "Nhap luong co ban: ";
	cin >> LuongCoBan;
}

void NhanVien::Xuat() {
	cout << "||" << setw(12) << MaNV << setw(23) << HoTen << setw(17) << NoiSinh << setw(13);
	cout << NgaySinh.ngay << "/" << NgaySinh.thang << "/" << NgaySinh.nam << setw(23);
	cout << LuongCoBan << setw(20);
}

long NhanVien::getLuong() {
	return this->TinhLuong();
}

string NhanVien::getMaNV() {
	return this->MaNV;
}

string NhanVien::getTen() {
	return this->HoTen;
}

string NhanVien::getNoiSinh() {
	return this->NoiSinh;
}

int NhanVien::getNamSinh() {
	return this->NgaySinh.nam;
}

long NhanVien::getLuongCoBan() {
	return this->LuongCoBan;
}

void NhanVien::xuat_File(ofstream& fileout) {
	fileout << "||" << setw(12) << MaNV << setw(23) << HoTen << setw(16) << NoiSinh << setw(13);
	fileout << NgaySinh.ngay << "/" << NgaySinh.thang << "/" << NgaySinh.nam << setw(20);
	fileout << LuongCoBan << setw(20);
}

//Nhan vien san xuat
NhanVienSanXuat::NhanVienSanXuat() {
	GiaMotSP = 0;
	SoSP = 0;
}

NhanVienSanXuat::~NhanVienSanXuat() {
}

void NhanVienSanXuat::doc_File(ifstream& filein) {
	NhanVien::doc_File(filein);
	filein >> GiaMotSP;
	filein.ignore();
	filein >> SoSP;
	filein.ignore();
}

void NhanVienSanXuat::Nhap() {
	NhanVien::Nhap();
	cout << "Nhap gia 1 san pham: ";
	cin >> GiaMotSP;
	cout << "Nhap so san pham: ";
	cin >> SoSP;
}

void NhanVienSanXuat::Xuat() {
	NhanVien::Xuat();
	cout << GiaMotSP << setw(17) << SoSP << setw(18) << this->TinhLuong() << setw(4) << "||" <<  endl;
}

long NhanVienSanXuat::TinhLuong() {
	return (this->getLuongCoBan() + GiaMotSP*SoSP);
}

void NhanVienSanXuat::xuat_File(ofstream& fileout) {
	NhanVien::xuat_File(fileout);
	fileout << GiaMotSP << setw(17) << SoSP << setw(18) << this->TinhLuong() << setw(4) << "||" <<  endl;
}

//Nhan vien van phong
NhanVienVanPhong::NhanVienVanPhong() {
	HeSoLuong = 0;
	SoNgayLam = 0;
}

NhanVienVanPhong::~NhanVienVanPhong() {
}

void NhanVienVanPhong::doc_File(ifstream& filein) {
	NhanVien::doc_File(filein);
	filein >> HeSoLuong;
	filein.ignore();
	filein >> SoNgayLam;
	filein.ignore();
}

void NhanVienVanPhong::Nhap() {
	NhanVien::Nhap();
	cout << "Nhap he so luong: ";
	cin >> HeSoLuong;
	cout << "Nhap so ngay lam: ";
	cin >> SoNgayLam;
}

void NhanVienVanPhong::Xuat() {
	NhanVien::Xuat();
	cout << setw(20) << HeSoLuong << setw(20) << SoNgayLam << setw(22) << this->TinhLuong() << setw(4) << "||" << endl;
}

long NhanVienVanPhong::TinhLuong() {
	return (this->getLuongCoBan()*HeSoLuong*SoNgayLam);
}

void NhanVienVanPhong::xuat_File(ofstream& fileout) {
	NhanVien::xuat_File(fileout);
	fileout << setw(22) << HeSoLuong << setw(18) << SoNgayLam << setw(21) << this->TinhLuong() << setw(4) << "||" << endl;
}

//Quan ly nhan vien
void QuanLyNhanVien::doc_File(ifstream& filein) {
	filein.open("dulieu.txt", ios_base::in);
	if(!filein.is_open()) {
		cout << "\t\tKhong tim thay file!";
	}
	else {
		filein >> n;
		filein.ignore();
		for(int i=0; i<n; i++) {
			NhanVien *NV;
			char c;
			filein >> c;
			if(c == 'P') {
				NV = new NhanVienSanXuat;
				NV->doc_File(filein);
			}
			else if(c == 'O') {
				NV = new NhanVienVanPhong;
				NV->doc_File(filein);
			}
			nv[i] = NV;
		}
		cout << "\t\tDoc file thanh cong!";
		filein.ignore();
	}
}

void QuanLyNhanVien::Xuat_DS_NVSX() {
	cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------";
    cout << "\n||    MA NHAN VIEN    ||    HO VA TEN    ||    NOI SINH    ||    NGAY SINH    ||     LUONG CO BAN      ||    DON GIA    ||    SO LUONG    ||     LUONG     ||";
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for(int i=0; i<n; i++) {
		if(nv[i]->getMaNV().find('P') != string::npos){
			nv[i]->Xuat();
			cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
}

void QuanLyNhanVien::Xuat_DS_NVVP() {
	cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    cout << "\n||    MA NHAN VIEN    ||    HO VA TEN    ||    NOI SINH    ||    NGAY SINH    ||      LUONG CO BAN      ||    HE SO LUONG    ||    SO NGAY LAM    ||    LUONG    ||";
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for(int i=0; i<n; i++) {
		if(nv[i]->getMaNV().find('O') != string::npos){
			nv[i]->Xuat();
			cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}	
}

void QuanLyNhanVien::ThemNV() {
	system("cls");
	int viTriChon = 0, pos;
	NhanVien *NV;
	Menu *m = new Menu;
	vector<string> menu = {"NHAN VIEN SAN XUAT", "NHAN VIEN VAN PHONG", "TRO VE"};
	bool troVe = false;
	while (true) {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\n\t\t\t\t\t\tChon loai nhan vien muon them\n\n";
		for (int i = 0; i < menu.size(); ++i) {
			if (viTriChon == i) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		int diChuyenPhim;
		if (_kbhit) {
			diChuyenPhim = m->phimDiChuyen();
			switch (diChuyenPhim) {
				case 1:
				case 3: {
					viTriChon += 1;
					if (viTriChon == menu.size())
						viTriChon = 0;
					break;
				}
				case 2:
				case 4: {
					viTriChon -= 1;
					if (viTriChon == -1)
						viTriChon = menu.size() - 1;
					break; 
				}
				case 5: {
					if (viTriChon == menu.size() - 1) {
						troVe = true;
						break;
					}
					else {
						system("cls");
						switch(viTriChon) {
							case 0:
								cout << "Nhap so bat ky de them: "; cin >> pos;
								if(pos < 0) {
									pos = 0;
								}
								else if(pos > n) {
									pos = n;
								}
								NV = new NhanVienSanXuat;
								NV->Nhap();
								for(int i=n; i>pos; i--) {
									nv[i] = nv[i-1];
								}
								nv[pos] = NV;
								++n;
								Xuat_DS_NVSX();
								system("pause");
								break;
							case 1:
								cout << "Nhap so bat ky de them: "; cin >> pos;
								if(pos < 0) {
									pos = 0;
								}
								else if(pos > n) {
									pos = n;
								}
								NV = new NhanVienVanPhong;
								NV->Nhap();
								for(int i=n; i>pos; i--) {
									nv[i] = nv[i-1];
								}
								nv[pos] = NV;
								++n;
								Xuat_DS_NVVP();
								system("pause");
								break;
							default:
								break;
						}
					}
					break;
				}
				default:
					break;
				}
			}
			if (troVe == true) {
				break;
		}
	}
}

void QuanLyNhanVien::XoaNV() {
	system("cls");
	vector<string> menu = { "THEO MA NHAN VIEN", "THEO HO VA TEN", "THEO NOI SINH", "THEO NAM SINH", "TRO VE" };
	int pointer = 0;
	bool troVe = false;
	Menu *m = new Menu;
	string tukhoa;
	int nam;
	while (true) {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\n\t\t\t\t\t\tChon tieu chi tim kiem\n";
		for (int i = 0; i < menu.size(); ++i) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
					cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menu[i] << right << setw(0) << "|";
					cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			int x;
			if (_kbhit) {
				x = m->phimDiChuyen();
				switch (x) {
				case 1:
				case 3: {
					pointer += 1;
					if (pointer == 5)
						pointer = 0;
					break; }
				case 2:
				case 4: {
					pointer -= 1;
					if (pointer == -1)
						pointer = 4;
					break; }
				case 5: {
					if (pointer == menu.size() - 1) {
						troVe = true;
						break;
					}
					else {
						system("cls");
						int dem = 0;
						switch(pointer) {
							case 0:
								cout << "\nNhap ma nhan vien muon xoa: ";
								getline(cin, tukhoa);
								for(int i=0; i<n; i++) {
									if(tukhoa == nv[i]->getMaNV()) {
										for(int j=i; j<n; j++) {
											nv[j] = nv[j+1];
										}
										--n;
										dem++;
										cout << "\nDa xoa nhan vien co ma la: " << tukhoa;
										break; 
									}
								}
								if(dem == 0)
									cout << "\nNhan vien co ma " << tukhoa << " khong ton tai!";
								else {
									Xuat_DS_NVSX();
									cout << "\n\n\n\n";
									Xuat_DS_NVVP();
									dem = 0;
								}
								system("pause");
								break;
							case 1:
								cout << "\nNhap ten nhan vien muon xoa: ";
								getline(cin, tukhoa);
								for(int i=0; i<n; i++) {
									if(tukhoa == nv[i]->getTen()) {
										for(int j=i; j<n; j++) {
											nv[j] = nv[j+1];
										}
										--n;
										dem++;
										cout << "\nDa xoa nhan vien co ten la: " << tukhoa; 
										break;
									}
								}
								if(dem == 0)
									cout << "\nNhan vien co ten " << tukhoa << " khong ton tai!";
								else {
									Xuat_DS_NVSX();
									cout << "\n\n\n\n";
									Xuat_DS_NVVP();
									dem = 0;
								}
								system("pause");
								break;
							case 2:
								cout << "\nNhap noi sinh muon xoa: ";
								getline(cin, tukhoa);
								for(int i=0; i<n; i++) {
									if(tukhoa == nv[i]->getNoiSinh()) {
										for(int j=i; j<n; j++) {
											nv[j] = nv[j+1];
										}
										--n;
										dem++;
										cout << "\nDa xoa nhan vien co noi sinh la: " << tukhoa; 
										break;
									}
								}
								if(dem == 0)
									cout << "\nNhan vien co noi sinh " << tukhoa << " khong ton tai!";
								else {
									Xuat_DS_NVSX();
									cout << "\n\n\n\n";
									Xuat_DS_NVVP();
									dem = 0;
								}
								system("pause");
								break;
							case 3:
								cout << "\nNhap nam sinh muon xoa: ";
								cin >> nam;
								for(int i=0; i<n; i++) {
									if(nam == nv[i]->getNamSinh()) {
										for(int j=i; j<n; j++) {
											nv[j] = nv[j+1];
										}
										--n;
										dem++;
										cout << "\nDa xoa nhan vien co nam sinh la: " << nam; 
										break;
									}
								}
								if(dem == 0)
									cout << "\nNhan vien co nam sinh " << nam << " khong ton tai!";
								else {
									Xuat_DS_NVSX();
									cout << "\n\n\n\n";
									Xuat_DS_NVVP();
									dem = 0;
								}
								system("pause");
								break;
							default:
								break;
						}
					}
					break;
				}
				default:
					break;
				}
			}
			if (troVe == true) {
				break;
		}
	}
}

void QuanLyNhanVien::TimKiem() {
	system("cls");
	vector<string> menu = { "THEO MA NHAN VIEN", "THEO HO VA TEN", "THEO NOI SINH", "THEO NAM SINH", "TRO VE" };
	int pointer = 0;
	bool troVe = false;
	Menu *m = new Menu;
	string tukhoa;
	int nam;
	while (true) {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\n\t\t\t\t\t\tChon tieu chi tim kiem\n";
		for (int i = 0; i < menu.size(); ++i) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
		}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			int x;
			if (_kbhit) {
				x = m->phimDiChuyen();
				switch (x) {
				case 1:
				case 3: {
					pointer += 1;
					if (pointer == 5)
						pointer = 0;
					break; }
				case 2:
				case 4: {
					pointer -= 1;
					if (pointer == -1)
						pointer = 4;
					break; }
				case 5: {
					if (pointer == menu.size() - 1) {
						troVe = true;
						break;
					}
					else {
						int dem = 0;
						system("cls");
						switch(pointer) {
							case 0:
								cout << "\nNhap ma nhan vien muon tim: ";
								getline(cin, tukhoa);
								cout << "\n\t\t\t\t\t\t\t>>  THONG TIN NHAN VIEN  <<\n" << endl;
								for(int i=0; i<n; i++) {
									if(nv[i]->getMaNV().find(tukhoa) != string::npos) {
										nv[i]->Xuat();
										++dem;
									}
								}
								if(dem == 0)
									cout << "\nKhong tim thay nhan vien lien quan den tu khoa: " << tukhoa;
								system("pause");
								break;
							case 1:
								cout << "\nNhap ten nhan vien muon tim: ";
								getline(cin, tukhoa);
								cout << "\n\t\t\t\t\t\t\t>>  THONG TIN NHAN VIEN  <<" << endl;
								for(int i=0; i<n; i++) {
									if(nv[i]->getTen().find(tukhoa) != string::npos) {
										nv[i]->Xuat();
										++dem;
									}
								}
								if(dem == 0)
									cout << "\nKhong tim thay nhan vien lien quan den tu khoa: " << tukhoa;
								system("pause");
								break;
							case 2:
								cout << "\nNhap noi sinh muon tim: ";
								getline(cin, tukhoa);
								cout << "\n\t\t\t\t\t\t>>  THONG TIN NHAN VIEN  <<\n" << endl;
								for(int i=0; i<n; i++) {
									if(tukhoa == nv[i]->getNoiSinh()) {
										nv[i]->Xuat();
										++dem;
									}
								}
								if(dem == 0)
									cout << "\nKhong tim thay nhan vien lien quan den tu khoa: " << tukhoa;
								system("pause");
								break;
							case 3:
								cout << "\nNhap nam sinh muon tim: ";
								cin >> nam;
								cout << "\n\t\t\t\t\t\t>>  THONG TIN NHAN VIEN  <<\n" << endl;
								for(int i=0; i<n; i++) {
									if(nam == nv[i]->getNamSinh()) {
										nv[i]->Xuat();
										++dem;
									}
								}
								if(dem == 0)
									cout << "\nKhong tim thay nhan vien lien quan den tu khoa: " << tukhoa;
								break;
							default:
								break;
						}
					}
					break;
				}
				default:
					break;
				}
			}
			if (troVe == true) {
				break;
		}
	}
}

void HoanVi(NhanVien *&nv1, NhanVien *&nv2) {
	NhanVien *nv3;
	nv3 = nv1;
	nv1 = nv2;
	nv2 = nv3;
}

void QuanLyNhanVien::SapXep() {
	system("cls");
	vector<string> menu = { "THEO MA NHAN VIEN", "THEO HO VA TEN", "THEO NOI SINH", "THEO NAM SINH", "THEO LUONG", "TRO VE" };
	int pointer = 0;
	Menu *m = new Menu;
	bool troVe = false;
	while (true) {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\n\t\t\t\t\t\tChon tieu chi sap xep\n";
		for (int i=0; i<menu.size(); ++i) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		int x;
		if (_kbhit) {
			x = m->phimDiChuyen();
			switch (x) {
				case 1:
				case 3: {
					pointer += 1;
					if (pointer == 6)
						pointer = 0;
					break; }
				case 2:
				case 4: {
					pointer -= 1;
					if (pointer == -1)
						pointer = 5;
					break; }
				case 5: {
					if (pointer == menu.size() - 1) {
						troVe = true;
						break;
					}
					else {
						system("cls");
						vector<string> menuChon;
						int vitriChon = 0;
						Menu *k = new Menu;
						bool quayLai = false;
						switch(pointer) {
							case 0: 
								menuChon = { "CHIEU XUOI", "CHIEU NGUOC", "QUAY LAI" };
								while (true) {
									system("cls");
									Xuat_DS_NVSX();
									cout << "\n\n\n";
									Xuat_DS_NVVP();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									cout << "\n\t\t\t\t\tChon chieu sap xep\n";
									for (int i=0; i<menuChon.size(); ++i) {
										if (i == vitriChon) {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
										else {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
									}
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									int v;
									v = k->phimDiChuyen();
									switch (v) {
										case 1:
										case 3: {
											vitriChon += 1;
											if (vitriChon == 3)
												vitriChon = 0;
											break; }
										case 2:
										case 4: {
											vitriChon -= 1;
											if (vitriChon == -1)
												vitriChon = 2;
											break; }
										case 5: {
											if(vitriChon == menuChon.size() - 1) {
												quayLai = true;
												break;
											}
											else {
												switch(vitriChon) {
													case 0:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																char* str1 = new char[nv[i]->getMaNV().length()];
																strcpy(str1, nv[i]->getMaNV().c_str());
																char* str2 = new char[nv[j]->getMaNV().length()];
																strcpy(str2, nv[j]->getMaNV().c_str());
																if(strcmp(str1, str2) > 0) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													case 1:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																char* str1 = new char[nv[i]->getMaNV().length()];
																strcpy(str1, nv[i]->getMaNV().c_str());
																char* str2 = new char[nv[j]->getMaNV().length()];
																strcpy(str2, nv[j]->getMaNV().c_str());
																if(strcmp(str1, str2) < 0) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													default:
														break;
												}
											}
											break;
										}
										default:
											break;
									}
									if (quayLai == true)
										break;
								}
								break;	
							case 1:
								menuChon = { "CHIEU XUOI", "CHIEU NGUOC", "QUAY LAI" };
								while (true) {
									system("cls");
									Xuat_DS_NVSX();
									cout << "\n\n\n";
									Xuat_DS_NVVP();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									cout << "\n\t\t\t\t\tChon chieu sap xep\n";
									for (int i=0; i<menuChon.size(); ++i) {
										if (i == vitriChon) {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
										else {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
									}
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									int v;
									v = k->phimDiChuyen();
									switch (v) {
										case 1:
										case 3: {
											vitriChon += 1;
											if (vitriChon == 3)
												vitriChon = 0;
											break; }
										case 2:
										case 4: {
											vitriChon -= 1;
											if (vitriChon == -1)
												vitriChon = 2;
											break; }
										case 5: {
											if(vitriChon == menuChon.size() - 1) {
												quayLai = true;
												break;
											}
											else {
												switch(vitriChon) {
													case 0:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																char* str1 = new char[nv[i]->getTen().length()];
																strcpy(str1, nv[i]->getTen().c_str());
																char* str2 = new char[nv[j]->getTen().length()];
																strcpy(str2, nv[j]->getTen().c_str());
																if(strcmp(str1, str2) > 0) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													case 1:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																char* str1 = new char[nv[i]->getTen().length()];
																strcpy(str1, nv[i]->getTen().c_str());
																char* str2 = new char[nv[j]->getTen().length()];
																strcpy(str2, nv[j]->getTen().c_str());
																if(strcmp(str1, str2) < 0) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													default:
														break;
												}
											}
											break;
										}
										default:
											break;
									}
									if (quayLai == true)
										break;
								}
								break;		
							case 2:
								menuChon = { "CHIEU XUOI", "CHIEU NGUOC", "QUAY LAI" };
								while (true) {
									system("cls");
									Xuat_DS_NVSX();
									cout << "\n\n\n";
									Xuat_DS_NVVP();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									cout << "\n\t\t\t\t\tChon chieu sap xep\n";
									for (int i=0; i<menuChon.size(); ++i) {
										if (i == vitriChon) {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
										else {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
									}
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									int v;
									v = k->phimDiChuyen();
									switch (v) {
										case 1:
										case 3: {
											vitriChon += 1;
											if (vitriChon == 3)
												vitriChon = 0;
											break; }
										case 2:
										case 4: {
											vitriChon -= 1;
											if (vitriChon == -1)
												vitriChon = 2;
											break; }
										case 5: {
											if(vitriChon == menuChon.size() - 1) {
												quayLai = true;
												break;
											}
											else {
												switch(vitriChon) {
													case 0:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																char* str1 = new char[nv[i]->getNoiSinh().length()];
																strcpy(str1, nv[i]->getNoiSinh().c_str());
																char* str2 = new char[nv[j]->getNoiSinh().length()];
																strcpy(str2, nv[j]->getNoiSinh().c_str());
																if(strcmp(str1, str2) > 0) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													case 1:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																char* str1 = new char[nv[i]->getNoiSinh().length()];
																strcpy(str1, nv[i]->getNoiSinh().c_str());
																char* str2 = new char[nv[j]->getNoiSinh().length()];
																strcpy(str2, nv[j]->getNoiSinh().c_str());
																if(strcmp(str1, str2) < 0) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													default:
														break;
												}
											}
											break;
										}
										default:
											break;
									}
									if (quayLai == true)
										break;
								}
								break;	
							case 3:
								menuChon = { "TANG DAN", "GIAM DAN", "QUAY LAI" };
								while (true) {
									system("cls");
									Xuat_DS_NVSX();
									cout << "\n\n\n";
									Xuat_DS_NVVP();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									cout << "\n\t\t\t\t\tChon chieu sap xep\n";
									for (int i=0; i<menuChon.size(); ++i) {
										if (i == vitriChon) {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
										else {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
									}
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									int v;
									v = k->phimDiChuyen();
									switch (v) {
										case 1:
										case 3: {
											vitriChon += 1;
											if (vitriChon == 3)
												vitriChon = 0;
											break; }
										case 2:
										case 4: {
											vitriChon -= 1;
											if (vitriChon == -1)
												vitriChon = 2;
											break; }
										case 5: {
											if(vitriChon == menuChon.size() - 1) {
												quayLai = true;
												break;
											}
											else {
												switch(vitriChon) {
													case 0:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																if(nv[i]->getNamSinh() > nv[j]->getNamSinh()) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													case 1:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																if(nv[i]->getNamSinh() < nv[j]->getNamSinh()) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													default:
														break;
												}
											}
											break;
										}
										default:
											break;
									}
									if (quayLai == true)
										break;
								}
								break;	
							case 4:
								menuChon = { "LON DAN", "NHO DAN", "QUAY LAI" };
								while (true) {
									system("cls");
									Xuat_DS_NVSX();
									cout << "\n\n\n";
									Xuat_DS_NVVP();
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									cout << "\n\t\t\t\t\tChon chieu sap xep\n";
									for (int i=0; i<menuChon.size(); ++i) {
										if (i == vitriChon) {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
										else {
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
											cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
											cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
										}
									}
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									int v;
									v = k->phimDiChuyen();
									switch (v) {
										case 1:
										case 3: {
											vitriChon += 1;
											if (vitriChon == 3)
												vitriChon = 0;
											break; }
										case 2:
										case 4: {
											vitriChon -= 1;
											if (vitriChon == -1)
												vitriChon = 2;
											break; }
										case 5: {
											if(vitriChon == menuChon.size() - 1) {
												quayLai = true;
												break;
											}
											else {
												switch(vitriChon) {
													case 0:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																if(nv[i]->getLuong() > nv[j]->getLuong()) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													case 1:
														for(int i=0; i<n-1; i++) {
															for(int j=n-1; j>i; j--) {
																if(nv[i]->getLuong() < nv[j]->getLuong()) {
																	HoanVi(nv[i], nv[j]);
																} 
															}
														}
														break;
													default:
														break;
												}
											}
											break;
										}
										default:
											break;
									}
									if (quayLai == true)
										break;
								}
								break;	
							default:
								break;
						}	
					}
					break;
				}
				default:
					break;
			}
		}
		if (troVe == true)
				break;	
	}
}

void QuanLyNhanVien::xuat_File(ofstream& fileout) {
	fileout.open("xuatdulieu.txt", ios_base::out);
	fileout << "\n------------------------------------------------------------------------------------------------------------------------------------------------------------";
    fileout << "\n||    MA NHAN VIEN    ||    HO VA TEN    ||    NOI SINH    ||    NGAY SINH    ||      LUONG CO BAN      ||    DON GIA    ||    SO LUONG    ||    LUONG    ||";
    fileout << "\n------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for(int i=0; i<n; i++) {
		if(nv[i]->getMaNV().find('P') != string::npos){
			nv[i]->xuat_File(fileout);
			fileout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	fileout << "\n\n\n\n";
	fileout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    fileout << "\n||    MA NHAN VIEN    ||    HO VA TEN    ||    NOI SINH    ||    NGAY SINH    ||      LUONG CO BAN      ||    HE SO LUONG    ||    SO NGAY LAM    ||    LUONG    ||";
    fileout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for(int i=0; i<n; i++) {
		if(nv[i]->getMaNV().find('O') != string::npos){
			nv[i]->xuat_File(fileout);
			fileout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	fileout.close();
}

Menu::Menu() {}

int Menu::phimDiChuyen() {
	char c = _getch();
	if ((int)c == -32) c = _getch();
	switch ((int)c) {
		case 80:
			return 1; //cout << "Xuong";
		case 72:
			return 2; //cout << "Len";
		case 77:
			return 3; //cout << "Phai";       
		case 75:
			return 4; //cout << "Trai";
		case 27:
			return 8; //Nut ESC thoat
		case 13:
			return 5; //Nut Enter
		default:
			return 0; //cout << "Sai";
	}
}

int MENU_QL() {
	vector<string> menu = { "DOC DU LIEU TU FILE", "XEM DANH SACH NHAN VIEN", "SAP XEP NHAN VIEN", "THEM NHAN VIEN", "XOA NHAN VIEN", "TIM KIEM", "XUAT FILE", "THOAT CHUONG TRINH" };
	int pointer = 0;
	ifstream filein;
	ofstream fileout;
	bool daDoc = false;
	QuanLyNhanVien *QLNV = new QuanLyNhanVien;
	Menu *m = new Menu;
	while (true) {
		fflush(stdin);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\t\t\t\t\t         | >>>>>>> HE THONG QUAN LY NHAN VIEN <<<<<<< |\n\n";
		for (int i = 0; i < menu.size(); i++) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(10) << ">>  " << left << setw(34) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(10) << "    " << left << setw(34) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		int x;
		bool thoat = false;
		if (_kbhit) {
			x = m->phimDiChuyen();
			switch (x) {
			case 1:
			case 3: {
				pointer += 1;
				if (pointer == menu.size())
					pointer = 0;
				thoat = true;
				break; }
			case 2:
			case 4: {
				pointer -= 1;
				if (pointer == -1)
					pointer = menu.size() - 1;
				thoat = true;
				break; }
			case 5: {
				switch (pointer) {
				case 0:
					cout << "\nBan da chon doc file nhan vien!\n";
					system("cls");
					QLNV->doc_File(filein);
					daDoc = true;
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break; 
				case 1:
					system("cls");
					if(daDoc) {
						cout << "\nBan da chon xuat danh sach nhan vien!\n";
						QLNV->Xuat_DS_NVSX();
						cout << "\n\n\n\n";
						QLNV->Xuat_DS_NVVP();
					}else{
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break; 
				case 2:
                    system("cls");
					if(daDoc) {
						cout << "\nBan da chon sap xep nhan vien!\n";
						QLNV->SapXep();
					}else {
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break;
				case 3:
					system("cls");
					if(daDoc) {
						cout << "\nBan da chon them nhan vien!\n";
						QLNV->ThemNV();
					}else {
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break;
				case 4:
					system("cls");
					if(daDoc) {
						cout << "\nBan da chon xoa nhan vien!\n";
						QLNV->XoaNV();
					}else {
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break;
				case 5:
					system("cls");
					if(daDoc) {
						cout << "\nBan da chon tim kiem nhan vien!\n";
						QLNV->TimKiem();
					}else {
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break;
				case 6:
					system("cls");
					if(daDoc) {
						cout << "\nBan da chon xuat file danh sach nhan vien!\n";
						QLNV->xuat_File(fileout);
						cout <<"\nXuat file thanh cong!\n";	
					}
					else {
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout <<"\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break;
				default:

					return 0;
					break;
				}
				thoat = true;
				break;
			}
			default:
				break;
			}
		}
	}
}

int MENU_NV() {
	vector<string> menu = { "DOC DU LIEU TU FILE", "XEM DANH SACH NHAN VIEN", "SAP XEP NHAN VIEN", "TIM KIEM", "THOAT CHUONG TRINH" };
	int pointer = 0;
	ifstream filein;
	ofstream fileout;
	bool daDoc = false;
	QuanLyNhanVien *QLNV = new QuanLyNhanVien;
	Menu *m = new Menu;
	while (true) {
		fflush(stdin);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\t\t\t\t         | >>>>>>> HE THONG QUAN LY NHAN VIEN <<<<<<< |\n\n";
		for (int i = 0; i < menu.size(); i++) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(10) << ">>  " << left << setw(34) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t----------------------------------------------";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(10) << "    " << left << setw(34) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		int x;
		bool thoat = false;
		if (_kbhit) {
			x = m->phimDiChuyen();
			switch (x) {
			case 1:
			case 3: {
				pointer += 1;
				if (pointer == menu.size())
					pointer = 0;
				thoat = true;
				break; }
			case 2:
			case 4: {
				pointer -= 1;
				if (pointer == -1)
					pointer = menu.size() - 1;
				thoat = true;
				break; }
			case 5: {
				switch (pointer) {
				case 0:
					cout << "\nBan da chon doc file nhan vien!\n";
					system("cls");
					QLNV->doc_File(filein);
					daDoc = true;
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break; 
				case 1:
					system("cls");
					if(daDoc) {
						cout << "\nBan da chon xuat danh sach nhan vien!\n";
						QLNV->Xuat_DS_NVSX();
						cout << "\n\n\n\n";
						QLNV->Xuat_DS_NVVP();
					}else{
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break; 
				case 2:
                    system("cls");
					if(daDoc) {
						cout << "\nBan da chon sap xep nhan vien!\n";
						QLNV->SapXep();
					}else {
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break;
				case 3:
					system("cls");
					if(daDoc) {
						cout << "\nBan da chon tim kiem nhan vien!\n";
						QLNV->TimKiem();
					}else {
						cout << "\n\t\tVui long doc file nhan vien truoc!\n";
					}
					cout << "\n\t\tNhan phim bat ky de tiep tuc!\n";
					getch();
					break;
				default:
					return 0;
					break;
				}
				thoat = true;
				break;
			}
			default:
				break;
			}
		}
	}
}

int SYSTEM() {
	string pass_reg = "";
    string name_reg = "";
    string pass = "";
    string name = "";
    fstream fileNV;
	fstream fileQL;
    char ch;
	int pointer = 0;
	Menu *m = new Menu;
	vector<string> menu = {"NHAN VIEN", "QUAN LY", "THOAT"};
	while (true) {
		fflush(stdin);
		system("cls");
		cout << "\n\t\t\t\t\t\t\t\t\t ----------------------------------------------";
    	cout << "\n\t\t\t\t\t\t\t\t\t ||   WELCOME TO EMPLOYEE MANAGEMENT SYSTEM  ||";
    	cout << "\n\t\t\t\t\t\t\t\t\t ----------------------------------------------";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t            BAN LA \n\n";
		for (int i = 0; i < menu.size(); i++) {
			if (i == pointer) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				cout << "\n\t\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "\n\t\t\t\t\t\t\t\t\t ----------------------------------------------";
				cout << "\n\t\t\t\t\t\t\t\t\t |" << right << setw(15) << "    " << left << setw(29) << menu[i] << right << setw(0) << "|";
				cout << "\n\t\t\t\t\t\t\t\t\t ----------------------------------------------";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		int x;
		bool thoat = false;
		if (_kbhit) {
			x = m->phimDiChuyen();
			switch (x) {
			case 1:
			case 3: {
				pointer += 1;
				if (pointer == 3)
					pointer = 0;
				thoat = true;
				break; }
			case 2:
			case 4: {
				pointer -= 1;
				if (pointer == -1)
					pointer = 2;
				thoat = true;
				break; }
			case 5: {
				system("cls");
				vector<string> menuChon;
				int vitriChon = 0;
				Menu *k = new Menu;
				bool quayLai = false;
				switch(pointer) {
					case 0: 
						menuChon = { "DANG KY", "DANG NHAP", "QUAY LAI" };
						while (true) {
							system("cls");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int i=0; i<menuChon.size(); ++i) {
								if (i == vitriChon) {
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
									cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
								}
								else {
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
									cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
								}
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							int v;
							v = k->phimDiChuyen();
							switch (v) {
								case 1:
								case 3: {
									vitriChon += 1;
									if (vitriChon == 3)
										vitriChon = 0;
									break; }
								case 2:
								case 4: {
									vitriChon -= 1;
									if (vitriChon == -1)
										vitriChon = 2;
									break; }
								case 5: {
									if(vitriChon == menuChon.size() - 1) {
										quayLai = true;
										break;
									}
									else {
										switch(vitriChon) {
											case 0:
												system("cls");
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\t\t\t\t\t\t\t\t>>        DANG KY        <<";
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\n\t\t\t\t\t\t\t\tNhap ten: ";
												cin >> name_reg;
												cout << "\n\t\t\t\t\t\t\t\tNhap mat khau: ";
												ch = _getch();
												while (ch != 13) {
													pass_reg.push_back(ch);
													cout << '*';
													ch = _getch();
												}
												fileNV.open("Emp_data.txt", ios::app);
												fileNV << " " << name_reg << " " << pass_reg << "\n";
												fileNV.close();
												cout << "\nLuu dang ky thanh cong!";
												getch();
												break;
											case 1:
												system("cls");
												fileNV.open("Emp_data.txt", ios::in);
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\t\t\t\t\t\t\t\t>>       DANG NHAP       <<";
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\n\t\t\t\t\t\t\t\tNhap ten: ";
												cin >> name;
												cout << "\n\t\t\t\t\t\t\t\tNhap mat khau: ";
												ch = _getch();
												while (ch != 13) {
													pass.push_back(ch);
													cout << '*';
													ch = _getch();
												}
												fileNV >> name_reg >> pass_reg;
												while (!fileNV.eof()) {
													if(pass == pass_reg && name == name_reg) {
														cout << "\n\n\n\t\t\t\t\t\t\t\t| Dang xac minh |\n\t\t\t\t\t\t\t\t";
														for (int a = 1; a < 8; a++) {
															Sleep(500);
															cout << "...";
														}
														cout << "\n\nChap thuan quyen truy cap...\n\n";
														system("PAUSE");
														MENU_NV();
														break;
													}
													else {
														cout << "\n\n\n\t\t\t\t\t\t\t\t| Dang xac minh |\n\t\t\t\t\t\t\t\t";
														for (int a = 1; a < 8; a++) {
															Sleep(500);
															cout << "...";
														}
														cout << "\n\nTu choi quyen truy cap...\n\n";
														system("PAUSE");
														break;
													}
													fileNV >> name_reg >> pass_reg;
												}
												fileNV.close();
												break;
											default:
												cout << "\nDau vao khong hop le .. Vui long thu lai ..";
												break;
										}
									}
									break;
								}
								default:
									break;
							}
							if (quayLai == true)
								break;
						}
						break;
					case 1:
						menuChon = { "DANG KY", "DANG NHAP", "QUAY LAI" };
						while (true) {
							system("cls");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int i=0; i<menuChon.size(); ++i) {
								if (i == vitriChon) {
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
									cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << ">>  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
								}
								else {
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
									cout << "\n\t\t\t\t\t\t\t\t |" << right << setw(15) << "  " << left << setw(29) << menuChon[i] << right << setw(0) << "|";
									cout << "\n\t\t\t\t\t\t\t\t ----------------------------------------------";
								}
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							int v;
							v = k->phimDiChuyen();
							switch (v) {
								case 1:
								case 3: {
									vitriChon += 1;
									if (vitriChon == 3)
										vitriChon = 0;
									break; }
								case 2:
								case 4: {
									vitriChon -= 1;
									if (vitriChon == -1)
										vitriChon = 2;
									break; }
								case 5: {
									if(vitriChon == menuChon.size() - 1) {
										quayLai = true;
										break;
									}
									else {
										switch(vitriChon) {
											case 0:
												system("cls");
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\t\t\t\t\t\t\t\t>>        DANG KY        <<";
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\n\t\t\t\t\t\t\t\tNhap ten: ";
												cin >> name_reg;
												cout << "\n\t\t\t\t\t\t\t\tNhap mat khau: ";
												ch = _getch();
												while (ch != 13) {
													pass_reg.push_back(ch);
													cout << '*';
													ch = _getch();
												}
												fileQL.open("Man_data.txt", ios::app);
												fileQL << " " << name_reg << " " << pass_reg << "\n";
												fileQL.close();
												cout << "\nLuu dang ky thanh cong!";
												getch();
												break;
											case 1:
												system("cls");
												fileQL.open("Man_data.txt", ios::in);
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\t\t\t\t\t\t\t\t>>       DANG NHAP       <<";
												cout << "\n\t\t\t\t\t\t\t\t---------------------------";
												cout << "\n\n\t\t\t\t\t\t\t\tNhap ten: ";
												cin >> name;
												cout << "\n\t\t\t\t\t\t\t\tNhap mat khau: ";
												ch = _getch();
												while (ch != 13) {
													pass.push_back(ch);
													cout << '*';
													ch = _getch();
												}
												fileQL >> name_reg >> pass_reg;
												while (!fileQL.eof()) {
													if(pass == pass_reg && name == name_reg) {
														cout << "\n\n\n\t\t\t\t\t\t\t\t| Dang xac minh |\n\t\t\t\t\t\t\t\t";
														for (int a = 1; a < 8; a++) {
															Sleep(500);
															cout << "...";
														}
														cout << "\n\nChap thuan quyen truy cap..\n\n";
														system("PAUSE");
														MENU_QL();
													}
													else {
														cout << "\n\n\n\t\t\t\t\t\t\t\t| Dang xac minh |\n\t\t\t\t\t\t\t\t";
														for (int a = 1; a < 8; a++) {
															Sleep(500);
															cout << "...";
														}
														cout << "\n\nTu choi quyen truy cap...\n\n";
														system("PAUSE");
													}
													fileQL >> name_reg >> pass_reg;
												}
												fileQL.close();
												break;
											default:
												cout << "\nDau vao khong hop le .. Vui long thu lai ..";
												break;
										}
									}
									break;
								}
								default:
									break;
							}
							if (quayLai == true)
								break;
						}
						break;
					default:
						return 0;
						break;
				}
				thoat = true;
				break;
			}
			default:
				break;
			}
		}
	}
}
int main() {
	system("cls");
	SYSTEM();
}