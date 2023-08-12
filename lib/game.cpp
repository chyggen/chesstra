#include "game.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <stdexcept>

namespace ctra
{
    game::~game() 
    {
        if (autoSave)
        {
            exportPGN();
        }
    }
    
    void game::start()
    {
        try
        {
            board.init(fen);
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "invalid FEN" << std::endl;
            return;
        }
        
        disp.updateBoard(board);
        writeGameStatus(board.fullmoveCounter(), board.whiteToMove());
        
        // loop until the quit command is received
        for (;;)
        {
            // Blocking read
            std::string str = disp.readUserInput();
            command c = command_parser::identifyCommand(str);

            if (c == command::QUIT)
            {
                return;
            }
            else if (c == command::INVALID)
            {
                disp.writeUserOutput("command not recognized");
            }
            else if (c == command::MOVE_TWO_SQUARE)
            {
                if (status == gameStatus::IN_PROG)
                {
                    auto sq_pair = command_parser::parseTwoSquare(str);
                    moveResult move_res = board.movePiece(sq_pair.first, sq_pair.second);
                    if (isLegal(move_res)) 
                    {
                        // write to movetext
                        if (!board.whiteToMove())
                        {
                            moveText << board.fullmoveCounter() << ". " << 
                            algebraicMove(sq_pair.first, sq_pair.second) << " ";
                        }
                        else
                        {
                            moveText << algebraicMove(sq_pair.first, sq_pair.second) << " ";
                        }

                        disp.writeUserOutput("valid move"); 

                        // if a checkmate happened, end the game
                        if (board.algFlags().isMate)
                        {
                            status = gameStatus::CHECKMATE;
                            moveText << getResultStr();
                        }
                    }
                    else 
                    {
                        disp.writeUserOutput("invalid move"); 
                    }
                    disp.updateBoard(board);
                    writeGameStatus(board.fullmoveCounter(), board.whiteToMove());
                }
                else
                {
                    disp.writeUserOutput("cannot move pieces, game is over");
                }
            }
            else if (c == command::GAME_RESIGN)
            {
                if (status == gameStatus::IN_PROG)
                {
                    status = gameStatus::RESIGNATION;
                    moveText << getResultStr();
                    writeGameStatus(board.fullmoveCounter(), board.whiteToMove());

                }
                else
                {
                    disp.writeUserOutput("cannot resign, game is over");
                }
            }
            else if (c == command::GAME_DRAW)
            {
                if (status == gameStatus::IN_PROG)
                {
                    status = gameStatus::DRAW_AGREEMENT;
                    moveText << getResultStr();
                    writeGameStatus(board.fullmoveCounter(), board.whiteToMove());

                }
                else
                {
                    disp.writeUserOutput("cannot draw, game is over");
                }
            }
            else if (c == command::MOVE_COMMENT)
            {
                moveText << " {" << str.substr(4) << "} ";
                disp.writeUserOutput("comment added");
            }
            else if (c == command::GET_PGN)
            {
                exportPGN();
            }
            else
            {
                std::stringstream ss;
                ss << "command unimplemented";
                disp.writeUserOutput(ss.str());
            }
        }
    }

    void game::writeGameStatus(unsigned int fullmoveCount, bool whiteToMove)
    {
        std::stringstream msg;
        msg << fullmoveCount << ". ";
        switch (status)
        {
            case game::gameStatus::IN_PROG:
                msg << (whiteToMove ? "White to move" : "Black to move");
                break;

            case game::gameStatus::CHECKMATE:
            case game::gameStatus::RESIGNATION:
                msg << (whiteToMove ? "Black is victorious!" : "White is victorious!");
                break;

            case game::gameStatus::DRAW_AGREEMENT:
                msg << "Game drawn by agreement";
                break;
        }
        disp.writeGameStatus(msg.str());
    }

    std::string game::getResultStr()
    {
        switch (status)
        {
            case gameStatus::IN_PROG:
                return "*";
            case gameStatus::CHECKMATE:
            case gameStatus::RESIGNATION:
                return board.whiteToMove() ? "0-1" : "1-0";
            case gameStatus::DRAW_AGREEMENT:
                return "1/2-1/2";
            default:
                return "?";
        }
    }

    bool game::exportPGN()
    {
        std::string resultStr = getResultStr();
        // cannot use "/" character in filenames, so if draw must rename result str
        if (resultStr == "1/2-1/2")
        {
            resultStr = "draw";
        }

        std::string plyCount = std::to_string(
            2 * board.fullmoveCounter() - (board.whiteToMove() ? 2 : 1));

        std::string filename =  eventName + "_" + whiteName + "v" + blackName + "_" + 
                                resultStr + "_" + plyCount + ".pgn"; 

        std::ofstream pgnFile(filename);

        if (pgnFile.is_open()) 
        {
            // File opened successfully, write pgn data to it

            // Get the current time
            std::time_t currentTime;
            std::time(&currentTime);

            // Convert the time to a local time struct
            std::tm* localTime = std::localtime(&currentTime);

            // Extract date components
            int year = localTime->tm_year + 1900; // Years since 1900
            int month = localTime->tm_mon + 1;    // Months are 0-based
            int day = localTime->tm_mday;

            // step 1: write tag pairs
            pgnFile << "[Event \"" << eventName << "\"]\n";
            pgnFile << "[Site \"ChessTra Analysis\"]\n";
            pgnFile << "[Date \"" << year << "." << month << "." << day << "\"]\n";
            pgnFile << "[Round \"?\"]\n";
            pgnFile << "[White \"" << whiteName << "\"]\n";
            pgnFile << "[Black \"" << blackName << "\"]\n";
            pgnFile << "[Result \"" << resultStr << "\"]\n";
            pgnFile << "[PlyCount \"" << plyCount << "\"]\n";
            // if game started from fen, add fen string
            if (startFromFen)
            {
                pgnFile << "[FEN \"" << fen << "\"]\n";
            }

            pgnFile << std::endl;

            // step 2: write moves
            pgnFile << moveText.str();

            pgnFile.close();
            return true;
        } 
        else 
        {
            // Failed to open the file
            return false;
        }
    }

    std::string game::algebraicMove(square src, square dest)
    {
        algebraicNotationFlags flags = board.algFlags();
        std::string str = "";
        
        // If the move is a castle, we ignore most steps
        if (flags.isQCastle)
        {
            str += "O-O-O";
        }
        if (flags.isKCastle)
        {
            str += "O-O";
        }
        else
        {
            // Not a castle, start with piece identifier
            switch (board.at(dest)->getPieceId())
            {
                case pieceID::king:
                   str += "K";
                   break; 
                case pieceID::queen:
                   str += "Q";
                   break; 
                case pieceID::rook:
                   str += "R";
                   break; 
                case pieceID::bishop:
                   str += "B";
                   break; 
                case pieceID::knight:
                   str += "N";
                   break;
                // no identifier for pawns
            }

            // Next is disambiguation mofifiers
            if(flags.disambiguateWithX)
            {
                str += (getCoords(src).first + 'a');
            }
            if(flags.disambiguateWithY)
            {
                str += (getCoords(src).second + '1');
            }

            // Next is capture mofifier 
            if(flags.isCapture)
            {
                str += "x";
            }

            // Next is destination square
            str += (getCoords(dest).first + 'a');
            str += (getCoords(dest).second + '1');

            // Next is promotions
            if(flags.isPromotion)
            {
                // only queen promotions supported
                str += "=Q";
            }
        }
        
        // last is check / checkmate 
        if (flags.isCheck)
        {
            str += "+";
        }
        else if(flags.isMate)
        {
            str += "#";
        }

        return str;
    }

}