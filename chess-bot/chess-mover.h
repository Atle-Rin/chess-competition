#pragma once

#include <string>
#include <vector>

#include "chess-piece.h"

struct boardState {
    pieceType theBoard[8][8];
};

class chessMover {
public:

    static void makeInstance();
    static void killInstance();

    chessMover();
    ~chessMover();

    bool getIsWhite() { return isWhite; }
    void setIsWhite(bool inWhite) { isWhite = inWhite; }

    void createBoard(std::string boardFEN);
    void copyBoard(boardState &copy);
    boardState getBoard() { return board;}
    void findAllPieces();
    std::vector<std::string> getAllValidMoves();

    pieceType getBoardPos(std::pair<int, int> checkPos);
    std::vector<std::pair<int, int>> getCastles();
    std::vector<std::pair<int, int>> getPassants();
    std::vector<std::pair<int, int>> getPassantTargets();

private:
    boardState board;
    bool isWhite;
    std::vector<Piece*> pieces;
    std::string castleMoves;
    std::string enPassantMoves;
    int halfMoveNum;
    int turnCount;
};

static inline chessMover* gChessBot = nullptr;