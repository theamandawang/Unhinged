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


/*
 ● MUST be able to retrieve all related attribute-value pairs for a specified source attribute- value pair in better than O(N) time where N is the number of source attribute-value pairs stored in the object. So for example, O(log2 N) would be acceptable (although you can do much better). For big-O analysis purposes, you may assume that there's a constant that all attribute lengths are less than. You may also assume that the number of compatible pairs any attribute-value pair translates to is bounded by a constant (e.g., < 10 pairs).
 ● MUST use your RadixTree class to map source attribute-value information to compatible attribute-values (for full credit)
 ● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
 ● MUST NOT add any new public member functions or variables
 ● MAY use the STL list, vector, set, and unordered_set classes

 */
AttributeTranslator::AttributeTranslator(){}
AttributeTranslator::~AttributeTranslator(){}

//TODO: remove total at some point
bool AttributeTranslator::Load(std::string filename){
    std::string line;
    std::ifstream file(filename);
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
            count = count%4;
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
std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair &source) const{
    std::vector<AttValPair> empty;
    std::vector<AttValPair> * v = m_tree.search(source.attribute + ',' + source.value);
    if(v == nullptr) return empty;
    return *v;
}
