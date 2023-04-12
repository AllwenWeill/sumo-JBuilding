#include "buildXML_Config.h"

BuildXML_Config::BuildXML_Config() {

}

BuildXML_Config::BuildXML_Config(std::string content) 
	:m_content(content), m_curPtr(0)
{
	std::cout<<"Coming the BuildXML_Config"<<endl;
	configPath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/Config.cfg.xml";
	if (fs::exists(configPath)) {
		remove(configPath); //clear old xml file
	}
	init_keyword_uset();
	extractFeature_Config();
	if (writeConfig())
		std::cout << "build cfg.xml success!" << std::endl;
	else
		std::cout << "build cfg.xml failed!" << std::endl;
}

void BuildXML_Config::extractFeature_Config() {
	while (m_curPtr < m_content.size()) {
		char tmpCh = m_content[m_curPtr];
		std::string tmpStr = "";
		while (tmpCh != ' ' && tmpCh != '&' && tmpCh != '\0') {
			tmpStr.push_back(tmpCh);
			advance();
			tmpCh = m_content[m_curPtr];
		}
		if (keyword_uset.count(tmpStr)) { //this tmpStr is Key rather than a Value
			if (tmpStr == "start-time") {
				m_beginTime = getValue();
				tmpStr.clear();
			}
			else if (tmpStr == "end-time") {
				m_endTime = getValue();
				tmpStr.clear();
			}
			else if (tmpStr == "step") {
				m_stepTime = getValue();
				tmpStr.clear();
			}
			advance(); //eat &
		}
		else {
			perror("capture invaild token.\n");
		}
	}
}

bool BuildXML_Config::writeConfig() {
	std::ofstream cfgFile;
	cfgFile.open(configPath, ios::out);
	cfgFile << "<?xml version=\"1.0\" encoding=\"utf - 8\"?>" << std::endl;
	cfgFile << "<configuration xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"" << std::endl;
	cfgFile << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">" << std::endl;
	cfgFile << "    <input>" << std::endl;
	cfgFile << "        <net-file value=\"Two_Road.net.xml\" / > " << std::endl;
	cfgFile << "        <route-files value=\"test_rou.rou.xml\" /> " << std::endl;
	cfgFile << "    </input>" << std::endl;
	cfgFile << "<tripinfo>" << std::endl;
	cfgFile << "    <device.tripinfo.probability value=\"1\"/>" << std::endl;
	cfgFile << "</tripinfo>" << std::endl;
	cfgFile << "<emissions>" << std::endl;
	cfgFile << "	<device.emissions.probability value=\"1\"/>" << std::endl;
	cfgFile << "</emissions>" << std::endl;
	cfgFile << "<output>" << std::endl;
	cfgFile << "        <tripinfo-output value=\"tripinfo_output.xml\"/>" << std::endl;
	cfgFile << "        <lanechange-output value=\"lanechange - output.xml\"/>" << std::endl;
	cfgFile << "</output>" << std::endl;
	cfgFile << "<time>" << std::endl;
	cfgFile << "      <begin value=\"" <<m_beginTime<< "\" / > " << std::endl;
	cfgFile << "      <end value=\"" << m_endTime << "\" / > " << std::endl;
	cfgFile << "      <step-length value=\"" << m_stepTime << "\" / > " << std::endl;
	cfgFile << "</time>" << std::endl;
	cfgFile << "</configuration>" << std::endl;
	if (!fs::exists(configPath))
		return false;
	return true;
}

string BuildXML_Config::getValue() {
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

void BuildXML_Config::init_keyword_uset() {
	keyword_uset.insert("start-time");
	keyword_uset.insert("step");
	keyword_uset.insert("end-time");
	if (fs::exists(configPath)) {
		remove(configPath); //clear old xml file
	}
}

void BuildXML_Config::advance() {
	m_curPtr++;
}

BuildXML_Config::~BuildXML_Config() {

}
