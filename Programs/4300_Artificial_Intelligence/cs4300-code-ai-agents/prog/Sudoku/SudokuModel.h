#ifndef _SUDOKUMODEL_H_
#define _SUDOKUMODEL_H_
#include <vector>
#include <string>
#include <iostream>

namespace example {
  namespace Sudoku {

    class Piece	{
    public:
      // 1-N or 0 if not set
      int value;
			
      // 1 if part of the puzzle starter, 0 otherwise
      int fixed;
    };

    /* A column is a vertical set of N pieces
     * A row is a horizontal set of N pieces
     * A box is a sqrt(N) x sqrt(N) set of N pieces
     */
    class Board {
    public:
      /* Fills board with all wildcards (0) */
      /* sets the size of columns and rows to size_in */
      Board(int size_in);
      Board();
      
      /* delete allocated memory */
      ~Board();
      
      /* */
      void Delete();
      
      /* copy constructor */
      Board(const Board &rhs);
			
      /* assignment operator */
      Board &operator=(const Board &rhs);
      
      /* comparison operators */
      bool operator==(const Board &rhs) const;
      bool operator<(const Board &rhs) const;
      
      /* Resize the board and set all to wildcards */
      bool Resize(int size_in);
      
      /* input_stream is a row-by-row representation of the board.
       * whitespace separates neighboring values.
       * digits 1-9 for size 9 puzzles.  
       * letters a-g are possible for size 16 puzzles.
       * letters h-p are possible for size 25 puzzles.
       * letters q-zA are possible for size 36 puzzles.
       * '.' for wildcards.
       * Assumes that the Board has already been properly Resize()'d.
       */
      bool Fill(std::istream& input_stream);
      
      /* Filename names a file that contains a
       * board description in standard format,
       * one line per row, columns seperated by
       * white space.  Non-fixed locations are
       * marked as '.'.  
       * Assumes that the Board has already been properly Resize()'d.
       */
      bool FillFromFile(const std::string& filename);
      
      /* Display board to the output stream.
       * Pseudo-pretty print
       * Extra debugging info also shown.
       * not the inverse of Fill().
       */
      bool Display(std::ostream &os) const;
      
      /* Send board to a stream.
       * This is the inverse of Fill()
       */
      bool ToStream(std::ostream &os) const;
      bool ToStream(std::ostream &os, const bool with_whitespace) const;
      
      /* Generate a string representation of
       * the board, with no whitespace.
       */
      std::string ToString() const;
      
      /*
       * Get the size of the board
       */
      int GetSize( ) const;
			
      /*
       * Get the size of a box in the board
       */
      int GetBoxSize( ) const;
			
      /*
       * Get the value of the piece[row][col].
       */
      int GetValue(int row, int col) const;
			
      /*
       * Set the value of the piece[row][col].
       */
      bool SetValue(int row, int col, int value);
			
      /* Fill a single box, randomly filling the empty pieces
       * with unused values.
       */
      bool FillBox(int row, int col);
			
      /* For each box, randomly fill the empty pieces with values
       * not already used.  This completes the values that are not
       * fixed for a complete-state formulation
       */
      bool FillBoxes();
      
      /* Count the number of conflicts in row, column and
       * box for a single piece.
       */
      int CountPieceConflicts(int row, int col) const;
			
      /* Count the number of conflicts for all pieces.
       * Actually double counts right now, but monotonicity allows this.
       */
      int CountConflicts() const;
			
      /* Find the neighbor state with the least number of conflicts.
       * Only consider neighbors with swaps within the box specified
       * by row and col.
       * Returns the result in "b".
       */
      int BestNeighborBox(Board &b, int row, int col, int& neighbors_generated) const;
			
      /* Find the neighbor state with the least number of conflicts.
       * Returns the conflict count, stores the board in best_board.
       */
      int BestNeighbor(Board &best_board, int& neighbors_generated) const;
      
      /* For the box specified by row,col, randomly swap a pair of
       * non-fixed pieces.
       * Returns the result in "b".
       * Return value is the conflict count.
       */
      int RandomNeighborBox(Board &b, int row, int col) const;
      
      /* Find a random neighbor state.
       * Returns the conflict count, stores the board in random_board.
       */
      int RandomNeighbor(Board &random_board) const;


      /* Set row and col to the position of the first wildcard
       * in the puzzle.  Both set to -1 if there are none.
       * Returns true if found, otherwise false.
       */
      bool FindFirstWildcard( int& row, int& col) const;
      
      /* Find the available values for position ( row, col )
       * such that no box, row or column conflicts exist.
       * Returns true if > 0 found.
       */
      bool FindAvailableValues( const int row, const int col, std::vector<int>& values) const;
      
      /* Return true if no wildcards are present,
       * and there are no conflicts.
       */
      bool IsSolved( ) const;
      
    protected:
      int mSize;
      int mBoxSize;
      std::vector< std::vector< Piece > > mPieces;
    };
  }
}

#endif /* _SUDOKUMODEL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
