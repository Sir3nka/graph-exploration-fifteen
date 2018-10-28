//
// Created by root on 19.10.18.
//
#include "Board.h"
#include <algorithm>

Board::Board(const matrix& tab): boardSize(tab), hCoord(0), wCoord(0){}


const int Board::takeAction(const int where) {

    if (where == 'U'){
            std::swap(boardSize[hCoord][wCoord], boardSize[hCoord-1][wCoord]);
            --hCoord;
            return 'U';
    }
    else if(where == 'L'){
            std::swap(boardSize[hCoord][wCoord], boardSize[hCoord][wCoord-1]);
            --wCoord;
            return 'L';
    }
    else if(where == 'D'){
            std::swap(boardSize[hCoord][wCoord], boardSize[hCoord+1][wCoord]);
            ++hCoord;
            return 'D';
    }
    else if(where == 'R'){
            std::swap(boardSize[hCoord][wCoord], boardSize[hCoord][wCoord+1]);
            ++wCoord;
            return 'R';
    }
    return 'E';
}

void Board::printSize(matrix& matrix) {
    for(unsigned int i(0); i <= 3; ++i){
        for(unsigned int j(0); j <= 3; ++j){
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
    for(unsigned int i(0); i <= 3; ++i){
        for (unsigned int j(0); j <= 3; ++j){
            if(this->boardSize[i][j] == 0) {
                this->wCoord = j;
                this->hCoord = i;
            }
        }
    }
}
const std::vector<int> Board::getPossibleMoves() const{
    std::vector<int> possibleMoves;
    possibleMoves.reserve(4);


    if (hCoord > 0) {
        possibleMoves.emplace_back('U');
    }
    if (hCoord < 3) {
        possibleMoves.emplace_back('D');
    }
    if (wCoord > 0) {
        possibleMoves.emplace_back('L');
    }
    if (wCoord < 3) {
        possibleMoves.emplace_back('R');
    }

    return possibleMoves;
}

const matrix &Board::getBoard() const {
    return boardSize;
}

void Board::setBoardSize(const matrix &boardSize) {
    Board::boardSize = boardSize;
}
