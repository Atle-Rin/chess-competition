#pragma once

#include <string>
#include <vector>

#include "chess-piece.h"

struct boardState {
    pieceType theBoard[8][8];
};

class chessMover;

static inline chessMover* gChessBot = nullptr;

class chessMover {
public:

    static void makeInstance() {
        gChessBot = new chessMover();
    }
    static chessMover* getInstance() { return gChessBot; }
    static void killInstance();

    chessMover();
    ~chessMover();

    bool getIsWhite() { return isWhite; }
    void setIsWhite(bool inWhite) { isWhite = inWhite; }
    std::vector<Piece*> getPiecesStorage() { return pieces; }
    void setPiecesStorage(std::vector<Piece*> &inPieces) { pieces = inPieces; }
    std::string getCastlesString() { return castleMoves; }
    void setCastlesString(std::string &inCastleString) { castleMoves = inCastleString; }
    std::string getPassantsString() { return enPassantMoves; }
    void setPassantsString(std::string &inPassantsString) { enPassantMoves = inPassantsString; }
    int getHalfMoveNum() { return halfMoveNum; }
    void setHalfMoveNum(int inHalfMoves) { halfMoveNum = inHalfMoves; }
    int getTurnCount() { return turnCount; }
    void setTurnCount(int inTurnCount) { turnCount = inTurnCount; }

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

