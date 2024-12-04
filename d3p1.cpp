#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>

int multiplyFromStr(std::string str){
    int openParenIdx = str.find("(");
    int commaIdx = str.find(",");
    int endParenIdx = str.find(")");
    int a = std::stoi(str.substr(openParenIdx+1, commaIdx));
    int b = std::stoi(str.substr(commaIdx+1, endParenIdx));
    return a*b;
}

int main(){
    std::regex targetRgx("mul\\(\\d*,\\d*\\)");
    std::string input;
    std::ifstream inputFile("input.txt");
    std::getline(inputFile, input);

    std::smatch m;
    int ans = 0;
    while(std::regex_search(input, m, targetRgx)){
        // std::cout << "hi";
        ans += multiplyFromStr(m.str());
        input = m.suffix();
        // std::cout << input;
    }
    std::cout << ans;
}