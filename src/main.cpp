
#include <boost/filesystem.hpp>
#include <iostream>

int main ()
{

    boost::filesystem::directory_iterator itr_end;
    //= boost::filesystem::directory_iterator();
    boost::filesystem::path basicPath("/");
    for (boost::filesystem::directory_iterator itr(basicPath); itr != itr_end; itr++)
        std::cout << itr->path().string() << std::endl;


    return 0;
}