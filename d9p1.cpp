#include <fstream>
#include <iostream>
#include <vector>

using ll = long long;

ll solve(std::vector<int>& hardDrive, int numFileSpaces){
    ll ans = 0;
    int endIdx = hardDrive.size()-1;
    for(int i=0; i<numFileSpaces; i++){
        if(hardDrive[i] < 0){
            while(hardDrive[endIdx] < 0){
                endIdx--;
            }
            hardDrive[i] = hardDrive[endIdx];
            hardDrive[endIdx] = -1;
        }
        // std::cerr << hardDrive[i];
        ans += hardDrive[i] * i;
    }
    // std::cerr << std::endl;
    return ans;
}

int main(){
    std::ifstream inputFile("input.txt");

    std::vector<int> hardDrive;
    int currId = 0;
    int numFileSpaces = 0;
    bool currCharIsWhitespace = false;
    char c;
    while(inputFile >> c){
        if(currCharIsWhitespace){
            for(int i=0; i<(c-'0'); i++){
                hardDrive.push_back(-1);
            }
        }
        else{
            for(int i=0; i<(c-'0'); i++){
                hardDrive.push_back(currId);
                numFileSpaces++;
            }
            currId++;
        }
        currCharIsWhitespace = !currCharIsWhitespace;
    }
    // std::cout << numFileSpaces << std::endl;
    std::cout << solve(hardDrive, numFileSpaces) << std::endl;
}