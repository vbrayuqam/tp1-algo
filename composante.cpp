// Auteur: Vincent Bray, BRAV20069009
#include "composante.hpp"

const string &composante::getType() const {
    return type;
}
void composante::setType(const string &type) {
    composante::type = type;
}
composante::~composante() {}

