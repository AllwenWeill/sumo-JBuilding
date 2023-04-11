#include "httprequest.h"
using namespace std;
namespace fs = std::filesystem;

const unordered_set<string> HttpRequest::DEFAULT_HTML{
            "/index", "/helper", "/inputROU", "/inputNET", "inputCFG","/show",
             "/welcome", };

const unordered_map<string, int> HttpRequest::DEFAULT_HTML_TAG {
            {"/inputROU.html", 1}, {"/inputNET.html", 2}, {"inputCFG.html", 3}};

void HttpRequest::Init() {
    method_ = path_ = version_ = body_ = "";
    state_ = REQUEST_LINE;
    header_.clear();
    post_.clear();
    isFindCompileButton = false;
}

bool HttpRequest::IsKeepAlive() const {
    if(header_.count("Connection") == 1) {
        return header_.find("Connection")->second == "keep-alive" && version_ == "1.1";
    }
    return false;
}

bool HttpRequest::parse(Buffer& buff) {
    const char CRLF[] = "\r\n";
    if(buff.ReadableBytes() <= 0) {
        return false;
    }
    // for(auto i : buff.buffer_){
    //     cout<<i;
    // }
    while(buff.ReadableBytes() && state_ != FINISH) {   
        const char* lineEnd = search(buff.Peek(), buff.BeginWriteConst(), CRLF, CRLF + 2);
        std::string line(buff.Peek(), lineEnd);
        //printf("L: %d, state %d\n",__LINE__,state_);
        switch(state_)  //此处各种错误/异常状态没有判断，鲁棒性不强，后期可以继续完善
        {
        case REQUEST_LINE:
            if(!ParseRequestLine_(line)) {
                return false;
            }
            ParsePath_();
            break;    
        case HEADERS:
            ParseHeader_(line);
            if(buff.ReadableBytes() <= 2) {
                state_ = FINISH;
            }
            break;
        case BODY:
            cout<<"BODY"<<endl;
            ParseBody_(line);
            break;
        default:
            break;
        }
        if(lineEnd == buff.BeginWrite()) { break; }
        buff.RetrieveUntil(lineEnd + 2);
    }
    return true;
}

void HttpRequest::ParsePath_() {
    if(path_ == "/") {
        path_ = "/index.html"; 
    }
    else {
        for(auto &item: DEFAULT_HTML) { //通过根据当前post请求中用户需要的html页面，返将对应的html地址加入path路径中作为response发送给用户。
            if(item == path_) {
                path_ += ".html";
                break;
            }
        }
    }
}

