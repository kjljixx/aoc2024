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
    bool enabled = true;
    std::regex targetRgx("mul\\(\\d*,\\d*\\)|do\\(\\)|don't\\(\\)");
    std::string input;
    std::ifstream inputFile("inputTest.txt");
    std::getline(inputFile, input);

    std::smatch m;
    int ans = 0;
    while(std::regex_search(input, m, targetRgx)){
        // std::cout << "hi";
        std::cout << std::string(m.prefix()) << std::endl;
        input = m.suffix();
        std::cout << m.str() << std::endl;
        std::cout << input << std::endl;
        if(m.str() == "don't()"){
            enabled = false;
            continue;
        }
        if(m.str() == "do()"){
            enabled = true;
            continue;
        }
        if(enabled){
            ans += multiplyFromStr(m.str());
        }
        // std::cout << input;
    }
    std::cout << ans;
}