#include <string>
#include <board.h>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdio>

namespace ctra
{
    bool isLegal(moveResult r)
    {
        return static_cast<int>(r) >= 0;
    }

    void board::init(const std::string& fen)
    {
        if (!importFen(fen))
        {
            throw std::runtime_error("Invalid Fen");
        }
    }

    bool board::importFen(const std::string& fen)
    {
        // find the locations of the seperating spaces
        std::size_t space1 = fen.find(' ');
        std::size_t space2 = fen.find(' ', space1 + 1);
        std::size_t space3 = fen.find(' ', space2 + 1);
        std::size_t space4 = fen.find(' ', space3 + 1);
        std::size_t space5 = fen.find(' ', space4 + 1); 
        std::size_t fenEnd = fen.find(' ', space5 + 1); // should be npos if the fen is valid

        if (space1 == std::string::npos || space2 == std::string::npos ||
            space3 == std::string::npos || space4 == std::string::npos ||
            space5 == std::string::npos || fenEnd != std::string::npos) 
        {
            // incorrect number of space, invalid FEN
            return false; 
        }

        // step 1: parse piece placement
        int rank = 7, file = 0;
        for (int i = 0; i < space1; ++i)
        {
            char ch = fen[i];

            if (ch == '/') 
            {
                if (file != 8)
                {
                    // not 8 pieces in a rank, invalid FEN
                    return false;
                }
                rank--;
                file = 0; 
            }
            else if (isdigit(ch)) 
            {
                file += ch - '0';
            } 
            else if (isalpha(ch)) 
            {
                pieceID p = fenCharToPieceId(ch);
                if (p == pieceID::INVALID)
                {
                    // not a valid FEN char, invalid FEN
                    return false;
                }
                colour c = isupper(ch) ? colour::white : colour::black;
                square sq = getSquare(file,rank);
                assignPiece(p, c, sq);
                file++;
            }
            else // found invalid characters
            {
                return false;
            } 
        }

        // step 2: parse active player
        if (fen[space1 + 1] == 'w')
        {
            m_whiteToMove = true;
        }
        else if (fen[space1 + 1] == 'b')
        {
            m_whiteToMove = false; 
        }
        else
        {
            // invalid active player char, invalid FEN
            return false;
        }

        // step 3: parse castling rights
        for (int i = space2 + 1; i < space3; ++i)
        {   
            // valid options
            if (fen[i] == 'K' ||  fen[i] == 'Q' || fen[i] == 'k' || fen[i] == 'q' )
            {
                m_castlingRights.insert(fen[i]);
            }
            else if (fen[i] != '-') // '-' indicates no castling rights, only other valid char
            {
                // invalid character for castling rights, invalid FEN
                return 0;
            }
        }

        // step 4: parse en-passant square
        if (fen[space3 + 1] == '-')
        {
            m_enPassantTarget = SQUARE_INVALID;
        }
        else 
        {
            char x = fen[space3 + 1] - 'a';
            char y = fen[space3 + 2] - '1';
            square sq = getSquare(x, y);
            if (sq != SQUARE_INVALID)
            {
                m_enPassantTarget = sq;
            }
            else
            {
                // invalid en-passant sqaure, invalid FEN
                return false;
            }
        }
                                            
        // steps 5 & 6: parse half-move clock and full-move number
        if (!std::sscanf(fen.c_str() + space4 + 1, "%d %d", &m_halfmoveClock,  &m_fullmoveCounter))
        {
            // Failed to parse half-move clock and full-move number, invalid FEN
            return false;
        }

        // If this point is reached, we have a valid FEN
        return true;
    }

    std::string board::generateFEN() const 
    {
        std::string fen = "";
        int emptyCount = 0;

        // step 1: generate position field
        for (int rank = 0; rank < 8; ++rank) 
        {
            for (int file = 0; file < 8; ++file) 
            {
                if (at(file, rank) != nullptr)
                {
                    if (emptyCount > 0) {
                        fen += std::to_string(emptyCount);
                        emptyCount = 0;
                    }
                    pieceID p = at(file, rank)->getPieceId();
                    colour c = at(file, rank)->getPieceColour();
                    fen += pieceIdToFenChar(p, c);
                }
                else {
                    emptyCount++;
                }
            }
            if (emptyCount > 0) 
            {
                fen += std::to_string(emptyCount);
                emptyCount = 0;
            }
            if (rank != 7) 
            {
                fen += "/";
            }
        }
        fen += " ";

        // step 2: generate active player
        fen += m_whiteToMove ? "w " : "b ";

        // step 3: generate castling rights
        if (m_castlingRights.empty())
        {
            fen += "-";
        }
        else
        {
            for (char c : m_castlingRights)
            {
                fen += c;
            }
        }
        fen += " ";
        
        // step 4: generate en passant target
        if (m_enPassantTarget != SQUARE_INVALID)
        {
            std::pair<int,int> coords = getCoords(m_enPassantTarget);
            fen += static_cast<char>(coords.first + 'a');
            fen += static_cast<char>(coords.second + '1');
        }
        else
        {
            fen += "-";
        }
        fen += " ";

        // step 5: generate halfmove clock
        fen += std::to_string(m_halfmoveClock);
        fen += " ";


        //step 6: generate fullmove counter
        fen += std::to_string(m_fullmoveCounter);
        fen += " ";

        return fen;
    }

