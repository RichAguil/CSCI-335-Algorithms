#ifndef PROJECT2_H
#define PROJECT2_H

#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class KeywordsInFile {
    private:
        char character;
        int numberOfLines = 1;
        std::ifstream keyWordsFile;
        std::ifstream textFile;
        std::unordered_set<std::string>hashSetKeyWords;
        std::unordered_map<std::string, std::vector<int>>keyWordsPerLine;
    public:
        KeywordsInFile() = delete;
        KeywordsInFile(std::string& filename_with_keywords, std::string& filename_with_text);
        bool KeyWordFound(std::string& keyword);
        int KeywordInLine(std::string& keyword, int& line_number);
        int TotalOccurences(std::string& keyword);
        friend std::ostream& operator<<(std::ostream& output, KeywordsInFile& newObject);
};

std::ostream& operator<<(std::ostream& output, KeywordsInFile& newObject);

#include "project2.cpp"
#endif
