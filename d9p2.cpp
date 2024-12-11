#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using ll = long long;

struct File{
    int start;
    int size;
    int id;
    File* prev;
    File* next;

    File(int start, int size, int id, File* prev, File* next) : 
        start(start), size(size), id(id), prev(prev), next(next){}
};

void moveSingleFile(File* toBeMoved, File* startFile){
    File* currFile = startFile;
    while(currFile && currFile != toBeMoved && (toBeMoved->size > currFile->size || currFile->id >= 0)){
        currFile = currFile->next;
    }
    if(!currFile || currFile == toBeMoved){
        return;
    }
    toBeMoved->prev->next = new File(0, toBeMoved->size, -1, toBeMoved->prev, toBeMoved->next);;
    if(toBeMoved->next){
        toBeMoved->next->prev = toBeMoved->prev->next;
    }
    toBeMoved->prev = currFile->prev;
    currFile->prev->next = toBeMoved;
    toBeMoved->next = currFile;
    currFile->prev = toBeMoved;
    currFile->size = currFile->size-toBeMoved->size;
    // if(toBeMoved->prev->id == 5235){
    //     std::cerr << "FLAG\n\n:" << currFile;
    // }
}
File* debug2 = nullptr;

ll solve(File* startFile, File* endFile){
    File* currFile = endFile;
    while(currFile){
        // std::cerr << debug2 << ":" << currFile << ":" << currFile->prev << ":" << currFile->id << " ";
        if(currFile->id == -1){
            currFile = currFile->prev;
            continue;
        }
        
        // std::cout << currFile->start << " ";
        File* debug = startFile;
        while(debug){
            // std::cerr << debug->id << ":" << debug->size << " ";
            debug = debug->next;
        }
        // std::cerr << std::endl;
        File* prevFile = currFile->prev;
        if(!prevFile){currFile = prevFile; continue;}
        moveSingleFile(currFile, startFile);
        // std::cout << currFile << " ";
        currFile = prevFile;
    }

    int i=0;
    ll ans = 0;
    currFile = startFile;
    while(currFile){
        for(int j=0; j<currFile->size; j++){
            if(currFile->id >= 0){
                ans += i*currFile->id;
            }
            i++;
        }
        // std::cerr << currFile << " ";
        currFile = currFile->next;
    }
    return ans;
}

int main(){
    std::ifstream inputFile("input.txt");

    std::vector<File> hardDrive;
    File* startFile = nullptr;
    File* currFile = nullptr;
    File* newFile = nullptr;
    int currId = 0;
    int i = 0;
    bool currCharIsWhitespace = false;
    char c;
    while(inputFile >> c){
        if(currCharIsWhitespace){
            newFile = new File(i, c-'0', -1, currFile, nullptr);
            // std::cerr << "-1" << " ";
            if(currFile){
                if(currFile->id == 5235){
                    debug2 = newFile;
                }
                currFile->next = newFile;
            }
            currFile = newFile;
            i += c-'0';
        }
        else{
            newFile = new File(i, c-'0', currId, currFile, nullptr);
            // std::cerr << currId << " ";
            if(currFile){
                currFile->next = newFile;
            }
            else{
                startFile = newFile;
            }
            currFile = newFile;
            i += c-'0';
            currId++;
        }
        currCharIsWhitespace = !currCharIsWhitespace;
    }
    // std::cerr << currFile->prev->id << std::endl;
    std::cout << solve(startFile, currFile) << std::endl;
}