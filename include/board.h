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

    // movePiece return type to indicate reason for a failed move
    enum class moveResult
    {
        // attempt to move a white piece on black's turn, or vice-versa
        WRONG_TURN = -1,

        // attempt to capture a friendly piece
        FRIENDLY_CAPTURE = -2,

        // no piece exists on the source square
        EMPTY_SRC = -3,

        // attempt to move a piece to the same square it started on
        SAME_SRC_DEST = -4,

        // requested move violates other chess rules
        ILLEGAL = -5,

        // valid move 
        OKAY = 0
    };

    bool isLegal(moveResult r);

    class board
    {
    public:

        board();
        ~board();

        std::string exportFen() const; 
        bool importFen(std::string fen);
        std::shared_ptr<ctra::piece> at(ctra::square sq) const;
        std::shared_ptr<ctra::piece> at(int x, int y) const;
        bool assignPiece(ctra::pieceID id, ctra::colour c, ctra::square sq);
        moveResult movePiece(ctra::square src, ctra::square dest);

        // getters
        bool whiteToMove(){return m_whiteToMove;}
        unsigned int fullmoveCounter(){return m_fullmoveCounter;}

    private:

        // ctra::game& m_gameRef;

        // Fen Fields
        std::array<std::shared_ptr<ctra::piece>, 64> m_placement;
        bool m_whiteToMove;
        std::set<char> m_castlingRights;
        ctra::square m_enPassantTarget;
        unsigned int m_halfmoveClock;
        unsigned int m_fullmoveCounter;

        // Other usefull fields for move logic
        bool m_wasPromotion;

        void updateBoardFlags(ctra::square src, ctra::square dest);

        
    };

    ctra::square getSquare(int x, int y); 
    std::pair<int,int> getCoords(ctra::square sq); 
}