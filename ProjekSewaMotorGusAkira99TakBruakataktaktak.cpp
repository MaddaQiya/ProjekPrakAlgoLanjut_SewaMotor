#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct Motor {
    string model;
    string platNomor;
    int hargaPerHari;
    bool tersedia;
    string penyewa;
    int lamaSewa;
};

const int MAX_MOTOR = 100;
Motor daftarMotor[MAX_MOTOR] = {
    {"Honda Vario 125", "AB1234CD", 50000, true},
    {"Yamaha NMAX 155", "AB2345DE", 70000, true},
    {"Honda Beat Street 110", "AB3456EF", 45000, true},
    {"Suzuki Nex II 115", "AB4567FG", 40000, true},
    {"Yamaha Mio S 125", "AB5678GH", 48000, true},
    {"Honda PCX 160", "AB6789IJ", 75000, true},
    {"Vespa Sprint 150", "AB7890JK", 90000, true},
    {"Kawasaki Ninja RR 150", "AB8901KL", 120000, true},
    {"Honda Supra X 125", "AB9012LM", 50000, true},
    {"Yamaha Aerox Turbo 155", "AB0123MN", 65000, true},
    {"Honda Scoopy Prestige 110", "AB1122OP", 53000, true},
    {"Yamaha Lexi S 125", "AB2233QR", 60000, true},
    {"Suzuki Satria FU 150", "AB3344ST", 62000, true},
    {"Vespa LX 125", "AB4455UV", 87000, true},
    {"Yamaha XSR 155", "AB5566WX", 95000, true},
    {"Honda Revo Fit 110", "AB6677YZ", 41000, true},
    {"Kawasaki W175 175", "AB7788AA", 100000, true},
    {"Honda CBR 150R", "AB8899BB", 110000, true},
    {"Yamaha R15 V4 155", "AB9900CC", 115000, true},
    {"Suzuki GSX R150", "AB0011DD", 108000, true}
};
int jumlahMotor = 20;

int ketersediaan[5][7] = {
    {1, 1, 0, 1, 1, 1, 0}, 
    {1, 1, 1, 1, 1, 1, 1}, 
    {0, 0, 0, 0, 0, 1, 1}, 
    {1, 1, 1, 1, 1, 0, 0}, 
    {1, 0, 1, 0, 1, 0, 1}  
};


////////////////////////////////////////////// Menu 3/////////////////////////////////////////////////////////
int cariMotor(string plat) {
    for (int i = 0; i < jumlahMotor; i++) {
        if (daftarMotor[i].platNomor == plat) return i;
    }
    return -1;
}

