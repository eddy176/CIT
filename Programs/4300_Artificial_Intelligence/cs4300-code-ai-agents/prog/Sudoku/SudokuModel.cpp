#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "SudokuModel.h"

namespace example {
  namespace Sudoku {
    /* Board class */

    Board::Board(int size_in)
      : mSize(0),
        mBoxSize(0) {
      this->Resize(size_in);
    }
		
    Board::Board()
      : mSize(0),
        mBoxSize(0) {
    }
    
    Board::~Board() {
      this->Delete();
    }
    
    void Board::Delete() {
      mSize = 0;
      mBoxSize = 0;
      mPieces.resize( 0 );
    }
		
    Board::Board(const Board &rhs)
      : mSize(0),
        mBoxSize(0) {
      *this = rhs;
    }

    Board &Board::operator=(const Board &rhs) {
      this->Delete();

      this->mSize = rhs.mSize;
      this->mBoxSize = rhs.mBoxSize;
			
      int i,j;
			this->mPieces.resize( this->mSize );
      for(i = 0; i < this->mSize; i++) {
        this->mPieces[i].resize( this->mSize );
        for(j = 0; j < this->mSize; j++) {
          mPieces[i][j] = rhs.mPieces[i][j];
        }
      }
			
      return *this;
    }
		
    bool Board::operator==(const Board &rhs) const {
      if(this->mSize != rhs.mSize) {
        return false;
      }
      int i,j;
      for(i = 0; i < this->mSize; i++) {
        for(j = 0; j < this->mSize; j++) {
          if(this->mPieces[i][j].value != rhs.mPieces[i][j].value) {
            return false;
          }
        }
      }
      return true;
    }
  
    bool Board::operator<(const Board &rhs) const {
      if(this->mSize < rhs.mSize) {
        return true;
      } else if(this->mSize > rhs.mSize) { 
        return false;
      }
      int i,j;
      for(i = 0; i < this->mSize; i++) {
        for(j = 0; j < this->mSize; j++) {
          if(this->mPieces[i][j].value < rhs.mPieces[i][j].value) {
            return true;
          } else if(this->mPieces[i][j].value > rhs.mPieces[i][j].value) {
            return false;
          }
        }
      }
      return true;
    }
  
  
    bool Board::Resize(int size_in) {
      this->Delete();
      this->mSize = size_in;
      this->mBoxSize = 0;
      while(this->mBoxSize * this->mBoxSize < this->mSize) {
        this->mBoxSize ++;
      }
			this->mPieces.resize( this->mSize );
      int i,j;
      for(i = 0; i < this->mSize; i++) {
        this->mPieces[i].resize( this->mSize );
        for(j = 0; j < this->mSize; j++) {
          mPieces[i][j].value = 0;
        }
      }
			
      return true;
    }
		
    bool Board::Fill(std::istream& stream) {
      std::string word;
      bool ret = true;
      int i, j;
      for( i = 0; i < this->mSize; i++ ) {
        for( j = 0; j < this->mSize; j++ ) {
          stream >> word;
          if( word.size() != 1 ) {
            // ERROR
            ret = false;
            continue;
          } else if( word[ 0 ] >= '1' && word[ 0 ] <= '9' ) {
            this->SetValue( i, j, word[ 0 ] - '0' );
            this->mPieces[i][j].fixed = true;
          } else if( word[ 0 ] >= 'a' && word[ 0 ] <= 'z' ) {
            this->SetValue( i, j, word[ 0 ] - 'a' + 10 );
            this->mPieces[i][j].fixed = true;
          } else if( word[ 0 ] >= 'A' && word[ 0 ] <= 'Z' ) {
            this->SetValue( i, j, word[ 0 ] - 'A' + 36 );
            this->mPieces[i][j].fixed = true;
          } else if( word[ 0 ] == '.' ) {
            this->SetValue( i, j, 0 );
            this->mPieces[i][j].fixed = false;
          } else {
            // ERROR
            ret = false;
          }
        }
      }
      return ret;
    }

