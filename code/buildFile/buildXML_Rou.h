#ifndef BUILDXML_ROW_H
#define BUILDXML_ROW_H
#include <string>
#include <vector>
#include <unordered_map>
struct flowInformation{
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
struct flowType{
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

class BuildXML_Rou{
private:
    std::string m_content; //original text
    int m_carNum; //total number of cars
    double m_penetrationRate;
    int m_flowNum; //the number of car flow
    std::unordered_map<std::string, flowInformation> flowInfo_umap;
    std::unordered_map<std::string, flowType> flowType_umap;
public:
    BuildXML_Rou();
    BuildXML_Rou(std::string content);
    ~BuildXML_Rou();
    void extractFeature_Rou(); //read and get the information of 'Row' from intermediate file
};

#endif