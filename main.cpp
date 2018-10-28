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
#include <stack>


matrix Goal ={{1,2,3,4},
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
int BFS (std::shared_ptr<Board> BoardState, matrix resoult, std::vector<std::string> &pattern)
{
    if(BoardState->getBoard()==Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }
    auto start = std::make_shared<Node>("Error", nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node>Children;
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
                std::cout << curNode->getPath() ;
                return 1;
        }
        else {
            for (const auto &it:curNode->getPossibleMovesForNode()){
                BoardState->setBoardSize(curNode->getState());
                BoardState->setCoordinates();
                BoardState->takeAction(it);

                Children = std::make_shared<Node> (it,curNode, BoardState->getPossibleMoves() , BoardState->getBoard(), pattern);

                if(explored.find(Children->getState()) != explored.end())
                    continue;

                if(BoardState->getBoard()==Goal) {
                    std::cout << Children->getCounter() << std::endl;
                    std::cout << Children->getPath() ;
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

void Visit(std::shared_ptr<Board> BoardState, std::shared_ptr<Node> cN, std::stack<std::shared_ptr<Node>> &ol,std::unordered_set<matrix, VectorHash> &explored, std::vector<std::string> &pattern,
        std::set<matrix> &hold,int &counter,std::string &it
) {
    if(counter<2)
     {
            counter += 1;
            BoardState->setBoardSize(cN->getState());
            BoardState->setCoordinates();
            BoardState->takeAction(it);
            auto Children = std::make_shared<Node>(it, cN, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);
            if (BoardState->getBoard() == Goal) {
                std::cout << Children->getCounter() << std::endl;
                std::cout << Children->getPath();
                return;
            }
            for(auto it:Children->getPossibleMovesForNode()) {
                if(hold.find(Children->getState())!=hold.end())
                    continue;
                ol.push(Children);
                hold.insert(Children->getState());

                if(explored.find(Children->getState())!=explored.end())
                    continue;
                Visit(BoardState, Children, ol, explored, pattern, hold, counter, it);
                explored.insert(Children->getState());
            }

        }
    return;
    }


int DFS (std::shared_ptr<Board> BoardState, matrix resoult, std::vector<std::string> &pattern){
    if(BoardState->getBoard()==Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }
    auto start = std::make_shared<Node>("Error", nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node>Children;
    std::set<matrix> hold;
    std::stack<std::shared_ptr<Node>> open_list;
    std::unordered_set<matrix, VectorHash> explored;

    open_list.push(start);
    while(!open_list.empty()){
        int rc=0;
        curNode = open_list.top();
        explored.insert(curNode->getState());
        //std::cout << " TEST " << open_list.size() <<std::endl;
        open_list.pop();
        if(BoardState->getBoard()==Goal){
            std::cout << curNode->getCounter() << std::endl;
            std::cout << curNode->getPath() ;
            return 1;
        }
        else {
            for (auto it:curNode->getPossibleMovesForNode()) {
                Visit(BoardState, curNode, open_list, explored, pattern, hold, rc, it);
                BoardState->printSize(BoardState->getBoard());
                if(explored.find(curNode->getState())!=explored.end())
                    continue;
            }
            }
        }
        return 1;
    }


matrix parserToMatrix(std::string &arg) {
matrix Numbers;
std::ifstream infile(arg.c_str());
if(!infile.fail()) {
    std::string String;
    int a;
    while (getline(infile, String)) {
        //Kinda lazy solution
        if (String.size() > 3) {
            std::vector<int> Line;
            std::stringstream Stream(String);
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
    std::vector<std::string> pattern ;
    std::vector<std::string>  fileName;
    if(argc>1) {
        fileName.assign(argv + 1, argv + argc-1);
    }
    std::string Hold;
    for(auto &it:fileName)
        Hold.append(it);
    //STRASZNIE CHUJOWO ZROBIONE
    if(argc>2) {
        std::string str = (argv[2]);
        std::string help;
        for (unsigned int i = 0; i <= 3; i++) {
            char hold = str.at(i);
            pattern.push_back(help=hold);
        }
    }
    matrix Testuje=parserToMatrix(Hold);
    auto Test = std::make_shared<Board>(Testuje);
    Test->setCoordinates();
    int a =20;
    std::string A;
    std::cout <<"What method \n";
    std::cin >> A;
    clock_t tStart = clock();
    if(A=="BFS")
    BFS(Test, Goal, pattern);
    if(A=="DFS")
    DFS(Test, Goal, pattern);
    printf("\nTime taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}