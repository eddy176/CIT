#ifndef _CUBEMOVESET_H_
#define _CUBEMOVESET_H_

#include "CubeModel.h"
#include <string>
#include <vector>
#include <map>

namespace ai {
  namespace rubiks {

    class MoveSet {
    public:
      MoveSet( );
      void clearMoves( );
      void addBasicMoves( );
      void addHalfTurnMoves( );
      void addSliceMoves( );
      void addHalfTurnSliceMoves( );
      void addMove( const std::string& name, const Move& move );
      int  addMovesByName( const std::vector< std::string >& move_names );
      const std::map< std::string, Move >& getMoves( ) const;
      bool moveExists( const std::string& move_name ) const;
      const Move& getMove( const std::string& move_name ) const;
      const Move& getRandomMove( ) const;

      bool moveIsDefined( const std::string& name ) const;
      int  defineMove( const std::string& name, const Move& move );
      int  defineMove( const std::string& name, const std::vector< std::string >& move_names );
      const std::map< std::string, Move >& getDefinedMoves( ) const;
      const Move& getDefinedMove( const std::string& move_name ) const;

    protected:
      std::map< std::string, Move > mMoves;
      std::vector< std::string >    mKeys;
      std::map< std::string, Move > mDefinedMoves;

    private:

    };

  }
}

#endif /* _CUBEMOVESET_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
