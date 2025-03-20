#include "graph_ttt.hpp"


Tic::Tic() :
    player(Player::NONE), number(0) { }

Tic::Tic(Player player, int number) :
    player(player), number(number) { }

Tic::Tic(const std::pair<Player, int>& init) :
    player(init.first), number(init.second) { }

bool Tic::isEmpty() const { return this->player == Player::NONE; }

void Tic::set(Player player, int number) {
    this->player = player;
    this->number = number;
}

void Tic::set(const Tic& edge) { this->set(edge.player, edge.number); }

Player Tic::getPlayer() const {
    return this->player;
}

int Tic::getNumber() const {
    return this->number;
}

std::string Tic::str() const {
    if(this->isEmpty())
        return " ";
    return std::string(1, static_cast<std::underlying_type_t<Player>>(this->player)) + std::to_string(this->number);
}


bool operator==(const Tic& r, const Tic& l) {
    return (r.player == l.player) && (r.number == l.number);
}

bool operator<(const Tic& r, const Tic& l) { return r.number < l.number; }