int binarySearch(string target) {
    int low = 0, high = jumlahMotor - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (daftarMotor[mid].platNomor == target) return mid;
        else if (daftarMotor[mid].platNomor < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
void urutkanPlatNomor() {
    for (int i = 0; i < jumlahMotor - 1; i++) {
        for (int j = i + 1; j < jumlahMotor; j++) {
            if (daftarMotor[i].platNomor > daftarMotor[j].platNomor) {
                swap(daftarMotor[i], daftarMotor[j]);
            }
        }
    }
    cout << "[INFO] Data telah diurutkan berdasarkan plat nomor (A-Z).\n";
}


void menuCariMotor() {
    int metode;
    cout << "\n====== Menu Pencarian Motor ======\n";
    cout << "1. Cari dengan Sequential Search\n";
    cout << "2. Cari dengan Binary Search (plat harus diurutkan)\n";
    cout << "Pilihan: ";
    cin >> metode;

    cin.ignore();
    string plat;
    cout << "Masukkan plat nomor (Tanpa Spasi): ";
    getline(cin, plat);

    int idx = -1;
    if (metode == 1) {
        idx = cariMotor(plat);
    } else if (metode == 2) {
    urutkanPlatNomor();
    idx = binarySearch(plat);
    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    if (idx != -1)
        cout << "Motor ditemukan: " << daftarMotor[idx].model << " (" << daftarMotor[idx].platNomor << ")\n";
    else
        cout << "Motor tidak ditemukan.\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////Menu 5////////////////////////////////////////////////////////
int hitungBiaya(int harga, int lama) {
    if (lama == 0) return 0;
    return harga + hitungBiaya(harga, lama - 1);
}

int estimasiPemasukan(int hari, int awal) {
    if (hari == 1) return awal;
    return awal + 50000 + estimasiPemasukan(hari - 1, awal + 50000);
}

int totalHargaDisewa(int idx) {
    if (idx < 0) return 0;
    return (!daftarMotor[idx].tersedia ? daftarMotor[idx].hargaPerHari : 0) + totalHargaDisewa(idx - 1);
}

int faktorial(int n) {
    if (n <= 1) return 1;
    return n * faktorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}


void menuPrediksi() {
    int pilihan;
    cout << "\n====== Menu Prediksi dan Simulasi ======\n";
    cout << "1. Total harga motor disewa\n";
    cout << "2. Estimasi pemasukan\n";
    cout << "3. Hitung Diskon Nama (Faktorial Panjang Nama)\n";
    cout << "4. Simulasi Bonus Loyalitas (Fibonacci Hari Sewa)\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    switch(pilihan) {
        case 1:
            cout << "Total harga motor disewa: Rp" << totalHargaDisewa(jumlahMotor - 1) << endl;
            break;
        case 2: {
            int hari;
            cout << "Masukkan jumlah hari: "; cin >> hari;
            if (jumlahMotor > 0)
                cout << "Estimasi pemasukan: Rp" << estimasiPemasukan(hari, daftarMotor[0].hargaPerHari) << endl;
            else
                cout << "Data kosong.\n";
            break;
        }
        case 3: {
            string nama;
            cin.ignore();
            cout << "Masukkan nama penyewa (Tanpa Spasi): ";
            getline(cin, nama);
            int diskon = faktorial(nama.length()) % 100;
            cout << "Diskon khusus berdasarkan nama: " << diskon << "%\n";
            break;
        }
        case 4: {
            int hari;
            cout << "Masukkan jumlah hari sewa: "; cin >> hari;
            int bonus = fibonacci(hari) * 100;
            if (bonus > 100000) bonus = 100000;
            cout << "Bonus loyalitas (estimasi): Rp" << bonus << endl;
            break;
        }
        default:
            cout << "Pilihan tidak valid.\n";
    }
}
/// /////////////////////////////////////////////////////////////////////////////////////////////////////

void diskon(Motor* m, int persen) {
    m->hargaPerHari = m->hargaPerHari * (100 - persen) / 100;
}

// Fungsi Menu
void tambahMotor() {
    if (jumlahMotor >= MAX_MOTOR) {
        cout << "Kapasitas maksimum tercapai.\n";
        return;
    }
    cin.ignore();
    cout << "\nMasukkan model motor: "; getline(cin, daftarMotor[jumlahMotor].model);
    cout << "Masukkan plat nomor: "; getline(cin, daftarMotor[jumlahMotor].platNomor);
    int harga;
    cout << "Masukkan harga sewa per hari (dalam ribuan, contoh 80 untuk 80.000): "; cin >> harga;
    daftarMotor[jumlahMotor].hargaPerHari = harga * 1000;
    daftarMotor[jumlahMotor].tersedia = true;
    daftarMotor[jumlahMotor].penyewa = "";
    daftarMotor[jumlahMotor].lamaSewa = 0;
    jumlahMotor++;
    cout << "Motor berhasil ditambahkan!\n";
}

void hapusMotor() {
    cin.ignore();
    string plat, alasan;
    cout << "Masukkan plat nomor motor yang ingin dihapus: "; getline(cin, plat);
    int idx = cariMotor(plat);
    if (idx != -1) {
        cout << "Masukkan alasan penghapusan (misal: kecelakaan, diservis, dll): ";
        getline(cin, alasan);
        for (int i = idx; i < jumlahMotor - 1; i++) {
            daftarMotor[i] = daftarMotor[i + 1];
        }
        jumlahMotor--;
        ofstream log("log_penghapusan.txt", ios::app);
        log << "Motor dengan plat " << plat << " dihapus. Alasan: " << alasan << "\n";
        log.close();
        cout << "Motor berhasil dihapus dari daftar.\n";
    } else {
        cout << "Motor tidak ditemukan.\n";
    }
}

void menuEditMotor() {
    int pilihan;
    cout << "\n--- Edit Daftar Motor ---\n";
    cout << "1. Tambah motor\n";
    cout << "2. Hapus motor\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    switch(pilihan) {
        case 1: tambahMotor(); break;
        case 2: hapusMotor(); break;
        default: cout << "Pilihan tidak valid.\n";
    }
}
/////////////////////////////////////////////// Menu 1 /////////////////////////////////////////////////////////
void tampilkanMotor() {
    cout << "\n============================================================================================\n";
    cout << "| No |           Model Motor            |  Plat Nomor  |  Harga/Hari  |      Status        |\n";
    cout << "============================================================================================\n";
    for (int i = 0; i < jumlahMotor; i++) {
        cout << "| " << setw(2) << i + 1 << " | " << left << setw(33) << daftarMotor[i].model
             << " | " << setw(12) << daftarMotor[i].platNomor
             << " | Rp" << right << setw(10) << daftarMotor[i].hargaPerHari
             << " | " << left << setw(17) << (daftarMotor[i].tersedia ? "Available" : "Rented Out") << " |\n";
    }
    cout << "============================================================================================\n";
}


void tampilkanMotorTersedia() {
    cout << "\n========================================================================\n";
    cout << "| No |           Model Motor            |  Plat Nomor  |  Harga/Hari   |\n";
    cout << "========================================================================\n";
    int no = 1;
    for (int i = 0; i < jumlahMotor; i++) {
        if (daftarMotor[i].tersedia) {
            cout << "| " << setw(2) << no++ << " | " << left << setw(33) << daftarMotor[i].model
                 << " | " << setw(12) << daftarMotor[i].platNomor
                 << " | Rp" << right << setw(10) << daftarMotor[i].hargaPerHari << " |\n";
        }
    }
    if (no == 1) cout << "| Tidak ada motor yang tersedia saat ini.                                                  |\n";
    cout << "========================================================================\n";
}


void tampilkanMotorDisewa() {
    cout << "\n======================================================================================================\n";
    cout << "| No |           Model Motor            |  Plat Nomor  |  Harga/Hari  |     Penyewa     | Lama Sewa  |\n";
    cout << "======================================================================================================\n";
    int no = 1;
    for (int i = 0; i < jumlahMotor; i++) {
        if (!daftarMotor[i].tersedia) {
            cout << "| " << setw(2) << no++ << " | " << left << setw(33) << daftarMotor[i].model
                 << " | " << setw(12) << daftarMotor[i].platNomor
                 << " | Rp" << right << setw(10) << daftarMotor[i].hargaPerHari
                 << " | " << left << setw(15) << daftarMotor[i].penyewa
                 << " | " << right << setw(9) << daftarMotor[i].lamaSewa << " |\n";
        }
    }
    if (no == 1) cout << "| Semua motor tersedia, tidak ada yang sedang disewa.                                                |\n";
    cout << "======================================================================================================\n";
}

void bubbleSort(bool ascending = true) {
    for (int i = 0; i < jumlahMotor - 1; i++) {
        for (int j = 0; j < jumlahMotor - i - 1; j++) {
            if ((ascending && daftarMotor[j].hargaPerHari > daftarMotor[j + 1].hargaPerHari) ||
                (!ascending && daftarMotor[j].hargaPerHari < daftarMotor[j + 1].hargaPerHari)) {
                swap(daftarMotor[j], daftarMotor[j + 1]);
            }
        }
    }
}


void insertionSort(bool ascending = true) {
    for (int i = 1; i < jumlahMotor; i++) {
        Motor key = daftarMotor[i];
        int j = i - 1;
        while (j >= 0 && ((ascending && daftarMotor[j].hargaPerHari > key.hargaPerHari) ||
                          (!ascending && daftarMotor[j].hargaPerHari < key.hargaPerHari))) {
            daftarMotor[j + 1] = daftarMotor[j];
            j--;
        }
        daftarMotor[j + 1] = key;
    }
}

void selectionSort(bool ascending = true) {
    for (int i = 0; i < jumlahMotor - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jumlahMotor; j++) {
            if ((ascending && daftarMotor[j].hargaPerHari < daftarMotor[idx].hargaPerHari) ||
                (!ascending && daftarMotor[j].hargaPerHari > daftarMotor[idx].hargaPerHari)) {
                idx = j;
            }
        }
        swap(daftarMotor[i], daftarMotor[idx]);
    }
}

void shellSort(bool ascending = true) {
    for (int gap = jumlahMotor / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jumlahMotor; i++) {
            Motor temp = daftarMotor[i];
            int j;
            for (j = i; j >= gap &&
                ((ascending && daftarMotor[j - gap].hargaPerHari > temp.hargaPerHari) ||
                 (!ascending && daftarMotor[j - gap].hargaPerHari < temp.hargaPerHari)); j -= gap) {
                daftarMotor[j] = daftarMotor[j - gap];
            }
            daftarMotor[j] = temp;
        }
    }
}

