#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

struct Pos{
    int x;
    int y;
    int dir;
    bool outside;
};

std::array<int, 4> xChange = {{0, 1, 0, -1}};
std::array<int, 4> yChange = {{-1, 0, 1, 0}};

void move(std::vector<std::vector<bool>>& isObstacle, Pos& pos){
    if(pos.x + xChange[pos.dir] >= isObstacle.size() || pos.x + xChange[pos.dir] < 0){
        pos.outside = true;
        return;
    }
    if(pos.y + yChange[pos.dir] >= isObstacle.size() || pos.y + yChange[pos.dir] < 0){
        pos.outside = true;
        return;
    }

    int newX = pos.x + xChange[pos.dir];
    int newY = pos.y + yChange[pos.dir];
    // std::cerr << newY << " " << newX << std::endl;
    if(isObstacle[newY][newX]){
        pos.dir += 1;
        pos.dir %= 4;
        return;
    }

    pos.x = newX;
    pos.y = newY;
    return;
}

bool isCycle(std::vector<std::vector<bool>>& isObstacle, Pos& pos){
    std::set<std::pair<int, std::pair<int, int>>> visited;
    while(!pos.outside){
        move(isObstacle, pos);
        // std::cerr << pos.x << ":" << pos.y << ":" << pos.dir << std::endl;
        // std::cerr << isObstacle.size() << " " << pos.x << " " << pos.y << " " << pos.dir << " " <<pos.outside << std::endl;
        if(pos.outside){
            return false;
        }
        if(visited.find({pos.dir, {pos.x, pos.y}}) != visited.end()){
            return true;
        }
        visited.insert({pos.dir, {pos.x, pos.y}});
    }
    return false;
}

int main(){
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<std::vector<bool>> isObstacle;
    Pos pos; pos.outside = false;

    int y = 0;
    while(std::getline(inputFile, line)){
        // std::cerr << "hi";
        isObstacle.push_back(std::vector<bool>());
        int x = 0;
        for(char c : line){
            if(c == '#'){
                isObstacle[y].push_back(true);
            }
            else{
                isObstacle[y].push_back(false);
            }
            if(c == '^'){
                pos.x = x;
                pos.y = y;
                pos.dir = 0;
            }
            if(c == '>'){
                pos.x = x;
                pos.y = y;
                pos.dir = 1;
            }
            if(c == 'v'){
                pos.x = x;
                pos.y = y;
                pos.dir = 2;
            }
            if(c == '<'){
                pos.x = x;
                pos.y = y;
                pos.dir = 3;
            }
            x++;
        }
        y++;
    }

    int ans = 0;
    for(int y=0; y<isObstacle.size(); y++){
        for(int x=0; x<isObstacle.size(); x++){
            if((x != pos.x || y != pos.y) && !isObstacle[y][x]){
                Pos changedPos = pos;
                isObstacle[y][x] = true;
                bool isCyc = isCycle(isObstacle, changedPos);
                ans += isCyc;
                if(isCyc)
                std::cerr << x << " " << y << " " << isCyc << std::endl;
                isObstacle[y][x] = false;
            }
        }
    }

    std::cout << ans << std::endl;
}