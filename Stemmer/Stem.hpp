//
//  Stem.hpp
//  Stemmer
//
//  Created by Doğukan Avcı on 07/08/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#ifndef Stem_hpp
#define Stem_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class Stem{
public:
    Stem(){}
    void Partition();
    void SetFlag(bool currentFlag,int currentFlagValue);
    void SetFlags();
    void Simplification();
    void Stemming(std::string &rawWord);
    int step;
private:
    std::vector<char> partitions;
    std::string::iterator it;
    int m;
    std::string word;
    std::vector <bool> flags;
    std::vector <int> flagPriorities;
};


#endif /* Stem_hpp */
