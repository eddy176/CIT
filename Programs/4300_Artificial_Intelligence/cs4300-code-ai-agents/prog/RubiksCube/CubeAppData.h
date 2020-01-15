#ifndef _CUBEAPPDATA_H_
#define _CUBEAPPDATA_H_

#include "CubeModel.h"
#include "CubeAppConfig.h"
#include "CubeAppCommand.h"
#include "CubeMoveSet.h"
#include "CubeCubeSet.h"
#include "CubeProblem.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace ai {
  namespace rubiks {

    struct AppData {

      AppData( std::istream &is_in, std::ostream &os_in );
      int setLegalMoves( );
      AppConfig config;
      Cube cube;
      std::vector< Cube > goal_cubes;
      std::istream &is;
      std::ostream &os;

      std::vector< std::string > words;  // for line-by-line processing
      std::map< std::string, ActionRecord > actions;
      MoveSet move_set;
      CubeSet cube_set;
      bool    done;

      bool        solution_valid;
      std::string solution;
    };
  }
}


#endif /* _CUBEAPPDATA_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
