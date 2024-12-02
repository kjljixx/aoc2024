#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

int main(){
  std::ifstream file("input.txt");
  std::vector<int> list1, list2;
  int num;
  int iter = 0;
  while(file >> num){
    if(iter % 2 == 0){
      list1.push_back(num);
    }
    else{
      list2.push_back(num);
    }
    iter++;
  }
  file.close();
  std::cout << "Size of list1: " << list1.size() << std::endl;
  std::cout << "Size of list2: " << list2.size() << std::endl;
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());
  int sum = 0;
  for(int i = 0; i < list1.size(); i++){
    sum += std::abs(list1[i] - list2[i]);
  }
  std::cout << sum << std::endl;
  return 0;
}