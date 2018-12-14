//
// Created by Dirkuu on 01.11.2018.
//

#ifndef FIFTEENGAME_HAMMING_CPP
#define FIFTEENGAME_HAMMING_CPP

#include <memory>
#include <queue>
#include <unordered_set>
#include "hashes.h"
#include "Board.h"
#include "Node.h"

const uint_fast16_t Hamming(matrix arg){
    uint_fast16_t goal(0);
    for(uint_fast16_t i(0); i < 4; ++i)
        for(uint_fast16_t j(0); j < 4; ++j){
            if(arg[i][j] != 0 && arg[i][j] != Goal[i][j])
                goal++;
        }
    return goal;
}

int ASTARhamming(const std::shared_ptr<Board> &BoardState, unsigned short& realOpenListSize, unsigned short& realExploredSize,
        int& maxRecursionDepth, unsigned short& numbersOfSteps, std::string& path){

    if(BoardState->getBoard() == Goal){
        numbersOfSteps  = 0;
        path            = "";
        return 1;
    }
    std::vector<uint_fast16_t> pattern = {'U','D','L','R'};
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;
    auto cmpHamming = [](std::shared_ptr<Node> &left,std::shared_ptr<Node> &right){
        return left->getCounter() + Hamming (left->getState()) > right->getCounter() + Hamming(right->getState()) &&
               left->getCounter() + Hamming (left->getState()) != right->getCounter() + Hamming(right->getState());
    };
    std::priority_queue<std::shared_ptr<Node>, std::deque<std::shared_ptr<Node>>, decltype(cmpHamming) > open_list(cmpHamming);
    std::unordered_set<uint_fast16_t> explored;
    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));
    ++realOpenListSize;

    while(!open_list.empty()){
        curNode = open_list.top();
        ++realExploredSize;
        explored.insert(Hash<uint_fast16_t >()(curNode->getState()));
        open_list.pop();
        --realOpenListSize;

        for (const auto &it:curNode->getPossibleMovesForNode()){
            BoardState->setBoardSize(curNode->getState());
            BoardState->setCoordinates();
            BoardState->takeAction(it);
            Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

            if (Children->getCounter() > maxRecursionDepth)         maxRecursionDepth = Children->getCounter();
            if(explored.find(Hash<uint_fast16_t >()(Children->getState())) != explored.end())
                continue;
            else if(BoardState->getBoard() == Goal) {
                numbersOfSteps  = Children->getCounter();
                path            = Children->getPath();
                return 1;
            };
            open_list.push(Children);
            ++realOpenListSize;
        }
    }
    numbersOfSteps = 65535;
    return -1;
}


#endif //FIFTEENGAME_HAMMING_CPP