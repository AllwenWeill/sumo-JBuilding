#include "buildXML_Config.h"

BuildXML_Config::BuildXML_Config() {

}

BuildXML_Config::BuildXML_Config(std::string content) 
	:m_content(content), m_beginTime(0), m_endTime(0), m_stepTime(0.5)
{
	configPath = "../Config.cfg.xml";
	if (fs::exists(configPath)) {
		remove(configPath); //clear old xml file
	}
	extractFeature_Config();
	writeConfig();
	if (writeConfig())
		std::cout << "build cfg.xml success!" << std::endl;
	else
		std::cout << "build cfg.xml failed!" << std::endl;
}

void BuildXML_Config::extractFeature_Config() {

}

bool BuildXML_Config::writeConfig() {
	std::ofstream cfgFile;
	cfgFile.open(configPath, 0x02);
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

BuildXML_Config::~BuildXML_Config() {

}
