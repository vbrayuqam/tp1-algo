// Auteur: Vincent Bray, BRAV20069009
#include "vis.hpp"

int vis::getSillons() const {
    return sillons;
}
void vis::setSillons(int sillons) {
    vis::sillons = sillons;
}
vis::~vis() {}
vis::vis(int sillons) : sillons(sillons) {}
