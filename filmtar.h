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
    bool hozzaad(Film* uj); //hozzáad egy új eltárolt filmet a heterogén kollekcióhoz
    Film** keres(const String& feltetel, int& talalat); // vissza ad egy szűrt listát
    bool modosit(Film* film); //módosítja egy kiválasztott film egy adattagját
    bool torol(Film* film); //kitörli a kiválasztott filmet a heterogén kollekcióból
    void fajlbol_betolt();  //betölti a fájlból a filmeket
    void fajlba_ment(); //menti a fájlokba a filmeket
};

#endif