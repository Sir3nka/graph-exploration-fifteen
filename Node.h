//
// Created by root on 20.10.18.
//

#ifndef FIFTEENGAME_NODE_H
#define FIFTEENGAME_NODE_H

#include <string>
#include <vector>
class Node{
public:
    Node(const std::string &actionTaken, Node *parent, const std::vector<std::string > & neightbours) : actionTaken(actionTaken),
    parent(parent),neightbours(neightbours) {
        if(parent != nullptr){
            this->path = parent->getPath();
            if(actionTaken!="ERROR"){
                path+=this->actionTaken;
            }
        }
    }

    const std::vector<std::string> &getNeightbours() const;

    Node *getParent() const;

    const std::string &getActionTaken() const;
    const std::string &getPath() const;
    std::vector<std::string> possibleMoves();

private:
    std::string actionTaken;
    std::string path;
    Node *parent;
    std::vector<std::string> neightbours;

};
#endif //FIFTEENGAME_NODE_H
