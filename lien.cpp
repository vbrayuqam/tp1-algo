// Auteur: Vincent Bray, BRAV20069009
#include "lien.hpp"

lien::lien() {}
const string &lien::getType() const {
    return type;
}
void lien::setType(const string &type) {
    lien::type = type;
}
lien::~lien() {}
