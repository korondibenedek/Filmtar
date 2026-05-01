#include <cstddef>

class String{
    char* adat;
    size_t hossz;
public:
    String();
    String(const char* szöveg);
    String(const String& string);
    ~String();
    String& operator=(const String& rhs);
    String& operator+ (const String& rhs);
    bool operator==(const String& rhs); 
    bool illeszkedik(const String& minta); //ez keresi ki a *-ot
    const char* c_str() const; //nyers mutatot ad vissza
};