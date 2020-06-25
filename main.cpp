// Auteur: Vincent Bray, BRAV20069009
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include "constantes.hpp"
#include "composante.hpp"
#include "engrenage.hpp"
#include "vis.hpp"
#include "lien.hpp"
#include "direct.hpp"
#include "chaine.hpp"
#include "essieu.hpp"
using namespace std;

/*
 * Fait la validation du nombre d'arguments.
 *
 * nbArgs: Le nombre d'arguments du programme.
 * tabArgs: Tableau contenant les arguments.
 */
void validationNbArguments(int nbArgs, char** tabArgs) {
    if ( nbArgs != 2 ) {
        cerr << "Le nombre d'arguments est invalide." << endl;
        exit(-1);
    }
}

/*
 * Valide si le fichier donner en argument existe.
 *
 * fichier: Nom du ficher.
 */
void validationFichierExistant(char* fichier) {
    fstream contenu;

    contenu.open(fichier);
    if (contenu.fail()) {
        cerr << MSSG_ERR_FICHIER_INEXISTANT << endl;
        exit(-1);
    }
    contenu.close();
}

/*
 * Valide si il y a le nombre de composante minimal dans le fichier.
 *
 * contenu: "vector" contenant des "string" des noms des composantes.
 */
void validationNbComposanteMin(vector<string> contenu) {
   bool composanteValide;
   int nbComposante = 0;

   for (int i = 0; i < contenu.size(); i++) {
       composanteValide = regex_search(contenu.at(i), regex("engrenage|vis"));
       if (composanteValide) {
           nbComposante += 1;
       }
   }
   if (nbComposante == 0) {
       cerr << MSSG_ERR_UNE_COMPOSANTE_MINIMUM << endl;
       exit(-1);
   }
}

/*
 * Valide si le "string" represenant une composante de type "engrenage" est adequat.
 *
 * mot: "string" contenant le type de la composante.
 */
void validationEngrenage(string mot) {
    if (!regex_search(mot, regex("\\d+"))) {
        cerr << MSSG_ERR_DENTS_ENTIERE << endl;
        exit(-1);
    }
    if (!regex_search(mot, regex("^1\\d+|^2\\d+|^3\\d+|^4\\d+|^5\\d+|^6\\d*|^7\\d*|^8\\d*|^9\\d*"))) {
        cerr << MSSG_ERR_NOMBRE_DENT_MINIMUM << endl;
        exit(-1);
    }
}

/*
 * Valide si le "string" represenant une composante est de type "vis".
 *
 * mot: "string" contenant le type de la composante.
 */
void validationVis(string mot) {
    if (!regex_search(mot, regex("\\d+"))) {
        cerr << MSSG_ERR_SILLONS_ENTIERE << endl;
        exit(-1);
    }
    if (!regex_search(mot, regex("^1|^2|^3|^4"))) {
        cerr << MSSG_ERR_NOMBRE_SILLON << endl;
        exit(-1);
    }
}

/*
 * Valide si le lien suivant une composante de type "vis" est adequat.
 *
 * mot:  "string" contenant le type du lien.
 */
void validationLienVis(string mot) {
    if (!regex_search(mot, regex("direct|chaine|essieu"))) {
        cerr << MSSG_ERR_LIEN_INVALIDE << endl;
        exit(-1);
    }
    if (mot != "direct") {
        cerr << MSSG_ERR_SEULEMENT_DIRECT << endl;
        exit(-1);
    }
}

/*
* Valide si le lien suivant une composante de type "vis" est adequat et retourne le type.
*
* mot:  "string" contenant le type du lien.
*/
string validationLienCompo(string mot) {
    if (!regex_search(mot, regex("direct|chaine|essieu"))) {
        cerr << MSSG_ERR_LIEN_INVALIDE << endl;
        exit(-1);
    }
    return mot;
}

/*
 * Valide si le lien antecedant a une composante de type "vis" est adequat.
 *
 * mot:  "string" contenant le type du lien.
 */
void validationLienAnteVis(string lien) {
    if (lien == "direct") {
        cerr << MSSG_ERR_SEULEMENT_ENGRENAGE_DIRECT << endl;
        exit(-1);
    }
    if (lien == "chaine") {
        cerr << MSSG_ERR_SEULEMENT_ENGRENAGE_CHAINE << endl;
    }
}

/*
 * Valide si la derniere valeur d'un fichier est une composante.
 *
 * mot: "string" contenant la derniere valeur du fichier.
 */
