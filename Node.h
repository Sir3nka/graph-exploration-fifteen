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
    Node(const std::string &actionTaken, NodePtr parent, const std::vector<std::string > & neightbours, matrix oldState) : actionTaken(actionTaken),
    parent(parent),oldState(oldState) {
        for (const auto & it:neightbours){
            std::string toNotPush;
            if(parent!= nullptr) {
                if (parent->getActionTaken() == "D")
                    toNotPush = "U";
                if (parent->getActionTaken() == "L")
                    toNotPush = "R";
                if (parent->getActionTaken() == "R")
                    toNotPush = "L";
                if (parent->getActionTaken() == "U")
                    toNotPush = "D";
                if(it!=toNotPush)
                this->posMoves.push_back(it);
            }else{
                this->posMoves.push_back(it);
            }

        }
        if(parent != nullptr){
            this->path = parent->getPath();
            if(actionTaken!="ERROR"){
                path+=this->actionTaken;
            }
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

};
#endif //FIFTEENGAME_NODE_H
