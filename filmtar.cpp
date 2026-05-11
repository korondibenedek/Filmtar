#include "filmtar.h"
#include "sajat_string.h"
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <cstdlib>

/// @brief filmtar konstruktora
Filmtar::Filmtar():db(0), kapacitas(50){
    filmek = new Film*[kapacitas];
    
    for(size_t i = 0; i < kapacitas; i++) {
        filmek[i] = nullptr;
    }
}

/// @brief filmtar destruktora
Filmtar::~Filmtar(){
    for(size_t i = 0; i < db; i++) {
        delete filmek[i];
    }
    delete [] filmek;
}

/// @brief hozza ad egy film tipusu pointert a heterogen kollekciohoz
/// @param uj hozzaadni kivant film pointer
void Filmtar::hozzaad(Film* uj){
    //ervenytelen nullptr
    if (uj == nullptr) throw std::invalid_argument("Hiba: Ures filmet nem lehet a tarhoz adni!");

    //kapaciatas novelese
    if(db >= kapacitas){
        kapacitas += 50;
        Film** ujfilmek = new Film*[kapacitas];
        
        //regi filmek atmasolasa
        for(size_t i = 0; i< db; i++){
            ujfilmek[i] = filmek[i];    
        }

        //ujjonnan lefoglalt pointerek nullptrre allitasa
        for(size_t i= db; i< kapacitas; i++){
            ujfilmek[i] = nullptr;
        }
        delete [] filmek;
        filmek = ujfilmek;
        
    }

    //uj elem hozzadasa
    filmek[db] = uj;
    db++;
}

/// @brief cim alapjan torteno kereses
/// @param feltetel keresett filmcim/filmcimresz *-al
/// @param talalat talalatok szama
/// @return szurt lista a talalatokrol
Film** Filmtar::keresCim(const String& feltetel, int& talalat){
    talalat = 0;
    
    //maximum lehtseges talalat, az osszes
    Film** talalatok = new Film* [db];

    //vegig megy az osszes cimen es osszehasonlitja
    for(size_t i = 0; i< db; i++){
        if(filmek[i]->getCim().illeszkedik(feltetel)){
            talalatok[talalat]= filmek[i];
            talalat++;
        }
    }

    return talalatok;
}

/// @brief idotartam alapjan torteno kereses
/// @param minHossz az intervallum alja 
/// @param maxHossz az intervallum teteje
/// @param talalat talalatok szama
/// @return szurt lista a talalatokrol
Film** Filmtar::keresHossz(int minHossz , int maxHossz, int& talalat){
    talalat = 0;

        //maximum lehtseges talalat, az osszes
    Film** talalatok = new Film* [db];

    //vegig megy az osszes hosszon es osszehasonlitja
    for(size_t i = 0; i< db; i++){
        if(filmek[i]->getHossz() >= minHossz && filmek[i]->getHossz() <= maxHossz){
            talalatok[talalat]= filmek[i];
            talalat++;
        }
    }

    return talalatok;
}

/// @brief kiadasi alapjan torteno kereses
/// @param minEv az intervallum alja 
/// @param maxEv az intervallum teteje
/// @param talalat talalatok szama
/// @return szurt lista a talalatokrol
Film** Filmtar::keresEv(int minEv , int maxEv, int& talalat){
    talalat = 0;

        //maximum lehtseges talalat, az osszes
    Film** talalatok = new Film* [db];

    //vegig megy az osszes hosszon es osszehasonlitja
    for(size_t i = 0; i< db; i++){
        if(filmek[i]->getEv() >= minEv && filmek[i]->getEv() <= maxEv){
            talalatok[talalat]= filmek[i];
            talalat++;
        }
    }

    return talalatok;
}

/// @brief kikeresi a megadott filmet es kitorli
/// @param film torlendo film
void Filmtar::torol(Film* film){

    //megkeressuk a film indexet a filmtarban
    for(size_t i = 0; i< db; i++){
        if(filmek[i] == film){
            delete filmek[i];

            //rashifteljuk a filmtar veget
            for(size_t j = i; j < db - 1; j++ ){
                filmek[j] = filmek[j+1];
            }

            //a regi utolso helyet kinullazzuk
            filmek[db - 1] = nullptr; 
            db -= 1;
            return;
        }
    }
    
    //ha ide eljut a kod az azt jelenti hogy nics benne a tommben a film
    throw std::invalid_argument("Hiba: A torlendo film nem talalhato a tarban!");
}

/// @brief elmenti a filmtar.txt -be a filmeket
void Filmtar::fajlba_ment(){
    //fajl megnyitasa olvasasra
    std::ofstream f("filmtar.txt");

    if(!f.is_open()){
        throw std::runtime_error("Hiba: Nem sikerult megnyitni a fajlt mentesre!");
    }

    //filmek fajlba betoltese
    for(size_t i = 0; i< db; i++){
        f << filmek[i]->encode() << "\n"; // az encode tartalmazza a tipusjelzot
    }

    f.close();
}

/// @brief betolti a filmtar.txt -bol a filmeket
void Filmtar::fajlbol_betolt(){
    // fajl megnyitasa olvasasra
    std::ifstream f("filmtar.txt");

    if(!f.is_open()){
        throw std::runtime_error("Hiba: Nem sikerult megnyitni a fajlt betoltesre!");
    }

    char sor[512];
    // soronkent beolvasunk, amig van adat
    while (f.getline(sor, 512)) {
        
        //darabolas a pontosvesszok (;) menten
        char* tipus_str = strtok(sor, ";");
        char* cim_str   = strtok(nullptr, ";");
        char* hossz_str = strtok(nullptr, ";");
        char* ev_str    = strtok(nullptr, ";");
        char* extra_str = strtok(nullptr, ";");
        
        //ha barmi hianyzik (ures vagy hibas sor, aka. == nullptr), atugorjuk
        if (!tipus_str || !cim_str || !hossz_str || !ev_str || !extra_str) continue;
        
        //a Windows-os (\r) karakter levagasa, ha ott lenne
        char* per_r = strchr(extra_str, '\r'); //vissza adja a keresett karakter pointert
        if (per_r != nullptr) *per_r = '\0';

        //tipuskonverziok
        String cim(cim_str);
        int hossz = atoi(hossz_str);
        int ev = atoi(ev_str);
        Film* uj = nullptr;
        
        //a tipusjelzo alapjan letrehozzuk a megfelelo objektumot
        if (strcmp(tipus_str, "H") == 0) uj = new HorrorFilm(cim, hossz, ev, atoi(extra_str));
        else if (strcmp(tipus_str, "C") == 0) uj = new CsaladiFilm(cim, hossz, ev, atoi(extra_str));
        else if (strcmp(tipus_str, "D") == 0) uj = new DokumentumFilm(cim, hossz, ev, String(extra_str));
        
        //hozzadjuk a tarhoz
        if (uj != nullptr) hozzaad(uj);
    }
    
    f.close();
}