void validationDerniereComposante(string mot) {
    if (mot ==  "chaine") {
        cerr << MSSG_ERR_COMPOSANTE_NECESSAIRE  << mot << "." << endl;
        exit(-1);
    }
    if (mot ==  "essieu") {
        cerr << MSSG_ERR_COMPOSANTE_NECESSAIRE  << mot << "." << endl;
        exit(-1);
    }
    if (mot ==  "direct") {
        cerr << MSSG_ERR_COMPOSANTE_NECESSAIRE  << mot << "." << endl;
        exit(-1);
    }
}

/*
 * Valide le contenu du fichier.
 *
 * contenu: "vector" de "string" des "conposantes" et "liens" contenus dans le fichier.
 */
void validationContenu(vector<string> contenu) {
    string lienAnte = "";
    for(int i = 0; i < contenu.size(); i++) {
        if (contenu.at(i)  == "engrenage") {
            i++;
            validationEngrenage(contenu.at(i));
            i++;

            if (i < contenu.size()) {
                lienAnte = validationLienCompo(contenu.at(i));
            }
        } else if (contenu.at(i)  == "vis") {
            validationLienAnteVis(lienAnte);

            i++;
            validationVis(contenu.at(i));
            i++;

            if (i < contenu.size()) {
                validationLienVis(contenu.at(i));
                lienAnte = "direct";
            }
        } else {
            cerr << MSSG_ERR_COMPOSANTE_INVALIDE << endl;
            exit(-1);
        }
    }
    validationDerniereComposante(contenu.at(contenu.size()-1));
}

/*
 * Fait la lecture du fichier et retourne un "vecteur" des mots contenus.
 *
 * fichier: Nom du fichier.
 */
vector<string> lectureFichier(char* fichier) {
    string mot = "";
    vector<string> mots;
    fstream contenu;

    contenu.open(fichier);
    while (contenu >> mot) {
        mots.push_back(mot);
    }
    contenu.close();

    return mots;
}

/*
 * Cree les composantes qui peuvent etre extraire du fichier.
 *
 * contenant: "vector" de "composante" qui recoit les objets.
 * contenu: "vector" de "string" contenu de composantes dans le fichier.
 */
void creerComposantes(vector<composante*> &contenant, vector<string> contenu) {
    for (int i = 0; i < contenu.size() ; ++i) {
        if (contenu.at(i) == "engrenage") {
            i++;

            stringstream nbDents(contenu.at(i));
            int nbD = 0;
            nbDents >> nbD;
            engrenage * eng = new engrenage(nbD);
            eng->setType("engrenage");
            contenant.push_back(eng);

            i++;
        } else {
            i++;

            stringstream nbSill(contenu.at(i));
            int nbS = 0;
            nbSill >> nbS;
            vis * vi = new vis(nbS);
            vi->setType("vis");
            contenant.push_back(vi);

            i++;
        }
    }
}

/*
 * Cree les liens qui peuvent etre extraire du fichier.
 *
 * contenant: "vector" de "liens" qui recoit les objets.
 * contenu: "vector" de "string" de liens contenu dans le fichier.
 */
void creerLiens(vector<lien*> &contenant, vector<string> contenu) {
    for (int i = 2; i < contenu.size() ; ++i) {
        if (contenu.at(i) == "direct") {
            direct * dir = new direct();
            dir->setType("direct");
            contenant.push_back(dir);
            i++;
            i++;
        } else if (contenu.at(i) == "chaine") {
            chaine * cha = new chaine();
            cha->setType("chaine");
            contenant.push_back(cha);
            i++;
            i++;
        } else {
            essieu * ess = new essieu();
            ess->setType("essieu");
            contenant.push_back(ess);
            i++;
            i++;
        }
    }
}

/*
 * Lance le processus pour faire des requetes.
 */
vector<double> faireRequetes() {
    vector<double> inputs;
    double inputVit;
    double inputCou;

    cout << MSSG_REQUETE_VITESSE << endl;

    cin >> inputVit;
    if (cin.fail()) {
        cerr << MSSG_ERR_VITESSE_INVALIDE << endl;
        exit(-1);
    }

    cout << MSSG_REQUETE_COUPLE << endl;

    cin >> inputCou;
    if (cin.fail()) {
        cerr << MSSG_ERR_COUPLE_INVALIDE << endl;
        exit(-1);
    }
    if ((inputVit > 0 && inputCou < 0) || (inputVit < 0 && inputCou > 0)) {
        cerr << MSSG_ERR_MEME_SIGNE << endl;
        exit(-1);
    }
    inputs.push_back(inputVit);
    inputs.push_back(inputCou);
    return inputs;
}

