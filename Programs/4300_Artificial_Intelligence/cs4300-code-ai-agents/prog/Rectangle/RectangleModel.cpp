#include "RectangleModel.h"

#include <vector>
#include <sstream>

namespace ai {
  namespace rectangle {

    bool Square::operator==(const Square &rhs) const {
      return ((this->x == rhs.x) && (this->y == rhs.y));
    }

    bool Square::operator!=(const Square &rhs) const {
      return !(*this == rhs);
    }

    bool Square::operator<(const Square &rhs) const {
      if(this->x < rhs.x) { 
        return true; 
      }
      else if(rhs.x < this->x) {
        return false; 
      }
      else {
        if(this->y < rhs.y) { 
          return true; 
        }
        else if(rhs.y < this->y) { 
          return false; 
        }
      }
      return false;
    }

    bool Piece::operator==(const Piece &rhs) const {
      unsigned int i;
      for(i = 0; i < sizeof(this->squares)/sizeof(this->squares[0]); i++) {
        if(this->squares[i] != rhs.squares[i]) { 
          return false; 
        }
      }
      if(this->rotation != rhs.rotation) { 
        return false; 
      }
      if(this->flip != rhs.flip) { 
        return false; 
      }
      return true;
    }

    bool Piece::operator!=(const Piece &rhs) const {
      return !(*this == rhs);
    }

    bool Piece::operator<(const Piece &rhs) const {
      unsigned int i;
      for(i = 0; i < sizeof(this->squares)/sizeof(this->squares[0]); i++) {
        if(this->squares[i] < rhs.squares[i]) { 
          return true; 
        }
        if(rhs.squares[i] < this->squares[i]) { 
          return false; 
        }
      }
      if(this->rotation < rhs.rotation) { 
        return true; 
      }
      if(rhs.rotation < this->rotation) { 
        return false;
      }
      if(this->flip < rhs.flip) { 
        return true; 
      }
      if(rhs.flip < this->flip) { 
        return false; 
      }
      return false;
    }

    std::string Piece::DisplayString( char c ) const {
      int minx, miny;
      unsigned int x, y, i;
      char grid[ 5 ][ 5 ];
      for( y = 0; y < 5; y++ ) {
        for( x = 0; x < 5; x++ ) {
          grid[ y ][ x ] = '.';
        }
      }
      minx = 5;
      miny = 5;
      for( i = 0; i < 5; i++ ) {
        if( squares[ i ].x < minx ) {
          minx = squares[ i ].x;
        }
        if( squares[ i ].y < miny ) {
          miny = squares[ i ].y;
        }
      }

      for( i = 0; i < 5; i++ ) {
        x = squares[ i ].x - minx;
        y = squares[ i ].y - miny;
        if( squares[ i ].x == 0 && squares[ i ].y == 0 ) {
          grid[y][x] = c + 'A' - 'a';
        } else {
          grid[y][x] = c;
        }
      }
      
      std::stringstream ss;

      for( y = 0; y < 5; y++ ) {
        for( x = 0; x < 5; x++ ) {
          ss << grid[ y ][ x ];
        }
        ss << std::endl;
      }
      
      return ss.str( );
    }

    Move::Move(const unsigned int p, const int r, const int f, const int x_in, const int y_in) 
      : which_piece(p), rotation(r), flip(f), x(x_in), y(y_in) {
    }
    
    double Move::getCost( ) const {
      return 1.0;
    }
    
    std::string Move::DisplayString( ) const {
      std::stringstream ss;
      ss << (char)( 'a' + which_piece )
         << "@" << x << "," << y << ":" << rotation << ":" << flip;
      return ss.str( );
    }

    Model::Model( ) 
      : board_width(10),
        board_height(6),
        use_flood_fill( false ) {
      Init( board_width, board_height );
    }
    
    Model::Model(int board_width_in, int board_height_in)
      : board_width(board_width_in),
        board_height(board_height_in),
        use_flood_fill( false ) {
      Init( board_width, board_height );
    }

    Model::Model(const Model &rhs) 
      : board_width(rhs.board_width),
        board_height(rhs.board_height),
        use_flood_fill( rhs.use_flood_fill ) {
      unsigned int i;
      for(i = 0; i < rhs.pieces.size(); i ++) {
        pieces.push_back(rhs.pieces[i]);
      }
      int x, y;
      board.resize(board_width);
      for(x = 0; x < board_width; x++) {
        board[x].resize(board_height);
        for(y = 0; y < board_height; y++) {
          board[x][y] = rhs.board[x][y];
        }
      }
    }

    Model::~Model() {
    }

    bool Model::operator==( const Model& rhs ) const {
      if( board_width != rhs.board_width || board_height != rhs.board_height ) {
        return false;
      }
      int x, y;
      for(y = 0; y < board_height; y++) {
        for(x = 0; x < board_width; x++) {
          if( board[x][y] != rhs.board[x][y] ) {
            return false;
          }
        }
      }
      return true;
    }

