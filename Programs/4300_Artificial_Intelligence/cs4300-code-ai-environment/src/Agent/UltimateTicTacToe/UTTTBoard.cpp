#include <ai_ultimatetictactoe.h>

#include <cstring>
#include <cstdio>
#include <sstream>
#include <algorithm>

namespace ai
{
  namespace UltimateTicTacToe
  {

    /************************************************************/
    MoveData::MoveData( ) 
      : board_x( -1 ), board_y( -1 ), pos_x( -1 ), pos_y( -1 ) {
    }
    MoveData::MoveData( int bx, int by, int px, int py ) 
      : board_x( bx ), board_y( by ), pos_x( px ), pos_y( py ) {
    }
    void MoveData::setData( int bx, int by, int px, int py ) {
      board_x = bx;
      board_y = by;
      pos_x = px;
      pos_y = py;
    }
    bool MoveData::operator<( const MoveData& rhs ) const {
      if( this->board_x < rhs.board_x ) {
        return true;
      } else if( this->board_x > rhs.board_x ) {
        return false;
      } else if( this->board_y < rhs.board_y ) {
        return true;
      } else if( this->board_y > rhs.board_y ) {
        return false;
      } else if( this->pos_x < rhs.pos_x ) {
        return true;
      } else if( this->pos_x > rhs.pos_x ) {
        return false;
      } else if( this->pos_y < rhs.pos_y ) {
        return true;
      } else if( this->pos_y > rhs.pos_y ) {
        return false;
      } else {
        return false;
      }
    }

    std::ostream& operator<<( std::ostream& os, const MoveData& move ) {
      os << move.board_x << "," << move.board_y << ":" << move.pos_x << "," << move.pos_y;
      return os;
    }

    /************************************************************/
    SubBoardData::SubBoardData( ) {
      Reset( );
    }

    void SubBoardData::Reset( ) {
      int x, y;
      for( y = 0; y < 3; y++ ) {
        for( x = 0; x < 3; x++ ) {
          this->grid[y][x] = 0;
        }
      }
    }
    
    bool SubBoardData::Winner( int player ) const {
      WinReasonEnum reason = this->FindPlayerWin( player );
      return reason != WIN_NONE;
    }


    bool SubBoardData::Complete( ) const {
      if( this->Winner( 1 ) || this->Winner( 2 ) ) {
        return true;
      }
      int x,y;
      for( y = 0; y < 3; y++ ) {
        for( x = 0; x < 3; x++ ) {
          if( this->grid[y][x] == 0 ) {
            return false;
          }
        }
      }
      return true;
    }
    
    WinReasonEnum SubBoardData::FindPlayerWin( int player ) const {
      int x,y;
      
      /* horizontal row win */
      for(y = 0; y < 3; y++) {
        if(this->grid[y][0] == this->grid[y][1] &&
           this->grid[y][0] == this->grid[y][2] &&
           this->grid[y][0] == player) {
          switch( y ) {
          case 0: return WIN_ROW_0; break;
          case 1: return WIN_ROW_1; break;
          case 2: return WIN_ROW_2; break;
          default: return WIN_NONE; break;
          }
        }
      }
      
      /* vertical column win */
      for(x = 0; x < 3; x++) {
        if(this->grid[0][x] == this->grid[1][x] &&
           this->grid[0][x] == this->grid[2][x] &&
           this->grid[0][x] == player) {
          switch( x ) {
          case 0: return WIN_COLUMN_0; break;
          case 1: return WIN_COLUMN_1; break;
          case 2: return WIN_COLUMN_2; break;
          default: return WIN_NONE; break;
          }
        }
      }
      
      /* diagonal win */
      if(this->grid[0][0] == this->grid[1][1] &&
         this->grid[0][0] == this->grid[2][2] &&
         this->grid[0][0] == player) {
        return WIN_DIAGONAL_0;
      }
      if(this->grid[0][2] == this->grid[1][1] &&
         this->grid[0][2] == this->grid[2][0] &&
         this->grid[0][2] == player) {
        return WIN_DIAGONAL_1;
      }
      return WIN_NONE;
    }

    /************************************************************/
    BoardData::BoardData( ) {
      this->Reset( );
    }
    void BoardData::Reset( ) {
      int x, y;
      for( y = 0; y < 3; y++ ) {
        for( x = 0; x < 3; x++ ) {
          this->grid[y][x].Reset( );
        }
      }
      this->num_players = 0;
      this->player_turn = 1;
      this->next_board_x = -1;
      this->next_board_y = -1;
    }
    bool BoardData::Complete( ) const {
      if( this->Winner( 1 ) || this->Winner( 2 ) ) {
        return true;
      }
      int x,y;
      for( y = 0; y < 3; y++ ) {
        for( x = 0; x < 3; x++ ) {
          if( !this->grid[y][x].Complete( ) ) {
            return false;
          }
        }
      }
      return true;
    }
    bool BoardData::Winner( int player ) const {
      WinReasonEnum reason = this->FindPlayerWin( player );
      return reason != WIN_NONE;
    }