    bool Board::FillFromFile(const std::string& filename) {

      std::ifstream fin( filename );
      if(!fin) {
        std::cout << "Error opening file: " << filename << std::endl;
        return false;
      }
      bool ret = true;
      ret &= this->Fill( fin );
      fin.close();
    
      return ret;
    }

    bool Board::Display( std::ostream &os ) const {
      int i,j;
      if(this->mSize <= 0) {
        return false;
      }
      
      int conflicts = this->CountConflicts();
      for(i = 0; i < this->mSize; i++) {
        if(i % this->mBoxSize == 0) {
          for(j = 0; j < this->mSize + 1; j++) {
            if(j % this->mBoxSize == 0) { 
              os << " + "; 
            }
            if(j < this->mSize) {
              os << "-"; 
            }
          }
          os << std::endl;
        }

        int *count = new int[this->mSize+1];
        std::memset(count, 0, (this->mSize+1) * sizeof(int));
        for(j = 0; j < this->mSize; j++) {
          count[mPieces[i][j].value]++;
          char c = mPieces[i][j].value + '0';
          if(c == '0') {
            c = '.';
          }
          if(j % this->mBoxSize == 0) {
            os << " | ";
          }
          os << c;
        }
        if(j % this->mBoxSize == 0) {
          os << " | ";
        }
        if(conflicts) {
          for(j = 1; j < this->mSize+1; j++) {
            if(count[j] == 0) {
              os  << "[" << j << "]";
            }
            if(count[j] > 1) {
              os  << j;
            }
          }
        }
        os << std::endl;
        delete [] count;
      }
    
      for(j = 0; j < this->mSize + 1; j++) {
        if(j % this->mBoxSize == 0) {
          os << " + ";
        }
        if(j < this->mSize) {
          os << "-";
        }
      }
      os << std::endl;

      if(conflicts) {
        for(j = 0; j < this->mSize; j++) {
          int *count = new int[this->mSize+1];
          std::memset(count, 0, (this->mSize+1) * sizeof(int));
          for(i = 0; i < this->mSize; i++) {
            count[mPieces[i][j].value]++;
          }
          for(i = 1; i < this->mSize+1; i++) {
            if(count[i] == 0) {
              os  << "[" << i << "]";
            }
            if(count[i] > 1) {
              os  << i;
            }
          }
          os << std::endl;
          delete [] count;
        }
      }
      return true;
    }

    bool Board::ToStream(std::ostream &os) const {
      return this->ToStream( os, true );
    }

    bool Board::ToStream(std::ostream &os, const bool with_whitespace) const {
      int i, j;
      for( i = 0; i < this->mSize; i++ ) {
        for( j = 0; j < this->mSize; j++ ) {
          char c;
          int v = this->mPieces[i][j].value;
          if( !this->mPieces[i][j].fixed && v == 0 ) {
            c = '.';
          } else if( v >= 1 && v <= 9 ) {
            c = '0' + v;
          } else if( v >= 10 && v <= 35 ) {
            c = 'a' + v - 10;
          } else if( v >= 36 && v <= 61 ) {
            c = 'A' + v - 36;
          } else { 
            // ERROR
            c = '!'; 
          }
          if( with_whitespace && j > 0 ) {
            os << " ";
          }
          os << c;
        }
        if( with_whitespace ) {
          os << std::endl;
        }
      }
      return true;
    }

    std::string Board::ToString() const {
      std::stringstream ss;
      this->ToStream( ss, false );
      return ss.str();
    }
  
    int Board::GetSize( ) const {
      return this->mSize;
    }
			
    int Board::GetBoxSize( ) const {
      return this->mBoxSize;
    }
			
    int Board::GetValue(int row, int col) const {
      return mPieces[row][col].value;
    }

    bool Board::SetValue(int row, int col, int value) {
      mPieces[row][col].value = value;
      return true;
    }