/*
 * Demande si l'usager veut faire une nouvelle requete et retourne true si c'est le cas.
 */
bool recommencerRequetes() {
    string input;
    bool continuer;

    cout << MSSG_QUESTION_CONTINUER << endl;

    cin >> input;
    if (cin.fail()) {
        cerr << MSSG_ERR_COUPLE_INVALIDE << endl;
        exit(-1);
    }
    if (input == "n") {
        continuer = false;
    } else {
        continuer = true;
    }
    return continuer;
}

/*
 * Fait le calcul des valeurs de vitesse et de couple des compsantes du systeme.
 *
 * index: L'index de la boucle de la fonction antecedente.
 * composantes: "vector" contenant les composantes du systeme.
 * liens: "vector" contenant les liens du systeme.
 * eng1: "engrenage" qui est la 1er composante du couple.
 * eng2: "engrenage" qui est la 2ieme composante du couple.
 * vitesses: "vector" contenant les valeurs de vitesse des composantes.
 * couples: "vector" contenant les valeurs de couple des composantes.
 * efficacites: "vector" contenant les valeurs d'efficacite des composantes.
 */
void faireCalculs(int index, vector<composante*> &composantes, vector<lien*> &liens, engrenage  eng1, engrenage  eng2, vector<double> &vitesses, vector<double> &couples, vector<double> &efficacites) {
    double r = 0;
    if(liens.at(index)->getType() == "chaine") {
        chaine *cha = dynamic_cast<chaine *>(liens.at(index));
        efficacites.push_back(0.8);
        r = static_cast<double>(eng2.getDents())/static_cast<double>(eng1.getDents());
    } else if (liens.at(index)->getType() == "direct") {
        direct *dir = dynamic_cast<direct *>(liens.at(index));
        efficacites.push_back(0.9);
        r = -(static_cast<double>(eng2.getDents())/static_cast<double>(eng1.getDents()));
    } else {
        essieu *ess = dynamic_cast<essieu *>(liens.at(index));
        efficacites.push_back(1.0);
        r = 1;
    }
    vitesses.push_back(vitesses.at(index) / r);
    couples.push_back(couples.at(index) * r);
}

/*
 * Fait le calcul des valeurs de vitesse et de couple des compsantes du systeme. (Surchage)
 *
 * index: L'index de la boucle de la fonction antecedente.
 * composantes: "vector" contenant les composantes du systeme.
 * liens: "vector" contenant les liens du systeme.
 * eng1: "engrenage" qui est la 1er composante du couple.
 * vis1: "vis qui est la 2ieme composante du couple.
 * vitesses: "vector" contenant les valeurs de vitesse des composantes.
 * couples: "vector" contenant les valeurs de couple des composantes.
 * efficacites: "vector" contenant les valeurs d'efficacite des composantes.
 */
void faireCalculs(int index, vector<composante*> &composantes, vector<lien*> &liens, engrenage eng1, vis vis1, vector<double> &vitesses, vector<double> &couples, vector<double> &efficacites) {
    double r = 0;
    efficacites.push_back(1.0);
    r = 1;
    vitesses.push_back(vitesses.at(index) / r);
    couples.push_back(couples.at(index) * r);
}

/*
 * Fait le calcul des valeurs de vitesse et de couple des compsantes du systeme. (Surchage)
 *
 * index: L'index de la boucle de la fonction antecedente.
 * composantes: "vector" contenant les composantes du systeme.
 * liens: "vector" contenant les liens du systeme.
 * vis1: "vis" qui est la 1er composante du couple.
 * eng1: "engrenage" qui est la 2ieme composante du couple.
 * vitesses: "vector" contenant les valeurs de vitesse des composantes.
 * couples: "vector" contenant les valeurs de couple des composantes.
 * efficacites: "vector" contenant les valeurs d'efficacite des composantes.
 */
