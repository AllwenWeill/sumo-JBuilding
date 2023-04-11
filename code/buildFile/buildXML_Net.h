#ifndef BUILDXML_NET_H
#define BUILDXML_NET_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <cmath>
namespace fs = std::filesystem;
using namespace std;
class BuildXML_Net{
private:
    std::string m_content; //original text
    std::string m_sceneKind;
    std::string m_netKind;
    int m_curPtr; //pointer to the current character
    std::unordered_set<std::string> keyword_uset;
    fs::path netPath;
    fs::path targetNetPath; //target file in the classic road network library
public:
    BuildXML_Net();
    BuildXML_Net(string content);
    ~BuildXML_Net();
    void extractFeature_Net();
    void advance(); //the pointer forward a step
    void init_keyword_uset();
    std::string getValue();
    bool writeNet(); //build executable xml file
    bool selectNet(); //select stored net xml file
};

#endif
