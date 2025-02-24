#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Motor {
    string nama;
    string platNomor;
    int hargaPerHari;
    bool tersedia;
};

struct Rental {
    string namaPenyewa;
    string kontak;
    int lamaHari;
    int indexMotor;
    bool aktif;
};

Motor daftarMotor[3] = {
    {"Honda Vario", "AB 1234 XY", 50000, true},
    {"Yamaha NMAX", "AB 5678 XY", 70000, true},
    {"Suzuki Satria", "AB 9101 XY", 60000, true}
};

Rental daftarRental[5];
int jumlahRental = 0;


void tampilkanMotorRekursif(int i) {
    if (i >= 3) return; 
    cout << left << setw(5) << i + 1
         << setw(15) << daftarMotor[i].nama
         << setw(12) << daftarMotor[i].platNomor
         << "Rp " << setw(8) << daftarMotor[i].hargaPerHari
         << (daftarMotor[i].tersedia ? "Tersedia" : "Disewa") << "\n";
    tampilkanMotorRekursif(i + 1); 
}

void tampilkanMotor() {
    cout << "\n=== Daftar Motor ===\n";
    cout << left << setw(5) << "No" << setw(15) << "Nama Motor" 
         << setw(12) << "Plat Nomor" << setw(12) << "Harga/Hari" << "Status\n";
    cout << "---------------------------------------------------------\n";
    tampilkanMotorRekursif(0);
}

void sewaMotor() {
    if (jumlahRental >= 5) {
        cout << "Maaf, semua slot penyewaan sudah penuh.\n";
        return;
    }

    tampilkanMotor();

    int pilih;
    cout << "\nPilih nomor motor yang ingin disewa: ";
    cin >> pilih;

    if (pilih < 1 || pilih > 3 || !daftarMotor[pilih - 1].tersedia) {
        cout << "Pilihan tidak valid atau motor sedang disewa.\n";
        return;
    }

    cout << "Masukkan nama penyewa: ";
    cin.ignore();
    getline(cin, daftarRental[jumlahRental].namaPenyewa);

    cout << "Masukkan kontak penyewa: ";
    getline(cin, daftarRental[jumlahRental].kontak);

    cout << "Masukkan lama sewa (hari): ";
    cin >> daftarRental[jumlahRental].lamaHari;

    daftarRental[jumlahRental].indexMotor = pilih - 1;
    daftarRental[jumlahRental].aktif = true;
    daftarMotor[pilih - 1].tersedia = false;
    jumlahRental++;

    cout << "Motor berhasil disewa oleh " << daftarRental[jumlahRental - 1].namaPenyewa << "!\n";
}

void tampilkanRental() {
    cout << "\n=== Daftar Penyewaan Aktif ===\n";
    if (jumlahRental == 0) {
        cout << "Belum ada penyewaan aktif.\n";
        return;
    }

    cout << left << setw(5) << "No" << setw(15) << "Nama Penyewa"
         << setw(15) << "Motor" << setw(10) << "Lama (hari)" << "\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < jumlahRental; i++) {
        if (daftarRental[i].aktif) {
            int idx = daftarRental[i].indexMotor;
            cout << left << setw(5) << i + 1
                 << setw(15) << daftarRental[i].namaPenyewa
                 << setw(15) << daftarMotor[idx].nama
                 << setw(10) << daftarRental[i].lamaHari << "\n";
        }
    }
}


int hitungBiaya(int hargaPerHari, int lamaHari) {
    if (lamaHari == 1) return hargaPerHari;  
    return hargaPerHari + hitungBiaya(hargaPerHari, lamaHari - 1);  
}

void kembalikanMotor() {
    if (jumlahRental == 0) {
        cout << "Tidak ada motor yang sedang disewa.\n";
        return;
    }

    tampilkanRental();

    int pilih;
    cout << "\nPilih nomor penyewaan yang akan dikembalikan: ";
    cin >> pilih;

    if (pilih < 1 || pilih > jumlahRental || !daftarRental[pilih - 1].aktif) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    int idxMotor = daftarRental[pilih - 1].indexMotor;
    int lamaHari = daftarRental[pilih - 1].lamaHari;
    int totalBiaya = hitungBiaya(daftarMotor[idxMotor].hargaPerHari, lamaHari);

    daftarMotor[idxMotor].tersedia = true;
    daftarRental[pilih - 1].aktif = false;

    cout << "\nMotor telah dikembalikan oleh " << daftarRental[pilih - 1].namaPenyewa << ".\n";
    cout << "Total biaya sewa: Rp " << totalBiaya << "\n";
}

int main() {
    int pilihan;

    do {
        cout << "\n=== Sistem Rental Motor ===\n";
        cout << "1. Tampilkan Daftar Motor\n";
        cout << "2. Sewa Motor\n";
        cout << "3. Tampilkan Daftar Penyewaan\n";
        cout << "4. Kembalikan Motor\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanMotor();
                break;
            case 2:
                sewaMotor();
                break;
            case 3:
                tampilkanRental();
                break;
            case 4:
                kembalikanMotor();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan layanan kami!\n";
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}
