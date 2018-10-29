//
// Created by root on 19.10.18.
//


/*
 * ADRIAN DLUGOSZ 211949
 * WOJCIECH JEZOWSKI 211954
 */
#ifndef FIFTEENGAME_BOARD_H
#define FIFTEENGAME_BOARD_H

#include <iostream>
#include <vector>

typedef    std::vector<std::vector<unsigned short>> matrix;

class Board{
private:
    /*So i tought we will be moving based on coordinates of our blank which is 0
     *If we want to move up our hCoord will get ++ etc, that's the idea
     */
    unsigned short hCoord;
    unsigned short wCoord;
    matrix boardSize;
public:
    void setBoardSize(const matrix& boardSize);
public:
    Board(const matrix& tab);
    /*Board( Board &RHS){
        RHS.wCoord=this->wCoord;
        RHS.hCoord=this->hCoord;
        RHS.boardSize=this->boardSize;

    }*/
    void printSize(matrix& matrix);
    void setCoordinates();
    const unsigned short takeAction(const unsigned short where);

    const std::vector<unsigned short> getPossibleMoves() const;

    const matrix& getBoard() const;

    virtual ~Board();
};

#endif //FIFTEENGAME_BOARD_H
