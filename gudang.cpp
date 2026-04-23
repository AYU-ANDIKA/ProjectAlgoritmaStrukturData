#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
using namespace std;


//         STRUKTUR DATA (LINKED LIST)

struct barang {
    int id;
    char nama[50];
    int stok;
    float harga;
    
    barang *next;
};


//            POINTER GLOBAL

barang *head = NULL;


//              TAMPILAN MENU

void garis() {
    cout << setfill('-') << setw(65) << "" << endl;
    cout << setfill(' ');
}

void menu() {
    garis();
    cout << "       SISTEM MANAJEMEN LOGISTIK & GUDANG" << endl;
    garis();
    cout << "  1. Tambah Barang" << endl;
    cout << "  2. Tampilkan Semua Barang" << endl;
    cout << "  3. Cari Barang" << endl;
    cout << "  4. Sorting Barang" << endl;
    cout << "  5. Transaksi (Keluar/Masuk Stok)" << endl;
    cout << "  6. Hapus Barang" << endl;
    cout << "  7. Simpan ke File" << endl;
    cout << "  0. Keluar" << endl;
    garis();
}


//         TAMBAH BARANG (LINKED LIST)

void tambahBarang() {
    barang *baru = new barang();

    cout << "\n--- TAMBAH BARANG BARU ---\n";
    cout << "ID Barang  : "; cin >> baru->id;

    // Cek duplikat ID
    barang *cek = head;
    while (cek != NULL) {
        if (cek->id == baru->id) {
            cout << "[!] ID sudah digunakan!\n";
            delete baru;
            return;
        }
        cek = cek->next;
    }

    cin.ignore();
    cout << "Nama Barang: "; cin.getline(baru->nama, 50);
    cout << "Stok       : "; cin >> baru->stok;
    cout << "Harga      : "; cin >> baru->harga;

    baru->next = head;
    head = baru;
    cout << "[+] Barang berhasil ditambahkan!\n";
}

//         TAMPIL BARANG (LINKED LIST)

void tampilBarang() {
    if (head == NULL) {
        cout << "\n[!] Gudang kosong!\n";
        return;
    }

    cout << "\n";
    garis();
    cout << left
         << setw(6)  << "ID"
         << setw(22) << "NAMA BARANG"
         << setw(10) << "STOK"
         << setw(15) << "HARGA (Rp)"
         << endl;
    garis();

    barang *temp = head;
    while (temp != NULL) {
        cout << left
             << setw(6)  << temp->id
             << setw(22) << temp->nama
             << setw(10) << temp->stok
             << "Rp " << fixed << setprecision(2) << temp->harga
             << endl;
        temp = temp->next;
    }
    garis();
}

//    CARI BARANG - SEQUENTIAL SEARCH (by ID)
//             & LINEAR SEARCH (by Nama)

void cariBarang() {
    cout << "\n--- CARI BARANG ---\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Nama\n";
    cout << "Pilih: ";
    int opsi; cin >> opsi;

    if (opsi == 1) {
        // Sequential Search by ID
        int idCari;
        cout << "Masukkan ID: "; cin >> idCari;

        barang *temp = head;
        bool ketemu = false;
        int posisi = 1;

        while (temp != NULL) {
            if (temp->id == idCari) {
                ketemu = true;
                cout << "\n[+] Barang ditemukan di posisi node ke-" << posisi << ":\n";
                garis();
                cout << "ID    : " << temp->id << endl;
                cout << "Nama  : " << temp->nama << endl;
                cout << "Stok  : " << temp->stok << endl;
                cout << "Harga : Rp " << fixed << setprecision(2) << temp->harga << endl;
                garis();
                break;
            }
            temp = temp->next;
            posisi++;
        }
        if (!ketemu) cout << "[-] Barang dengan ID " << idCari << " tidak ditemukan.\n";

    } else if (opsi == 2) {
        // Linear Search by Nama (case-insensitive partial match)
        char namaCari[50];
        cin.ignore();
        cout << "Masukkan Nama: "; cin.getline(namaCari, 50);

        // Konversi ke lowercase untuk perbandingan
        char namaLower[50];
        strcpy(namaLower, namaCari);
        for (int i = 0; namaLower[i]; i++) namaLower[i] = tolower(namaLower[i]);

        barang *temp = head;
        bool ketemu = false;
        cout << "\nHasil pencarian \"" << namaCari << "\":\n";
        garis();

        while (temp != NULL) {
            char tempLower[50];
            strcpy(tempLower, temp->nama);
            for (int i = 0; tempLower[i]; i++) tempLower[i] = tolower(tempLower[i]);

            if (strstr(tempLower, namaLower) != NULL) {
                ketemu = true;
                cout << left
                     << setw(6)  << temp->id
                     << setw(22) << temp->nama
                     << setw(10) << temp->stok
                     << "Rp " << fixed << setprecision(2) << temp->harga
                     << endl;
            }
            temp = temp->next;
        }
        garis();
        if (!ketemu) cout << "[-] Barang tidak ditemukan.\n";
    } else {
        cout << "[!] Pilihan tidak valid.\n";
    }
}

//     SORTING - BUBBLE SORT (by Nama / Harga)

