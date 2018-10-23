//
// Created by root on 19.10.18.
//
#include "Board.h"
#include <algorithm>

Board::Board(const matrix &tab){
    this->boardSize=tab;
    this->hCoord=0;
    this->wCoord=0;
    }


const std::string Board::takeAction(const std::string &where) {
    //TODO No need to check if eligle for move, getNeightbours is responsible for that

    if (where =="U" ){
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord-1][wCoord]);
            this->hCoord--;
            return "U";
    }
    if(where =="L" ){
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord][wCoord-1]);
            this->wCoord--;
            return "L";
    }
    if(where =="D" ){
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord+1][wCoord]);
            this->hCoord++;
            return "D";
    }
    if(where =="R" ){
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord][wCoord+1]);
            this->wCoord++;
            return "R";
    }
    return "ERROR";
}

void Board::printSize(matrix matrix) {
    for(int i=0; i<=3;i++){
        for(int j=0; j<=3;j++){
            std::cout<<matrix[i][j] <<"    ";
        }
        std::cout<<"\n";
    }
}

Board::~Board() {

}

int Board::getHCoord() const {
    return hCoord;
}

int Board::getWCoord() const {
    return wCoord;
};
void Board::setCoordinates() {
    for(int i=0;i<=3;i++){
        for (int j=0;j<=3;j++){
            if(this->boardSize[i][j]==0) {
                this->wCoord = j;
                this->hCoord = i;
    }
    }
    }
}
const std::vector<std::string> Board::getNeightbours(){

    int x=0;
    int y=0;
    bool U = true;
    bool D = true;
    bool L = true;
    bool R = true;
    std::vector<std::string> possibleMoves;
    for (int i=0; i<=3;i++){
        y=this->hCoord;
        x=this->wCoord;
        if (y > 0) {
            if(U)
                possibleMoves.push_back("U");
            U=false;
        }
        if (y < 3) {
            if(D)
                possibleMoves.push_back("D");
            D=false;
        }
        if (x > 0) {
            if(L)
                possibleMoves.push_back("L");
            L=false;
        }
        if (x < 3) {
            if(R)
                possibleMoves.push_back("R");
            R=false;
        }
    }
    return possibleMoves;

    /*
    std::vector<std::pair<int,int>> posMoves;
        if(hCoord>0)
            posMoves.emplace_back(hCoord-1, wCoord);
        if(hCoord<3)
            posMoves.emplace_back(hCoord+1, wCoord);
        if(wCoord>0)
            posMoves.emplace_back(hCoord, wCoord-1);
        if (wCoord<3)
            posMoves.emplace_back(hCoord,wCoord+1);
    return posMoves;
*/
}

const matrix &Board::getBoardSize() const {
    return boardSize;
}

void Board::setBoardSize(const matrix &boardSize) {
    Board::boardSize = boardSize;
}
