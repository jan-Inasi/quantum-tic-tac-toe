#ifndef MOVE_INTERPRETER_HPP
#define MOVE_INTERPRETER_HPP


#include "board_collection.hpp"
#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

/**
 * @brief This class parses http requests and performs appropriate operation on the game state.
 * 
 */
class MoveInterpreter {
public:
    /**
     * @brief Construct a new Move Interpreter object
     * 
     */
    MoveInterpreter();

    /**
     * @brief parses given http path and chooses appropraite operation to run
     * 
     * @param path a path from http request
     * @return std::string game state change in json format
     */
    std::string detectMove(std::string path);

private:
    std::pair<int, std::string> parseMove(std::stringstream& ss, std::string path);

    std::string detectedEntangle(std::stringstream& ss, int board_id);

    std::string detectedRestart(std::stringstream& ss, int board_id);

    std::string detectedColapse(std::stringstream& ss, int board_id);

    std::string noMatch();

    BoardCollection boards;
};

#endif