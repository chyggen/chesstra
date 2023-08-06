#pragma once

#include <set>
#include "board.h"

namespace ctra
{
    enum class pieceID
    {
        pawn,
        bishop,
        knight, 
        rook,
        king,
        queen,
        empty
    };

    enum class colour
    {
        white,
        black,
        empty
    };


    // Base piece class. A square containing a piece of this class acts like an empty square
    class piece
    {
    public:
        
        piece(colour c);

        // piece() = delete;

        // virtual std::set<ctra::square> getValidMoves();
        // virtual bool move(ctra::square); // move a piece to specified square
        // virtual std::string algebraic(ctra::square); // gets a move in algebraic notation
        virtual std::string getDisplayChar() = 0; 
        virtual ctra::pieceID getPieceId() = 0; 
        virtual ~piece() {}


    protected:
        // ctra::board& m_board;
        const ctra::colour m_colour; 
        // ctra::square m_location;
    };

    

    // Specific piece classes

    class king : public piece
    {
    public:
        king(ctra::colour c);
        ~king() override;

        std::string getDisplayChar() override;
        ctra::pieceID getPieceId() override;
    };

    class queen : public piece
    {
        queen(ctra::colour c);
    };

    class rook : public piece
    {
        rook(ctra::colour c);
    };

    class bishop : public piece
    {
        bishop(ctra::colour c);
    };

    class knight : public piece
    {
        knight(ctra::colour c);
    };

    class pawn : public piece 
    {
        pawn(ctra::colour c);
    };

    std::shared_ptr<ctra::piece> newPiece(pieceID id, colour c);
    
}