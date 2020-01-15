#ifndef _TTTBOARD_H_
#define _TTTBOARD_H_
namespace ai
{
  namespace TicTacToe
  {
    class Environment;

    struct MoveData
    {
    public:
      int pos_x; /* 0 - 2*/
      int pos_y; /* 0 - 2*/

    };

    struct BoardData
    {
    public:
      /*
       * The actual board data.
       *   0 means empty.
       *   1-2 is filled by corresponding player.
       */
      int grid[3][3];
      int num_players; // number of players in this game (2)
      int player_turn; // whose turn 1-num_players

    };

    class Board
    {
    public:
      Board();
      Board(const Board &board_in);
      Board(const std::string &board_str_in);

      virtual ~Board();

      /*
       * Place player's mark at p_x,p_y
       *  Returns true if successful
       *  else returns false.  (Illegal moves, etc.)
       */
      virtual bool Move(int player, const MoveData &move_in, double seconds_in);
      virtual bool Move(int player, const MoveData &move_in);

      /*
       * Returns true of player can legally make the move
       */
      virtual bool IsLegal(int player, const MoveData &move_in);

      /*
       * returns true if <player> is in a goal state.
       */
      virtual bool Winner(int player) const;

      /*
       * returns player number of winner (0 if none, 3 if tie)
       */
      virtual int HaveWinner() const;

      /*
       * Determines all legal moves, including jump chains.
       */
      virtual const std::vector<MoveData> & DetermineLegalMoves(int player);

      /*
       * Returns the last moves by each player
       */
      virtual const std::vector<MoveData> & GetLastMoves() const;

      /*
       * Returns the seconds consumed by each player
       */
      virtual const std::vector<double> & GetPlayerTimes() const;

      /*
       *  Return the total number of turns that have been completed.
       */
      virtual unsigned int GetTotalMoves() const;

      /*
       * Returns a const reference to the actual data
       */
      virtual const BoardData & GetBoard() const;

      /*
       * Sets the current board information
       */
      virtual void SetBoard(const BoardData &board_in);

      /*
       * Returns a std::string representation of the board
       */
      virtual std::string GetBoardString() const;

      /*
       * Sets the board from the std::string representation
       */
      virtual void SetBoardString(const std::string &board_str_in);

      /*
       * Sets the number of players
       */
      virtual void SetNumPlayer(int num_player_in);

      /*
       *  Reset the board back to the starting point
       */
      virtual void InitBoard();

      /*
       * Returns true if the board is usable and has a mark at x,y
       */
      virtual bool Occupied(int x, int y) const;

      /*
       * Returns true if the board is usable and has no mark at x,y
       */
      virtual bool Available(int x, int y) const;

      /*
       *  Set the total number of turns that have been completed.
       */
      virtual bool SetTotalMoves(unsigned int total_moves);

      /*
       * Set the last moves by a player
       */
      virtual bool SetLastMove(int player_num, const MoveData &move);

      /*
       * Set the seconds consumed by a player
       */
      virtual bool SetPlayerTime(int player_num, const double &time);

    protected:
      friend class Environment;
      /*
       * The board data
       */
      BoardData board;

      unsigned int  number_of_turns;
      bool legal_moves_valid;
      std::vector<MoveData> legal_moves;
      std::vector<MoveData> last_moves;
      std::vector<double>   player_times;

    private:
    };
  }
}
#endif /* _TTTBOARD_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
