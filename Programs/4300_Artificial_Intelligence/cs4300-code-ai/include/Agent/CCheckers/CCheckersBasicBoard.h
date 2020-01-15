#ifndef _CCHECKERSBASICBOARD_H_
#define _CCHECKERSBASICBOARD_H_

#include <vector>
#include <string>

namespace ai
{
  namespace CCheckers
  {
    struct MoveData
    {
    public:
      int from_x;
      int from_y;
      int to_x;
      int to_y;
    };

    struct BoardData
    {
    public:
      /*
       * The actual board data.
       *   0 means empty.
       *   1-6 is filled by corresponding player.
       *   -1 means unusable.
       */
      int hole[17][17];
      int num_players; // number of players in this game (2)
      int player_turn; // whose turn 1-num_players
    };

    class BasicBoard
    {
    public:
      BasicBoard();
      BasicBoard(const BasicBoard &board_in);
      BasicBoard(const std::string &board_str_in);

      virtual ~BasicBoard();

      /*
       * Move player's piece from f_x,f_y to t_x,t_y
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
       * returns true if <player> is in its goal state.
       */
      virtual bool Winner(int player) const;

      /*
       * returns player number of winner (0 if none)
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
       * calculates the "forwardness" of the player
       */
      virtual int Forwardness(int player) const;

      /*
       *  Move all pieces back to the starting point
       */
      virtual void InitBoard();

      /*
       * recursively jumps without returning to the same locations
       *   NEEDED for DetermineLegalMoves
       */
      virtual void RecursiveVisit(int original_x, int original_y,
                                  int current_x, int current_y);

      /*
       * clear the visited flag for all locations.
       *   NEEDED for RecursiveVisit()
       */
      virtual void MarkAllNotVisited();


      /*
       * Returns true if the board is usable at x,y
       */
      virtual bool Usable(int x, int y) const;

      /*
       * Returns true if the board is usable and has a marble at x,y
       */
      virtual bool Occupied(int x, int y) const;

      /*
       * Returns true if the board is usable and has no marble at x,y
       */
      virtual bool Available(int x, int y) const;

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
      bool visited[17][17];
    private:
    };
  }
}

#endif /* _CCHECKERSBASICBOARD_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
