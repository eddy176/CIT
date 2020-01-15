#ifndef _TRIANGLEPUZZLE_H_
#define _TRIANGLEPUZZLE_H_

#include <vector>
#include <string>
#include <exception>
#include <iostream>

namespace ai {

  /* 
   * Board Positions are numbered as:
   *            0
   *           123
   *          45678
   * For bigger boards, the pattern continues
   *
   * Board edges are ordered as:
   *           0a3
   *          1bcd4
   *         2efghi5
   *          6 7 8
   * For bigger boards, the pattern continues
   *
   * See the data members below for more detailed information
   */
  
  class Exception: public std::exception {
  public:
    Exception( const std::string& msg );
    virtual const char* what() const throw();
  protected:
    std::string mMsg;
  };
  
  class TrianglePuzzle {
  public:
    /*
     * Constructors
     */
    TrianglePuzzle( );
    TrianglePuzzle( const size_t& size, const size_t& number_of_animal_types );
    TrianglePuzzle( const TrianglePuzzle& src);
    
    /* 
     * Getters to fetch information about the puzzle.
     *
     */
    // size of a side
    size_t getSize( ) const;
    // number of animal types
    size_t getAnimalSize( ) const;
    // number of movable pieces
    size_t getNumberOfPieces( ) const;
    // a string of length 3 from the specified board location, rotation is applied.
    const std::string getPiece( const size_t& number ) const;
    // a string of length 1.
    const std::string& getBoardEdge( const size_t& number ) const;

    /*
     * Setters and modifiers
     */
    // set the side size, wipes out any previous data, creates a solved random puzzle
    void setSize( const size_t& size );
    // set the maximum number of animal types, wipes out any previous data, creates a solved random puzzle
    void setAnimalSize( const size_t& animal_size );
    // a string of length 3 to the specified board location.
    void setPiece( const size_t& number, const std::string& s );
    // a string of length 1.
    void setBoardEdge( const size_t& number, const std::string& s );
    // shuffle the piece positions and rotations
    void shuffle( );
    // rotate the piece at position, cw_count times clockwise. 1 and 2 are valid values for cw_count.
    void rotate( const size_t& position, const size_t& cw_count );
    // trade the pieces at src and dst.  When the pieces move, they accept the rotation of their new locations.
    void swap( const size_t& src, const size_t& dst );
    // get a vector of possible rotation actions.  the pair contains position and cw_count values as first and second.
    std::vector< std::pair< size_t, size_t > > getRotateActions( ) const;
    // get a vector of possible swap actions.  the pair contains src and dst values as first and second.
    std::vector< std::pair< size_t, size_t > > getSwapActions( ) const;

    /*
     * Puzzle utility related methods
     */
    // The number of edges that match
    int utility( ) const;
    // The maximum number of edges that can match.
    int maxUtility( ) const;

    /*
     * These are only exposed as public for testing.  Don't call them!
     */
    void resizeVectors( );
    void makeRandomPuzzle( );
    void chooseAnimal( char& A, char& a ) const;
    void setPieceEdgeByBoard( const size_t& board_pos, const char& animal );
    void setPieceEdgeByNeighbor( const size_t& piece_number, const size_t& edge_number, const char& animal );
    void setPieceEdgeDirectly( const size_t& piece_position, const size_t& edge_number, const char& animal );
    void setBoardEdgeDirectly( const size_t& board_position, const char& animal );
    /* sets is_board to true if the neighbor is a board edge, otherwise false
     * sets dst_position to the index of the piece ( or board edge ) that is a neighbor
     * sets dst_edge to 0, 1, 2 the edge of the piece, if !is_board
     */
    void calcNeighbor( const size_t& position_number, const size_t& edge_number, size_t& dst_position, size_t& dst_edge, bool& is_board ) const;

  protected:
    
    size_t mSize; // size of one size of the puzzle
    size_t mAnimalSize; // number of animal types
    std::vector< std::string > mPieces;  /* the pieces
                                          * each value is a string of length 3
                                          * these are the letters of the animals in a clockwise order
                                          * lower case is "tail", upper case is "head"
                                          */
    std::vector< std::string > mBoard;   /* the board edge rows
                                          * each value is a string of length 1
                                          */
    std::vector< int > mPositions;       /* the positions of pieces in the board
                                          * the indexes are the same as for mPieces
                                          * the values are the board location of the piece
                                          */
    std::vector< int > mRotations;       /* the rotations of pieces in the board
                                          * the indexes are the same as for mPieces
                                          * the values are 0, 1, 2 for the rotation of the piece
                                          * 0 == "natural" position which is first edge down for 
                                          *   pointing up triangles and first edge up for pointing
                                          *   down triangles.
                                          * 1 == one clockwise rotation of the piece from natural position
                                          * 2 == two clockwise rotations of the piece from natural position
                                          */
    

  private:
  };

  std::ostream& operator<<( std::ostream& os, const TrianglePuzzle& p );
  std::istream& operator>>( std::istream& is, TrianglePuzzle& p );
}

  


#endif /* _TRIANGLEPUZZLE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
