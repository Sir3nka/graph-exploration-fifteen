//
// Created by root on 20.10.18.
//

#ifndef FIFTEENGAME_NODE_H
#define FIFTEENGAME_NODE_H

#include <string>
#include <vector>
#include <memory>
#include "Board.h"

class Node{
    typedef std::shared_ptr<Node> NodePtr;
private:
    NodePtr parent;
    matrix oldState;
    std::vector<int> posMoves;
    std::string path;
    int counter;
    int actionTaken;
public:
    Node(const int actionTaken, NodePtr parent, const std::vector<int>& neightbours, matrix oldState, std::vector<int>& pattern): actionTaken(actionTaken),
    parent(parent), oldState(oldState), counter(0) {
        posMoves.reserve(4);

        for(const auto &patternFromAgument:pattern)
            for (const auto &possibleMoveFromNeightbours:neightbours)
                if(patternFromAgument == possibleMoveFromNeightbours)
                        this->posMoves.emplace_back(possibleMoveFromNeightbours);

        if(parent != nullptr){
            this->path = parent->getPath();
            if(actionTaken != 'E'){
                path += this->actionTaken;
            }
            counter += 1 + this->parent->getCounter();
        }
    }

    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;
    int operator()();

    matrix& getState();

    const std::vector<int>& getPossibleMovesForNode() const;

    NodePtr getParent() const;

    const char &getActionTaken() const;
    const std::string& getPath() const;
    std::vector<std::string> possibleMoves();
    int getCounter() const;
};
#endif //FIFTEENGAME_NODE_H
