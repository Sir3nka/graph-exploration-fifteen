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
    matrix oldState;
    std::vector<uint_fast16_t> posMoves;
    NodePtr parent;
    std::string path;
    unsigned short counter;
    unsigned short actionTaken;

public:
    Node(const uint_fast16_t actionTaken, NodePtr parent, const std::vector<uint_fast16_t>& neightbours, matrix oldState, std::vector<uint_fast16_t>& pattern): actionTaken(actionTaken),
                                                                                                                                                                parent(parent), oldState(oldState), counter(0) {
        posMoves.reserve(4);

        for(const auto &patternFromArgument:pattern) {
            for (const auto &possibleMoveFromNeightbours:neightbours)
                if (patternFromArgument == possibleMoveFromNeightbours)
                    this->posMoves.emplace_back(possibleMoveFromNeightbours);

        }
        if(parent != nullptr){
            this->path = parent->getPath();
            if(actionTaken != 'E'){
                path += this->actionTaken;
            }
            counter += 1 + this->parent->getCounter();
        }
    }

    unsigned short getActionTaken() const;

    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;
    uint_fast16_t operator()();

    matrix& getState();
    const std::vector<uint_fast16_t>& getPossibleMovesForNode() const;

    NodePtr getParent() const;
    void Reverse ();

    const std::string& getPath() const;
    uint_fast16_t getCounter() const;
};
#endif //FIFTEENGAME_NODE_H
