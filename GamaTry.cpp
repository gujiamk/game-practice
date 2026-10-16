#include <iostream>
#include <chrono>
#include <string>
#include <filesystem>
#include "Game.h"

namespace fs = std::filesystem;

class TimePointer
{
public:
    TimePointer()
    {
        time = std::chrono::high_resolution_clock::now();
    }

    std::chrono::high_resolution_clock::time_point time;

    ~TimePointer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Time-end: " << std::chrono::duration_cast<std::chrono::microseconds>(end - time).count() << " mic" << std::endl;
    }

};

void writer()
{
    std::ofstream ofs(Chara_info,std::ios::out|std::ios::trunc);
    if (!ofs.is_open())
    {
        std::cout << "Error: can't open file" << std::endl;
        return;
    }

    ofs << "穗穗 12 10 100 10 2\n";
    ofs.close();
    std::cout << "Info-write success" << std::endl;
    return;

}

int main()
{

    Game* gametry = getGame();
    gametry->run();

    return 0;
}