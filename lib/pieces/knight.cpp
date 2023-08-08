#include "pieces.h"

namespace ctra
{
    knight::knight(colour c) : piece(c) {}
    knight::~knight() {}

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