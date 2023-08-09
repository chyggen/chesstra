#include "pieces.h"

namespace ctra
{
    knight::knight(colour c) : piece(c) {}
    knight::~knight() {}

    std::set<square> knight::getValidMoves(square loc, const board& boardRef)
    {
        std::set<square> moves;
        std::pair<int,int> loc_coords = getCoords(loc);

        // The knight is different than normal pieces in that it can only move fixed distances,
        // so no need to use coeffiecients and check directions. Instead, check all 8 fixed 
        // move vectors
        std::set<std::pair<int,int>> move_vecs = {
            {2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}};
        for (std::pair<int,int> vec : move_vecs)
        {
            int tmpx = loc_coords.first + vec.first;
            int tmpy = loc_coords.second + vec.second;
            square tmp = getSquare(tmpx, tmpy);
            if (tmp != SQUARE_INVALID)  
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
                // Don't add squares occupied by friendly pieces, 
            }
        }
        return moves;
    }

    std::string knight::getDisplayChar()
    {
        if(m_colour == colour::white)
        {
            return std::string(u8"♘");
        }
        else
        {
            return std::string(u8"♞");
        }
    }

    ctra::pieceID knight::getPieceId()
    {
        return pieceID::knight;
    }
} 