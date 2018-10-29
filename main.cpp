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


matrix Goal =  {{1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
                {13,14,15,0}};
/*
 * Fajna funkcja haszujaca wiem
 */
struct VectorHash{
    //
    unsigned short operator()(const matrix &v)const{
        std::hash<unsigned short> hasher;
        unsigned short seed(0);
        for(auto & it:v)
            for(auto & itt:it)
                seed ^=hasher(itt)+0x933779b9+(seed<<6) + (seed>>2);
            return seed;
    }
};
int BFS (std::shared_ptr<Board> BoardState, matrix& result, std::vector<unsigned short>& pattern)
{
    if(BoardState->getBoard()==Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }
    auto start(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));

    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node>Children;
    std::queue<std::shared_ptr<Node>> open_list;
    std::unordered_set<size_t> explored;
    open_list.push(start);

    while(!open_list.empty()){
        curNode = open_list.front();
        explored.insert(VectorHash()(curNode->getState()));
        open_list.pop();

        if(BoardState->getBoard() == Goal){
                std::cout << curNode->getCounter() << std::endl;
                std::cout << curNode->getPath();
                return 1;
        }
        else {
            for (const auto &it:curNode->getPossibleMovesForNode()){
                BoardState->setBoardSize(curNode->getState());
                BoardState->setCoordinates();
                BoardState->takeAction(it);


                Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves() , BoardState->getBoard(), pattern);

                if(explored.find(VectorHash()(Children->getState()) ) != explored.end())
                    continue;

                if(BoardState->getBoard()==Goal) {
                    std::cout << Children->getCounter() << std::endl;
                    std::cout << Children->getPath();
                    return 1;
                }
               open_list.push(Children);
            }
        }
    }
    return 15;
}

int DFS (std::shared_ptr<Board> BoardState, matrix resoult, std::vector<unsigned short>& pattern, unsigned short rec)
{
    if(BoardState->getBoard() == Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }
    auto start = std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node>Children;
    std::stack<std::shared_ptr<Node>> open_list;
    std::unordered_set<size_t> explored;
    open_list.push(start);

    while(!open_list.empty()){
        curNode = open_list.top();
        explored.insert(VectorHash()(curNode->getState()));
        open_list.pop();
        if(BoardState->getBoard() == Goal){
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

                if(explored.find(VectorHash()(Children->getState()) ) != explored.end())
                    continue;

                if(Children->getPath().length() >= rec)
                    continue;

                if(BoardState->getBoard() == Goal) {
                    std::cout << Children->getCounter() << std::endl;
                    std::cout << Children->getPath() ;
                    return 1;
                }
                open_list.push(Children);
            }
        }

    }
    return 15;
}

matrix parserToMatrix(std::string& arg) {
    std::ifstream infile(arg.c_str());
    if(!infile.fail()) {
        matrix Numbers;
        Numbers.reserve(3);
        std::string String;
        unsigned short a;
        std::vector<unsigned short> Line;

        while (getline(infile, String)) {
            Line.reserve(3);
            //Kinda lazy solution
            if (String.size() > 3) {
                std::stringstream Stream(String);
                while (Stream >> a) {
                    Line.emplace_back(a);
                }
                Numbers.emplace_back(Line);
                std::vector<unsigned short>().swap(Line);
            }
        }
        infile.close();
        return Numbers;
    }
    else std::cout << "FILE DOESNT EXIST!" << std::endl;
    return Goal;
}
int main(int argc, char* argv[]) {
    std::vector<unsigned short> pattern;
    pattern.reserve(3);

    std::vector<std::string> fileName;
    fileName.reserve(1);

    std::string Hold;
    Hold.reserve(60);
    if(argc>1) {
        fileName.assign(argv + 1, argv + argc-1);
    }
    for(auto &it:fileName) {
        Hold.append(it);
    }
    //STRASZNIE CHUJOWO ZROBIONE
    if(argc>2) {
        std::string str(argv[2]);
        for (unsigned short i(0); i <= 3; ++i) {
            pattern.emplace_back(str.at(i));
        }
    }
    matrix Testuje(parserToMatrix(Hold));
    auto Test(std::make_shared<Board>(Testuje));
    Test->setCoordinates();
    std::string methodName;
    methodName.reserve(3);
    std::cout <<"What method \n";
    std::cin >> methodName;
    clock_t tStart;
    if(methodName == "BFS") {
        tStart = clock();
        BFS(Test, Goal, pattern);
    }
    if(methodName == "DFS") {
        int rec;
        std::cout<<"NUMBER OF RECURSIONS\n";
        std::cin>>rec;
        tStart = clock();
        DFS(Test, Goal, pattern, rec);
    }
    printf("\nTime taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}