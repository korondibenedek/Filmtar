#ifndef MENU_H
#define MENU_H

#include "filmtar.h"
#include "sajat_string.h"

class Menu{
    Filmtar tar;

    int fomenu(); // kiírja a főmenüt 
    void letrehozasFolyamat(); // hozzáadás interface részét kezeli
    void modositasFolyamat(); // módosítás interface részét kezeli
    void torlesFolyamat(); //törlés interface részét kezeli
    void keresesFolyamat(); //keresés interface részét kezeli
    void listazasFolyamat(); // listázás interface részét kezeli
    Film* valasztasFolyamat(); // kiválsaztás interface részét kezeli

    String bekerString(const char* prompt); // bekér egy stringet az interfaceről
    int bekerInt(const char* prompt); // bekér egy intet az interfaceről
public:
    Menu();
    ~Menu();

    void run(); // futtatja a programot  
};

#endif