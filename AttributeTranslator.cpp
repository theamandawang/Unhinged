//
//  AttributeTranslator.cpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//
#include "AttributeTranslator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
AttributeTranslator::AttributeTranslator(){}
AttributeTranslator::~AttributeTranslator(){}

bool AttributeTranslator::Load(std::string filename){
    std::string line;
    std::ifstream file;
    file.open(filename);
    if(!file) return false;
    long count = 0;
    std::string att;
    std::string val;
    std::string compVal;
    std::string compAtt;
    while(std::getline(file, line)){
        std::stringstream commaLine(line);
        std::string line2;
        while(std::getline(commaLine, line2, ',')){
            if(count%4 == 0 && count != 0){
                AttValPair a(compAtt, compVal);
                std::vector<AttValPair> * v = m_tree.search(att+','+val);
                if(v == nullptr){
                    std::vector<AttValPair> temp;
                    temp.push_back(a);
                    m_tree.insert(att + ',' + val, temp);
                }
                else{
                    v->push_back(a);
                }
                att = "";
                val = "";
                compAtt = "";
                compVal = "";
            }
            if(count %4 == 0){
                att = line2;
            }
            if(count %4 == 1){
                val = line2;
            }
            if(count %4 == 2){
                compAtt = line2;
            }
            if(count %4 == 3){
                compVal = line2;
            }
            count = count%4 + 1;
        }
    }
    file.close();
    return true;
}

//O(1) time because we use radix tree and the length of attribute +',' + value is roughly constant
std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair &source) const{
    std::vector<AttValPair> empty;
    std::vector<AttValPair> * v = m_tree.search(source.attribute + ',' + source.value);
    if(v == nullptr) return empty;
    return *v;
}
