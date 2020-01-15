#include <ai_scavenger.h>

#if USE_GLUT

namespace ai {
  namespace Scavenger {

    EnvironmentModel::EnvironmentModel() {
      mObjectId               = "world";
      mCellColors["plain"]    = { 0.0f, 0.4f, 0.09f, 1.0f };
      mCellColors["rocks"]    = { 0.7f, 0.7f, 0.7f, 1.0f };
      mCellColors["mud"]      = { 0.34f, 0.18f, 0.0f, 1.0f };
      mCellColors["ice"]      = { 0.69f, 0.98f, 1.0f, 1.0f };
      mCellColors["wall"]     = { 0.3f, 0.2f, 0.11f, 1.0f };
      mCellColors["cliff"]    = { 0.0f, 0.4f, 0.09f, 1.0f };

      mCenterX                = 0;
      mCenterY                = 0;

      mTextureMgr             = new TextureManager();
      mRockTemplate           = new Model();
      mGrass                  = mTextureMgr->LoadTexture( "ScavengerData/grass.tga", true );
      mMud                    = mTextureMgr->LoadTexture( "ScavengerData/mud.tga", true );
      mRock                   = mTextureMgr->LoadTexture( "ScavengerData/rock.tga", true );
      mCliff                  = mTextureMgr->LoadTexture( "ScavengerData/cliff.tga", true );
      mIce                    = mTextureMgr->LoadTexture( "ScavengerData/ice.tga", true );

      mRockTemplate->LoadModel( "ScavengerData/rock.obj", mRock );
    }

    EnvironmentModel::~EnvironmentModel() {}

