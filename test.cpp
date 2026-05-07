#include <iostream>
using namespace std;

film *head = NULL;
struct film
{
    char judul;
    char  genre;
    char tanggal;
    int harga;
    int durasi;
    film* next;
};

void simpanFile(){
    FILE* f = fopen("film.txt", "w");
    if (f = NULL){
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    film *temp = head;

    while(temp != NULL){
        fprintf(f, "%s|%s|%s|%d|%d",
            temp->judul,
            temp->genre,
            temp->tanggal,
            temp->harga,
            temp->durasi);
        temp = temp->next;
    }
    fclose(f);
}


void loadFile(){
    FILE* f = fopen("");
}
