#pragma once
#include <string>
#include <vector>

namespace ChessSimulator {
/**
 * @brief Move a piece on the board
 *
 * @param fen The board as FEN
 * @return std::string The move as UCI
 */
    std::string Move(std::string fen);
    std::vector<std::string> orderedMovesByMaterialGain(std::vector<std::string> &moves);
    std::pair<int, int> findLocFromMove(std::string move, bool findTarget = false);
} // namespace ChessSimulator