    bool Board::FillBox(int row, int col) {
      int *have = new int[this->mSize];
      std::memset(have, 0, (this->mSize) * sizeof(int));
      int *values = new int[this->mSize];
      std::memset(values, 0, (this->mSize) * sizeof(int));
      int nvalue = 0;
  
      int r_min = (row/this->mBoxSize) * this->mBoxSize;
      int c_min = (col/this->mBoxSize) * this->mBoxSize;
      int i,j;

      // find all the values that are fixed
      for(i = r_min; i < r_min + this->mBoxSize; i++) {
        for(j = c_min; j < c_min + this->mBoxSize; j++) {
          if(mPieces[i][j].fixed) {
            have[mPieces[i][j].value-1] = 1;
          }
        }
      }

      // find all the values the are not fixed
      for(i = 0; i < this->mSize; i++) {
        if(have[i] == 0) {
          values[nvalue] = i+1;
          nvalue ++;
        }
      }

      /* randomize the order of unfixed pieces */
      for(i = 0; i < nvalue; i++) {
        j = std::rand() % nvalue;
        int t = values[i];
        values[i] = values[j];
        values[j] = t;
      }

      // place the unfixed pieces
      int next_value = 0;
      for(i = r_min; i < r_min + this->mBoxSize; i++) {
        for(j = c_min; j < c_min + this->mBoxSize; j++) {
          if(!mPieces[i][j].fixed) {
            SetValue(i,j,values[next_value]);
            next_value++;
          }
        }
      }
      delete [] have;
      delete [] values;
      return true;
    }

    bool Board::FillBoxes() {
      int row, col;
      for(row = 0; row < this->mSize; row += this->mBoxSize) {
        for(col = 0; col < this->mSize; col += this->mBoxSize) {
          FillBox(row, col);
        }
      }
      return true;
    }

    int Board::CountPieceConflicts(int row, int col) const {
      int count = 0;
      int value = mPieces[row][col].value;
      int i;
      // count duplicate value in the row
      for(i = 0; i < this->mSize; i++) {
        if((i != row) &&
           (value == mPieces[i][col].value)) {
          count ++;
        }
      }
  
      // count duplicate value in the column
      for(i = 0; i < this->mSize; i++) {
        if((i != col) &&
           (value == mPieces[row][i].value)) {
          count ++;
        }
      }
  
      // count duplicate value in the box
      // this should always be 0
      int r_min = (row/this->mBoxSize) * this->mBoxSize;
      int c_min = (col/this->mBoxSize) * this->mBoxSize;
      int j;
      for(i = r_min; i < r_min + this->mBoxSize; i++) {
        for(j = c_min; j < c_min + this->mBoxSize; j++) {
          if((i != row) &&
             (j != col) &&
             (value == mPieces[i][j].value)) {
            count ++;
          }
        }
      }
  
      return count;
    }

    int Board::CountConflicts() const {
      int count = 0;
      int row, col;
      for(row = 0; row < this->mSize; row++) {
        for(col = 0; col < this->mSize; col++) {
          count += CountPieceConflicts(row, col);
        }
      }
      return count;
    }

    int Board::BestNeighborBox(Board &best_board, int row, int col, int& neighbors_generated) const {
      Board tmp(*this);
      int r_min = (row/this->mBoxSize) * this->mBoxSize;
      int c_min = (col/this->mBoxSize) * this->mBoxSize;
      int i,j;
      int ii,jj;
      int index_i, index_ii;

      int best_count = 0x7FFFFFFF;
      int count;
  
      // swap all pairs in this box
      for(i = r_min; i < r_min + this->mBoxSize; i++) {
        for(j = c_min; j < c_min + this->mBoxSize; j++) {
          index_i = i * this->mBoxSize + j;
          if(!tmp.mPieces[i][j].fixed) {
	      
            for(ii = r_min; ii < r_min + this->mBoxSize; ii++) {
              for(jj = c_min; jj < c_min + this->mBoxSize; jj++) {
                index_ii = ii * this->mBoxSize + jj;
                if(index_ii <= index_i) { continue; } // avoid duplicate swaps
			
                if(!tmp.mPieces[ii][jj].fixed) {
                  /* swap */
                  int t = tmp.mPieces[i][j].value;
                  tmp.mPieces[i][j].value   = tmp.mPieces[ii][jj].value;
                  tmp.mPieces[ii][jj].value = t;

                  count = CountConflicts();
                  neighbors_generated++;
                  if(count < best_count) {
                    best_count = count;
                    best_board = tmp;
                  }
			  
			  
                  /* unswap */
                  t = tmp.mPieces[i][j].value;
                  tmp.mPieces[i][j].value   = tmp.mPieces[ii][jj].value;
                  tmp.mPieces[ii][jj].value = t;
                }
              }
            }
	      
	      
          }
        }
      }
    
      return best_count;
    }

