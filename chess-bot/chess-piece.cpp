#include "chess-piece.h"
#include "chess-mover.h"

Piece::Piece(std::pair<int, int> posIn) {
    positionLN = posIn;
}

Piece::~Piece() {}

King::King(const std::pair<int, int> &posIn, bool inWhite) : Piece(posIn) {
    if (inWhite) setType(wKing);
    else setType(bKing);
}

King::~King() {}

std::vector<std::pair<int, int>> King::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;

    if (chessMover::getInstance() == nullptr) return retList;

    retList = chessMover::getInstance()->getCastles();

    std::pair<int, int> checkPosition = getPosition();
    checkPosition.second += 1;
    pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first += 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first -= 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first -= 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    return retList;
}

Queen::Queen(const std::pair<int, int> &posIn, bool inWhite) : Piece(posIn) {
    if (inWhite) setType(wQueen);
    else setType(bQueen);
}

Queen::~Queen() {}

std::vector<std::pair<int, int>> Queen::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;
    std::vector<std::pair<int, int>> revList;

    std::pair<int, int> checkPos;

    for (int i = 0; i < 8; i++) {
        checkPos.first = i;
        checkPos.second = getPosition().second;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            retList.push_back(checkPos);
            if (i < getPosition().first) retList.clear();
            else if (i > getPosition().first) goto firstDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            retList.push_back(checkPos);
            if (i < getPosition().first) retList.clear();
            else if (i > getPosition().first) goto firstDone;
        }
        else if (i < getPosition().first) retList.clear();
        else if (i > getPosition().first) goto firstDone;
    }
    firstDone:

    for (int i = 0; i < 8; i++) {
        checkPos.first = getPosition().first;
        checkPos.second = i;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) revList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            revList.push_back(checkPos);
            if (i < getPosition().second) revList.clear();
            else if (i > getPosition().second) goto secondDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            revList.push_back(checkPos);
            if (i < getPosition().second) revList.clear();
            else if (i > getPosition().second) goto secondDone;
        }
        else if (i < getPosition().second) revList.clear();
        else if (i > getPosition().second) goto secondDone;
    }
    secondDone:

    std::vector<std::pair<int, int>> diaRetList;

    checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first++;
        checkPos.second++;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) diaRetList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            diaRetList.push_back(checkPos);
            goto urDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            diaRetList.push_back(checkPos);
            goto urDone;
        }
        else goto urDone;
    }
    urDone:

    checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first++;
        checkPos.second--;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) diaRetList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            diaRetList.push_back(checkPos);
            goto drDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            diaRetList.push_back(checkPos);
            goto drDone;
        }
        else goto drDone;
    }
    drDone:

    checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first--;
        checkPos.second++;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) diaRetList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            diaRetList.push_back(checkPos);
            goto ulDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            diaRetList.push_back(checkPos);
            goto ulDone;
        }
        else goto ulDone;
    }
    ulDone:

    checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first--;
        checkPos.second--;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) diaRetList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            diaRetList.push_back(checkPos);
            goto dlDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            diaRetList.push_back(checkPos);
            goto dlDone;
        }
        else goto dlDone;
    }
    dlDone:

    std::vector<std::pair<int, int>> retListFinal = retList;
    for (auto move : revList) {
        retListFinal.push_back(move);
    }
    for (auto move : diaRetList) {
        retListFinal.push_back(move);
    }

    return retListFinal;
}

Rook::Rook(const std::pair<int, int> &posIn, bool inWhite) : Piece(posIn) {
    if (inWhite) setType(wRook);
    else setType(bRook);
}

Rook::~Rook() {}

