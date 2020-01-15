#ifndef _JETANBOARD_H_
#define _JETANBOARD_H_

#include <vector>

namespace ai
{
  namespace Jetan
  {
    class Environment;

    class BoardOffset {
      // difference in x and y coordinates, may be positive, negative, or zero.
    public:
      char dx, dy; 
    };

    class BoardLocation {
      // x and y coordinates, should be non-negative
    public:
      char x, y; 
      bool operator<( const BoardLocation& rhs ) const;
    };

    class SetOfBoardLocations {
    public:
      SetOfBoardLocations( );
      void clear( );
      int count( const BoardLocation& destination ) const;
      void insert( const BoardLocation& destination );
    protected:
      char board_locations[ 100 ];
    };

    class MovePath {
      // sequence of steps a piece must take, last item is the where the piece ends up.
      // each offset is relative to the previous offset position (the piece's original position for the first offset)
    public:
      std::vector< BoardOffset > steps;
    };

    class PiecePaths {
      // list of possible move paths for a piece
    public:
      PiecePaths( const std::vector< MovePath >& paths );
      const std::vector< MovePath >& getPaths( ) const;

    protected:
      std::vector< MovePath > mPaths;
    };

    class WarriorPiecePaths : public PiecePaths {
      // Warrior: 2 feathers; 2 spaces straight in any direction or combination.
    public:
      WarriorPiecePaths( );
    };

    class PadwarPiecePaths : public PiecePaths {
      // Padwar: 2 feathers; 2 spaces diagonal in any direction or combination.
    public:
      PadwarPiecePaths( );
    };

    class DwarPiecePaths : public PiecePaths {
      // Dwar: 3 feathers; 3 spaces straight in any direction or combination.
    public:
      DwarPiecePaths( );
    };

    class FlierPiecePaths : public PiecePaths {
      // Flier: 3 bladed propellor; 3 spaces diagonal in any direction or combination; and may jump intervening pieces.
    public:
      FlierPiecePaths( );
    };

    class ChiefPiecePaths : public PiecePaths {
      // Chief: Diadem with ten jewels; 3 spaces in any direction; straight or diagonal or combination.
    public:
      ChiefPiecePaths( );
    };

    class PrincessPiecePaths : public PiecePaths {
      // Princess: Diadem with one jewel; same as Chief, except may jump intervening pieces.
    public:
      PrincessPiecePaths( );
    };

    class PrincessPieceEscapePaths : public PiecePaths {
      // Princess: escape to anywhere on the board
    public:
      PrincessPieceEscapePaths( );
    };

    class ThoatPiecePaths : public PiecePaths {
      // Thoat: Mounted warrior 2 feathers; 2 spaces, one straight and one diagonal in any direction.
    public:
      ThoatPiecePaths( );
    };

    class Player1PanthanPiecePaths : public PiecePaths {
      // Panthan: 1 feather; 1 space, forward, side, or diagonal, but not backward.
    public:
      Player1PanthanPiecePaths( );
    };

    class Player2PanthanPiecePaths : public PiecePaths {
      // Panthan: 1 feather; 1 space, forward, side, or diagonal, but not backward.
    public:
      Player2PanthanPiecePaths( );
    };

    class Piece {
    public:
      enum TYPE { WARRIOR, PADWAR, DWAR, FLIER, CHIEF, PRINCESS, THOAT, PANTHAN };
      
      // defaults to dummy data
      Piece( );
      // defaults to alive, and mPaths initialized based on type
      Piece( const char player, const char type, const BoardLocation& location );

      const PiecePaths* mPaths;
      char              mPlayer;
      char              mType;
      BoardLocation     mLocation;
      bool              mAlive;
      
    protected:

    private:
    };

    class MoveData {
    public:
      MoveData( );
      MoveData( const BoardLocation& piece_in, const BoardOffset& offset_in );
      void setData( const BoardLocation& piece_in, const BoardOffset& offset_in );
      bool operator<( const MoveData& rhs ) const;

      BoardLocation piece; // location of the piece to move
      BoardOffset offset;  // offset to move to
    };

    class BoardData {
    public:
      BoardData( );
      void Reset( );

