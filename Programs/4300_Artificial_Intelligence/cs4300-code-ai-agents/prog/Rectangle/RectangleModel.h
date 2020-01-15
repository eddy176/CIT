#ifndef _RECTANGLEMODEL_H_
#define _RECTANGLEMODEL_H_
#include <vector>
#include <iostream>
#include <string>

namespace ai {
  namespace rectangle {

    class Square {
    public:
      int x;
      int y;
      bool operator==(const Square &rhs) const;
      bool operator!=(const Square &rhs) const;
      bool operator<(const Square &rhs) const;
    };

    class Piece {
    public:
      Square squares[5];
      int rotation;
      int flip;
      int x_orig;
      int y_orig;
      bool placed;
      int max_rotation;
      int max_flip;
      bool operator==(const Piece &rhs) const;
      bool operator!=(const Piece &rhs) const;
      bool operator<(const Piece &rhs) const;
      std::string DisplayString( char c ) const;
    };

    class Move {
    public:
      Move(const unsigned int p, const int r, const int f, const int x_in, const int y_in);
      unsigned int which_piece;
      int rotation;
      int flip;
      int x;
      int y;
      double getCost( ) const;
      std::string DisplayString( ) const;
    };

    class Model {
    public:
      Model( );
      Model(int board_width_in, int board_height_in);
      Model(const Model &rhs);
      virtual ~Model();

      bool operator==( const Model& rhs ) const;
      bool operator<( const Model& rhs ) const;

      bool ApplyMove( const Move& move );
      bool PlacePiece(unsigned int which_piece,
                      int rotation, int flip, int x, int y);
      bool ClearPiece(unsigned int which_piece);

      void Init(int board_width_in, int board_height_in);
      void Reset(int board_width_in, int board_height_in);
      bool IsSolved() const;
      bool BoardUsable() const;
      void Transform(int x_in, int y_in, int rot_in, int flip_in,
                     int x_orig_in, int y_orig_in, 
                     int &x_out, int &y_out) const;

      int GetWidth() const;
      int GetHeight() const;
      const Piece& GetPiece( int i ) const;
      unsigned int GetNumPieces( ) const;
      std::string DisplayString( ) const;

      void SetUseFloodFill( bool value );

    protected:
      std::vector<Piece> pieces;
      std::vector<std::vector<char> > board;

      int board_width;
      int board_height;

      bool use_flood_fill;

    private:
    };


  }
}

#endif /* _RECTANGLEMODEL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
