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

const int Manhattan(const matrix &arg){
    int sum(0);
    for(int i(0); i < arg.size(); ++i)
        for(int j(0); j < arg[0].size(); ++j) {
            int value = arg[i][j];
//            if (arg[i][j] != 0 && arg[i][j] != Goal[i][j])
//            {
//               auto makePair = [=](int value, matrix arg) {
//                    for (int y(0); y < 4; y++)
//                        for (int x(0); x < 4; x++)
//                            if (arg[x][y] == value)
//                                return std::make_pair( x, y);
//                };
            if(value == 0)
                continue;
                sum += abs( i - ( value -1 ) / arg.size() ) + abs( j - ((value-1)%arg.size()));
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
    std::vector<uint_fast16_t> pattern = {'D','U','R','L'};
    std::shared_ptr<Node> curNode;
    std::shared_ptr<Node> Children;

    auto cmpManhattan = [=](std::shared_ptr<Node> &left, std::shared_ptr<Node> &right){
        return ( left->getCounter() + Manhattan (left->getState()) ) >= ( right->getCounter() + Manhattan(right->getState()) );
    };
    std::priority_queue<std::shared_ptr<Node>, std::deque<std::shared_ptr<Node>>, decltype(cmpManhattan) > open_list(cmpManhattan);
    std::unordered_set<size_t > explored;
    open_list.push(std::make_shared<Node>('E', nullptr, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern));
    ++realOpenListSize;

    while(!open_list.empty()){
        curNode = open_list.top();
        ++realExploredSize;
        explored.insert(Hash<size_t >()(curNode->getState()));
        open_list.pop();
        --realOpenListSize;

        for (const auto &it:curNode->getPossibleMovesForNode()){
            BoardState->setBoardSize(curNode->getState());
            BoardState->setCoordinates();
            BoardState->takeAction(it);
            Children = std::make_shared<Node> (it, curNode, BoardState->getPossibleMoves(), BoardState->getBoard(), pattern);

            if (Children->getCounter() > maxRecursionDepth) maxRecursionDepth = Children->getCounter();
            if (Children -> getCounter() == 8 )
                continue;
            if(explored.find(Hash<size_t >()(Children->getState())) != explored.end())
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

#endif //FIFTEENGAME_MANHATTAN_CPP