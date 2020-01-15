#include "JetanAlphaBeta.h"
#include <cstdio>
#include <chrono>

namespace ai
{
namespace Jetan
{

const double MY_INFINITY = 1.e10;
std::chrono::duration<double> TOTAL_TIME = std::chrono::duration<double>(0);

PlyData::PlyData(double utility_in)
    : move_ok(false),
      utility(utility_in)
{
}

AlphaBeta::AlphaBeta(ai::Agent::Options *opts)
    : max_depth(3), // always choose odd
      evaluation_method(PIECE_COUNT),
      //warrior, padwar, dwar, flyer, chief, princess, thoat, panthan
      pieceArray{2, 2, 2, 3, 2, 2, 2, 2}
{
    if (opts->GetArgInt("user1") > 0)
    { // -U --user1
        this->max_depth = opts->GetArgInt("user1");
    }
    if (opts->GetArgInt("user2") > 0)
    { // -V --user2
        this->evaluation_method = static_cast<EvaluationOption>(opts->GetArgInt("user2"));
    }
    std::stringstream ss;
    ss << "AlphaBeta";
    ss << "-d" << this->max_depth;
    ss << "-e" << this->evaluation_method;
    SetName(ss.str());
}

AlphaBeta::~AlphaBeta()
{
}

ai::Agent::Action *AlphaBeta::Program(const ai::Agent::Percept *percept)
{

    ai::Jetan::Action *action = new ai::Jetan::Action;

    std::string board_str = percept->GetAtom("BOARD").GetValue();
    ai::Jetan::Board board(board_str);

    int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

    PlyData ply_data = this->PickMove(board, player);

    if (ply_data.move_ok)
    {
        action->SetCode(ai::Jetan::Action::MOVE);
        action->SetMove(ply_data.move);
    }
    else
    {
        action->SetCode(ai::Jetan::Action::QUIT);
    }

    return action;
}

PlyData AlphaBeta::PickMove(const ai::Jetan::Board &board, int player)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    PlyData ply_data = this->Max(board, player, 1, -MY_INFINITY, MY_INFINITY);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    TOTAL_TIME += time_span;
    return ply_data;
}

PlyData AlphaBeta::Max(const ai::Jetan::Board &board, int player, int depth, double alpha, double beta)
{
    PlyData ply_data(-MY_INFINITY);
        if (TOTAL_TIME > std::chrono::duration<double>(595))
    {
        max_depth = 1;
    }
    else if (TOTAL_TIME > std::chrono::duration<double>(590))
    {
        max_depth = 2;
    }
    else if (TOTAL_TIME > std::chrono::duration<double>(500))
    {
        max_depth = 3;
    }
    // else if (TOTAL_TIME <= std::chrono::duration<double>(.1))
    // {
    //     max_depth = 4;
    // }
        else if (TOTAL_TIME <= std::chrono::duration<double>(50))
    {
        max_depth = 5;
    }
    else if (TOTAL_TIME <= std::chrono::duration<double>(150))
    {
        max_depth = 6;
    }
    else if (TOTAL_TIME <= std::chrono::duration<double>(450))
    {
        max_depth = 5;
    }
    else if (TOTAL_TIME <= std::chrono::duration<double>(500))
    {
        max_depth = 4;
    }
    if (board.HaveWinner() || depth > this->max_depth)
    {
        ply_data.utility = this->Evaluate(board, player);
        return ply_data;
    }
    double zed = depth * .001;

    ai::Jetan::Board my_board(board);
    const std::vector<ai::Jetan::MoveData> &moves = my_board.DetermineLegalMoves(player);
    int other_player = (player == 1) ? 2 : 1;
    otherAttacked.clear();
    myAttacked.clear();
    my_board.DetermineAttackedLocations(player, otherAttacked);
    my_board.DetermineAttackedLocations(other_player, myAttacked);
    PlyData tmp_ply_data(-MY_INFINITY);
    int i;
    if (depth == 1)
    {
        std::vector<PlyData> best_plys;
        best_plys.clear();

        for (i = 0; i < (int)moves.size(); i++)
        {
            const BoardData &bd = my_board.GetBoard(); // get the copied board's data
            int tx = moves[i].piece.x;
            int ty = moves[i].piece.y;
            // is this piece that moved a princess
            if (bd.pieces[int(bd.squares[ty][tx])].mType == ai::Jetan::Piece::PRINCESS)
            {
                if (myAttacked.count(bd.pieces[int(bd.squares[ty][tx])].mLocation) == 0)
                {
                    continue; // next node skips her moves
                }
            }
            ai::Jetan::Board tmp_board(board);
            tmp_board.Move(player, moves[i]);

            tmp_ply_data = this->Min(tmp_board, player, depth + 1, alpha, beta);
            if (tmp_ply_data.utility > ply_data.utility)
            {
                ply_data.utility = tmp_ply_data.utility;
                ply_data.move = moves[i];
                ply_data.move_ok = true;

                best_plys.clear();
                best_plys.push_back(ply_data);

                if (ply_data.utility > beta)
                { /* parent node has a better (or equal) child, so this node will not be chosen */
                    break;
                }
                if (ply_data.utility > alpha)
                {
                    alpha = ply_data.utility;
                }
            }
            else if (tmp_ply_data.utility == ply_data.utility)
            {
                PlyData t(-MY_INFINITY);
                t.utility = tmp_ply_data.utility;
                t.move = moves[i];
                t.move_ok = true;
                best_plys.push_back(t);
            }
        }
        if (best_plys.size() == 0)
        {
            return tmp_ply_data;
        }
        return best_plys[rand() % best_plys.size()];
    }
    //////////////////////////////////////////////////////
    for (i = 0; i < (int)moves.size(); i++)
    {
        const BoardData &bd = my_board.GetBoard(); // get the copied board's data
        int tx = moves[i].piece.x;
        int ty = moves[i].piece.y;
        // is this piece that moved a princess
        if (bd.pieces[int(bd.squares[ty][tx])].mType == ai::Jetan::Piece::PRINCESS)
        {
            if (myAttacked.count(bd.pieces[int(bd.squares[ty][tx])].mLocation) == 0)
            {
                continue; // next node skips her moves
            }
        }
        ai::Jetan::Board tmp_board(board);
        tmp_board.Move(player, moves[i]);

        PlyData tmp_ply_data = this->Min(tmp_board, player, depth + 1, alpha, beta);
        if (tmp_ply_data.utility * (1 - zed) > ply_data.utility) // if current utility is greater than saved
        {
            ply_data.utility = tmp_ply_data.utility * (1 - zed); // update the utility
            ply_data.move = moves[i];                            // save the current move into moves[i]
            ply_data.move_ok = true;
            if (ply_data.utility >= beta)
            { /* parent node has a better (or equal) child, so this node will not be chosen */
                break;
            }
            if (ply_data.utility > alpha)
            {
                alpha = ply_data.utility;
            }
        }
    }
    return ply_data;
}

PlyData AlphaBeta::Min(const ai::Jetan::Board &board, int player, int depth, double alpha, double beta)
{
    PlyData ply_data(MY_INFINITY);
        if (TOTAL_TIME > std::chrono::duration<double>(595))
    {
        max_depth = 1;
    }
    else if (TOTAL_TIME > std::chrono::duration<double>(590))
    {
        max_depth = 2;
    }
    else if (TOTAL_TIME > std::chrono::duration<double>(500))
    {
        max_depth = 3;
    }
    // else if (TOTAL_TIME <= std::chrono::duration<double>(.1))
    // {
    //     max_depth = 4;
    // }
        else if (TOTAL_TIME <= std::chrono::duration<double>(50))
    {
        max_depth = 5;
    }
    else if (TOTAL_TIME <= std::chrono::duration<double>(150))
    {
        max_depth = 6;
    }
    else if (TOTAL_TIME <= std::chrono::duration<double>(450))
    {
        max_depth = 5;
    }
    else if (TOTAL_TIME <= std::chrono::duration<double>(500))
    {
        max_depth = 4;
    }
    if (board.HaveWinner() || depth > this->max_depth)
    {
        ply_data.utility = this->Evaluate(board, player);
        return ply_data;
    }
    double zed = depth * .001;
    ai::Jetan::Board my_board(board);

    int other_player = (player == 1) ? 2 : 1;
    const std::vector<ai::Jetan::MoveData> &moves = my_board.DetermineLegalMoves(other_player);

    otherAttacked.clear();
    myAttacked.clear();
    my_board.DetermineAttackedLocations(player, otherAttacked);
    my_board.DetermineAttackedLocations(other_player, myAttacked);
    int i;
    for (i = 0; i < (int)moves.size(); i++)
    {
        //////////////////////// princess additions
        const BoardData &bd = my_board.GetBoard(); // get the copied board's data
        int tx = moves[i].piece.x;
        int ty = moves[i].piece.y;
        // is this piece that moved a princess
        if (bd.pieces[int(bd.squares[ty][tx])].mType == ai::Jetan::Piece::PRINCESS)
        {
            if (otherAttacked.count(bd.pieces[int(bd.squares[ty][tx])].mLocation) == 0)
            {
                continue; // next node skips her moves
            }
        } ///////////////////////////////////////////

        ai::Jetan::Board tmp_board(board);
        tmp_board.Move(other_player, moves[i]);
        PlyData tmp_ply_data = this->Max(tmp_board, player, depth + 1, alpha, beta);
        if (tmp_ply_data.utility * (1 - zed) < ply_data.utility)
        {
            ply_data.utility = tmp_ply_data.utility * (1 - zed);
            ply_data.move = moves[i];
            ply_data.move_ok = true;
            if (ply_data.utility <= alpha)
            { /* parent node has a better (or equal) child, so this node will not be chosen */
                break;
            }
            if (ply_data.utility < beta)
            {
                beta = ply_data.utility;
            }
        }
    }
    return ply_data;
}

double AlphaBeta::Evaluate(const ai::Jetan::Board &board, int player)
{
    double v = 0.0;
    switch (this->evaluation_method)
    {
    default:
    case PIECE_COUNT_WIN:
        v = this->EvaluatePieceCountWin(board, player);
        break;

    case NEW_TECHNIQUE:
        pieceArray[0] = 3; // warrior
        pieceArray[1] = 3; // padwar
        pieceArray[2] = 4; // dwar
        pieceArray[3] = 5; // flyer
        pieceArray[4] = 3; // chief
        pieceArray[5] = 2; // princess
        pieceArray[6] = 2; // thoat
        pieceArray[7] = 1; // panthan
        v = this->EvaluatePieceCountWinPlusWeight2(board, player);
        break;

    case NEW_TECHNIQUE_NEW_WEIGHTS:
        pieceArray[0] = 3; // warrior
        pieceArray[1] = 4; // padwar
        pieceArray[2] = 5; // dwar
        pieceArray[3] = 6; // flyer
        pieceArray[4] = 3; // chief
        pieceArray[5] = 2; // princess
        pieceArray[6] = 2; // thoat
        pieceArray[7] = 1; // panthan
        v = this->EvaluatePieceCountWinPlusWeight2(board, player);
        break;
    }
    return v;
}

double AlphaBeta::EvaluatePieceCountWinPlusWeight2(const ai::Jetan::Board &board, int player)
{
    const BoardData &boardData = board.GetBoard();

    if (boardData.player_turn == 5)
    {
        if (player == 1) // if player 1 is going to win
        {
            return MY_INFINITY / 2.0; // setting extreme for win or loss
        }
        else
        {
            return -MY_INFINITY / 2.0;
        }
    }
    else if (boardData.player_turn == 6)
    {
        if (player == 1)
        {
            return -MY_INFINITY / 2.0;
        }
        else
        {
            return MY_INFINITY / 2.0;
        }
    }
    else if (boardData.player_turn == 7) // if going to tie
    {
        if (player == 1)
        {
            return 0.0;
        }
        else
        {
            return 0.0;
        }
    }
    return EvaluateNewVersion2(board, player); // testing
}

// subtract number of times under attack + piece weight
double AlphaBeta::EvaluateAttackedSpaces2(const ai::Jetan::Board &board, int player)
{
double v = 0;
    const BoardData &boardData = board.GetBoard();
    int i;
    for (i = 0; i < 20; i++)
    {
        ai::Jetan::Piece current = boardData.pieces[i];
        if (current.mAlive)
        {
            if (myAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation) > 0)
            {
                if (player == 1)
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v -= (7 * myAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
                else
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v += (7 * myAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
            }
            ////////////////////
            if (otherAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation) > 0)
            {
                if (player == 2)
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v += (8 * otherAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
                else
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v -= (8 * otherAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
            }
            ////////////////////
        }
    }
    for (i = 20; i < 40; i++)
    {
        ai::Jetan::Piece current = boardData.pieces[i];
        if (current.mAlive)
        {
            if (otherAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation) > 0)
            {
                if (player == 2)
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v += (7 * otherAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
                else
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v -= (7 * otherAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
            }
            ///////////////
            if (myAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation) > 0)
            {
                if (player == 1)
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v += (8 * myAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
                else
                {
                    if (current.mType != ai::Jetan::Piece::PRINCESS)
                    {
                        v -= (8 * myAttacked.count(boardData.pieces[int(boardData.squares[int(current.mLocation.y)][int(current.mLocation.x)])].mLocation));
                    }
                }
            }
            //////////////
        }
    }
    return v; // test 3

}

double AlphaBeta::EvaluateNewVersion2(const ai::Jetan::Board &board, int player)
{
    double v = 0;
    const BoardData &boardData = board.GetBoard();
    int i;
    for (i = 0; i < 20; i++)
    {
        if (boardData.pieces[i].mType != ai::Jetan::Piece::PRINCESS)
        {
            if (boardData.pieces[i].mAlive)
            {
                if (player == 1)
                {
                    v += (pieceArray[int(boardData.pieces[i].mType)] + 2 * boardData.pieces[i].mPaths->getPaths().size());
                } // if it's not a -1, then the piece is attacking another piece
                else
                {
                    v -= (pieceArray[int(boardData.pieces[i].mType)] + 2 * boardData.pieces[i].mPaths->getPaths().size());
                }
            }
        }
    }
    for (i = 20; i < 40; i++)
    {
        if (boardData.pieces[i].mType != ai::Jetan::Piece::PRINCESS)
        {
            if (boardData.pieces[i].mAlive)
            {
                if (player == 2)
                {
                    v -= (pieceArray[int(boardData.pieces[i].mType)] + 2 * boardData.pieces[i].mPaths->getPaths().size());
                }
                else
                {
                    v += (pieceArray[int(boardData.pieces[i].mType)] + 2 * boardData.pieces[i].mPaths->getPaths().size());
                }
            }
        }
    }
    return v * 4 + EvaluateAttackedSpaces2(board, player);
}

// level 1 agent

double AlphaBeta::EvaluatePieceCountWin(const ai::Jetan::Board &board, int player)
{
    const BoardData &boardData = board.GetBoard();
    if (boardData.player_turn == 5)
    {
        if (player == 1)
        {
            max_depth = 5;
            return MY_INFINITY / 2.0; // setting extreme for win or loss
        }
        else
        {
            max_depth = 5;
            return -MY_INFINITY / 2.0;
        }
    }
    else if (boardData.player_turn == 6)
    {
        if (player == 1)
        {
            max_depth = 5;
            return -MY_INFINITY / 2.0;
        }
        else
        {
            max_depth = 5;
            return MY_INFINITY / 2.0;
        }
    }
    else if (boardData.player_turn == 7)
    {
        if (player == 1)
        {
            max_depth = 5;
            return 0.0;
        }
        else
        {
            max_depth = 5;
            return 0.0;
        }
    }
    return EvaluatePieceCount(board, player);
}

double AlphaBeta::EvaluatePieceCount(const ai::Jetan::Board &board, int player)
{
    const BoardData &boardData = board.GetBoard();
    double v = 0;
    int i;
    for (i = 0; i < 20; i++)
    {
        if (boardData.pieces[i].mAlive)
        {
            if (player == 1)
            {
                v += 1;
            }
            else
            {
                v -= 1;
            }
        }
    }
    for (i = 20; i < 40; i++)
    {
        if (boardData.pieces[i].mAlive)
        {
            if (player == 2)
            {
                v += 1;
            }
            else
            {
                v -= 1;
            }
        }
    }
    return v;
}

} // namespace Jetan
} // namespace ai