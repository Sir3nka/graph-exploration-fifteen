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
    auto start = std::make_shared<Node>(BoardState->takeAction("L"), nullptr, BoardState->getNeightbours(), BoardState->getBoardSize());
    std::set<matrix> hold;
    std::queue<std::shared_ptr<Node>> open_list;
    std::unordered_set<matrix, VectorHash> explored;
    //std::map<matrix,int>explored;
    //std::shared_ptr<Board> Trying = std::make_shared<Board>(*BoardState);

    open_list.push(start);
    int numExpanded = 0 ;
    if(open_list.empty())
        std::cout<<"lista jest pusta";
    while(!open_list.empty()){
        auto curNode = open_list.front();
        //BoardState->printSize(curNode->getState());
        open_list.pop();
        //for (auto &it:curNode->getNeightbours())
        //    std::cout << "M "<<it <<" ";
        //std::cout<<" LAST MOVE "<<curNode->getActionTaken()<<std::endl;



            if(BoardState->getBoardSize()==Goal) {
                std::cout << "FOUND SOLUTION";
                return 1;
            }else {
                for (auto &it:curNode->getNeightbours()){
                    BoardState->setBoardSize(curNode->getState());
                    BoardState->setCoordinates();
                    BoardState->takeAction(it);
                    //std::cout<<"DEBUGGING FOR CHECKING EXPLORED\n ";
                    //BoardState->printSize(BoardState->getBoardSize());
                    //std::cout<<"####################################\n";

                    auto Children = std::make_shared<Node> (it,curNode, BoardState->getNeightbours() , BoardState->getBoardSize());
                    //std::cout<<" MOVE : " << Children->getActionTaken() << "__COUNTER " <<numExpanded<< std::endl;
                    //BoardState->printSize(BoardState->getBoardSize());

                    if(BoardState->getBoardSize()==Goal) {
                        std::cout<<"FOUND SOLUTION" << std::endl;
                        return 1;
                    }

                    std::cout<<std::endl;
                   if(explored.find(Children->getState())==explored.end()){
                       if(hold.find(Children->getState())==hold.end())
                           open_list.push(Children);
                            /*
                             * JAK TO SOBIE ODKOMENTUEJSZ TO MASZ JAK WYGLADAL BOARD W KAZDYM PRZEBIEGU
                             * I JAK SOBIE SKACZE
                             */
                            //BoardState->printSize(Children->getState());
                            hold.insert(Children->getState());
                            std::cout<<" SIZE OF OPEN " << open_list.size() << std::endl;
                       }
                    else {
                       //std::cout<< "DO I WORK?"<<std::endl;
                   }
                   //numExpanded++;
                }
                explored.insert(curNode->getState());
                std::cout<<" SIZE___"<<explored.size()<<std::endl;
                if(explored.size()>1500)
                    return 1;
                numExpanded++;
            }

    }
    return 15;
}
int main() {
    matrix Testuje={{1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,0},
                    {13,14,15,12}};
    auto Test = std::make_shared<Board>(Testuje);
    //ptrBoard Test = std::make_shared<Board>(Board())
    Test->setCoordinates();
    /*
     * MOVEMENT DEBUGGING
    int i=7;
    while(i!=0){
        std::cin >> i;
        std::cout << "BEFORE\n";
        Test->printSize(Test->getBoardSize());
            if(i==1)
                std::cout<<Test->takeAction("L")<<std::endl;
            if(i==2)
                std::cout<<Test->takeAction("R")<<std::endl;
            if(i==3)
                std::cout<<Test->takeAction("U")<<std::endl;
            if(i==4)
                std::cout<<Test->takeAction("D")<<std::endl;
        std::cout<<"###################################\n";
        Test->printSize(Test->getBoardSize());
        std::cout<<"AFTER\n";
    }
     */

    BFS(Test, Goal);

    return 0;
}