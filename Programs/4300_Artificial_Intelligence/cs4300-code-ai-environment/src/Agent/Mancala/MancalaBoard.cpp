#include <ai_mancala.h>

#include <cstring>
#include <cstdio>

namespace ai
{
  namespace Mancala
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


    MoveData::MoveData()
      : bins(0),
        counts(0)
    {
    }
    MoveData::MoveData(int b_in, int c_in)
    {
      this->bins.clear();
      this->counts.clear();
      this->AddBin(b_in, c_in);
    }
    MoveData::MoveData(const MoveData &m_in)
    {
      *this = m_in;
    }
    MoveData &MoveData::operator=(const MoveData &m_in)
    {
      this->bins = m_in.bins;
      this->counts = m_in.counts;
      return *this;
    }
    bool MoveData::AddBin(int b_in, int c_in)
    {
      this->bins.push_back(b_in);
      this->counts.push_back(c_in);
      return true;
    }
    void MoveData::Display(std::ostream &os) const
    {
      os << this->ToString() << std::endl;
    }
    std::string MoveData::ToString() const
    {
      std::string s = "";
      int i;
      char buf[128];
      for(i = 0; i < (int)bins.size(); i++)
        {
          std::sprintf(buf, "%d:%d ", this->bins[i], this->counts[i]);
          s += buf;
        }
      return s;
    }


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

    bool Board::MoveAux(int player, const MoveData &move_in)
    {
      /* Assume move is legal */
      int last_bin = -1;
      unsigned int i;
      for(i = 0; i < move_in.bins.size(); i++)
        {
          int count = move_in.counts[i];
          board.board[move_in.bins[i]] = 0;

          int index = move_in.bins[i];
          for(int j = 0; j < count; j++)
            {
              index ++;
              index %= 14;
              /* don't drop stones in opponent's store */
              if(player == 1 && index == 13) { index ++; }
              if(player == 2 && index ==  6) { index ++; }
              index %= 14;
              board.board[index] ++;
              last_bin = index;
            }
        }

      /* Capture opponent's stones if last stone is in empty bin,
       * and opposite bin has stones */
      if((player == 1) && (last_bin >= 0) && (last_bin < 6) &&
         (board.board[last_bin] == 1) && (board.board[12-last_bin] != 0))
        {
          board.board[6] += board.board[last_bin] + board.board[12-last_bin];
          board.board[last_bin] = 0;
          board.board[12-last_bin] = 0;
        }
      else if((player == 2) && (last_bin >= 7) && (last_bin < 13) &&
              (board.board[last_bin] == 1) && (board.board[12-last_bin] != 0))
        {
          board.board[13] += board.board[last_bin] + board.board[12-last_bin];
          board.board[last_bin] = 0;
          board.board[12-last_bin] = 0;
        }

      /* If the either player only has empty bins, the opponent gets
       * to keep all remaining stones. */
      int j;
      int c[2] = { 0, 0 };
      for(j = 0; j < 6; j++)
        {
          c[0] += board.board[j];
          c[1] += board.board[j+7];
        }
      if((c[0] == 0) || (c[1] == 0))
        {
          for(j = 0; j < 6; j++)
            {
              board.board[6]  += board.board[j];
              board.board[13] += board.board[j+7];
              board.board[j] = 0;
              board.board[j+7] = 0;
            }
          board.game_over = true;
        }

      return true;
    }
    bool Board::Move(int player, const MoveData &move_in, double seconds_in)
    {
      if((IsLegal(player, move_in)) &&
         (player == board.player_turn))
        {
          this->MoveAux(player, move_in);
          board.player_turn = ((board.player_turn)%board.num_players) + 1;

          /* keep stats */
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
          if(move_in.bins.size() == legal_moves[i].bins.size())
            {
              int j;
              bool ok = true;
              for(j = 0; j < (int) move_in.bins.size(); j++)
                {
                  if(!(move_in.bins[j] == legal_moves[i].bins[j] &&
                       move_in.counts[j] == legal_moves[i].counts[j]))
                    {
                      ok = false;
                    }
                }
              if(ok)
                {
                  return true;
                }
            }
        }
      return false;
    }

