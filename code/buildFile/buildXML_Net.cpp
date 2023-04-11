#include "buildXML_Net.h"

BuildXML_Net::BuildXML_Net() {

}


BuildXML_Net::BuildXML_Net(std::string content)
    :m_content(content), m_curPtr(0)
{
    netPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/Net.net.xml";
    init_keyword_uset();
    extractFeature_Net();
    if (selectNet())
        std::cout << "build net.xml success!" << std::endl;
    else
        std::cout << "build net.xml failed!" << std::endl;
}



void BuildXML_Net::extractFeature_Net() {
    while (m_curPtr < m_content.size()) {
        char tmpCh = m_content[m_curPtr];
        std::string tmpStr = "";
        while (tmpCh != ' ' && tmpCh != '&' && tmpCh != '\0') {
            tmpStr.push_back(tmpCh);
            advance();
            tmpCh = m_content[m_curPtr];
        }
        if (keyword_uset.count(tmpStr)) { //this tmpStr is Key rather than a Value
            if (tmpStr == "scene") {
                m_sceneKind = getValue();
                tmpStr.clear();
            }
            else if (tmpStr == "net") {
                m_netKind = getValue();
                tmpStr.clear();
            }
            advance(); //eat &
        }
        else {
            perror("capture invaild token.\n");
        }
    }
    //cout << m_sceneKind << ";" << m_netKind;
}


bool BuildXML_Net::selectNet() {
    if (m_sceneKind == "scene1" && m_netKind == "net1") {
        targetNetPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/classicRoadNetwork/intersection.net.xml";
    }
    else if (m_sceneKind == "scene2" && m_netKind == "net2") {
        targetNetPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/classicRoadNetwork/motorway.net.xml";
    }
    else if (m_sceneKind == "scene3" && m_netKind == "net3") {
        targetNetPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/classicRoadNetwork/off-ramp.net.xml";
    }
    else if (m_sceneKind == "scene4" && m_netKind == "net4") {
        targetNetPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/classicRoadNetwork/on-ramp.net.xml";
    }
    else if (m_sceneKind == "scene5" && m_netKind == "net2") {
        targetNetPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/classicRoadNetwork/on-off-ramp.net.xml";
    }
    std::ifstream stream(targetNetPath, std::ios::binary);
    std::error_code ec;
    int filesize = fs::file_size(targetNetPath, ec);
    vector<char> buffer;
    buffer.resize((size_t)filesize + 1);
    if (!stream.read(buffer.data(), (std::streamsize)filesize)) {
        perror("stream read failed!\n");
        exit(-1);
    }
    string filememo = string(buffer.begin(), buffer.end());
    cout << filememo << endl;
    std::ofstream netFile;
    netFile.open(netPath, ios::out);
    netFile << filememo;
    if (!fs::exists(netPath))
        return false;
    return true;
}

string BuildXML_Net::getValue() {
    string valueStr = "";
    advance(); //eat blank
    char tmpCh = m_content[m_curPtr];
    while (tmpCh != ',' && tmpCh != '&' && m_curPtr != m_content.size()) {
        valueStr.push_back(tmpCh);
        advance();
        tmpCh = m_content[m_curPtr];
    }
    std::cout << valueStr << std::endl;
    return valueStr;
}

bool BuildXML_Net::writeNet() {
    std::ofstream netFile;
    netFile.open(netPath, ios::out);
    netFile << "<routes>" << std::endl;
   
    if (!fs::exists(netPath))
        return false;
    return true;
}

void BuildXML_Net::init_keyword_uset() {
    keyword_uset.insert("scene");
    keyword_uset.insert("net");
    /*keyword_uset.insert("scene2");
    keyword_uset.insert("scene3");
    keyword_uset.insert("scene4");
    keyword_uset.insert("scene5");
    keyword_uset.insert("net1");
    keyword_uset.insert("net2");
    keyword_uset.insert("net3");
    keyword_uset.insert("net4");*/
    if (fs::exists(netPath)) {
        remove(netPath); //clear old xml file
    }
}

void BuildXML_Net::advance() {
    m_curPtr++;
}


BuildXML_Net::~BuildXML_Net() {

}
