#include "sajat_string.h"

class Film{
    String cim;
    int idotartam;
    int kiadasi_ev;
public:
    Film(String  cim, int hossz, int ev);
    virtual ~Film();
    virtual String encode() const = 0;
    virtual String toString() const = 0;
};

class HorrorFilm: public Film{
    int ijesztes_faktor;
public:
    HorrorFilm(String cim, int idö, int ev, int ijesztes);

    String encode() const override;
    String toString() const override;
};

class DokumentumFilm: public Film{
    String tema;
public:
    DokumentumFilm(String cim, int idö, int ev, String tema);

    String encode() const override;
    String toString() const override;
};

class CsaladiFilm: public Film{
    int korhatar;
public:
    CsaladiFilm(String cim, int idö, int ev, String tema);
    String encode() const override;
    String toString() const override;
};