#include <iostream>
#include "Node.h"
#include <queue>
#include <memory>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>

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
int BFS (std::shared_ptr<Board> BoardState, matrix resoult)
{
    //TODO Kinda stuck on how to move around graph via nodes, should I save the state of the board before entering childrens?
    if(BoardState->getBoardSize()==Goal){
        std::cout<<"Found Solution";
        return 1;
    }
    auto start = std::make_shared<Node>("Error", nullptr, BoardState->getNeightbours(), BoardState->getBoardSize());
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node>Children;
    std::set<matrix> hold;
    std::queue<std::shared_ptr<Node>> open_list;
    std::unordered_set<matrix, VectorHash> explored;

    open_list.push(start);
    int numExpanded = 0 ;
    while(!open_list.empty()){
        curNode = open_list.front();
        open_list.pop();



            if(BoardState->getBoardSize()==Goal){
                    std::cout << "FOUND SOLUTION";
                    std::cout << curNode->getPath() << std::endl;
                    return 1;
                    break;
            }
            else {
                for (auto &it:curNode->getNeightbours()){
                    BoardState->setBoardSize(curNode->getState());
                    BoardState->setCoordinates();
                    BoardState->takeAction(it);

                    Children = std::make_shared<Node> (it,curNode, BoardState->getNeightbours() , BoardState->getBoardSize());
                   std::cout<<"#####################################\n";
                    BoardState->printSize(BoardState->getBoardSize());

                    std::cout<<"#####################################\n";
                    if(BoardState->getBoardSize()==Goal) {
                        std::cout<<"FOUND SOLUTION" << std::endl;
                        std::cout << Children->getPath()<<std::endl;
                        return 1;
                        break;
                    }

                   if(explored.find(Children->getState())==explored.end()){
                       if(hold.find(Children->getState())==hold.end())
                           open_list.push(Children);
                            /*
                             * JAK TO SOBIE ODKOMENTUEJSZ TO MASZ JAK WYGLADAL BOARD W KAZDYM PRZEBIEGU
                             * I JAK SOBIE SKACZE
                             */
                            hold.insert(Children->getState());
                       }
                    else {
                   }
                }
                explored.insert(curNode->getState());
                //std::cout<<"EXPLORED SIZE "<<explored.size() <<" OPEN LIST " << open_list.size()<<std::endl;
            }

    }
    return 15;
}
int main() {
    matrix Testuje={{1,2,3,4},
                    {5,10,6,7},
                    {9,14,11,8},
                    {13,0,15,12}};
    auto Test = std::make_shared<Board>(Testuje);
    Test->setCoordinates();

    BFS(Test, Goal);

    return 0;
}