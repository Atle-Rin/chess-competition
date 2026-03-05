#include "chess-mover.h"


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
            board.theBoard[L][N] = bKing;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[1]) {
            board.theBoard[L][N] = bQueen;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[2]) {
            board.theBoard[L][N] = bRook;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[3]) {
            board.theBoard[L][N] = bBishop;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[4]) {
            board.theBoard[L][N] = bKnight;
            N++;
        }
        else if (boardFEN[i] == whitePieceIDs[5]) {
            board.theBoard[L][N] = bPawn;
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
            if (board.theBoard[L][N] == wKing) pieces.push_back(new King(std::make_pair(L,N)));
            if (board.theBoard[L][N] == wQueen) pieces.push_back(new Queen(std::make_pair(L,N)));
            if (board.theBoard[L][N] == wRook) pieces.push_back(new Rook(std::make_pair(L,N)));
            if (board.theBoard[L][N] == wBishop) pieces.push_back(new Bishop(std::make_pair(L,N)));
            if (board.theBoard[L][N] == wKnight) pieces.push_back(new Knight(std::make_pair(L,N)));
            if (board.theBoard[L][N] == wPawn) pieces.push_back(new Pawn(std::make_pair(L,N)));
            if (board.theBoard[L][N] == bKing) pieces.push_back(new King(std::make_pair(L,N)));
            if (board.theBoard[L][N] == bQueen) pieces.push_back(new Queen(std::make_pair(L,N)));
            if (board.theBoard[L][N] == bRook) pieces.push_back(new Rook(std::make_pair(L,N)));
            if (board.theBoard[L][N] == bBishop) pieces.push_back(new Bishop(std::make_pair(L,N)));
            if (board.theBoard[L][N] == bKnight) pieces.push_back(new Knight(std::make_pair(L,N)));
            if (board.theBoard[L][N] == bPawn) pieces.push_back(new Pawn(std::make_pair(L,N), false));
        }
    }
}


std::vector<std::string> chessMover::getAllValidMoves() {
    std::vector<std::string> retList;

    for (auto piece : pieces) {
        std::vector<std::pair<int, int>> pieceMoves = piece->GetValidMoves();
        for (auto move : pieceMoves) {
            std::string moveStr = "";
            char letter = (char)(piece->getPosition().first + 97);
            moveStr += letter;
            moveStr += std::to_string(piece->getPosition().second);
            letter = (char)(move.first + 97);
            moveStr += letter;
            moveStr += std::to_string(move.second);
            if (piece->getType() == wPawn && move.first == 7) {
                retList.push_back(moveStr + "q");
                retList.push_back(moveStr + "r");
                retList.push_back(moveStr + "b");
                retList.push_back(moveStr + "n");
            }
            else if (piece->getType() == bPawn && move.first == 0) {
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
    return board.theBoard[checkPos.first][checkPos.second];
}

std::vector<std::pair<int, int>> chessMover::getCastles() {
    std::vector<std::pair<int, int>> retList;

    std::string moves = "KQkq";
    for (int i = 0; i < castleMoves.size(); i++) {
        if (castleMoves[i] == moves[0] && isWhite) retList.push_back(std::make_pair(6, 1));
        if (castleMoves[i] == moves[1] && isWhite) retList.push_back(std::make_pair(2, 1));
        if (castleMoves[i] == moves[2] && !isWhite) retList.push_back(std::make_pair(6, 8));
        if (castleMoves[i] == moves[3] && !isWhite) retList.push_back(std::make_pair(2, 8));
    }

    return retList;
}

std::vector<std::pair<int, int>> chessMover::getPassants() {
    std::vector<std::pair<int, int>> retList;

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

    for (int i = 0; i < enPassantMoves.size(); i++) {
        std::pair<int, int> move;
        move.first = (char)enPassantMoves[i] - 97;
        i++;
        move.second = std::stoi(enPassantMoves.substr(i));
        retList.push_back(move);
    }

    return retList;
}
