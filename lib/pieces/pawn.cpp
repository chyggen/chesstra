#include "pieces.h"

namespace ctra
{
    pawn::pawn(colour c) : piece(c) {}
    pawn::~pawn() {}

    std::string pawn::getDisplayChar()
    {
        if(m_colour == colour::white)
        {
            return std::string(u8"♙");
        }
        else
        {
            return std::string(u8"♟︎");
        }
    }

    ctra::pieceID pawn::getPieceId()
    {
        return pieceID::pawn;
    }
} 