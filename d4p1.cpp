#include <array>
#include <iostream>
#include <fstream>
#include <vector>

enum Direction{
    UP,
    UP_RIGHT,
    RIGHT,
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
    LEFT,
    UP_LEFT,
};

std::array<int, 8> xChanges = {{0, 1, 1, 1, 0, -1, -1, -1}};
std::array<int, 8> yChanges = {{-1, -1, 0, 1, 1, 1, 0, -1}};
std::array<int, 8> xIters = {{1, 1, 1, 1, 1, -1, -1, -1}};
std::array<int, 8> yIters = {{-1, -1, 1, 1, 1, 1, 1, -1}};
std::array<int, 8> xStart = {{0, 0, 0, 0, 0, 1, 1, 1}};
std::array<int, 8> yStart = {{1, 1, 0, 0, 0, 0, 0, 1}};

int charToInt(char a){
    switch(a){
        case 'X': return 0;
        case 'M': return 1;
        case 'A': return 2;
        case 'S': return 3;
        default: return -1;
    }
}

int main(){
    std::ifstream inputFile("input.txt");
    
    std::vector<std::vector<int>> crossword;
    std::string line;
    int size = 0;
    while(std::getline(inputFile, line)){
        std::vector<int> parsedLine;
        for(char a : line){
            parsedLine.push_back(charToInt(a));
        }
        size++;
        crossword.push_back(parsedLine);
    }
    std::cout << "Input Done" << std::endl;
    // std::cout << size << std::endl;

    for(int x=0; x<size; x++){
        for(int y=0; y<size; y++){
            // std::cout << crossword[x][y] << " ";
        }
        // std::cout << std::endl;
    }

    std::vector<std::vector<int>> processingGrid(size, std::vector<int>(size));
    int ans = 0;
    for(int i=0; i<8; i++){
        // std::cout << i << std::endl;
        for(int x = xStart[i]*(size-1); x != (1-xStart[i])*(size-1)+xIters[i]; x += xIters[i]){
            for(int y = yStart[i]*(size-1); y != (1-yStart[i])*(size-1)+yIters[i]; y += yIters[i]){
                // std::cout << x << "," << y << std::endl;
                processingGrid[y][x] = -1;
                if(crossword[y][x] == -1){
                    processingGrid[y][x] = -1;
                    // std::cout << "n";
                    continue;
                }
                if(crossword[y][x] == 0){
                    processingGrid[y][x] = 0;
                    // std::cout << "z";
                    continue;
                }
                if(x - xChanges[i] < 0 || x - xChanges[i] >= size){
                    // std::cout << "xoob\n";
                    continue;
                }
                if(y - yChanges[i] < 0 || y - yChanges[i] >= size){
                    // std::cout << "yoob\n";
                    continue;
                }
                if(crossword[y][x] == processingGrid[y-yChanges[i]][x-xChanges[i]] + 1){
                    // std::cout << "(" << x-xChanges[i] << "," << y-yChanges[i] << ")";
                    processingGrid[y][x] = crossword[y][x];
                }
                else{
                    processingGrid[y][x] = -1;
                }
                if(processingGrid[y][x] == 3){
                    // std::cout << Direction(i) << "SCORE" << std::endl;
                    ans++;
                }
            }
        }
    }
    std::cout << ans << std::endl;
}