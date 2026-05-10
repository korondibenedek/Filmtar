#ifndef FILM_H
#define FILM_H

#include "sajat_string.h"
#include <iostream>

/// @brief Filmek alaposztalya(abstract)
class Film{
    String cim;
    int idotartam;
    int kiadasi_ev;
public:
    Film(String  cim, int hossz, int ev);
    virtual ~Film();
    virtual String encode() const = 0; // fájl formátumba alakítja
    virtual String toString() const = 0; // kiírható formátumba alakítja
};

/// @brief HorrorFilm, a Film alosztalya plusz adattag ijesztes_faktor
class HorrorFilm: public Film{
    int ijesztes_faktor;
public:
    HorrorFilm(String cim, int ido, int ev, int ijesztes);

    String encode() const override; // fájl formátumba alakítja
    String toString() const override; // kiírható formátumba alakítja
};

/// @brief DokumentumFilm, a Film alosztalya plusz adattag tema
class DokumentumFilm: public Film{
    String tema;
public:
    DokumentumFilm(String cim, int ido, int ev, String tema);

    String encode() const override; // fájl formátumba alakítja
    String toString() const override; // kiírható formátumba alakítja
};


/// @brief CsaladiFilm, a Film alosztalya plusz adattag korhatar
class CsaladiFilm: public Film{
    int korhatar;
public:
    CsaladiFilm(String cim, int ido, int ev, int korhatar);
    String encode() const override; // fájl formátumba alakítja
    String toString() const override; // kiírható formátumba alakítja
};

std::ostream& operator<<(std::ostream& os, const Film& film); // kiírható formátumban kiírja a filmet

#endif 