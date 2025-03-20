#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "quantum-tictactoe.hpp"

using res = QuantumTicTacToe::Result;

TEST_CASE("Colapse Cycle 3x3 v1") {
  QuantumTicTacToe board(3);

  board.moveEntangle({0, 0}, {1, 1}); // x1
  board.moveEntangle({0, 0}, {1, 0}); // o1
  board.moveEntangle({2, 0}, {1, 0}); // x2
  board.moveEntangle({1, 1}, {1, 0}); // o2

  board.moveColapse({1, 1}, EdgeTTT{Player::O_PLAYER, 2});

  REQUIRE(board[{0, 0}] == VertexTTT{Player::X_PLAYER, 1});
  REQUIRE(board[{0, 1}].isEmpty());
  REQUIRE(board[{0, 2}].isEmpty());
  REQUIRE(board[{1, 0}] == VertexTTT{Player::O_PLAYER, 1});
  REQUIRE(board[{1, 1}] == VertexTTT{Player::O_PLAYER, 2});
  REQUIRE(board[{1, 2}].isEmpty());
  REQUIRE(board[{2, 0}] == VertexTTT{Player::X_PLAYER, 2});
  REQUIRE(board[{2, 1}].isEmpty());
  REQUIRE(board[{2, 2}].isEmpty());

  REQUIRE_THROWS_AS(board.moveEntangle({1, 0}, {1, 2}), IllegalMoveException);
  REQUIRE_THROWS_AS(board.moveEntangle({2, 2}, {2, 0}), IllegalMoveException);
  REQUIRE_THROWS_AS(board.moveEntangle({1, 0}, {2, 2}), IllegalMoveException);

  board.moveEntangle({0, 1}, {0, 2}); // x3
  board.moveEntangle({0, 2}, {1, 2}); // o3
  board.moveEntangle({0, 1}, {0, 2}); // x4

  board.moveColapse({0, 2}, EdgeTTT{Player::X_PLAYER, 4});

  REQUIRE(board[{0, 0}] == VertexTTT{Player::X_PLAYER, 1});
  REQUIRE(board[{0, 1}] == VertexTTT{Player::X_PLAYER, 3});
  REQUIRE(board[{0, 2}] == VertexTTT{Player::X_PLAYER, 4});
  REQUIRE(board[{1, 0}] == VertexTTT{Player::O_PLAYER, 1});
  REQUIRE(board[{1, 1}] == VertexTTT{Player::O_PLAYER, 2});
  REQUIRE(board[{1, 2}] == VertexTTT{Player::O_PLAYER, 3});
  REQUIRE(board[{2, 0}] == VertexTTT{Player::X_PLAYER, 2});
  REQUIRE(board[{2, 1}].isEmpty());
  REQUIRE(board[{2, 2}].isEmpty());
}

TEST_CASE("Colapse Cycle 3x3 v2") {
  QuantumTicTacToe board(3);

  REQUIRE_THROWS_AS(board.moveEntangle({2, 1}, {2, 1}), IllegalMoveException);

  board.moveEntangle({2, 1}, {1, 2}); // x1
  REQUIRE_THROWS_AS(board.moveColapse({2, 1}, EdgeTTT{Player::O_PLAYER, 2}),
                    IllegalMoveException);
  board.moveEntangle({0, 1}, {0, 2}); // o1
  board.moveEntangle({1, 1}, {2, 1}); // x2
  board.moveEntangle({1, 0}, {2, 1}); // o2
  REQUIRE_THROWS_AS(board.moveColapse({2, 1}, EdgeTTT{Player::O_PLAYER, 2}),
                    IllegalMoveException);
  board.moveEntangle({0, 0}, {2, 0}); // x3
  board.moveEntangle({2, 2}, {2, 0}); // o3
  board.moveEntangle({0, 2}, {1, 2}); // x4
  board.moveEntangle({1, 0}, {0, 1}); // o4

  REQUIRE_THROWS_AS(board.moveEntangle({2, 2}, {2, 1}), IllegalMoveException);

  board.moveColapse({2, 1}, EdgeTTT{Player::O_PLAYER, 2});

  REQUIRE(board[{0, 0}].isEmpty());
  REQUIRE(board[{0, 1}] == VertexTTT{Player::O_PLAYER, 1});
  REQUIRE(board[{0, 2}] == VertexTTT{Player::X_PLAYER, 4});
  REQUIRE(board[{1, 0}] == VertexTTT{Player::O_PLAYER, 4});
  REQUIRE(board[{1, 1}] == VertexTTT{Player::X_PLAYER, 2});
  REQUIRE(board[{1, 2}] == VertexTTT{Player::X_PLAYER, 1});
  REQUIRE(board[{2, 0}].isEmpty());
  REQUIRE(board[{2, 1}] == VertexTTT{Player::O_PLAYER, 2});
  REQUIRE(board[{2, 2}].isEmpty());

  board.moveEntangle({0, 0}, {2, 2}); // x5
  board.moveColapse({2, 0}, EdgeTTT{Player::X_PLAYER, 3});

  REQUIRE(board[{0, 0}] == VertexTTT{Player::X_PLAYER, 5});
  REQUIRE(board[{0, 1}] == VertexTTT{Player::O_PLAYER, 1});
  REQUIRE(board[{0, 2}] == VertexTTT{Player::X_PLAYER, 4});
  REQUIRE(board[{1, 0}] == VertexTTT{Player::O_PLAYER, 4});
  REQUIRE(board[{1, 1}] == VertexTTT{Player::X_PLAYER, 2});
  REQUIRE(board[{1, 2}] == VertexTTT{Player::X_PLAYER, 1});
  REQUIRE(board[{2, 0}] == VertexTTT{Player::X_PLAYER, 3});
  REQUIRE(board[{2, 1}] == VertexTTT{Player::O_PLAYER, 2});
  REQUIRE(board[{2, 2}] == VertexTTT{Player::O_PLAYER, 3});
}

