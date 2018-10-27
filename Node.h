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
public:
    Node(const char &actionTaken, NodePtr parent, const std::vector<char> & neightbours, matrix oldState, std::vector<char> &pattern) : actionTaken(actionTaken),
    parent(parent),oldState(oldState) {
        for(const auto &patternFromAgument:pattern)
            for (const auto &possibleMoveFromNeightbours:neightbours)
                if(patternFromAgument == possibleMoveFromNeightbours)
                        this->posMoves.push_back(possibleMoveFromNeightbours);

        this->counter=0;
        if(parent != nullptr){
            this->path = parent->getPath();
            if(actionTaken != 'E'){
                path+=this->actionTaken;
            }
            counter += 1+this->parent->getCounter();
        }
    }

    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;
    char operator()() ;

    matrix getState() ;

    const std::vector<char> &getPossibleMovesForNode() const;

    NodePtr getParent() const;

    const char &getActionTaken() const;
    const std::string &getPath() const;
    std::vector<std::string> possibleMoves();
    int getCounter() const;


private:
    char actionTaken;
    std::string path;
    NodePtr parent;
    std::vector<char> posMoves;
    matrix oldState;
    int counter;
};
#endif //FIFTEENGAME_NODE_H
