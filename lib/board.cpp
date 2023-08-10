#include <string>
#include <board.h>
#include <iostream>
#include <stdexcept>
#include <cassert>

namespace ctra
{

    bool isLegal(moveResult r)
    {
        return static_cast<int>(r) >= 0;
    }

    board::board()
    {
        // fill the board in the default position
        assignPiece(ctra::pieceID::rook,      ctra::colour::white, ctra::A1);
        assignPiece(ctra::pieceID::knight,    ctra::colour::white, ctra::B1);
        assignPiece(ctra::pieceID::bishop,    ctra::colour::white, ctra::C1);
        assignPiece(ctra::pieceID::queen,     ctra::colour::white, ctra::D1);
        assignPiece(ctra::pieceID::king,      ctra::colour::white, ctra::E1);
        assignPiece(ctra::pieceID::bishop,    ctra::colour::white, ctra::F1);
        assignPiece(ctra::pieceID::knight,    ctra::colour::white, ctra::G1);
        assignPiece(ctra::pieceID::rook,      ctra::colour::white, ctra::H1);

        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::A2);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::B2);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::C2);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::D2);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::E2);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::F2);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::G2);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::white, ctra::H2);

        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::A7);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::B7);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::C7);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::D7);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::E7);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::F7);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::G7);
        assignPiece(ctra::pieceID::pawn,      ctra::colour::black, ctra::H7);

        assignPiece(ctra::pieceID::rook,      ctra::colour::black, ctra::A8);
        assignPiece(ctra::pieceID::knight,    ctra::colour::black, ctra::B8);
        assignPiece(ctra::pieceID::bishop,    ctra::colour::black, ctra::C8);
        assignPiece(ctra::pieceID::queen,     ctra::colour::black, ctra::D8);
        assignPiece(ctra::pieceID::king,      ctra::colour::black, ctra::E8);
        assignPiece(ctra::pieceID::bishop,    ctra::colour::black, ctra::F8);
        assignPiece(ctra::pieceID::knight,    ctra::colour::black, ctra::G8);
        assignPiece(ctra::pieceID::rook,      ctra::colour::black, ctra::H8);

        // set the FEN fields for the starting position
        m_whiteToMove = true;
        m_castlingRights = {'K', 'Q', 'k', 'q'};
        m_enPassantTarget = SQUARE_INVALID;
        m_halfmoveClock = 0;
        m_fullmoveCounter = 1;

    }

    board::~board()
    {
        // for (int y = 0; y < 8; ++y)
        // {
        //     for (int x = 0; x < 8; ++x)
        //     {
        //         if (m_placement[getSquare(x,y)] != nullptr)
        //         {
        //             m_placement[getSquare(x,y)].reset();
        //         }
        //     }
        // }
    }

    std::shared_ptr<ctra::piece> board::at(ctra::square sq) const
    {
        int index = static_cast<int>(sq);
        if (index >= 0 && index < 64)
        {
            std::cout << m_placement[index] << std::endl;
            return m_placement[index];
        }
        else
        {
            throw std::runtime_error("invalid square provided to board::at");
        }
            
    }

    std::shared_ptr<ctra::piece> board::at(int x, int y) const
    {
        return m_placement[8*y +x];
    }

    bool board::assignPiece(ctra::pieceID id, ctra::colour c, ctra::square sq)
    {
        int index = static_cast<int>(sq);
        if (index >= 0 && index < 64)
        {
            if (m_placement[index] == nullptr)
            {
                m_placement[index] = newPiece(id, c);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            throw std::runtime_error("invalid square provided to assignPiece");
        }
    }

    moveResult board::movePiece(ctra::square src, ctra::square dest)
    {
        int src_index = static_cast<int>(src);
        int dest_index = static_cast<int>(dest);

        // Throw if the src or dest squares are invalid
        if (src_index < 0 || src_index > 63)
        {
            throw std::runtime_error("invalid src square provided to movePiece");
        }
        if (dest_index < 0 || dest_index > 63)
        {
            throw std::runtime_error("invalid dest square provided to movePiece");
        }

        // Check some invalid move cases
        if (m_placement[src] == nullptr)
        {
            return moveResult::EMPTY_SRC;
        }
        if (src == dest)
        {
            return moveResult::SAME_SRC_DEST;
        }
        if (m_placement[src]->isWhite() != m_whiteToMove)
        {
            return moveResult::WRONG_TURN;
        }
        if (m_placement[dest] != nullptr && (
            m_placement[src]->getPieceColour() == 
            m_placement[dest]->getPieceColour())
        )
        {
            return moveResult::FRIENDLY_CAPTURE;
        }
        if (!m_placement[src]->getValidMoves(src, *this).count(dest))
        {
            return moveResult::ILLEGAL;
        }

        // TODO: check if the move is actually legal within chess rules

        // If no invalid move cases were triggered, update the board flags and move the piece
        updateBoardFlags(src, dest);
        m_placement[dest] = std::move(m_placement[src]);

        // Update some fen fields 

        return moveResult::OKAY;
    }

    void board::updateBoardFlags(ctra::square src, ctra::square dest)
    {
        // If it was black's turn, update the fullmove count
        m_fullmoveCounter += (!m_whiteToMove ? 1 : 0);

        m_whiteToMove = !m_whiteToMove;
    }

    void board::updateAttackStats()
    {
        // First, clear the previous attack stats
        for (int i = 0; i < 64; ++i)
        {    
            m_attackStats[i].reset();
        }

        for (int i = 0; i < 64; ++i)
        {
            square sq = static_cast<square>(i);

            //if theres a piece on the square 
            if (m_placement[sq] != nullptr)
            {
                // add the sqaures the piece is attacking to the attackStats
                for (square mov : m_placement[sq]->getValidMoves(sq, *this, true))
                {
                    m_attackStats[mov].attackedBy.insert(sq);
                    if (m_placement[sq]->isWhite())
                    {
                        m_attackStats[mov].white = true;
                    }
                    else
                    {
                        m_attackStats[mov].black = true;
                    }
                }
            }
        }
    }

    ctra::square getSquare(int x, int y) 
    {
        if( x > 7 || x < 0 || y > 7 || y < 0 )
        {
            return SQUARE_INVALID;
        }
        else
        {
            return static_cast<ctra::square>(8*(7-y) + x);
        }
    }

    std::pair<int,int> getCoords(ctra::square sq)
    {
        int idx = static_cast<int>(sq);
        if (idx >= 0 && idx < 64)
        {
            int x = idx % 8;
            int y = 7 - (idx / 8);
            return std::pair<int,int>(x,y);
        } 
        else
        {
            return std::pair<int,int>(-1,-1);
        }
    }
}