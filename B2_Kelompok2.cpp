#include <iostream>  // Digunakan Untuk Memudahkan Untuk Input Output
#include <string>    // Digunakan Untuk Beroperasi Pada Tipe Data String
#include <vector>    // Digunakan Untuk Secara Otomatis Menyimpan Dan Mengatur Alokasi 
#include <stdexcept> // header untuk exception
#include <cstdlib>  // Digunakan untuk alokasi memori dinamis
#include <time.h>  //Digunakan untuk waktu dan tanggal
#include <stdlib.h> // Digunakan untuk fungsi standar cpp
#include <limits> //Digunakan untuk membatasi nilai tipe data
#include <conio.h> //Digunakan untuk fungsi input output
#include <iomanip> //Digunakan untuk mengatur tampilan output
#include <windows.h> //Digunakan Untuk menyediakan akses API ke windows
#include <chrono> //Digunakan untuk mengatur waktu dan tunggu 
#include <thread> //Digunakan untuk mengatur thread atau benang
#include <fstream> //DIgunakan untuk mengizinkan akses berkas biner untuk input output
#include <map>

using namespace std; // Digunakan Untuk Mempermudah Agar Tidak Mendeklarasikan std Berkala

struct DataDiri
{
    int id_pasien;
    string nama_pasien;
    string jeniskelamin_pasien;
    float beratbadan_pasien;
    float tinggibadan_pasien;
    string keluhan_pasien;
    DataDiri *next = NULL;
};


// Mendefinisikan Struct Untuk Data Dokter
struct DataDokter {
    int id;
    string nama;
    string jeniskelamin;
    string spesialis;
    DataDokter* next;
};

// ------------ Queue ------------

struct pasien_terdaftar
{
    int id_pasienterdaftar;
    string nama_pasienterdaftar;
    string tanggalkunjungan_pasienterdaftar; 
    pasien_terdaftar *next = NULL;
};

struct pasien
{
    pasien_terdaftar ps;
    pasien *next;
};

pasien *newpasien(){
    pasien *nodeBaru = new pasien();
    cout << "Masukkan ID : ";
    fflush(stdin);
    cin >> nodeBaru->ps.id_pasienterdaftar;
    cout << "Masukkan Nama: ";
    fflush(stdin);
    getline(cin, nodeBaru->ps.nama_pasienterdaftar);
    cout << "Masukkan Tanggal : ";
    fflush(stdin);
    getline (cin, nodeBaru->ps.tanggalkunjungan_pasienterdaftar);
    return nodeBaru;
}


// ------------ DATA PASIEN ------------
DataDiri* headDataDiri = nullptr; // Linked list untuk data diri
bool IsFutureDate(const string& date) {
    // meriksa apa tanggal lebih besar dari hari ini atau besok.
   

    // Dapatkan tanggal 
    time_t now = time(0);
    tm* currentDate = localtime(&now);

    int currentDay = currentDate->tm_mday;
    int currentMonth = currentDate->tm_mon + 1; // Januari dimulai dari 1
    int currentYear = currentDate->tm_year + 1900; // Tahun ini biar kada lewat

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (year > currentYear || (year == currentYear && (month > currentMonth || (month == currentMonth && day > currentDay)))) {
        return true;
    }

    return false;
}
bool IsDateValid(const string& date) {
    
    if (date.size() != 10) {
        return false;
    }

    if (date[2] != '/' || date[5] != '/') {
        return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        return false;
    }

    return true;
}

DataDiri* CreateDataDiri() {
    DataDiri* newData = new DataDiri;

    cout << "Masukkan Nama: ";
    getline(cin, newData->nama_pasien);

    // Validasi Nama
    if (newData->nama_pasien.empty()) {
        cout << "Nama tidak boleh kosong." << endl;
        delete newData;
        return nullptr;
    }

    char jenisKelaminInput;
    bool validJenisKelamin = false;

    do {
        cout << "Pilih Jenis Kelamin (L: Laki-laki / P: Perempuan): ";
        cin >> jenisKelaminInput;

        // Membersihkan buffer input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        jenisKelaminInput = toupper(jenisKelaminInput);

        // Validasi Jenis Kelamin
        if (jenisKelaminInput == 'L' || jenisKelaminInput == 'P') {
            validJenisKelamin = true;
        } else {
            cout << "Jenis kelamin tidak valid. Harap masukkan 'L' untuk laki-laki atau 'P' untuk perempuan." << endl;
        }

    } while (!validJenisKelamin);

    if (jenisKelaminInput == 'L') {
        newData->jeniskelamin_pasien = "Laki-laki";
    } else {
        newData->jeniskelamin_pasien = "Perempuan";
    }

    // Input berat badan
    cout << "Masukkan Berat Badan (kg): ";
    cin >> newData->beratbadan_pasien;

    // Validasi Berat Badan
    if (cin.fail() || newData->beratbadan_pasien <= 0) {
        cout << "Berat badan harus berupa angka positif." << endl;
        delete newData;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return nullptr;
    }

    // Input tinggi badan
    cout << "Masukkan Tinggi Badan (cm): ";
    cin >> newData->tinggibadan_pasien;

    // Validasi Tinggi Badan
    if (cin.fail() || newData->tinggibadan_pasien <= 0) {
        cout << "Tinggi badan harus berupa angka positif." << endl;
        delete newData;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return nullptr;
    }

    cin.ignore();

    // Input keluhan sakit
    do {
        cout << "Masukkan Keluhan Sakit: ";
        getline(cin, newData->keluhan_pasien);

        // Validasi Keluhan Sakit
        if (newData->keluhan_pasien.empty()) {
            cout << "Keluhan sakit tidak boleh kosong. Silakan masukkan kembali." << endl;
        }

    } while (newData->keluhan_pasien.empty());

    // Generate ID dan Tanggal Kunjungan secara acak
    newData->id_pasien = rand() % 1000 + 1; // ID acak antara 1-1000
    time_t now = time(0);
    tm* date = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y", date);

    newData->next = nullptr;

    return newData;
}


// ------------ DATA DOKTER ------------
DataDokter* headDokter = nullptr; // Linked list untuk dokter
// Fungsi untuk membuat dokter baru
DataDokter* CreateDokter() {
    DataDokter* newDokter = new DataDokter;

    // Generate ID Dokter secara acak (maksimal 3 angka)
    newDokter->id = rand() % 1000;

    cout << "Masukkan Nama Dokter: ";
    
    getline(cin, newDokter->nama);

    // Validasi Nama
    if (newDokter->nama.empty()) {
        cout << "Nama dokter tidak boleh kosong." << endl;
        delete newDokter;
        return nullptr;
    }

    char jenisKelaminInput;
    bool validInput = false;

    do {
        cout << "Masukkan Jenis Kelamin (L: Laki-laki / P: Perempuan): ";
        cin >> jenisKelaminInput;

        // Membersihkan buffer input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Mengonversi input jenis kelamin ke huruf kapital
        jenisKelaminInput = toupper(jenisKelaminInput);

        // Validasi Jenis Kelamin
        if (jenisKelaminInput == 'L' || jenisKelaminInput == 'P') {
            validInput = true;
        } else {
            cout << "Jenis Kelamin tidak valid. Harap masukkan 'L' untuk laki-laki atau 'P' untuk perempuan." << endl;
        }

    } while (!validInput);

    newDokter->jeniskelamin = jenisKelaminInput;

    cout << "Masukkan Spesialis: ";
    getline(cin, newDokter->spesialis);

    // Validasi Spesialis
    if (newDokter->spesialis.empty()) {
        cout << "Spesialis tidak boleh kosong." << endl;
        delete newDokter;
        return nullptr;
    }

    newDokter->next = nullptr;

    return newDokter;
}

