#pragma once

#include <set>

namespace ctra
{
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

    // structure which describes what pieces attack a square
    struct sqaureAttackStats
    {
        bool white; // true if attacked by white
        bool black; // true if attacked by black

        // contains the squares of the pieces which attack this square.
        std::set<square> attackedBy; 

        void reset() 
        {
            white = false;
            black = false;
            attackedBy.clear();
        }
    };

    // structure which describes algebraic move notation modifiers
    struct algebraicNotationFlags
    {
        bool isCapture;
        bool isCheck;
        bool isMate;
        bool isPromotion;
        bool disambiguateWithX;
        bool disambiguateWithY;
        bool isQCastle;
        bool isKCastle;
    };

    
}   


