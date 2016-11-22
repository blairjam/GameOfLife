#include "CellBoard.hpp"
#include "Game.hpp"
#include "Timer.hpp"

#include <iostream>

#define BOARD_1 100
#define BOARD_5 500
#define BOARD_10 1000
#define BOARD_20 2000

#define DEF_ITS 1000

void run_100();
void run_500();
void run_1000();
void run_2000();

int main()
{
    run_100();
    run_500();
    run_1000();
    run_2000();

    system("pause");

    return 0;
}

void run_100()
{
    Timer t;
    CellBoard board(BOARD_1);
    Game game(board);

    double serial_t;
    double parallel_t;

    std::cout << "Starting serial run of 100x100 board." << std::endl;
    t.start();
    game.runSerial(DEF_ITS);
    t.stop();

    serial_t = t.get_elapsed_time();
    std::cout << "Serial run finished with a time of " << serial_t << "ms." << std::endl;

    std::cout << "Starting parallel run of 100x100 board." << std::endl;
    t.start();
    game.runParallel(DEF_ITS);
    t.stop();

    parallel_t = t.get_elapsed_time();
    std::cout << "Parallel run finished with a time of " << parallel_t << "ms." << std::endl;

    std::cout << "Speedup for 100x100 board: " << (serial_t / parallel_t) << "\n" << std::endl;
}

void run_500()
{
    Timer t;
    CellBoard board(BOARD_5);
    Game game(board);

    double serial_t;
    double parallel_t;

    std::cout << "Starting serial run of 500x500 board." << std::endl;
    t.start();
    game.runSerial(DEF_ITS);
    t.stop();

    serial_t = t.get_elapsed_time();
    std::cout << "Serial run finished with a time of " << serial_t << "ms." << std::endl;

    std::cout << "Starting parallel run of 500x500 board." << std::endl;
    t.start();
    game.runParallel(DEF_ITS);
    t.stop();

    parallel_t = t.get_elapsed_time();
    std::cout << "Parallel run finished with a time of " << parallel_t << "ms." << std::endl;

    std::cout << "Speedup for 500x500 board: " << (serial_t / parallel_t) << "\n" << std::endl;
}

void run_1000()
{
    Timer t;
    CellBoard board(BOARD_10);
    Game game(board);

    double serial_t;
    double parallel_t;

    std::cout << "Starting serial run of 1000x1000 board." << std::endl;
    t.start();
    game.runSerial(DEF_ITS);
    t.stop();

    serial_t = t.get_elapsed_time();
    std::cout << "Serial run finished with a time of " << serial_t << "ms." << std::endl;

    std::cout << "Starting parallel run of 1000x1000 board." << std::endl;
    t.start();
    game.runParallel(DEF_ITS);
    t.stop();

    parallel_t = t.get_elapsed_time();
    std::cout << "Parallel run finished with a time of " << parallel_t << "ms." << std::endl;

    std::cout << "Speedup for 1000x1000 board: " << (serial_t / parallel_t) << "\n" << std::endl;
}

void run_2000()
{
    Timer t;
    CellBoard board(BOARD_20);
    Game game(board);

    double serial_t;
    double parallel_t;

    std::cout << "Starting serial run of 2000x2000 board." << std::endl;
    t.start();
    game.runSerial(DEF_ITS);
    t.stop();

    serial_t = t.get_elapsed_time();
    std::cout << "Serial run finished with a time of " << serial_t << "ms." << std::endl;

    std::cout << "Starting parallel run of 2000x2000 board." << std::endl;
    t.start();
    game.runParallel(DEF_ITS);
    t.stop();

    parallel_t = t.get_elapsed_time();
    std::cout << "Parallel run finished with a time of " << parallel_t << "ms." << std::endl;

    std::cout << "Speedup for 2000x2000 board: " << (serial_t / parallel_t) << "\n" << std::endl;
}

