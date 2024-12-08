#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>

using ll = long long;

bool testOpConfig(std::vector<ll>& list, ll target, ll ops){
  ll ans = list[0];
  for(int i=0; i<list.size()-1; i++){
    if(ops % 3 == 1){
      ans += list[i+1];
    }
    else if(ops % 3 == 0){
      ans *= list[i+1];
    }
    else{
      ans = ans*std::pow(10,(std::floor(std::log10l(list[i+1]))+1))+list[i+1];
    }
    ops /= 3;
  }
  return ans == target;
}

bool test(std::vector<ll>& list, ll target){
  ll ops; //1 = add, 0 = multiply, 2 = concat
  for(ll i = 0; i < std::pow(3, list.size()-1); i++){
    if(testOpConfig(list, target, i)){
      return true;
    }
    ops++;
  }
  return false;
}

int main(){
  std::ifstream file("input.txt");
  std::string line;
  std::vector<ll> list;
  ll target;
  ll ans = 0;
  while(std::getline(file, line)){
    list.clear();
    int splitIdx = line.find(':');
    target = std::stoll(line.substr(0, splitIdx));
    std::istringstream iss(line.substr(splitIdx+1));
    while(iss >> line){
    // std::cout << line << std::endl;
      list.push_back(std::stoll(line));
    }
    if(test(list, target)){
      ans += target;
    }
  }
  file.close();
  std::cout << ans << std::endl;
}