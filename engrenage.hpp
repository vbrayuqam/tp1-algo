// Auteur: Vincent Bray, BRAV20069009
#ifndef _ENGRENAGE_HPP
#define _ENGRENAGE_HPP
#include "composante.hpp"

// C'est une classe qui represente une "composante" de type "engrenage".
class engrenage : public composante{
private:
    int dents;
public:
    // Constructeur
    engrenage(int dents);
    // Getter
    int getDents() const;
    // Setter
    void setDents(int dents);
    // Destructeur
    virtual ~engrenage();
};

#endif
