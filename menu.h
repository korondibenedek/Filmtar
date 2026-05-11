#ifndef MENU_H
#define MENU_H

#include "filmtar.h"
#include "sajat_string.h"

/// @brief inerface-t kezelo Menu
class Menu{
    Filmtar tar;

    int fomenu(); // kiírja a főmenüt és visszaadja a választott menüpont számát
    void letrehozasFolyamat(); // hozzáadás interface részét kezeli
    void modositasFolyamat(); // módosítás interface részét kezeli
    void torlesFolyamat(); //törlés interface részét kezeli
    void keresesFolyamat(); //keresés interface részét kezeli
    void listazasFolyamat(); // listázás interface részét kezeli
    Film* valasztasFolyamat(Film** lista, int meret); // kiválasztás interface részét kezeli

    String bekerString(const char* szoveg); // bekér egy stringet az interfaceről
    int bekerInt(const char* szoveg); // bekér egy intet az interfaceről
public:
    Menu();
    ~Menu();

    void run(); // futtatja a programot  
};

#endif