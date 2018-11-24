//
// Created by Dirkuu on 01.11.2018.
//

#ifndef FIFTEENGAME_DFS_CPP
#define FIFTEENGAME_DFS_CPP

#include <memory>
#include <stack>
#include <unordered_set>
#include "hashes.h"
#include "Board.h"
#include "Node.h"
#include <unordered_map>

int DFS (std::shared_ptr<Board> BoardState, unsigned short& realOpenListSize, unsigned short& realExploredSize, int& maxRecursionDepth, unsigned short& numbersOfSteps, std::string& path, std::vector<uint_fast16_t>& pattern, uint_fast16_t maxRecurionsNumber)
{
    if(BoardState->getBoard() == Goal){
        //std::cout<<"Found Solution, loaded matrix is equal to final matrix";
        numbersOfSteps  = 0;
        path            = "";
        return 1;
    }

    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;
    std::stack<std::shared_ptr<Node>> open_list;
    std::unordered_map<int, int> explored;
    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));
    ++realOpenListSize;

    while(!open_list.empty()){
        curNode = open_list.top();
        ++realExploredSize;
        explored[VectorDFSHash()(curNode->getState())] = curNode->getCounter();
        open_list.pop();
        --realOpenListSize;


        for (const auto &it:curNode->getPossibleMovesForNode()){
            BoardState->setBoardSize(curNode->getState());
            BoardState->setCoordinates();
            BoardState->takeAction(it);


            Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

            if (Children->getCounter() > maxRecursionDepth)         maxRecursionDepth = Children->getCounter();

            if(Children->getPath().length() >= maxRecurionsNumber)
                continue;
            else if(explored.find(VectorDFSHash()(Children->getState())) != explored.end()) {
                if(explored.at( VectorDFSHash()( Children->getState() )) <= Children ->getCounter() ) {
                    continue;
                }else {
                        explored.at(VectorDFSHash()(Children->getState())) = Children->getCounter();
                }

            }
            else if(BoardState->getBoard() == Goal) {
                //std::cout << Children->getCounter() << std::endl;
                //std::cout << Children->getPath();
                numbersOfSteps  = Children->getCounter();
                path            = Children->getPath();

                return 1;
            }
            open_list.push(Children);
            ++realOpenListSize;
        }
    }
    numbersOfSteps = 65535;
    return -1;
}

#endif //FIFTEENGAME_DFS_CPP