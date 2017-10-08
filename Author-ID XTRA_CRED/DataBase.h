//
//  DataBase.h
//  Process File and Hash It
//
//  Created by Andrew Masters on 5/31/17.
//  Copyright © 2017 IronHack Studios. All rights reserved.
//

#ifndef DataBase_h
#define DataBase_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

//DataBaseEntry class declaration ---------------------------
class DataBaseEntry{
public:
    DataBaseEntry(const string &inputFile, const string &outStr);
    
    void clearProb() {totalProb = 0.0;}
    void calcProb();
    void createProb(string line);
    void addProb(const string & word);
    bool insert(const string & word, double num = 1);
    
    //accessors
    int getTotalLine() {return numOfLines;}
    int getTotalWords() {return totalWords;}
    int getWordsRequested() {return wordsRequested;}
    double getProb() {return totalProb;}
    
private:
    unordered_map<string, double> hashEntry;
    void editDBEntry(string line);
    double totalProb;
    int numOfLines = 0;
    int wordsRequested = 0;
    int totalWords;
};


//DataBaseEntry method implementation -----------------------
DataBaseEntry::DataBaseEntry(const string &inputFile, const string &outStr){
    string line;
    
    ifstream infile(inputFile);
    ofstream outFile(outStr);
        if(!infile || !outFile){
        cout << "File Not Found" << endl;
        return;
    }
    
    for(int lineNum = 0; !infile.eof(); lineNum++){
        getline(infile, line);

        line.erase(remove(line.begin(), line.end(), '\''), line.end());
        
        if(lineNum % 15 == 0){
            outFile << line << "\n";
        }
        else{
            editDBEntry(line);
        }
    }
    infile.close();
    outFile.close();
    
    calcProb();
}



//a method that goes through each word and cleans it of all special chars
void DataBaseEntry::editDBEntry(string line){
    string proLine;
    int wordStart = 0, wordEnd;
    bool inWord = false;
    
    //check each char keeping it if it's a char a-z
    for(int i = 0; i < line.length(); i++){
        proLine.clear();
        line[i] = tolower(line[i]);
        
        if(isalpha(line[i])){
            if(!inWord){
                wordStart = i;
                inWord = true;
            }
            
        }
        else{
            if(inWord){
                inWord = false;
                wordEnd = i;
                for(; wordStart < wordEnd; wordStart++)
                    proLine += line[wordStart];
                insert(proLine);
            }
        }
    }
    if(inWord){
        for(; wordStart < line.length(); wordStart++)
            proLine += line[wordStart];
        insert(proLine);
    }
    if(numOfLines == 0)
        insert("<UNK>", 0.2);

    numOfLines++;
}

// method to insert each word from author into the hash table or increment
// the amount of it alread exists
bool DataBaseEntry::insert(const string & word, double num){
    totalWords++;
    unordered_map<string, double>::iterator iter = hashEntry.find(word);
    if(iter != hashEntry.end()){
        hashEntry.at(word) += 1;
        return true;
    }
    else{
        hashEntry.insert(iter, std::pair<string, double>(word, num));
        return true;
    }
}

//helper method that changes the number of every word to the probability
void DataBaseEntry::calcProb(){
    unordered_map<string, double>::iterator iterBegin = hashEntry.begin();
    unordered_map<string, double>::iterator iterEnd = hashEntry.end();
    for(; iterBegin != iterEnd; iterBegin++)
        hashEntry.at(iterBegin->first) = log(iterBegin->second / totalWords);
}

//method that takes user input, matches the words with words in the hash table
// for every author and adds the probabilites for every word that is entered
// from the user for every author
void DataBaseEntry::createProb(string line){
    clearProb();
    wordsRequested = 0;
    string proline;
    int i, wordStart = 0, wordEnd;
    bool inWord = false;
    
    for(i = 0; i < line.length(); i++){
        proline.clear();
        line[i] = tolower(line[i]);
        
        if(isalpha(line[i])){
            if(!inWord){
                wordStart = i;
                inWord = true;
            }
            
        }
        else{
            if(inWord){
                inWord = false;
                wordEnd = i;
                for(; wordStart < wordEnd; wordStart++)
                    proline += line[wordStart];
                addProb(proline);
            }
        }
    }
    if(inWord){
        for(; wordStart < line.length(); wordStart++)
            proline += line[wordStart];
        addProb(proline);
    }
}


//helper method for createProb that finds the words and adds the probability
// it also keeps track if all the words entered in are unknown
void DataBaseEntry::addProb(const string & word){
    unordered_map<string, double>::iterator iter = hashEntry.find(word);
    if(iter != hashEntry.end()){
        totalProb += hashEntry.at(word);
        wordsRequested += 1;
    }
    else
        totalProb += hashEntry.at("<UNK>");
}



//FindMax class implementation -------------------------
//created for the purpose of finding the author
//with the largest possibility
class FindMax{
public:
    FindMax(string auth, DataBaseEntry per) : author(auth), person(per) {};
    string getAuthor() {return author;}
    double getProbability() {return person.getProb();}
    int getWordsRequested() {return person.getWordsRequested();}
    
protected:
    string author;
    DataBaseEntry person;
};

//method that takes FindMax class as parameters to locate
//the largest possibility and return the author's name
string findMaxProb(FindMax authorOne, FindMax authorTwo, FindMax authorThree,
                            FindMax authorFour, FindMax authorFive,
                            FindMax authorSix, FindMax authorSeven){
    int j;
    string author;
    vector<FindMax> vecPtr;
    
    vecPtr.push_back(authorOne);
    vecPtr.push_back(authorTwo);
    vecPtr.push_back(authorThree);
    vecPtr.push_back(authorFour);
    vecPtr.push_back(authorFive);
    vecPtr.push_back(authorSix);
    vecPtr.push_back(authorSeven);
    
    for(j = 0; j < vecPtr.size(); ){
        if(vecPtr[j].getWordsRequested() == 0 ||
           vecPtr[j].getProbability() == 0){
            vecPtr.erase(vecPtr.begin() + j);
        }
        else j++;
    }
    
    if(vecPtr.empty())
        return "none";
    
    double maxProbability = vecPtr[0].getProbability();
    author = vecPtr[0].getAuthor();
    
    for(int j = 1; j < vecPtr.size(); j++){
        if(vecPtr[j].getProbability() > maxProbability){
            maxProbability = vecPtr[j].getProbability();
            author = vecPtr[j].getAuthor();
        }
    }
    return author;
}

#endif /* DataBase_h */