TEST_CASE("Colapse Cycle 3x3 v3") {
  QuantumTicTacToe board(3);

  board.moveEntangle({1, 1}, {2, 1}); // x1
  board.moveEntangle({1, 1}, {0, 1}); // o1
  board.moveEntangle({0, 0}, {2, 0}); // x2
  board.moveEntangle({1, 1}, {0, 0}); // o2
  board.moveEntangle({1, 0}, {0, 0}); // x3
  board.moveEntangle({2, 2}, {1, 0}); // o3
  board.moveEntangle({2, 2}, {1, 2}); // x4
  board.moveEntangle({0, 2}, {1, 2}); // o4
  board.moveEntangle({0, 2}, {2, 0}); // x5

  REQUIRE_THROWS_AS(board.moveColapse({0, 2}, EdgeTTT{Player::X_PLAYER, 4}),
                    IllegalMoveException);

  // not in cycle (vertex and edge)
  REQUIRE_THROWS_AS(board.moveColapse({1, 1}, EdgeTTT{Player::X_PLAYER, 1}),
                    IllegalMoveException);
  // not in cycle (just edge)
  REQUIRE_THROWS_AS(board.moveColapse({0, 0}, EdgeTTT{Player::O_PLAYER, 2}),
                    IllegalMoveException);

  board.moveColapse({0, 2}, EdgeTTT{Player::X_PLAYER, 5});

  REQUIRE(board[{0, 0}] == VertexTTT{Player::X_PLAYER, 3});
  REQUIRE(board[{0, 1}] == VertexTTT{Player::O_PLAYER, 1});
  REQUIRE(board[{0, 2}] == VertexTTT{Player::X_PLAYER, 5});
  REQUIRE(board[{1, 0}] == VertexTTT{Player::O_PLAYER, 3});
  REQUIRE(board[{1, 1}] == VertexTTT{Player::O_PLAYER, 2});
  REQUIRE(board[{1, 2}] == VertexTTT{Player::O_PLAYER, 4});
  REQUIRE(board[{2, 0}] == VertexTTT{Player::X_PLAYER, 2});
  REQUIRE(board[{2, 1}] == VertexTTT{Player::X_PLAYER, 1});
  REQUIRE(board[{2, 2}] == VertexTTT{Player::X_PLAYER, 4});
}

TEST_CASE("Colapse Cycle 2x2 v1") {
  QuantumTicTacToe board(2);

  board.moveEntangle({1, 0}, {0, 1}); // x1
  board.moveEntangle({0, 1}, {1, 0}); // o1
  board.moveColapse({1, 0}, EdgeTTT{Player::O_PLAYER, 1});

  REQUIRE(board[{0, 0}].isEmpty());
  REQUIRE(board[{0, 1}] == VertexTTT{Player::X_PLAYER, 1});
  REQUIRE(board[{1, 0}] == VertexTTT{Player::O_PLAYER, 1});
  REQUIRE(board[{1, 1}].isEmpty());

  board.moveEntangle({0, 0}, {1, 1}); // x2
  board.moveEntangle({0, 0}, {1, 1}); // o2
  board.moveColapse({1, 1}, EdgeTTT{Player::X_PLAYER, 2});

  REQUIRE(board[{0, 0}] == VertexTTT{Player::O_PLAYER, 2});
  REQUIRE(board[{0, 1}] == VertexTTT{Player::X_PLAYER, 1});
  REQUIRE(board[{1, 0}] == VertexTTT{Player::O_PLAYER, 1});
  REQUIRE(board[{1, 1}] == VertexTTT{Player::X_PLAYER, 2});
}

