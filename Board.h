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
public:
    void setBoardSize(const matrix &boardSize);

private:
    int wCoord;
    matrix boardSize;
public:
    Board(const matrix &tab);
    /*Board( Board &RHS){
        RHS.wCoord=this->wCoord;
        RHS.hCoord=this->hCoord;
        RHS.boardSize=this->boardSize;

    }*/
    void printSize(matrix matrix);
    void setCoordinates();
    const std::string takeAction(const std::string &where) ;

    int getWCoord() const;

    int getHCoord() const;
    const std::vector<std::string>  getPossibleMoves();

    const matrix &getBoard() const;
    inline std::pair<int, int> getX(int &val){
        std::pair<int,int> coords;
        for(int i=0; i<=3; i++) {
            for (int j = 0; j <= 3; j++) {
                if (val == this->boardSize[i][j]) {
                    coords.first=i;
                    coords.second=j;
                    return coords;
                }
            }
        }
    }

    virtual ~Board();
};

#endif //FIFTEENGAME_BOARD_H
