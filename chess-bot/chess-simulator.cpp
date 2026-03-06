#include "chess-simulator.h"
// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
// #include "chess.hpp"
#include <random>
#include <unordered_map>
using namespace ChessSimulator;

std::string ChessSimulator::Move(std::string fen,  int timeLimitMs) {
  // create your board based on the board string following the FEN notation
  // search for the best move using minimax / monte carlo tree search /
  // alpha-beta pruning / ... try to use nice heuristics to speed up the search
  // and have better results return the best move in UCI notation you will gain
  // extra points if you create your own board/move representation instead of
  // using the one provided by the library

  chessMover::makeInstance();
  chessMover::getInstance()->createBoard(fen);
  std::vector<std::string> allMoves = chessMover::getInstance()->getAllValidMoves();
  allMoves = orderedMovesByMaterialGain(allMoves);

  return allMoves[0]; //return the move that gives the greatest taken-material value, don't consider incoming losses yet.
}

std::vector<std::string> ChessSimulator::orderedMovesByMaterialGain(std::vector<std::string> &moves, int depth) {
  std::unordered_map<std::string, int> materialValuedMoves;

  for (int i = 0; i < moves.size(); i++) {
    bool leavesCheck = false;
    int moveValue = tryMoveSeeEnemyAnswer(moves[i], leavesCheck, depth);
    if (!leavesCheck) materialValuedMoves.insert({moves[i], moveValue});
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

int ChessSimulator::getMoveCaptureValue(std::string move, bool &leavesCheck, bool tryingEnemy) {
    int moveValue = 0;
    if (chessMover::getInstance()->getIsWhite()) {
        switch (chessMover::getInstance()->getBoardPos(findLocFromMove(move, true))) {
            case bKing:
                if (tryingEnemy) leavesCheck = true;
                else moveValue = 999;
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
        switch (chessMover::getInstance()->getBoardPos(findLocFromMove(move, true))) {
            case wKing:
                if (tryingEnemy) leavesCheck = true;
                else moveValue = 999;
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
    return moveValue;
}

int ChessSimulator::getMoveCaptureValue(std::pair<int, int> move, bool &leavesCheck, bool tryingEnemy) {
    int moveValue = 0;
    if (chessMover::getInstance()->getIsWhite()) {
        switch (chessMover::getInstance()->getBoardPos(move)) {
            case bKing:
                if (tryingEnemy) leavesCheck = true;
                else moveValue = 999;
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
        switch (chessMover::getInstance()->getBoardPos(move)) {
            case wKing:
                if (tryingEnemy) leavesCheck = true;
                else moveValue = 999;
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
    return moveValue;
}

std::pair<int, int> ChessSimulator::findLocFromMove(std::string move, bool findTarget) {
  std::pair<int, int> ret;
  int start = 0;
  if (findTarget) start += 2;
  char letter = move[start];
  ret.second = (int)(letter - 97);
  start++;
  ret.first = 8 - std::stoi(move.substr(start));
  return ret;
}

int ChessSimulator::getMoveAttackValue(std::string move, bool &leavesCheck, bool tryingEnemy) {
    Piece* movedPiece = chessMover::getInstance()->getPieceAtLocation(findLocFromMove(move));
    if (movedPiece == nullptr) return -999;
    std::pair<int, int> oldPos = movedPiece->getPosition();
    std::pair<int, int> target = findLocFromMove(move, true);
    movedPiece->setPosition(target.first, target.second);
    /*bool wasPawn = false;
    if (movedPiece->getType() == wPawn || movedPiece->getType() == bPawn) {
        wasPawn = true;
        if (move.size() > 4) {
            char check = move[4];
            switch (check) {
                case 113:
                    if (movedPiece->getType() == wPawn) movedPiece = new Queen(target);
                    else movedPiece = new Queen(target, false);
                    break;
                case 114:
                    if (movedPiece->getType() == wPawn) movedPiece = new Rook(target);
                    else movedPiece = new Rook(target, false);
                    break;
                case 98:
                    if (movedPiece->getType() == wPawn) movedPiece = new Bishop(target);
                    else movedPiece = new Bishop(target, false);
                    break;
                case 110:
                    if (movedPiece->getType() == wPawn) movedPiece = new Knight(target);
                    else movedPiece = new Knight(target, false);
                    break;
                default:
                    break;
            }
        }
        else {
            //Pawn* movedPawn = dynamic_cast<Pawn*>(movedPiece);
            //movedPawn->setHasMoved(true);
        }
    }*/
    std::vector<std::pair<int, int>> newMoves = movedPiece->GetValidMoves();
    int retValue = 0;
    for (auto tryMove : newMoves) {
        retValue += getMoveCaptureValue(tryMove, tryingEnemy, leavesCheck);
        if (leavesCheck) return retValue;
    }
    movedPiece->setPosition(oldPos.first, oldPos.second);
    /*if (wasPawn) {
        movedPiece->setType(wPawn);
        //Pawn* movedPawn = dynamic_cast<Pawn*>(movedPiece);
        //movedPawn->setHasMoved(true);
    }*/
    return retValue;
}

int ChessSimulator::tryMoveSeeEnemyAnswer(std::string move, bool &leavesCheck, int depth) {
    int ret = 0;
    ret += getMoveCaptureValue(move, leavesCheck) * 10;
    ret += getMoveAttackValue(move, leavesCheck);

    if (depth >= 2) return ret;

    chessMover saveBoard;
    saveBoard.copyBoard(chessMover::getInstance()->getBoard());
    saveBoard.setPiecesStorage(chessMover::getInstance()->getPiecesStorage());
    saveBoard.setIsWhite(chessMover::getInstance()->getIsWhite());
    saveBoard.setCastlesString(chessMover::getInstance()->getCastlesString());
    saveBoard.setPassantsString(chessMover::getInstance()->getPassantsString());
    saveBoard.setHalfMoveNum(chessMover::getInstance()->getHalfMoveNum());
    saveBoard.setTurnCount(chessMover::getInstance()->getTurnCount());

    tryMove(move);

    std::vector<std::string> allMoves = chessMover::getInstance()->getAllValidMoves();
    allMoves = orderedMovesByMaterialGain(allMoves, depth + 1);

    ret -= getMoveCaptureValue(allMoves[0], leavesCheck, true) * 10;
    ret -= getMoveAttackValue(allMoves[0], leavesCheck);

    chessMover::getInstance()->copyBoard(saveBoard.getBoard());
    chessMover::getInstance()->setPiecesStorage(saveBoard.getPiecesStorage());
    chessMover::getInstance()->setIsWhite(saveBoard.getIsWhite());
    chessMover::getInstance()->setCastlesString(saveBoard.getCastlesString());
    chessMover::getInstance()->setPassantsString(saveBoard.getPassantsString());
    chessMover::getInstance()->setHalfMoveNum(saveBoard.getHalfMoveNum());
    chessMover::getInstance()->setTurnCount(saveBoard.getTurnCount());

    return ret / (depth + 1);
}

void ChessSimulator::tryMove(std::string move) {
    chessMover::getInstance()->setIsWhite(!chessMover::getInstance()->getIsWhite());
    Piece* movedPiece = chessMover::getInstance()->getPieceAtLocation(findLocFromMove(move));
    if (movedPiece == nullptr) return;
    std::pair<int, int> oldPos = movedPiece->getPosition();
    std::pair<int, int> target = findLocFromMove(move, true);
    movedPiece->setPosition(target.first, target.second);
    /*if (movedPiece->getType() == wPawn || movedPiece->getType() == bPawn) {
        if (move.size() > 4) {
            char check = move[4];
            switch (check) {
                case 113:
                    if (movedPiece->getType() == wPawn) movedPiece = new Queen(target);
                    else movedPiece = new Queen(target, false);
                    break;
                case 114:
                    if (movedPiece->getType() == wPawn) movedPiece = new Rook(target);
                    else movedPiece = new Rook(target, false);
                    break;
                case 98:
                    if (movedPiece->getType() == wPawn) movedPiece = new Bishop(target);
                    else movedPiece = new Bishop(target, false);
                    break;
                case 110:
                    if (movedPiece->getType() == wPawn) movedPiece = new Knight(target);
                    else movedPiece = new Knight(target, false);
                    break;
                default:
                    break;
            }
        }
        else {
            //Pawn* movedPawn = dynamic_cast<Pawn*>(movedPiece);
            //movedPawn->setHasMoved(true);
        }
    }*/
    chessMover::getInstance()->setBoardPos(oldPos, Empty);
    chessMover::getInstance()->setBoardPos(target, movedPiece->getType());
}

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
    if (!inWhite && posIn.first == 1) hasMoved = false;
    else if (inWhite && posIn.first == 6) hasMoved = false;
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

    checkPosition.second += 1;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace && checkRes != Empty) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    checkPosition.second -= 2;
    checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
    if (checkRes < 6 && !chessMover::getInstance()->getIsWhite() && checkRes != NullSpace && checkRes != Empty) retList.push_back(checkPosition);
    else if (checkRes >= 6 && chessMover::getInstance()->getIsWhite()) retList.push_back(checkPosition);

    if (!hasMoved) {
        checkPosition.second += 1;
        if (isWhite) checkPosition.first -= 1;
        else checkPosition.first += 1;
        checkRes = chessMover::getInstance()->getBoardPos(checkPosition);
        if (checkRes == pieceType::Empty) retList.push_back(checkPosition);
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

void chessMover::killInstance() {
    delete gChessBot;
    gChessBot = nullptr;
}

chessMover::chessMover() {

}

chessMover::~chessMover() {

}

void chessMover::createBoard(std::string boardFEN) {
    board = boardState();
    std::string blackPieceIDs = "kqrbnp";
    std::string whitePieceIDs = "KQRBNP";
    std::string SLASH = "/";
    int L = 0;
    int N = 0;
    int i = 0;
    for (i = 0; L < 8; i++) {
        if (boardFEN[i] == SLASH[0]) i++;
        if (boardFEN[i] == blackPieceIDs[0]) {
            board.theBoard[L][N] = bKing;
            N++;
        }
        else if (boardFEN[i] == blackPieceIDs[1]) {
            board.theBoard[L][N] = bQueen;
            N++;
        }
        else if (boardFEN[i] == blackPieceIDs[2]) {
            board.theBoard[L][N] = bRook;
            N++;
        }
        else if (boardFEN[i] == blackPieceIDs[3]) {
            board.theBoard[L][N] = bBishop;
            N++;
        }
        else if (boardFEN[i] == blackPieceIDs[4]) {
            board.theBoard[L][N] = bKnight;
            N++;
        }
        else if (boardFEN[i] == blackPieceIDs[5]) {
            board.theBoard[L][N] = bPawn;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[0]) {
            board.theBoard[L][N] = wKing;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[1]) {
            board.theBoard[L][N] = wQueen;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[2]) {
            board.theBoard[L][N] = wRook;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[3]) {
            board.theBoard[L][N] = wBishop;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[4]) {
            board.theBoard[L][N] = wKnight;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[5]) {
            board.theBoard[L][N] = wPawn;
            N++;
        }
        else {
            int spaces = std::stoi(boardFEN.substr(i));
            for (int j = 0; j < spaces; j++) {
                board.theBoard[L][N] = Empty;
                N++;
            }
        }
        if (N >= 8) {
            N = 0;
            L++;
        }
    }
    i++;
    std::string WHITE = "w";
    if (boardFEN[i] == WHITE[0]) isWhite = true;
    else isWhite = false;
    i += 2;
    std::string EMPTY = " ";
    castleMoves = "";
    while (boardFEN[i] != EMPTY[0]) {
        castleMoves += boardFEN[i];
        i++;
    }
    i++;
    enPassantMoves = "";
    while (boardFEN[i] != EMPTY[0]) {
        enPassantMoves += boardFEN[i];
        i++;
    }
    i++;
    halfMoveNum = stoi(boardFEN.substr(i));
    i += 2;
    turnCount = stoi(boardFEN.substr(i));
    findAllPieces();
}

void chessMover::copyBoard(boardState &copy) {
    board = copy;
    findAllPieces();
}

void chessMover::findAllPieces() {
    for (int L = 0; L < 8; L++) {
        for (int N = 0; N < 8; N++) {
            if (board.theBoard[L][N] == wKing) {
                King* newKing = new King(std::make_pair(L, N));
                pieces.push_back(newKing);
            }
            if (board.theBoard[L][N] == wQueen) {
                Queen* newQueen = new Queen(std::make_pair(L, N));
                pieces.push_back(newQueen);
            }
            if (board.theBoard[L][N] == wRook) {
                Rook* newRook = new Rook(std::make_pair(L, N));
                pieces.push_back(newRook);
            }
            if (board.theBoard[L][N] == wBishop) {
                Bishop* newBishop = new Bishop(std::make_pair(L, N));
                pieces.push_back(newBishop);
            }
            if (board.theBoard[L][N] == wKnight) {
                Knight* newKnight = new Knight(std::make_pair(L, N));
                pieces.push_back(newKnight);
            }
            if (board.theBoard[L][N] == wPawn) {
                Pawn* newPawn = new Pawn(std::make_pair(L, N));
                pieces.push_back(newPawn);
            }
            if (board.theBoard[L][N] == bKing) {
                King* newKing = new King(std::make_pair(L, N), false);
                pieces.push_back(newKing);
            }
            if (board.theBoard[L][N] == bQueen) {
                Queen* newQueen = new Queen(std::make_pair(L, N), false);
                pieces.push_back(newQueen);
            }
            if (board.theBoard[L][N] == bRook) {
                Rook* newRook = new Rook(std::make_pair(L, N), false);
                pieces.push_back(newRook);
            }
            if (board.theBoard[L][N] == bBishop) {
                Bishop* newBishop = new Bishop(std::make_pair(L, N), false);
                pieces.push_back(newBishop);
            }
            if (board.theBoard[L][N] == bKnight) {
                Knight* newKnight = new Knight(std::make_pair(L, N), false);
                pieces.push_back(newKnight);
            }
            if (board.theBoard[L][N] == bPawn) {
                Pawn* newPawn = new Pawn(std::make_pair(L, N), false);
                pieces.push_back(newPawn);
            }
        }
    }
}

std::vector<std::string> chessMover::getAllValidMoves() {
    std::vector<std::string> retList;

    for (auto piece : pieces) {
        std::vector<std::pair<int, int>> pieceMoves;
        if (piece->getType() < 6 && isWhite) pieceMoves = piece->GetValidMoves();
        if (piece->getType() >= 6 && !isWhite) pieceMoves = piece->GetValidMoves();
        for (auto move : pieceMoves) {
            std::string moveStr = "";
            char letter = (char)(piece->getPosition().second + 97);
            moveStr += letter;
            moveStr += std::to_string(8 - piece->getPosition().first);
            letter = (char)(move.second + 97);
            moveStr += letter;
            moveStr += std::to_string(8 - move.first);
            if (piece->getType() == wPawn && move.first == 0) {
                retList.push_back(moveStr + "q");
                retList.push_back(moveStr + "r");
                retList.push_back(moveStr + "b");
                retList.push_back(moveStr + "n");
            }
            else if (piece->getType() == bPawn && move.first == 7) {
                retList.push_back(moveStr + "q");
                retList.push_back(moveStr + "r");
                retList.push_back(moveStr + "b");
                retList.push_back(moveStr + "n");
            }
            else retList.push_back(moveStr);
        }
    }

    return retList;
}

pieceType chessMover::getBoardPos(std::pair<int, int> checkPos) {
    if (checkPos.first <= -1 || checkPos.second <= -1) return NullSpace;
    if (checkPos.first >= 8 || checkPos.second >= 8) return NullSpace;
    return this->board.theBoard[checkPos.first][checkPos.second];
}

void chessMover::setBoardPos(std::pair<int, int> checkPos, pieceType newVal) {
    if (checkPos.first <= -1 || checkPos.second <= -1) return;
    if (checkPos.first >= 8 || checkPos.second >= 8) return;
    this->board.theBoard[checkPos.first][checkPos.second] = newVal;
}

std::vector<std::pair<int, int>> chessMover::getCastles() {
    std::vector<std::pair<int, int>> retList;

    std::string moves = "KQkq";
    for (int i = 0; i < castleMoves.size(); i++) {
        if (castleMoves[i] == moves[0] && isWhite) {
            std::pair<int, int> castlePair = std::make_pair(7, 5);
            if (getBoardPos(castlePair) == Empty) {
                castlePair.second++;
                if (getBoardPos(castlePair) == Empty) retList.push_back(castlePair);
            }
        }
        if (castleMoves[i] == moves[1] && isWhite) {
            std::pair<int, int> castlePair = std::make_pair(7, 3);
            if (getBoardPos(castlePair) == Empty) {
                castlePair.second--;
                if (getBoardPos(castlePair) == Empty) retList.push_back(castlePair);
            }
        }
        if (castleMoves[i] == moves[2] && !isWhite) {
            std::pair<int, int> castlePair = std::make_pair(0, 5);
            if (getBoardPos(castlePair) == Empty) {
                castlePair.second++;
                if (getBoardPos(castlePair) == Empty) retList.push_back(castlePair);
            }
        }
        if (castleMoves[i] == moves[3] && !isWhite) {
            std::pair<int, int> castlePair = std::make_pair(0, 3);
            if (getBoardPos(castlePair) == Empty) {
                castlePair.second--;
                if (getBoardPos(castlePair) == Empty) retList.push_back(castlePair);
            }
        }
    }

    return retList;
}

std::vector<std::pair<int, int>> chessMover::getPassants() {
    std::vector<std::pair<int, int>> retList;
    std::string DASH = "-";
    if (enPassantMoves[0] == DASH[0]) return retList;

    for (int i = 0; i < enPassantMoves.size(); i++) {
        std::pair<int, int> move;
        move.second = (char)enPassantMoves[i] - 97;
        i++;
        move.first = std::stoi(enPassantMoves.substr(i));
        if (isWhite) move.first--;
        if (move.first == 5) {
            move.second--;
            if (getBoardPos(move) != NullSpace) retList.push_back(move);
            move.second += 2;
            if (getBoardPos(move) != NullSpace) retList.push_back(move);
        }
        if (!isWhite) move.first++;
        if (move.first == 4) {
            move.second--;
            if (getBoardPos(move) != NullSpace) retList.push_back(move);
            move.second += 2;
            if (getBoardPos(move) != NullSpace) retList.push_back(move);
        }
    }

    return retList;
}

std::vector<std::pair<int, int> > chessMover::getPassantTargets() {
    std::vector<std::pair<int, int>> retList;
    std::string DASH = "-";
    if (enPassantMoves[0] == DASH[0]) return retList;

    for (int i = 0; i < enPassantMoves.size(); i++) {
        std::pair<int, int> move;
        move.first = (char)enPassantMoves[i] - 97;
        i++;
        move.second = std::stoi(enPassantMoves.substr(i));
        retList.push_back(move);
    }

    return retList;
}

Piece *chessMover::getPieceAtLocation(std::pair<int, int> checkPos) {
    for (auto piece : pieces) {
        if (piece->getPosition() == checkPos) return piece;
    }
    return nullptr;
}