    WinReasonEnum BoardData::FindPlayerWin( int player ) const {
      int x,y;
      /* horizontal row win */
      for(y = 0; y < 3; y++) {
        if( this->grid[y][0].Winner( player ) &&
            this->grid[y][1].Winner( player ) &&
            this->grid[y][2].Winner( player ) ) {
          switch( y ) {
          case 0: return WIN_ROW_0; break;
          case 1: return WIN_ROW_1; break;
          case 2: return WIN_ROW_2; break;
              default: return WIN_NONE; break;
          }
            }
      }
      
      /* vertical column win */
      for(x = 0; x < 3; x++) {
        if( this->grid[0][x].Winner( player ) &&
            this->grid[1][x].Winner( player ) &&
            this->grid[2][x].Winner( player ) ) {
          switch( x ) {
          case 0: return WIN_COLUMN_0; break;
          case 1: return WIN_COLUMN_1; break;
          case 2: return WIN_COLUMN_2; break;
          default: return WIN_NONE; break;
          }
        }
      }
      
      /* diagonal win */
      if( this->grid[0][0].Winner( player ) &&
          this->grid[1][1].Winner( player ) &&
          this->grid[2][2].Winner( player ) ) {
        return WIN_DIAGONAL_0;
      }
      if( this->grid[0][2].Winner( player ) &&
          this->grid[1][1].Winner( player ) &&
          this->grid[2][0].Winner( player ) ) {
        return WIN_DIAGONAL_1;
      }
      return WIN_NONE;
    }


    /************************************************************/
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
      : number_of_turns( 0 ),
        legal_moves_valid(false),
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
      DBGP_L(LOG_STREAM(std::cerr) 
             << "Player: " << player
             << "  Move: " << move_in
             << "  IsLegal: " << IsLegal(player, move_in)
             << "  TurnOK: " << (player == board.player_turn)
             << std::endl);
      if((IsLegal(player, move_in)) &&
         (player == board.player_turn))
        {
          board.grid[move_in.board_y][move_in.board_x].grid[move_in.pos_y][move_in.pos_x] = player;
          board.player_turn = ((board.player_turn)%board.num_players) + 1;
          if( board.grid[move_in.board_y][move_in.board_x].Complete( ) ){
            board.next_board_x = -1;
            board.next_board_y = -1;
          } else {
            board.next_board_x = move_in.pos_x;
            board.next_board_y = move_in.pos_y;
          }
          last_moves[player-1]    = move_in;
          DBGP_L(LOG_STREAM(std::cerr) 
                 << "player-1: " << (player-1)
                 << "  last_moves[player-1]: " << last_moves[player-1]
                 << std::endl);
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

    bool Board::IsLegal(int player, const MoveData &move_in) {
      DetermineLegalMoves(player);
      return std::binary_search( legal_moves.begin( ), legal_moves.end( ), move_in );
    }
    
    bool Board::Winner(int player) const
    {
      return board.Winner( player );
    }

    int Board::HaveWinner() const
    {
      int i;
      for(i = 1; i <= 2; i++) {
        if(Winner(i)) {
          return i;
        }
      }
      if( board.Complete( ) ) {
        return 3;
      }
      return 0;
    }

    const std::vector<MoveData> & Board::DetermineLegalMoves(int player)
    {
      int x, y, board_x, board_y;
      MoveData d;

      if(legal_moves_valid)
        {
          return legal_moves;
        }

      legal_moves.resize(0);

      // it's very important that these moves are inserted in sorted order.
      for( board_x = 0; board_x < 3; board_x++ ) {
        for( board_y = 0; board_y < 3; board_y++ ) {
          
          /* 
           * ( this board is not complete ) AND ( next board is wild OR next board is complete OR this board is the next board )
           */
          if((!board.grid[board_y][board_x].Complete( ) ) &&
             ( ( board.next_board_x == -1 && board.next_board_y == -1 ) ||
               ( board.next_board_x >= 0 && board.next_board_y >= 0 && board.grid[board.next_board_y][board.next_board_x].Complete( ) ) ||
               ( board.next_board_x == board_x && board.next_board_y == board_y ) ) ) {
            d.board_x = board_x;
            d.board_y = board_y;
            for(x = 0; x < 3; x++) {
              for(y = 0; y < 3; y++) {
                if(board.grid[board_y][board_x].grid[y][x] == 0) {
                  d.pos_x = x;
                  d.pos_y = y;
                  legal_moves.push_back(d);
                }
              }
            }
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

    std::string Board::GetBoardString() const {
      std::stringstream ss;
      unsigned int i,j,ii,jj;

      for( ii = 0; ii < 3; ii++ ) {
        for( jj = 0; jj < 3; jj++ ) {
          for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
              ss << board.grid[ii][jj].grid[i][j] << ",";
            }
          }
        }
      }
      
      ss << board.num_players << ",";
      ss << board.player_turn << ",";
      ss << board.next_board_x << ",";
      ss << board.next_board_y << ",";
      ss << number_of_turns << ",";

      return ss.str( );
    }

    void Board::SetBoardString(const std::string &board_str_in) {
      std::stringstream ss( board_str_in );
      unsigned int i,j,ii,jj;
      int x;
      char comma;

      for( ii = 0; ii < 3; ii++ ) {
        for( jj = 0; jj < 3; jj++ ) {
          for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
              ss >> x >> comma;
              board.grid[ii][jj].grid[i][j] = x;
            }
          }
        }
      }

      ss >> board.num_players >> comma;
      ss >> board.player_turn >> comma;
      ss >> board.next_board_x >> comma;
      ss >> board.next_board_y >> comma;
      ss >> number_of_turns >> comma;
    }

    void Board::SetNumPlayer( int num_player_in ) {
      board.num_players = num_player_in;
    }

    void Board::InitBoard ( ) {
      board.Reset( );
      
      number_of_turns = 0;
      legal_moves_valid = false;
      int i;
      for( i = 0; i < 2; i++ ) {
        last_moves[i].board_x = last_moves[i].board_y = -1;
        last_moves[i].pos_x = last_moves[i].pos_y = -1;
        player_times[i] = 0.;
      }
    }

    bool Board::Occupied( int bx, int by, int x, int y ) const {
      if(board.grid[by][bx].grid[y][x]>=1)
        return true;
      else
        return false;
    }

    bool Board::Available( int bx, int by, int x, int y ) const
    {
      if(board.grid[by][bx].grid[y][x]==0)
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
