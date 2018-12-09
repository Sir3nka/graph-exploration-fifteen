//
// Created by Dirkuu on 01.11.2018.
//

#ifndef FIFTEENGAME_MANHATTAN_CPP
#define FIFTEENGAME_MANHATTAN_CPP

#include <memory>
#include <queue>
#include <unordered_set>
#include "hashes.h"
#include "Board.h"
#include "Node.h"

const uint_fast16_t Manhattan(const std::shared_ptr<Board> &BoardState){
    uint_fast16_t sum(0);
    for(uint_fast16_t i(0); i < 4; ++i)
        for(uint_fast16_t j(0); j < 4; ++j) {
            if(BoardState->getBoard()[i][j] == 0)
                continue;
            sum += abs((i + j) - BoardState->findCoordinatesofValue(Goal[i][j]));
        }
    return sum;
}

int ASTARmanhattan(const std::shared_ptr<Board> &BoardState, unsigned short& realOpenListSize, unsigned short& realExploredSize,
        int& maxRecursionDepth, unsigned short& numbersOfSteps, std::string& path){

    if(BoardState->getBoard() == Goal){
        numbersOfSteps  = 0;
        path            = "";
        return 1;
    }
    std::vector<uint_fast16_t> pattern;
    pattern.emplace_back('U');
    pattern.emplace_back('D');
    pattern.emplace_back('L');
    pattern.emplace_back('R');
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;

    auto cmpManhattan = [=](std::shared_ptr<Node> &left, std::shared_ptr<Node> &right){
        return left->getCounter() + Manhattan (BoardState) >= right->getCounter() + Manhattan(BoardState) &&
               left->getCounter() + Manhattan (BoardState) != right->getCounter() + Manhattan(BoardState);
    };
    std::priority_queue<std::shared_ptr<Node>, std::deque<std::shared_ptr<Node>>, decltype(cmpManhattan) > open_list(cmpManhattan);
    std::unordered_set<size_t> explored;
    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));
    ++realOpenListSize;

    while(!open_list.empty()){
        curNode = open_list.top();
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
            if(explored.find(Hash<size_t>()(Children->getState())) != explored.end())
                continue;
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

#endif //FIFTEENGAME_MANHATTAN_CPP