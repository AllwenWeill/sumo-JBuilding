#ifndef BUILDXML_ROW_H
#define BUILDXML_ROW_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <math.h>
struct flowInformation {
    std::string id;
    std::string type;
    std::string color;
    std::string begin;
    std::string end;
    std::string from;
    std::string to;
    std::string number;
    std::string departLane;
    std::string arrivalLane;
};
struct flowType {
    std::string id;
    std::string vClass;
    std::string lcStrategic;
    std::string carFollowingModel;
    std::string accel;
    std::string decel;
    std::string emergencyDecel;
    std::string minGap;
    std::string tau;
    std::string speedDev;
    std::string sigma;
    std::string actionStepLength;
};

class BuildXML_Rou {
private:
    std::string m_content; //original text
    int m_carKinds; //total number of cars
    int m_flowTypeKinds; //total number of flows
    double m_penetrationRate;
    int m_flowNum; //the number of car flow
    int m_curPtr; //pointer to the current character
    std::unordered_map<std::string, flowInformation> flowInfo_umap;
    std::unordered_map<std::string, flowType> flowType_umap;
    std::unordered_set<std::string> keyword_uset;
    std::vector<flowInformation> m_flows;
    std::vector<flowType> m_flowTypes;
public:
    BuildXML_Rou();
    BuildXML_Rou(std::string content);
    ~BuildXML_Rou();
    void extractFeature_Rou(); //read and get the information of 'Row' from intermediate file
    void advance(); //the pointer forward a step
    void init_keyword_uset();
    int getKindsNum(); //get m_carKinds & m_flowTypeKinds
    std::string getValue();
};
int stringToInt(std::string str);
#endif