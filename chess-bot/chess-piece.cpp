#include "chess-piece.h"
#include "chess-mover.h"

Piece::Piece(std::pair<int, int> posIn) {
    positionLN = posIn;
}

King::King(const std::pair<int, int> &posIn) : Piece(posIn) {
    if (gChessBot->getIsWhite()) setType(wKing);
    else setType(bKing);
}

King::~King() = default;

std::vector<std::pair<int, int>> King::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;

    if (gChessBot == nullptr) return retList;

    retList = gChessBot->getCastles();

    std::pair<int, int> checkPosition = getPosition();
    checkPosition.second += 1;
    pieceType checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first += 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first -= 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first -= 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    return retList;
}

Queen::Queen(const std::pair<int, int> &posIn) : Piece(posIn) {
    if (gChessBot->getIsWhite()) setType(wQueen);
    else setType(bQueen);
}

Queen::~Queen() = default;

std::vector<std::pair<int, int>> Queen::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;
    std::vector<std::pair<int, int>> revList;

    std::pair<int, int> checkPos;

    for (int i = 0; i < 8; i++) {
        checkPos.first = i;
        checkPos.second = getPosition().second;
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPos);
        else if (i < getPosition().first) retList.clear();
        else if (i > getPosition().first) goto firstDone;
    }
    firstDone:

    for (int i = 0; i < 8; i++) {
        checkPos.first = getPosition().first;
        checkPos.second = i;
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) revList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) revList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) revList.push_back(checkPos);
        else if (i < getPosition().second) revList.clear();
        else if (i > getPosition().second) goto secondDone;
    }
    secondDone:

    std::vector<std::pair<int, int>> diaRetList;
    std::vector<std::pair<int, int>> diaRevList;

    int vertStart = getPosition().first - getPosition().second;
    int diaDiff = getPosition().second * 2;

    for (int i = 0; i < 8; i++) {
        checkPos.second = i;
        checkPos.first = vertStart + i;
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) diaRetList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) diaRetList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) diaRetList.push_back(checkPos);
        else if (i < getPosition().second) diaRetList.clear();
        else if (i > getPosition().second) goto urDone;
    }
    drDone:

    for (int i = 0; i < 8; i++) {
        checkPos.second = i;
        checkPos.first = vertStart + i + (diaDiff - (2 * i));
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) diaRevList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) diaRevList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) diaRevList.push_back(checkPos);
        else if (i < getPosition().second) diaRevList.clear();
        else if (i > getPosition().second) goto urDone;
    }
    urDone:

    std::vector<std::pair<int, int>> retListFinal = retList;
    for (auto move : revList) {
        retListFinal.push_back(move);
    }
    for (auto move : diaRetList) {
        retListFinal.push_back(move);
    }
    for (auto move : diaRevList) {
        retListFinal.push_back(move);
    }

    return retListFinal;
}

Rook::Rook(const std::pair<int, int> &posIn) : Piece(posIn) {
    if (gChessBot->getIsWhite()) setType(wRook);
    else setType(bRook);
}

Rook::~Rook() = default;

std::vector<std::pair<int, int>> Rook::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;
    std::vector<std::pair<int, int>> revList;

    std::pair<int, int> checkPos;

    for (int i = 0; i < 8; i++) {
        checkPos.first = i;
        checkPos.second = getPosition().second;
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPos);
        else if (i < getPosition().first) retList.clear();
        else if (i > getPosition().first) goto firstDone;
    }
    firstDone:

    for (int i = 0; i < 8; i++) {
        checkPos.first = getPosition().first;
        checkPos.second = i;
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) revList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) revList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) revList.push_back(checkPos);
        else if (i < getPosition().second) revList.clear();
        else if (i > getPosition().second) goto secondDone;
    }
    secondDone:

    std::vector<std::pair<int, int>> retListFinal = retList;
    for (auto move : revList) {
        retListFinal.push_back(move);
    }

    return retList;
}

Bishop::Bishop(const std::pair<int, int> &posIn) : Piece(posIn) {
    if (gChessBot->getIsWhite()) setType(wBishop);
    else setType(bBishop);
}

Bishop::~Bishop() = default;

std::vector<std::pair<int, int>> Bishop::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;
    std::vector<std::pair<int, int>> revList;

    int vertStart = getPosition().first - getPosition().second;
    int diaDiff = getPosition().second * 2;

    std::pair<int, int> checkPos;

    for (int i = 0; i < 8; i++) {
        checkPos.second = i;
        checkPos.first = vertStart + i;
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPos);
        else if (i < getPosition().second) retList.clear();
        else if (i > getPosition().second) goto urDone;
    }
    drDone:

    for (int i = 0; i < 8; i++) {
        checkPos.second = i;
        checkPos.first = vertStart + i + (diaDiff - (2 * i));
        pieceType checkRes = gChessBot->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPos);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPos);
        else if (i < getPosition().second) revList.clear();
        else if (i > getPosition().second) goto urDone;
    }
    urDone:

    std::vector<std::pair<int, int>> retListFinal = retList;
    for (auto move : revList) {
        retListFinal.push_back(move);
    }
    return retListFinal;
}

Knight::Knight(const std::pair<int, int> &posIn) : Piece(posIn) {
    if (gChessBot->getIsWhite()) setType(wKnight);
    else setType(bKnight);
}

Knight::~Knight() = default;

std::vector<std::pair<int, int>> Knight::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;

    if (gChessBot == nullptr) return retList;

    std::pair<int, int> checkPosition = getPosition();
    checkPosition.second += 2;
    checkPosition.first += 1;
    pieceType checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkPosition.first += 1;
    if (gChessBot->getBoardPos(checkPosition) == pieceType::Empty) retList.push_back(checkPosition);
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 2;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkPosition.first -= 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first -= 2;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkPosition.first -= 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 2;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkPosition.first += 1;
    checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    return retList;
}

Pawn::Pawn(const std::pair<int, int> &posIn, bool inWhite) : Piece(posIn) {
    if (gChessBot->getIsWhite() && posIn.first == 2) hasMoved = false;
    else hasMoved = true;
    isWhite = inWhite;
    if (isWhite) setType(wPawn);
    else setType(bPawn);
}

Pawn::~Pawn() = default;

std::vector<std::pair<int, int>> Pawn::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;

    if (gChessBot == nullptr) return retList;

    std::pair<int, int> checkPosition = getPosition();
    if (isWhite) checkPosition.first += 1;
    else checkPosition.first -= 1;
    pieceType checkRes = gChessBot->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);

    if (!hasMoved) {
        if (isWhite) checkPosition.first += 1;
        else checkPosition.first -= 1;
        checkRes = gChessBot->getBoardPos(checkPosition);
        if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
        else if (checkRes < 6 && !gChessBot->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
        else if (checkRes >= 6 && gChessBot->getIsWhite()) retList.push_back(checkPosition);
    }

    std::vector<std::pair<int, int>> passant = gChessBot->getPassants();
    std::vector<std::pair<int, int>> passantTarget = gChessBot->getPassantTargets();
    for (auto move : passant) {
        if (move == getPosition()) {
            for (auto target : passantTarget) {
                if (target.second - move.second == 1 || target.second - move.second == -1) retList.push_back(target);
            }
        }
    }

    return retList;
}
