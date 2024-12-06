#include <fstream>
#include <iostream>
#include <map>
#include <vector>

void dfs(std::map<int, int>& pages, std::map<int, std::vector<int>>& rules, int currPage, std::vector<int>& reverseSortedPages){
    pages.erase(currPage);
    for(int i=0; i<rules[currPage].size(); i++){
        if(pages.find(rules[currPage][i]) != pages.end()){
            dfs(pages, rules, rules[currPage][i], reverseSortedPages);
        }
    }
    reverseSortedPages.push_back(currPage);
}

bool isFollowsRules(std::vector<int>& pages, std::map<int, std::vector<int>>& rules, std::map<int, int> pagesMap){
    for(int i=0; i<pages.size(); i++){
        int pageNum = pages[i];
        for(int laterPage : rules[pageNum]){
            // std::cout << pageNum << " " << laterPage << std::endl;
            if(pagesMap.find(laterPage) != pagesMap.end() && pagesMap[laterPage] < i){
                return false;
            }
        }
    }
    return true;
}

int main(){
    std::string line;
    std::ifstream inputFile("input.txt");
    
    std::vector<int> pages;
    std::map<int, std::vector<int>> rules;

    while(true){
        std::getline(inputFile, line);

        int splitPos = line.find('|');
        if(splitPos == std::string::npos){
            // std::cerr << "hi";
            break;
        }

        rules[std::stoi(line.substr(0, splitPos))].push_back(std::stoi(line.substr(splitPos+1)));
    }

    int ans = 0;
    while(std::getline(inputFile, line)){
    // std::cerr << line << "\n"; 
        pages.clear();
        while(true){
            int splitPos = line.find(',');
            if(splitPos == std::string::npos){
                break;
            }

            pages.push_back(std::stoi(line.substr(0, splitPos)));
            line = line.substr(splitPos+1);
        }
        pages.push_back(std::stoi(line));
        std::map<int, int> pagesMap;
        for(int i=0; i<pages.size(); i++){
            pagesMap[pages[i]] = i;
        }
        // std::cout << "hi" << std::endl;
        if(!isFollowsRules(pages, rules, pagesMap)){
            std::vector<int> reverseSortedPages;
            while(pagesMap.size()){
                dfs(pagesMap, rules, pagesMap.begin()->first, reverseSortedPages);
            }
            ans += reverseSortedPages[reverseSortedPages.size()/2];
        }
    }
    std::cout << ans << std::endl;
}