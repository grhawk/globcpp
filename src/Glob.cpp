//
// Created by Petraglia Riccardo, INI-CLD-TCL on 25.11.20.
//

#include "Glob.h"
#include <array>
#include <iostream>

typedef unsigned int guint;

std::vector<Path>* Glob::glob(const std::string& glob) {
    auto result = new std::vector<Path>();

    std::array<guint, 3> globsPositions = std::array<guint, 3>();
    globsPositions[0] = glob.find('*');
    globsPositions[1] = glob.find("**", 0, 2);
    globsPositions[2] = glob.find('?');

    guint nextGlobPosition = *(std::min_element(globsPositions.cbegin(), globsPositions.cend()));
    Path basicPath = Path(glob.substr(0, nextGlobPosition));

//    boost::filesystem::directory_iterator itr_begin(basicPath);
//    boost::filesystem::directory_iterator itr_end;
//
//    for (boost::filesystem::directory_iterator itr(basicPath); itr != itr_end; itr++)
//        std::cout << itr->path().string() << std::endl;


    return result;
}
