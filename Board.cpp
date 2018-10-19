//
// Created by root on 19.10.18.
//
#include "Board.h"
#include <algorithm>

Board::Board(matrix tab){
    this->boardSize=tab;
    this->hCoord=0;
    this->wCoord=0;
    for(int i=0;i<=3; i++){
        for (int j;j<=3;j++){
            //Assigning values from argument to our board that we will be working on
            boardSize[i][j]=tab[i][j];
            }
        }
    }


std::string Board::takeAction(std::string where) {
    if (where == "U" || where == "u"){
        if(this->hCoord>0) {
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord-1][wCoord]);
            this->hCoord--;
            return "U";
        }
    }
    if(where == "L" || where == "l"){
        if(this->wCoord>0){
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord][wCoord-1]);
            this->wCoord--;
            return "L";
        }
    }
    if(where =="D" || where == "d"){
        if(this->hCoord<3){
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord+1][wCoord]);
            this->hCoord++;
            return "D";
        }
    }
    if(where == "R" || where == "r"){
        if(this->wCoord<3){
            std::swap(boardSize[hCoord][wCoord],boardSize[hCoord][wCoord+1]);
            this->wCoord++;
            return "R";
        }
    }
    return "Nothing happend!";
}

void Board::printSize() {
    for(int i=0; i<=3;i++){
        for(int j=0; j<=3;j++){
            std::cout<<boardSize[i][j] <<"    ";
            if(boardSize[i][j]==0) {
                this->wCoord = j;
                this->hCoord = i;
            }
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