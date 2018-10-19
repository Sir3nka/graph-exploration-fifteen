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
    /*So i tought we will be moving based on coordinates of our blank which is 0
     *If we want to move up our hCoord will get ++ etc, that's the idea
     */
    int hCoord;
    int wCoord;
    matrix boardSize;
public:
    Board(matrix tab);
    void printSize();
    void setCoordinates();
    std::string takeAction(std::string where);

    int getWCoord() const;

    int getHCoord() const;

    virtual ~Board();
};

#endif //FIFTEENGAME_BOARD_H