      // Player 1
      // Warrior Padwar Dwar Flier Chief Princess Flier Dwar Padwar Warrior
      // Thoat Panthan Panthan Panthan Panthan Panthan Panthan Panthan Panthan Thoat
      
      // Player 2
      // Warrior Padwar Dwar Flier Chief Princess Flier Dwar Padwar Warrior
      // Thoat Panthan Panthan Panthan Panthan Panthan Panthan Panthan Panthan Thoat

 
      Piece pieces[ 40 ]; // 0-19 player 1, 20-39 player 2
      char  squares[ 10 ][ 10 ]; // index into pieces, or -1 if vacant
      // squares[ row ][ column ]
      
      /* whose turn:
       *  1 or 2, game still on,
       *  5 -> player 1 wins, 
       *  6 -> player 2 wins, 
       *  7 -> tie
       */
      int player_turn;
      
      char used_escape[ 2 ]; // if the player has used the princess escape move yet 0 == no, 1 == yes
    };

    class Board {
    public:
      Board( );
      Board( const Board &board_in );
      Board( const std::string &board_str_in );

      virtual ~Board( );

      /*
       * Apply player's move_in.
       *  Returns true if successful
       *  else returns false.  (Illegal moves, etc.)
       */
      virtual bool Move( int player, const MoveData &move_in, double seconds_in );
      virtual bool Move( int player, const MoveData &move_in );
      /*
       * Allow a player to quit.
       */
      virtual bool Quit( int player );

      /*
       * Returns true of player can legally make the move
       */
      virtual bool IsLegal( int player, const MoveData &move_in );

      /*
       * returns true if <player> is in a goal state.
       */
      virtual bool Winner( int player ) const;

      /*
       * returns player number of winner (0 if none, 3 if tie)
       */
      virtual int HaveWinner( ) const;

      /*
       * Determines all locations that player can attack
       */
      virtual void DetermineAttackedLocations( int player, SetOfBoardLocations& locations ) const;

      /*
       * Determines all legal moves
       */
      virtual const std::vector< MoveData >& DetermineLegalMoves( int player );

      /*
       * Returns the last moves by each player
       */
      virtual const std::vector< MoveData >& GetLastMoves( ) const;

      /*
       * Returns the seconds consumed by each player
       */
      virtual const std::vector< double >& GetPlayerTimes( ) const;

      /*
       *  Return the total number of turns that have been completed.
       */
      virtual unsigned int GetTotalMoves( ) const;

      /*
       * Returns the number of moves by each player
       */
      virtual const std::vector< unsigned int >& GetPlayerTotalMoves( ) const;
      
      /*
       *  Return the total number of turns that player has completed.
       */
      virtual unsigned int GetPlayerTotalMoves( int player ) const;
      
      /*
       * Returns a const reference to the actual data
       */
      virtual const BoardData& GetBoard( ) const;

      /*
       * Sets the current board information
       */
      virtual void SetBoard( const BoardData &board_in );

      /*
       * Returns a std::string representation of the board
       */
      virtual std::string GetBoardString( ) const;

      /*
       * Sets the board from the std::string representation
       */
      virtual void SetBoardString( const std::string &board_str_in );

      /*
       *  Reset the board back to the starting point
       */
      virtual void InitBoard( );

      /*
       *  Set the total number of turns that have been completed.
       */
      virtual bool SetTotalMoves( unsigned int total_moves );

      /*
       * Set the last moves by a player
       */
      virtual bool SetLastMove( int player_num, const MoveData &move );

      /*
       * Set the seconds consumed by a player
       */
      virtual bool SetPlayerTime( int player_num, const double &time );
      
      /*
       * Configure the maximum time per player
       */
      virtual void SetMaxPlayerTime( const double max_time );

    protected:
      friend class Environment;
      /*
       * The board data
       */
      BoardData board;

      unsigned int  number_of_turns;
      std::vector< unsigned int >   number_of_player_turns;
      bool legal_moves_valid;
      std::vector< MoveData > legal_moves;
      std::vector< MoveData > last_moves;
      std::vector< double >   player_times;
      double                  max_player_time;
      
    private:
    };

  }
}

std::ostream& operator<<( std::ostream& os, const ai::Jetan::MoveData& move );
std::ostream& operator<<( std::ostream& os, const ai::Jetan::Piece& piece );

#endif /* _JETANBOARD_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