bool HttpRequest::ParseRequestLine_(const string& line) {
    regex patten("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    smatch subMatch;
    if(regex_match(line, subMatch, patten)) {   
        method_ = subMatch[1];
        path_ = subMatch[2];
        version_ = subMatch[3];
        state_ = HEADERS;
        return true;
    }
    return false;
}

void HttpRequest::ParseHeader_(const string& line) {
    regex patten("^([^:]*): ?(.*)$");
    smatch subMatch;
    if(regex_match(line, subMatch, patten)) {
        header_[subMatch[1]] = subMatch[2];
    }
    else {
        state_ = BODY;
    }
}

void HttpRequest::ParseBody_(const string& line) {
    body_ = line;
    ParsePost_();
    state_ = FINISH;
}

int HttpRequest::ConverHex(char ch) {
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    if (ch >= '0' && ch <= '9')  return ch - '0';
}

void HttpRequest::ParsePost_() {
    if(method_ == "POST" && header_["Content-Type"] == "application/x-www-form-urlencoded") {
        std::string unparsedContent= ParseFromUrlencoded_();
        cout<<"path:"<<path_<<endl;
        if(DEFAULT_HTML_TAG.count(path_)) {
            cout<<"path____"<<path_<<endl;
            int tag = DEFAULT_HTML_TAG.find(path_)->second;
            if(tag == 1) { //inputROU.html
                // if(post_.count("sendbtn")){
                //     cout<<"post_.count(sendbtn)";
                //     isFindCompileButton = true;
                //     //svParser(codeText);
                // }
                // if(post_.count("car_num")){ //post_不包含解析内容，此处需要修改为：解析unparsedContent内容
                //     cout<<"post_.count(car_num)";
                //     isFindCompileButton = true;
                //     //svParser(codeText);
                //     if(svParser(unparsedContent))
                //          path_ = "/inputROU.html"; //content-type:text/html
                //     else
                //         path_ = "/error.html";
                // }
                if(getXML_Rou(unparsedContent))
                    path_ = "/inputROU.html";
                else
                    path_ = "/error.html";
            }
            if(tag == 2){ //inputNET.html
                if(getXML_Net(unparsedContent))
                    path_ = "/inputNET.html";
                else
                    path_ = "/error.html"; 
            }
            if(tag == 3){ //inputCFG.html
                path_ = "/inputCFG.html";
            }
        }
    }   
}

bool getXML_Rou(std::string content){
    std::cout<<"myContent1:"<<content.size()<<endl;
    BuildXML_Rou BR(content); //该BR对象会自动构建rou.xml文件
    fs::path filepath_rou = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/Rou.rou.xml";
    if(!fs::exists(filepath_rou)){
        return false;
    }
    return true;
}

bool getXML_Net(std::string content){
    std::cout<<"myContent2:"<<content.size()<<endl;
    BuildXML_Net NET(content); //该BR对象会自动构建net.xml文件
    fs::path filepath_net = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/Net.net.xml";
    if(!fs::exists(filepath_net)){
        return false;
    }
    return true;
}


void writeParserResult(std::string res){
    fs::path filepath = "/home/allwen77/Desktop/workstation/sumo-JBuilding/resources/ret.txt";//resources/ret.txt code/http/httprequest.cpp
    if (!fs::exists(filepath)) {
        perror("Error: Invaild filepath.\n");
        exit(-1); 
    }
    ofstream output{ filepath };
    output << res << endl;
    output.close();
}

string HttpRequest::ParseFromUrlencoded_() {
    if(body_.size() == 0) { return nullptr; }
    // cout<<body_<<endl;
    std::string key, value;
    std::string getContent; //post表单内容(body)
    int num = 0;
    int n = body_.size();
    int i = 0, j = 0;
    for(; i < n; i++) {
        char ch = body_[i];
        switch (ch) {
        case '=':
            key = body_.substr(j, i - j);
            j = i + 1;
        case '+':
            getContent.push_back(' ');
            continue;
        case '%': {//此处应该有bug
            int OCTnum = ConverHex(body_[i + 1]) * 16 + ConverHex(body_[i + 2]);
            cout << OCTnum << endl;
            char tmpCh = (char)OCTnum;
            getContent.push_back(tmpCh);
            i += 2;
            continue;
        }
        case '&':
            value = body_.substr(j, i - j);
            j = i + 1;
            post_[key] = value;
            break;
        default:
            break;
        }
        getContent.push_back(body_[i]);
    }
    cout<<"getContent:"<<getContent<<endl;
    assert(j <= i);
    if(post_.count(key) == 0 && j < i) {
        value = body_.substr(j, i - j);
        post_[key] = value;
    }
    return getContent;
}

std::string HttpRequest::path() const{
    return path_;
}

std::string& HttpRequest::path(){
    return path_;
}
std::string HttpRequest::method() const {
    return method_;
}

std::string HttpRequest::version() const {
    return version_;
}

std::string HttpRequest::GetPost(const std::string& key) const {
    assert(key != "");
    if(post_.count(key) == 1) {
        return post_.find(key)->second;
    }
    return "";
}

std::string HttpRequest::GetPost(const char* key) const {
    assert(key != nullptr);
    if(post_.count(key) == 1) {
        return post_.find(key)->second;
    }
    return "";
}

bool HttpRequest::getIsFindCompileButton(){
    return isFindCompileButton;
}