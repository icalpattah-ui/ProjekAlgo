#include <iostream>
using namespace std;

struct film
{
    char judul[100], genre[10], tanggal[50], kursi[100];
    int ID, harga, durasi;
    string jadwal[3];
    film* next;
};

film *head = NULL;

void simpanFile(){
    FILE *f = fopen("film.txt", "w");
    if (f == NULL){
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    film *temp = head;

    while (temp != NULL){
        fprintf(f, "%s|%s|%s|%d|%d",
            temp->judul,
            temp->genre,
            temp->tanggal,
            temp->harga,
            temp->durasi);
        temp = temp->next;
    }
    fclose(f);
    cout << "Data berhasil disimpan ke file" << endl;
}


void loadFile(){
    FILE *f = fopen("film.txt", "r");
    
    if(f == NULL) return;
    film *tail = NULL; // buat append & jaga urutan asli
    film *filmBaru = new film;

    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%d|%d",
                    filmBaru->judul,
                    filmBaru->genre,
                    filmBaru->tanggal,
                    &filmBaru->harga,
                    &filmBaru->durasi) == 6 )
    {
        //
        filmBaru->next = NULL;
        if(head == NULL){
            head = filmBaru;
            tail = filmBaru;
        } else {
            tail->next = filmBaru;
            tail = filmBaru;
        }

        filmBaru = new film;
    }
    delete filmBaru; //
    fclose(f);
}

//fungsi biar kalo nyari judul ga kapital bisa terdeteksi
void toLowerStr(char *str){
    for (int i = 0; str[i]; i++)
        str[i] = tolower((unsigned char)str[i]);   
}

void keluar(){
    char pilih;

    cout << " Apakah Anda yakin ingin keluar? (y/n): ";
    cin >> pilih;

    if (pilih == 'y' || pilih == 'Y')
    {
        simpanFile();
        cout << "Terima kasih telah memesan tiket, datang kembali" << endl;
        exit(0);
    } else {
        cout << "Kembali ke menu utama" << endl;
    }
}


