#include "move_interpreter.hpp"


MoveInterpreter::MoveInterpreter() { }

std::string MoveInterpreter::detectMove(std::string path) {
    std::stringstream ss;

    auto [board_id, move_type] = parseMove(ss, std::move(path));

    if(move_type == "entangle") {
        return detectedEntangle(ss, board_id);
    }
    if(move_type == "restart") {
        return detectedRestart(ss, board_id);
    }
    if(move_type == "colapse") {
        return detectedColapse(ss, board_id);
    }
    return noMatch();
}


std::pair<int, std::string> MoveInterpreter::parseMove(std::stringstream& ss, std::string path) {
    std::replace(path.begin(), path.end(), '/', ' ');
    ss << path;
    std::string move_type;
    int board_id; //NOLINT TODO
    ss >> board_id >> move_type;
    return {board_id, move_type};
}

std::string MoveInterpreter::detectedEntangle(std::stringstream& ss, int board_id) {
    int v1, v2; //NOLINT
    ss >> v1 >> v2;
    auto json = boards.at(board_id).moveEntangle(v1, v2);
    return json.dump();
}

std::string MoveInterpreter::detectedRestart(std::stringstream& ss, int board_id) {
    board_id = board_id == 0 ? boards.generateNewBoardId() : board_id;

    int board_size; //NOLINT
    ss >> board_size;

    // this->board = QuantumTicTacToe(board_size);
    boards[board_id] = QuantumTicTacToe(board_size);

    nlohmann::json json;
    json["board_id"] = board_id;

    std::cout << boards.size() << '\n';
    return json.dump();
}

std::string MoveInterpreter::detectedColapse(std::stringstream& ss, int board_id) {
    int idx, nr; //NOLINT
    char player; //NOLINT
    ss >> idx >> player >> nr;
    std::cout << idx << "{" << player << ", " << nr << "}\n";
    // auto json = this->board.moveColapse(idx, {player, nr});
    auto json = boards.at(board_id).moveColapse(idx, Tic(Player(player), nr));

    return json;
}

std::string MoveInterpreter::noMatch() {
    nlohmann::json j;
    j["nothing"] = "nothing";
    return j.dump();
}