    int Board::BestNeighbor(Board &best_board, int& neighbors_generated) const {
      int best_count = 0x7FFFFFFF;
      int count;
      Board b;
    
      // for each box, examine neighbors
      int row, col;
      for(row = 0; row < this->mSize; row += this->mBoxSize) {
        for(col = 0; col < this->mSize; col += this->mBoxSize) {
          count = BestNeighborBox(b, row, col, neighbors_generated);
          if(count < best_count) {
            best_count = count;
            best_board = b;
          }
        }
      }
      return best_count;
    }

    int Board::RandomNeighborBox(Board &random_board, int row, int col) const {
      int r_min = (row/this->mBoxSize) * this->mBoxSize;
      int c_min = (col/this->mBoxSize) * this->mBoxSize;
      int i,j;
      int ii,jj;
      int index_i, index_ii;

      int count;

      int found = 0;
      do {
        i = std::rand() % this->mBoxSize + r_min;
        j = std::rand() % this->mBoxSize + c_min;
	
        ii = std::rand() % this->mBoxSize + r_min;
        jj = std::rand() % this->mBoxSize + c_min;
    
        index_i = i * this->mBoxSize + j;
        index_ii = ii * this->mBoxSize + jj;

        if((index_i != index_ii) &&
           !mPieces[i][j].fixed &&
           !mPieces[ii][jj].fixed) {
          /* copy current board */
          random_board = *this;
	    
          /* swap */
          int t = random_board.mPieces[i][j].value;
          random_board.mPieces[i][j].value   = random_board.mPieces[ii][jj].value;
          random_board.mPieces[ii][jj].value = t;

          /* count */
          count = random_board.CountConflicts();

          /* done */
          found = 1;
        }
      } while(!found);
	   
      return count;
    }

    int Board::RandomNeighbor(Board &random_board) const {
      int count;
    
      // randomly pick a box.
      int row, col;
      row = this->mBoxSize*(std::rand() % this->mBoxSize);
      col = this->mBoxSize*(std::rand() % this->mBoxSize);
      // Find a neighbor
      count = RandomNeighborBox(random_board, row, col);
  
      return count;
    }
  
    bool Board::FindFirstWildcard( int& w_row, int& w_col) const {
      int row, col;
      for(row = 0; row < this->mSize; row++) {
        for(col = 0; col < this->mSize; col++) {
          if( mPieces[row][col].value == 0 ) {
            w_row = row;
            w_col = col;
            return true;
          }
        }
      }
      w_row = w_col = -1;
      return false;
    }

    bool Board::FindAvailableValues( const int row, const int col, std::vector<int>& values) const {
      values.clear( );
      std::set< int > available;
      int i,j;
      for( i = 1; i <= this->mSize; i++ ) {
        available.insert( i );
      }

      int r_min = (row/this->mBoxSize) * this->mBoxSize;
      int c_min = (col/this->mBoxSize) * this->mBoxSize;
      for( i = r_min; i < r_min + this->mBoxSize; i++ ) {
        for( j = c_min; j < c_min + this->mBoxSize; j++ ) {
          available.erase( this->mPieces[ i ][ j ].value );
        }
      }
      for( i = 0; i < this->mSize; i++ ) {
        available.erase( this->mPieces[ i ][ col ].value );
      }
      for( j = 0; j < this->mSize; j++ ) {
        available.erase( this->mPieces[ row ][ j ].value );
      }
      std::set< int >::iterator it;
      for( it = available.begin( ); it != available.end( ); it++ ) {
        values.push_back( *it );
      }
      return values.size( ) > 0;
    }

    bool Board::IsSolved( ) const {
      int row, col;
      if( FindFirstWildcard( row, col ) ) {
        return false;
      }
      return CountConflicts( ) == 0;
    }

  }
}
