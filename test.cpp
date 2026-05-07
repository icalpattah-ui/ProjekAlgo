#include <iostream>
using namespace std;

struct film
{
    string judul;
    string  genre;
    string tanggal;
    int harga;
    int durasi;
    film* next;
};

