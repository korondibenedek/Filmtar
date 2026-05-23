#include "gtest_lite.h"
#include "filmtar.h"
#include "film.h"
#include "menu.h"
#include "sajat_string.h"

int main() {
    // --- String osztály tesztjei ---
    TEST(StringTeszt, Konstruktorok) {
        String ures;
        EXPECT_EQ((size_t)0, ures.size());
        EXPECT_STREQ("", ures.c_str());

        String szoveg("alma");
        EXPECT_EQ((size_t)4, szoveg.size());
        EXPECT_STREQ("alma", szoveg.c_str());

        String szam(42);
        EXPECT_STREQ("42", szam.c_str());

        String masolat(szoveg);
        EXPECT_STREQ("alma", masolat.c_str());
    } END

    TEST(StringTeszt, Operatorok) {
        String a("alma");
        String b("fa");
        String c = a + b;
        EXPECT_STREQ("almafa", c.c_str());

        String d;
        d = c;
        EXPECT_STREQ("almafa", d.c_str());
        EXPECT_TRUE(c == d);
        EXPECT_FALSE(a == b);
    } END

    TEST(StringTeszt, Illeszkedik) {
        String a("almafa");
        EXPECT_TRUE(a.illeszkedik(String("almafa")));
        EXPECT_TRUE(a.illeszkedik(String("alma*")));
        EXPECT_TRUE(a.illeszkedik(String("*fa")));
        EXPECT_TRUE(a.illeszkedik(String("al*fa")));
        EXPECT_FALSE(a.illeszkedik(String("korte*")));
    } END

    // --- Film osztály és alosztályainak tesztjei ---
    TEST(FilmTeszt, KonstruktorokEsfajlformatum) {
        HorrorFilm h("Ragyogas", 146, 1980, 8);
        EXPECT_STREQ("H;Ragyogas;146;1980;8", h.encode().c_str());
        
        CsaladiFilm c("Shrek", 90, 2001, 12);
        EXPECT_STREQ("C;Shrek;90;2001;12", c.encode().c_str());

        DokumentumFilm d("Bolygonk", 120, 2006, "Termeszet");
        EXPECT_STREQ("D;Bolygonk;120;2006;Termeszet", d.encode().c_str());
    } END

    TEST(FilmTeszt, KiirhatoFormatum) {
        HorrorFilm h("Ragyogas", 146, 1980, 8);
        EXPECT_STREQ("Cim: Ragyogas; Idotartam: 146; Kiadasi ev: 1980; Ijesztesi faktor (1-10): 8", h.toString().c_str());
        
        CsaladiFilm c("Shrek", 90, 2001, 12);
        EXPECT_STREQ("Cim: Shrek; Idotartam: 90; Kiadasi ev: 2001; Korhatar: 12", c.toString().c_str());

        DokumentumFilm d("Bolygonk", 120, 2006, "Termeszet");
        EXPECT_STREQ("Cim: Bolygonk; Idotartam: 120; Kiadasi ev: 2006; Tema: Termeszet", d.toString().c_str());
    } END

    // --- Filmtar (Heterogén Kollekció) tesztjei ---
    TEST(FilmtarTeszt, HozzaadasEsKereses) {
        Filmtar tar;
        tar.hozzaad(new HorrorFilm("Ragyogas", 146, 1980, 8));
        tar.hozzaad(new CsaladiFilm("Shrek", 90, 2001, 12));
        
        int talalat = 0;
        Film** eredmeny = tar.keresCim(String("Ragyogas"), talalat);
        EXPECT_EQ(1, talalat);
        if (eredmeny != nullptr) {
            EXPECT_STREQ("Ragyogas", eredmeny[0]->getCim().c_str());
            delete[] eredmeny;
        }

        eredmeny = tar.keresEv(2000, 2010, talalat);
        EXPECT_EQ(1, talalat);
        if (eredmeny != nullptr) {
            EXPECT_STREQ("Shrek", eredmeny[0]->getCim().c_str());
            delete[] eredmeny;
        }
        
        eredmeny = tar.keresHossz(100, 200, talalat);
        EXPECT_EQ(1, talalat);
        if (eredmeny != nullptr) {
            EXPECT_STREQ("Ragyogas", eredmeny[0]->getCim().c_str());
            delete[] eredmeny;
        }
    } END

    TEST(FilmtarTeszt, Torles) {
        Filmtar tar;
        Film* f1 = new HorrorFilm("Ragyogas", 146, 1980, 8);
        Film* f2 = new CsaladiFilm("Shrek", 90, 2001, 12);
        tar.hozzaad(f1);
        tar.hozzaad(f2);
        
        int talalat = 0;
        Film** osszes = tar.getMind(talalat);
        EXPECT_EQ(2, talalat);
        delete[] osszes;

        tar.torol(f1);
        
        osszes = tar.getMind(talalat);
        EXPECT_EQ(1, talalat);
        EXPECT_STREQ("Shrek", osszes[0]->getCim().c_str());
        delete[] osszes;
        
        // Nem létező film törlése exception-t kell hogy dobjon
        Film* dummy = new HorrorFilm("Dummy", 0, 0, 0);
        bool dobott_kivetelt = false;
        try {
            tar.torol(dummy);
        } catch(const std::invalid_argument&) {
            dobott_kivetelt = true;
        }
        EXPECT_TRUE(dobott_kivetelt);
        delete dummy;
    } END

    return 0;
}