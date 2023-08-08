#include "pieces.h"

namespace ctra
{
    bishop::bishop(colour c) : piece(c) {}
    bishop::~bishop() {}

    std::string bishop::getDisplayChar()
    {
        if(m_colour == colour::white)
        {
            return std::string(u8"♗");
        }
        else
        {
            return std::string(u8"♝");
        }
    }

    ctra::pieceID bishop::getPieceId()
    {
        return pieceID::bishop;
    }
} 