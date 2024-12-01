#include <locale>
#include <string>
#include <algorithm>
#include <iostream>

// Fonction pour convertir une chaîne en minuscules tout en respectant les accents (UTF-8)
struct my_tolower {
    std::locale loc;
    
    my_tolower() : loc(std::locale("fr_FR")) {} // Utiliser la locale UTF-8
    
    char operator()(char c) const {
        // Appliquer tolower de la locale pour garder les caractères accentués
        return std::tolower(c, loc);
    }
};
int main() {
    std::string texte = "Élève d'école";  // Exemple avec des accents
    
    // Convertir le texte en minuscules tout en respectant les accents
    std::transform(texte.begin(), texte.end(), texte.begin(), my_tolower());
    
    std::cout << texte << std::endl;  // Affiche : "élève d'école"
    
    return 0;
}