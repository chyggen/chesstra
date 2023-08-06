#pragma once

#include <string>
#include <array>
#include <memory>
#include "pieces.h"

namespace ctra
{
    // ctra class definitions
    class piece;
    class game;
    enum class pieceID;
    enum class colour;

    enum square
    {
        A8=0, B8, C8, D8, E8, F8, G8, H8,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A1, B1, C1, D1, E1, F1, G1, H1,
        SQUARE_INVALID
    };

    class board
    {
    public:

        board();
        ~board();

        std::string exportFen() const; 
        bool importFen(std::string fen);
        std::shared_ptr<ctra::piece> at(ctra::square sq) const;
        std::shared_ptr<ctra::piece> at(int x, int y) const;
        bool assignEmpty(ctra::pieceID id, ctra::colour c, ctra::square sq);

    private:

        // ctra::game& m_gameRef;

        // Fen Fields
        std::array<std::shared_ptr<ctra::piece>, 64> m_placement;
        bool m_whiteToMove;
        std::set<char> m_castlingRights;
        ctra::square m_enPassantTarget;
        unsigned int m_halfmoveClock;
        unsigned int m_fullmoveCounter;
        
    };

    constexpr ctra::square getSquare(int x, int y); 
}