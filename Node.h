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
    Node(const std::string &actionTaken, NodePtr parent, const std::vector<std::string > & neightbours, matrix oldState, std::vector<std::string> &pattern) : actionTaken(actionTaken),
    parent(parent),oldState(oldState) {
        for(const auto &patternFromaAgument:pattern)
            for (const auto &possibleMoveFromNeightbours:neightbours)
                if(patternFromaAgument==possibleMoveFromNeightbours)
                        this->posMoves.push_back(possibleMoveFromNeightbours);
        this->counter=0;
        if(parent != nullptr){
            this->path = parent->getPath();
            if(actionTaken!="ERROR"){
                path+=this->actionTaken;
            }
            counter += 1+this->parent->getCounter();
        }
        this->seed = hashGenerator(oldState);
    }

    size_t getSeed() const;

    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;
    Node operator()(matrix &arg, size_t& value) ;

    matrix getState() ;

    const std::vector<std::string> &getPossibleMovesForNode() const;

    NodePtr getParent() const;

    const std::string &getActionTaken() const;
    const std::string &getPath() const;
    std::vector<std::string> possibleMoves();
    int getCounter() const;


private:
    std::string actionTaken;
    std::string path;
    NodePtr parent;
    std::vector<std::string> posMoves;
    matrix oldState;
    int counter;
    size_t seed;
    size_t hashGenerator(const matrix &v)const;

    };

#endif //FIFTEENGAME_NODE_H
