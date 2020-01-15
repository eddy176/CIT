#ifndef _SCAVENGERENVIRONMENTMODEL_
#define _SCAVENGERENVIRONMENTMODEL_

#if USE_GLUT

#include <ai_glut.h>

namespace ai {
  namespace Scavenger {
    class EnvironmentModel: public Model {
    public:

      struct CellModel {
        GLuint faces[4];
        GLuint textures[4];
        std::vector< bool > visited;
      };

      EnvironmentModel();                                                                 // Constructor
      virtual ~EnvironmentModel();                                                        // Deconstructor

      void LoadEnvironment( Environment *env );                                           // Load an Enviroment
      void DrawWorldModel( std::map< std::pair< float, float>, std::vector< bool >  > visited,
                           std::vector< std::vector< GLfloat > > colors, int agent, bool grid );// DrawModel to Screen
      void DrawGrid();                                                                    // Draw Grid Overlay
    protected:
      std::map< std::string, std::vector< GLfloat> > mCellColors;                         // CellColors
      std::map< std::pair< float, float>, std::vector< Vector3 > > mCellVerts;            // Cells by id
      std::map< std::pair< float, float>, GLuint > mCellObjects;                          // Cell Display Lists
      std::vector< Model* > mTerrainObjects;                                              // Terrain Objects
      TextureManager * mTextureMgr;                                                       // Texture Manager
      GLuint mWallsId, mGrid;                                                             // Wall and Grid Models
      GLuint mGrass, mMud, mRock, mCliff, mIce;                                           // Textures
      Model *mRockTemplate;                                                               // Rock Template
    private:
    };
  }
}

#else
#endif

#endif // _SCAVENGERENVIRONMENTMODEL
/* Local Variables: */
/* mode:c++         */
/* End:             */