// --- ANIMASI TAMPILAN ---
void draw(int selected) {
    system("cls");
	//Pointer
	string menu = " | Menu Read Data  | ";
	string *ptrMenu = &menu;
	cout << *ptrMenu << endl;
	cout << "___________________________________________"<<endl;
    cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selected == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Tampilkan Data" << endl;
    if (selected == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Kembali" << endl;
}

void draw2(int selected2) {
    system("cls");
	//Pointer
	string menu = " | Menu Data Pasien | ";
	string *ptrMenu = &menu;
	cout << *ptrMenu << endl;
	cout << "___________________________________________"<<endl;
    cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selected2 == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Tampilkan Rata-Rata pasien" << endl;
    if (selected2 == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Tampilkan data Pasien" << endl;
    if (selected2 == 3) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 3. ";cout<<"\033[1;32m" ;
    }
    cout << "Kembali" << endl;
}

void draw3(int selected2) {
    system("cls");
	//Pointer
	string menu = " | Menu Rekap Data Dokter | ";
	string *ptrMenu = &menu;
	cout << *ptrMenu << endl;
	cout << "___________________________________________"<<endl;
    cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selected2 == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Tampilkan Data" << endl;
    if (selected2 == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Kembali" << endl;
}

void drawkeluhan(int selectedk) {
    system("cls");
	//Pointer
	string menu = " | Menu keluhan  | ";
	string *ptrMenu = &menu;
	cout << *ptrMenu << endl;
	cout << "___________________________________________"<<endl;
    cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selectedk == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Cocokan Keluhan " << endl;
    if (selectedk == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Kembali" << endl;
}

void drawlog(int selectedlog) {
    system("cls");
    cout << "\033[1;32m";
	cout<<"========================"<<endl;
    cout<<"|""\033[1;37m"" Silahkan Pilih Login""\033[1;32m" " |"<<endl;
	cout<<"========================"<<endl;
    cout<<"\033[1;32m" ;
    if (selectedlog == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Login" << endl;
    if (selectedlog == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Register" << endl;
    if (selectedlog == 3) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 3. ";cout<<"\033[1;32m" ;
    }
    cout << "Keluar" << endl;
}

void drawOptions(int selectedOption) {
    system("cls");
	 cout << "\033[1;32m";
	//Pointer
	string menu = " ===  MENU ADMIN  === ";
	string *ptrMenu = &menu;
	cout << "=========================="<<endl;
	cout <<"||";
	cout << "\033[1;37m";
	cout << *ptrMenu;
	cout << "\033[1;32m";
	cout <<"||"<< endl;
	cout << "=========================="<<endl;
	cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selectedOption == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Menampilkan Data Dokter" << endl;
    if (selectedOption == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Menambah Data Dokter " << endl;
    if (selectedOption == 3) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 3. ";cout<<"\033[1;32m" ;
    }
    cout << "Mengubah Data Dokter" << endl;
	if (selectedOption == 4) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 4. ";cout<<"\033[1;32m" ;
    }
    cout << "Menghapus Data Dokter" << endl;
	if (selectedOption == 5) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 5. ";cout<<"\033[1;32m" ;
    }
    cout << "Tampilkan Rekap Dokter" << endl;
	if (selectedOption == 6) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 6. ";cout<<"\033[1;32m" ;
    }
    cout << "Tampilkan rekap pasien" << endl;
	if (selectedOption == 7) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 7. ";cout<<"\033[1;32m" ;
    }
    cout << "Cocokan keluhan" << endl;
	if (selectedOption == 8) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 8. ";cout<<"\033[1;32m" ;
    }
    cout << "Searching pasien" << endl;
    if (selectedOption == 9) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 9. ";cout<<"\033[1;32m" ;
    }
    cout << "Mengelola Antrian Pasien" << endl;
    if (selectedOption == 10) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
		cout<<"\033[1;37m" ;
        cout << " 10. ";cout<<"\033[1;32m" ;
    }
    cout << "Log Out" << endl;
}

void drawuser(int selecteduser) {
    system("cls");
	//Pointer
	string menu = " | Menu User | ";
	string *ptrMenu = &menu;
	cout << *ptrMenu << endl;
	cout << "___________________________________________"<<endl;
    cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selecteduser == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << " Menampilkan Data Diri Pasien " << endl;
    if (selecteduser == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Tambah Data Pasien" << endl;
    if (selecteduser == 3) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 3. ";cout<<"\033[1;32m" ;
    }
    cout << "Ubah Data Pasien " << endl;
    if (selecteduser == 4) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 4. ";cout<<"\033[1;32m" ;
    }
    cout << "Hapus Data Pasien" << endl;
    if (selecteduser == 5) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 5. ";cout<<"\033[1;32m" ;
    }
    cout << "Tampilkan Data Dokter" << endl;
    if (selecteduser == 6) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 6. ";cout<<"\033[1;32m" ;
    }
    cout << "Cari dokter berdasarkan nama" << endl;
    if (selecteduser == 7) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 7. ";cout<<"\033[1;32m" ;
    }
    cout << "Lihat antrian Pasien" << endl;
    if (selecteduser == 8) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 8. ";cout<<"\033[1;32m" ;
    }
    cout << "apa Keluhan anda" << endl;
    if (selecteduser == 9) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 9. ";cout<<"\033[1;32m" ;
    }
    cout << "Log Out" << endl;
}

void drawadmin(int selectedadmin) {
    system("cls");
	//Pointer
	string menu = " | Menu Tambahan | ";
	string *ptrMenu = &menu;
	cout << *ptrMenu << endl;
	cout << "___________________________________________"<<endl;
    cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selectedadmin == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Cocokkan Keluhan Pasien dengan Obat\n " << endl;
    if (selectedadmin == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Rekap Data Pasien\n" << endl;
    if (selectedadmin == 3) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 3. ";cout<<"\033[1;32m" ;
    }
    cout << "Keluar" << endl;
}

void drawadmin2(int selectedadmin) {
    system("cls");
	//Pointer
	string menu = " | Menu Mengelola antrian | ";
	string *ptrMenu = &menu;
	cout << *ptrMenu << endl;
	cout << "___________________________________________"<<endl;
    cout<<"\033[1;37m" ;
    cout << "Pilihan Menu:" << endl;cout<<"\033[1;32m" ;
    if (selectedadmin == 1) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 1. ";cout<<"\033[1;32m" ;
    }
    cout << "Tambah/Buat Antrian" << endl;
    if (selectedadmin == 2) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 2. ";cout<<"\033[1;32m" ;
    }
    cout << "Proses antrian" << endl;
    if (selectedadmin == 3) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 3. ";cout<<"\033[1;32m" ;
    }
    cout << "Lihat antrian Pertama " << endl;
    if (selectedadmin == 4) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 4. ";cout<<"\033[1;32m" ;
    }
    cout << "Lihat antrian Terakhir" << endl;
    if (selectedadmin == 5) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 5. ";cout<<"\033[1;32m" ;
    }
    cout << "Lihat semua Antrian" << endl;
    if (selectedadmin == 6) {
		cout<<"\033[1;31m" ;
        cout << "> ";cout<<"\033[1;32m" ;
    } else {
        cout<<"\033[1;37m" ;
        cout << " 6. ";cout<<"\033[1;32m" ;
    }
    cout << "Keluar" << endl;
}

// SEARCHING DATA PASIEN 
// Fungsi untuk mencari data Pasien berdasarkan nama dengan metode Fibonacci
DataDiri* searchByNamaFibonacci(DataDiri* head, string targetNama) {
    DataDiri* current = head;
    DataDiri* prev = nullptr;
    DataDiri* prev2 = nullptr;

    int fibM_minus_2 = 0;
    int fibM_minus_1 = 1;
    int fibM = fibM_minus_1 + fibM_minus_2;

    // Find the length of the linked list
    int length = 0;
    DataDiri* temp = head;
    while (temp != nullptr) {
        length++;
        temp = temp->next;
    }

    while (fibM < length) {
        prev2 = prev;
        prev = current;
        current = current->next;
        fibM_minus_2 = fibM_minus_1;
        fibM_minus_1 = fibM;
        fibM = fibM_minus_1 + fibM_minus_2;
    }

    while (current && current->nama_pasien.compare(targetNama) != 0) {
        int newFibM = fibM_minus_1 - fibM_minus_2;
        fibM_minus_1 = fibM_minus_2;
        fibM_minus_2 = newFibM;
        fibM = fibM_minus_1 + fibM_minus_2;

        if (current->nama_pasien.compare(targetNama) < 0) {
            if (prev) {
                prev2 = prev;
            }
            prev = current;
            current = current->next;
        } else {
            if (prev) {
                current = prev;
                prev = prev2;
            }
        }
    }

    if (current && current->nama_pasien.compare(targetNama) == 0) {
        return current;
    } else {
        return nullptr;
    }
}

DataDiri* cariByNama(DataDiri* head, const string& targetNama) 
{
    DataDiri* current = head;
    while (current != NULL) 
    {
        if (current->nama_pasien == targetNama) 
        {
            return current; 
        }
        current = current->next;
    }
    return NULL; 
}

// Fungsi untuk mencari data berdasarkan nama
void SearchByNama() {
    string targetNama;
    cout << "Masukkan Nama yang ingin Anda cari: ";
     
    getline(cin, targetNama);
    
    DataDiri* hasilPencarian = cariByNama(headDataDiri, targetNama);
    if (hasilPencarian != NULL) {
        cout << "Data ditemukan:" << endl;
        cout << "ID Pasien: " << hasilPencarian->id_pasien << endl;
        cout << "Nama Pasien: " << hasilPencarian->nama_pasien << endl;
        cout << "Jenis Kelamin: " << hasilPencarian->jeniskelamin_pasien << endl;
        cout << "Berat Badan: " << hasilPencarian->beratbadan_pasien << endl;
        cout << "Tinggi Badan: " << hasilPencarian->tinggibadan_pasien << endl;
        cout << "Keluhan : " << hasilPencarian->keluhan_pasien << endl;
    } else {
        cout << "Data dengan Nama '" << targetNama << "' tidak ditemukan." << endl;
    }
     this_thread::sleep_for(chrono::milliseconds(2000));
						cout << "Tekan Apa Saja Untuk Kembali"; getch();
						
						cout<<"\033[1;32m" ;
}

// SEARCHING DATA DOKTER
DataDokter* cariDokterByNama(DataDokter* head, const string& targetNama) {
    DataDokter* current = head;
    while (current != NULL) {
        if (current->nama == targetNama) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Fungsi untuk mencari data dokter berdasarkan nama
void SearchDokterByNama() {
    string targetNama;
    cout << "Masukkan Nama Dokter yang ingin Anda cari: ";
   
    getline(cin, targetNama);

    DataDokter* hasilPencarian = cariDokterByNama(headDokter, targetNama);
    if (hasilPencarian != NULL) {
        cout << "Data ditemukan:" << endl;
        cout << "ID Dokter: " << hasilPencarian->id << endl;
        cout << "Nama Dokter: " << hasilPencarian->nama << endl;
        cout << "Jenis Kelamin: " << hasilPencarian->jeniskelamin << endl;
        cout << "Spesialis: " << hasilPencarian->spesialis << endl;
    } else {
        cout << "Data dengan Nama Dokter '" << targetNama << "' tidak ditemukan." << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Tekan Apa Saja Untuk Kembali";
    getch();
    cout << "\033[1;32m";
}


// -------- FUNGSI DATA USER --------
// Fungsi untuk menambahkan data diri ke dalam linked list
void AddDataDiri() {
    DataDiri* newData = CreateDataDiri();

    if (newData) {
        if (!headDataDiri) {
            headDataDiri = newData;
        } else {
            DataDiri* current = headDataDiri;
            while (current->next) {
                current = current->next;
            }
            current->next = newData;
        }
        cout << "Data diri berhasil ditambahkan." << endl;
    }
}

// Fungsi untuk membagi daftar menjadi dua bagian
void SplitList(DataDiri* source, DataDiri** front, DataDiri** back) {
    DataDiri* fast;
    DataDiri* slow;
    slow = source;
    fast = source->next;

    // Melanjutkan fast dua kali lebih cepat daripada slow
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' berada pada tengah daftar, jadi membagi daftar menjadi dua bagian
    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

// Fungsi untuk menggabungkan dua daftar yang sudah diurutkan
DataDiri* MergeLists(DataDiri* left, DataDiri* right) {
    DataDiri* result = nullptr;

    if (left == nullptr) {
        return right;
    } else if (right == nullptr) {
        return left;
    }

    // Membandingkan string nama pasien untuk pengurutan
    if (left->nama_pasien <= right->nama_pasien) {
        result = left;
        result->next = MergeLists(left->next, right);
    } else {
        result = right;
        result->next = MergeLists(left, right->next);
    }

    return result;
}

// Fungsi untuk mengurutkan daftar dengan metode penggabungan
void MergeSort(DataDiri** head) {
    DataDiri* dataDiri = *head;
    DataDiri* left;
    DataDiri* right;

    if (dataDiri == nullptr || dataDiri->next == nullptr) {
        return; // Kondisi basis: data kosong atau hanya satu elemen
    }

    // Memecah daftar menjadi dua bagian
    SplitList(dataDiri, &left, &right);

    // Mengurutkan kedua bagian
    MergeSort(&left);
    MergeSort(&right);

    // Menggabungkan kedua bagian yang sudah diurutkan
    *head = MergeLists(left, right);
}

// Fungsi untuk menampilkan semua data diri
void ShowDataDiri() {
    if (!headDataDiri) {
        cout << "Tidak ada data." << endl;
        system("pause");
        system("cls");
        return;
    }

    // Menjalankan merge sort untuk mengurutkan data.
    MergeSort(&headDataDiri);

    DataDiri* current = headDataDiri;
    while (current) {
        cout << "ID: " << current->id_pasien << endl;
        cout << "Nama: " << current->nama_pasien << endl;
        cout << "Jenis Kelamin: " << current->jeniskelamin_pasien << endl;
        cout << "Berat Badan: " << current->beratbadan_pasien << " kg" << endl;
        cout << "Tinggi Badan: " << current->tinggibadan_pasien << " cm" << endl;
        cout << "Keluhan Sakit: " << current->keluhan_pasien << endl;
        cout << endl;

        current = current->next;
    }
}
// Fungsi untuk Mengubah data diri
void UpdateDataDiri(int id) {
    DataDiri* current = headDataDiri;

    while (current) {
        if (current->id_pasien == id) {
            cout << "Data saat ini:" << endl;
            cout << "ID: " << current->id_pasien << endl;
            cout << "Nama: " << current->nama_pasien << endl;
            cout << "Jenis Kelamin: " << current->jeniskelamin_pasien << endl;
            cout << "Berat Badan: " << current->beratbadan_pasien << " kg" << endl;
            cout << "Tinggi Badan: " << current->tinggibadan_pasien << " cm" << endl;
            cout << "Keluhan Sakit: " << current->keluhan_pasien << endl;
            cout << "Masukkan data baru:" << endl;

            // Validasi input nama
            do {
                cout << "Nama: ";
                cin.ignore();
                getline(cin, current->nama_pasien);

                if (current->nama_pasien.empty()) {
                    cout << "Nama tidak boleh kosong. Silakan masukkan kembali." << endl;
                }
            } while (current->nama_pasien.empty());

            char jenisKelaminInput;
            bool validJenisKelamin = false;

            do {
                cout << "Jenis Kelamin (L/P): ";
                cin >> jenisKelaminInput;
                cin.ignore(); // Menghapus karakter newline dari buffer

                if (jenisKelaminInput == 'L' || jenisKelaminInput == 'l') {
                    current->jeniskelamin_pasien = "Laki-laki";
                    validJenisKelamin = true;
                } else if (jenisKelaminInput == 'P' || jenisKelaminInput == 'p') {
                    current->jeniskelamin_pasien = "Perempuan";
                    validJenisKelamin = true;
                } else {
                    cout << "Jenis kelamin tidak valid. Harap masukkan 'L' atau 'P'." << endl;
                }
            } while (!validJenisKelamin);

            // Validasi input berat badan
            do {
                cout << "Berat Badan (kg): ";
                cin >> current->beratbadan_pasien;

                if (cin.fail() || current->beratbadan_pasien <= 0) {
                    cout << "Berat badan harus berupa angka positif. Silakan masukkan kembali." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (cin.fail() || current->beratbadan_pasien <= 0);

            // Validasi input tinggi badan
            do {
                cout << "Tinggi Badan (cm): ";
                cin >> current->tinggibadan_pasien;

                if (cin.fail() || current->tinggibadan_pasien <= 0) {
                    cout << "Tinggi badan harus berupa angka positif. Silakan masukkan kembali." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (cin.fail() || current->tinggibadan_pasien <= 0);

            cin.ignore();

            do {
                cout << "Keluhan Sakit: ";
                getline(cin, current->keluhan_pasien);

                // Validasi Keluhan Sakit
                if (current->keluhan_pasien.empty()) {
                    cout << "Keluhan sakit tidak boleh kosong. Silakan masukkan kembali." << endl;
                }
            } while (current->keluhan_pasien.empty());

            cout << "Data diri berhasil diperbarui." << endl;
            return;
        }
        current = current->next;
    }

    cout << "ID tidak ditemukan. Data diri tidak ditemukan." << endl;
}


// Fungsi untuk menghapus data diri pasien berdasarkan ID
void DeleteDataDiri(int id) {
    DataDiri* current = headDataDiri;
    DataDiri* prev = nullptr;

    while (current) {
        if (current->id_pasien == id) {
            cout << "Data diri yang akan dihapus:" << endl;
            cout << "ID: " << current->id_pasien << endl;
            cout << "Nama: " << current->nama_pasien << endl;
            cout << "Jenis Kelamin: " << current->jeniskelamin_pasien << endl;
            cout << "Berat Badan: " << current->beratbadan_pasien << " kg" << endl;
            cout << "Tinggi Badan: " << current->tinggibadan_pasien << " cm" << endl;
            cout << "Keluhan Sakit: " << current->keluhan_pasien << endl;
            cout << "Apakah Anda yakin ingin menghapus data diri ini? (Y/N): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                if (prev) {
                    prev->next = current->next;
                } else {
                    headDataDiri = current->next;
                }
                delete current;
                cout << "Data diri berhasil dihapus." << endl;
            } else {
                cout << "Penghapusan data diri dibatalkan." << endl;
            }
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "ID tidak ditemukan. Data diri tidak ditemukan." << endl;
}


// -------- FUNGSI DATA ADMIN --------
// Fungsi untuk menambahkan dokter baru ke dalam linked list
void AddDokter() {
    DataDokter* newDokter = CreateDokter();
    if (newDokter) {
        if (!headDokter) {
            headDokter = newDokter;
        } else {
            DataDokter* current = headDokter;
            while (current->next) {
                current = current->next;
            }
            current->next = newDokter;
        }
        cout << "Dokter berhasil ditambahkan." << endl;
    }
}

// Fungsi untuk membagi daftar menjadi dua bagian
void SplitListDokter(DataDokter* source, DataDokter** front, DataDokter** back) {
    DataDokter* fast;
    DataDokter* slow;
    slow = source;
    fast = source->next;

    // Melanjutkan fast dua kali lebih cepat daripada slow
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' berada pada tengah daftar, jadi membagi daftar menjadi dua bagian
    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

// Fungsi untuk menggabungkan dua daftar yang sudah diurutkan
DataDokter* MergeLists(DataDokter* left, DataDokter* right) {
    DataDokter* result = nullptr;

    if (left == nullptr) {
        return right;
    } else if (right == nullptr) {
        return left;
    }

    // Membandingkan string nama dokter untuk pengurutan
    if (left->nama <= right->nama) {
        result = left;
        result->next = MergeLists(left->next, right);
    } else {
        result = right;
        result->next = MergeLists(left, right->next);
    }

    return result;
}


// Fungsi untuk mengurutkan daftar dengan metode penggabungan
void MergeSortDokter(DataDokter** head) {
    DataDokter* dataDokter = *head;
    DataDokter* left;
    DataDokter* right;

    if (dataDokter == nullptr || dataDokter->next == nullptr) {
        return; // Kondisi basis: data kosong atau hanya satu elemen
    }

    // Memecah daftar menjadi dua bagian
    SplitListDokter(dataDokter, &left, &right);

    // Mengurutkan kedua bagian
    MergeSortDokter(&left);
    MergeSortDokter(&right);

    // Menggabungkan kedua bagian yang sudah diurutkan
    *head = MergeLists(left, right);
}

// Fungsi untuk menampilkan semua data dokter
void ShowDokter() {
    if (!headDokter) {
        cout << "Belum ada data dokter." << endl;
    } else {
         // Menjalankan merge sort untuk mengurutkan data dokter.
        MergeSortDokter(&headDokter);

        DataDokter* current = headDokter;
        cout << "Data Dokter:" << endl;
        while (current) {
            cout << "ID: " << current->id << endl;
            cout << "Nama Dokter: " << current->nama << endl;
            cout << "Spesialis: " << current->spesialis << endl;
            cout << "Jenis Kelamin: " << current->jeniskelamin << endl;
            cout << endl;
            current = current->next;
        }
    }

}

// Fungsi untuk mengubah data dokter
void EditDokter() {
    int targetId;
    if (!headDokter) {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << "Tekan Apa Saja Untuk Kembali";
        getch();
        cout << "\033[1;32m";
    } else {
        cout << "Masukkan ID dokter yang ingin diubah: ";
        cin >> targetId;

       
        while (cin.fail()) {
            cout << "ID harus berupa Nomor. Masukkan ID kembali: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> targetId;
        }

        DataDokter* current = headDokter;
        bool dokterDitemukan = false;

        while (current) {
            if (current->id == targetId) {
                cout << "Masukkan Nama Dokter Baru: ";
                cin.ignore();
                getline(cin, current->nama);

                // Validasi Nama
                if (current->nama.empty()) {
                    cout << "Nama dokter tidak boleh kosong." << endl;
                    return;
                }

                char jenisKelaminInput;
                bool validJenisKelamin = false;

                do {
                    cout << "Masukkan Jenis Kelamin Baru (L: Laki-laki / P: Perempuan): ";
                    cin >> jenisKelaminInput;
                    cin.ignore(); // Menghapus karakter newline dari buffer

                    jenisKelaminInput = toupper(jenisKelaminInput);

                    // Validasi Jenis Kelamin
                    if (jenisKelaminInput == 'L' || jenisKelaminInput == 'P') {
                        validJenisKelamin = true;
                    } else {
                        cout << "Jenis kelamin tidak valid. Harap masukkan 'L' atau 'P'." << endl;
                    }
                } while (!validJenisKelamin);

                if (jenisKelaminInput == 'L') {
                    current->jeniskelamin = "Laki-laki";
                } else {
                    current->jeniskelamin = "Perempuan";
                }

                cout << "Masukkan Spesialis Baru: ";
                getline(cin, current->spesialis);

                // Validasi Spesialis
                if (current->spesialis.empty()) {
                    cout << "Spesialis tidak boleh kosong." << endl;
                    return;
                }

                cout << "Data dokter berhasil diubah." << endl;
                dokterDitemukan = true;
                break;
            }
            current = current->next;
        }

        if (!dokterDitemukan) {
            cout << "Dokter dengan ID " << targetId << " tidak ditemukan." << endl;
            system("pause");
            system("cls");
        }
    }
}


// Fungsi untuk menghapus data dokter
void DeleteDokter() {
    int targetId;
    if (!headDokter) {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << "Tekan Apa Saja Untuk Kembali";
        getch();
        cout << "\033[1;32m";
    } else {
        cout << "Masukkan ID dokter yang ingin dihapus: ";
        cin >> targetId;

        // Validasi input ID 
        while (cin.fail()) {
            cout << "ID harus berupa Nomor. Masukkan ID kembali: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> targetId;
        }

        DataDokter* current = headDokter;
        DataDokter* prev = nullptr;
        bool dokterDitemukan = false;

        while (current) {
            if (current->id == targetId) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    headDokter = current->next;
                }

                delete current;
                cout << "Data dokter berhasil dihapus." << endl;
                dokterDitemukan = true;
                break;
            }

            prev = current;
            current = current->next;
        }

        if (!dokterDitemukan) {
            cout << "Dokter dengan ID " << targetId << " tidak ditemukan." << endl;
        }
    }
}

// Fungsi untuk menampilkan spesialis dokter
void tampilkanRekapDataDokter() {
      if (!headDokter) {
        cout << "Belum ada data dokter." << endl;
    } else {
        // Menjalankan merge sort untuk mengurutkan data dokter.
        MergeSortDokter(&headDokter);

        map<string, int> rekapSpesialis;

        // Iterate over the linked list
        DataDokter* current = headDokter;
        while (current) {
            rekapSpesialis[current->spesialis]++;
            current = current->next;
        }

        cout << "\nData Dokter :" << endl;
        current = headDokter;
        while (current) {
            cout << "ID: " << current->id << endl;
            cout << "Nama Dokter: " << current->nama << endl;
            cout << "Spesialis: " << current->spesialis << endl;
            cout << "Jenis Kelamin: " << current->jeniskelamin << endl;
            cout << endl;
            current = current->next;
        }
        
        cout << "Rekap Data Dokter Berdasarkan Spesialis:" << endl;
        for (const auto& entry : rekapSpesialis) {
            cout << "Spesialis " << entry.first << ": " << entry.second << " dokter" << endl;
            
        }
        cout << endl;
    }
}

// -- MENU TAMBAHAN --

void rekapDataPasien() {
    if (headDataDiri == nullptr) {
        cout << "Tidak ada data pasien yang tersimpan." << endl;
    } else {
        float totalBerat = 0.0, totalTinggi = 0.0;
        int jumlahPasien = 0;

        DataDiri* current = headDataDiri;

        while (current != nullptr) {
            totalBerat += current->beratbadan_pasien;
            totalTinggi += current->tinggibadan_pasien;
            jumlahPasien++;

            current = current->next;
        }

        float rataBerat = totalBerat / jumlahPasien;
        float rataTinggi = totalTinggi / jumlahPasien;

        cout << "Rekap Data Pasien:" << endl;
        cout << "Jumlah Pasien: " << jumlahPasien << endl;
        cout << "Rata-rata Berat Badan Pasien: " << rataBerat << endl;
        cout << "Rata-rata Tinggi Badan Pasien: " << rataTinggi << endl;
    }
}

string obatUntukKeluhan(const string& keluhan_pasien) {
    if (keluhan_pasien == "Gigi") {
        return "Paracetamol";
    } else if (keluhan_pasien == "Panas") {
        return "Obat Paracetamol";
    } else if (keluhan_pasien == "Panas") {
        return "Obat Paracetamol";
    } else if (keluhan_pasien == "Demam") {
        return "Obat Paracetamol";
    } else if (keluhan_pasien == "demam") {
        return "Obat Paracetamol";
    } else if (keluhan_pasien == "Batuk") {
        return "Obat Bisolvon";
    } else if (keluhan_pasien == "batuk") {
        return "Obat Bisolvon";
    } else if (keluhan_pasien == "Pilek") {
        return "Obat Ultraflu";
    } else if (keluhan_pasien == "pilek") {
        return "Obat Ultraflu";
    } else if (keluhan_pasien == "sakit hati") {
        return "Obat nya Dia";
    } else if (keluhan_pasien == "Sakit hati") {
        return "Obat nya Dia";
    } else if (keluhan_pasien == "Sakit gigi") {
        return "Obat Cataflam";
    } else if (keluhan_pasien == "gigi") {
        return "Obat Cataflam";
    } else {
        return "keluhan pasien tidak dikenal";
    }
}

// -- MENU QUEUE --
void Enque(pasien **Front, pasien **Rear){
        pasien *nodeBaru = newpasien();
        if (*Front == NULL){
            *Front = nodeBaru;
        }else{
            (*Rear)->next = nodeBaru;
        }
        *Rear = nodeBaru;
}

void deque(pasien **Front, pasien **Rear){
        if(*Front == NULL){
            cout << "Tidak ada antrian" << endl;
            return;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Memproses antrian..." << endl;
        pasien *temp = *Front;
        *Front = (*Front)->next;
        delete temp;
}

void display(pasien *Front, pasien *Rear, int cek){
        if (Front == NULL){
            cout << "Tidak ada Antrian" << endl;
            return;
        }
        if (cek == 1){
            while (Front != NULL){
                cout << "Id Pasien Terdaftar : " << Front->ps.id_pasienterdaftar << endl;
                cout << "Nama Pasien Terdaftar   : " << Front->ps.nama_pasienterdaftar << endl;
                cout << "Tanggal Kunjungan Pasien Terdaftar  : " << Front->ps.tanggalkunjungan_pasienterdaftar<< endl;
                cout << "============================" << endl << endl;
                Front = Front->next;
            }
        }else 
        if (cek == 2){
            cout << "Data Paling Depan" << endl;
            cout << "Id Pasien Terdaftar : " << Front->ps.id_pasienterdaftar << endl;
            cout << "Nama Pasien Terdaftar   : " << Front->ps.nama_pasienterdaftar<< endl;
            cout << "Tanggal Kunjungan Pasien Terdaftar  : " << Front->ps.tanggalkunjungan_pasienterdaftar<< endl;
            cout << "============================" << endl << endl;

        }else
        if(cek == 3){
            cout << "Data Paling Akhir" << endl;
            cout << "Id Pasien Terdaftar : " << Rear->ps.id_pasienterdaftar << endl;
            cout << "Nama Pasien Terdaftar   : " << Rear->ps.nama_pasienterdaftar<< endl;
            cout << "Tanggal Kunjungan Pasien Terdaftar  : " << Rear->ps.tanggalkunjungan_pasienterdaftar<< endl;
            cout << "============================" << endl << endl;

        }
        cout << endl;
        
}

// --- Buat Tampilan ---
// buat user
void tampilkan(){
    string ulang;
	int selected = 1;
	while (true) {
		draw(selected);
		int keyPressed = _getch();
		if (keyPressed == 224) {
			keyPressed = _getch();
			switch (keyPressed) {
				case 72: 
					selected--;
					if (selected < 1) {
						selected = 2;
					}
					break;
				case 80: 
					selected++;
					if (selected > 2) {
						selected = 1;
					}
					break;
			}
			draw(selected);
		} else if (keyPressed == 13) { 
			system("cls");
			switch (selected) {
				case 1:
					do {
					    ShowDataDiri();
						cout << " " << endl;
						this_thread::sleep_for(chrono::milliseconds(2000));
						cout << "Tekan Apa Saja Untuk Kembali"; getch();
						break;
						cout<<"\033[1;32m" ;
					}while (ulang == "n");
					tampilkan();
				case 2:
					return;	
			}
		}	
	}
}

// buat admin
void tampilkan2(){
    string ulang;
	int selected2 = 1;
	while (true) {
		draw(selected2);
		int keyPressed = _getch();
		if (keyPressed == 224) {
			keyPressed = _getch();
			switch (keyPressed) {
				case 72: 
					selected2--;
					if (selected2 < 1) {
						selected2 = 2;
					}
					break;
				case 80: 
					selected2++;
					if (selected2 > 2) {
						selected2 = 1;
					}
					break;
			}
			draw(selected2);
		} else if (keyPressed == 13) { 
			system("cls");
			switch (selected2) {
				case 1:
					do {
					    ShowDokter();
						cout << " " << endl;
						this_thread::sleep_for(chrono::milliseconds(2000));
						cout << "Tekan Apa Saja Untuk Kembali"; getch();
						break;
						cout<<"\033[1;32m" ;
					}while (ulang == "n");
					tampilkan2();
				case 2:
					return;	
			}
		}	
	}
}

// ( buat menu tambahan )
void tampilkan3(){
    string ulang;
	int selected3 = 1;
	while (true) {
		draw3(selected3);
		int keyPressed = _getch();
		if (keyPressed == 224) {
			keyPressed = _getch();
			switch (keyPressed) {
				case 72: 
					selected3--;
					if (selected3 < 1) {
						selected3 = 2;
					}
					break;
				case 80: 
					selected3++;
					if (selected3 > 2) {
						selected3 = 1;
					}
					break;
			}
			draw3(selected3);
		} else if (keyPressed == 13) { 
			system("cls");
			switch (selected3) {
				case 1:
					do {
					    tampilkanRekapDataDokter();
						cout << " " << endl;
						this_thread::sleep_for(chrono::milliseconds(2000));
						cout << "Tekan Apa Saja Untuk Kembali"; getch();
						break;
						cout<<"\033[1;32m" ;
					}while (ulang == "n");
					tampilkan3();
				case 2:
					return;	
			}
		}	
	}
}
void Tampilkanpasien(){
    string ulang;
	int selected3 = 1;
	while (true) {
		draw2(selected3);
		int keyPressed = _getch();
		if (keyPressed == 224) {
			keyPressed = _getch();
			switch (keyPressed) {
				case 72: 
					selected3--;
					if (selected3 < 1) {
						selected3 = 3;
					}
					break;
				case 80: 
					selected3++;
					if (selected3 > 3) {
						selected3 = 1;
					}
					break;
			}
			draw2(selected3);
		} else if (keyPressed == 13) { 
			system("cls");
			switch (selected3) {
				case 1:
					do {
					     rekapDataPasien();
						cout << " " << endl;
						this_thread::sleep_for(chrono::milliseconds(2000));
						cout << "Tekan Apa Saja Untuk Kembali"; getch();
						break;
						cout<<"\033[1;32m" ;
					}while (ulang == "n");
					Tampilkanpasien();
				case 2:
						ShowDataDiri();
                        
						this_thread::sleep_for(chrono::milliseconds(1000));
						cout << "Tekan Apa Saja Untuk Kembali"; getch();
						break;
						cout<<"\033[1;32m" ;
                case 3:
					return;	
			}
		}	
	}
}
void tampilkankeluhan(){
    string ulang;
    string keluhan_pasien;
	int selectedk = 1;
	while (true) {
		drawkeluhan(selectedk);
		int keyPressed = _getch();
		if (keyPressed == 224) {
			keyPressed = _getch();
			switch (keyPressed) {
				case 72: 
					selectedk--;
					if (selectedk < 1) {
						selectedk = 2;
					}
					break;
				case 80: 
					selectedk++;
					if (selectedk > 2) {
						selectedk = 1;
					}
					break;
			}
			drawkeluhan(selectedk);
		} else if (keyPressed == 13) { 
			system("cls");
			switch (selectedk) {
				case 1:
					do {
					    cout << "Masukkan keluhan pasien: ";
                        cin >> keluhan_pasien;
                        cout << "Obat yang direkomendasikan: " << obatUntukKeluhan(keluhan_pasien) << endl;
						cout << " " << endl;
						this_thread::sleep_for(chrono::milliseconds(2000));
						cout << "Tekan Apa Saja Untuk Kembali"; getch();
						break;
						cout<<"\033[1;32m" ;
					}while (ulang == "n");
					tampilkankeluhan();
				case 2:
					return;	
			}
		}	
	}
}

// -------- MENU QUEUE --------
void MenuQueue(DataDiri* head, pasien * &FRONT, pasien * &REAR) {
    int selectedadmin = 1;

     while (true) {
				drawadmin2(selectedadmin);
				int keyPressed = _getch();
				if (keyPressed == 224) {
					keyPressed = _getch();
					switch (keyPressed) {
						case 72: 
							selectedadmin--;
							if (selectedadmin < 1) {
								selectedadmin = 6;
							}
							break;
						case 80: 
							selectedadmin++;
							if (selectedadmin > 6) {
								selectedadmin = 1;
							}
							break;
					}
					drawadmin2(selectedadmin);
				} else if (keyPressed == 13) { 
					system("cls");
					switch (selectedadmin) {
						case 1:
                            Enque(&FRONT, &REAR);
                            this_thread::sleep_for(chrono::milliseconds(2000));
                            cout << "Tekan Apa Saja Untuk Kembali"; getch();
                            break;
                            cout<<"\033[1;32m" ;
                            
                        case 2:
                            deque(&FRONT, &REAR);
                            this_thread::sleep_for(chrono::milliseconds(2000));
                            cout << "Tekan Apa Saja Untuk Kembali"; getch();
                            break;
                            cout<<"\033[1;32m" ;
                            // pop(&Bottom, &TOP);
                        case 3:
                            display(FRONT, REAR, 2);
                            this_thread::sleep_for(chrono::milliseconds(2000));
                            cout << "Tekan Apa Saja Untuk Kembali"; getch();
                            break;
                            cout<<"\033[1;32m" ;
                            // display(Bottom, 2, TOP);
                           
                        case 4:
                            display(FRONT, REAR, 3);
                            this_thread::sleep_for(chrono::milliseconds(2000));
                            cout << "Tekan Apa Saja Untuk Kembali"; getch();
                            break;
                            cout<<"\033[1;32m" ;
                            // display(Bottom, 1, TOP);
                         
                        case 5:
                            display(FRONT, REAR, 1);
                            this_thread::sleep_for(chrono::milliseconds(2000));
                            cout << "Tekan Apa Saja Untuk Kembali"; getch();
                            break;
                            cout<<"\033[1;32m" ;
                        case 6:
                            return;
                    }
				}
			}  
}

// -------- MENU PASIEN DAN ADMIN --------
void MenuPasien(DataDiri *head, pasien * &FRONT, pasien * &REAR) {
    const int MAX_DATA = 100;
    DataDiri daftarDataDiri[MAX_DATA];
    DataDokter *dokterHead = dynamic_cast<DataDokter *>(dokterHead);
    string keluhan_pasien;
    int selecteduser = 1;

     while (true) {
				drawuser(selecteduser);
				int keyPressed = _getch();
				if (keyPressed == 224) {
					keyPressed = _getch();
					switch (keyPressed) {
						case 72: 
							selecteduser--;
							if (selecteduser < 1) {
								selecteduser = 9;
							}
							break;
						case 80: 
							selecteduser++;
							if (selecteduser > 9) {
								selecteduser = 1;
							}
							break;
					}
					drawuser(selecteduser);
				} else if (keyPressed == 13) { 
					system("cls");
					switch (selecteduser) {
						case 1:
                            tampilkan(); // Memanggil fungsi untuk menampilkan data diri
                            break;
                        case 2:
                            AddDataDiri(); // Memanggil fungsi untuk menambah data diri
                            break;
                        case 3:
                            ShowDataDiri();
                            cout << "Masukkan ID Pasien yang akan diubah: ";
                            int idToEdit;

                            while (true) {
                                if (cin >> idToEdit) {
                                    break; // Keluar dari loop jika input adalah angka
                                } else {
                                    cout << "Masukkan ID yang benar (angka): ";
                                    cin.clear(); // Menghapus flag kesalahan pada input
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
                                }
                            }

                            UpdateDataDiri(idToEdit); // Memanggil fungsi untuk mengubah data pasien
                            break;

                        case 4:
                            ShowDataDiri();
                            cout << "Masukkan ID Pasien yang akan dihapus: ";
                            int idToDelete;
                            cin >> idToDelete;
                            DeleteDataDiri(idToDelete); // Memanggil fungsi untuk menghapus data pasien
                            break;
                        case 5:
                            tampilkanRekapDataDokter();
                            this_thread::sleep_for(chrono::milliseconds(2000));
                            cout << "Tekan Apa Saja Untuk Kembali"; getch();
                            break;
                            cout<<"\033[1;32m" ;
                        case 6:
                            SearchDokterByNama();
                            break;
                        case 7:
                            display(FRONT, REAR, 1);
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            cout << "Tekan Apa Saja Untuk Kembali"; getch();
                            break;
                            cout<<"\033[1;32m" ;
                        case 8:
                            tampilkankeluhan();
                            break;
                        case 9:
                            return;
                            default:
                            std::cout << "\033[2J\033[1;1H"; //pembersih konsol dari library iostream
                        break;
					}
				}
			}   
}

void MenuAdmin(DataDiri* head, pasien * &FRONT, pasien * &REAR) {
    DataDokter *dokterHead = dynamic_cast<DataDokter *>(dokterHead);
    int selectedOption = 1;
    
   while (true) {
				drawOptions(selectedOption);
				int keyPressed = _getch();
				if (keyPressed == 224) {
					keyPressed = _getch();
					switch (keyPressed) {
						case 72: 
							selectedOption--;
							if (selectedOption < 1) {
								selectedOption = 10;
							}
							break;
						case 80: 
							selectedOption++;
							if (selectedOption > 10) {
								selectedOption = 1;
							}
							break;
					}
					drawOptions(selectedOption);
				} else if (keyPressed == 13) { 
					system("cls");
					switch (selectedOption) {
						case 1:
                            tampilkan2();
                            break;
                        case 2:
                            AddDokter();
                            break;
                        case 3:
                            ShowDokter();
                            EditDokter();
                            break;
                        case 4:
                            ShowDokter();
                            DeleteDokter();
                            break;
                        case 5:
                             tampilkan3();
                            break;
                        case 6:
                            Tampilkanpasien();
                            break;
                         case 7:
                            tampilkankeluhan();
                            break;
                        case 8:
                            SearchByNama();  
                            break;
                        case 9:
                            MenuQueue(head, FRONT, REAR);         
                            break;
                        case 10:
                        return;

                        
					}
				}
            }     
}
// --------  Login --------
    // Fungsi untuk registrasi
    void registerUser(vector<string>& usernames, vector<string>& passwords) {
        string username, password;

        cout << "Masukkan nama pengguna baru: ";
        cin >> username;

        // Periksa apakah nama pengguna sudah ada
        for (int i = 0; i < usernames.size(); i++) {
            if (usernames[i] == username) {
                cout << "Nama pengguna sudah ada. Silakan pilih yang lain." << endl;
                return;
            }
        }

        cout << "Masukkan kata sandi baru: ";
        cin >> password;

        usernames.push_back(username);
        passwords.push_back(password);

        cout << "Registrasi berhasil. Silakan login." << endl;
    }

    // Fungsi untuk login
    bool loginUser(const vector<string>& usernames, const vector<string>& passwords, string& loggedInUser) {
        string username, password;
        int counter = 0;
        char repeat = 'y';
        while (repeat == 'y'){
            for (int i = 0; i < 10; i++);
            cout << "\033[2J\033[H";
            cout << "\033[1;32m";
            string intro[] = { 
                "==================================",
                "|""\033[1;37m"" Silahkan Login Terlebih Dahulu""\033[1;32m" " |",
                "=================================="
            };
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < intro[i].length(); j++) {
                    cout << intro[i][j];
                    cout.flush();
                    this_thread::sleep_for(chrono::milliseconds(15));
                }
                cout << endl;
                this_thread::sleep_for(chrono::milliseconds(50));
                
            }
            cout << "Masukkan Username : ";  cout<<"\033[1;37m" ; cout << "\033[2m";cin >> username;
            cout << "\033[0m";
            cout << "\033[1;32m";
            cout << "Masukkan Password : "; cout<<"\033[1;37m"; cout << "\033[2m";cin >> password;	
            cout << "\033[0m";	

            if (username == "admin" && password == "admin") {
                loggedInUser = "admin";
                string login[] = { 
				" Anda Berhasil Login "		
                };
                for (int a = 0; a< 1; a++) {
                    for (int z = 0; z < login[a].length(); z++) {
                        cout << login[a][z];
                        cout.flush();
                        this_thread::sleep_for(chrono::milliseconds(20));
                        cout << "\033[0m";
                    }
                    cout << "\033[1;31m";
                    cout << ">";
                    cout << endl;
                    this_thread::sleep_for(chrono::milliseconds(400));
                }
                return true;
            }
            else{
                counter++;
                cout << "\033[1;31m";
                // cout<<"Anda telah gagal "; cout <<"\033[1;37m"<< counter;cout <<"\033[1;31m";cout <<" kali\n";
                cout <<"\033[1;37m";
                    this_thread::sleep_for(chrono::milliseconds(1500));
                system("cls");
                if (counter == 3){
                    string outro[] = {
                        " Anda telah diKeluarkan...... "
                    };
                    for (int i = 0; i < 1; i++){
                        cout << "\033[1;31m";
                        cout << endl;
                        for (int j = 0; j < outro[i].length(); j++){
                            cout << outro[i][j];
                            cout.flush();
                            this_thread::sleep_for(chrono::milliseconds(30));	
                        }
                        cout << endl;
                        cout << "\033[1;37m";					
                    }
                    break;
                }
		    }	
            for (int i = 0; i < usernames.size(); i++) {
                if (usernames[i] == username && passwords[i] == password) {
                    loggedInUser = username;
                    return true;
                }
            }

                if (username == "surya" && password == "surya") {
            loggedInUser = "surya";
            return true;}
                if (username == "fasda" && password == "fasda") {
            loggedInUser = "fasda";
            return true;}
                if (username == "zek" && password == "zek") {
            loggedInUser = "zek";
            return true;
        }
    }


        return false;{}

    }

int main(){
     const int MAX_DATA = 100;  // batas maksimum jumlah data
        DataDiri daftarDataDiri[MAX_DATA];   // array of struct untuk menyimpan data DataDiri
        // vector<string> usernames = {"surya","fasda","jek"};
        // vector<string> passwords = {"surya","fasda","jek"};
        vector<string> usernames = {"admin"};
        vector<string> passwords = {"admin"};
        string loggedInUser;
        DataDiri *head = NULL;

	string command;
	string nama, pw;
	char repeat = 'y';
	int counter = 0;
	int selectedlog = 1;
    pasien *FRONT = NULL;
    pasien *REAR = NULL;

    cout << "\033[1;32m";
	string intro[] = { 
			"========================",
			"|""\033[1;37m"" Silahkan Pilih Menu""\033[1;32m" "  |",
			"========================"
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < intro[i].length(); j++) {
			cout << intro[i][j];
			cout.flush();
			this_thread::sleep_for(chrono::milliseconds(10));
		}
		cout << endl;
		this_thread::sleep_for(chrono::milliseconds(50));	
    }
	while (true) {
		drawlog(selectedlog);
		int keyPressed = _getch();
		if (keyPressed == 224) {
			keyPressed = _getch();
			switch (keyPressed) {
				case 72: 
					selectedlog--;
					if (selectedlog < 1) {
						selectedlog = 3;
					}
					break;
				case 80: 
					selectedlog++;
					if (selectedlog > 3) {
						selectedlog = 1;
					}
					break;
					}
			drawlog(selectedlog);
		} else if (keyPressed == 13) { 
			system("cls");
            
			switch (selectedlog) {
				case 1:
        
                        if (loginUser(usernames, passwords, loggedInUser)) {
    
                 
                            if(loggedInUser == "admin"){
                                MenuAdmin(head, FRONT, REAR);
                            }
                            else if(loggedInUser == "surya"){
                                MenuPasien(head, FRONT, REAR);
                            }
                            else{
                                MenuPasien(head, FRONT, REAR);
                            }
                        } 
                        else{
                            cout << endl;
                            
                        }
                        
                        break;
                    
				case 2:
					registerUser(usernames, passwords);
					break;
				case 3:
                
					string outro[] = {
						" Anda telah Keluar...... "
					};
					for (int i = 0; i < 1; i++){
						cout << "\033[1;31m";
						cout << endl;
						for (int j = 0; j < outro[i].length(); j++){
							cout << outro[i][j];
							cout.flush();
							this_thread::sleep_for(chrono::milliseconds(30));	
						}
						cout << endl;
						cout << "\033[1;37m";		
					}
				return false;
			}
		}
	}		
    return 0;
}

 