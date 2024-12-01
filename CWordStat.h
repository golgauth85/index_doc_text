#pragma once

#include <fstream>  // Pour écrire dans un fichier
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

class CWordStat {
private:
    std::map<std::string, int> m;

public:
    bool operator()(const std::string &line, size_t lineNumber, size_t wordNumber, const std::string &word);
    void operator[](const std::string word);

    void printStats() const;

    const std::map<std::string, int>& getStats() const;
    void sortWords() ;
    void writeStopWordsList(const std::string& filename) const;
};
