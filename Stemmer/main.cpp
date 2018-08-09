//
//  main.cpp
//  Stemmer
//
//  Created by Doğukan Avcı on 07/08/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Stem.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    int success=0;
    int totalWords=0;
    Stem stem;
    string word;
    string targetWord;
    ifstream readData;
    ifstream readResult;
    readData.open("/Users/dogukanavci/Desktop/summerTraining/summerTraining/Stemmer/Assets/voc.txt");
    readResult.open("/Users/dogukanavci/Desktop/summerTraining/summerTraining/Stemmer/Assets/output.txt");
    if(readData.fail() || readResult.fail())
    {
        cerr<<"file failed to open"<<endl;
        return 0;
    }
    while (readData>>word) {
        totalWords++;
        readResult>>targetWord;
        stem.Stemming(word);
        if(word==targetWord){
            success++;
        }
        else{
            cout<<word<<" in steps: "<<stem.step<<" target word: "<<targetWord<<endl;
        }
    }
    std::cout<<endl<<"Succesful results: "<<success<<" out of "<< totalWords <<" words."<<endl<< "Success rate is: "<<(double)success/totalWords<<endl;
    readResult.close();
    readData.close();
    /*Stem stem;
    std::string word;
    word="a";
    stem.Stemming(word);
    std::cout<<word;*/
    return 0;
}