void faireCalculs(int index, vector<composante*> &composantes, vector<lien*> &liens, vis vis1, engrenage eng1, vector<double> &vitesses, vector<double> &couples, vector<double> &efficacites) {
    double r = 0;
    switch (vis1.getSillons()) {
        case 1:
            efficacites.push_back(0.8);
            break;
        case 2:
            efficacites.push_back(0.7);
            break;
        case 3:
            efficacites.push_back(0.6);
            break;
        case 4:
            efficacites.push_back(0.5);
            break;
    }
    r = static_cast<double>(eng1.getDents())/static_cast<double>(vis1.getSillons());
    vitesses.push_back(vitesses.at(index) / r);
    couples.push_back(couples.at(index) * r);
}

/*
 * Calcule l'efficacite totale du systeme.
 *
 * tab: "vector" contenant les valeurs d'efficacites.
 */
double calculEffTotale(vector<double> tab) {
    double eff = tab.at(0);
    for (int i = 1; i < tab.size(); i++) {
        eff *= tab.at(i);
    }
    return eff;
}

/*
 * Supprime les allocations dynamique des les "vector" de composantes et de liens.
 *
 * composantes: "vector" contenant les composantes du systeme.
 * liens: "vector" contenant les liens du systeme.
 */
void nettoyer(vector<composante*> &composantes, vector<lien*> &liens) {
    for (int i = 0; i < composantes.size(); i++) {
        delete composantes.at(i);
    }
    for (int i = 0; i < liens.size(); i++) {
        delete liens.at(i);
    }
    composantes.clear();
    liens.clear();
}

/*
 * Affiche le resultat des calculs au terminal.
 *
 * vitesses: "vector" contenant les valeurs de vitesse des composantes.
 * couples: "vector" contenant les valeurs de couple des composantes.
 * eff: Efficacite totale du systeme.
 */
void afficherCaculs(vector<double> vitesses, vector<double> couples, double eff) {
    for (int i = 0; i < vitesses.size(); i++) {
        cout << "V" << i << " = " << (vitesses.at(i) * eff) << ", C" << i << " = " << (couples.at(i) * eff) << endl;
    }
}

/*
 * Complete les actions necessaires a l'aboutissement d'une requete.
 *
 * args: "vector" contenant les valeurs de vitesse et de couple initiales.
 * composantes: "vector" contenant les composantes du systeme.
 * liens: "vector" contenant les liens du systeme.
 */
void completerRequetes(vector<double> args, vector<composante*> &composantes, vector<lien*> &liens) {
    vector<double> vitesses;
    vector<double> couples;
    vector<double> efficacites;
    double effTotale = 1;

    vitesses.push_back(args.at(0));
    couples.push_back(args.at(1));

    if (!(composantes.size() == 1)) {
        for (int i = 0; i < liens.size(); i++) {
            if (composantes.at(i)->getType() == "engrenage") {
                if (composantes.at(i + 1)->getType() == "engrenage") {
                    engrenage *eng = dynamic_cast<engrenage *>(composantes.at(i));
                    engrenage *eng2 = dynamic_cast<engrenage *>(composantes.at(i + 1));
                    faireCalculs(i, composantes, liens, *eng, *eng2, vitesses, couples, efficacites);
                } else {
                    engrenage *eng = dynamic_cast<engrenage *>(composantes.at(i));
                    vis *vi = dynamic_cast<vis *>(composantes.at(i + 1));
                    faireCalculs(i, composantes, liens, *eng, *vi, vitesses, couples, efficacites);
                }
            } else {
                vis *vi = dynamic_cast<vis *>(composantes.at(i));
                engrenage *eng = dynamic_cast<engrenage *>(composantes.at(i + 1));
                faireCalculs(i, composantes, liens, *vi, *eng, vitesses, couples, efficacites);
            }
        }
        effTotale = calculEffTotale(efficacites);
    }
    afficherCaculs(vitesses, couples, effTotale);
}

// Fonction main
int main(int argc, char* argv []) {
    // Variables
    vector<string> mots;
    vector<composante *> composantes;
    vector<lien *> liens;

    // Gestion des entrees
    validationNbArguments(argc, argv);
    validationFichierExistant(argv[1]);

    // Gestion du contenu
    mots = lectureFichier(argv[1]);
    validationNbComposanteMin(mots);
    validationContenu(mots);

    // Creation des objets
    creerComposantes(composantes, mots);
    creerLiens(liens, mots);

    // Requetes
    vector<double> arguments;
    bool continuer = false;
    do {
        arguments = faireRequetes();
        completerRequetes(arguments, composantes, liens);
        continuer = recommencerRequetes();
    } while (continuer);
    nettoyer(composantes, liens);
}
