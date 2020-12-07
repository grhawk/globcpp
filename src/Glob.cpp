//
// Created by Petraglia Riccardo, INI-CLD-TCL on 25.11.20.
//

#include "Glob.h"
#include <iostream>
#include <algorithm>
#include <regex>

using gh::Glob;

std::vector<Path>* Glob::glob(const std::string& glob) {
    auto result = new std::vector<Path>();
    const char folderSeparator = '/';

    // Find the first glob symbol in the glob
    std::map<size_t, std::string> globsPositions;
    globsPositions[glob.find('*')] = "*";
    globsPositions[glob.find("**", 0, 2)] = "**";
    globsPositions[glob.find('?')] = "?";
    size_t nextGlobPosition = globsPositions.cbegin()->first;

    // Find the last folder-separator before the glob symbol
    if (nextGlobPosition > glob.size())
        nextGlobPosition = glob.size();

    /*
     * Possible separator situations:
     *  1) /folder/file_?
     *  2) /folder/*\/
     *  3) ./*\/
     *  4) *
     *  5) file_?
     *  6) /file_?
     *  7) ./file_?
     */

    size_t lastFolderSeparator = glob.find_last_of(folderSeparator, nextGlobPosition);
    size_t firstFolderSeparatorAfterGlobChar = std::min(glob.find(folderSeparator, lastFolderSeparator + 1), glob.size());
    std::string globSymbol;
    if (lastFolderSeparator == firstFolderSeparatorAfterGlobChar)
        globSymbol = "";
    else
        globSymbol = std::string(glob.cbegin() + lastFolderSeparator + 1, glob.cbegin() + firstFolderSeparatorAfterGlobChar);
    for (auto it : mapGlobRegex){
        size_t  last_glob_found = globSymbol.find(it.first);
        while(last_glob_found != std::string::npos){
            globSymbol = globSymbol.substr(0, last_glob_found).insert(last_glob_found, it.second).insert(last_glob_found + it.second.size(), globSymbol.substr(last_glob_found + it.first.size(), std::string::npos));
            last_glob_found = globSymbol.find(it.first);
        }
    }

    std::string regex;
    if (lastFolderSeparator != std::string::npos)
        std::string regex(glob.substr(0, lastFolderSeparator).insert(lastFolderSeparator, globSymbol));
    else
        regex = globSymbol;
    std::regex regexGlob(regex);


    Path basicPath = Path(glob.substr(0, lastFolderSeparator));
    if (!boost::filesystem::exists(basicPath))
        throw FileNotFoundException(basicPath.string());

    boost::filesystem::directory_iterator itr_begin(basicPath);
    boost::filesystem::directory_iterator itr_end;
    for (auto itr = itr_begin; itr != itr_end; itr++) {
        std::string strPath(itr->path().string());
        if(std::regex_match(strPath.cbegin(), strPath.cend(), regexGlob))
            result->push_back(itr->path());
    }

    return result;
}

Glob::Glob() noexcept {
    mapGlobRegex["*"] = "([^\\/]+|)";  // Everything but a directory-change
    mapGlobRegex["**"] = ".*";  // Everything
    mapGlobRegex["?"] = "[^\\/]+"; // Any character but not a directory-change
}

gh::FileNotFoundException::FileNotFoundException(const std::string& msg) : std::runtime_error("File " + msg + " does not exist!"){}

