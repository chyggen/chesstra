#include "pieces.h"

namespace ctra
{
    queen::queen(colour c) : piece(c) {}
    queen::~queen() {}

    std::string queen::getDisplayChar()
    {
        if(m_colour == colour::white)
        {
            return std::string(u8"♕");
        }
        else
        {
            return std::string(u8"♛");
        }
    }

    ctra::pieceID queen::getPieceId()
    {
        return pieceID::queen;
    }
} 