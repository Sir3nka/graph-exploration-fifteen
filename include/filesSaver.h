//
// Created by Dirkuu on 01.11.2018.
//

#ifndef FIFTEENGAME_FILESSAVER_H
#define FIFTEENGAME_FILESSAVER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

void saveSolutionsToFile (std::string& originalFileName, unsigned short& realOpenListSize, unsigned short& realExploredSize, int& maxRecursionDepth, unsigned short numbersOfSteps, std::string& path, std::string method, std::vector<uint_fast16_t> patternOrHeuristic, double time) {
    //std::cout << originalFileName << std::endl;
    //std::cout << method << std::endl;
    //std::cout << (char)patternOrHeuristic[0] << std::endl;
    //std::cout << numbersOfSteps << std::endl;
    //std::cout << path << std::endl;

    std::string solutionFileName = originalFileName;

    solutionFileName.erase(solutionFileName.find(".txt"), 4);
    solutionFileName.append("_")
                    .append(method)
                    .append("_");

    if ((char)(patternOrHeuristic[0]) != 'm' && (char)(patternOrHeuristic[0]) != 'h') {
        solutionFileName += (char) (patternOrHeuristic[0] + 32);
        solutionFileName += (char) (patternOrHeuristic[1] + 32);
        solutionFileName += (char) (patternOrHeuristic[2] + 32);
        solutionFileName += (char) (patternOrHeuristic[3] + 32);
    }
    else {
        solutionFileName += (char) patternOrHeuristic[0];
        solutionFileName += (char) patternOrHeuristic[1];
        solutionFileName += (char) patternOrHeuristic[2];
        solutionFileName += (char) patternOrHeuristic[3];
    }
    std::string statsFileName = solutionFileName;
    statsFileName.append("_stats.txt");

    solutionFileName.append("_sol.txt");


    //std::cout << solutionFileName <<std::endl;
    std::ofstream solutionFile;
    solutionFile.open(solutionFileName);

    std::ofstream statsFile;
    statsFile.open(statsFileName);

    if (numbersOfSteps != 65535) {
        solutionFile << numbersOfSteps << '\n' << path;
        statsFile << numbersOfSteps << '\n';
    }
    else {
        solutionFile << "-1";
        statsFile << "-1\n";
    }

    //2 line
    statsFile << realExploredSize << '\n';

    //3 line
    statsFile << realExploredSize + realOpenListSize << '\n';

    //4 line
    statsFile << maxRecursionDepth << '\n';

    //5 line
    statsFile << time << '\n';

    solutionFile.close();
    statsFile.close();




}

#endif //FIFTEENGAME_FILESSAVER_H