int partition(int low, int high, bool ascending) {
    int pivot = daftarMotor[high].hargaPerHari;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if ((ascending && daftarMotor[j].hargaPerHari < pivot) ||
            (!ascending && daftarMotor[j].hargaPerHari > pivot)) {
            i++;
            swap(daftarMotor[i], daftarMotor[j]);
        }
    }
    swap(daftarMotor[i + 1], daftarMotor[high]);
    return i + 1;
}

void quickSort(int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition(low, high, ascending);
        quickSort(low, pi - 1, ascending);
        quickSort(pi + 1, high, ascending);
    }
}

void algoritmasorting(){
    int metode;
    cout << "\n--- Pilih Algoritma Sorting ---\n";
cout << "1. Bubble Sort Ascending\n";
cout << "2. Bubble Sort Descending\n";
cout << "3. Insertion Sort Ascending\n";
cout << "4. Insertion Sort Descending\n";
cout << "5. Selection Sort Ascending\n";
cout << "6. Selection Sort Descending\n";
cout << "7. Shell Sort Ascending\n";
cout << "8. Shell Sort Descending\n";
cout << "9. Quick Sort Ascending\n";
cout << "10. Quick Sort Descending\n";
cout << "Pilih Metode (1-10) : "; 
    cin >> metode;
    switch(metode) {
    case 1: bubbleSort(true); break;
    case 2: bubbleSort(false); break;
    case 3: insertionSort(true); break;
    case 4: insertionSort(false); break;
    case 5: selectionSort(true); break;
    case 6: selectionSort(false); break;
    case 7: shellSort(true); break;
    case 8: shellSort(false); break;
    case 9: quickSort(0, jumlahMotor - 1, true); break;
    case 10: quickSort(0, jumlahMotor - 1, false); break;
    default: cout << "Pilihan tidak valid.\n"; return;
}

    cout << "Data berhasil diurutkan dengan algoritma pilihan.\n";
    tampilkanMotor();
}

