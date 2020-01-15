#ifndef _AI_SCAVENGER_H_
#define _AI_SCAVENGER_H_

#include <string>
#include <vector>
#include <map>
#include <thread>

#include <ai_xy.h>

#include <Agent/Scavenger/ScavengerLocation.h>              // uses
#include <Agent/Scavenger/ScavengerAction.h>                // uses Location
#include <Agent/Scavenger/ScavengerCellInterface.h>         // uses
#include <Agent/Scavenger/ScavengerObject.h>                // uses
#include <Agent/Scavenger/ScavengerAgent.h>                 // uses Cell, Interface, Object
#include <Agent/Scavenger/ScavengerBase.h>                  // uses Agent
#include <Agent/Scavenger/ScavengerCell.h>                  // uses Location, Base, Object, Interface
#include <Agent/Scavenger/ScavengerEnvironment.h>           // uses Agent, Cell, Object, Location

#include <Agent/Scavenger/ScavengerDisplayDriver.h>         // 

#include <Agent/Scavenger/ScavengerTexture.h>               // Textures
#include <Agent/Scavenger/ScavengerModel.h>                 // Models
#include <Agent/Scavenger/ScavengerEnvironmentModel.h>      // Environment Model
#include <Agent/Scavenger/ScavengerHover.h>                 // Hover Agent
#include <Agent/Scavenger/ScavengerEnvironmentDisplay.h>    // 2D Display
#include <Agent/Scavenger/ScavengerEnvironmentDisplay3D.h>  // 3D Display
#include <Agent/Scavenger/ScavengerEnvironmentDriver.h>     // Environment Driver


#endif /* _AI_SCAVENGER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
