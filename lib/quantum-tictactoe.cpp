#include "quantum-tictactoe.hpp"


QuantumTicTacToe::QuantumTicTacToe(int siz) :
    size(siz), move_count(1), player(Player::X_PLAYER), result(Result::pending), graph(size * size) { }

QuantumTicTacToe::QuantumTicTacToe(int siz, const std::vector<Tic>& start_fields) :
    size(siz), move_count(1), player(Player::X_PLAYER), graph(size * size) {
    for(size_t i = 0; i < start_fields.size(); ++i) {
        this->graph[i] = start_fields[i];
    }
    this->result = this->checkResult();
}

char QuantumTicTacToe::getPlayerChar() const { return static_cast<std::underlying_type_t<Player>>(this->player); }

const VertexTTT& QuantumTicTacToe::operator[](const VertexDesc& v_desc) const {
    return this->graph[v_desc];
}

const VertexTTT& QuantumTicTacToe::operator[](const PointIndex& idx) const {
    return (*this)[this->idx1d(idx)];
}

nlohmann::json QuantumTicTacToe::moveEntangle(const PointIndex& field_one, const PointIndex& field_two) {
    return moveEntangle(this->idx1d(field_one), this->idx1d(field_two));
}

nlohmann::json QuantumTicTacToe::moveEntangle(int idx_1, int idx_2) {
    if(this->result != Result::pending)
        throw GameFinishedException();
    if(this->cycle.size() > 0)
        throw IllegalMoveException();
    if(idx_1 == idx_2)
        throw IllegalMoveException();
    if(!((*this)[idx_1].isEmpty() && (*this)[idx_2].isEmpty()))
        throw IllegalMoveException();

    this->cycle = find_connection(this->graph, idx_1, idx_2);

    auto edge = boost::add_edge(idx_1, idx_2, this->graph).first;
    this->graph[edge] = this->nextEdge();

    nlohmann::json json;
    if(this->cycle.size() > 0) {
        this->cycle.push_back(edge);
        json["move_type"] = "colapse";

        for(auto& node : this->cycle) {
            boost::target(node, this->graph);
        }
        this->cycleToJson(json);
    } else {
        json["move_type"] = "entangle";
    }

    json["player"] = std::string(1, this->getPlayerChar());
    json["tic"] = this->graph[edge].str();

    return json;
}

void QuantumTicTacToe::cycleToJson(nlohmann::json& json) {
    std::unordered_map<int, std::pair<std::string, std::string>> map;
    for(auto e : this->cycle) {
        auto s = boost::source(e, this->graph);
        auto t = boost::target(e, this->graph);
        auto tic = this->graph[e].str();
        if(map[s].first.size() > 0)
            map[s].second = tic;
        else
            map[s].first = tic;
        if(map[t].first.size() > 0)
            map[t].second = tic;
        else
            map[t].first = tic;
    }
    for(auto [idx, tics] : map) {
        json["cycle"][std::to_string(idx)] = tics;
    }
}

nlohmann::json QuantumTicTacToe::moveColapse(const PointIndex& field, const EdgeTTT& edge) {
    return moveColapse(this->idx1d(field), edge);
}

nlohmann::json QuantumTicTacToe::moveColapse(const VertexDesc& v_desc, const EdgeTTT& edge) {
    if(this->result != Result::pending)
        throw GameFinishedException();

    // find edge connected to field with data equal to given edge
    auto e_iter = std::find_if(this->cycle.begin(), this->cycle.end(), [&](auto e) {
        auto source = boost::source(e, this->graph);
        auto target = boost::target(e, this->graph);
        return (v_desc == source || v_desc == target) && this->graph[e] == edge;
    });

    if(e_iter == this->cycle.end())
        throw IllegalMoveException();

    nlohmann::json json;

    auto e = *e_iter;
    this->graph[v_desc].set(this->graph[e]);
    json["colapse"][std::to_string(v_desc)] = {this->graph[e].str()};

    boost::remove_edge(e, this->graph);

    ColapseVisitor::ColapseList to_colapse;

    ColapseVisitor vis(to_colapse);
    boost::breadth_first_search(this->graph, v_desc, visitor(vis));


    for(auto [v, new_value] : to_colapse) {
        this->graph[v].set(new_value);
        boost::clear_vertex(v, this->graph);
        json["colapse"][std::to_string(v)] = {new_value.str()};
    }

    this->cycle.clear();

    this->result = this->checkResult();

    json["result"] = this->getResultStr();

    json["player"] = std::string(1, this->getPlayerChar());
    json["move_type"] = "entangle";

    return json.dump();
}

