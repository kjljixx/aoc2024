#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

int main(){
  std::ifstream file("input.txt");
  std::unordered_map<int, int> freqs;
  std::vector<int> list1;
  int num;
  int iter = 0;
  while(file >> num){
    if(iter % 2 == 0){
      list1.push_back(num);
    }
    else{
      freqs[num]++;
    }
    iter++;
  }
  file.close();
  std::cout << "Size of list1: " << list1.size() << std::endl;
  int sum = 0;
  for(int i = 0; i < list1.size(); i++){
    sum += list1[i] * freqs[list1[i]];
  }
  std::cout << sum << std::endl;
  return 0;
}