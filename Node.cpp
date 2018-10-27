//
// Created by root on 20.10.18.
//

#include "Node.h"

const std::vector<char>& Node::getPossibleMovesForNode() const {
    return this->posMoves;
}
const char& Node::getActionTaken() const {
    return this->actionTaken;
}
std::shared_ptr<Node> Node::getParent() const {
    return this ->parent;
}

const std::string &Node::getPath() const {
    return path;
}
std::vector<std::string> Node::possibleMoves(){


}

matrix Node::getState()  {
    return oldState;
}

bool Node::operator==(const Node &rhs) const {
    return actionTaken == rhs.actionTaken &&
           path == rhs.path &&
           parent == rhs.parent &&
           posMoves == rhs.posMoves;
}

bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}
char Node::operator() () {
    char toReturn;
    for( auto&it:this->oldState)
        for( auto &itt:it)
            toReturn = itt;

    for( auto&it:this->getPossibleMovesForNode())
            toReturn = it;
    return toReturn;
}

int Node::getCounter() const {
    return counter;
}
