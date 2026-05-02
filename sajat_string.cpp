#include "sajat_string.h"
#include <cstring>

/// @brief konstruktor 
String::String(): adat(nullptr), hossz(0){};

/// @brief konstruktor szovegbol ha ures mutatot kap default konstruktor
/// @param szoveg 
String::String(const char* szoveg){
    if(szoveg == nullptr){
        adat = nullptr;
        hossz = 0;
    }
    else{
        hossz = strlen(szoveg);
        adat = new char[hossz + 1];
        strcpy(adat, szoveg);
    }
}

/// @brief copy konstruktor
/// @param string 
String::String(const String& string){
    hossz = string.hossz;
    if (string.adat == nullptr) {
        adat = nullptr;
    }
    else {
        adat = new char[hossz + 1];
        strcpy(adat, string.adat);
    }
}

/// @brief destruktor
String::~String(){
    delete[]adat;
}

/// @brief egyenloseg operator
/// @param rhs 
/// @return felul irja a regi stringet
String& String::operator=(const String& rhs){
    if(this == &rhs){
        return *this;
    }
    hossz = rhs.hossz;

    delete[] adat;

    if(rhs.adat == nullptr){
        adat = nullptr;
        return *this;
    }
    adat = new char[hossz+1];
    strcpy(adat, rhs.adat);

    return *this;
}

/// @brief osszeado operator
/// @param rhs 
/// @return vissza ad egy uj stringet amiben osszefuzi a ket elozot
String String::operator+(const String& rhs)const{
    String ujadat;
    ujadat.hossz = hossz + rhs.hossz; 

    //teszteljuk azt hogy nem a null prtmindketto
    if (ujadat.hossz > 0) {
        ujadat.adat = new char[ujadat.hossz + 1];

        if(adat != nullptr){    
            strcpy(ujadat.adat,adat);
        }
        else{
            ujadat.adat[0] = '\0';
        }

        if(rhs.adat != nullptr){
           strcat(ujadat.adat,rhs.adat);
        }
    }

    return ujadat;
}

/// @brief egyenloseg vizsgalo ket string kozott
/// @param rhs 
/// @return igaz ha egyenlo 
bool String::operator==(const String& rhs)const{

    //ha veletlen mindketto nullptr lenne igazat ad vissza
    if(adat == rhs.adat){
        return true;
    }

    //tesztel hogy nem-e nullptr valamelyik mert az strcmp nem tudja ertelmezni
    if(adat == nullptr || rhs.adat== nullptr){
        return false;
    }

    if(strcmp(adat, rhs.adat)== 0){
        return true;
    }
    return false;
}

bool String::illeszkedik(const String& minta)const{
    if(adat == nullptr || minta.adat == nullptr){
        throw "Null pointer hiba az illeszkedik fuggvenyben!";
    }

    int csillagI = -1;
    for (size_t i = 0; i< minta.hossz; i++){
        if(minta.adat[i] == '*'){
            csillagI = i;
        }
    }

     // osszehasonlitas ha nincs benne csillag
    if(csillagI == -1){
        if(strcmp(adat,minta.adat) == 0)
            return true;
        else{
            return false;
        }
    }

    // osszehasonlitas ha az elejen van a csillag
    if(csillagI == 0){

        // ha a bemeneti szoveg hosszabb mint az eltarolt kilep
        if(hossz + 1 < minta.hossz) return false; //csillag nelkuli hossz

        // a bemenet pointeret eltoljuk hogy ne legyen benne a *
        const char* MintaMasolat = minta.adat + 1;

        // annyival tolja arrebb a az eredeti pointert, hogy pont annyi karakter legyen mint a bemenetben es azt hasonlitja ossze a bemenettel
        if (strcmp(adat + (hossz - (minta.hossz - 1)), MintaMasolat) == 0){ //-1 a csillag miatt
            return true;
        }
        else{
            return false;
        }
    }

    // osszehasonlitas ha a vegen van a csillag
    if(csillagI == (int)minta.hossz - 1){//-1 a csillag miatt

        // ha a bemeneti szoveg hosszabb mint az eltarolt kilep
        if(hossz + 1 < minta.hossz) return false; //-1 csillag nelkuli hossz

        // osszehasonlitjuk a csillag hosszaig a caStr -t a bemenettel
        if(strncmp(adat, minta.adat, minta.hossz-1) == 0){ //-1 a csillag miatt
            return true;
        }
        else{
            return false;
        }
    }

    // osszehasonlitas ha közötte van a csillag
    else{
        // kette bontjuk a bemenetet

        // eleje hossza: csillag pozicioja
        int ElejeHossz = csillagI;
        // vege hossza: teljeshossz - eleje hossz - 1 (csillag)
        int VegeHossz = (int)minta.hossz - csillagI - 1;

        // ha rovidebb a vizsgalt szo mint a bemenet ket fele osszesen
        if(hossz < (size_t)(ElejeHossz + VegeHossz)) return false;

        // 1. eleje ellenorzese
        if(strncmp(adat, minta.adat, ElejeHossz) != 0) return false;

        // 2. vege ellenorzese
        // a vege pointeret a * utani karakterre allitjuk
        const char* Vege = minta.adat + csillagI + 1;

        //osszehasonlitja az Vege-t az eredeti vegevel
        if(strcmp(adat + (hossz - VegeHossz), Vege) == 0){
            return true;
        }
        else{
            return false;
        }
    }

}

/// @brief kinyeri a nyers stringet
/// @return string pointer
const char* String::c_str() const{
    return adat != nullptr ? adat : "";        
}

std::ostream& operator<<(std::ostream& os, const String& str){
    os << str.c_str();
    return os;
}
