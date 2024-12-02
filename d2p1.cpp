#include <fstream>
#include <iostream>
#include <vector>

#define INF 1000000000

bool isReportSafe(std::vector<int> &list){
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
    ans += isReportSafe(list);
  }
  file.close();
  std::cout << ans << std::endl;
}