//
//  main.cpp
//  Author-ID XTRA_CRED
//  Program Build and Client Interaction
//
//  Created by Andrew Masters on 5/30/17.
//  Copyright © 2017 IronHack Studios. All rights reserved.
//

#include <iostream>
#include <string>
#include <functional>
#include <unistd.h>
#include <stdlib.h>
#include "DataBase.h"
using namespace std;

int main(int argc, const char * argv[]) {
    int i, arrSize, randArrNum, randLineNum;
    string input, testLine, multiLines, author, comment, answer,
    showAuthors = "Alexandre Dumas\nSir Arthur Conan Doyle\nCharles "
        "Dickens\nJane Austen\nJules Verne\nMark Twain\nRobert Louis Stevenson";
    
    DataBaseEntry Dumas("alexandre_dumas.txt", "test_dumas.txt");

    DataBaseEntry Doyle("arthur_conan_doyle.txt", "test_doyle.txt");

    DataBaseEntry Dickens("charles_dickens.txt", "test_dickens.txt");

    DataBaseEntry Austen("jane_austen.txt", "test_austen.txt");
    
    DataBaseEntry Verne("jules_verne.txt", "test_verne.txt");

    DataBaseEntry Twain("mark_twain.txt", "test_twain.txt");
    
    DataBaseEntry Stevenson("robert_louis_stevenson.txt", "test_stevenson.txt");
    
    cout << "Given These Authors..." << endl;
    sleep(1);
    cout << "Alexandre Dumas" << endl;
    sleep(1);
    cout << "Sir Arthur Conan Doyle" << endl;
    sleep(1);
    cout << "Charles Dickens" << endl;
    sleep(1);
    cout << "Jane Austen" << endl;
    sleep(1);
    cout << "Mark Twain" << endl;
    sleep(1);
    cout << "Robert Louis Stevenson" << endl << endl;
    sleep(1);
    
    cout << "Can I Guess The Author You Resemble?" << endl;
    sleep(2);
    cout << "Begin typing..." << endl << endl;
    while(input != "terminateprogram"){
        getline(cin, input);
        
        if(input == "makespace") {
            for (int i = 0; i < 53; i++)
                cout << endl;
            
            cout << "Begin typing..." << endl << endl;
            getline(cin, input);
        }
        else if(input == "okay"){
            cout << endl;
            cout << "Go ahead, talk to me..." << endl << endl;
            getline(cin, input);
        }
        if(input == "Authors in data base"){
            cout << showAuthors << endl << endl;
            getline(cin, input);
        }
        
        if(input == "terminateprogram")
            break;
        
        while(cin.get() != '\n'){
            getline(cin, input);
        }
        
        if(input == "Dumas" || input == "Doyle" || input == "Dickens" ||
           input == "Austen" || input == "Verne" || input == "Twain" ||
           input == "Stevenson")
        {
            multiLines.clear();
            testLine.clear();
            randLineNum = rand() % 5620;
            
            cout << "A Random Excerpt From " << input << "..." << endl;
            
            input.insert(0, "test_");
            input.append(".txt");
            ifstream infile(input);
            
            if(!infile)
                cout << "Test file Not Found" << endl;
            
            for(i = 0; !infile.eof(); i++){
                getline(infile, testLine);
                if(i >= randLineNum && i <= randLineNum + 4){
                    multiLines.append(testLine + " ");
                }
            }
            cout << multiLines << endl << endl;
            input = multiLines;
            infile.close();
            
            Dumas.createProb(input);
            Doyle.createProb(input);
            Dickens.createProb(input);
            Austen.createProb(input);
            Verne.createProb(input);
            Twain.createProb(input);
            Twain.createProb(input);
            Stevenson.createProb(input);
            
            FindMax DumasProb("Alexandre Dumas", Dumas);
            FindMax DoyleProb("Sir Arthur Conan Doyle", Doyle);
            FindMax DickensProb("Charles Dickens", Dickens);
            FindMax AustenProb("Jane Austen", Austen);
            FindMax VerneProb("Jules Verne", Verne);
            FindMax TwainProb("Mark Twain", Twain);
            FindMax StevensonProb("Robert Louis Stevenson", Stevenson);
            
            author = findMaxProb(DumasProb, DoyleProb, DickensProb, AustenProb,
                                 VerneProb, TwainProb, StevensonProb);
            if(author == "none"){
                cout << "This doesn't match any author that I know..." << endl;
                sleep(1);
                cout << "Maybe you should try again" << endl << endl << endl;
            }
            else cout << "This excerpt is similar to " << author << endl << endl
                << endl;
            
        }
        else{
        
            Dumas.createProb(input);
            Doyle.createProb(input);
            Dickens.createProb(input);
            Austen.createProb(input);
            Verne.createProb(input);
            Twain.createProb(input);
            Twain.createProb(input);
            Stevenson.createProb(input);
            
            FindMax DumasProb("Alexandre Dumas", Dumas);
            FindMax DoyleProb("Sir Arthur Conan Doyle", Doyle);
            FindMax DickensProb("Charles Dickens", Dickens);
            FindMax AustenProb("Jane Austen", Austen);
            FindMax VerneProb("Jules Verne", Verne);
            FindMax TwainProb("Mark Twain", Twain);
            FindMax StevensonProb("Robert Louis Stevenson", Stevenson);
            
            author = findMaxProb(DumasProb, DoyleProb, DickensProb, AustenProb,
                        VerneProb, TwainProb, StevensonProb);
            
            string comments[] = {"Hmmm, that's a toughie",
                "Wow this is interesting", "Hmmmmm",
                "Wow you're a great writer", "Yikes",
                "Oh geez", "This is awesome",
                "This is so good, you should write a book",
                "yeah ha ha... okay"};
            
            string answers[] = {"I'm guessing it's ",
                "Your writing style resembles ",
                "This text is really similar to ", "That sounds a lot like ",
                "This is probably written by "};
            
            arrSize = (sizeof(comments) / sizeof(comments[0]));
            randArrNum = rand() % arrSize;
            comment = comments[randArrNum];
            
            arrSize = (sizeof(answers) / sizeof(answers[0]));
            randArrNum = rand() % arrSize;
            answer = answers[randArrNum];
            
            cout << comment;
            sleep(1);
            
            cout << ", let me think..." << endl;
            sleep(2);
            
            if(author == "none"){
                cout << "\nThis doesn't match anybody that I know..." << endl;
                sleep(1);
                cout << "Maybe you should try again, okay? " << endl << endl;
            }
            else
                cout << answer << author << endl << endl << endl;
        }
    }
    return 0;
}
