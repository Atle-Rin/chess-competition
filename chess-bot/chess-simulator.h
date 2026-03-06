#pragma once
#include <string>
#include <vector>
#include <utility>

class chessMover;

namespace ChessSimulator {
/**
 * @brief Move a piece on the board
 *
 * @param fen The board as FEN
 * @return std::string The move as UCI
 */
    std::string Move(std::string fen,  int timeLimitMs = 10000);
    std::vector<std::string> orderedMovesByMaterialGain(std::vector<std::string> &moves, int depth = 0);
    int getMoveCaptureValue(std::string move, bool tryingEnemy = false);
    int getMoveCaptureValue(std::pair<int, int> move, bool tryingEnemy = false);
    std::pair<int, int> findLocFromMove(std::string move, bool findTarget = false);
    int getMoveAttackValue(std::string move, bool tryingEnemy = false);
    int tryMoveSeeEnemyAnswer(std::string move, int depth);
    void tryMove(std::string move);
} // namespace ChessSimulator

enum pieceType {
    NullSpace = -2,
    Empty = -1,
    wKing = 0,
    wQueen,
    wRook,
    wBishop,
    wKnight,
    wPawn,
    bKing = 6,
    bQueen,
    bRook,
    bBishop,
    bKnight,
    bPawn,
};

class Piece {
public:

    explicit Piece(std::pair<int, int> posIn);
    ~Piece();

    std::pair<int, int> getPosition() { return positionLN; }
    void setPosition(int x, int y) { positionLN = std::make_pair(x, y); }
    pieceType getType() { return type; }
    void setType(pieceType inType) { type = inType; }

    virtual std::vector<std::pair<int, int>> GetValidMoves() = 0;

private:
    std::pair<int, int> positionLN;
    pieceType type;
};

class King : public Piece {
public:

    explicit King(const std::pair<int, int> &posIn, bool inWhite = true);
    ~King();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
    bool hasMoved = false;
};

class Queen : public Piece {
public:

    explicit Queen(const std::pair<int, int> &posIn, bool inWhite = true);
    ~Queen();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
};

class Rook : public Piece {
public:

    explicit Rook(const std::pair<int, int> &posIn, bool inWhite = true);
    ~Rook();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
};

class Bishop : public Piece {
public:

    explicit Bishop(const std::pair<int, int> &posIn, bool inWhite = true);
    ~Bishop();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
};

class Knight : public Piece {
public:

    explicit Knight(const std::pair<int, int> &posIn, bool inWhite = true);
    ~Knight();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
};

class Pawn : public Piece {
public:

    explicit Pawn(const std::pair<int, int> &posIn, bool inWhite = true);
    ~Pawn();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
    bool hasMoved = false;
    bool isWhite;
};

struct boardState {
    pieceType theBoard[8][8];
};

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
    std::vector<Piece *> &getPiecesStorage() { return pieces; }
    void setPiecesStorage(std::vector<Piece*> &inPieces) { pieces = inPieces; }
    std::string &getCastlesString() { return castleMoves; }
    void setCastlesString(std::string &inCastleString) { castleMoves = inCastleString; }
    std::string &getPassantsString() { return enPassantMoves; }
    void setPassantsString(std::string &inPassantsString) { enPassantMoves = inPassantsString; }
    int getHalfMoveNum() { return halfMoveNum; }
    void setHalfMoveNum(int inHalfMoves) { halfMoveNum = inHalfMoves; }
    int getTurnCount() { return turnCount; }
    void setTurnCount(int inTurnCount) { turnCount = inTurnCount; }

    void createBoard(std::string boardFEN);
    void copyBoard(boardState &copy);

    boardState &getBoard() { return board;}
    void findAllPieces();
    std::vector<std::string> getAllValidMoves();

    pieceType getBoardPos(std::pair<int, int> checkPos);
    void setBoardPos(std::pair<int, int> checkPos, pieceType newVal);
    std::vector<std::pair<int, int>> getCastles();
    std::vector<std::pair<int, int>> getPassants();
    std::vector<std::pair<int, int>> getPassantTargets();
    Piece* getPieceAtLocation(std::pair<int, int> checkPos);

private:
    boardState board;
    bool isWhite;
    std::vector<Piece*> pieces;
    std::string castleMoves;
    std::string enPassantMoves;
    int halfMoveNum;
    int turnCount;
};