void sortingBarang() {
    if (head == NULL || head->next == NULL) {
        cout << "[!] Data tidak cukup untuk diurutkan.\n";
        return;
    }

    cout << "\n--- SORTING BARANG ---\n";
    cout << "Urutkan berdasarkan:\n";
    cout << "1. Nama (A-Z)\n";
    cout << "2. Harga (Termurah - Termahal)\n";
    cout << "3. Stok (Terbanyak - Tersedikit)\n";
    cout << "Pilih: ";
    int opsi; cin >> opsi;

    // Bubble Sort pada Linked List (swap data, bukan pointer)
    bool swapped;
    do {
        swapped = false;
        barang *curr = head;
        while (curr->next != NULL) {
            bool perluSwap = false;

            if (opsi == 1 && strcmp(curr->nama, curr->next->nama) > 0)
                perluSwap = true;
            else if (opsi == 2 && curr->harga > curr->next->harga)
                perluSwap = true;
            else if (opsi == 3 && curr->stok < curr->next->stok)
                perluSwap = true;

            if (perluSwap) {
                // Swap semua field (kecuali pointer)
                int  tmpId   = curr->id;   curr->id   = curr->next->id;   curr->next->id   = tmpId;
                int  tmpStok = curr->stok; curr->stok = curr->next->stok; curr->next->stok = tmpStok;
                float tmpHrg = curr->harga;curr->harga= curr->next->harga;curr->next->harga= tmpHrg;
                char tmpNama[50];
                strcpy(tmpNama, curr->nama);
                strcpy(curr->nama, curr->next->nama);
                strcpy(curr->next->nama, tmpNama);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);

    cout << "[+] Data berhasil diurutkan!\n";
    tampilBarang();
}

//     TRANSAKSI - STOK MASUK / STOK KELUAR

void transaksi() {
    if (head == NULL) { cout << "[!] Gudang kosong!\n"; return; }

    cout << "\n--- TRANSAKSI ---\n";
    cout << "1. Stok Masuk\n";
    cout << "2. Stok Keluar\n";
    cout << "Pilih: ";
    int opsi; cin >> opsi;

    int idTarget;
    cout << "ID Barang: "; cin >> idTarget;

    barang *temp = head;
    while (temp != NULL) {
        if (temp->id == idTarget) {
            int jumlah;
            if (opsi == 1) {
                cout << "Jumlah stok masuk : "; cin >> jumlah;
                if (jumlah <= 0) { cout << "[!] Jumlah tidak valid.\n"; return; }
                temp->stok += jumlah;
                cout << "[+] Stok bertambah. Stok sekarang: " << temp->stok << endl;
            } else if (opsi == 2) {
                cout << "Jumlah stok keluar: "; cin >> jumlah;
                if (jumlah <= 0) { cout << "[!] Jumlah tidak valid.\n"; return; }
                if (jumlah > temp->stok) {
                    cout << "[!] Stok tidak mencukupi! Stok tersedia: " << temp->stok << endl;
                    return;
                }
                temp->stok -= jumlah;
                float total = jumlah * temp->harga;
                cout << "[+] Stok berkurang. Stok sekarang: " << temp->stok << endl;
                cout << "    Total nilai transaksi: Rp " << fixed << setprecision(2) << total << endl;
            } else {
                cout << "[!] Pilihan tidak valid.\n";
            }
            return;
        }
        temp = temp->next;
    }
    cout << "[-] Barang dengan ID " << idTarget << " tidak ditemukan.\n";
}

//     HAPUS BARANG (LINKED LIST - DELETE NODE)

void hapusBarang() {
    if (head == NULL) { cout << "[!] Gudang kosong!\n"; return; }

    cout << "\n--- HAPUS BARANG ---\n";
    int idHapus;
    cout << "ID Barang yang dihapus: "; cin >> idHapus;

    barang *curr = head, *prev = NULL;

    while (curr != NULL) {
        if (curr->id == idHapus) {
            if (prev == NULL)
                head = curr->next;       // Node pertama
            else
                prev->next = curr->next; // Node tengah/akhir

            cout << "[+] Barang \"" << curr->nama << "\" berhasil dihapus.\n";
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "[-] Barang dengan ID " << idHapus << " tidak ditemukan.\n";
}

//         SIMPAN KE FILE (BINARY)

void simpanKeFile() {
    FILE *file1 = fopen("data.dat", "wb");
    if (file1 == NULL) {
        cout << "[!] Gagal membuka file.\n";
        return;
    }

    barang *temp = head;
    int jumlah = 0;
    while (temp != NULL) {
        barang simpan = *temp;
        simpan.next = NULL; // Jangan simpan pointer
        fwrite(&simpan, sizeof(barang), 1, file1);
        jumlah++;
        temp = temp->next;
    }
    fclose(file1);
    cout << "[+] " << jumlah << " data berhasil disimpan ke file \"data.dat\".\n";
}

// =============================================
//         BACA DARI FILE (BINARY)
// =============================================
void bacaDariFile() {
    FILE *file1 = fopen("data.dat", "rb");
    if (file1 == NULL) return;

    barang temp;
    while (fread(&temp, sizeof(barang), 1, file1)) {
        barang *baru = new barang();
        *baru = temp;
        baru->next = head;
        head = baru;
    }
    fclose(file1);
    cout << "[*] Data berhasil dimuat dari file.\n";
}


int main() {
    bacaDariFile();

    int pilih;
    do {
        menu();
        cout << "  Pilih menu: ";
        cin >> pilih;
        cout << endl;

        switch (pilih) {
            case 1: tambahBarang();  break;
            case 2: tampilBarang();  break;
            case 3: cariBarang();    break;
            case 4: sortingBarang(); break;
            case 5: transaksi();     break;
            case 6: hapusBarang();   break;
            case 7: simpanKeFile();  break;
            case 0:
                simpanKeFile();
                cout << "[*] Data tersimpan. Sampai jumpa!\n";
                break;
            default:
                cout << "[!] Menu tidak tersedia.\n";
        }
        cout << endl;
    } while (pilih != 0);

    return 0;
}