QuantumTicTacToe::Result QuantumTicTacToe::getResult() const {
    return this->result;
}

std::string QuantumTicTacToe::getResultStr() {
    switch(this->result) {
    case Result::pending: return "pending";
    case Result::draw: return "draw";
    case Result::x_won: return "x won";
    case Result::o_won: return "o won";
    default: return "";
    }
}


QuantumTicTacToe::Result QuantumTicTacToe::checkResult() const {
    std::vector<Tic> winning_tics;
    int empty_count = this->checkResultRowsAndCols(winning_tics);
    this->checkResultDiagonals(winning_tics);

    auto e = std::min_element(winning_tics.begin(), winning_tics.end());

    if(e == winning_tics.end()) {
        if(empty_count < 2) {
            return Result::draw; // 1 or less empty field and nobody has won => draw
        }
        return Result::pending;
    }

    auto winner_tic = *e;

    e = std::find_if(winning_tics.begin(), winning_tics.end(), [&](Tic tic) {
        return (tic.getPlayer() != winner_tic.getPlayer()) && (tic.getNumber() == winner_tic.getNumber());
    });

    if(e != winning_tics.end()) {
        return Result::draw;
    }

    return winner_tic.getPlayer() == Player::X_PLAYER ? Result::x_won : Result::o_won;
}

int QuantumTicTacToe::checkResultRowsAndCols(std::vector<Tic>& winning_tics) const {
    int empty_count = 0;
    for(int i = 0; i < this->size; ++i) {
        WinChecker<Tic> row_checker(this->size), col_checker(this->size);
        for(int j = 0; j < this->size; ++j) {
            auto col_mark = (*this)[{i, j}];
            auto row_mark = (*this)[{j, i}];
            row_checker.check(row_mark);
            col_checker.check(col_mark);
            if(row_mark.isEmpty())
                empty_count++;
        }
        if(col_checker.winnerFound())
            winning_tics.push_back(col_checker.getWinner());
        if(row_checker.winnerFound())
            winning_tics.push_back(row_checker.getWinner());
    }
    return empty_count;
}

void QuantumTicTacToe::checkResultDiagonals(std::vector<Tic>& winning_tics) const {
    WinChecker<Tic> up_checker(this->size), down_checker(this->size);
    for(int i = 0; i < this->size; ++i) {
        auto up_mark = (*this)[{i, this->size - 1 - i}];
        auto down_mark = (*this)[{i, i}];
        up_checker.check(up_mark);
        down_checker.check(down_mark);
    }
    if(up_checker.winnerFound())
        winning_tics.push_back(up_checker.getWinner());
    if(down_checker.winnerFound())
        winning_tics.push_back(down_checker.getWinner());
}

QuantumTicTacToe::VertexDesc QuantumTicTacToe::idx1d(const PointIndex& idx) const {
    return idx.first + this->size * idx.second;
}

EdgeTTT QuantumTicTacToe::nextEdge() {
    EdgeTTT edge {this->player, this->move_count};
    this->updatePlayer();
    return edge;
}

void QuantumTicTacToe::updatePlayer() {
    if(this->player == Player::O_PLAYER) {
        this->player = Player::X_PLAYER;
        this->move_count++;
    } else {
        this->player = Player::O_PLAYER;
    }
}
