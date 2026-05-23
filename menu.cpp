# include "menu.h"
#include <stdexcept>
#include "memtrace.h"


/// @brief Menu konstruktora: indulaskor betolti az adatokat fajlbol
Menu::Menu() {
    try {
        tar.fajlbol_betolt();
        std::cout << "Adatbazis sikeresen betoltve a fajlbol!\n";
    } catch(const std::exception& e) {
        std::cout << e.what() << " (Ures adattarral indul a program)\n\n";
    }
}

/// @brief Menu destruktora: kilepeskor elmenti az adatokat fajlba
Menu::~Menu() {
    try {
        tar.fajlba_ment();
        std::cout << "Adatbazis sikeresen elmentve a fajlba!\n";
    } catch(const std::exception& e) {
        std::cout << "Hiba a mentes soran: " << e.what() << "\n";
    }
}

/// @brief a begepelt kerdest felteszi es a valaszt visszadja
/// @param szoveg feltenni kivant kerdes
/// @return valasztott szam, ha van benne betu -1 el ter vissza
int Menu::bekerInt(const char* szoveg){
    std::cout << szoveg;
    String valasz;
    std::cin >> valasz;
    
    //vegignezzuk a karaktereket hogy csak szam van e benne
    for (size_t i = 0; i < valasz.size(); i++) {
        if (valasz.c_str()[i] < '0' || valasz.c_str()[i] > '9') {
            return -1; //ha talalunk benne betut ervenytelen
        }
    }
    
    return atoi(valasz.c_str());
}

/// @brief 
/// @param szoveg 
/// @return 
String Menu::bekerString(const char* szoveg){
    std::cout << szoveg;
    String valasz;
    std::cin >> valasz;
    return valasz;
}

/// @brief fomenu kiirasa
/// @return valasztott opcio
int Menu::fomenu(){
    using namespace std;
    cout << "\nMenu:" << endl;
    cout << "1. Film hozzaadasa" << endl;
    cout << "2. Film keresese" << endl;
    cout << "3. Film torlese" << endl;
    cout << "4. filmek kilistazasa" << endl;
    cout << "0. Kilepes es mentes." << endl;
    return bekerInt("Adj meg egy opciot (0-4): ");
}

/// @brief kezeli a hozzadas interface-et
void Menu::letrehozasFolyamat(){

    //letrehozasi opciok
    using namespace std;
    cout << "\nMilyen tipusu filmet akarsz letrehozni" << endl;
    cout << "1. Horror Film" << endl;
    cout << "2. Dokumentum Film" << endl;
    cout << "3. Csaladi Film" << endl;
    cout << "0. (vissza)" << endl;

    //kilep ha 0 vagy mas
    int filmtipus = bekerInt("Adj meg egy opciot(0-3): ");
    if (filmtipus > 3 || filmtipus < 1) {
        return;
    }

    //adatbekeres
    String film_cim = bekerString("Adja meg a Film cimet: ");
    int film_hossz = bekerInt("Adja meg a film hosszat percben: ");
    int  film_ev = bekerInt("Adja meg melyik evben keszult a film: ");

    if(film_hossz == -1 || film_ev == -1) {
        std::cout << "Hiba: Ervenytelen szamot adtal meg!\n";
        return;
    }

    //filmek hozzaadasa a tarhoz
    switch (filmtipus){
    case 1 : //HorrorFilm adattagok bekerese es hozzadas
        {
            int extra = bekerInt("Add meg hogy a film mennyire ijeszto (1-10)-es skalan: ");
            if (extra>10 || extra <1){
                cout << "Hiba: nem resze az intervallumnak a szam!\n";
                return;
            }
            HorrorFilm* Horror_Film = new HorrorFilm(film_cim,film_hossz,film_ev,extra);
            tar.hozzaad(Horror_Film);
            cout << "Sikeres hozzadas: " <<Horror_Film->toString()<< endl;
        }
        break;
        
    case 2 : //DokumentumFilm adattagok bekerese es hozzadas
        {
            String extra = bekerString("Add meg roviden a film temajat: ");
            DokumentumFilm* Dokumentum_Film = new DokumentumFilm(film_cim,film_hossz,film_ev,extra);
            tar.hozzaad(Dokumentum_Film);
            cout << "Sikeres hozzadas: " <<Dokumentum_Film->toString() << endl;
        }
        break;

    case 3: //CsaladiFilm adattagok bekerese es hozzadas
        {
            int extra = bekerInt("Add meg a film korhatarat: ");
            CsaladiFilm* Csaladi_Film = new CsaladiFilm(film_cim,film_hossz,film_ev,extra);
            tar.hozzaad(Csaladi_Film);
            cout << "Sikeres hozzadas: " <<Csaladi_Film->toString()<< endl;
        }
        break;

    default:
        std::cout<< "Nincs ilyen opcio!";
        break;
    }

}