    bool Model::operator<( const Model& rhs ) const {
      if( board_width < rhs.board_width ) {
        return true;
      } else if( board_width > rhs.board_width ) {
        return false;
      }
      if( board_height < rhs.board_height ) {
        return true;
      } else if( board_height > rhs.board_height ) {
        return false;
      }

      int x, y;
      for(y = 0; y < board_height; y++) {
        for(x = 0; x < board_width; x++) {
          if( board[x][y] < rhs.board[x][y] ) {
            return true;
          } else if( board[x][y] > rhs.board[x][y] ) {
            return false;
          }
        }
      }
      return false;
    }

    bool Model::ApplyMove( const Move& move ) {
      return PlacePiece( move.which_piece, move.rotation, move.flip, move.x, move.y );
    }

    bool Model::PlacePiece(unsigned int which_piece,
                           int rotation, int flip, int x, int y) {
      unsigned int i;
      int x1, y1;
      // loop over squares in the piece to be placed
      for(i = 0; i < 5; i++) {
        Transform(pieces[which_piece].squares[i].x,
                  pieces[which_piece].squares[i].y,	
                  rotation, flip, 
                  x, y,
                  x1, y1);
        // this square would be out of the board
        if(x1 < 0 || x1 >= board_width || y1 < 0 || y1 >= board_height) {
          return false;
        }
        // this square would be on top of an already placed piece's square
        if(board[x1][y1] != ' ') { 
          return false; 
        }
      }

      pieces[which_piece].x_orig   = x;
      pieces[which_piece].y_orig   = y;
      pieces[which_piece].rotation = rotation;
      pieces[which_piece].flip     = flip;
      pieces[which_piece].placed   = true;
      
      // place the piece's squares on the board
      for(i = 0; i < 5; i++) {	
        Transform(pieces[which_piece].squares[i].x,
                  pieces[which_piece].squares[i].y,	
                  pieces[which_piece].rotation, pieces[which_piece].flip, 
                  pieces[which_piece].x_orig, pieces[which_piece].y_orig,
                  x1, y1);		
        board[x1][y1] = 'a' + which_piece;
      }
	
      return BoardUsable();
    }

    bool Model::ClearPiece(unsigned int which_piece) {
      if( which_piece >= pieces.size( ) ) {
        return false;
      }
      if( !pieces[ which_piece ].placed ) {
        return false;
      }

      unsigned int i;
      int x1, y1;
      // loop over squares in the piece to be cleared
      for(i = 0; i < 5; i++) {
        Transform(pieces[which_piece].squares[i].x,
                  pieces[which_piece].squares[i].y,	
                  pieces[which_piece].rotation, pieces[which_piece].flip, 
                  pieces[which_piece].x_orig, pieces[which_piece].y_orig,
                  x1, y1);
        // this square would be out of the board
        if(x1 < 0 || x1 >= board_width || y1 < 0 || y1 >= board_height) {
          return false;
        }
        // this square isn't the piece in question
        if(board[x1][y1] != (char)('a' + which_piece)) { 
          return false; 
        }
      }

      // clear the piece's squares on the board
      for(i = 0; i < 5; i++) {	
        Transform(pieces[which_piece].squares[i].x,
                  pieces[which_piece].squares[i].y,	
                  pieces[which_piece].rotation, pieces[which_piece].flip, 
                  pieces[which_piece].x_orig, pieces[which_piece].y_orig,
                  x1, y1);		
        board[x1][y1] = ' ';
      }

      pieces[which_piece].x_orig   = 0;
      pieces[which_piece].y_orig   = 0;
      pieces[which_piece].rotation = 0;
      pieces[which_piece].flip     = 0;
      pieces[which_piece].placed   = false;

      return true;
    }

