#include "pieces.h"
#include <iostream>
#include <fstream>

namespace ctra
{
    pawn::pawn(colour c) : piece(c) {}
    pawn::~pawn() {}

    std::set<square> pawn::getValidMoves(square loc, const board& boardRef,
            bool checkAttacks)
    {
        std::set<square> moves;
        std::pair<int,int> loc_coords = getCoords(loc);
        square tmp;

        std::ofstream oFile;
        oFile.open("pawnDebug.txt");

        // The pawn is the most unique piece in terms of movement. First, we need to determine 
        // what direction is considered forward:
        int forward = (boardRef.at(loc)->isWhite() ? 1 : -1);

        oFile << "forward: " << forward << std::endl;

        // Second, we check what non-capture options the pawn has. Since a pawn does not attack
        // straight forwards, only add these if we arent checking the pawn's attacks

        if (!checkAttacks)
        {
            // Check if the square directly in front of the pawn is empty:
            tmp = getSquare(loc_coords.first, loc_coords.second + forward);
            oFile << "tmp: " << static_cast<int>(tmp) << std::endl;
            if ((tmp != SQUARE_INVALID) && (boardRef.at(tmp) == nullptr))
            {
                moves.insert(tmp);
                // If the first square is empty, we can check if the pawn is on its starting rank
                int starting_y = (boardRef.at(loc)->isWhite() ? 1 : 6);
                if ((tmp != SQUARE_INVALID) && (loc_coords.second == starting_y))
                {
                    // If it is, check if the square two in front of the pawn is empty:
                    tmp = getSquare(loc_coords.first, loc_coords.second + 2 * forward);
                    if (boardRef.at(tmp) == nullptr)
                    {
                        moves.insert(tmp);
                    }
                }
            }
        }

        // Third, we check the pawn's capture options. These are the forward diagonals which are 
        // either occupied by an enemy piece or the board's en-passant target square. If we are 
        // checking attacks, these squares are always added if they are not invalid

        // First diagonal
        tmp = getSquare(loc_coords.first + 1, loc_coords.second + forward);
        if ((tmp != SQUARE_INVALID) && (
            (tmp == boardRef.enPassentTarget()) || checkAttacks || (
                (boardRef.at(tmp) != nullptr) && 
                (boardRef.at(tmp)->getPieceColour() != boardRef.at(loc)->getPieceColour()))
            ))
        {
            moves.insert(tmp);
        }

        // Second diagonal
        tmp = getSquare(loc_coords.first - 1, loc_coords.second + forward);
        if ((tmp != SQUARE_INVALID) && (
            (tmp == boardRef.enPassentTarget()) || checkAttacks ||(
                (boardRef.at(tmp) != nullptr) && 
                (boardRef.at(tmp)->getPieceColour() != boardRef.at(loc)->getPieceColour()))
            ))
        {
            moves.insert(tmp);
        }

        oFile << "moves: ";
        for (auto mov : moves)
        {
            oFile << static_cast<int>(mov);
        }
        oFile << std::endl;
        oFile.close();

        return moves;
    }

    std::string pawn::getDisplayChar()
    {
        if(m_colour == colour::white)
        {
            return std::string(u8"♙");
        }
        else
        {
            return std::string(u8"♟︎");
        }
    }

    ctra::pieceID pawn::getPieceId()
    {
        return pieceID::pawn;
    }
} 