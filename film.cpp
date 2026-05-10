#include "film.h"
#include "sajat_string.h"

/// @brief konstruktor
/// @param cim film cime
/// @param hossz film hossza 
/// @param ev kiadasi ev
Film::Film(String cim, int hossz, int ev):cim(cim), idotartam(hossz), kiadasi_ev(ev){}

/// @brief destruktor
Film::~Film(){}

/// @brief fajlba menheto alakba irja
/// @return atalakitott string
String Film::encode() const{
    return cim + ";" + String(idotartam) + ";" + String(kiadasi_ev);
}

/// @brief kiirhato alakba irja
/// @return atalakitott string
String Film::toString() const{
    String Cim = "Cim: "; //csak egyik iranyba van megirva az osszefuzes :)
    return  Cim + cim + "; Idotartam: " + String(idotartam) + "; Kiadasi ev: " + String(kiadasi_ev);
}

/// @brief Horror film konstruktora
/// @param cim film cime
/// @param hossz film hossza 
/// @param ev kiadasi ev
/// @param ijesztes 1-10- es skala hogy mennyire ijeszto a film
HorrorFilm::HorrorFilm(String cim, int ido, int ev, int ijesztes): Film(cim,ido,ev), ijesztes_faktor(ijesztes){}

/// @brief fajlba menheto alakba irja, plusz adattag ijesztes_faktor
/// @return atalakitott string
String HorrorFilm::encode() const{
    return Film::encode() + ";" + String(ijesztes_faktor);
}

/// @brief kiirhato alakba irja, plusz adattag ijesztes_faktor
/// @return atalakitott string
String HorrorFilm::toString() const{
    return Film::toString() + "; Ijesztesi faktor (1-10): " + String(ijesztes_faktor); 
}

/// @brief Dokumentum film konstruktora
/// @param cim film cime
/// @param hossz film hossza 
/// @param ev kiadasi ev
/// @param tema rövid leírás a film temajarol
DokumentumFilm::DokumentumFilm(String cim, int ido, int ev, String tema): Film(cim,ido,ev), tema(tema){}

/// @brief fajlba menheto alakba irja, plusz adattag tema
/// @return atalakitott string
String DokumentumFilm::encode() const{
    return Film::encode() + ";" + tema;
}

/// @brief kiirhato alakba irja, plusz adattag tema
/// @return atalakitott string
String DokumentumFilm::toString() const{
    return Film::toString() + "; Tema: " + tema;
}

/// @brief Csaladi film konstruktora
/// @param cim film cime
/// @param hossz film hossza 
/// @param ev kiadasi ev
/// @param korhatar film korhatara
CsaladiFilm::CsaladiFilm(String cim, int ido, int ev, int korhatar): Film(cim,ido,ev), korhatar(korhatar){}

/// @brief fajlba menheto alakba irja, plusz adattag korhatar
/// @return atalakitott string
String CsaladiFilm::encode() const{
    return Film::encode() + ";" + String(korhatar);
}

/// @brief kiirhato alakba irja, plusz adattag korhatar
/// @return atalakitott string
String CsaladiFilm::toString() const{
    return Film::toString() + "; Korhatar: " + String(korhatar);
}