    void Model::Init(int board_width_in, int board_height_in) {
      board_width = board_width_in;
      board_height = board_height_in;

      Piece p1;
      int i = 0;
      
      // create all pieces
      /*  
       *   x
       *  xxx
       *	 x
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = -1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 1;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = -1;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 1;
      p1.max_flip     = 1;
      pieces.push_back(p1);

      /*  
       *   xxxxx 
       *	
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 2;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 3;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 4;
      p1.squares[i++].y = 0;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 2;
      p1.max_flip     = 1;
      pieces.push_back(p1);

      /*  
       *  x
       *  xx
       *   xx
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 1;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 1;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 2;
      p1.squares[i].x   = 2;
      p1.squares[i++].y = 2;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 1;

      pieces.push_back(p1);


      /*   x
       *   x
       *	xxx
       */
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 2;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = -1;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = -2;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 1;

      pieces.push_back(p1);



      /*    xx
       *    x
       *	 xx
       */
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = -1;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = -2;
      p1.squares[i].x   = 2;
      p1.squares[i++].y = -2;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 2;
      p1.max_flip     = 2;
      pieces.push_back(p1);

      /*   x x
       *   xxx 
       *	 
       */
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = -1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = -1;
      p1.squares[i].x   = -1;
      p1.squares[i++].y = -1;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 1;

      pieces.push_back(p1);

      /*  xxx
       *  x 
       *	x
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 2;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = -1;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = -2;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 1;

      pieces.push_back(p1);


      /*    xx
       *	xxx
       */
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = -1;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = -2;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = -2;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = -3;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 2;

      pieces.push_back(p1);


      /*   x
       *   xxxx 
       *	
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 1;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 2;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 3;
      p1.squares[i++].y = 0;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 2;

      pieces.push_back(p1);



      /*   x
       *   x
       *   xx
       *	 x
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 1;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 2;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 3;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 2;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 2;

      pieces.push_back(p1);


      /*  
       *  x
       *  xx
       *  xx
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 1;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 2;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 1;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 2;

      pieces.push_back(p1);


      /*  
       *  x
       *  xx
       * xx
       */		
      i = 0;
      p1.squares[i].x   = 0;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 0;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 1;
      p1.squares[i].x   = 1;
      p1.squares[i++].y = 2;
      p1.squares[i].x   = 2;
      p1.squares[i++].y = 1;
      p1.rotation = 0;
      p1.flip     = 0;
      p1.placed   = 0;
      p1.max_rotation = 4;
      p1.max_flip     = 2;

      pieces.push_back(p1);

      Reset( board_width, board_height );
    }

    void Model::Reset(int board_width_in, int board_height_in) {
      board_width = board_width_in;
      board_height = board_height_in;

      int x, y;
      // empty board
      board.resize(board_width);
      for(x = 0; x < board_width; x++) {
        board[x].resize(board_height);
        for(y = 0; y < board_height; y++) {
          board[x][y] = ' ';
        }
      }
      unsigned int i;
      for( i = 0; i < pieces.size( ); i++ ) {
        pieces[ i ].rotation = 0;
        pieces[ i ].flip = 0;
        pieces[ i ].placed = 0;
      }
    }

    bool Model::IsSolved() const {
      int x, y;
      for(y = 0; y < board_height; y++) {
        for(x = 0; x < board_width; x ++) {
          if(board[x][y] == ' ') {
            return false;
          }
        }
      }
      return true;
    }
    
    int flood_fill_multiple_of_5_aux( std::vector< std::vector< char > >& tmp_board, unsigned int i, unsigned int j, char curr_filler ) {
      int count = 0;
      if( i >= tmp_board.size( ) ) {
        // pass
      } else if( j >= tmp_board[ i ].size( ) ) {
        // pass
      } else if( tmp_board[ i ][ j ] == ' ' ) {
        tmp_board[ i ][ j ] = curr_filler;
        count ++;
        count += flood_fill_multiple_of_5_aux( tmp_board, i - 1, j, curr_filler );
        count += flood_fill_multiple_of_5_aux( tmp_board, i + 1, j, curr_filler );
        count += flood_fill_multiple_of_5_aux( tmp_board, i, j - 1, curr_filler );
        count += flood_fill_multiple_of_5_aux( tmp_board, i, j + 1, curr_filler );
      }
      return count;
    }

    bool flood_fill_multiple_of_5( std::vector< std::vector< char > > tmp_board ) {
      char curr_filler = 'Z';
      unsigned int i, j;
      int ok = 1;
      int count;
      for( i = 0; i < tmp_board.size( ); i++ ) {
        for( j = 0; j < tmp_board[ i ].size( ); j++ ) {
          count = flood_fill_multiple_of_5_aux( tmp_board, i, j, curr_filler );
          if( (count % 5) != 0 ) {
            ok = 0;
          }
          if( count > 0 ) {
            curr_filler--;
          }
        }
      }
      /*
      char curr_filler = 'Z';
      int count = 0;
      int ok = 1;
      unsigned int i, j, ii, jj;
      for( i = 0; i < tmp_board.size( ); i++ ) {
        for( j = 0; j < tmp_board[ i ].size( ); j++ ) {
          if( tmp_board[ i ][ j ] == ' ' ) {
            tmp_board[ i ][ j ] = curr_filler;
            count ++;
            for( ii = i; ii < tmp_board.size( ); ii++ ) {
              for( jj = 0; jj < tmp_board[ ii ].size( ); jj++ ) {
                if( tmp_board[ ii ][ jj ] == ' ' 
                    && ( ( ii > 0 && tmp_board[ ii - 1 ][ jj ] == curr_filler )
                         || ( jj > 0 && tmp_board[ ii ][ jj - 1 ] == curr_filler ) ) ) {
                  tmp_board[ ii ][ jj ] = curr_filler;
                  count ++;
                }
              }
              for( jj = tmp_board[ ii ].size( ); jj > 0; jj-- ) {
                if( tmp_board[ ii ][ jj-1 ] == ' ' 
                    && ( ( ii > 0 && tmp_board[ ii - 1 ][ jj - 1 ] == curr_filler )
                         || ( jj < tmp_board[ ii ].size( ) && tmp_board[ ii ][ jj ] == curr_filler ) ) ) {
                  tmp_board[ ii ][ jj - 1 ] = curr_filler;
                  count ++;
                }
              }
            }
            if( count % 5 != 0 ) {
              ok = 0;
            }
            count = 0;
            curr_filler--;
          }
        }
      }
      */
      /*
      if( false && !ok ) {
        if( ok ) {
          std::cout << "OK" << std::endl;
        } else {
          std::cout << "BAD" << std::endl;
        }
        for(i = 0; i < tmp_board.size( ); i++) {
          for(j = 0; j < tmp_board[ i ].size( ); j++) {
            if( tmp_board[i][j] == ' ' ) {
              std::cout << '.';
            } else {
              std::cout << tmp_board[i][j];
            }
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
      }
      */
      return ok == 1;
    }

