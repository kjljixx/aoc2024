#include <fstream>
#include <iostream>
#include <vector>

bool isReportSafe(const std::vector<int> &list){
  if(list.size() < 2){
    return true;
  }
  int prevNum = list[0];
  bool increasing = list[1] > prevNum;
  for(int i = 0; i < list.size(); i++){
    if(i == 0){
      continue;
    }
    if(list[i] > prevNum && increasing){
      if(list[i] - prevNum > 3){
        return false;
      }
      if(list[i] - prevNum < 1){
        return false;
      }
    }
    else if(list[i] < prevNum && !increasing){
      if(prevNum - list[i] > 3){
        return false;
      }
      if(prevNum - list[i] < 1){
        return false;
      }
    }
    else{
      return false;
    }
    prevNum = list[i];
  }
  return true;
}

bool p2IsReportSafe(std::vector<int> &list){
  std::cerr << "hi";
  for(int i=0; i<list.size(); i++){
    std::vector<int> list2 = list;
    list2.erase(list2.begin() + i);
    if(isReportSafe(list2)){
      return true;
    }
  }
  return false;
}


int main(){
  std::ifstream file("input.txt");
  std::string line;
  std::vector<int> list;
  int ans = 0;
  while(std::getline(file, line)){
    list.clear();
    std::string token;
    for(int i = 0; i < line.size(); i++){
      if(line[i] == ' ' && token != ""){
        list.push_back(std::stoi(token));
        token = "";
      }
      else{
        token += line[i];
      }
    }
    std::cout << "hi";
    ans += p2IsReportSafe(list);
  }
  file.close();
  std::cout << ans << std::endl;
}