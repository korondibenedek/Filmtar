#ifndef FILMTAR_H
#define FILMTAR_H

#include"sajat_string.h"
#include "film.h"
#include <stdio.h>
#include <cstddef>

class Filmtar{
    Film** filmek;
    size_t db;
    size_t kapacitas;
public:
    Filmtar();
    ~Filmtar();
    bool hozzaad(Film* uj);
    Film** keres(const String& feltetel, int& talalat);
    bool modosit(Film* film);
    bool torol(Film* film);
    void fajlbol_betolt();
    void fajlba_ment();
};

#endif