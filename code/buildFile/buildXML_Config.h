#pragma once
#ifndef BUILDXML_CONFIG_H
#define BUILDXML_CONFIG_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <cmath>
using namespace std;
namespace fs = std::filesystem;
class BuildXML_Config {
private:
    std::string m_content; //original text
    int m_curPtr; //pointer to the current character
    fs::path configPath;
    bool m_isTurnOnEmissions;
    bool m_isTurnOnTripinfo;
    string m_beginTime;
    string m_endTime;
    string m_stepTime;
    std::unordered_set<std::string> keyword_uset;
public:
    BuildXML_Config();
    BuildXML_Config(std::string content);
    ~BuildXML_Config();
    void extractFeature_Config();
    bool writeConfig(); //build executable xml file
    void init_keyword_uset();
    void advance(); //the pointer forward a step
    std::string getValue();
};

#endif