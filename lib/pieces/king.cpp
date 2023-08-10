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
                    
                    if (tmp != SQUARE_INVALID) // TODO: don't consider squares attacked by enemy pieces 
                    {
                        if (checkAttacks)
                        {
                            // All squares bordering the king are always attacked
                            moves.insert(tmp);
                        }
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

        // //also check castling options 
        // {
        //     boardRef.at()
        // }
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


