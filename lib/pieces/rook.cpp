#include "pieces.h"

namespace ctra
{
    rook::rook(colour c) : piece(c) {}
    rook::~rook() {}

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