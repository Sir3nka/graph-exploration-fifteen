//
// Created by root on 20.10.18.
//

#include "Node.h"

const std::vector<std::string>& Node::getNeightbours() const {
    return this->neightbours;
}
const std::string& Node::getActionTaken() const {
    return this->actionTaken;
}
Node* Node::getParent() const {
    return this ->parent;
}

const std::string &Node::getPath() const {
    return path;
}
std::vector<std::string> Node::possibleMoves(){


}
