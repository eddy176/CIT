#include <ai_tictactoe.h>

#include <cstring>
#include <cstdio>

namespace ai
{
  namespace TicTacToe
  {
#ifdef WIN32
    static const char *index(const char *s, int c)
    {
      while(s && *s && *s != c)
        {
          s++;
        }
      return s;
    }
#endif

    Board::Board()
      : number_of_turns(0),
        legal_moves_valid(false),
        legal_moves(0),
        last_moves(2),
        player_times(2)
    {
      InitBoard();
    }

    Board::Board(const Board &board_in)
      : number_of_turns(board_in.number_of_turns),
        legal_moves_valid(board_in.legal_moves_valid),
        legal_moves(board_in.legal_moves),
        last_moves(board_in.last_moves),
        player_times(board_in.player_times)
    {
      board = board_in.board;
    }

    Board::Board(const std::string &board_str_in)
      : legal_moves_valid(false),
        legal_moves(0),
        last_moves(2),
        player_times(2)
    {
      SetBoardString(board_str_in);
    }

    Board::~Board()
    {
    }

    bool Board::Move(int player, const MoveData &move_in, double seconds_in)
    {
      if((IsLegal(player, move_in)) &&
         (player == board.player_turn))
        {
          board.grid[move_in.pos_y][move_in.pos_x] = player;
          board.player_turn = ((board.player_turn)%board.num_players) + 1;

          last_moves[player-1]    = move_in;
          player_times[player-1] += seconds_in;

          number_of_turns ++;
          legal_moves_valid = false;
          return true;
        }
      return false;
    }
    bool Board::Move(int player, const MoveData &move_in)
    {
      return Move(player, move_in, 0.);
    }

    bool Board::IsLegal(int player, const MoveData &move_in)
    {
      DetermineLegalMoves(player);

      for(unsigned int i=0; i<legal_moves.size(); i++)
        {
          if(move_in.pos_x == legal_moves[i].pos_x &&
             move_in.pos_y == legal_moves[i].pos_y)
            {
              return true;
            }
        }
      return false;
    }

    bool Board::Winner(int player) const
    {
      int x,y;
      /* horizontal row win */
      for(y = 0; y < 3; y++)
        {
          if(board.grid[y][0] == board.grid[y][1] &&
             board.grid[y][0] == board.grid[y][2] &&
             board.grid[y][0] == player)
            {
              return true;
            }
        }

      /* vertical column win */
      for(x = 0; x < 3; x++)
        {
          if(board.grid[0][x] == board.grid[1][x] &&
             board.grid[0][x] == board.grid[2][x] &&
             board.grid[0][x] == player)
            {
              return true;
            }
        }

      /* diagonal win */
      if(board.grid[0][0] == board.grid[1][1] &&
         board.grid[0][0] == board.grid[2][2] &&
         board.grid[0][0] == player)
        {
          return true;
        }
      if(board.grid[0][2] == board.grid[1][1] &&
         board.grid[0][2] == board.grid[2][0] &&
         board.grid[0][2] == player)
        {
          return true;
        }
      return false;
    }

    int Board::HaveWinner() const
    {
      int i, x, y;
      for(i = 1; i <= 2; i++)
        {
          if(Winner(i))
            {
              return i;
            }
        }
      int count = 0;
      for(y = 0; y < 3; y++)
        {
          for(x = 0; x < 3; x++)
            {
              if(board.grid[y][x] == 0)
                {
                  count ++;
                }
            }
        }
      if(count == 0)
        {
          return 3;
        }
      return 0;
    }

    const std::vector<MoveData> & Board::DetermineLegalMoves(int player)
    {
      int x, y;
      MoveData d;

      if(legal_moves_valid)
        {
          return legal_moves;
        }

      legal_moves.resize(0);

      for(y = 0; y < 3; y++)
        {
          for(x = 0; x < 3; x++)
            {
              if(board.grid[y][x] == 0)
                {
                  d.pos_x = x;
                  d.pos_y = y;
                  legal_moves.push_back(d);
                }
            }
        }
      legal_moves_valid = true;
      return legal_moves;
    }

    const std::vector<MoveData> & Board::GetLastMoves() const
    {
      return last_moves;
    }

    const std::vector<double> & Board::GetPlayerTimes() const
    {
      return player_times;
    }

    unsigned int Board::GetTotalMoves() const
    {
      return number_of_turns;
    }

    const BoardData & Board::GetBoard() const
    {
      return board;
    }

    void Board::SetBoard(const BoardData &board_in)
    {
      board = board_in;
    }

    std::string Board::GetBoardString() const
    {
      unsigned int i,j;
      std::string str;
      char str_tmp[16];

      for(i = 0; i < 3; i++)
        {
          for(j = 0; j < 3; j++)
            {
              std::sprintf(str_tmp, "%d,", board.grid[i][j]);
              str += str_tmp;
            }
        }
      std::sprintf(str_tmp, "%d,", board.num_players);
      str += str_tmp;

      std::sprintf(str_tmp, "%d,", board.player_turn);
      str += str_tmp;

      std::sprintf(str_tmp, "%d,", number_of_turns);
      str += str_tmp;

      return str;
    }

    void Board::SetBoardString(const std::string &board_str_in)
    {
      unsigned int i,j;
      const char *str = board_str_in.c_str();

      for(i = 0; i < 3; i++)
        {
          for(j = 0; j < 3; j++)
            {
              std::sscanf(str, "%d,", &board.grid[i][j]);
              str = index(str, ',');
              str++;
            }
        }

      std::sscanf(str, "%d,", &board.num_players);
      str = index(str, ',');
      str++;

      std::sscanf(str, "%d,", &board.player_turn);
      str = index(str, ',');
      str++;

      std::sscanf(str, "%d,", &number_of_turns);
      str = index(str, ',');
      str++;
    }

    void Board::SetNumPlayer(int num_player_in)
    {
      board.num_players = num_player_in;
    }

    void Board::InitBoard()
    {
      int x, y, i;

      for(y = 0; y < 3; y++)
        {
          for(x = 0; x < 3; x++)
            {
              board.grid[y][x] = 0;
            }
        }

      board.num_players = 0;
      board.player_turn = 1;

      number_of_turns   = 0;
      legal_moves_valid = false;

      for(i = 0; i < 2; i++)
        {
          last_moves[i].pos_x = last_moves[i].pos_y = -1;
          player_times[i] = 0.;
        }
    }

    bool Board::Occupied(int x, int y) const
    {
      if(board.grid[y][x]>=1)
        return true;
      else
        return false;
    }

    bool Board::Available(int x, int y) const
    {
      if(board.grid[y][x]==0)
        return true;
      else
        return false;
    }

    bool Board::SetTotalMoves(unsigned int total_moves)
    {
      number_of_turns = total_moves;
      return true;
    }

    bool Board::SetLastMove(int player_num, const MoveData &move)
    {
      last_moves[player_num-1] = move;
      return true;
    }

    bool Board::SetPlayerTime(int player_num, const double &time)
    {
      player_times[player_num-1] = time;
      return true;
    }

  }
}
