#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

int charToAntennaFreq(char c){
  if(c >= 'a'){
    return c - 'a';
  }
  if(c >= 'A'){
    return c - 'A' + 26;
  }
  return c - '0' + 52;
}

bool validCoord(std::pair<int, int> coord, int size){
  return coord.first >= 0 && coord.first < size && coord.second >= 0 && coord.second < size;
}

void getAntinodesFromPair(std::pair<int, int>& a, std::pair<int, int>& b,
                          std::set<std::pair<int, int>>& antinodes, int size){
  bool aValid = true;
  bool bValid = true;
  std::pair<int, int> movement = {a.first - b.first, a.second - b.second};
  movement.first /= std::gcd(movement.first, movement.second);
  movement.second /= std::gcd(movement.first, movement.second);
  antinodes.insert(a);
  int multiples = 1;
  while(aValid || bValid){
    // std::cerr << a.first << ":" << a.second << " " << b.first << ":" << b.second << std::endl;
    if(validCoord({a.first + movement.first*multiples, a.second + movement.second*multiples}, size)){
      // std::cerr << a.first + movement.first << " " << a.second + movement.second << " "<< antinodes.size() << std::endl;
      antinodes.insert({a.first + movement.first*multiples, a.second + movement.second*multiples});
    }
    else{
      aValid = false;
    }
    if(validCoord({a.first - movement.first*multiples, a.second - movement.second*multiples}, size)){
      // std::cerr << b.first - movement.first << " " << b.second - movement.second << " "<< antinodes.size() << std::endl;
      antinodes.insert({a.first - movement.first*multiples, a.second - movement.second*multiples});
    }
    else{
      bValid = false;
    }
    multiples++;
  }
}

int getNumAntinodes(std::vector<std::vector<std::pair<int, int>>>& antennae, int size){
  std::set<std::pair<int, int>> antinodes;
  for(auto sameFreqAntennae : antennae){
    for(int aIdx = 0; aIdx < sameFreqAntennae.size(); aIdx++){
      std::pair<int, int> a = sameFreqAntennae[aIdx];
      for(int bIdx = aIdx+1; bIdx < sameFreqAntennae.size(); bIdx++){
        std::pair<int, int> b = sameFreqAntennae[bIdx];
        getAntinodesFromPair(a, b, antinodes, size);
      }
    }
  }
  return antinodes.size();
}

int main(){
  std::ifstream inputFile("input.txt");
  std::vector<std::vector<std::pair<int, int>>> antennae(62, std::vector<std::pair<int, int>>{});
  int x = 0;
  int y = 0;
  std::string line;
  while(std::getline(inputFile, line)){
    x=0;
    for(int i = 0; i < line.size(); i++){
      if(line[i] == '.'){
        x++;
        continue;
      }
      antennae[charToAntennaFreq(line[i])].push_back({x, y});
      x++;
    }
    y++;
  }

  std::cout << getNumAntinodes(antennae, y) << std::endl;
}