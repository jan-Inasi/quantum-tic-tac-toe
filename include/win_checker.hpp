#ifndef WIN_CHECKER_HPP
#define WIN_CHECKER_HPP

#include "graph_ttt.hpp"

/**
 * @brief This class helps with checking whether given board line has winning configuration.
 * 
 * @tparam T - game board type
 */
template<typename T>
class WinChecker {
public:
    /**
     * @brief Construct a new Win Checker object
     * 
     * @param board_size the size of checking board
     */
    WinChecker(int board_size);

    /**
     * @brief apply check with given tic
     * 
     * @param mark tic of current field
     */
    void check(const T& mark);

    /**
     * @brief gives information whether the winner has been found
     * 
     * @return true - the winner has been found
     * @return false - the winner has not been found
     */
    bool winnerFound() const;

    /**
     * @brief Get the Winner object
     * 
     * @return T - the tic from the winning row with the highest number
     */
    T getWinner() const;

private:
    T mark_mem;
    int iter;
    bool win_impossible;
};

#endif