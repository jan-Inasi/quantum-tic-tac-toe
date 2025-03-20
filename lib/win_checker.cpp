#include "win_checker.hpp"

template<typename T>
WinChecker<T>::WinChecker(int board_size) :
    iter(board_size), win_impossible(false) { }

template<typename T>
void WinChecker<T>::check(const T& mark) {
    this->iter--;
    if(win_impossible)
        return;
    if(mark.isEmpty()) {
        win_impossible = true;
        return;
    }
    if(mark_mem.isEmpty()) {
        mark_mem = mark;
        return;
    }
    if(mark_mem.getPlayer() != mark.getPlayer()) {
        win_impossible = true;
        return;
    }
    if(mark.getNumber() > mark_mem.getNumber())
        mark_mem = mark;
}

template<typename T>
bool WinChecker<T>::winnerFound() const {
    return this->iter == 0 ? !win_impossible : false;
}

template<typename T>
T WinChecker<T>::getWinner() const {
    return winnerFound() ? mark_mem : T();
}

template class WinChecker<Tic>;