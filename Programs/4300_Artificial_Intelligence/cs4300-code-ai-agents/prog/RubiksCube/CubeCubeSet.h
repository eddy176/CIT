#ifndef _CUBECUBESET_H_
#define _CUBECUBESET_H_

#include "CubeModel.h"
#include <map>
#include <string>

namespace ai {
  namespace rubiks {

    class CubeSet {
    public:
      CubeSet( );
      void clearDefinedCubes( );
      const std::map< std::string, Cube >& getDefinedCubes( ) const;
      const Cube& getDefinedCube( const std::string& cube_name ) const;
      bool cubeIsDefined( const std::string& cube_name ) const;
      int defineCube( const std::string& cube_name, const Cube& cube );

    protected:
      std::map< std::string, Cube > mDefinedCubes;

    private:

    };

  }
}
#endif /* _CUBECUBESET_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
