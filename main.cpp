#include <locale>
#include <iostream>
#include <regex>
#include <cctype>    // pour tolower et toupper 
#include <string>  
#include <fstream>   
#include <algorithm> // pour transform 
#include "FileHandling.hpp"
#include "CWordStat.h"




bool ecrire(const std::string &ligne, size_t lineNumber, size_t wordNumber, const std::string &word) {
    // Affiche les informations du mot actuel
    std::cout << "Ligne " << lineNumber << ", Mot " << wordNumber << ": " << word << std::endl;

    if (word == "STOP") {
        return false; // Passer à la ligne suivante
    }

    return true; // Continuer le traitement
}
void test(const char *file,CWordStat &stat)
{
	std::cout << file << std::endl ;
	ExtractWords<CWordStat &>(file, stat);
	//stat.sortWords();
	//stat.printStats();
	
	
}


int main()
{
	// Mise en place de la locale pour que la conversion de casse (std::lower) puisse g�rer les carat�res accentu�s
	// Par d�fault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'�crit "fr_FR"
	std::locale::global(std::locale("fr_FR"));
	CWordStat MajStats;
	
	IterateOnFileDir<1,2,CWordStat &>("/Users/user/Downloads/converted/", MajStats);
	std::cout << "fin " << std::endl;
	MajStats.sortWords();
	MajStats.printStats();
    	

    return EXIT_SUCCESS;

}
