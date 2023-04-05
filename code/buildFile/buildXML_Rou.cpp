#include "buildXML_Rou.h"

BuildXML_Rou::BuildXML_Rou() {
    init_keyword_uset();
}

BuildXML_Rou::BuildXML_Rou(std::string content)
    :m_content(content), m_curPtr(0)
{
    rouPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/rou.xml";
    init_keyword_uset();
    extractFeature_Rou();
    if (writeRou())
        std::cout << "build rou.xml success!" << std::endl;
    else
        std::cout << "build rou.xml failed!" << std::endl;
}

int BuildXML_Rou::getKindsNum() {
    std::cout<<"getKindsNum()0"<<std::endl;
    char tmpCh = m_content[m_curPtr];
    std::string tmpStr = "";
    std::cout<<"getKindsNum()1"<<std::endl;
    while (tmpCh != ' ' && tmpCh != '\0') { //get 'carNum'
        tmpStr.push_back(tmpCh);
        advance();
        tmpCh = m_content[m_curPtr];
    }
    std::cout<<"getKindsNum()2"<<std::endl;
    if (tmpStr != "car_kinds" && tmpStr != "type_kinds") {
        perror("getCarNum() failed");
    }
    advance(); //eat blank
    tmpCh = m_content[m_curPtr];
    tmpStr.clear();
    while (tmpCh != '&' && tmpCh != '\0') { //get value
        tmpStr.push_back(tmpCh);
        advance();
        tmpCh = m_content[m_curPtr];
    }
    std::cout<<"getKindsNum()3"<<std::endl;
    return stringToInt(tmpStr);
}

int stringToInt(std::string str) {
    int res = 0;
    int ptr = 0;
    for (int i = str.size()-1; i >= 0; i--) {
        char tmpCh = str[ptr];
        int diff = tmpCh - '0';
        res += diff * pow(10, i);
    }
    return res;
}

void BuildXML_Rou::extractFeature_Rou() {
    std::cout<<"extractFeature_Rou()1"<<std::endl;
    m_carKinds = getKindsNum();
    advance(); //eat &
    m_flows.resize(m_carKinds);
    while (m_curPtr < m_content.size()) {
        char tmpCh = m_content[m_curPtr];
        std::string tmpStr = "";
        while (tmpCh != ' ' && tmpCh != '&' && tmpCh != '\0') {
            tmpStr.push_back(tmpCh);
            advance();
            tmpCh = m_content[m_curPtr];
        }
        //advance(); //eat &
        if (keyword_uset.count(tmpStr)) { //this tmpStr is Key rather than a Value
            if (tmpStr == "flow_id") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].id = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "type") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].type = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "color") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].color = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "begin") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].begin = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "end") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].end = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "from") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].from = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "to") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].to = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "number") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].number = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "departLane") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].departLane = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "arrivalLane") {
                for (int i = 0; i < m_carKinds; i++) {
                    m_flows[i].arrivalLane = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "type_kinds") {
                m_curPtr -= tmpStr.size();
                m_flowTypeKinds = getKindsNum();
                m_flowTypes.resize(m_flowTypeKinds);
                tmpStr.clear();
            }
            else if (tmpStr == "type_id") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].id = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "vClass") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].vClass = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "lcStrategic") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].lcStrategic = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "car-followingModel") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].carFollowingModel = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "accel") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].accel = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "decel") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].decel = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "emergencyDecel") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].emergencyDecel = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "minGap") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].minGap = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "tau") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].tau = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "speedDev") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].speedDev = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "sigma") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].sigma = getValue();
                }
                tmpStr.clear();
            }
            else if (tmpStr == "actionStepLength") {
                for (int i = 0; i < m_flowTypeKinds; i++) {
                    m_flowTypes[i].actionStepLength = getValue();
                }
                tmpStr.clear();
            }
            if(m_curPtr != m_content.size())
                advance();
        }
        else {
            perror("capture invaild token.\n");
        }
    }
    std::cout<<"extractFeature_Rou()2"<<std::endl;
    //test:
    /*for (auto i : m_flows) {
        std::cout<<i.id<<std::endl;
    }*/
}

