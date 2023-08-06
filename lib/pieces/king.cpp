#include "pieces.h"

namespace ctra
{
    // king::king(colour c) : m_colour(c)
    // {

    // }

    king::king(colour c) : piece(c) 
    {
        // king.colour = c
    }

    king::~king() {}
    

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

    ctra::pieceID king::getPieceId()
    {
        return pieceID::king;
    }
} 


