#include "menu.h"
#include "filmtar.h"
#include "film.h"
#include "sajat_string.h"

int main() {
    //Tesztprogram vaza a Filmtar projekthez.

    // Osztalyok kapcsolatanak demonstralasa
    Filmtar teszt_tar;
    
    // A film altipusok letrehozasa
    Film* horror = new HorrorFilm(String("Alien"), 117, 1979, 9);
    Film* csaladi = new CsaladiFilm(String("Shrek"), 90, 2001, 12);
    
    // A filmek hozzaadasa a Filmtarhoz
    teszt_tar.hozzaad(horror);
    teszt_tar.hozzaad(csaladi);
  
    

    Menu fomenu;
    fomenu.run();
    
    return 0;
}