    void EnvironmentModel::LoadEnvironment( Environment *env ) {
      std::cout << "Loading Environment..." << std::endl;

      float tXChange[]    = { 500.0f, 500.0f, -500.0f, -500.0f };
      float tYChange[]    = { 500.0f, -500.0f, -500.0f, 500.0f };

      // Set up Variables for Determining Center Point
      float tWidthMax     = -99999999;
      float tWidthMin     = 99999999;
      float tHeightMax    = -99999999;
      float tHeightMin    = 99999999;

      // Read in Cells
      std::map< Location, Cell* >::iterator iCells;
      for( iCells = env->cells.begin(); iCells != env->cells.end(); ++iCells ) {
        if ( iCells->second == 0 ) {
          std::cerr << "Error: Bad Pointer" << std::endl;
          continue;
        }

        // Set up Variables for Generating Each Cell
        Location tLocation = iCells->second->GetLocation();

        // Update Edges for Center Point Calculation
        if ( tLocation.GetX() > tWidthMax )
          tWidthMax = tLocation.GetX();
        if ( tLocation.GetX() < tWidthMin )
          tWidthMin = tLocation.GetX();
        if ( tLocation.GetY() > tHeightMax )
          tHeightMax = tLocation.GetY();
        if ( tLocation.GetY() < tHeightMin )
          tHeightMin = tLocation.GetY();

        // Verticies Required for Cell
        Vector3 tCenter             = { (float)tLocation.GetX(), (float)tLocation.GetY(), (float) tLocation.GetElevation() };
        Vector3 tTopLeft            = { (float)tLocation.GetX() + tXChange[3], (float)tLocation.GetY() + tYChange[3], (float)tLocation.GetElevation() };
        Vector3 tTopCenter          = { (float)tLocation.GetX(), (float)tLocation.GetY() + tYChange[0], (float)tLocation.GetElevation() };
        Vector3 tTopRight           = { (float)tLocation.GetX() + tXChange[0], (float)tLocation.GetY() + tYChange[0], (float)tLocation.GetElevation() };
        Vector3 tRightCenter        = { (float)tLocation.GetX() + tXChange[0], (float)tLocation.GetY(), (float)tLocation.GetElevation() };
        Vector3 tBottomRight        = { (float)tLocation.GetX() + tXChange[1], (float)tLocation.GetY() + tYChange[1], (float)tLocation.GetElevation() };
        Vector3 tBottomCenter       = { (float)tLocation.GetX(), (float)tLocation.GetY() + tYChange[1], (float)tLocation.GetElevation() };
        Vector3 tBottomLeft         = { (float)tLocation.GetX() + tXChange[2], (float)tLocation.GetY() + tYChange[2], (float)tLocation.GetElevation() };
        Vector3 tLeftCenter         = { (float)tLocation.GetX() + tXChange[2], (float)tLocation.GetY(), (float)tLocation.GetElevation() };
        Vector3 *tCornerVertices[4] = { &tTopRight, &tBottomRight, &tBottomLeft, &tTopLeft };

        // Directional Interfaces
        std::string tNorthInterface = iCells->second->GetInterface( Location::NORTH ).GetTitle();
        std::string tSouthInterface = iCells->second->GetInterface( Location::SOUTH ).GetTitle();
        std::string tEastInterface  = iCells->second->GetInterface( Location::EAST ).GetTitle();
        std::string tWestInterface  = iCells->second->GetInterface( Location::WEST ).GetTitle();
        std::string tInterfaces[4]  = { tNorthInterface, tSouthInterface, tEastInterface, tWestInterface };

        // Interfaces grouped by Corner Verticies
        std::pair< std::string, std::string > tCornerInterfaces[4] = { { tNorthInterface, tEastInterface },
                                                                       { tEastInterface, tSouthInterface },
                                                                       { tSouthInterface, tWestInterface },
                                                                       { tWestInterface, tNorthInterface } };

        // Neighboring Cells
        Cell* tNorthNeighbor = env->cells_by_id[iCells->second->GetNeighborId( Location::NORTH )];
        Cell* tEastNeighbor  = env->cells_by_id[iCells->second->GetNeighborId( Location::EAST )];
        Cell* tSouthNeighbor = env->cells_by_id[iCells->second->GetNeighborId( Location::SOUTH )];
        Cell* tWestNeighbor  = env->cells_by_id[iCells->second->GetNeighborId( Location::WEST )];
        Cell* tNeighbors[4]  = { tNorthNeighbor, tSouthNeighbor, tEastNeighbor, tWestNeighbor };

        // Neighbors grouped by Corner Vertices
        std::pair< Cell*, Cell* > tEdgeNeighbors[4] = { { tNorthNeighbor, tEastNeighbor },
                                                        { tEastNeighbor, tSouthNeighbor },
                                                        { tSouthNeighbor, tWestNeighbor },
                                                        { tWestNeighbor, tNorthNeighbor } };

        // Corner Neighbors
        //Cell* tTopRightCorner    = NULL;
        //Cell* tTopLeftCorner     = NULL;
        //Cell* tBottomRightCorner = NULL;
        //Cell* tBottomLeftCorner  = NULL;
        //Cell* tCornerCells[4]    = { tTopRightCorner, tBottomRightCorner, tBottomLeftCorner, tTopLeftCorner };

        // Locational Directions we will be Looking
        std::pair< Location::Direction, Location::Direction > tDirections[4] = { { Location::NORTH, Location::EAST },
                                                                                 { Location::EAST, Location::SOUTH },
                                                                                 { Location::SOUTH, Location::WEST },
                                                                                 { Location::WEST, Location::NORTH } };

        // Reversed Directions for looking at corner Neighbors
        std::pair< Location::Direction, Location::Direction > tNeighborCornerInterfaces[4] = { { Location::WEST, Location::SOUTH },
                                                                                               { Location::NORTH, Location::WEST },
                                                                                               { Location::EAST, Location::NORTH },
                                                                                               { Location::SOUTH, Location::EAST } };

        // Flags for Averaged Verticies
        //bool tCornerAvg[4] = { false, false, false, false };
        //bool tNghbrAvg[8] = { false, false, false, false, false, false, false, false };

        // Calculate Z Values for Corners
        for ( int iCorner = 0; iCorner < 4; ++iCorner ) {
          float tZ = tLocation.GetElevation();
          int tCount = 1;
          if ( ( tCornerInterfaces[iCorner].first == "wall" || tCornerInterfaces[iCorner].first == "cliff" ) &&
               ( tCornerInterfaces[iCorner].second == "wall" || tCornerInterfaces[iCorner].second == "cliff" ) ) {
            tCornerVertices[iCorner]->z = tZ / tCount;
            continue;
          } else if ( tEdgeNeighbors[iCorner].second &&
                      ( tCornerInterfaces[iCorner].first == "wall" || tCornerInterfaces[iCorner].first == "cliff" ) &&
                      ( tEdgeNeighbors[iCorner].second->GetInterface( tDirections[iCorner].first ).GetTitle() == "wall" ||
                        tEdgeNeighbors[iCorner].second->GetInterface( tDirections[iCorner].first ).GetTitle() == "cliff" ) ) {
            tZ += tEdgeNeighbors[iCorner].second->GetLocation().GetElevation();
            tCount ++;
          } else if ( tEdgeNeighbors[iCorner].first &&
                      ( tCornerInterfaces[iCorner].second == "wall" || tCornerInterfaces[iCorner].second == "cliff" ) &&
                      ( tEdgeNeighbors[iCorner].first->GetInterface( tDirections[iCorner].second ).GetTitle() == "wall" ||
                        tEdgeNeighbors[iCorner].first->GetInterface( tDirections[iCorner].second ).GetTitle() == "cliff" ) ) {
            tZ += tEdgeNeighbors[iCorner].first->GetLocation().GetElevation();

            tCount ++;
          } else {
            Cell* tCornerNeighbor = NULL;
            if ( tEdgeNeighbors[iCorner].second &&
                 ( tCornerInterfaces[iCorner].second != "wall" && tCornerInterfaces[iCorner].second != "cliff" ) ) {
              tZ += tEdgeNeighbors[iCorner].second->GetLocation().GetElevation();
              tCount ++;

              tCornerNeighbor = env->cells_by_id[tEdgeNeighbors[iCorner].second->GetNeighborId( tDirections[iCorner].first )];
            }
            if ( tEdgeNeighbors[iCorner].first &&
                 ( tCornerInterfaces[iCorner].first != "wall" && tCornerInterfaces[iCorner].first != "cliff" ) ) {
              tZ += tEdgeNeighbors[iCorner].first->GetLocation().GetElevation();
              tCount ++;
              tCornerNeighbor = env->cells_by_id[tEdgeNeighbors[iCorner].first->GetNeighborId( tDirections[iCorner].second )];
            }
            if ( tCornerNeighbor ) {
              //tCornerCells[iCorner] = tCornerNeighbor;
              if ( !( ( tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].first ).GetTitle() == "wall" ||
                        tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].first ).GetTitle() == "cliff" ) &&
                      ( tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].second ).GetTitle() == "wall" ||
                        tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].second ).GetTitle() == "cliff" ) ) ) {
                tZ += tCornerNeighbor->GetLocation().GetElevation();
                tCount ++;
                //tCornerAvg[iCorner] = true;
              }
              if ( tEdgeNeighbors[iCorner].first &&
                   ( tCornerInterfaces[iCorner].first == "cliff" || tCornerInterfaces[iCorner].first == "wall" ) &&
                   ( tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].first ).GetTitle() != "wall" &&
                     tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].first ).GetTitle() != "cliff" ) &&
                   tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].second ). GetTitle() != "wall" &&
                   tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].second ).GetTitle() != "cliff" ) {
                tZ += tEdgeNeighbors[iCorner].first->GetLocation().GetElevation();
                //tNghbrAvg[iCorner*2] = true;
                tCount ++;
              }
              if ( tEdgeNeighbors[iCorner].second &&
                   ( tCornerInterfaces[iCorner].second== "cliff" || tCornerInterfaces[iCorner].second == "wall" ) &&
                   ( tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].first ).GetTitle() != "wall" &&
                     tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].first ).GetTitle() != "cliff" ) &&
                   tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].second ). GetTitle() != "wall" &&
                   tCornerNeighbor->GetInterface( tNeighborCornerInterfaces[iCorner].second ).GetTitle() != "cliff" ) {
                tZ += tEdgeNeighbors[iCorner].second->GetLocation().GetElevation();
                //tNghbrAvg[iCorner*2+1] = true;
                tCount ++;
              }
            }

          }
          tCornerVertices[iCorner]->z = tZ / tCount;
        }

        float tZ = tLocation.GetElevation();

        // Calculate Z values for center vertices
        if ( tNorthInterface == "wall" || tNorthInterface == "cliff" )
          tTopCenter.z = tLocation.GetElevation();
        else
          tTopCenter.z = ( tTopLeft.z + tTopRight.z ) / 2.0;

        if ( tEastInterface == "wall" || tEastInterface == "cliff" )
          tRightCenter.z = tLocation.GetElevation();

        else
          tRightCenter.z = ( tBottomRight.z + tTopRight.z ) / 2.0;

        if ( tSouthInterface == "wall" || tSouthInterface == "cliff" )
          tBottomCenter.z = tLocation.GetElevation();
        else
          tBottomCenter.z = ( tBottomLeft.z + tBottomRight.z ) / 2.0;


        if ( tWestInterface == "wall" || tWestInterface == "cliff" )
          tLeftCenter.z = tLocation.GetElevation();
        else
          tLeftCenter.z = ( tTopLeft.z + tBottomLeft.z ) / 2.0;

        std::vector< GLfloat > tMaterial;

        GLuint tTextures[]  = { mGrass, mMud, mIce };
        int tLenTextures = 3;
        int tNorthTex, tEastTex, tSouthTex, tWestTex;
        if ( tNorthInterface == "mud" )
          tNorthTex = 1;
        else if ( tNorthInterface == "ice" )
          tNorthTex = 2;
        else
          tNorthTex = 0;

        if ( tSouthInterface == "mud" )
          tSouthTex = 1;
        else if ( tSouthInterface == "ice" )
          tSouthTex = 2;
        else
          tSouthTex = 0;

        if ( tEastInterface == "mud" )
          tEastTex = 1;
        else if ( tEastInterface == "ice" )
          tEastTex = 2;
        else
          tEastTex = 0;

        if ( tWestInterface == "mud" )
          tWestTex = 1;
        else if ( tWestInterface == "ice" )
          tWestTex = 2;
        else
          tWestTex = 0;

        Vector3 tNormal1 = CalculateNormal( tCenter, tTopLeft, tTopCenter );
        Vector3 tNormal2 = CalculateNormal( tCenter, tTopCenter, tTopRight );
        Vector3 tNormal3 = CalculateNormal( tCenter, tTopRight, tRightCenter );
        Vector3 tNormal4 = CalculateNormal( tCenter, tRightCenter, tBottomRight );
        Vector3 tNormal5 = CalculateNormal( tCenter, tBottomRight, tBottomCenter );
        Vector3 tNormal6 = CalculateNormal( tCenter, tBottomCenter, tBottomLeft );
        Vector3 tNormal7 = CalculateNormal( tCenter, tBottomLeft, tLeftCenter );
        Vector3 tNormal8 = CalculateNormal( tCenter, tLeftCenter, tTopLeft );

        GLuint tCellFace = glGenLists( 1 );
        glNewList( tCellFace, GL_COMPILE );

        glTranslatef(0.0f,0.0f,0.0f);
        glPushMatrix();

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_COLOR_MATERIAL );
        glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
        glEnable( GL_TEXTURE_2D );
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

        for ( int iTexture = 0; iTexture < tLenTextures; ++iTexture ) {
          glBindTexture( GL_TEXTURE_2D, tTextures[iTexture] );

          glBegin(GL_TRIANGLES);
          if ( tNorthTex == iTexture ) {
            glNormal3f( tNormal1.x, tNormal1.y, tNormal1.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal1.x, tNormal1.y, tNormal1.z );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( tTopLeft.x, tTopLeft.y, tTopLeft.z );
            glNormal3f( tNormal1.x, tNormal1.y, tNormal1.z );
            glTexCoord2f( 0.5f, 1.0f );
            glVertex3f( tTopCenter.x, tTopCenter.y, tTopCenter.z );

            glNormal3f( tNormal2.x, tNormal2.y, tNormal2.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal2.x, tNormal2.y, tNormal2.z );
            glTexCoord2f( 0.5f, 1.0f );
            glVertex3f( tTopCenter.x, tTopCenter.y, tTopCenter.z );
            glNormal3f( tNormal2.x, tNormal2.y, tNormal2.z );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( tTopRight.x, tTopRight.y, tTopRight.z );
          }

          if ( tEastTex == iTexture ) {
            glNormal3f( tNormal3.x, tNormal3.y, tNormal3.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal3.x, tNormal3.y, tNormal3.z );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( tTopRight.x, tTopRight.y, tTopRight.z );
            glNormal3f( tNormal3.x, tNormal3.y, tNormal3.z );
            glTexCoord2f( 1.0f, 0.5f );
            glVertex3f( tRightCenter.x, tRightCenter.y, tRightCenter.z );

            glNormal3f( tNormal4.x, tNormal4.y, tNormal4.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal4.x, tNormal4.y, tNormal4.z );
            glTexCoord2f( 1.0f, 0.5f );
            glVertex3f( tRightCenter.x, tRightCenter.y, tRightCenter.z );
            glNormal3f( tNormal4.x, tNormal4.y, tNormal4.z );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( tBottomRight.x, tBottomRight.y, tBottomRight.z );
          }

          if ( tSouthTex == iTexture ) {
            glNormal3f( tNormal5.x, tNormal5.y, tNormal5.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal5.x, tNormal5.y, tNormal5.z );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( tBottomRight.x, tBottomRight.y, tBottomRight.z );
            glNormal3f( tNormal5.x, tNormal5.y, tNormal5.z );
            glTexCoord2f( 0.5f, 0.0f );
            glVertex3f( tBottomCenter.x, tBottomCenter.y, tBottomCenter.z );

            glNormal3f( tNormal6.x, tNormal6.y, tNormal6.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal6.x, tNormal6.y, tNormal6.z );
            glTexCoord2f( 0.5f, 0.0f );
            glVertex3f( tBottomCenter.x, tBottomCenter.y, tBottomCenter.z );
            glNormal3f( tNormal6.x, tNormal6.y, tNormal6.z );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( tBottomLeft.x, tBottomLeft.y, tBottomLeft.z );
          }

          if ( tWestTex == iTexture ) {
            glNormal3f( tNormal7.x, tNormal7.y, tNormal7.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal7.x, tNormal7.y, tNormal7.z );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( tBottomLeft.x, tBottomLeft.y, tBottomLeft.z );
            glNormal3f( tNormal7.x, tNormal7.y, tNormal7.z );
            glTexCoord2f( 0.0f, 0.5f );
            glVertex3f( tLeftCenter.x, tLeftCenter.y, tLeftCenter.z );

            glNormal3f( tNormal8.x, tNormal8.y, tNormal8.z );
            glTexCoord2f( 0.5f, 0.5f );
            glVertex3f( tCenter.x, tCenter.y, tCenter.z);
            glNormal3f( tNormal8.x, tNormal8.y, tNormal8.z );
            glTexCoord2f( 0.0f, 0.5f );
            glVertex3f( tLeftCenter.x, tLeftCenter.y, tLeftCenter.z );
            glNormal3f( tNormal8.x, tNormal8.y, tNormal8.z );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( tTopLeft.x, tTopLeft.y, tTopLeft.z );
          }
          glEnd();
        }

        glPopMatrix();
        glEndList();

        std::pair< float, float > tCellFaceLocation = { tCenter.x, tCenter.y };
        mCellObjects[tCellFaceLocation] = tCellFace;

        if ( tNorthInterface == "rocks" ) {
          Model * tRock = new Model();
          tRock->SetModelId( mRockTemplate->GetModelId() );
          tRock->SetTextureId( mRock );
          tRock->SetPosition( tTopCenter.x, tTopCenter.y, tTopCenter.z );
          mTerrainObjects.push_back( tRock );
        }

        if ( tEastInterface == "rocks" ) {
          Model * tRock = new Model();
          tRock->SetModelId( mRockTemplate->GetModelId() );
          tRock->SetTextureId( mRock );
          tRock->SetPosition( tRightCenter.x, tRightCenter.y, tRightCenter.z );
          mTerrainObjects.push_back( tRock );
        }

        // Store Cell Vertices for Grid to Process
        std::pair< float, float > tLocationId = { tCenter.x, tCenter.y };
        std::vector< Vector3 > tFacesVec;
        tFacesVec.push_back( tCenter );
        tFacesVec.push_back( tTopLeft );
        tFacesVec.push_back( tTopCenter );
        tFacesVec.push_back( tTopRight );
        tFacesVec.push_back( tRightCenter );
        tFacesVec.push_back( tBottomRight );
        tFacesVec.push_back( tBottomCenter );
        tFacesVec.push_back( tBottomLeft );
        tFacesVec.push_back( tLeftCenter );
        mCellVerts[tLocationId] = tFacesVec;

        // Variables for Creating Walls
        std::vector< Vector3 > tNorthPoints             = { tTopCenter, tTopRight, tTopLeft };
        std::vector< Vector3 > tSouthPoints             = { tBottomCenter, tBottomLeft, tBottomRight };
        std::vector< Vector3 > tEastPoints              = { tRightCenter, tBottomRight, tTopRight };

        std::vector< Vector3 > tWestPoints              = { tLeftCenter, tTopLeft, tBottomLeft };
        std::vector< std::vector< Vector3 > > tPoints   = { tNorthPoints, tSouthPoints, tEastPoints, tWestPoints };

        // Create Walls
        tZ = -1500;
        for ( int iDir = 0; iDir < 4; ++iDir ) {
          if ( ( tNeighbors[iDir] && tInterfaces[iDir] == "cliff" ) ||
               ( !tNeighbors[iDir] && tInterfaces[iDir] == "wall" ) ) {

            Vector3 tWallCenter      = { tPoints[iDir][0].x, tPoints[iDir][0].y, tZ };
            Vector3 tWallRightCenter = { tPoints[iDir][1].x, tPoints[iDir][1].y, tZ };
            Vector3 tWallTopRight    = { tPoints[iDir][1].x, tPoints[iDir][1].y, tPoints[iDir][1].z };
            Vector3 tWallTopCenter   = { tPoints[iDir][0].x, tPoints[iDir][0].y, tPoints[iDir][0].z };
            Vector3 tWallTopLeft     = { tPoints[iDir][2].x, tPoints[iDir][2].y, tPoints[iDir][2].z };
            Vector3 tWallLeftCenter  = { tPoints[iDir][2].x, tPoints[iDir][2].y, tZ };

            Vector3 tNormal = CalculateNormal( tWallCenter, tWallRightCenter, tWallTopRight );
            Vector3 tNormal2 = CalculateNormal( tWallCenter, tWallTopRight, tWallTopCenter );
            Vector3 tNormal3 = CalculateNormal( tWallCenter, tWallTopCenter, tWallTopLeft );
            Vector3 tNormal4 = CalculateNormal( tWallCenter, tWallTopLeft, tWallLeftCenter );

            GLuint tWallsId = glGenLists( 1 );
            glNewList( tWallsId, GL_COMPILE );

            glTranslatef(0.0f,0.0f,0.0f);

            glPushMatrix();

            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            glEnable( GL_COLOR_MATERIAL );
            glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
            glEnable( GL_TEXTURE_2D );
            glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
            glBindTexture( GL_TEXTURE_2D, mCliff );

            glBegin(GL_TRIANGLES);
            glNormal3f( tNormal.x, tNormal.y, tNormal.z );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( tWallCenter.x, tWallCenter.y, tWallCenter.z);
            glNormal3f( tNormal.x, tNormal.y, tNormal.z );
            glTexCoord2f( 2.0f, 2.0f );
            glVertex3f( tWallTopRight.x, tWallTopRight.y, tWallTopRight.z );
            glNormal3f( tNormal.x, tNormal.y, tNormal.z );
            glTexCoord2f( 2.0f, 0.0f );
            glVertex3f( tWallRightCenter.x, tWallRightCenter.y, tWallRightCenter.z );

            glNormal3f( tNormal2.x, tNormal2.y, tNormal2.z );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( tWallCenter.x, tWallCenter.y, tWallCenter.z);
            glNormal3f( tNormal2.x, tNormal2.y, tNormal2.z );
            glTexCoord2f( 1.0f, 2.0f );
            glVertex3f( tWallTopCenter.x, tWallTopCenter.y, tWallTopCenter.z );
            glNormal3f( tNormal2.x, tNormal2.y, tNormal2.z );
            glTexCoord2f( 2.0f, 2.0f );
            glVertex3f( tWallTopRight.x, tWallTopRight.y, tWallTopRight.z );

            glNormal3f( tNormal3.x, tNormal3.y, tNormal3.z );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( tWallCenter.x, tWallCenter.y, tWallCenter.z);
            glNormal3f( tNormal3.x, tNormal3.y, tNormal3.z );
            glTexCoord2f( 0.0f, 2.0f );
            glVertex3f( tWallTopLeft.x, tWallTopLeft.y, tWallTopLeft.z );
            glNormal3f( tNormal3.x, tNormal3.y, tNormal3.z );
            glTexCoord2f( 1.0f, 2.0f );
            glVertex3f( tWallTopCenter.x, tWallTopCenter.y, tWallTopCenter.z );

            glNormal3f( tNormal4.x, tNormal4.y, tNormal4.z );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( tWallCenter.x, tWallCenter.y, tWallCenter.z);
            glNormal3f( tNormal4.x, tNormal4.y, tNormal4.z );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( tWallLeftCenter.x, tWallLeftCenter.y, tWallLeftCenter.z );
            glNormal3f( tNormal4.x, tNormal4.y, tNormal4.z );
            glTexCoord2f( 0.0f, 2.0f );
            glVertex3f( tWallTopLeft.x, tWallTopLeft.y, tWallTopLeft.z );

            glEnd();

            glDisable( GL_TEXTURE_2D );
            glDisable( GL_BLEND );
            glDisable( GL_COLOR_MATERIAL );

            glPopMatrix();
            glEndList();

            std::pair< float, float > tWallFaces = { tWallCenter.x, tWallCenter.y };
            mCellObjects[tWallFaces] = tWallsId;
          }
        }
      }


      mCenterX = ( tWidthMax + tWidthMin ) / 2.0;
      mCenterY = ( tHeightMax + tHeightMin ) / 2.0;
      DrawGrid();
    }

    void EnvironmentModel::DrawWorldModel( std::map< std::pair< float, float>, std::vector< bool >  > visited,
                                           std::vector< std::vector< GLfloat > > colors, int agent, bool grid ) {
      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
      glEnable( GL_COLOR_MATERIAL );
      glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
      glEnable( GL_LIGHTING );

      std::map< std::pair< float, float >, GLuint >::iterator tCell;

      for ( tCell = mCellObjects.begin(); tCell != mCellObjects.end(); ++tCell ) {
        glPushMatrix();
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        if ( agent != -2 ) {
          std::pair< float, float > tLoc = { tCell->first.first, tCell->first.second };
          if ( visited.count( tLoc ) != 0 ) {
            if ( agent >= 0 && visited[tLoc][agent] ) {
              glColor4f( colors[agent][0], colors[agent][1], colors[agent][2], colors[agent][3] );
            } else if ( agent == -1 ) {
              for ( unsigned int iAgent = 0; iAgent < visited[tLoc].size(); ++iAgent ) {
                if ( visited[tLoc][iAgent] ) {
                  glColor4f( colors[iAgent][0], colors[iAgent][1], colors[iAgent][2], colors[iAgent][3] );
                  break;
                }
              }
            }
          }
        }

        glCallList( tCell->second );
        glPopMatrix();
      }

      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      for ( size_t iObject = 0; iObject < mTerrainObjects.size(); ++iObject ) {
        mTerrainObjects[iObject]->DrawModel();
      }

      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      if ( grid ) {
        glCallList( mGrid );
      }

      glDisable( GL_LIGHTING );
      glDisable( GL_COLOR_MATERIAL );
      glDisable( GL_BLEND );
    }

    void EnvironmentModel::DrawGrid() {
      float tGridHeight   = 10.0f;
      float tGridWidth    = 15.0f;

      mGrid               = glGenLists( 1 );
      glNewList( mGrid, GL_COMPILE );

      std::map< std::pair< float, float >, std::vector< Vector3 > >::iterator tCell;
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glPushMatrix();
      glBegin( GL_QUADS );
      for ( tCell = mCellVerts.begin(); tCell != mCellVerts.end(); ++tCell ) {
        glVertex3f( tCell->second[1].x - tGridWidth, tCell->second[1].y + tGridWidth, tCell->second[1].z + tGridHeight );
        glVertex3f( tCell->second[1].x - tGridWidth, tCell->second[1].y - tGridWidth, tCell->second[1].z + tGridHeight );
        glVertex3f( tCell->second[2].x, tCell->second[2].y - tGridWidth, tCell->second[2].z + tGridHeight );
        glVertex3f( tCell->second[2].x, tCell->second[2].y + tGridWidth, tCell->second[2].z + tGridHeight );

        glVertex3f( tCell->second[2].x, tCell->second[2].y - tGridWidth , tCell->second[2].z + tGridHeight );
        glVertex3f( tCell->second[2].x, tCell->second[2].y + tGridWidth, tCell->second[2].z + tGridHeight );
        glVertex3f( tCell->second[3].x + tGridWidth, tCell->second[3].y + tGridWidth, tCell->second[3].z + tGridHeight );
        glVertex3f( tCell->second[3].x + tGridWidth, tCell->second[3].y - tGridWidth, tCell->second[3].z + tGridHeight );

        glVertex3f( tCell->second[3].x - tGridWidth, tCell->second[3].y + tGridWidth, tCell->second[3].z + tGridHeight );
        glVertex3f( tCell->second[3].x + tGridWidth, tCell->second[3].y + tGridWidth, tCell->second[3].z + tGridHeight );
        glVertex3f( tCell->second[4].x + tGridWidth, tCell->second[4].y, tCell->second[4].z + tGridHeight );
        glVertex3f( tCell->second[4].x - tGridWidth, tCell->second[4].y, tCell->second[4].z + tGridHeight );

        glVertex3f( tCell->second[4].x - tGridWidth, tCell->second[4].y, tCell->second[4].z + tGridHeight );
        glVertex3f( tCell->second[4].x + tGridWidth, tCell->second[4].y, tCell->second[4].z + tGridHeight );
        glVertex3f( tCell->second[5].x + tGridWidth, tCell->second[5].y - tGridWidth, tCell->second[5].z + tGridHeight );
        glVertex3f( tCell->second[5].x - tGridWidth, tCell->second[5].y - tGridWidth, tCell->second[5].z + tGridHeight );

        glVertex3f( tCell->second[5].x + tGridWidth, tCell->second[5].y + tGridWidth, tCell->second[5].z + tGridHeight );
        glVertex3f( tCell->second[5].x + tGridWidth, tCell->second[5].y - tGridWidth, tCell->second[5].z + tGridHeight );
        glVertex3f( tCell->second[6].x, tCell->second[6].y - tGridWidth, tCell->second[6].z + tGridHeight );
        glVertex3f( tCell->second[6].x, tCell->second[6].y + tGridWidth, tCell->second[6].z + tGridHeight );

        glVertex3f( tCell->second[6].x, tCell->second[6].y + tGridWidth, tCell->second[6].z + tGridHeight );
        glVertex3f( tCell->second[6].x, tCell->second[6].y - tGridWidth, tCell->second[6].z + tGridHeight );
        glVertex3f( tCell->second[7].x - tGridWidth, tCell->second[7].y - tGridWidth, tCell->second[7].z + tGridHeight );
        glVertex3f( tCell->second[7].x - tGridWidth, tCell->second[7].y + tGridWidth, tCell->second[7].z + tGridHeight );

        glVertex3f( tCell->second[7].x - tGridWidth, tCell->second[7].y - tGridWidth, tCell->second[7].z + tGridHeight );
        glVertex3f( tCell->second[7].x + tGridWidth, tCell->second[7].y - tGridWidth, tCell->second[7].z + tGridHeight );
        glVertex3f( tCell->second[8].x + tGridWidth, tCell->second[8].y, tCell->second[8].z + tGridHeight );
        glVertex3f( tCell->second[8].x - tGridWidth, tCell->second[8].y, tCell->second[8].z + tGridHeight );

        glVertex3f( tCell->second[8].x - tGridWidth, tCell->second[8].y, tCell->second[8].z + tGridHeight );
        glVertex3f( tCell->second[8].x + tGridWidth, tCell->second[8].y, tCell->second[8].z + tGridHeight );
        glVertex3f( tCell->second[1].x + tGridWidth, tCell->second[1].y + tGridWidth, tCell->second[1].z + tGridHeight );
        glVertex3f( tCell->second[1].x - tGridWidth, tCell->second[1].y + tGridWidth, tCell->second[1].z + tGridHeight );
      }
      glEnd();
      glPopMatrix();
      glEndList();
    }
  } // End Scavenger Namespace
} // End AI Namespace

#else
#endif
