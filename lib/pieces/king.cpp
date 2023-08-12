#include "pieces.h"

namespace ctra
{
    king::king(colour c) : piece(c) {}
    king::~king() {}

    std::set<square> king::getValidMoves(square loc, const board& boardRef,
            bool checkAttacks)
    {
        std::set<square> moves;
        std::pair<int,int> loc_coords = getCoords(loc);

        // check all squares bordering king, 
        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                // no need to check offset of 0,0
                if (x != 0 || y != 0)
                {
                    square tmp = getSquare(loc_coords.first + x, loc_coords.second + y);
                    if (tmp != SQUARE_INVALID)
                    {
                        if (checkAttacks)
                        {
                            // All squares bordering the king are always attacked
                            moves.insert(tmp);
                        }

                        bool squareAttacked = (boardRef.at(loc)->isWhite() ? 
                            boardRef.attackStats(tmp).black : boardRef.attackStats(tmp).white);
                        if (!squareAttacked)
                        {
                            if (boardRef.at(tmp) == nullptr) 
                            {
                                // Add squares not occupied by any piece
                                moves.insert(tmp);
                            }
                            else if (boardRef.at(tmp)->getPieceColour() != this->getPieceColour()) 
                            {
                                // Add squares occupied by capturable enemy pieces
                                moves.insert(tmp);
                            }
                        }
                    } 
                }
            }
        }

        // Also check castling options. Note that in order for castling to be legal, no pieces can occupy
        // the squares between the involved king and rook and the king cannot pass through check. 
        if (boardRef.at(loc)->isWhite())
        {
            // If the king is white, castling castling rights are denoted by upper case
            // and moves the king to g1 or c1
            if (boardRef.castlingRights().count('K') && 
                boardRef.at(F1) == nullptr && 
                boardRef.at(G1) == nullptr &&
                !boardRef.attackStats(F1).black &&
                !boardRef.attackStats(G1).black)
            {
                moves.insert(G1);
            }
            if (boardRef.castlingRights().count('Q') && 
                boardRef.at(D1) == nullptr && 
                boardRef.at(C1) == nullptr &&
                boardRef.at(B1) == nullptr &&
                !boardRef.attackStats(D1).black &&
                !boardRef.attackStats(C1).black)
            {
                moves.insert(C1);
            }

        }
        else
        {
            // If the king is black, castling castling rights are denoted by lower case
            // and moves the king to g8 or c8
            if (boardRef.castlingRights().count('k') && 
                boardRef.at(F8) == nullptr && 
                boardRef.at(G8) == nullptr &&
                !boardRef.attackStats(F8).white &&
                !boardRef.attackStats(G8).white)
            {
                moves.insert(G8);
            }
            if (boardRef.castlingRights().count('q') &&
                boardRef.at(D8) == nullptr &&
                boardRef.at(C8) == nullptr &&
                boardRef.at(B8) == nullptr &&
                !boardRef.attackStats(D8).white &&
                !boardRef.attackStats(C8).white)
            {
                moves.insert(C8);
            }
        }
        return moves;
    }

    std::string king::getDisplayChar()
    {
        if(m_colour == colour::white)
        {
            return std::string(u8"♔");
        }
        else
        {
            return std::string(u8"♚");
        }
    }

    pieceID king::getPieceId()
    {
        return pieceID::king;
    }
} 


