// Auteur: Vincent Bray, BRAV20069009
#include "engrenage.hpp"

int engrenage::getDents() const {
    return dents;
}
void engrenage::setDents(int dents) {
    engrenage::dents = dents;
}
engrenage::~engrenage() {}
engrenage::engrenage(int dents) : dents(dents) {}
