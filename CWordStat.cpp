#include "CWordStat.h"


bool CWordStat::operator()(const std::string &line, size_t lineNumber, size_t wordNumber, const std::string &word) {
    ++m[word];
    return true; 
}

void CWordStat::operator[](const std::string word){
    std::cout << m[word] << std::endl;
};

void CWordStat::printStats() const {
    for (const auto &entry : m) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}

const std::map<std::string, int>& CWordStat::getStats() const {
    return m;
}

void CWordStat::sortWords() {
        // Créer un vector de paires (mot, fréquence)
        std::vector<std::pair<std::string, int>> wordVector(m.begin(), m.end());

        // Trier le vector en fonction de la fréquence, ordre décroissant
        std::sort(wordVector.begin(), wordVector.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second; // Comparer par fréquence en ordre décroissant
        });
}

void CWordStat::writeStopWordsList(const std::string& filename) const {
        // Convertir la map en un vecteur de paires (mot, fréquence)
        std::vector<std::pair<std::string, int>> wordVector(m.begin(), m.end());

        // Tri par fréquence décroissante
        std::sort(wordVector.begin(), wordVector.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });

        // Déterminer les seuils pour les mots les plus fréquents et les moins fréquents
        size_t totalWords = wordVector.size();
        size_t cutoffMostFrequent = totalWords / 100;  // 1% des mots les plus fréquents
        size_t cutoffLeastFrequent = totalWords / 5;   // 20% des mots les moins fréquents

        // Ouvrir un fichier en écriture
        std::ofstream outputFile(filename);

        // Écrire les mots les plus fréquents
        outputFile << "Mots les plus fréquents (1%):\n";
        for (size_t i = 0; i < cutoffMostFrequent; ++i) {
            outputFile << wordVector[i].first << "\n";
        }

        // Écrire les mots les moins fréquents
        outputFile << "\nMots les moins fréquents (20%):\n";
        for (size_t i = totalWords - cutoffLeastFrequent; i < totalWords; ++i) {
            outputFile << wordVector[i].first << "\n";
        }

        // Fermer le fichier
        outputFile.close();
        std::cout << "Liste des stop words écrite dans " << filename << std::endl;
    }