std::vector<std::pair<int, int>> Rook::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;
    std::vector<std::pair<int, int>> revList;

    std::pair<int, int> checkPos;

    for (int i = 0; i < 8; i++) {
        checkPos.first = i;
        checkPos.second = getPosition().second;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            retList.push_back(checkPos);
            if (i < getPosition().first) retList.clear();
            else if (i > getPosition().first) goto firstDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            retList.push_back(checkPos);
            if (i < getPosition().first) retList.clear();
            else if (i > getPosition().first) goto firstDone;
        }
        else if (i < getPosition().first) retList.clear();
        else if (i > getPosition().first) goto firstDone;
    }
    firstDone:

    for (int i = 0; i < 8; i++) {
        checkPos.first = getPosition().first;
        checkPos.second = i;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) revList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            revList.push_back(checkPos);
            if (i < getPosition().second) revList.clear();
            else if (i > getPosition().second) goto secondDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            revList.push_back(checkPos);
            if (i < getPosition().second) revList.clear();
            else if (i > getPosition().second) goto secondDone;
        }
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

Bishop::Bishop(const std::pair<int, int> &posIn, bool inWhite) : Piece(posIn) {
    if (inWhite) setType(wBishop);
    else setType(bBishop);
}

Bishop::~Bishop() {}

std::vector<std::pair<int, int>> Bishop::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;

    std::pair<int, int> checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first++;
        checkPos.second++;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            retList.push_back(checkPos);
            goto urDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            retList.push_back(checkPos);
            goto urDone;
        }
        else goto urDone;
    }
    urDone:

    checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first++;
        checkPos.second--;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            retList.push_back(checkPos);
            goto drDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            retList.push_back(checkPos);
            goto drDone;
        }
        else goto drDone;
    }
    drDone:

    checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first--;
        checkPos.second++;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            retList.push_back(checkPos);
            goto ulDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            retList.push_back(checkPos);
            goto ulDone;
        }
        else goto ulDone;
    }
    ulDone:

    checkPos = getPosition();

    for (int i = checkPos.first; i < 8; i++) {
        checkPos.first--;
        checkPos.second--;
        pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPos);
        if (checkRes == pieceType::Empty) retList.push_back(checkPos);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) {
            retList.push_back(checkPos);
            goto dlDone;
        }
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) {
            retList.push_back(checkPos);
            goto dlDone;
        }
        else goto dlDone;
    }
    dlDone:

    return retList;
}

Knight::Knight(const std::pair<int, int> &posIn, bool inWhite) : Piece(posIn) {
    if (inWhite) setType(wKnight);
    else setType(bKnight);
}

Knight::~Knight() {}

std::vector<std::pair<int, int>> Knight::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;

    if (chessMover::getInstance() == nullptr) return retList;

    std::pair<int, int> checkPosition = getPosition();
    checkPosition.second += 2;
    checkPosition.first += 1;
    pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkPosition.first += 1;
    if (chessMover::getInstance()->getBoardPos(checkPosition) == pieceType::Empty) retList.push_back(checkPosition);
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 2;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 1;
    checkPosition.first -= 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.first -= 2;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkPosition.first -= 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 2;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second += 1;
    checkPosition.first += 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    return retList;
}

Pawn::Pawn(const std::pair<int, int> &posIn, bool inWhite) : Piece(posIn) {
    if (inWhite && posIn.first == 1) hasMoved = false;
    else if (!inWhite && posIn.first == 6) hasMoved = false;
    else hasMoved = true;
    isWhite = inWhite;
    if (isWhite) setType(wPawn);
    else setType(bPawn);
}

Pawn::~Pawn() {}

std::vector<std::pair<int, int>> Pawn::GetValidMoves() {
    std::vector<std::pair<int, int>> retList;

    if (chessMover::getInstance() == nullptr) return retList;

    std::pair<int, int> checkPosition = getPosition();
    if (isWhite) checkPosition.first -= 1;
    else checkPosition.first += 1;
    pieceType checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
    else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    if (!hasMoved) {
        if (isWhite) checkPosition.first -= 1;
        else checkPosition.first += 1;
        checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
        if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
        else if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace) retList.push_back(checkPosition);
        else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);
    }

    std::vector<std::pair<int, int>> passant = chessMover::getInstance()->getPassants();
    std::vector<std::pair<int, int>> passantTarget = chessMover::getInstance()->getPassantTargets();
    for (auto move : passant) {
        if (move == getPosition()) {
            for (auto target : passantTarget) {
                if (target.second - move.second == 1 || target.second - move.second == -1) retList.push_back(target);
            }
        }
    }

    return retList;
}
