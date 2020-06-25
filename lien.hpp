// Auteur: Vincent Bray, BRAV20069009
#ifndef _LIEN_HPP
#define _LIEN_HPP
#include <string>
using namespace std;

// C'est une classe qui represente un "lien".
class lien {
private:
    string type;
public:
    // Constructeur
    lien();
    // Destructeur
    virtual ~lien();
    // Getter
    const string &getType() const;
    // Setter
    void setType(const string &type);
};

#endif