// pesan tiket
void tampilkanDaftarFilm(){
    if(head == NULL){
        cout << "\nBelum ada film yang tersedia.";
        return;
    }

    cout << "=====================================================================" << endl;
    cout << "                    DAFTAR FILM YANG SEDANG TAYANG                   " << endl;
    cout << "=====================================================================" << endl;
    cout << "| No | Judul Film         | Genre     | Tanggal   | Harga  | Durasi  " << endl;
    cout << "=====================================================================" << endl;

    film *temp = head;
    int no = 1;
    while(temp != NULL){
       printf("| %-2d | %-30s | Rp %-6d |\n", no, temp->judul, temp->harga);
        temp = temp->next;
        no++;
    }
    cout << "==================================================" << endl;
}
\\ menacri film berdasarkan judul
film* cariFilmByJudul(char judulCari[]) {
    film* temp = head;
    char judulCariLower[100];

    \\ ubah judulCari ke lowercase untuk pencarian 

    char tempJudulLower[100];
    strcpy(judulCariLower, judulCari);
    toLowerStr(judulCariLower);


    while (temp != NULL) {
        strcpy(judulTemp, temp->judul);
        toLowerStr(judulTemp);
        
        if (strcmp(judulTemp, judulCariLower) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// menampilkan detail film
void tampilkanDetailFilm(film* f) {
    cout << "\n=== DETAIL FILM ===" << endl;
    cout << "Judul   : " << f->judul << endl;
    cout << "Genre   : " << f->genre << endl;
    cout << "Tanggal : " << f->tanggal << endl;
    cout << "Harga   : Rp " << f->harga << endl;
    cout << "Durasi  : " << f->durasi << " menit" << endl;
    for (int i = 0; i < 3; i++) {
        if (!f->jadwal[i].empty())
            cout << f->jadwal[i] << " ";
    }
    cout << endl;
}

// MENU 1 - pesan tiket
void pesanTiket() {
    cout << "\n========================================" << endl;
    cout << "             PESAN TIKET FILM            " << endl;
    cout << "========================================" << endl;

// tampilkan daftar film
    tampilkanDaftarFilm();

    if(head == NULL) return;

    char if (head == NULL) {
        cout << "Tidak bisa memesan karena belum ada film.\n";
        return;
    }

    // pilih film
    char pilihJudul[100];
    cout << "Masukkan judul film yang ingin dipesan: ";
    cin.get.ignore();
    cin.getline(pilihJudul, 100);

    film* filmDipilih = cariFilmByJudul(pilihJudul);

    if (filmDipilih == NULL) {
        cout << "Film dengan judul '" << pilihJudul << "' tidak ditemukan.\n";
        return;
    }

    // tampilkan detail film
    tampilkanDetailFilm(filmDipilih);

    // input data pemesan
    pemesanan *pesananBaru = new pemesanan;
    
    cout << "\n=== DATA PEMESAN ===" << endl;
    cout << "Nama   : ";
    cin.getline(pesananBaru->nama, 100);

    // pilih jadwal
    cout << "\nPilih jadwal tayang: ";
    for (int i = 0; i < 3; i++) {
        if (!filmDipilih->jadwal[i].empty()){
            cout << (i + 1) << ". " << filmDipilih->jadwal[i] << " ";
    }
}

int pilihJadwal;
cout << "pilih (1-3): ";
cin >> pilihJadwal;

if (pilihJadwal >= 1 && pilihJadwal <= 3 && !filmDipilih->jadwal[pilihJadwal-1].empty()) {
        pesananBaru->jamTayang = filmDipilih->jadwal[pilihJadwal-1];
    } else {
        cout << "Pilihan jadwal tidak valid.\n";
        delete pesananBaru;
        return;
    }

// input jumlah tiket
     cout << "Jumlah tiket: ";
    cin >> pesananBaru->jumlahTiket;

// input kursi
    cout << "Pilih kursi (contoh: A1, B2): ";
    cin.ignore();
    cin.getline(pesananBaru->kursi, 10);

//hitung total harga
    pesananBaru->totalHarga = pesananBaru->jumlahTiket * filmDipilih->harga;    

// simpan ke linked list riwayat (akhir)
if(headRiwayat == NULL) {
    headRiwayat = pesananBaru;
} else {
    pemesanan* temp = headRiwayat;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = pesananBaru;
}

// tampilan struk
cout << "\n========================================" << endl;
cout << "              STRUK PEMESANAN            " << endl;
cout << "==========================================" << endl;
cout << " Nama Pemesan : " << pesananBaru->namaPemesan << endl;
cout << " Judul Film   : " << filmDipilih->judulFilm << endl;
cout << "Tanggal Tayang : " << pesananBaru->tanggalTayang << endl;
cout << "Jam Tayang     : " << pesananBaru->jamTayang << endl;
cout << "Jumlah Tiket   : " << pesananBaru->jumlahTiket << endl;
cout << "Kursi          : " << pesananBaru->kursi << endl;
cout << "Total Harga    : Rp " << pesananBaru->totalHarga << endl;
cout << "==========================================" << endl;
cout << "Terima kasih! Selamat menonton!" << endl;
}

// MENU 2 - lihat riwayat pemesanan
void lihatRiwayatPemesanan() {
    cout << "\n========================================" << endl;
    cout << "          RIWAYAT PEMESANAN FILM         " << endl;
    cout << "==========================================" << endl;

    if (headRiwayat == NULL) {
        cout << "Belum ada pemesanan yang dilakukan.\n";
        return;
    }

    pemesanan* temp = headRiwayat;
    int no = 1;
    while (temp != NULL) {
        cout << no++ << ". " << temp->namaPemesan << " - " << temp->judulFilm 
             << " (" << temp->tanggalTayang << " " << temp->jamTayang << ") - "
             << temp->jumlahTiket << " tiket - Rp " << temp->totalHarga << endl;
        temp = temp->next;
    }
}

// table riwayat
 cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "| No | Nama Pemesan     | Judul Film                | Jml | Kursi | Tanggal      | Jam    | Total Harga |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    pemesanan* temp = headRiwayat;
    int no = 1;

    while (temp != NULL) {
        printf("| %-2d | %-15s | %-25s | %-3d | %-5s | %-12s | %-6s | Rp %-10d |\n",
               no++, temp->namaPemesan, temp->judulFilm, temp->jumlahTiket, temp->kursi,
               temp->tanggalTayang, temp->jamTayang, temp->totalHarga);
        temp = temp->next;
    }
     cout << "----------------------------------------------------------------------------------------------------------" << endl;

    // hitung total pendapatan
    int totalPendapatan = 0;
    int totalTiketTerjual = 0;
    temp = headRiwayat;
    while (temp != NULL) {
        totalPendapatan += temp->totalHarga;
        totalTiketTerjual += temp->jumlahTiket;
        temp = temp->next;
    }

    cout << "\nTotal Pemesanan : " << (no - 1) << " kali " << endl;
    cout << "Total Tiket Terjual : " << totalTiketTerjual << " tiket" << endl;
    cout << "Total Pendapatan : Rp " << totalPendapatan << endl;

    // Load Riwayat
    void simpanRiwayatKeFile() {
    FILE *f = fopen("riwayat.txt", "w");
    if (f == NULL) {
        cout << " Gagal Menyimpan Riwayat!! " << endl;
        return;
    }

    pemesanan* temp = headRiwayat;
    while (temp != NULL) {
        fprintf(f, "%s|%s|%s|%s|%d\n",
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
        FILE *f = fopen("riwayat.txt", "r");
        if (f == NULL) return;

        pemesanan *tail = NULL;

        while (true) {
            pemesanan* pesananBaru = new pemesanan;
            if (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]\n",
                    pesananBaru->namaPemesan,
                    pesananBaru->judulFilm,
                    pesananBaru->tanggalTayang,
                    pesananBaru->jamTayang,
                    &pesananBaru->totalHarga) != 5) 
            if (result != 7) {
            delete pesananBaru;
            break;
        }
        
        pesananBaru->jamTayang = string(jamTayangTemp);
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

int main(){
    loadFile(); //ngambil data film nya

    int pilih;

    do
    {
        cout << "+========================================+" << endl;
        cout << "          LETS WATCH MOVIE TODAY        " << endl;
        cout << "========================================" << endl;
        cout << " 1. Tampilkan Film                         " << endl;
        cout << " 2. Cari Film                           " << endl;
        cout << " 3. Pesan Tiket                         " << endl;
        cout << " 4. Riwayat Pemesanan                   " << endl;
        cout << " 5. Keluar                              " << endl;
        cout << "+========================================+" << endl;
        cout << " Pilih menu (1-5): ";
        cin >> pilih;

        switch (pilih)
        {
        case 5:
            keluar();
            break;
        
        default:
          cout << " Maaf, pilihan tidak ada silahkan masukkan pilihan yang benar" << endl;
            break;
        }
    } while (pilih != 5);

    return 0;
}