    std::shared_ptr<ctra::piece> board::at(ctra::square sq) const
    {
        int index = static_cast<int>(sq);
        if (index >= 0 && index < 64)
        {
            return m_placement[index];
        }
        else
        {
            throw std::runtime_error("invalid square provided to board::at");
        }
    }

    std::shared_ptr<ctra::piece> board::at(int x, int y) const
    {
        int index = 8 * y + x;
        if (index >= 0 && index < 64)
        {
            return m_placement[index];
        }
        else
        {
            throw std::runtime_error("invalid coords provided to board::at");
        }
    }

    bool board::removePiece(square sq)
    {
        int index = static_cast<int>(sq);
        if (index >= 0 && index < 64)
        {
            if (m_placement[index] != nullptr)
            {
                m_placement[index].reset();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            throw std::runtime_error("invalid square provided to removePiece");
        }
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
                m_placement[index] = newPiece(id, c);
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
        postMoveUpdates(src, dest);

        // Update some fen fields 

        return moveResult::OKAY;
    }

    void board::updateBoardFlags(ctra::square src, ctra::square dest)
    {
        // If it was black's turn, update the fullmove count
        m_fullmoveCounter += (!m_whiteToMove ? 1 : 0);

        // Switch turns
        m_whiteToMove = !m_whiteToMove;

        // update the halfmove clock
        if (at(src)->getPieceId() == pieceID::pawn || 
            at(dest) != nullptr)
        {
            // on pawn moves or captures, reset the clock
            m_halfmoveClock = 0;
        }
        else
        {
            // On other moves, increment the clock
            ++m_halfmoveClock;
        }
    }

    void board::postMoveUpdates(square src, square dest)
    {
        // If the king is moving, we must remove castling rights and check if the move itself is a castle
        if (at(dest)->getPieceId() == pieceID::king)
        {
            // check if the king is on the starting square 
            if (at(dest)->isWhite() && src == E1)
            {
                // check if the king is moving to a castling position
                if (dest == G1)
                {
                    m_placement[F1] = std::move(m_placement[H1]);
                }
                else if (dest == C1)
                {
                    m_placement[D1] = std::move(m_placement[A1]);
                }
                // otherwise, no castle has occured. 
                // in any case, we remove white's castling rights:
                m_castlingRights.erase('K');
                m_castlingRights.erase('Q');
            }
            // do the same for black
            if (!at(dest)->isWhite() && src == E8)
            {
                if (dest == G8)
                {
                    m_placement[F8] = std::move(m_placement[H8]);
                }
                else if (dest == C8)
                {
                    m_placement[D8] = std::move(m_placement[A8]);
                }
                m_castlingRights.erase('k');
                m_castlingRights.erase('q');
            }
        }

        // If a rook is moving from its starting square, we must remove castling rights
        if (at(dest)->getPieceId() == pieceID::rook)
        {
            if (at(dest)->isWhite())
            {
                if (src == H1)
                {
                    m_castlingRights.erase('K');
                }
                else if (src == A1)
                {
                    m_castlingRights.erase('Q');
                }
            }
            else  
            {
                if (src == H8)
                {
                    m_castlingRights.erase('k');
                }
                else if (src == A8)
                {
                    m_castlingRights.erase('q');
                }

            }
        }

        // If a pawn is moving, there are several cases to check:
        if (at(dest)->getPieceId() == pieceID::pawn)
        {
            int srcx = getCoords(src).first;
            int srcy = getCoords(src).second;
            int destx = getCoords(dest).first;
            int desty = getCoords(dest).second;
            
            // If a pawn is moving to the en-passant target, we must capture (remove) 
            // the pawn in front of the target
            if(dest == m_enPassantTarget)
            {
                if (at(dest)->isWhite())
                {
                    removePiece(getSquare(destx, desty - 1));
                }
                else
                {
                    removePiece(getSquare(destx, desty + 1));
                }
            }

            // If a pawn moves two squares, we must add en-passant target
            if (at(dest)->isWhite() && desty == 3 && srcy == 1)
            {
                // target will be the sqaure behind the destination
                m_enPassantTarget = getSquare(destx, 2);
            }
            else if (!at(dest)->isWhite() && desty == 4 && srcy == 6)
            {
                // target will be the sqaure behind the destination
                m_enPassantTarget = getSquare(destx, 5);
            }
            else
            {
                // if no pawn moved two squares, remove the en-passant target
                m_enPassantTarget = SQUARE_INVALID;
            }

            // If a pawn reaches the back rank, auto-promote to a queen 
            // (other promotion types are not currently supported)
            if (at(dest)->isWhite() && desty == 7)
            {
                assignPiece(pieceID::queen, colour::white, dest);
            }
            else if (!at(dest)->isWhite() && desty == 0)
            {
                assignPiece(pieceID::queen, colour::black, dest);
            }
        }
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