    bool Board::Winner(int player) const
    {
      return this->board.game_over;
    }

    int Board::HaveWinner() const
    {
      if(!this->board.game_over)
        {
          return 0;
        }
      else if(this->board.board[6] > this->board.board[13])
        {
          return 1;
        }
      else if(this->board.board[6] < this->board.board[13])
        {
          return 2;
        }
      else
        { /* tied */
          return 3;
        }
    }


    std::vector<MoveData> Board::LegalMovesAux(const int player, const BoardData &bd_in) const
    {
      std::vector<MoveData> tmp_legal_moves;
      int i;
      unsigned int j, k;
      int start = 0 + ((player == 2) ? 7 : 0);

      for(i = start; i < start + 6; i++)
        {
          if(bd_in.board[i] > 0)
            {
              MoveData m(i, bd_in.board[i]);
              if(MoveEndsInStore(player, i, bd_in.board[i]))
                { /* This move will land in the player's store, they
                   * get to go again.
                   */
                  Board temp = *this;
                  temp.MoveAux(player, m);
                  std::vector<MoveData> moves = temp.LegalMovesAux(player, temp.board);

                  if(moves.size() > 0)
                    {
                      for(j = 0; j < moves.size(); j++)
                        {
                          MoveData m2 = m;
                          for(k = 0; k < moves[j].bins.size(); k++)
                            {
                              m2.AddBin(moves[j].bins[k], moves[j].counts[k]);
                            }
                          tmp_legal_moves.push_back(m2);
                        }
                    }
                  else
                    {
                      tmp_legal_moves.push_back(m);
                    }
                }
              else
                {
                  tmp_legal_moves.push_back(m);
                }
            }
        }

      return tmp_legal_moves;
    }


    const std::vector<MoveData> & Board::DetermineLegalMoves(int player)
    {
      if(legal_moves_valid)
        {
          return legal_moves;
        }

      legal_moves.resize(0);
      this->legal_moves = this->LegalMovesAux(player, this->board);
      legal_moves_valid = true;
      return legal_moves;
    }

    bool Board::MoveEndsInStore(const int player, const int from_bin, const int num_stones) const
    {
      int start = 0 + ((player == 2) ? 7 : 0);
      return (((num_stones%13) - (6 + start - from_bin) ) % 14) == 0;
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
      unsigned int i;
      std::string str;
      char str_tmp[16];

      for(i = 0; i < this->board.board.size(); i++)
        {
          std::sprintf(str_tmp, "%d,", board.board[i]);
          str += str_tmp;
        }
      std::sprintf(str_tmp, "%d,", board.num_players);
      str += str_tmp;

      std::sprintf(str_tmp, "%d,", board.player_turn);
      str += str_tmp;

      std::sprintf(str_tmp, "%d,", number_of_turns);
      str += str_tmp;

      std::sprintf(str_tmp, "%d,", board.game_over);
      str += str_tmp;

      return str;
    }

    void Board::SetBoardString(const std::string &board_str_in)
    {
      unsigned int i;
      int tmp;
      const char *str = board_str_in.c_str();
      board.board.resize(14);
      for(i = 0; i < board.board.size(); i++)
        {
          std::sscanf(str, "%d,", &tmp);
          board.board[i] = tmp;
          str = index(str, ',');
          str++;
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

      std::sscanf(str, "%d,", &tmp);
      board.game_over = tmp;
      str = index(str, ',');
      str++;
    }

    void Board::SetNumPlayer(int num_player_in)
    {
      board.num_players = num_player_in;
    }

    void Board::InitBoard()
    {

      int i;
      board.board.resize(14);
      for(i = 0; i < 6; i++)
        {
          board.board[i] = board.board[i+7] = 4;
        }
      board.board[6] = board.board[13] = 0;
      board.game_over = false;

      board.num_players = 0;
      board.player_turn = 1;

      number_of_turns   = 0;
      legal_moves_valid = false;

      // Why did we do this?
      //last_moves.resize(0);
    }

    int Board::Score(const int player) const
    {
      if(player == 1)
        {
          return this->board.board[6];
        }
      else if(player == 2)
        {
          return this->board.board[13];
        }
      return 0;
    }

  }
}