void menuTampilkanMotor() {
    int pilihan;
    cout << "\n--- Tampilkan Daftar Motor ---\n";
    cout << "1. Semua motor\n";
    cout << "2. Hanya yang tersedia\n";
    cout << "3. Hanya yang disewa\n";
    cout << "4. Urutkan berdasarkan harga dengan algoritma tertentu\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    switch(pilihan) {
        case 1: tampilkanMotor(); break;
        case 2: tampilkanMotorTersedia(); break;
        case 3: tampilkanMotorDisewa(); break;
        case 4: algoritmasorting(); break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// //////////////////////////////////// Menu 4 //////////////////////////////////////////////////////////
void diskonMotor() {
    cin.ignore();
    string input;
    int persen;
    cout << "Masukkan model motor atau plat (bagian dari nama/plat): "; getline(cin, input);
    cout << "Masukkan besar diskon (persen): "; cin >> persen;
    bool found = false;
    for (int i = 0; i < jumlahMotor; i++) {
        if (daftarMotor[i].model.find(input) != string::npos || daftarMotor[i].platNomor.find(input) != string::npos) {
            diskon(&daftarMotor[i], persen);
            found = true;
        }
    }
    if (found) cout << "Diskon berhasil diberikan.\n";
    else cout << "Tidak ada motor yang cocok ditemukan.\n";
}

void sewaMotor() {
    string plat, nama;
    int lama;
    cin.ignore();
    cout << "Masukkan plat motor(Tanpa Spasi): "; getline(cin, plat);
    int idx = cariMotor(plat);
    if (idx != -1 && daftarMotor[idx].tersedia) {
        cout << "Masukkan nama penyewa: "; getline(cin, nama);
        cout << "Lama sewa (hari): "; cin >> lama;
        daftarMotor[idx].tersedia = false;
        daftarMotor[idx].penyewa = nama;
        daftarMotor[idx].lamaSewa = lama;
        int biaya = hitungBiaya(daftarMotor[idx].hargaPerHari, lama);

        ofstream log("log_transaksi.txt", ios::app);
        log << nama << ", " << plat << ", " << lama << " hari, Rp" << biaya << "\n";
        log.close();

        cout << "Sewa berhasil! Total biaya: Rp" << biaya << endl;
    } else {
        cout << "Motor tidak tersedia atau tidak ditemukan.\n";
    }
}

void kembalikanMotor() {
    string plat;
    cin.ignore();
    cout << "Masukkan plat motor yang dikembalikan(Tanpa Spasi): "; getline(cin, plat);
    int idx = cariMotor(plat);
    if (idx != -1 && !daftarMotor[idx].tersedia) {
        cout << "Motor dikembalikan oleh: " << daftarMotor[idx].penyewa << endl;
        int biaya = hitungBiaya(daftarMotor[idx].hargaPerHari, daftarMotor[idx].lamaSewa);
        cout << "Total biaya sewa: Rp" << biaya << endl;
        daftarMotor[idx].tersedia = true;
        daftarMotor[idx].penyewa = "";
        daftarMotor[idx].lamaSewa = 0;
    } else {
        cout << "Motor tidak ditemukan atau belum disewa.\n";
    }
}

void menuSewa() {
    int pilihan;
    cout << "\n--- Menu Sewa ---\n";
    cout << "1. Sewa motor\n";
    cout << "2. Kembalikan motor\n";
    cout << "3. Diskon Motor\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    switch(pilihan) {
        case 1: sewaMotor(); break;
        case 2: kembalikanMotor(); break;
        case 3: diskonMotor(); break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////// Menu 6 ////////////////////////////////////////////////////////////////////////////
void simpanKeFile() {
    ofstream file("data_motor.txt");
    for (int i = 0; i < jumlahMotor; i++) {
        file << daftarMotor[i].model << ";" << daftarMotor[i].platNomor << ";" << daftarMotor[i].hargaPerHari << ";"
             << daftarMotor[i].tersedia << ";" << daftarMotor[i].penyewa << ";" << daftarMotor[i].lamaSewa << "\n";
    }
    file.close();
    cout << "Data berhasil disimpan.\n";
}

void bacaDariFile() {
    ifstream file("data_motor.txt");
    jumlahMotor = 0;
    while (getline(file, daftarMotor[jumlahMotor].model, ';') &&
           getline(file, daftarMotor[jumlahMotor].platNomor, ';') &&
           file >> daftarMotor[jumlahMotor].hargaPerHari && file.get() &&
           file >> daftarMotor[jumlahMotor].tersedia && file.get() &&
           getline(file, daftarMotor[jumlahMotor].penyewa, ';') &&
           file >> daftarMotor[jumlahMotor].lamaSewa) {
        file.get();
        jumlahMotor++;
    }
    file.close();
    cout << "Data berhasil dibaca dari file.\n";
    tampilkanMotor();
}

void tampilkanLogTransaksi() {
    ifstream log("log_transaksi.txt");
    if (!log) {
        cout << "\nBelum ada data transaksi.\n";
        return;
    }

    string baris;
    cout << "\n=========== Riwayat Transaksi ==========\n";
    while (getline(log, baris)) {
        cout << baris << endl;
    }
    log.close();
    cout << "========================================\n";
}

void hapusFile() {
    string namaFile;
    cin.ignore();
    cout << "Masukkan nama file yang ingin dihapus: ";
    getline(cin, namaFile);

    if (remove(namaFile.c_str()) == 0) {
        cout << "[INFO] File berhasil dihapus.\n";
    } else {
        cout << "[ERROR] Gagal menghapus file. Pastikan file ada.\n";
    }
}

void renameFile() {
    string lama, baru;
    cin.ignore();
    cout << "Masukkan nama file lama (namafile.tipefile/namafile.txt): ";
    getline(cin, lama);
    cout << "Masukkan nama file baru (namafile.tipefile/namafile.txt): ";
    getline(cin, baru);

    if (rename(lama.c_str(), baru.c_str()) == 0) {
        cout << "[INFO] File berhasil diubah namanya.\n";
    } else {
        cout << "[ERROR] Gagal mengganti nama file. Pastikan file lama ada.\n";
    }
}

void menuManajemenData() {
    int pilihan;
    cout << "\n====== Manajemen Data ======\n";
    cout << "1. Simpan data ke file\n";
    cout << "2. Muat data dari file\n";
    cout << "3. Tampilkan log transaksi\n";
    cout << "4. Hapus file\n";
    cout << "5. Ganti nama file\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    switch(pilihan) {
        case 1: simpanKeFile(); break;
        case 2: bacaDariFile(); tampilkanMotor(); break;
        case 3: tampilkanLogTransaksi(); break;
        case 4: hapusFile(); break;
        case 5: renameFile(); break;
        default: cout << "Pilihan tidak valid.\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////// Menu 7//////////////////////////////////////////
void tampilkanKetersediaan() {
    cout << "\n--- Simulasi Ketersediaan Motor (Array 2D) ---\n";
    string hari[] = {"Sen", "Sel", "Rab", "Kam", "Jum", "Sab", "Min"};
    cout << setw(12) << "Motor/Hari";
    for (int i = 0; i < 7; i++) cout << setw(6) << hari[i];
    cout << endl;

    for (int i = 0; i < 5; i++) {
        cout << setw(12) << "Motor " + to_string(i + 1);
        for (int j = 0; j < 7; j++) {
            cout << setw(6) << (ketersediaan[i][j] ? "Y" : "N");
        }
        cout << endl;
    }
}
string servis[2][12][4];
void isiJadwalServis() {
    // Motor 1 diservis di bulan Maret (2) & September (8)
    servis[0][2][1] = "Service";
    servis[0][8][2] = "Service";

    // Motor 2 diservis di bulan Januari (0) & Juli (6)
    servis[1][0][2] = "Service";
    servis[1][6][1] = "Service";

    // Sisanya kosong
    for (int m = 0; m < 2; m++) {
        for (int b = 0; b < 12; b++) {
            for (int w = 0; w < 4; w++) {
                if (servis[m][b][w].empty())
                    servis[m][b][w] = "-";
            }
        }
    }
}


void tampilkanJadwalServisTahunan() {
    string namaBulan[] = {
        "Jan", "Feb", "Mar", "Apr", "Mei", "Jun",
        "Jul", "Agu", "Sep", "Okt", "Nov", "Des"
    };

    cout << "\n--- Jadwal Servis Tahunan (Array 3D) ---\n";
    for (int m = 0; m < 2; m++) {
        cout << "\nMotor " << m + 1 << ":\n";
        for (int b = 0; b < 12; b++) {
            cout << namaBulan[b] << ": ";
            for (int w = 0; w < 4; w++) {
                cout << setw(10) << servis[m][b][w];
            }
            cout << endl;
        }
    }
}

void menuJadwalServis() {
    int sub;
            cout << "\n--- Simulasi Jadwal ---\n";
            cout << "1. Ketersediaan Mingguan (Array 2D)\n";
            cout << "2. Jadwal Servis Tahunan (Array 3D)\n";
            cout << "Pilihan: ";
            cin >> sub;
            if (sub == 1) tampilkanKetersediaan();
            else if (sub == 2){
                isiJadwalServis();
                tampilkanJadwalServisTahunan();
}
            else cout << "Pilihan tidak valid.\n";
        }

//////////////////////////////////////////////////////////////////////////////

/// ///////////////////////////// Menu 8 /////////////////////////////////////////

void pointerKeArray() {
    int harga[] = {50000, 60000, 70000, 80000, 90000};
    int* ptr = harga;

    cout << "\n--- Pointer ke Array ---\n";
    for (int i = 0; i < 5; i++) {
        cout << "Harga ke-" << i + 1 << " = Rp" << *(ptr + i) << endl;
    }
}

void pointerKeString() {
    int index;
    cout << "\n--- Pointer ke String (dari Array) ---\n";
    cout << "Pilih nomor motor (1 - " << jumlahMotor << "): ";
    cin >> index;
    if (index < 1 || index > jumlahMotor) {
        cout << "Nomor motor tidak valid.\n";
        return;
    }

    string* ptr = &daftarMotor[index - 1].model;
    cout << "Model Motor [" << index << "] = " << *ptr << endl;
    cout << "(Data ini berasal dari daftarMotor[" << index - 1 << "].model)\n";
}



void pointerKePointer() {
    int harga = 100000;
    int* ptr = &harga;
    int** ptrptr = &ptr;

    cout << "\n--- Pointer ke Pointer ---\n";
    cout << "Harga sewa motor disimpan dalam variabel.\n";

    cout << "Langkah 1: Akses langsung         = Rp" << harga << endl;
    cout << "Langkah 2: Akses melalui pointer  = Rp" << *ptr << endl;
    cout << "Langkah 3: Akses lewat pointer ke pointer = Rp" << **ptrptr << endl;

    cout << "\nPenjelasan:\n";
    cout << "- Pointer (ptr) menunjuk ke variabel harga.\n";
    cout << "- Pointer ke pointer (ptrptr) menunjuk ke ptr.\n";
    cout << "- Semua cara tersebut mengakses nilai yang sama yaitu 100000.\n";
}


void menuSimulasiPointer() {
    int pilihan;
    char ulang;

    do {
        cout << "\n====== Simulasi Pointer ======\n";
        cout << "1. Pointer ke Array\n";
        cout << "2. Pointer ke String\n";
        cout << "3. Pointer ke Pointer\n";
        cout << "4. Kembali ke Menu Utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: pointerKeArray(); break;
            case 2: pointerKeString(); break;
            case 3: pointerKePointer(); break;
            case 4: return;
            default:
                cout << "Pilihan tidak valid.\n";
                continue;
        }

        cout << "\nKembali ke menu pointer? (y/n): ";
        cin >> ulang;

    } while (ulang == 'y' || ulang == 'Y');
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool kembaliKeMenu() {
    char jawab;
    cout << "\nKembali ke menu utama? (y/n): ";
    cin >> jawab;
    return (jawab == 'y' || jawab == 'Y');
}


int main() {
    int pilihan;
    do {
    cout << "\n========= SEWA MOTOR GUS AKIRA 99 =========\n";
    cout << "1. Tampilkan Daftar Motor\n";
    cout << "2. Edit Daftar Motor\n";
    cout << "3. Cari Motor (Plat Nomor)\n";
    cout << "4. Sewa / Kembalikan Motor\n";
    cout << "5. Prediksi\n";
    cout << "6. Manajemen Data\n";
    cout << "7. Jadwal Servis\n";
    cout << "8. Simulasi Pointer\n";
    cout << "9. Keluar\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1: menuTampilkanMotor(); break;
        case 2: menuEditMotor(); break;
        case 3: menuCariMotor(); break;
        case 4: menuSewa(); break;
        case 5: menuPrediksi(); break;
        case 6: menuManajemenData(); break;
        case 7: menuJadwalServis();break;
        case 8: menuSimulasiPointer(); break;
        case 9: cout << "Terima kasih Telah Menggunakan Program Sewa Motor Gus Akira 99\n"; break;
        default: cout << "Pilihan tidak valid.\n";
    }

    if (pilihan != 9 && !kembaliKeMenu()) break;
    } while (pilihan != 9);

    return 0;
}