std::string BuildXML_Rou::getValue() {
    std::string valueStr = "";
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

bool BuildXML_Rou::writeRou() {
    std::ofstream rouFile;
    rouFile.open(rouPath, ios::out);
    rouFile << "<routes>" << std::endl;
    for (int i = 0; i < m_carKinds; i++) {
        rouFile << "    <flow ";
        rouFile << "id=\"" << m_flows[i].id << "\"";
        rouFile << " type=\"" << m_flows[i].type << "\"";
        rouFile << " color=\"" << m_flows[i].color << "\"";
        rouFile << " begin=\"" << m_flows[i].begin << "\"";
        rouFile << " end=\"" << m_flows[i].end << "\"";
        rouFile << " from=\"" << m_flows[i].from << "\"";
        rouFile << " to=\"" << m_flows[i].to << "\"" << std::endl;
        rouFile << "     number=\"" << m_flows[i].number << "\"";
        rouFile << " departLane=\"" << m_flows[i].departLane << "\"";
        rouFile << " arrivalLane=\"" << m_flows[i].arrivalLane << "\"" << std::endl;
        rouFile << "    </flow>"<< std::endl;
    }
    for (int i = 0; i < m_flowTypeKinds; i++) {
        rouFile << "    <vType";
        rouFile << " id=" << m_flowTypes[i].id << "\"";
        rouFile << " vClass=\"" << m_flowTypes[i].vClass << "\"";
        rouFile << " lcStrategic=\"" << m_flowTypes[i].lcStrategic << "\"";
        rouFile << " carFollowModel=\"" << m_flowTypes[i].carFollowingModel << "\"";
        rouFile << " accel=\"" << m_flowTypes[i].accel << "\"" << std::endl;
        rouFile << "     decel=\"" << m_flowTypes[i].decel << "\"";
        rouFile << " emergencyDecel=\"" << m_flowTypes[i].emergencyDecel << "\"";
        rouFile << " minGap=\"" << m_flowTypes[i].minGap << "\"";
        rouFile << " tau=\"" << m_flowTypes[i].tau << "\"";
        rouFile << " speedDev=\"" << m_flowTypes[i].speedDev << "\"";
        rouFile << " sigma=\"" << m_flowTypes[i].sigma << "\"";
        rouFile << " actionStepLength=\"" << m_flowTypes[i].actionStepLength <<"\"" << std::endl;
        rouFile << "    </vType>" << std::endl;

    }
    rouFile << "</routes>" << std::endl;
    if (!fs::exists(rouPath))
        return false;
    return true;
}

void BuildXML_Rou::init_keyword_uset() {
    keyword_uset.insert("flow_id");
    keyword_uset.insert("type");
    keyword_uset.insert("color");
    keyword_uset.insert("begin");
    keyword_uset.insert("end");
    keyword_uset.insert("from");
    keyword_uset.insert("to");
    keyword_uset.insert("number");
    keyword_uset.insert("departLane");
    keyword_uset.insert("arrivalLane");
    keyword_uset.insert("type_kinds");
    keyword_uset.insert("type_id");
    keyword_uset.insert("vClass");
    keyword_uset.insert("lcStrategic");
    keyword_uset.insert("car-followingModel");
    keyword_uset.insert("accel");
    keyword_uset.insert("decel");
    keyword_uset.insert("emergencyDecel");
    keyword_uset.insert("minGap");
    keyword_uset.insert("tau");
    keyword_uset.insert("speedDev");
    keyword_uset.insert("sigma");
    keyword_uset.insert("actionStepLength");
    if (fs::exists(rouPath)) {
        remove(rouPath); //clear old xml file
    }
}

void BuildXML_Rou::advance() {
    m_curPtr++;
}

BuildXML_Rou::~BuildXML_Rou() {

}