TEST_CASE("Check Result 3x3 v1", "draw double win") {
  std::vector<Tic> init = {{Player::X_PLAYER, 1}, {Player::X_PLAYER, 2}, {Player::X_PLAYER, 3}, {Player::O_PLAYER, 3}, {Player::O_PLAYER, 1},
                           {Player::O_PLAYER, 2}, {Player::X_PLAYER, 4}, {Player::NONE, 0}, {Player::NONE, 0}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::draw);

  REQUIRE_THROWS_AS(board.moveEntangle({1, 2}, {2, 2}), GameFinishedException);
}

TEST_CASE("Check Result 3x3 v2", "win 1 row") {
  std::vector<Tic> init = {{Player::X_PLAYER, 1}, {Player::X_PLAYER, 2}, {Player::X_PLAYER, 3}, {Player::NONE, 0}, {Player::O_PLAYER, 1},
                           {Player::O_PLAYER, 2}, {Player::NONE, 0}, {Player::NONE, 0}, {Player::NONE, 0}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::x_won);
  REQUIRE_THROWS_AS(board.moveEntangle({1, 2}, {2, 2}), GameFinishedException);
}

TEST_CASE("Check Result 3x3 v3", "win 1 col") {
  std::vector<Tic> init = {{Player::X_PLAYER, 1}, {Player::X_PLAYER, 2}, {Player::O_PLAYER, 3}, {Player::NONE, 0}, {Player::O_PLAYER, 1},
                           {Player::O_PLAYER, 2}, {Player::X_PLAYER, 4}, {Player::X_PLAYER, 3}, {Player::O_PLAYER, 4}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::o_won);
  REQUIRE_THROWS_AS(board.moveEntangle({1, 2}, {2, 2}), GameFinishedException);
}

TEST_CASE("Check Result 3x3 v4", "win 2 col") {
  std::vector<Tic> init = {{Player::O_PLAYER, 4}, {Player::X_PLAYER, 2}, {Player::O_PLAYER, 3}, {Player::NONE, 0}, {Player::X_PLAYER, 1},
                           {Player::O_PLAYER, 2}, {Player::X_PLAYER, 3}, {Player::X_PLAYER, 4}, {Player::O_PLAYER, 1}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::o_won);
  REQUIRE_THROWS_AS(board.moveColapse({2, 1}, {Player::O_PLAYER, 3}), GameFinishedException);
}

TEST_CASE("Check Result 3x3 v5", "win diag down") {
  std::vector<Tic> init = {{Player::X_PLAYER, 4}, {Player::O_PLAYER, 1}, {Player::O_PLAYER, 3}, {Player::O_PLAYER, 4}, {Player::X_PLAYER, 2},
                           {Player::O_PLAYER, 2}, {Player::X_PLAYER, 3}, {Player::X_PLAYER, 5}, {Player::X_PLAYER, 1}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::x_won);
  REQUIRE_THROWS_AS(board.moveColapse({2, 1}, {Player::O_PLAYER, 3}), GameFinishedException);
}

TEST_CASE("Check Result 3x3 v6", "pending") {
  std::vector<Tic> init = {{Player::NONE, 0}, {Player::O_PLAYER, 1}, {Player::O_PLAYER, 3}, {Player::NONE, 0}, {Player::X_PLAYER, 2},
                           {Player::O_PLAYER, 2}, {Player::X_PLAYER, 3}, {Player::NONE, 0}, {Player::X_PLAYER, 1}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::pending);
  REQUIRE_NOTHROW(board.moveEntangle({0, 0}, {1, 2}));
}

TEST_CASE("Check Result 3x3 v7", "draw one empty") {
  std::vector<Tic> init = {{Player::O_PLAYER, 4}, {Player::X_PLAYER, 2}, {Player::O_PLAYER, 3}, {Player::X_PLAYER, 4}, {Player::O_PLAYER, 1},
                           {Player::O_PLAYER, 2}, {Player::X_PLAYER, 3}, {Player::NONE, 0}, {Player::X_PLAYER, 1}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::draw);
  REQUIRE_THROWS_AS(board.moveColapse({2, 1}, {Player::O_PLAYER, 3}), GameFinishedException);
}

TEST_CASE("Check Result 3x3 v8", "draw full") {
  std::vector<Tic> init = {{Player::X_PLAYER, 5}, {Player::O_PLAYER, 3}, {Player::X_PLAYER, 2}, {Player::X_PLAYER, 4}, {Player::O_PLAYER, 1},
                           {Player::O_PLAYER, 2}, {Player::O_PLAYER, 4}, {Player::X_PLAYER, 3}, {Player::X_PLAYER, 1}};
  QuantumTicTacToe board(3, init);
  REQUIRE(board.getResult() == res::draw);
  REQUIRE_THROWS_AS(board.moveColapse({2, 1}, {Player::O_PLAYER, 3}), GameFinishedException);
}
