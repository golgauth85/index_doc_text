#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>    // pour tolower et toupper  
#include <algorithm> // pour transform
#include <regex>
#include <map>
#include <locale>
#include <unordered_map>
#include "CWordStat.h"

class FileHandling
{
private:
	struct DirListStruct;
	typedef DirListStruct* DIRHANDLE;
	enum class ETypeResult
	{
		FILE_DIR,
		ONLY_FILE,
		ONLY_DIR
	};

public:
	FileHandling(const char *baseDir);
	FileHandling(const std::string &s) : FileHandling(s.c_str()) {}
	virtual ~FileHandling();
	inline bool GetNext(std::string &str) { return(GetNextElmt(str,ETypeResult::FILE_DIR)); }
	inline bool GetNextFile(std::string &str) { return(GetNextElmt(str,ETypeResult::ONLY_FILE)); }
	inline bool GetNextDir(std::string &str) { return(GetNextElmt(str,ETypeResult::ONLY_DIR)); }

public:
	static bool isFile(const char *file);
	static bool isDir(const char *file);
	static void ParseFileName(const char * const file,std::string &dir,std::string &fileName,std::string &ext);
	static size_t GetFileSize(const char * const file);

private:
	FileHandling(const FileHandling &obj) {}
	FileHandling& operator=(const FileHandling &obj) { return(*this); }
	bool GetNextElmt(std::string &str,ETypeResult kind);

private:
	DIRHANDLE hDir;
};


struct my_tolower {
   
    char operator()(char c) const {
        // Vérifier si le caractère est une lettre majuscule
        if (std::isalpha(c, std::locale("fr_FR"))) {
            return std::tolower(c, std::locale("fr_FR"));
        }
        return c; // Retourne le caractère tel quel sinon
    }
};





template <class F>
void ExtractWords(const char *file, F &&func) {
    std::ifstream infile(file);
    if (!infile) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << file << std::endl;
        return;
    }

    std::string line;
    size_t lineNumber = 0;
    std::regex pattern(R"#(\w[\w\-]*)#"); 

    while (std::getline(infile, line)) {
        ++lineNumber; 

        // Transformer la ligne en minuscules
        std::transform(line.begin(), line.end(), line.begin(), my_tolower());

        auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto words_end = std::sregex_iterator();
        size_t wordNumber = 0;

        for (auto it = words_begin; it != words_end; ++it) {
            ++wordNumber; 

            std::string word = it->str(); 

    
            bool continueProcessing = func(line, lineNumber, wordNumber, word);

            // Arrêter le traitement si le foncteur retourne `false`
            if (!continueProcessing) {
                break;
            }
        }
		//return func;
    }
}


template <int I=0, int Limit=0, class F>
void IterateOnFileDir(const char *baseDir,F &&func)
{
	std::string fileName;

	FileHandling dirList(baseDir);
	int i=0;
	while ((Limit==0 || i<Limit) && dirList.GetNextFile(fileName))
	{
		std::string file(baseDir);
		file+=fileName;

		//func(file.c_str(), stats);
		std::cout << file << std::endl ;
		ExtractWords<CWordStat &>(file.c_str(), func);
		
		++i;
		if (I!=0 && i%I==0)
		{
			std::cout << i << " fichier";
			if (i>1) std::cout << 's';
			std::cout << " traité";
			if (i>1) std::cout << 's';
			std::cout << std::endl;
		}
	}
}