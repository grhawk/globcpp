//
// Created by Petraglia Riccardo, INI-CLD-TCL on 25.11.20.
//

#ifndef EXAMPLE1_GLOB_H
#define EXAMPLE1_GLOB_H

#include <string>
#include <boost/filesystem.hpp>
#include <unordered_map>

typedef boost::filesystem::path Path;

namespace gh {
    class Glob {
    private:
        std::unordered_map<std::string, std::string> mapGlobRegex;
        typedef std::pair<const std::string, std::string> mapGlobRegexItem;

    public:
        Glob() noexcept;

        std::vector<Path>* glob(const std::string& glob);
    };

    class FileNotFoundException : public std::runtime_error {
    public:
        explicit FileNotFoundException(const std::string& msg);
    };
}

#endif //EXAMPLE1_GLOB_H
