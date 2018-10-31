//
// Created by root on 19.10.18.
//


/*
 * ADRIAN DLUGOSZ 211949
 * WOJCIECH JEZOWSKI NIE ZNAM TWOJEGO INDEKSU XD
 */
#ifndef FIFTEENGAME_BOARD_H
#define FIFTEENGAME_BOARD_H

#include <iostream>
#include <vector>

typedef    std::vector<std::vector<int> > matrix;

class Board{
private:
    int wCoord;
    matrix boardSize;
    int hCoord;
public:
    void setBoardSize(const matrix &boardSize);
    Board(const matrix &tab);
    void printSize(matrix matrix);
    void setCoordinates();
    const std::string takeAction(const std::string &where) ;
    int getWCoord() const;
    int getHCoord() const;
    const int findCoordinatesofValue(const int &value);
    const std::vector<std::string>  getPossibleMoves();
    const matrix &getBoard() const;
    virtual ~Board();

};

#endif //FIFTEENGAME_BOARD_H
