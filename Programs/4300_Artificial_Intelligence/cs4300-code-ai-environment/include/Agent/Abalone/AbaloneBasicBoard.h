#ifndef _ABALONEBASICBOARD_H_
#define _ABALONEBASICBOARD_H_

#include <array>
#include <string>
#include <utility>
#include <vector>

namespace ai {
	namespace Abalone {

		/*
		 * Stores from (x,y) and to (x,y) coordinates
		 */
		struct MoveData {
			public:
				std::array<int, 5> from_x;
				std::array<int, 5> from_y;
				std::array<int, 5> to_x;
				std::array<int, 5> to_y;
				unsigned int number;
				
			MoveData() {
				number = 0;
			}
			MoveData(std::array<int, 5> fx, std::array<int, 5> fy, std::array<int, 5> tx, std::array<int, 5> ty, int num) {
				from_x = fx;
				from_y = fy;
				to_x = tx;
				to_y = ty;
				number = num;
			}
		};

		/*
		 * Stores the board data with values:
		 *   + 0: empty
		 *   + 1-4: corresponding player.
		 *   + -1: unusable.
		 */
		struct BoardData {
			public:
				int hole[11][11];
				int num_players; // number of players (2 is usual but variants exist for 4)
				int player_turn; // whose turn it is
				int p1_count; // how many pieces player 1 has on the board
				int p2_count;
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
		  //virtual bool IsLegal(int player, const MoveData &move_in);

		  /*
		   * returns true if <player> is in its goal state.
		   */
		  //virtual bool Winner(int player) const;

		  /*
		   * returns player number of winner (0 if none)
		   */
		  virtual int HaveWinner() const;

		  /*
		   * Determines all legal moves, including jump chains.
		   */
		  virtual const std::vector<MoveData>& DetermineLegalMoves(int player);

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
		   * Returns a printable std::string representation of the board
		   */
		  virtual std::string GetPrintableBoardString() const;

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
		   *  Move all pieces back to the starting point
		   */
		  virtual void InitBoard();

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

		  unsigned int number_of_turns;
		  bool legal_moves_valid;
		  std::vector<MoveData> legal_moves;
		  std::vector<MoveData> last_moves;
		  std::vector<double> player_times;
		private:
		};

	}
}

#endif /* _ABALONEBASICBOARD_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
