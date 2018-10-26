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
        for(const auto &itt:pattern)
            for (const auto &it:neightbours)
                if(it==itt)
                        this->posMoves.push_back(it);

        if(parent != nullptr){
            this->path = parent->getPath();
            if(actionTaken!="ERROR"){
                path+=this->actionTaken;
            }
        }
        this-> counter=0;
        if(parent!=nullptr) {
            counter += 1+this->parent->getCounter();
        }
    }

    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;
    std::string operator()() ;

    matrix getState() ;

    const std::vector<std::string> &getNeightbours() const;

    NodePtr getParent() const;

    const std::string &getActionTaken() const;
    const std::string &getPath() const;
    std::vector<std::string> possibleMoves();

private:
    std::string actionTaken;
    std::string path;
    NodePtr parent;
    std::vector<std::string> posMoves;
    matrix oldState;
    int counter;
public:
    int getCounter() const;

};
#endif //FIFTEENGAME_NODE_H
