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
struct VectorBFSHash{
    //With unsigned short we cannot into finding long path
    uint_fast16_t operator()(const matrix &v)const{
        std::hash<uint_fast16_t> hasher;
        uint_fast16_t  seed(0);
        for(auto & it:v)
            for(auto & itt:it)
                seed ^= hasher(itt) + 0x933779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};
struct VectorDFSHash{
    //
    inline int operator()(const matrix &v)const{
        std::hash<int> hasher;
        int seed(0);
        for(auto & it:v)
            for(auto & itt:it)
                seed ^= hasher(itt) + 0x933779b9 +(seed<<6) + (seed>>2);
        return seed;
    }
};
struct VectorASTRHash{
    //
    inline size_t operator()(const matrix &v)const{
        std::hash<size_t> hasher;
        size_t seed(0);
        for(auto & it:v)
            for(auto & itt:it)
                seed ^= hasher(itt) + 0x933779b9 +(seed<<6) + (seed>>2);
        return seed;
    }
};
int BFS (std::shared_ptr<Board> BoardState, std::vector<uint_fast16_t>& pattern)
{
    if(BoardState->getBoard() == Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }

    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;
    std::queue<std::shared_ptr<Node>> open_list;
    std::unordered_set<uint_fast16_t> explored;
    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));

    while(!open_list.empty()){
        curNode = open_list.front();
        explored.insert(VectorBFSHash()(curNode->getState()));
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


                Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

                if(explored.find(VectorBFSHash()(Children->getState()) ) != explored.end())
                    continue;
                else if(BoardState->getBoard() == Goal) {
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

int DFS (std::shared_ptr<Board> BoardState, std::vector<uint_fast16_t>& pattern, uint_fast16_t maxRecurionsNumber)
{
    if(BoardState->getBoard() == Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }

    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;
    std::stack<std::shared_ptr<Node>> open_list;
    std::unordered_set<int> explored;
    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));

    while(!open_list.empty()){
        curNode = open_list.top();
        explored.insert(VectorDFSHash()(curNode->getState()));
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


                Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

                if(Children->getPath().length() >= maxRecurionsNumber)
                    continue;
                else if(explored.find(VectorDFSHash()(Children->getState())) != explored.end())
                    continue;
                else if(BoardState->getBoard() == Goal) {
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
const uint_fast16_t Hamming(matrix arg){
    uint_fast16_t goal=0;
    for(uint_fast16_t i=0; i<=3; i++)
        for(uint_fast16_t j=0;j<=3;j++){
            if(arg[i][j]==0)
                //Zaznaczaał żeby ignorować pole z zerem
                continue;
            if(arg[i][j]!=Goal[i][j])
                goal++;
        }
    return goal;
}

const uint_fast16_t Manhattan(const std::shared_ptr<Board> &BoardState){
    uint_fast16_t sum=0;
    for(uint_fast16_t i=0;i<=3;i++)
        for(uint_fast16_t j=0; j<=3;j++) {
            if(Goal[i][j]==0)
                continue;
            sum += abs((i + j) - BoardState->findCoordinatesofValue(Goal[i][j]));
        }
    return sum;
}

int ASTAR(const std::shared_ptr<Board> &BoardState, std::vector<uint_fast16_t> &pattern){
    if(BoardState->getBoard() == Goal){
        std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        return 1;
    }

    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;
    //Lambda przypisana do funkcji, śmieszne
    //TODO make it able to pick which comparator (now its for manhatann)
    auto cmpHamming = [](std::shared_ptr<Node> &left,std::shared_ptr<Node> &right){
        return left->getCounter() + Hamming (left->getState()) >= right->getCounter() + Hamming(right->getState()) &&
               left->getCounter() + Hamming (left->getState()) != right->getCounter() + Hamming(right->getState());
    };
    //COMMENT THIS ONE FOR HAMMING
    auto cmpManhattan = [=](std::shared_ptr<Node> &left, std::shared_ptr<Node> &right){
        return left->getCounter() + Manhattan (BoardState) >= right->getCounter() + Manhattan(BoardState) &&
               left->getCounter() + Manhattan (BoardState) != right->getCounter() + Manhattan(BoardState);
    };

    std::priority_queue<std::shared_ptr<Node>, std::deque<std::shared_ptr<Node>>, decltype(cmpHamming) > open_list(cmpHamming);
    std::unordered_set<size_t> explored;

    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));

    while(!open_list.empty()){
        curNode = open_list.top();
        explored.insert(VectorASTRHash()(curNode->getState()));
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

                Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

                if(explored.find(VectorASTRHash()(Children->getState())) != explored.end())
                    continue;
                else if(BoardState->getBoard() == Goal) {
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
        uint_fast16_t a;
        std::vector<uint_fast16_t> Line;

        while (getline(infile, String)) {
            Line.reserve(3);
            //Kinda lazy solution
            if (String.size() > 3) {
                std::stringstream Stream(String);
                while (Stream >> a) {
                    Line.emplace_back(a);
                }
                Numbers.emplace_back(Line);
                std::vector<uint_fast16_t>().swap(Line);
            }
        }
        infile.close();
        return Numbers;
    }
    else std::cout << "FILE DOESNT EXIST!" << std::endl;
    return Goal;
}

int main(int argc, char* argv[]) {
    std::vector<uint_fast16_t> pattern;
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
        for (unsigned char i(0); i < 4; ++i) {
            pattern.emplace_back(str.at(i));
        }
    }
    matrix Testuje(parserToMatrix(Hold));

    auto Test(std::make_shared<Board>(Testuje));

    std::cout<<"MANHATANN VALUE: " << Manhattan(Test) << std::endl;
    std::cout<<"HAMMING VALUE: " << Hamming(Test->getBoard()) << std::endl;

    Test->setCoordinates();

    std::string methodName;
    methodName.reserve(3);


    clock_t tStart;

    std::cout << "What method \n";
    std::cin >> methodName;

    if(methodName == "bfs") {
        tStart = clock();
        BFS(Test, pattern);
    }
    else if(methodName == "dfs") {
        uint_fast16_t maxRecurionsNumber;

        std::cout<<"NUMBER OF RECURSIONS\n";
        std::cin>>maxRecurionsNumber;
        tStart = clock();

        DFS(Test, pattern, maxRecurionsNumber);
    }
    else if(methodName == "astr"){
        tStart = clock();
        ASTAR(Test, pattern);
    }
    printf("\nTime taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}
