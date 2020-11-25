//
// Created by Petraglia Riccardo, INI-CLD-TCL on 25.11.20.
//

#ifndef EXAMPLE1_GLOB_H
#define EXAMPLE1_GLOB_H

#include <string>
#include <boost/filesystem.hpp>

typedef boost::filesystem::path Path;

class Glob {
private:
    const char* m_star = "([^\\/]+|)";  // Everything but a directory-change
    const char* m_sstar = ".*";  // Everything
    const char* m_qmark = "[^\\/]+"; // Any character but not a directory-change

public:
    std::vector<Path>* glob(const std::string& glob);
};

class FileNotFoundException : public std::runtime_error {
public:
    explicit FileNotFoundException(const std::string& msg);
};

#endif //EXAMPLE1_GLOB_H
