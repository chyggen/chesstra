#pragma once

#include <string>
#include <array>
#include <memory>
#include "pieces.h"
#include "utils.h"

namespace ctra
{
    // ctra class definitions
    class piece;
    enum class pieceID;
    enum class colour;

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
        board(const std::string& fen);

        ~board();

        std::string exportFen() const; 
        bool importFen(const std::string& fen);
        std::shared_ptr<piece> at(square sq) const;
        std::shared_ptr<piece> at(int x, int y) const;
        bool assignPiece(pieceID id, colour c, square sq);
        moveResult movePiece(square src, square dest);

        // getters
        bool whiteToMove() const {return m_whiteToMove;}
        square enPassentTarget() const {return m_enPassantTarget;}
        unsigned int fullmoveCounter() const {return m_fullmoveCounter;}
        sqaureAttackStats attackStats(square sq) const {return m_attackStats[sq];}

    private:

        // game& m_gameRef;

        // Fen Fields
        std::array<std::shared_ptr<piece>, 64> m_placement;
        bool m_whiteToMove;
        std::set<char> m_castlingRights;
        square m_enPassantTarget;
        unsigned int m_halfmoveClock;
        unsigned int m_fullmoveCounter;

        // Other usefull fields for move logic
        bool m_wasPromotion;
        std::array<sqaureAttackStats, 64> m_attackStats;
        
        void updateBoardFlags(square src, square dest);

        void updateAttackStats();
        
    };

    square getSquare(int x, int y); 
    std::pair<int,int> getCoords(square sq); 
    

}