    bool Model::BoardUsable() const {
      if( use_flood_fill ) {
        return flood_fill_multiple_of_5( board );
      } else {
        return true;
      }

      /*
      // make sure each empty board position has at least 1 empty neighbor.
      // this could be made stronger by checking empty regions for multiples of 5.
      int x, y;
      // the 4 direct neighbors, in direction
      int xn[4] = { 1, -1, 0, 0 };
      int yn[4] = { 0, 0, 1, -1 };
      int i;
      int x1, y1;
      bool ok;

      for(y = 0; y < board_height; y++) {
        for(x = 0; x < board_width; x ++) {
          if(board[x][y] == ' ') {
            ok = false;
            for(i = 0; i < 4; i++) {
              x1 = x + xn[i];
              y1 = y + yn[i];
              if(x1 >= 0 && x1 < board_width && y1 >= 0 && y1 < board_height) {
                if(board[x1][y1] == ' ') {
                  ok = true;
                  break;
                }
              }
            }
            if(! ok) { 
              return false; 
            }
          }
        }
      }

      return true;
      */
    }

    void Model::Transform(int x_in, int y_in, int rot_in, int flip_in,
                          int x_orig_in, int y_orig_in, 
                          int &x_out, int &y_out) const {
      switch(rot_in) {
      case 0:
        x_out = x_in;
        y_out = y_in;
        break;
      case 1:
        x_out = -y_in;
        y_out = x_in;
        break;
      case 2:
        x_out = -x_in;
        y_out = -y_in;
        break;
      case 3:
        x_out = y_in;
        y_out = -x_in;
        break;
      }

      switch(flip_in) {
      case 0:
        break;
      case 1:
        x_out = -x_out;
        break;
      }
      x_out += x_orig_in;
      y_out += y_orig_in;
    }
    
    int Model::GetWidth() const {
      return board_width;
    }
    int Model::GetHeight() const {
      return board_height;
    }

    const Piece& Model::GetPiece( int i ) const {
      return pieces[ i ];
    }

    unsigned int Model::GetNumPieces( ) const {
      return pieces.size( );
    }

    std::string Model::DisplayString( ) const {
      std::stringstream ss;

      unsigned int i, j;
      std::vector< std::string > piece_strings;
      std::vector< unsigned int > piece_string_starts;
      for( i = 0; i < pieces.size( ); i++ ) {
        if( !pieces[ i ].placed ) {
          piece_strings.push_back( pieces[ i ].DisplayString( 'a' + i ) );
          piece_string_starts.push_back( 0 );
        }
      }
      
      for( i = 0; i < 5; i++ ) {
        for( j = 0; j < piece_strings.size( ); j++ ) {
          std::string::size_type next = piece_strings[ j ].find( '\n', piece_string_starts[ j ] );
          if( next != std::string::npos ) {
            ss << piece_strings[ j ].substr( piece_string_starts[ j ], next - piece_string_starts[ j ] - 1 );
            piece_string_starts[ j ] = next + 1;
          } else {
            ss << "     ";
          }
          ss << " ";
        }
        ss << std::endl;
      }
      ss << std::endl;

      int x, y;
      for(y = 0; y < board_height; y++) {
        for(x = 0; x < board_width; x++) {
          if( board[x][y] == ' ' ) {
            ss << '.';
          } else {
            ss << board[x][y];
          }
        }
        ss << std::endl;
      }
      return ss.str( );
    }
    
    void Model::SetUseFloodFill( bool value ) {
      use_flood_fill = value;
    }

  }
}
