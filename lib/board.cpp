#include <string>
#include <board.h>
#include <iostream>
#include <stdexcept>
#include <cassert>

namespace ctra
{

    board::board()
    {
        // for (int i = 0; i < m_placement.size(); ++i)
        // {
        //     m_placement[i] = std::make_shared<piece>(ctra::colour::empty);
        // }
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

    bool board::movePiece(ctra::square src, ctra::square dest)
    {
        int src_index = static_cast<int>(src);
        int dest_index = static_cast<int>(dest);
        if (src_index >= 0 && src_index < 64 &&
            dest_index >= 0 && dest_index < 64)
        {
            if ((m_placement[src] != nullptr) && (src != dest))
            {
                m_placement[dest] = std::move(m_placement[src]);
                assert(m_placement[src] == nullptr);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            throw std::runtime_error("invalid square provided to movePiece");
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
}