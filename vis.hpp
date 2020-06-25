// Auteur: Vincent Bray, BRAV20069009
#ifndef _VIS_HPP
#define _VIS_HPP
#include "composante.hpp"

// C'est une classe qui represente une "composante" de type "vis".
class vis : public composante{
private:
    int sillons;
public:
    // Constructeur
    vis(int sillons);
    // Destructeur
    virtual ~vis();
    // Getter
    int getSillons() const;
    // Setter
    void setSillons(int sillons);
};

#endif
