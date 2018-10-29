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
    std::vector<unsigned short> posMoves;
    std::string path;
    unsigned short counter;
    unsigned short actionTaken;
public:
    Node(const unsigned short actionTaken, NodePtr parent, const std::vector<unsigned short>& neightbours, matrix oldState, std::vector<unsigned short>& pattern): actionTaken(actionTaken),
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
    unsigned short operator()();

    matrix& getState();

    const std::vector<unsigned short>& getPossibleMovesForNode() const;

    NodePtr getParent() const;

    const std::string& getPath() const;
    unsigned short getCounter() const;
};
#endif //FIFTEENGAME_NODE_H
