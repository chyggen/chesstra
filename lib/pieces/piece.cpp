#include "pieces.h"
#include <stdexcept>

namespace ctra
{
    piece::piece(colour c) : 
        m_colour(c)
    {}

    ctra::colour piece::getPieceColour()
    {
        return m_colour;
    }

    bool piece::isWhite()
    {
       return m_colour == colour::white;
    }

    // helper functions

    pieceID fenCharToPieceId(char c)
    {
        switch (tolower(c))
        {
            case 'k':
                return pieceID::king;
            case 'q':
                return pieceID::queen;
            case 'r':
                return pieceID::rook;
            case 'b':
                return pieceID::bishop;
            case 'n':
                return pieceID::knight;
            case 'p':
                return pieceID::pawn;
            default:
                return pieceID::INVALID;
        }
    }

    char pieceToFenChar(pieceID piece, colour c)
    {
        switch (piece)
        {
            case pieceID::king:
                return (c == colour::white) ? 'K' : 'k';
            case pieceID::queen:
                return (c == colour::white) ? 'Q' : 'q';
            case pieceID::rook:
                return (c == colour::white) ? 'R' : 'r';
            case pieceID::bishop:
                return (c == colour::white) ? 'B' : 'b';
            case pieceID::knight:
                return (c == colour::white) ? 'N' : 'n';
            case pieceID::pawn:
                return (c == colour::white) ? 'P' : 'p';
            default:
                return '-';
        }
    }


    std::shared_ptr<ctra::piece> newPiece(pieceID id, colour c){
        if (c != colour::black && c != colour::white)
        {
            throw std::runtime_error("invalid colour passed to newPiece");
        }
        switch (id)
        {
        case pieceID::pawn:
            return std::make_shared<ctra::pawn>(c);

        case pieceID::bishop:
            return std::make_shared<ctra::bishop>(c);

        case pieceID::knight:
            return std::make_shared<ctra::knight>(c);

        case pieceID::rook:
            return std::make_shared<ctra::rook>(c);

        case pieceID::king:
            return std::make_shared<ctra::king>(c);

        case pieceID::queen:
            return std::make_shared<ctra::queen>(c);

        default:
            throw std::runtime_error("invalid piece ID passed to newPiece");
        }
    }
}