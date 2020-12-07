//
// Created by Petraglia Riccardo, INI-CLD-TCL on 25.11.20.
//

#include "Glob.h"
#include <iostream>
#include <algorithm>
#include <regex>
#include <set>

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

    Path searchedPathFolder;
    Path searchedPathRegex;
    for (const Path& pathFolderIterator : Path(glob)) {
        Path next = pathFolderIterator;
        bool containGlob = false;
        for (const auto& it : mapGlobRegex) {
            size_t last_glob_found = pathFolderIterator.string().find(it.first);
            while (last_glob_found != std::string::npos) {
                containGlob = true;
                next = Path(pathFolderIterator.string()
                                    .substr(0, last_glob_found)
                                    .insert(last_glob_found, it.second)
                                    .insert(
                                            last_glob_found + it.second.size(),
                                            pathFolderIterator.string()
                                                    .substr(last_glob_found + it.first.size(),
                                                            std::string::npos)));
                last_glob_found = pathFolderIterator.string().find(it.first, last_glob_found + it.second.size());
            }
        }
        searchedPathRegex /= next;
        if (!containGlob)
            searchedPathFolder /= next;

        if (!boost::filesystem::exists(searchedPathFolder))
            throw FileNotFoundException(searchedPathFolder.string());

        std::cout << "Searched Path Regex -> " << searchedPathRegex.string() << std::endl;
        std::cout << "Searched Path Folder -> " << searchedPathFolder.string() << std:: endl;

        boost::filesystem::directory_iterator itr_begin(searchedPathFolder);
        boost::filesystem::directory_iterator itr_end;
        for (auto itr = itr_begin; itr != itr_end; itr++) {
            std::string strPath(itr->path().string());
            if (std::regex_match(strPath.cbegin(), strPath.cend(), std::regex(searchedPathRegex.string())))
                result->push_back(itr->path());
        }
    }

    return result;
}

Glob::Glob() noexcept {
    mapGlobRegex["*"] = "([^\\/]+|)";  // Everything but a directory-change
    mapGlobRegex["**"] = ".*";  // Everything
    mapGlobRegex["?"] = "[^\\/]"; // Any character but not a directory-change
}

gh::FileNotFoundException::FileNotFoundException(const std::string& msg) : std::runtime_error("File " + msg + " does not exist!"){}

