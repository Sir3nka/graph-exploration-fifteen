#include <iostream>
#include "Board.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    matrix Testuje={{1,2,3,4},
                    {5,6,7,0},
                    {8,9,10,11},
                    {12,13,14,15}};
    Board *Test = new Board(Testuje);
    //ptrBoard Test = std::make_shared<Board>(Board())
    Test->printSize();
    Test->setCoordinates();
    //std::cout<<Test->getHCoord()<<"  "<<Test->getWCoord();
    Test->takeAction("r");
    std::cout << " #################################3\n";
    Test->printSize();
    delete Test;
    return 0;
}