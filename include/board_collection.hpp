#ifndef BOARD_COLLECTION_HPP
#define BOARD_COLLECTION_HPP


#include "quantum-tictactoe.hpp"
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <random>
#include <thread>

/**
 * @brief this class stores multiple quantum tic-tac-toe games and deletes them on timeout.
 * 
 */
class BoardCollection {
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    using Duration = std::chrono::nanoseconds;

public:
    /**
     * @brief Construct a new Board Collection object
     * 
     * @param time_limit timeout for game delete
     */
    BoardCollection(const int time_limit = 5);
    ~BoardCollection();

    /**
     * @brief returns boardgame of given id and updates id time stamp
     * 
     * @param id game id
     * @return QuantumTicTacToe& game state
     */
    QuantumTicTacToe& at(const int id);

    /**
     * @brief returns boardgame of given id and updates id time stamp
     * 
     * @param id game id
     * @return QuantumTicTacToe& game state
     */
    QuantumTicTacToe& operator[](const int id);

    /**
     * @brief generetes unique game id 
     * 
     * @return int unique game id
     */
    int generateNewBoardId();

    /**
     * @brief returns the number of current game boards
     * 
     * @return int the number of current game boards
     */
    int size() const;

private:
    /**
     * @brief thread function which removes boards on timeout every so often
     * 
     */
    void cleaner_thread();


    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> rand_pint;
    const Duration time_limit;
    TimePoint time_point;
    std::unordered_map<int, std::pair<QuantumTicTacToe, TimePoint>> boards;

    std::mutex mutex, finish_mutex;
    std::condition_variable cv;

    volatile bool finish;
    std::thread thread;
};

#endif