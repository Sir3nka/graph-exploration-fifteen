//
// Created by Dirkuu on 01.11.2018.
//

#ifndef FIFTEENGAME_BFS_CPP
#define FIFTEENGAME_BFS_CPP

#include <memory>
#include <queue>
#include <unordered_set>
#include "hashes.h"
#include "Board.h"
#include "Node.h"

int BFS (std::shared_ptr<Board> BoardState, unsigned short& realOpenListSize, unsigned short& realExploredSize,
        int& maxRecursionDepth, unsigned short& numbersOfSteps, std::string& path, std::vector<uint_fast16_t>& pattern)
        {
    if(BoardState->getBoard() == Goal){
        numbersOfSteps  = 0;
        path            = "";
        return 1;
    }

    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;
    std::queue<std::shared_ptr<Node>> open_list;
    std::unordered_set<size_t> explored;
    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));
    ++realOpenListSize;

    while(!open_list.empty()){
        curNode = open_list.front();
        ++realExploredSize;
        explored.insert(Hash<size_t>()(curNode->getState()));
        open_list.pop();
        --realOpenListSize;

        for (const auto &it:curNode->getPossibleMovesForNode()){
            BoardState->setBoardSize(curNode->getState());
            BoardState->setCoordinates();
            BoardState->takeAction(it);
            Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

            if (Children->getCounter() > maxRecursionDepth) maxRecursionDepth = Children->getCounter();
            if(explored.find(Hash<size_t>()(Children->getState()) ) != explored.end())
                continue;
            else if(BoardState->getBoard() == Goal) {
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

#endif //FIFTEENGAME_BFS_CPP