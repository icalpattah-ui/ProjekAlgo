#include <iostream>
#include <iomanip>
#include <string.h>
#include <ctype.h>

using namespace std;

struct film {
    char judul[100], genre[20], tanggal[50];
    int harga, durasi;
    string jadwal[3];
    film* next;
};

struct pemesanan {
    char namaPemesan[100];
    char judulFilm[100];
    char tanggalTayang[50];
    char jamTayang[50];
    string kursi;

    int jumlahTiket;
    int totalHarga;

    pemesanan* next;
};

film* head = NULL;
pemesanan* headRiwayat = NULL;

// ==================== FUNCTION ====================

void simpanFile() {
    FILE* f = fopen("film.txt", "w");

    if (f == NULL) {
        cout << "Gagal menyimpan file!\n";
        return;
    }

    film* temp = head;

    while (temp != NULL) {
        fprintf(f, "%s|%s|%s|%d|%d\n",
                temp->judul,
                temp->genre,
                temp->tanggal,
                temp->harga,
                temp->durasi);

        temp = temp->next;
    }

    fclose(f);
}

void loadFile() {
    FILE* f = fopen("film.txt", "r");

    if (f == NULL) return;

    film* tail = NULL;

    while (true) {
        film* filmBaru = new film;

        int result = fscanf(f, "%[^|]|%[^|]|%[^|]|%d|%d\n",
                            filmBaru->judul,
                            filmBaru->genre,
                            filmBaru->tanggal,
                            &filmBaru->harga,
                            &filmBaru->durasi);

        if (result != 5) {
            delete filmBaru;
            break;
        }

        // Jadwal default
        filmBaru->jadwal[0] = "10:00";
        filmBaru->jadwal[1] = "13:00";
        filmBaru->jadwal[2] = "19:00";

        filmBaru->next = NULL;

        if (head == NULL) {
            head = filmBaru;
            tail = filmBaru;
        } else {
            tail->next = filmBaru;
            tail = filmBaru;
        }
    }

    fclose(f);
}

