// Auteur: Vincent Bray, BRAV20069009
#ifndef _COMPOSANTE_H
#define _COMPOSANTE_H
#include <string>
using namespace std;

// C'est une classe qui represente une "composante".
class composante {
private:
    string type;
public:
    // Destructeur
    virtual ~composante();
    // Getter
    const string &getType() const;
    // Setter
    void setType(const string &type);
};

#endif
