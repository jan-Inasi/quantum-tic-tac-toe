#ifndef GRAPH_TTT_HPP
#define GRAPH_TTT_HPP

#include "player_enum.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <type_traits>

/*!
 * This class contains information about a mark on board.
*/
class Tic {
public:
    /*!
     * Default constructor - creats empty tic.
    */
    Tic();
    /*!
     * Creates nth tic of given player.
    @param player x / o
    @param number move number
    */
    Tic(Player player, int number);
    /**
     * @brief Construct a new Tic object from pair
     * 
     * @param init 
     */
    Tic(const std::pair<Player, int>& init);

    /**
     * @brief 
     * 
     * @return true when field is empty
     * @return false when field is occupied by x or o 
     */
    bool isEmpty() const;

    /**
     * @brief sets tics values
     * 
    @param player x / o
    @param number move number
     */
    void set(Player player, int number);

    /**
     * @brief sets tic values with another tic's values
     * 
     * @param edge other tic
     */
    void set(const Tic& edge);

    /**
     * @brief Get the Player object
     * 
     * @return Player 
     */
    Player getPlayer() const;

    /**
     * @brief Get the Number object
     * 
     * @return int 
     */
    int getNumber() const;

    /**
     * @brief returns string description of a tic
     * 
     * @return std::string
     */
    std::string str() const;

    friend bool operator==(const Tic&, const Tic&);
    friend bool operator<(const Tic&, const Tic&);

private:
    Player player;
    int number;
};

typedef Tic EdgeTTT;
typedef Tic VertexTTT;

using GraphTTT = boost::adjacency_list<boost::vecS, boost::vecS,
    boost::undirectedS, VertexTTT, EdgeTTT>;

#endif