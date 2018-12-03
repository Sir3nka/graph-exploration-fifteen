#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "../include/bfs.h"
#include "../include/dfs.h"
#include "../include/hamming.h"
#include "../include/manhattan.h"
#include "../include/filesSaver.h"

matrix parserToMatrix(std::string& arg) {
    std::ifstream infile(arg.c_str());
    if(!infile.fail()) {
        matrix Numbers;
        Numbers.reserve(3);
        std::string String;
        uint_fast16_t a;
        std::vector<uint_fast16_t> Line;

        while (getline(infile, String)) {
            Line.reserve(3);
            //Kinda lazy solution
            if (String.size() > 3) {
                std::stringstream Stream(String);
                while (Stream >> a) {
                    Line.emplace_back(a);
                }
                Numbers.emplace_back(Line);
                std::vector<uint_fast16_t>().swap(Line);
            }
        }
        infile.close();
        return Numbers;
    }
    else std::cout << "FILE DOESNT EXIST!" << std::endl;
    return Goal;
}

int main(int argc, char* argv[]) {
    //Arguments parse
    std::string methodName(argv[1]);

    std::vector<uint_fast16_t> patternOrHeuristic;
    patternOrHeuristic.reserve(3);

    for (unsigned char i(0); i < 4; ++i)
    {
        patternOrHeuristic.push_back(argv[2][i]);
    }

    std::string fileName(argv[3]);
    matrix Testuje(parserToMatrix(fileName));

    auto Test(std::make_shared<Board>(Testuje));
    Test->setCoordinates();

    clock_t tStart;
    unsigned short numbersOfSteps;
    std::string path;
    unsigned short realOpenListSize = 0;
    unsigned short realExploredSize = 0;
    int maxRecursionDepth = 0;
    if(methodName == "bfs") {
        tStart = clock();
        BFS(Test, realOpenListSize, realExploredSize, maxRecursionDepth, numbersOfSteps, path, patternOrHeuristic);
    }
    else if(methodName == "dfs") {
        uint_fast16_t maxRecurionsNumber(20);

        tStart = clock();

        DFS(Test, realOpenListSize, realExploredSize, maxRecursionDepth, numbersOfSteps, path, patternOrHeuristic, maxRecurionsNumber);
    }
    else if(methodName == "astr"){
        if (patternOrHeuristic.at(0) == 'm')
        {
            tStart = clock();
            ASTARmanhattan(Test, realOpenListSize, realExploredSize, maxRecursionDepth, numbersOfSteps, path);
        }
        else
        {
            tStart = clock();
            ASTARhamming(Test, realOpenListSize, realExploredSize, maxRecursionDepth, numbersOfSteps, path);
        }
    }
    double executinTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    //printf("\nTime taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    saveSolutionsToFile(fileName, realOpenListSize, realExploredSize, maxRecursionDepth, numbersOfSteps, path, methodName, patternOrHeuristic, executinTime);

    return 0;
}
