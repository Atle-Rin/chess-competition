#pragma once

#include <utility>
#include <vector>
#include <string>

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

    explicit King(const std::pair<int, int> &posIn);
    ~King();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
    bool hasMoved = false;
};

class Queen : public Piece {
public:

    explicit Queen(const std::pair<int, int> &posIn);
    ~Queen();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
};

class Rook : public Piece {
public:

    explicit Rook(const std::pair<int, int> &posIn);
    ~Rook();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
};

class Bishop : public Piece {
public:

    explicit Bishop(const std::pair<int, int> &posIn);
    ~Bishop();

    std::vector<std::pair<int, int>> GetValidMoves() override;

private:
};

class Knight : public Piece {
public:

    explicit Knight(const std::pair<int, int> &posIn);
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