#include <iostream>
#include "Node.h"
#include <queue>
#include <memory>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <fstream>
#include <sstream>
#include <time.h>


matrix Goal =  {{1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
                {13,14,15,0}};
/*
 * Fajna funkcja haszujaca wiem
 */
struct VectorHash{
    size_t operator()(const matrix &v)const{
        std::hash<int> hasher;
        size_t seed=0;
        for(auto & it:v)
            for(auto & itt:it)
                seed ^=hasher(itt)+0x933779b9+(seed<<6) + (seed>>2);
            return seed;
    }
};
int BFS (std::shared_ptr<Board> BoardState, matrix& result, std::vector<char>& pattern)
{
    if(BoardState->getBoard()==Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }
    auto start = std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;
    std::set<matrix> hold;
    std::queue<std::shared_ptr<Node>> open_list;
    std::unordered_set<matrix, VectorHash> explored;

    open_list.push(start);
    while(!open_list.empty()){
        curNode = open_list.front();
        explored.insert(curNode->getState());
        open_list.pop();
        if(BoardState->getBoard()==Goal){
                std::cout << curNode->getCounter() << std::endl;
                std::cout << curNode->getPath();
                return 1;
        }
        else {
            for (const auto &it:curNode->getPossibleMovesForNode()){
                BoardState->setBoardSize(curNode->getState());
                BoardState->setCoordinates();
                BoardState->takeAction(it);

                Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

                if(explored.find(Children->getState()) != explored.end())
                    continue;

                if(BoardState->getBoard()==Goal) {
                    std::cout << Children->getCounter() << std::endl;
                    std::cout << Children->getPath();
                    return 1;
                }

               if(hold.find(Children->getState()) != hold.end())
                   continue;
               open_list.push(Children);
               hold.insert(Children->getState());
            }
        }

    }
    return 15;
}

matrix parserToMatrix(std::string& arg) {
    matrix Numbers;
    std::ifstream infile(arg.c_str());
    if(!infile.fail()) {
        std::string String;
        while (getline(infile, String)) {
            //Kinda lazy solution
            if (String.size() > 3) {
                std::vector<int> Line;
                std::stringstream Stream(String);
                int a;
                while (Stream >> a)
                    Line.push_back(a);
                Numbers.push_back(Line);
            }
        }
        infile.close();
        return Numbers;
    }
    else std::cout << "FILE DOESNT EXIST!" << std::endl;
    return Goal;
}
int main(int argc, char* argv[]) {
    clock_t tStart = clock();
    std::vector<char> pattern;
    std::vector<std::string> fileName;
    if(argc>1) {
        fileName.assign(argv + 1, argv + argc-1);
    }
    std::string Hold;
    for(auto &it:fileName)
        Hold.append(it);
    //STRASZNIE CHUJOWO ZROBIONE
    if(argc>2) {
        std::string str = (argv[2]);
        for (unsigned int i = 0; i <= 3; i++) {
            pattern.push_back(str.at(i));
        }
    }
    matrix Testuje = parserToMatrix(Hold);
    auto Test = std::make_shared<Board>(Testuje);
    Test->setCoordinates();

    BFS(Test, Goal, pattern);
    printf("\nTime taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}