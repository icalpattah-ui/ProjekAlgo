#include <iostream>
using namespace std;

struct film
{
    char judul[100], genre[100], tanggal[100];
    int harga;
    int durasi;
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
