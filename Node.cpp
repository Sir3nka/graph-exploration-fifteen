//
// Created by root on 20.10.18.
//

#include "Node.h"

const std::vector<unsigned short>& Node::getPossibleMovesForNode() const {
    return posMoves;
}
std::shared_ptr<Node> Node::getParent() const {
    return parent;
}

const std::string &Node::getPath() const {
    return path;
}

matrix& Node::getState()  {
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
unsigned short Node::operator() () {
    for( auto&it:this->getPossibleMovesForNode())
        return it;
    return 1;
}

unsigned short Node::getCounter() const {
    return counter;
}
