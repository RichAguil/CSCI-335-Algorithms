#include "project2.h"
#include <iostream>
#include <fstream>

int main() {

    std::string keyWordsFile = "keyWords.txt";
    std::string testFile = "testFile.txt";
    KeywordsInFile test1(keyWordsFile, testFile);
    std::string word = "Lorem";
    int lineNumber = 1;
    //test1.KeyWordFound(word);
    std::cout<<test1.KeywordInLine(word, lineNumber)<<std::endl;
    //test1.TotalOccurences(word);
    std::cout<<test1;
    return 0;
}