/// @brief kilistazza a filmeket
void Menu::listazasFolyamat(){
    std::cout << "\n--- Filmek listaja ---\n";
    int darab = 0;
    Film** osszes = tar.getMind(darab);
    
    if (darab == 0) {
        std::cout << "A filmtar jelenleg ures.\n";
    } else {
        for (int i = 0; i < darab; i++) {
            std::cout << i + 1 << ". " << osszes[i]->toString() << std::endl; //atalakitja stringe es kilistazza
        }
    }
    delete[] osszes; //az ideiglenes tömböt töröljük.
    std::cout << "----------------------\n";
}

/// @brief kiválasztás interface részét kezeli
/// @param lista
/// @param meret lista merete
/// @return kivalasztott efilm pointere
Film* Menu::valasztasFolyamat(Film** lista, size_t meret){
    if(meret == 0) throw std::runtime_error("Hiba: Nincs talalat, ures a lista!"); //ures lista
    if(meret == 1) return lista[0]; //ha csak egy elemu visszadja azt
    
    //kilistazza az elemeket es lehet valasztani
    std::cout << "\n--- Talalatok ---\n";
    for(size_t i = 0; i< meret; i++){
        std::cout << i+1 << ". " << lista[i]->toString() << std::endl; 
    }
    
    int valasztas = bekerInt("Valasszon egy szamot: ");
    if (valasztas < 1 || (size_t)valasztas > meret) {
        throw std::out_of_range("Hiba: Ervenytelen sorszam!");
    }
    
    return lista[valasztas-1];
}

