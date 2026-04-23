#include <iostream>
#include <fstream>
using namespace std;

struct Barang {
    string id;
    string nama;
    string jenis;
    int stok;
    int harga;

    Barang* next;
    Barang* prev;
};

Barang* head = NULL;
Barang* tail = NULL;

// Tambah barang
void tambahBarang() {
    Barang* baru = new Barang();

    cout << "\n=== Tambah Barang ===\n";
    cout << "ID Barang      : "; cin >> baru->id;
    cout << "Nama Barang    : "; cin >> baru->nama;
    cout << "Jenis Barang   : "; cin >> baru->jenis;
    cout << "Stok Barang    : "; cin >> baru->stok;
    cout << "Harga Barang   : "; cin >> baru->harga;

    baru->next = NULL;
    baru->prev = NULL;

    if (head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }

    cout << "\nBarang berhasil ditambahkan!\n";
}

// Tampilkan barang
void tampilBarang() {
    if (head == NULL) {
        cout << "\nData barang masih kosong!\n";
        return;
    }

    Barang* temp = head;

    cout << "\n=== Data Barang Gudang ===\n";
    cout << "ID\tNama\tJenis\tStok\tHarga\n";
    cout << "---------------------------------------------\n";

    while (temp != NULL) {
        cout << temp->id << "\t"
             << temp->nama << "\t"
             << temp->jenis << "\t"
             << temp->stok << "\t"
             << temp->harga << endl;

        temp = temp->next;
    }
}

// Cari barang
void cariBarang() {
    if (head == NULL) {
        cout << "\nData kosong!\n";
        return;
    }

    string cari;
    cout << "\nMasukkan ID Barang yang dicari: ";
    cin >> cari;

    Barang* temp = head;
    bool ditemukan = false;

    while (temp != NULL) {
        if (temp->id == cari) {
            cout << "\nBarang ditemukan!\n";
            cout << "Nama  : " << temp->nama << endl;
            cout << "Jenis : " << temp->jenis << endl;
            cout << "Stok  : " << temp->stok << endl;
            cout << "Harga : " << temp->harga << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "\nBarang tidak ditemukan!\n";
    }
}

// Sort barang berdasarkan nama (ascending)
void sortBarang() {
    if (head == NULL) {
        cout << "\nData kosong!\n";
        return;
    }

    for (Barang* i = head; i != NULL; i = i->next) {
        for (Barang* j = i->next; j != NULL; j = j->next) {
            if (i->nama > j->nama) {
                swap(i->id, j->id);
                swap(i->nama, j->nama);
                swap(i->jenis, j->jenis);
                swap(i->stok, j->stok);
                swap(i->harga, j->harga);
            }
        }
    }

    cout << "\nData berhasil di-sort berdasarkan nama!\n";
}

// Transaksi masuk / keluar
void transaksiBarang() {
    if (head == NULL) {
        cout << "\nData kosong!\n";
        return;
    }

    string cari;
    cout << "\nMasukkan ID Barang: ";
    cin >> cari;

    Barang* temp = head;

    while (temp != NULL) {
        if (temp->id == cari) {
            int pilih, jumlah;

            cout << "\n1. Barang Masuk\n";
            cout << "2. Barang Keluar\n";
            cout << "Pilih: ";
            cin >> pilih;

            cout << "Jumlah: ";
            cin >> jumlah;

            if (pilih == 1) {
                temp->stok += jumlah;
                cout << "\nStok berhasil ditambah!\n";
            } else if (pilih == 2) {
                if (jumlah <= temp->stok) {
                    temp->stok -= jumlah;
                    cout << "\nStok berhasil dikurangi!\n";
                } else {
                    cout << "\nStok tidak mencukupi!\n";
                }
            } else {
                cout << "\nPilihan tidak valid!\n";
            }
            return;
        }
        temp = temp->next;
    }

    cout << "\nBarang tidak ditemukan!\n";
}

// Simpan ke file
void simpanFile() {
    ofstream file("data_barang.txt");
    Barang* temp = head;

    while (temp != NULL) {
        file << temp->id << " "
             << temp->nama << " "
             << temp->jenis << " "
             << temp->stok << " "
             << temp->harga << endl;

        temp = temp->next;
    }

    file.close();
    cout << "\nData berhasil disimpan ke file!\n";
}

int main() {
    int pilihan;

    do {
        cout << "\n========================================\n";
        cout << " SISTEM MANAJEMEN LOGISTIK DAN GUDANG\n";
        cout << "========================================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Cari Barang\n";
        cout << "4. Sort Barang\n";
        cout << "5. Transaksi Masuk/Keluar\n";
        cout << "6. Simpan dan Keluar\n";
        cout << "========================================\n";
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilBarang();
                break;
            case 3:
                cariBarang();
                break;
            case 4:
                sortBarang();
                break;
            case 5:
                transaksiBarang();
                break;
            case 6:
                simpanFile();
                cout << "\nProgram selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 6);

    return 0;
}

