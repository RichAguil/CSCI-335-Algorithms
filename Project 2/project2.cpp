#include "project2.h"
#include <iostream>
#include <sstream>

KeywordsInFile::KeywordsInFile(std::string& filename_with_keywords, std::string& filename_with_text) {

    std::string errorMessage = "One or more files does not exist";
    keyWordsFile.open(filename_with_keywords.c_str());
    textFile.open(filename_with_text.c_str());
    std::string line;
    std::string builtWord = "";

    if (keyWordsFile.fail() || textFile.fail()) { //Checks if the keywords file or text file even exists
        throw errorMessage;
    }

    //Extracting every character from keyword file and building a string from it.
    //This is being done in order to check that each character is alphabetic. Once a non-alphabetic character is reached, that signifies the end of a word, and it's inserted in hashset
    while (keyWordsFile.get(character)) {
        if (isalpha(character)) {
            builtWord.push_back(character);
        } else {
            if (hashSetKeyWords.count(builtWord) != 1 && builtWord != "") { //This checks if the keyword is in the hashset. Returns 1 if key is found, 0 otherwise
		
                hashSetKeyWords.insert(builtWord);
                builtWord = "";
            }
        }
    }

    builtWord = "";

    while (getline(textFile, line)) {//Self-explanatory. Just counts the number of lines in the text;
      numberOfLines++;
    }

    std::vector<int>keyWordsPerLineVector(numberOfLines + 1, 0); //Initializes a vector filled with zeros. The number of zeros will equal the number of lines in the text + 1
    textFile.clear(); //This pair of lines with the textFile object will clear the fail flags and return back to the top of the file. If this isn't done, the following while loop will never execute, as the textFile stream will be at the end
    textFile.seekg(0);
    int currentLine = 1;

    //The following snippet of code loops through text and checks if any of the words in each line are keywords. If they are, insert the keyword as a key in the hashtable, and make its value equal to the vector of zeros
    //As soon as the value is now a vector, increment the appropriate index by 1. Each index represents a line. Zeroth index = total occurences in the whole text, first index = occurences in line 1, second index = occurences in line 2, etc.
    while (getline(textFile, line)) {
        std::istringstream iss(line);      
        while (iss.get(character)) {
            if (isalpha(character)) {
                builtWord.push_back(character);
            } else {
                if (hashSetKeyWords.count(builtWord) == 1 && keyWordsPerLine.count(builtWord) != 1) {
                    keyWordsPerLine[builtWord] = keyWordsPerLineVector;
                    keyWordsPerLine[builtWord][0] += 1;
                    keyWordsPerLine[builtWord][currentLine] += 1;
                } else if (hashSetKeyWords.count(builtWord) == 1) {
                    keyWordsPerLine[builtWord][0] += 1;
                    keyWordsPerLine[builtWord][currentLine] += 1;
                }
                builtWord = "";
            }
        }
        currentLine++;
    }

    textFile.clear();
    textFile.seekg(0);

}

bool KeywordsInFile::KeyWordFound(std::string& keyword) {

    if (keyWordsPerLine.count(keyword) == 1) {
        return true;
    } else {
        return false;
    }

}

int KeywordsInFile::KeywordInLine(std::string &keyword, int& line_number) {

    if (numberOfLines < line_number) { //Throws exception of line number is larger than number of lines in text
        throw std::out_of_range("Line number is out-of-range");
    }

    if (KeyWordFound(keyword) == false) { //Throws error if keyword does not exist
        throw std::domain_error("Try a different word. Word specified is not a keyword");
    }

    return keyWordsPerLine[keyword][line_number];
}

int KeywordsInFile::TotalOccurences(std::string& keyword) {

    if (KeyWordFound(keyword) == false) {
        throw std::domain_error("This is not a keyword");
    }

    return keyWordsPerLine[keyword][0];
}

std::ostream& operator<<(std::ostream& output, KeywordsInFile& newObject) {

    for (auto it = newObject.keyWordsPerLine.begin(); it != newObject.keyWordsPerLine.end(); ++it) { //This creates an iterator object to iterate through hashmap.
        output<<"Keyword: "<<it->first<<", found "<<it->second[0]<<" time(s) in text"<<std::endl;
    }

    return output;
}
