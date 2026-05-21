#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

struct film
{
    char judul[100], genre[10], tanggal[50], kursi[100];
    int ID, harga, durasi;
    string jadwal[3];
    film* next;
};

film *head = NULL;

void loadFile(){
    FILE *f = fopen("film.txt", "r");
    
    if(f == NULL) return;
    film *tail = NULL; // buat append & jaga urutan asli
    film *filmBaru = new film;

    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%d|%d\n",
                    filmBaru->judul,
                    filmBaru->genre,
                    filmBaru->tanggal,
                    &filmBaru->harga,
                    &filmBaru->durasi) == 5 )
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
        return;
    }
}

void swapFilm(film *a, film *b){

    char judul[100], genre[10], tanggal[50];
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

void sortHargaAsc(){
    if(head == NULL){
        cout << "Maaf, film belum tersedia." << endl;
        return;
    }

    bool swap;
    film *ptr;

    do 
    {
        swap = false;
        ptr = head;
        while(ptr->next != NULL){
            if(ptr->harga > ptr->next->harga){
                swapFilm(ptr, ptr->next);
                swap = true;
            }
            ptr = ptr->next;
        }
    } while(swap);
}

void sortHargaDsc(){
    if (head == NULL)
    {
        cout << "Maaf, film belum tersedia." << endl;
        return;
    }
        
    bool swap;
    film *ptr;
        
    do
    {
        swap = false;
        ptr = head;

        while (ptr->next != NULL)
        {
            if (ptr->harga < ptr->next->harga)
            {
                swapFilm(ptr, ptr->next);
                swap = true;
            }
            ptr = ptr->next;
        }      
    } while (swap);
}

void sortAbjad(){
    if (head == NULL)
    {
        cout << "Maaf, film belum tersedia." << endl;
        return;
    }

    bool swap;
    film *ptr;

    do
    {
        swap = false;
        ptr = head;

        while (ptr->next != NULL)
        {
            if (strcmp(ptr->judul, ptr->next->judul) > 0) //cmp buat konvert char jadi string (membandingkan)
            {
                swapFilm(ptr, ptr->next);
                swap = true;
            }
            ptr = ptr->next;
        }
    } while (swap);
}

void detailFilm(film* f){
    cout << setfill('=') << setw(40) << "" << endl;
    cout << setfill(' ');
    cout << "|" << setw(20) << right << "DETAIL FILM" << setw(18) << right << "|" << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    cout << setfill(' ');
    cout << "Judul   : " << f->judul << endl;
    cout << "Genre   : " << f->genre << endl;
    cout << "Tanggal : " << f->tanggal << endl;
    cout << "Harga   : Rp " << f->harga << endl;
    cout << "Durasi  : " << f->durasi << " menit" << endl;
    cout << "Jadwal  : ";
    for(int i = 0; i < 3; i++){
        if(!f->jadwal[i].empty())
            cout << f->jadwal[i] << " ";
    }
    cout << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    cout << setfill(' ');
}

void cariFilm(){
    char cariJudul[100];

    cout << "Masukkan judul film : ";
    cin.ignore();
    cin.getline(cariJudul, 100);

    film* temp = head;
    bool found = false;

    toLowerStr(cariJudul);

    while (temp != NULL)
    {
        char judulTemp[100];
        strcpy(judulTemp, temp->judul);
        toLowerStr(judulTemp);

        if (strcmp(judulTemp, cariJudul) == 0)
        {
            found = true;
            break;
        }
        temp = temp->next;
    }
    
    if (found)
    {
        cout << "Film ditemukan!" << endl;
        detailFilm(temp);

    } else {
        cout << "Sorry, film " << cariJudul << " tidak ditemukan." << endl;
    }
}

void tampilFilm(){
    
    if(head == NULL){
        cout << "Maaf, sedang maintence belum ada film yang tersedia";
        return;
    }

    int daftarFilm;
    cout << "========= Urutkan menurut ========" << endl;
    cout << "1. Termahal " << endl;
    cout << "2. Termurah " << endl;
    cout << "3. Judul Film (A-Z)" << endl;
    cout << "Pilih : ";
    cin >> daftarFilm;

    switch (daftarFilm)
    {
    case 1:
        sortHargaDsc();
        break;
    case 2:
        sortHargaAsc();
        break;
    case 3:
        sortAbjad();
        break;
    default:
        cout << "Maaf, pilihan tidak ada silahkan masukkan pilihan yang benar" << endl;
        break;
    }

    cout << setfill('=') << setw(80) << "" << endl;
    cout << setfill(' ');
    cout << "|" << setw(50) << right << "DAFTAR FILM YANG SEDANG TAYANG" << setw(27) << right << "|" << endl;
	cout << setfill('=') << setw(80) << "" << endl;
    cout << setfill(' ');
    cout << "| " << left << setw(4)  << "No"
         << "| " << setw(25) << "Judul Film"
         << "| " << setw(8)  << "Genre"
         << "| " << setw(12) << "Tanggal"
         << "| " << setw(10) << "Harga"
         << "| " << setw(7)  << "Durasi"
         << "|" << endl;
    cout << setfill('=') << setw(80) << "" << endl;
    cout << setfill(' ');

    film *temp = head;
    int no = 1;
    while (temp != NULL)
    {
        cout << "| " << left << setw(4)  << no
            << "| " << setw(25) << temp->judul
            << "| " << setw(8)  << temp->genre
            << "| " << setw(12) << temp->tanggal
            << "| " << setw(10) << temp->harga
            << "| " << setw(7)  << temp->durasi
            << "|" << endl;
        temp = temp->next;
        no++;
    }
    cout << setfill('=') << setw(80) << "" << endl;
    cout << setfill(' ');
}

// MENU 1 - pesan tiket
void pesanTiket() {
    cout << "\n========================================" << endl;
    cout << "             PESAN TIKET FILM            " << endl;
    cout << "========================================" << endl;

// tampilkan daftar film
    tampilFilm();

    if(head == NULL) return;

    if (head == NULL) {
        cout << "Tidak bisa memesan karena belum ada film.\n";
        return;
    }

    // pilih film
    char pilihJudul[100];
    cout << "Masukkan judul film yang ingin dipesan: ";
    cin.ignore();
    cin.getline(pilihJudul, 100);

    film* filmDipilih = cariFilm(pilihJudul);

    if (filmDipilih == NULL) {
        cout << "Film dengan judul '" << pilihJudul << "' tidak ditemukan.\n";
        return;
    }

    // tampilkan detail film
    ta(filmDipilih);

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
        cout << " Pilih menu : ";
        cin >> pilih;
        cout << endl;

        
        switch (pilih)
        {
            case 1: 
            tampilFilm();
                break;
            case 2: 
            cariFilm();
                break;
            case 3: 
            
                break;
            case 4:
            
                break;
            case 5: keluar();
            break;
        
        default:
            cout << "Maaf, pilihan tidak ada silahkan masukkan pilihan yang benar" << endl;
            break;
        }
    } while (true);

    return 0;
}
