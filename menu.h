#ifndef MENU_H
#define MENU_H

#include "filmtar.h"
#include "sajat_string.h"

class Menu{
    Filmtar tar;

    int fomenu();
    void letrehozasFolyamat();
    void modositasFolyamat();
    void torlesFolyamat();
    void keresesFolyamat();
    void listazasFolyamat();
    Film* valasztasFolyamat();

    String bekerString(const char* prompt);
    int bekerInt(const char* prompt);
public:
    Menu();
    ~Menu();

    void run();
};

#endif