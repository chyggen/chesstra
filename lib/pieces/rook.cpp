#include "pieces.h"

namespace ctra
{
    rook::rook(colour c) : piece(c) {}
    rook::~rook() {}

    std::set<square> rook::getValidMoves(square loc, const board& boardRef,
            bool checkAttacks)
    {
        std::set<square> moves;
        std::pair<int,int> loc_coords = getCoords(loc);

        // check directions, one at a time 
        // each pair in the offsets set represents a direction in which the rook
        // is allowed to move (digonals, ranks and files in the case of a rook)
        std::set<std::pair<int,int>> offsets = {
            {0,1}, {0,-1}, {1,0}, {-1,0}};
        for (std::pair<int,int> dir : offsets)
        {
            // multiply this offset by a coefficient to get a possible move to check.
            // keep checking moves in this direction until an invalid move is detected,
            // add the last move if it is valid, then break and check the next direction.
            for (int coef = 1; true; ++coef)
            {
                int tmpx = loc_coords.first + dir.first * coef;
                int tmpy = loc_coords.second + dir.second * coef;
                square tmp = getSquare(tmpx, tmpy);
                if (tmp != SQUARE_INVALID)  
                {
                    if (boardRef.at(tmp) == nullptr) 
                    {
                        // Add squares not occupied by any piece
                        moves.insert(tmp);
                        // Keep searching 
                    }
                    else if (boardRef.at(tmp)->getPieceColour() != this->getPieceColour()) 
                    {
                        // Add squares occupied by capturable enemy pieces
                        moves.insert(tmp);
                        // Rook cannot move through pieces, end search
                        break;
                    }
                    else
                    {
                        // The sqaure under consideration is occupied by a friendly piece.
                        // Only add it if we are checking attacks
                        if (checkAttacks)
                        {
                            moves.insert(tmp);
                        }
                        // The rook cannot move past it. End search.
                        break;
                    }
                }
                else 
                {
                    // tmp is an invalid square, the rook cannot move to it or past it.
                    // End search
                    break;
                }
            }
        }

        return moves;
    }

    std::string rook::getDisplayChar()
    {
        if(m_colour == colour::white)
        {
            return std::string(u8"♖");
        }
        else
        {
            return std::string(u8"♜");
        }
    }

    ctra::pieceID rook::getPieceId()
    {
        return pieceID::rook;
    }
} 