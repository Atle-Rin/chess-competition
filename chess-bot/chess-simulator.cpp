#include "chess-simulator.h"
// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
// #include "chess.hpp"
#include <random>
#include <unordered_map>
#include "chess-mover.h"
using namespace ChessSimulator;

std::string ChessSimulator::Move(std::string fen,  int timeLimitMs) {
  // create your board based on the board string following the FEN notation
  // search for the best move using minimax / monte carlo tree search /
  // alpha-beta pruning / ... try to use nice heuristics to speed up the search
  // and have better results return the best move in UCI notation you will gain
  // extra points if you create your own board/move representation instead of
  // using the one provided by the library

  /*
  // here goes a random movement
  chess::Board board(fen);
  chess::Movelist moves;
  chess::movegen::legalmoves(moves, board);
  if(moves.size() == 0)
    return "";

  // get random move
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, moves.size() - 1);
  auto move = moves[dist(gen)];
  return chess::uci::moveToUci(move);*/

  gChessBot->makeInstance();
  gChessBot->createBoard(fen);
  std::vector<std::string> allMoves = gChessBot->getAllValidMoves();
  allMoves = orderedMovesByMaterialGain(allMoves);

  return allMoves[0]; //return the move that gives the greatest taken-material value, don't consider incoming losses yet.
}

std::vector<std::string> ChessSimulator::orderedMovesByMaterialGain(std::vector<std::string> &moves) {
  std::unordered_map<std::string, int> materialValuedMoves;

  for (int i = 0; i < moves.size(); i++) {
    int moveValue = 0;
    if (gChessBot->getIsWhite()) {
      switch (gChessBot->getBoardPos(findLocFromMove(moves[i], true))) {
        case bKing:
          moveValue = 999;
          break;
        case bQueen:
          moveValue = 9;
          break;
        case bRook:
          moveValue = 5;
          break;
        case bBishop:
          moveValue = 3;
          break;
        case bKnight:
          moveValue = 3;
          break;
        case bPawn:
          moveValue = 1;
          break;
        default:
          break;
      }
    }
    else {
      switch (gChessBot->getBoardPos(findLocFromMove(moves[i], true))) {
        case wKing:
          moveValue = 999;
          break;
        case wQueen:
          moveValue = 9;
          break;
        case wRook:
          moveValue = 5;
          break;
        case wBishop:
          moveValue = 3;
          break;
        case wKnight:
          moveValue = 3;
          break;
        case wPawn:
          moveValue = 1;
          break;
        default:
          break;
      }
    }
    materialValuedMoves.insert({moves[i], moveValue});
  }

  std::vector<std::string> orderedMoves;
  for (auto i = materialValuedMoves.begin(); i != materialValuedMoves.end(); ++i) {
    for (auto j = orderedMoves.begin(); j != orderedMoves.end(); ++j) {
      if (i->second >= materialValuedMoves.find(*j)->second) {
        orderedMoves.insert(j, i->first);
        goto added;
      }
    }
    orderedMoves.push_back(i->first);
    added:
  }
  return orderedMoves;
}

std::pair<int, int> ChessSimulator::findLocFromMove(std::string move, bool findTarget) {
  std::pair<int, int> ret;
  int start = 0;
  if (findTarget) start += 2;
  char letter = move[start];
  ret.second = (int)(letter - 97);
  start++;
  ret.first = std::stoi(move.substr(start));
  return ret;
}