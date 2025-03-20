#include "board_collection.hpp"


BoardCollection::BoardCollection(const int time_limit) :
    dev(), rng(dev()), rand_pint(1, std::numeric_limits<int>::max()),
    time_limit(std::chrono::nanoseconds(std::chrono::minutes(time_limit))),
    finish(false), thread(&BoardCollection::cleaner_thread, this) { }

BoardCollection::~BoardCollection() {
    this->finish = true;
    this->cv.notify_all();
    this->thread.join();
}

QuantumTicTacToe& BoardCollection::at(const int id) {
    std::lock_guard<std::mutex> guard {this->mutex};
    auto& [board, time_stamp] = boards.at(id);
    time_stamp = std::chrono::system_clock::now();
    // auto dif = std::chrono::system_clock::now() - time_stamp;
    // std::cout << "b" << dif.count() << " " << time_limit.count() << " " << (time_limit > dif) << "\n";
    return board;
}

QuantumTicTacToe& BoardCollection::operator[](const int id) {
    std::lock_guard<std::mutex> guard {this->mutex};
    auto& [board, time_stamp] = boards[id];
    time_stamp = std::chrono::system_clock::now();
    return board;
}

int BoardCollection::generateNewBoardId() {
    int board_id; //NOLINT
    while(boards.count(board_id = rand_pint(rng)))
        ;
    return board_id;
}

int BoardCollection::size() const {
    return boards.size();
}

void BoardCollection::cleaner_thread() {
    std::unique_lock<std::mutex> lk {finish_mutex};
    while(!this->cv.wait_for(lk, this->time_limit, [&] { return this->finish; })) {
        std::lock_guard<std::mutex> guard {this->mutex};
        auto iter = this->boards.begin();
        auto now = std::chrono::system_clock::now();
        std::cout << "clean\n";
        while(iter != this->boards.end()) {
            if((now - iter->second.second) > this->time_limit) {
                std::cout << "removed board: " << iter->first << "\n";
                iter = this->boards.erase(iter);
            } else
                iter++;
        }
        std::cout << "end clean\n";
    }
}
