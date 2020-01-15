#include "CubeCubeSet.h"
#include "CubeAppCommand.h"
#include <map>
#include <string>

namespace ai {
  namespace rubiks {

    CubeSet::CubeSet( ) {
      clearDefinedCubes( );
    }

    void CubeSet::clearDefinedCubes( ) {
      mDefinedCubes.clear( );
    }

    const std::map< std::string, Cube >& CubeSet::getDefinedCubes( ) const {
      return mDefinedCubes;
    }
    
    const Cube& CubeSet::getDefinedCube( const std::string& cube_name ) const {
      return mDefinedCubes.at( cube_name );
    }

    bool CubeSet::cubeIsDefined( const std::string& cube_name ) const {
      return mDefinedCubes.count( cube_name ) > 0;
    }

    int CubeSet::defineCube( const std::string& cube_name, const Cube& cube ) {
      if( cubeIsDefined( cube_name ) ) {
        return EXIT_USAGE;
      }
      mDefinedCubes[ cube_name ] = cube;
      return EXIT_OK;
    }

  }
}
