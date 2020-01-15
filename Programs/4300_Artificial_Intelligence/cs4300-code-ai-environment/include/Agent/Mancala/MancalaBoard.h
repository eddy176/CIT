#ifndef _MANCALABOARD_H_
#define _MANCALABOARD_H_
namespace ai
{
  namespace Mancala
  {
    struct MoveData
    {
    public:
      MoveData();
      MoveData(int b_in, int c_in);
      MoveData(const MoveData &m_in);
      MoveData &operator=(const MoveData &m_in);
      bool AddBin(int b_in, int c_in);
      void Display(std::ostream &os) const;
      std::string ToString() const;

      std::vector<int> bins;   // which bins to move from
      std::vector<int> counts; // how many tokens in the bins
    };

    struct BoardData
    {
    public:
      std::vector<int>  board; /* 14 values of the number of markers
                                * [0] - [5] is player 1's side of the board
                                * [6] is player 1's bin,
                                * [7] - [12] is player 2's side of the board
                                * [13] is player 2's bin
                                */
      /*
        12 11 10  9  8  7
        13                  6
        0  1  2  3  4  5
      */
      int num_players; // number of players in this game (2)
      int player_turn; // whose turn 1-num_players
      bool game_over;

    };

    class Board
    {
    public:
      Board();
      Board(const Board &board_in);
      Board(const std::string &board_str_in);

      virtual ~Board();

      /*
       * Apply player's move from move_in
       *  Returns true if successful
       *  else returns false.  (Illegal moves, etc.)
       */
      virtual bool MoveAux(int player, const MoveData &move_in);
      virtual bool Move(int player, const MoveData &move_in, double seconds_in);
      virtual bool Move(int player, const MoveData &move_in);

      /*
       * Returns true of player can legally make the move
       */
      virtual bool IsLegal(int player, const MoveData &move_in);

      /*
       * returns true if <player> has won.
       */
      virtual bool Winner(int player) const;

      /*
       * returns player number of winner (0 if none, 3 if tie)
       */
      virtual int HaveWinner() const;

      /*
       * Determines all legal moves, including chains.
       */
      virtual std::vector<MoveData> LegalMovesAux(const int player, const BoardData &bd_in) const;
      virtual const std::vector<MoveData> & DetermineLegalMoves(int player);

      /*
       * Used by DetermineLegalMoves
       */
      virtual bool MoveEndsInStore(const int player, const int from_bin, const int num_stones) const;

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
       *  Return player's current score.
       */
      virtual int Score(const int player) const;

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
#endif /* _MANCALABOARD_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
