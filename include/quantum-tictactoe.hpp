#ifndef QUANTUM_TICTACTOE_HPP
#define QUANTUM_TICTACTOE_HPP


#include <algorithm>
#include <nlohmann/json.hpp>
#include <sstream>
#include <utility>
#include <vector>
#include <stdexcept>

#include "colapse_cycle.hpp"
#include "find_connection.hpp"
#include "win_checker.hpp"
#include "graph_ttt.hpp"

struct IllegalMoveException : public std::runtime_error {
    IllegalMoveException() : std::runtime_error{"Illegal move was tried to be made."} {}
};
struct EdgeNotFoundException : public std::runtime_error {
    EdgeNotFoundException() : std::runtime_error{"Edge for move hasn't been found."} {}
};
struct GameFinishedException : public std::runtime_error { 
    GameFinishedException() : std::runtime_error{"Illegal move was tried to be made."} {}
};

/**
 * @brief This class stores the game state and defines the logic of quantum tic-tac-toe.
 * 
 */
class QuantumTicTacToe {
public:
    using PointIndex = std::pair<int, int>;
    using VertexDesc = boost::graph_traits<GraphTTT>::vertex_descriptor;
    using OutEdgeIter = boost::graph_traits<GraphTTT>::out_edge_iterator;

    enum class Result {
        pending = 0,
        draw = '_',
        x_won = 'x',
        o_won = 'o'
    };

    /**
     * @brief Construct a new Quantum Tic Tac Toe object
     * 
     * @param size board side size
     */
    QuantumTicTacToe(int size = 3);

    /**
     * @brief Construct a new Quantum Tic Tac Toe object
     * 
     * @param size board side size
     * @param start_fields vector of field values
     */
    QuantumTicTacToe(int size, const std::vector<Tic>& start_fields);

    /**
     * @brief Get the Player Char object
     * 
     * @return char 
     */
    char getPlayerChar() const;

    /**
     * @brief returns reference to the vertex given vertex descriptor
     * 
     * @param v_desc vertex descriptor
     * @return const VertexTTT& 
     */
    const VertexTTT& operator[](const VertexDesc& v_desc) const;

    /**
     * @brief returns reference to the vertex given field location
     * 
     * @param idx field location row x col
     * @return const VertexTTT& 
     */
    const VertexTTT& operator[](const PointIndex& idx) const;

    /**
     * @brief perform entangle move given two field locations
     * 
     * @param field_one 
     * @param field_two 
     * @return nlohmann::json state change
     */
    nlohmann::json moveEntangle(const PointIndex& field_one, const PointIndex& field_two);

    /**
     * @brief perform entangle move given two vertex descriptors
     * 
     * @param idx_1 
     * @param idx_2 
     * @return nlohmann::json 
     */
    nlohmann::json moveEntangle(int idx_1, int idx_2);

    /**
     * @brief converts cycle in json format
     * 
     * @param json cycle in json format
     */
    void cycleToJson(nlohmann::json& json);

    /**
     * @brief perform colapse move given field location and edge
     * 
     * @param field field location
     * @param edge edge values
     * @return nlohmann::json state change
     */
    nlohmann::json moveColapse(const PointIndex& field, const EdgeTTT& edge);

    /**
     * @brief perform colapse move given vertex descriptor and edge
     * 
     * @param v_desc vertex descriptor
     * @param edge edge values
     * @return nlohmann::json state change
     */
    nlohmann::json moveColapse(const VertexDesc& v_desc, const EdgeTTT& edge);

    /**
     * @brief Get the Result object
     * 
     * @return Result 
     */
    Result getResult() const;

    /**
     * @brief Get the Result Str object
     * 
     * @return std::string 
     */
    std::string getResultStr();

private:
    Result checkResult() const;

    int checkResultRowsAndCols(std::vector<Tic>& winning_tics) const;

    void checkResultDiagonals(std::vector<Tic>& winning_tics) const;

    VertexDesc idx1d(const PointIndex& idx) const;

    EdgeTTT nextEdge();

    void updatePlayer();

    int size;
    int move_count;
    Player player;
    Result result;
    std::vector<GraphTTT::edge_descriptor> cycle;
    GraphTTT graph;
};

#endif