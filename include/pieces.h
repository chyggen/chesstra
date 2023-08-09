#pragma once

#include <set>
#include "board.h"
#include "utils.h"

namespace ctra
{
    class board;

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
        black
    };

    // Base piece class. A square containing a piece of this class acts like an empty square
    class piece
    {
    public:
        
        piece(colour c);

        // piece is not default constructible
        piece() = delete;

        virtual std::set<ctra::square> getValidMoves(square loc, const board& boardRef) = 0;
        // virtual std::string algebraic(ctra::square); // gets a move in algebraic notation
        virtual std::string getDisplayChar() = 0; 
        virtual ctra::pieceID getPieceId() = 0; 
        virtual ~piece() {}

        ctra::colour getPieceColour();
        bool isWhite();

    protected:
        const ctra::colour m_colour; 
    };

    // helper function to create a new piece of a derived class type
    std::shared_ptr<ctra::piece> newPiece(pieceID id, colour c);

    // Specific (derived) piece classes

    class king : public piece
    {
    public:
        king(ctra::colour c);
        ~king() override;

        std::set<ctra::square> getValidMoves(square loc, const board& boardRef) override;
        std::string getDisplayChar() override;
        ctra::pieceID getPieceId() override;
    };

    class queen : public piece
    {
    public:
        queen(ctra::colour c);
        ~queen() override;

        std::set<ctra::square> getValidMoves(square loc, const board& boardRef) override;
        std::string getDisplayChar() override;
        ctra::pieceID getPieceId() override;
    };

    class rook : public piece
    {
    public:
        rook(ctra::colour c);
        ~rook() override;

        std::set<ctra::square> getValidMoves(square loc, const board& boardRef) override;
        std::string getDisplayChar() override;
        ctra::pieceID getPieceId() override;
    };

    class bishop : public piece
    {
    public:
        bishop(ctra::colour c);
        ~bishop() override;

        std::set<ctra::square> getValidMoves(square loc, const board& boardRef) override;
        std::string getDisplayChar() override;
        ctra::pieceID getPieceId() override;
    };

    class knight : public piece
    {
    public:
        knight(ctra::colour c);
        ~knight() override;

        std::set<ctra::square> getValidMoves(square loc, const board& boardRef) override;
        std::string getDisplayChar() override;
        ctra::pieceID getPieceId() override;
    };

    class pawn : public piece 
    {
    public:
        pawn(ctra::colour c);
        ~pawn() override;

        std::set<ctra::square> getValidMoves(square loc, const board& boardRef) override;
        std::string getDisplayChar() override;
        ctra::pieceID getPieceId() override;

        bool hasMoved() {return m_hasMoved;}

    private: 
        bool m_hasMoved;
    };

}