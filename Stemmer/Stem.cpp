//
//  Stem.cpp
//  Stemmer
//
//  Created by Doğukan Avcı on 07/08/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include "Stem.hpp"
#include <iostream>

void Stem::Partition(){
    //constructing the workspace
    m=0;
    step++;
    partitions.clear();
    it=word.begin();
    //fill partition vector by categorizing letters as v or c
    while(it!=word.end()){
        if(*it<=92 && *it>=65){
            //convert all to lowercase
            *it=*it+32;
        }
        if((*it=='a' || *it=='e' || *it=='i' || *it=='o' || *it=='u')){
            partitions.push_back('v');
        }
        else if (*it=='y'){
            it++;
            if(*it!='a' && *it!='e' && *it!='i' && *it!='o' && *it!='u'){
                partitions.push_back('v');
            }
            else{
                partitions.push_back('c');
            }
            it--;
        }
        else{
            partitions.push_back('c');
        }
        it++;
    }
    //set up m
    for (int i=0; i<partitions.size(); i++) {
        if(partitions[i]=='v' && i<partitions.size()-1){
            if(partitions[i+1]=='c'){
            m++;
            }
        }
    }
}

void Stem::SetFlag(bool currentFlag,int CurrentFlagValue){
    //same index
    flags.push_back(currentFlag);
    flagPriorities.push_back(CurrentFlagValue);
}
void Stem::SetFlags(){
    //first check for plurality and past tense
    //ends with s ,1
    SetFlag(word[word.size()-1]=='s' && m>0 && step==1,1);
    //ends with "oes" ,2
    SetFlag(word[word.size()-1]=='s' && word[word.size()-2]=='e' && word[word.size()-3]=='o' && m>1  && step==1,3);
    //ends with "ies" ,3
    SetFlag(word[word.size()-1]=='s' && word[word.size()-2]=='e' && word[word.size()-3]=='i'&& m>1  && step==1,3);
    //ends with "ed" ,4
    SetFlag(word[word.size()-1]=='d' && word[word.size()-2]=='e' && m>1 && step==1,2);
    //ends with "ing" ,5
    SetFlag(word[word.size()-1]=='g' && word[word.size()-2]=='n' && word[word.size()-3]=='i' && m>1,3);
    //ends with "like" ,6
    SetFlag(word[word.size()-1]=='e' && word[word.size()-2]=='k' && word[word.size()-3]=='i' && word[word.size()-4]=='l'&& m>2,4);
    //ends with double consonant ,7
    SetFlag(word[word.size()-1]==word[word.size()-2] && partitions[word.size()-1]=='c' && step==2,2);
    //ends with "tional" ,8
    SetFlag(word[word.size()-1]=='l' && word[word.size()-2]=='a' && word[word.size()-3]=='n' && word[word.size()-4]=='o' && word[word.size()-5]=='i' && word[word.size()-6]=='t',6);
    //ends with "ation" ,9
    SetFlag(word[word.size()-1]=='n' && word[word.size()-2]=='o' && word[word.size()-3]=='i' && word[word.size()-4]=='t' && word[word.size()-5]=='a',5);
    //ends with "faction" ,10
    SetFlag(word[word.size()-1]=='n' && word[word.size()-2]=='o' && word[word.size()-3]=='i' && word[word.size()-4]=='t' && word[word.size()-5]=='c' && word[word.size()-6]=='a' && word[word.size()-7]=='f' && m>2,7);
    //ends with "ement" ,11
    SetFlag(word[word.size()-1]=='t' && word[word.size()-2]=='n' && word[word.size()-3]=='e' && word[word.size()-4]=='m' && word[word.size()-5]=='e'&& word.size()>10,5);
    //ends with "age" ,12
    SetFlag(word[word.size()-1]=='e' && word[word.size()-2]=='g' && word[word.size()-3]=='a' && m>2,3);
    //ends with "ism" ,13
    SetFlag(word[word.size()-1]=='m' && word[word.size()-2]=='s' && word[word.size()-3]=='i' && m>1,3);
    //ends with "ful" ,14
    SetFlag(word[word.size()-1]=='l' && word[word.size()-2]=='u' && word[word.size()-3]=='f' && m>1,3);
    //ends with "ness" ,15
    SetFlag(word[word.size()-1]=='s' && word[word.size()-2]=='s' && word[word.size()-3]=='e' && word[word.size()-4]=='n' && m>1,4);
    //ends with "ability" ,16
    SetFlag(word[word.size()-1]=='y' && word[word.size()-2]=='t' && word[word.size()-3]=='i' && word[word.size()-4]=='l'&& word[word.size()-5]=='i' && word[word.size()-6]=='b'&& word[word.size()-7]=='a' && m>4,7);
    //ends with "less" ,17
    SetFlag(word[word.size()-1]=='s' && word[word.size()-2]=='s' && word[word.size()-3]=='e' && word[word.size()-4]=='l' && m>1,4);
    //ends with "y" ,18
    SetFlag(word[word.size()-1]=='y',1);
    //ends with "ness" ,19
    SetFlag(word[word.size()-1]=='s' && word[word.size()-2]=='s' && word[word.size()-3]=='e' && word[word.size()-4]=='n' && m>1,4);
    //ends with "able(i)" ,20
    SetFlag((word[word.size()-1]=='e'|| word[word.size()-1]=='i') && word[word.size()-2]=='l' && word[word.size()-3]=='b' && word[word.size()-4]=='a'&& word.size()>5 && m>0 ,4);
    //ends with e ,21
    SetFlag(word[word.size()-1]=='e' && m>0 && word.size()>2,1);
    //ends with "ity" ,22
    SetFlag(word[word.size()-1]=='i' && word[word.size()-2]=='t' && word[word.size()-3]=='i' && m>1,3);
    //ends with "ion" ,23
    SetFlag(word[word.size()-1]=='n' && word[word.size()-2]=='o' && word[word.size()-3]=='i' && m>1,3);
    //ends with "ate" ,24
    SetFlag(word[word.size()-1]=='e' && word[word.size()-2]=='t' && word[word.size()-3]=='a' && m>2,3);
    //ends with "er" ,25
    SetFlag(word[word.size()-1]=='r' && word[word.size()-2]=='e'&& m>2,2);
    //ends with "ize" ,26
    SetFlag(word[word.size()-1]=='e' && word[word.size()-2]=='z' && word[word.size()-3]=='i' && m>2,3);
    //ends with "ous" ,27
    SetFlag(word[word.size()-1]=='s' && word[word.size()-2]=='u' && word[word.size()-3]=='o' && m>2  && step==1,3);
    //ends with "ance" ,28
    SetFlag(word[word.size()-1]=='e' && word[word.size()-2]=='c' && word[word.size()-3]=='n' && word[word.size()-4]=='a' && m>0,4);
    //ends with "ator" ,29
    SetFlag(word[word.size()-1]=='r' && word[word.size()-2]=='o' && word[word.size()-3]=='t' && word[word.size()-4]=='a' && m>0,4);
    //ends with "iv" ,30
    SetFlag(word[word.size()-1]=='v' && word[word.size()-2]=='i'&& m>2,2);
    //ends with "eli" ,31
    SetFlag(word[word.size()-1]=='i' && word[word.size()-2]=='l'&& word[word.size()-3]=='e'&& m>1,3);
    //ends with "ment" ,32
    SetFlag(word[word.size()-1]=='t' && word[word.size()-2]=='n' && word[word.size()-3]=='e' && word[word.size()-4]=='m' &&m>3,4);
    //ends with "ant" ,33
    SetFlag(word[word.size()-1]=='t' && word[word.size()-2]=='n'&& word[word.size()-3]=='a'&& m>2 && step==1,3);
    //ends with "ical" ,34
    SetFlag(word[word.size()-1]=='l' && word[word.size()-2]=='a' && word[word.size()-3]=='c' && word[word.size()-4]=='i' && m>0,4);
    //ends with "ent" ,35
    SetFlag(word[word.size()-1]=='t' && word[word.size()-2]=='n'&& word[word.size()-3]=='e'&& m>2 && step==1 && word.size()>6,3);
}
void Stem::Simplification(){
    if (word=="apartment") {
        std::cout<<""<<std::endl;
    }
    int maximumIndex=-1;
    for (int i=0; i<flags.size(); i++) {
        if (flags[i]==true) {
            if(flagPriorities[i]>=flagPriorities[maximumIndex]){
                maximumIndex=i;
            }
        }
    }
    maximumIndex++;
    switch (maximumIndex) {
        case 0:
            break;
        case 1:
            word.erase(word.end()-1);
            break;
        case 2:
            word.erase(word.end()-2,word.end());
            break;
        case 3:
            word.erase(word.end()-3,word.end());
            word.append("y");
            break;
        case 4:
            word.erase(word.end()-2,word.end());
            break;
        case 5:
            word.erase(word.end()-3,word.end());
            break;
        case 6:
            word.erase(word.end()-4,word.end());
            break;
        case 7:
            if (partitions[0]=='c' && partitions[1]=='v'&& partitions[2]=='c' && partitions[3]=='c') {
                maximumIndex=0;
                break;
            }
            word.erase(word.end()-1);
            maximumIndex=0;
            break;
        case 8:
            word.erase(word.end()-6,word.end());
            word.append("e");
            break;
        case 9:
            word.erase(word.end()-3,word.end());
            word.append("e");
            break;
        case 10:
            word.erase(word.end()-5,word.end());
            word.append("y");
            break;
        case 11:
            word.erase(word.end()-5,word.end());
            break;
        case 12:
            word.erase(word.end()-3,word.end());
            break;
        case 13:
            word.erase(word.end()-3,word.end());
            break;
        case 14:
            word.erase(word.end()-3,word.end());
            break;
        case 15:
            word.erase(word.end()-4,word.end());
            break;
        case 16:
            word.erase(word.end()-7,word.end());
            break;
        case 17:
            maximumIndex=0;
            break;
        case 18:
            word.erase(word.end()-1);
            word.append("i");
            break;
        case 19:
            word.erase(word.end()-4,word.end());
            break;
        case 20:
            word.erase(word.end()-4,word.end());
            break;
        case 21:
            if (partitions[0]=='c' && partitions[1]=='v'&& partitions[2]=='c'&& word.size()==4) {
                maximumIndex=0;
                break;
            }
            else if (partitions[0]=='c' && partitions[1]=='c'&& partitions[2]=='v'&& partitions[3]=='c' && word.size()==5) {
                maximumIndex=0;
                break;
            }
            word.erase(word.end()-1);
            break;
        case 22:
            word.erase(word.end()-3,word.end());
            word.append("e");
            break;
        case 23:
            word.erase(word.end()-3,word.end());
            break;
        case 24:
            word.erase(word.end()-3,word.end());
            break;
        case 25:
            if (partitions[0]=='c' && partitions[1]=='c'&& partitions[2]=='v'&& partitions[3]=='c' && word.size()==5) {
                maximumIndex=0;
                break;
            }
            word.erase(word.end()-2,word.end());
            break;
        case 26:
            word.erase(word.end()-3,word.end());
            break;
        case 27:
            word.erase(word.end()-3,word.end());
            break;
        case 28:
            word.erase(word.end()-4,word.end());
            break;
        case 29:
            word.erase(word.end()-4,word.end());
            break;
        case 30:
            word.erase(word.end()-2,word.end());
            break;
        case 31:
            word.erase(word.end()-2,word.end());
            break;
        case 32:
            word.erase(word.end()-4,word.end());
            break;
        case 33:
            word.erase(word.end()-3,word.end());
            break;
        case 34:
            word.erase(word.end()-4,word.end());
            break;
        case 35:
            word.erase(word.end()-3,word.end());
            break;
        default:
            break;
    }
    if (maximumIndex!=0) {
        flags.clear();
        flagPriorities.clear();
        partitions.clear();
        Partition();
        SetFlags();
        Simplification();
    }
    
}
void Stem::Stemming(std::string &rawWord){
    step=0;
    word=rawWord;
    Partition();
    SetFlags();
    Simplification();
    rawWord=word;
    partitions.clear();
    flags.clear();
    flagPriorities.clear();
}
