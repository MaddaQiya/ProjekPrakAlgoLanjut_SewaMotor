#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Motor {
    string model;
    string platNomor;
    int hargaPerHari;
    bool tersedia;
};

struct Rental {
    string namaPenyewa;
    string platMotor;
    int lamaSewa;
};

const int JUMLAH_MOTOR = 20;
Motor daftarMotor[JUMLAH_MOTOR] = {
    {"Honda Vario", "AB1234CD", 50000, true},
    {"Yamaha NMAX", "AB2345DE", 70000, true},
    {"Honda Beat", "AB3456EF", 45000, true},
    {"Suzuki Nex", "AB4567FG", 40000, true},
    {"Yamaha Mio", "AB5678GH", 48000, true},
    {"Honda PCX", "AB6789IJ", 75000, true},
    {"Vespa Sprint", "AB7890JK", 90000, true},
    {"Kawasaki Ninja", "AB8901KL", 120000, true},
    {"Honda Supra", "AB9012LM", 50000, true},
    {"Yamaha Aerox", "AB0123MN", 65000, true},
    {"Honda Vario", "AB1122OP", 50000, true},
    {"Yamaha NMAX", "AB2233QR", 70000, true},
    {"Honda Beat", "AB3344ST", 45000, true},
    {"Suzuki Nex", "AB4455UV", 40000, true},
    {"Yamaha Mio", "AB5566WX", 48000, true},
    {"Honda PCX", "AB6677YZ", 75000, true},
    {"Vespa Sprint", "AB7788AA", 90000, true},
    {"Kawasaki Ninja", "AB8899BB", 120000, true},
    {"Honda Supra", "AB9900CC", 50000, true},
    {"Yamaha Aerox", "AB0011DD", 65000, true}
};


int transaksi[JUMLAH_MOTOR][2] = {0};
void tampilkanMotor() {
    cout << "\n=================================================================\n";
    cout << "| No |    Model Motor    |  Plat Nomor  | Harga/Hari | Status   |\n";
    cout << "=================================================================\n";
    for (int i = 0; i < JUMLAH_MOTOR; i++) {
        cout << "| " << setw(2) << i + 1 << " | " << setw(16) << daftarMotor[i].model << " | "
             << setw(12) << daftarMotor[i].platNomor << " | Rp" << setw(8) << daftarMotor[i].hargaPerHari
             << " | " << setw(8) << (daftarMotor[i].tersedia ? "Tersedia" : "Disewa") << " |\n";
    }
    cout << "================================================================= \n";
}

int sequentialSearch(string plat) {
    for (int i = 0; i < JUMLAH_MOTOR; i++) {
        if (daftarMotor[i].platNomor == plat) {
            return i;
        }
    }
    return -1;
}

int hitungBiaya(int hargaPerHari, int lama) {
    if (lama == 0) {
        return 0;
    }
    return hargaPerHari + hitungBiaya(hargaPerHari, lama - 1);
}

void sewaMotor() {
    string plat;
    int lama;
    cout << "\nMasukkan plat nomor motor yang ingin disewa: ";
    cin >> plat;
    cout << "Masukkan lama sewa (hari): ";
    cin >> lama;
    
    int index = sequentialSearch(plat);
    if (index != -1 && daftarMotor[index].tersedia) {
        daftarMotor[index].tersedia = false;
        transaksi[index][0] = lama;
        transaksi[index][1] = hitungBiaya(daftarMotor[index].hargaPerHari, lama);
        cout << "\nMotor dengan plat " << plat << " berhasil disewa selama " << lama << " hari!\n";
    } else {
        cout << "\nMotor tidak tersedia atau tidak ditemukan.\n";
    }
}

void kembalikanMotor() {
    string plat;
    cout << "\nMasukkan plat nomor motor yang dikembalikan: ";
    cin >> plat;
    
    int index = sequentialSearch(plat);
    if (index != -1 && !daftarMotor[index].tersedia) {
        daftarMotor[index].tersedia = true;
        cout << "\nMotor dengan plat " << plat << " berhasil dikembalikan.\n";
        cout << "Total biaya sewa: Rp" << transaksi[index][1] << "\n";
        transaksi[index][0] = 0;
        transaksi[index][1] = 0;
    } else {
        cout << "\nMotor tidak ditemukan atau belum disewa.\n";
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n========= SEWA MOTOR UHUY =========\n";
        cout << "1. Lihat daftar motor\n";
        cout << "2. Sewa motor\n";
        cout << "3. Kembalikan motor\n";
        cout << "4. Keluar\n";
        cout << "===================================\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tampilkanMotor();
                break;
            case 2:
                sewaMotor();
                break;
            case 3:
                kembalikanMotor();
                break;
            case 4:
                cout << "\nTerima kasih telah menggunakan layanan kami!\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }
    } while (pilihan != 4);
    
    return 0;
}
