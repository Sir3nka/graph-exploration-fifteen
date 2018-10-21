#include <iostream>
#include "Board.h"
#include "Node.h"
#include <queue>
    matrix Goal ={{1,2,3,4},
                  {5,6,7,8},
                  {9,10,11,12},
                  {13,14,15,0}};
int BFS (Board BoardState, Node start,  matrix resoult)
{
    //TODO Kinda stuck on how to move around graph via nodes, should I save the state of the board before entering childrens?
    std::queue<Node> open_list;
    std::vector < Node > explored;
    open_list.push(start);
    int numExpanded = 0 ;
    while(!open_list.empty()){
        Node curNode = open_list.front();
        Board curBoardState = BoardState;
        open_list.pop();
        numExpanded++;
            if(curBoardState.getBoardSize()==Goal)
                std::cout<<"FOUND SOLUTION";


    }
}
int main() {
    matrix Testuje={{1,2,3,4},
                    {5,6,7,0},
                    {8,9,10,11},
                    {12,13,14,15}};
    Board *Test = new Board(Testuje);
    //ptrBoard Test = std::make_shared<Board>(Board())
    Test->printSize(Test->getBoardSize());
    Test->setCoordinates();
    //std::cout<<Test->getHCoord()<<"  "<<Test->getWCoord();
    Test->takeAction("r");
    std::cout << " #################################3\n";
    Test->printSize(Test->getBoardSize());
    /*
     * Decided that nodes will have only list of their neightbours so whole takeAction need to be reworked
     * it needs to take coordinates as a param so we can move only to neighjtbours (white must be modified
     */
    /*
     * Dummy loop for checking if its working, in our main algorithm we will be creating nodes
     * and getting their neightbour vector to put it in the loop and push more nodes into open list
     * or something like that
     */
    Node *T = new Node(Test->takeAction("U"),nullptr,Test->getNeightbours());
    std::vector<Node> nodeContener;
    for (int i =0; i <=3; i++){
        nodeContener.push_back(*T);
        Test->printSize(Test->getBoardSize());
        T = new Node(Test->takeAction("l"),T,Test->getNeightbours());

    }
    /*for (const auto &it:nodeContener){
        std::cout << "\n SCIEZKA \n" << it.getPath();
    }*/
    int counter = 0;
    for ( auto &it:nodeContener){


        for(auto &hold:it.getNeightbours()) {
            std::cout <<"POSSIBLE MOVES " << hold <<" Counter"<<counter<< std::endl;
        }
        counter ++;
        }


    Test->printSize(Test->getBoardSize());
    delete Test;
    delete T;
    return 0;
}