void Menu::torlesFolyamat(){

    //torlesi opciok
    using namespace std;
    cout << "\nMi alapjan akarsz rakeresni a torlendo filmre?: " << endl;
    cout << "1. Cim" << endl;
    cout << "2. Idotartam (intervallum)" << endl;
    cout << "3. Ev (intervallum)" << endl;
    cout << "0. (vissza)" << endl;
    int valasztas = bekerInt("Adj meg egy opciot(0-3):");
    int db = 0;
    Film** talalatok = nullptr; 

    //torles az opciok alapjan
    switch (valasztas)
    {
    case 1: //cim
        {
            String cim = bekerString("Add meg a keresett cimet (hasznalhatsz * karaktert): ");
            talalatok = tar.keresCim(cim, db); 
        }
        break;
    
    case 2: //idotartam
        {
            int minHossz = bekerInt("Add meg a minimum filmhosszt (percben): ");
            int maxHossz = bekerInt("Add meg a maximum filmhosszt (percben): ");
            talalatok = tar.keresHossz(minHossz,maxHossz,db);
        }
        break; 
    case 3: //ev
        {
            int minEv = bekerInt("Add meg a minimum evjaratot: ");
            int maxEv = bekerInt("Add meg a maximum evjaratot: ");
            talalatok = tar.keresEv(minEv,maxEv,db);  
        }
        break;
    default:
        return;
    }

    //talalatok kilistazasa
    try{
        Film* valasztott = valasztasFolyamat(talalatok,db); 
        tar.torol(valasztott); //torles
        cout << "A film sikeresen torolve lett!\n";
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    delete[] talalatok; 
}

void Menu::keresesFolyamat(){
    
    //keresi opciok
    using namespace std;
    cout << "\nMi alapjan akarsz rakeresni filmre?: " << endl;
    cout << "1. Cim" << endl;
    cout << "2. Idotartam (intervallum)" << endl;
    cout << "3. Ev (intervallum)" << endl;
    cout << "0. (vissza)" << endl;
    int valasztas = bekerInt("Adj meg egy opciot(0-3):");
    int db = 0;
    Film** talalatok = nullptr; 

    //kereses az opciok alapjan
    switch (valasztas)
    {
    case 1: //cim
        {
            String cim = bekerString("Add meg a keresett cimet (hasznalhatsz * karaktert): ");
            talalatok = tar.keresCim(cim, db); 
        }
        break;
    
    case 2: //idotartam
        {
            int minHossz = bekerInt("Add meg a minimum filmhosszt (percben): ");
            int maxHossz = bekerInt("Add meg a maximum filmhosszt (percben): ");
            talalatok = tar.keresHossz(minHossz,maxHossz,db);
        }
        break; 
    case 3: //ev
        {
            int minEv = bekerInt("Add meg a minimum evjaratot: ");
            int maxEv = bekerInt("Add meg a maximum evjaratot: ");
            talalatok = tar.keresEv(minEv,maxEv,db);  
        }
        break;
    default:
        return;
    }

    //talalatok kilistazasa
    std::cout << "\n----- Talalatok -----\n";
    if (talalatok == nullptr) {
        std::cout << "Nincsenek talaltok.\n";
    } else {
        for (int i = 0; i < db; i++) {
            std::cout << i + 1 << ". " << talalatok[i]->toString() << std::endl; //atalakitja stringe es kilistazza
        }
    }
    delete[] talalatok; //az ideiglenes tombot toroljuk.
    std::cout << "---------------------\n";


}

/// @brief futtatja a programot
void Menu::run(){
    std::cout << R"(
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⢀⣠⣴⣾⡿⠿⠟⠛⠿⠿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⢀⣴⣿⢿⣿⣿⣧⠀⠀⠀⠀⢠⣿⣿⣿⢿⣷⡄⠱⣦⡀⠀⠀⠀⠀⠀⠀
        ⠀⠀⢀⣾⠏⠀⠀⠙⢿⣿⣧⡀⠀⣠⣿⣿⠟⠁⠀⠹⣿⣆⠈⠻⣦⡀⠀⠀⠀⠀
        ⠀⠀⣾⡏⠀⠀⠀⠀⠈⣿⣿⣷⣾⣿⣿⡏⠀⠀⠀⠀⢸⣿⡆⠀⠈⢻⣄⠀⠀⠀
        ⠀⢸⣿⣷⣤⣤⣤⣤⣴⣿⠋⣠⣤⡈⢻⣷⣤⣤⣤⣤⣴⣿⣷⠀⠀⠀⢻⣆⠀⠀
        ⠀⢸⣿⣿⠿⠿⠿⠿⠿⣿⡀⠻⠿⠃⣸⡿⠿⠿⠿⠿⢿⣿⣿⠀⠀⠀⠀⢿⡄⠀
        ⠀⠀⣿⣇⠀⠀⠀⠀⠀⣿⣿⣶⣶⣾⣿⡇⠀⠀⠀⠀⢰⣿⡇⠀⠀⠀⠀⢸⡇⠀
        ⠀⠀⠘⣿⣆⠀⠀⢀⣼⣿⡟⠁⠈⠻⣿⣿⣄⠀⠀⢠⣾⡟⠀⠀⠀⠀⠀⢸⡇⠀
        ⠀⠀⠀⠘⢿⣷⣶⣿⣿⡟⠀⠀⠀⠀⠘⣿⣿⣷⣶⣿⠏⠀⠀⠀⠀⠀⠀⢸⡇⠀
        ⠀⠀⠀⠀⠀⠉⠻⢿⣿⣷⣤⣤⣤⣤⣴⣿⣿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⣿⠃⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠛⠛⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⠀⠀
        ⠀⠀⠀⠀⠀⣀⣤⣴⠶⠶⠶⠷⠶⠶⢶⣤⣤⣀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠀⠀⠀
        ⠀⢀⣠⡶⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠳⢶⣤⣄⣀⣴⠟⠁⠀⠀⠀
        ⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠀⠀
)";
    std::cout << "            --- FILMTAR ---";

    bool kilep = false;
    while(!kilep){
        int valasz = fomenu();
        
        switch(valasz){
            case 1:
                letrehozasFolyamat();
                break;
            case 2:
                keresesFolyamat();
                break;
            case 3:
                torlesFolyamat(); 
                break;
            case 4:
                listazasFolyamat();
                break;
            case 0:
                kilep = true;
                tar.fajlba_ment(); 
                break;
            default:
                std::cout << "Nincs ilyen opcio!\n";
                break;
        }
    }
}
