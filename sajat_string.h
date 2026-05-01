#ifndef SAJAT_STRING_H
#define SAJAT_STRING_H

#include <cstddef>
#include <iostream>

class String{
    char* adat;
    size_t hossz;
public:
    String();
    String(const char* szöveg);
    String(const String& string);
    ~String();
    String& operator=(const String& rhs);
    String operator+(const String& rhs) const;
    bool operator==(const String& rhs) const; 
    bool illeszkedik(const String& minta) const; //ez keresi ki a *-ot
    const char* c_str() const; //vissaadja a nyers karaktertömböt
};

std::ostream& operator<<(std::ostream& os, const String& str); // kiírható formátumba alakítja

#endif