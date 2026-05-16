#ifndef FILMTAR_H
#define FILMTAR_H

#include"sajat_string.h"
#include "film.h"
#include <stdio.h>
#include <cstddef>

/// @brief filmeket osszefogo heterogen kollekcio
class Filmtar{
    Film** filmek;
    size_t db;
    size_t kapacitas;
public:
    Filmtar();
    ~Filmtar();
    void hozzaad(Film* uj); //hozzáad egy új eltárolt filmet a heterogén kollekcióhoz
    Film** keresCim(const String& feltetel, int& talalat); // vissza ad egy szűrt listát
    Film** keresHossz(int minHossz , int maxHossz, int& talalat); // vissza ad egy szűrt listát
    Film** keresEv(int minEv, int maxEv, int& talalat);// vissza ad egy szűrt listát
    Film** getMind(int& talalat); // visszaadja az osszes filmet
    //void modosit(Film* film); módosítja egy kiválasztott film egy adattagját (ez megse kell)
    void torol(Film* film); //kitörli a kiválasztott filmet a heterogén kollekcióból
    void fajlbol_betolt();  //betölti a fájlból a filmeket
    void fajlba_ment(); //menti a fájlokba a filmeket
};

#endif