void toLowerStr(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void keluar() {
    char pilih;

    cout << "Apakah Anda yakin ingin keluar? (y/n): ";
    cin >> pilih;

    if (pilih == 'y' || pilih == 'Y') {
        simpanFile();
        cout << "Terima kasih telah menggunakan program ini.\n";
        exit(0);
    }
}

void swapFilm(film* a, film* b) {

    char judul[100], genre[20], tanggal[50];
    int harga, durasi;

    strcpy(judul, a->judul);
    strcpy(genre, a->genre);
    strcpy(tanggal, a->tanggal);

    harga = a->harga;
    durasi = a->durasi;

    strcpy(a->judul, b->judul);
    strcpy(a->genre, b->genre);
    strcpy(a->tanggal, b->tanggal);

    a->harga = b->harga;
    a->durasi = b->durasi;

    strcpy(b->judul, judul);
    strcpy(b->genre, genre);
    strcpy(b->tanggal, tanggal);

    b->harga = harga;
    b->durasi = durasi;
}

void sortHargaAsc() {

    if (head == NULL) return;

    bool swap;
    film* ptr;

    do {
        swap = false;
        ptr = head;

        while (ptr->next != NULL) {

            if (ptr->harga > ptr->next->harga) {
                swapFilm(ptr, ptr->next);
                swap = true;
            }

            ptr = ptr->next;
        }

    } while (swap);
}

void sortHargaDsc() {

    if (head == NULL) return;

    bool swap;
    film* ptr;

    do {
        swap = false;
        ptr = head;

        while (ptr->next != NULL) {

            if (ptr->harga < ptr->next->harga) {
                swapFilm(ptr, ptr->next);
                swap = true;
            }

            ptr = ptr->next;
        }

    } while (swap);
}

void sortAbjad() {

    if (head == NULL) return;

    bool swap;
    film* ptr;

    do {
        swap = false;
        ptr = head;

        while (ptr->next != NULL) {

            if (strcmp(ptr->judul, ptr->next->judul) > 0) {
                swapFilm(ptr, ptr->next);
                swap = true;
            }

            ptr = ptr->next;
        }

    } while (swap);
}

void detailFilm(film* f) {

    cout << "\n====================================\n";
    cout << "DETAIL FILM\n";
    cout << "====================================\n";

    cout << "Judul   : " << f->judul << endl;
    cout << "Genre   : " << f->genre << endl;
    cout << "Tanggal : " << f->tanggal << endl;
    cout << "Harga   : Rp " << f->harga << endl;
    cout << "Durasi  : " << f->durasi << " menit\n";

    cout << "Jadwal  : ";

    for (int i = 0; i < 3; i++) {
        cout << f->jadwal[i] << " ";
    }

    cout << endl;
}

film* cariFilm() {

    char cariJudul[100];

    cin.ignore();

    cout << "Masukkan judul film: ";
    cin.getline(cariJudul, 100);

    char cariTemp[100];
    strcpy(cariTemp, cariJudul);

    toLowerStr(cariTemp);

    film* temp = head;

    while (temp != NULL) {

        char judulTemp[100];

        strcpy(judulTemp, temp->judul);

        toLowerStr(judulTemp);

        if (strcmp(judulTemp, cariTemp) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

void tampilFilm() {

    if (head == NULL) {
        cout << "Belum ada film tersedia.\n";
        return;
    }

    int pilih;

    cout << "\n===== URUTKAN FILM =====\n";
    cout << "1. Termahal\n";
    cout << "2. Termurah\n";
    cout << "3. A-Z\n";
    cout << "Pilih: ";
    cin >> pilih;

    switch (pilih) {

        case 1:
            sortHargaDsc();
            break;

        case 2:
            sortHargaAsc();
            break;

        case 3:
            sortAbjad();
            break;
    }

    cout << "\n================================================================================\n";
    cout << "| No | Judul Film             | Genre     | Tanggal     | Harga     | Durasi |\n";
    cout << "================================================================================\n";

    film* temp = head;
    int no = 1;

    while (temp != NULL) {

        cout << "| "
             << setw(2) << left << no++
             << " | "
             << setw(23) << left << temp->judul
             << " | "
             << setw(10) << left << temp->genre
             << " | "
             << setw(11) << left << temp->tanggal
             << " | "
             << setw(10) << left << temp->harga
             << " | "
             << setw(6) << left << temp->durasi
             << " |\n";

        temp = temp->next;
    }

    cout << "================================================================================\n";
}

void pesanTiket() {

    tampilFilm();

    if (head == NULL) return;

    film* filmDipilih = cariFilm();

    if (filmDipilih == NULL) {
        cout << "Film tidak ditemukan.\n";
        return;
    }

    detailFilm(filmDipilih);

    pemesanan* pesananBaru = new pemesanan;

    pesananBaru->next = NULL;

    cout << "\nNama Pemesan : ";

    cin.getline(pesananBaru->namaPemesan, 100);

    cout << "\nPilih Jadwal:\n";

    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". "
             << filmDipilih->jadwal[i] << endl;
    }

    int pilihJadwal;

    cout << "Pilih: ";
    cin >> pilihJadwal;

    if (pilihJadwal < 1 || pilihJadwal > 3) {

        cout << "Jadwal tidak valid.\n";
        delete pesananBaru;
        return;
    }

    strcpy(
        pesananBaru->jamTayang,
        filmDipilih->jadwal[pilihJadwal - 1].c_str()
    );

    strcpy(pesananBaru->judulFilm, filmDipilih->judul);
    strcpy(pesananBaru->tanggalTayang, filmDipilih->tanggal);

    cout << "Jumlah Tiket : ";
    cin >> pesananBaru->jumlahTiket;

    cin.ignore();

    cout << "Pilih Kursi : ";
    getline(cin, pesananBaru->kursi);

    pesananBaru->totalHarga =
        pesananBaru->jumlahTiket * filmDipilih->harga;

    // tambah ke linked list riwayat

    if (headRiwayat == NULL) {
        headRiwayat = pesananBaru;
    } else {

        pemesanan* temp = headRiwayat;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = pesananBaru;
    }

    // STRUK

    cout << "\n====================================\n";
    cout << "STRUK PEMESANAN\n";
    cout << "====================================\n";

    cout << "Nama Pemesan  : " << pesananBaru->namaPemesan << endl;
    cout << "Judul Film    : " << pesananBaru->judulFilm << endl;
    cout << "Tanggal       : " << pesananBaru->tanggalTayang << endl;
    cout << "Jam           : " << pesananBaru->jamTayang << endl;
    cout << "Jumlah Tiket  : " << pesananBaru->jumlahTiket << endl;
    cout << "Kursi          : " << pesananBaru->kursi << endl;
    cout << "Total Harga   : Rp "
         << pesananBaru->totalHarga << endl;

    cout << "====================================\n";
}

void lihatRiwayatPemesanan() {

    if (headRiwayat == NULL) {
        cout << "Belum ada riwayat pemesanan.\n";
        return;
    }

    cout << "\n==============================================\n";
    cout << "RIWAYAT PEMESANAN\n";
    cout << "==============================================\n";

    pemesanan* temp = headRiwayat;

    int no = 1;
    int totalPendapatan = 0;
    int totalTiket = 0;

    while (temp != NULL) {

        cout << no++ << ". "
             << temp->namaPemesan
             << " - "
             << temp->judulFilm
             << " - "
             << temp->jumlahTiket
             << " tiket - Rp "
             << temp->totalHarga
             << endl;

        totalPendapatan += temp->totalHarga;
        totalTiket += temp->jumlahTiket;

        temp = temp->next;
    }

    cout << "\nTotal Tiket Terjual : "
         << totalTiket << endl;

    cout << "Total Pendapatan    : Rp "
         << totalPendapatan << endl;
}

void simpanRiwayatKeFile() {

    FILE* f = fopen("riwayat.txt", "w");

    if (f == NULL) return;

    pemesanan* temp = headRiwayat;

    while (temp != NULL) {

        fprintf(f,
                "%s|%s|%s|%s|%d\n",
                temp->namaPemesan,
                temp->judulFilm,
                temp->tanggalTayang,
                temp->jamTayang,
                temp->totalHarga);

        temp = temp->next;
    }

    fclose(f);
}

void loadRiwayatDariFile() {

    FILE* f = fopen("riwayat.txt", "r");

    if (f == NULL) return;

    pemesanan* tail = NULL;

    while (true) {

        pemesanan* pesananBaru = new pemesanan;

        int result = fscanf(f,
                            "%[^|]|%[^|]|%[^|]|%[^|]|%d\n",
                            pesananBaru->namaPemesan,
                            pesananBaru->judulFilm,
                            pesananBaru->tanggalTayang,
                            pesananBaru->jamTayang,
                            &pesananBaru->totalHarga);

        if (result != 5) {
            delete pesananBaru;
            break;
        }

        pesananBaru->next = NULL;

        if (headRiwayat == NULL) {

            headRiwayat = pesananBaru;
            tail = pesananBaru;

        } else {

            tail->next = pesananBaru;
            tail = pesananBaru;
        }
    }

    fclose(f);
}

// ==================== MAIN ====================

int main() {

    loadFile();
    loadRiwayatDariFile();

    int pilih;

    do {

        cout << "\n========================================\n";
        cout << "        LETS WATCH MOVIE TODAY\n";
        cout << "========================================\n";
        cout << "1. Tampilkan Film\n";
        cout << "2. Cari Film\n";
        cout << "3. Pesan Tiket\n";
        cout << "4. Riwayat Pemesanan\n";
        cout << "5. Keluar\n";
        cout << "========================================\n";
        cout << "Pilih Menu : ";

        cin >> pilih;

        switch (pilih) {

            case 1:
                tampilFilm();
                break;

            case 2: {

                film* hasil = cariFilm();

                if (hasil != NULL) {

                    cout << "\nFilm ditemukan!\n";
                    detailFilm(hasil);

                } else {

                    cout << "Film tidak ditemukan.\n";
                }

                break;
            }

            case 3:
                pesanTiket();
                break;

            case 4:
                lihatRiwayatPemesanan();
                break;

            case 5:
                simpanFile();
                simpanRiwayatKeFile();
                keluar();
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (true);

    return 0;
}
