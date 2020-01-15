#ifndef _CUBEMODEL_H_
#define _CUBEMODEL_H_
#include <iostream>
#include <string>
#include <vector>

namespace ai {
namespace rubiks {

/**************************************************************
 *
 * Facelet type
 *
 */

/* By storing the facelets as chars, each cube requires 54 bytes.
 * This is the best we can do without bit-packing, which would slow
 * down operations on the cube.
 */
typedef char Facelet; // wgrboy*

// a few handy constants
const int NUM_SIDES = 6;
const int NUM_FACELETS_PER_SIDE = 9;
const int NUM_FACELETS_TOTAL = NUM_SIDES * NUM_FACELETS_PER_SIDE;
const int NUM_CUBIES_TOTAL = 20;
const int NUM_EDGES_TOTAL = 12;
const int NUM_CORNERS_TOTAL = 8;

/*
 *
 * Facelet type
 *
 **************************************************************/

/**************************************************************
 *
 * Move class
 *
 */

/*
 * The Move class represents the abstract concept of 0 or more
 * 90 degree rotations of a face or slice.  For the 3x3x3 cube,
 * the base rotations are the 2 90-degree rotations of each of the
 * 6 faces, for 12 basic moves.  All other moves are compositions
 * of these 12 moves.  If this code is ever adapted for higher
 * dimension cubes, this concept will need to be amended, to
 * allow for middle slice moves.
 *
 * We add 6 additional basic moves.  These are the rotations of
 * the entire cube about one of the major axes: x, y, z, in both
 * directions.
 *
 * In concept, the move would be represented by a matrix
 * to map old state into new state.  However, since each facelet
 * goes from exactly one place to exactly one place, we
 * will just use a 1-d mapping vector for where each facelet moves.
 *
 */
// forward declaration the Cube class, needed by the Move class.
class Cube;

class Move {
public:
  // M_EQ is named strangely due to cmath's M_E, the constant for the numeric
  // constant e. Don't know why we can't scope it away, but we can't. M_IDENTITY
  // is, I, and causes the cube to stay the same. M_U is, U, the clockwise
  // rotation of the Upper face. M_UP is, U', the counter-clockwise rotation of
  // the Upper face. Similar for Lower, Front, Right, Left, and Down faces.
  enum BasicMove {
    M_IDENTITY,
    M_U,
    M_UP,
    M_L,
    M_LP,
    M_F,
    M_FP,
    M_R,
    M_RP,
    M_B,
    M_BP,
    M_D,
    M_DP,
    M_EQ,
    M_EP,
    M_M,
    M_MP,
    M_S,
    M_SP,
    M_X,
    M_XP,
    M_Y,
    M_YP,
    M_Z,
    M_ZP
  };

  // Default constructor, no initialization
  Move();
  // Construct one of the basic moves
  Move(const BasicMove &basic_move);

  // read-only access to the transform vector
  const std::vector<int> &getTransform() const;

  // the number of quarter-turns required to perform the move.
  // each of the x, y, z transforms add 0.001 to the cost.
  double getCost() const;

  // a textual representation of the move, e.g. "U F' D' L"
  const std::string &getName() const;

  /* replace this->mTransform contents with the composite of move1 followed by
   * move2 It's OK if move1 == *this. Don't get too tricky.  If move2 == *this,
   * errors will occur. Returns *this by reference.
   */
  Move &compose(const Move &move2, const Move &move1);
  /*
   * move3 = move1 * move2
   * is the same as
   * move3.compose( move1, move2 )
   */
  Move operator*(const Move &rhs) const;

  /*
   * cube2 = move * cube1
   * is the same as
   * cube2.applyMove( move, cube1 )
   */
  Cube operator*(const Cube &rhs) const;

protected:
  ///////////////////////////////////
  // hard-coded mappings of the basic moves
  void buildIdentity();
  void buildU();
  void buildUPrime();
  void buildL();
  void buildLPrime();
  void buildF();
  void buildFPrime();
  void buildR();
  void buildRPrime();
  void buildB();
  void buildBPrime();
  void buildD();
  void buildDPrime();
  void buildE();
  void buildEPrime();
  void buildM();
  void buildMPrime();
  void buildS();
  void buildSPrime();
  void buildX();
  void buildXPrime();
  void buildY();
  void buildYPrime();
  void buildZ();
  void buildZPrime();
  // hard-coded mappings of the basic moves
  ///////////////////////////////////

  /* dst_index = mTransform[ src_index ] */
  std::vector<int> mTransform;

  double mCost; // quarter-turn metric cost

  std::string mName; // notational name of the move
private:
};

/*
 *
 * Move class
 *
 **************************************************************/

/**************************************************************
 *
 * Cube class
 *
 */

class Cube {
public:
  // Default, constructs a solved cube
  Cube();

  // all facelets are the same
  // '*' facelets match anything
  bool operator==(const Cube &rhs) const;
  // one or more facelets are different
  bool operator!=(const Cube &rhs) const;
  // for the first differing facelet, lhs is less than rhs
  bool operator<(const Cube &rhs) const;

  // changes the cube into 54 unique facelet values
  // instead of the 6 color-based facelet values
  void buildTestPattern();

  // assigns to the facelets the values in the string
  // string must have exactly 54 characters
  // no checks for valid facelet values are made
  void assignFromString(const std::string &s);

  // assigns to the facelets the solved values
  void assignSolved();

  // returns the facelets for read-only access
  const std::vector<Facelet> &getFacelets() const;

  /* copies cube.mFacelets, being transformed by move.mTransform,
   * into this->mFacelets.
   * *this and cube must be different cubes.
   * returns *this by reference
   *
   * example: cube2.applyMove( move, cube1 );
   * cube2 is a copy of cube1, with move applied
   */
  Cube &applyMove(const Move &move, const Cube &cube);

  /* copies cube.mFacelets, being reverse transformed by
   * move.mTransform, into this->mFacelets.
   * *this and cube must be different cubes.
   * returns *this by reference
   *
   * example: cube2.applyMove( move, cube1 );
   * cube2 is a copy of cube1, with the reverse of move applied
   */
  Cube &unapplyMove(const Move &move, const Cube &cube);

  /*
   * Cube * Move safely does unapplyMove( )
   *
   * example: cube2 = cube1 * move;
   * cube2 is a copy of cube1, with the reverse of move applied
   */
  Cube operator*(const Move &rhs) const;

  /*
   * mergeCube modifies the current cube,
   * Cube + Cube produces a new cube, where
   *  '*' + 'x' -> 'x'
   *  'x' + '*' -> 'x'
   *  'x' + 'x' -> 'x'
   *  '*' + '*' -> '*'
   *  'x' + 'y' -> exception
   */
  Cube &mergeCube(const Cube &cube);
  /*
   * cube1 + cube2 is the same as
   * cube1.mergeCube( cube2 );
   */
  Cube operator+(const Cube &rhs) const;

  // display the cube in the "T" format
  std::ostream &tDisplay(std::ostream &os) const;
  // display the cube with the 54 facelets concatenated into 1 word
  std::ostream &oneWordDisplay(std::ostream &os) const;
  // display the cube with each face making a word, all in 1 line
  std::ostream &oneLineDisplay(std::ostream &os) const;

  /* replaces any '*' facelets with 'x' facelets */
  void wildcardToX();

protected:
  // the 54 facelets
  std::vector<Facelet> mFacelets;

private:
};
/*
 *
 * Cube class
 *
 **************************************************************/
} // namespace rubiks
} // namespace ai

#endif /* _CUBEMODEL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
