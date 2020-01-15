#if USE_GLUT

#include <ai_scavenger.h>
#include <ai_glut.h>
#include <cstdio>
#include <cmath>

// Windows headers have DrawText() macro defined somewhere.
#ifdef DrawText
#undef DrawText
#endif

namespace ai {
  namespace Scavenger {

    typedef std::chrono::high_resolution_clock Clock;

    // Globals //
    bool KEYS[256];
    bool LIFTED[256];
    static EnvironmentDisplay3D *DISPLAY_MGR    = 0;
    static int DEBUG_MODE                       = 0;            // 0 = Standard, 1 = Descriptive, 2 = Verbose
    static std::string VERSION                  = "v1.3.40";

    static std::vector< std::vector< GLfloat > > AGENT_COLORS = { { 1.0f, 0.0f, 0.0f, 1.0f },
                                                                  { 0.0f, 0.5f, 0.0f, 1.0f },
                                                                  { 0.0f, 0.0f, 1.0f, 1.0f },
                                                                  { 1.0f, 0.0f, 1.0f, 1.0f },
                                                                  { 1.0f, 0.5f, 0.0f, 1.0f },
                                                                  { 0.0f, 1.0f, 1.0f, 1.0f },
                                                                  { 1.0f, 1.0f, 1.0f, 1.0f } };

    static bool GetKeyPressed( char key ) {
      if ( KEYS[(int)key] && !LIFTED[(int)key] ) {
        LIFTED[(int)key] = true;
        return true;
      }
      return false;
    }

    static bool GetKeyHeld( char key ) {
      return KEYS[(int)key];
    }

    // Debug Functions //
    static void DebugMessage( std::string msg, int level ) {
      if ( level <= DEBUG_MODE )
        std::cout << msg << std::endl;
    }

    // Glut Functions //
    static void Display() {
      DISPLAY_MGR->Redraw();
    }

    static void KeyDown( unsigned char key, int x, int y ) {
      KEYS[(int)key]   = true;
    }

    static void KeyUp( unsigned char key, int x, int y ) {
      KEYS[(int)key]   = false;
    }

    void DrawTitle(float x, float y, const char *str, int size ) {
      void *font = GLUT_BITMAP_HELVETICA_18;
      if ( size == 1 )
        font = GLUT_BITMAP_HELVETICA_12;
      int   i;
      int   len;

      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
      glEnable( GL_BLEND );

      glRasterPos2f( x, y );
      len = (int) strlen( str );
      for ( i = 0; i < len; i++ ) {
        glutBitmapCharacter( font, str[i] );
      }

      glDisable( GL_BLEND );
    }

    // Environment Display //
    EnvironmentDisplay3D::EnvironmentDisplay3D( ai::Agent::Environment *env, int widthIn, int heightIn )
      : ai::Agent::EnvironmentDisplay( env, widthIn, heightIn ) {
      DebugMessage( "Loading 3D Environment Display. " + VERSION, 0 );

      // Initialize Class Variables
      DISPLAY_MGR         = this;
      mTextureMgr         = new TextureManager();
      mCurrentAgent       = 0;

      mCamMode            = false;
      mGrid               = false;
      mVisited            = false;
      mHelp               = true;

      mDeltaTime          = 0.02;
      mStartTime          = Clock::now();
      mCurrentTime        = 0.0;
      mLastTime           = 0.0;
      mTotalServerTime    = 0.0;
      mTotalServerTicks   = 0;
      mFPS                = 0.0;
      mTotalTime          = 0.0;
      mFrames             = 0;
      mLastServerTime     = Clock::now();

      width               = 1024;
      height              = 768;

      mTargetX            = 0.0f;
      mTargetY            = 0.0f;
      mTargetZ            = 0.0f;
      mCamAlpha           = 0.0f;
      mCamTheta           = 20.0f;
      mCamRadius          = 6000.0f;

      // Load Up Actions into Action List
      mActionStrings.push_back( "MOVING NORTH" );
      mActionStrings.push_back( "MOVING SOUTH" );
      mActionStrings.push_back( "MOVING EAST" );
      mActionStrings.push_back( "MOVING WEST" );
      mActionStrings.push_back( "LOOKING" );
      mActionStrings.push_back( "RECHARGING" );
      mActionStrings.push_back( "PICKING UP" );
      mActionStrings.push_back( "DROPPING" );
      mActionStrings.push_back( "DEPOSITING" );
      mActionStrings.push_back( "EXAMINING" );
      mActionStrings.push_back( "SHUTDOWN" );
      mActionStrings.push_back( "NOOP" );

      mActionDirection.push_back( "NORTH" );
      mActionDirection.push_back( "SOUTH" );
      mActionDirection.push_back( "EAST" );
      mActionDirection.push_back( "WEST" );

      // Load up Directions for Move actions
      glutDisplayFunc( Display );
      glutKeyboardFunc( KeyDown );
      glutKeyboardUpFunc( KeyUp );
      InitializeLighting();

      // Load Initial Environment
      mEnvironment            = dynamic_cast< Environment* >( env );
      mWorld                  = new EnvironmentModel();
      mWorld->LoadEnvironment( mEnvironment );

      // Load Models and Textures
      Model* tBase            = new Model();
      Model* tBaseAccents     = new Model();
      Model* tAgentAccents    = new Model();
      Model* tAgentModel      = new Model();
      Model* tAgentProp       = new Model();

      GLuint tBaseTex         = mTextureMgr->LoadTexture( "ScavengerData/base.tga", false );
      GLuint tAgentTex        = mTextureMgr->LoadTexture( "ScavengerData/drone.tga", false );

      tBase->LoadModel( "ScavengerData/base.obj", 0 );
      tBaseAccents->LoadModel( "ScavengerData/baseAccents.obj", 0 );
      tAgentModel->LoadModel( "ScavengerData/drone.obj", 0 );
      tAgentAccents->LoadModel( "ScavengerData/droneaccents.obj", 0 );
      tAgentProp->LoadModel( "ScavengerData/droneprop.obj", 0 );

      // Initialize Agents
      for( size_t iAgent = 0; iAgent < mEnvironment->agents_order.size(); ++iAgent ) {
        DebugMessage( "Initializing Agent: " + std::to_string( (long double)iAgent ), 1 );
        Agent* tStoredAgent                 = static_cast< Agent* >( mEnvironment->agents[mEnvironment->agents_order[iAgent]] );
        Base*  tStoredBase                  = static_cast< Base* >( mEnvironment->bases[tStoredAgent->GetBase()] );
        Cell*  tBaseCell                    = static_cast< Cell* >( mEnvironment->cells_by_id[tStoredBase->GetCell()] );
        Location tBaseLocation              = tBaseCell->GetLocation();

        AgentInfo tAgent;
        tAgent.health                       = tStoredAgent->GetHitPoints();
        tAgent.charge                       = tStoredAgent->GetCharge();
        Location* tLocation                 = dynamic_cast< Location* >( tStoredAgent->GetLocation() );
        tAgent.x                            = tLocation->GetX();
        tAgent.y                            = tLocation->GetY();
        tAgent.z                            = tLocation->GetElevation();
        tAgent.baseX                        = tBaseLocation.GetX();
        tAgent.baseY                        = tBaseLocation.GetY();
        tAgent.baseZ                        = tBaseLocation.GetElevation();
        tAgent.agentName                    = tStoredAgent->GetName();
        tAgent.baseSize                     = 0;
        tAgent.hopperSize                   = 0;
        tAgent.locationSize                 = mEnvironment->cells[(*tLocation)]->GetObjects().size();
        tAgent.score                        = 0;
        tAgent.lastAction                   = NULL;

        Model* tAgentBase                   = new Model();
        Model* tAgentBaseAccents            = new Model();

        tAgentBase->SetModelId( tBase->GetModelId() );
        tAgentBase->SetTextureId( tBaseTex );
        tAgentBase->SetPosition( tAgent.x, tAgent.y, tAgent.z - 50.0 );
        tAgentBaseAccents->SetModelId( tBaseAccents->GetModelId() );
        tAgentBaseAccents->SetColor( AGENT_COLORS[iAgent][0], AGENT_COLORS[iAgent][1], AGENT_COLORS[iAgent][2], AGENT_COLORS[iAgent][3] );
        tAgentBaseAccents->SetPosition( tAgent.x, tAgent.y, tAgent.z - 50.0 );

        HoverAgent* tAgentInstance          = new HoverAgent( tAgent.x, tAgent.y, tAgent.z );
        tAgentInstance->InstanceModel( tAgentModel->GetModelId(), tAgentTex, tAgentAccents->GetModelId(), tAgentProp->GetModelId() );
        tAgentInstance->SetColor( AGENT_COLORS[iAgent][0], AGENT_COLORS[iAgent][1], AGENT_COLORS[iAgent][2], AGENT_COLORS[iAgent][3] );
        tAgent.agentModel                   = tAgentInstance;

        mAgents.push_back( tAgentInstance );
        mModels.push_back( tAgentBase );
        mModels.push_back( tAgentBaseAccents );

        mAgentsInfo.push_back( tAgent );
      }

      delete tBase;
      delete tBaseAccents;
      delete tAgentModel;
      delete tAgentAccents;
      delete tAgentProp;

      // Set World Center
      mTargetX = mWorld->GetCenterX();
      mTargetY = mWorld->GetCenterY();

      glClearColor( 0.0f, 0.5f, 0.82f, 1.0f );

      glShadeModel( GL_SMOOTH );
      glutReshapeWindow( width, height );

      // Load Textures
      mTopLeft        = mTextureMgr->LoadTexture( "ScavengerData/topleft.tga", false );
      mBottomRight    = mTextureMgr->LoadTexture( "ScavengerData/bottomright.tga", false );
      mBatteryFull    = mTextureMgr->LoadTexture( "ScavengerData/batteryfull.tga", false );
      mBattery75      = mTextureMgr->LoadTexture( "ScavengerData/battery75.tga", false );
      mBattery50      = mTextureMgr->LoadTexture( "ScavengerData/battery50.tga", false );
      mBattery25      = mTextureMgr->LoadTexture( "ScavengerData/battery25.tga", false );
      mHealthBar      = mTextureMgr->LoadTexture( "ScavengerData/healthbar.tga", false );
      mHealth         = mTextureMgr->LoadTexture( "ScavengerData/health.tga", false );
      mAgentLabel     = mTextureMgr->LoadTexture( "ScavengerData/agentlabel.tga", false );
    }

    EnvironmentDisplay3D::~EnvironmentDisplay3D() {
      DebugMessage( "Cleaning Up 3D Display..." , 0 );

      if ( mWorld ) {
        delete mWorld;
        mWorld = NULL;
      }

      if ( mTextureMgr ) {
        delete mTextureMgr;
        mTextureMgr = NULL;
      }

      for ( size_t iModel = 0; iModel < mModels.size(); ++iModel ) {
        if ( mModels[iModel] )
          delete mModels[iModel];
      }
      mModels.clear();
    }

    void EnvironmentDisplay3D::InitializeLighting() {
      DebugMessage( "Initializing Lights..." , 1 );

      GLfloat tSpecular[]         = { 0.0f, 0.0f, 0.0f, 0.0f };
      GLfloat tShininess[]        = { 0.0f };
      GLfloat tLightPosition[]    = { 30000.0f, 30000.0f, 15000.0f, 1.0f };
      GLfloat tWhiteLight[]       = { 0.75f, 0.75f, 0.75f, 1.0f };
      GLfloat tLowLight[]         = { 0.0f, 0.0f, 0.0f, 1.0f };

      glMaterialfv( GL_FRONT, GL_SPECULAR, tSpecular );
      glMaterialfv( GL_FRONT, GL_SHININESS, tShininess );

      glLightfv( GL_LIGHT0, GL_POSITION, tLightPosition);
      glLightfv( GL_LIGHT0, GL_AMBIENT, tLowLight );
      glLightfv( GL_LIGHT0, GL_DIFFUSE, tWhiteLight);
      glLightfv( GL_LIGHT0, GL_SPECULAR, tLowLight);

      glEnable( GL_LIGHTING );
      glEnable( GL_LIGHT0 );
    }

    void EnvironmentDisplay3D::SetEnv( ai::Agent::Environment *env_in ) {
      DebugMessage( "Setting the current Environment...", 2 );
      DBGP_DPY(LOG_STREAM(std::cerr) << "SetEnv()" << std::endl);
      mMutex.lock();

      // Calculate Server Response Time
      Clock::time_point tNow = Clock::now();
      mTotalServerTime = std::chrono::duration_cast< std::chrono::duration<double> >( tNow - mLastServerTime ).count();
      mTotalServerTicks ++;
      mLastServerTime = tNow;

      // Update Agents
      Environment* tEnv = dynamic_cast< Environment* >( env_in );
      for( size_t iAgent = 0; iAgent < tEnv->agents_order.size(); ++iAgent ) {
        DBGP_DPY(LOG_STREAM(std::cerr) << "iAgent("<<iAgent<<")" << std::endl);
        Agent* tStoredAgent = static_cast< Agent* >( tEnv->agents[tEnv->agents_order[iAgent]] );
        Base*  tStoredBase  = static_cast< Base* >( tEnv->bases[tStoredAgent->GetBase()] );

        mAgentsInfo[iAgent].health          = tStoredAgent->GetHitPoints();
        mAgentsInfo[iAgent].charge          = tStoredAgent->GetCharge();
        Location* tLocation                 = dynamic_cast< Location* >( tStoredAgent->GetLocation() );
        mAgentsInfo[iAgent].locationSize    = tEnv->cells[(*tLocation)]->GetObjects().size();
        mAgentsInfo[iAgent].x               = tLocation->GetX();
        mAgentsInfo[iAgent].y               = tLocation->GetY();
        mAgentsInfo[iAgent].z               = tLocation->GetElevation();
        mAgentsInfo[iAgent].hopperSize      = tStoredAgent->GetHopper().size();
        mAgentsInfo[iAgent].baseSize        = tStoredBase->GetHopper().size();
        mAgentsInfo[iAgent].score           = tStoredAgent->GetPerformance();
        mAgentsInfo[iAgent].lastAction      = dynamic_cast< Action* >( tStoredAgent->GetAction() );
        DBGP_DPY(LOG_STREAM(std::cerr) << "lastAction: " << mAgentsInfo[iAgent].lastAction << std::endl);

        std::pair< float, float > tLoc      = { tLocation->GetX(), tLocation->GetY() };
        if ( mVisitedCells.count( tLoc ) == 0 ) {
          std::vector< bool > tVisited    = { false, false, false, false, false, false, false };
          tVisited[iAgent]                = true;
          mVisitedCells[tLoc]             = tVisited;
        } else {
          mVisitedCells[tLoc][iAgent]     = true;
        }

        double tDuration                    = mTotalServerTime / mTotalServerTicks;
        if ( tDuration < 0.2 )
          tDuration                       = 0.2;

        // Perform Animation
        if ( mAgentsInfo[iAgent].health <= 0 || mAgentsInfo[iAgent].charge <= 0 ||
             ( mAgentsInfo[iAgent].lastAction && mAgentsInfo[iAgent].lastAction->GetCode() == 10 ) ) {
          mAgentsInfo[iAgent].agentModel->Death( tDuration );
        } else if ( mAgentsInfo[iAgent].health > 0 && mAgentsInfo[iAgent].charge > 0 && mAgentsInfo[iAgent].lastAction ) {
          DBGP_DPY(LOG_STREAM(std::cerr) << "MoveTo(" << tLocation->GetX() << ", " << tLocation->GetY() << ", " << tLocation->GetElevation() << ", " << tDuration << ")" << std::endl);
          mAgentsInfo[iAgent].agentModel->MoveTo( tLocation->GetX(), tLocation->GetY(), tLocation->GetElevation(), tDuration );

          if ( mAgentsInfo[iAgent].lastAction->GetCode() == 9 )
            mAgentsInfo[iAgent].agentModel->ScanObject( tDuration );
          else if ( mAgentsInfo[iAgent].lastAction->GetCode() == 8 )
            mAgentsInfo[iAgent].agentModel->BeamObject( tDuration, 2 );
          else if ( mAgentsInfo[iAgent].lastAction->GetCode() == 7 )
            mAgentsInfo[iAgent].agentModel->BeamObject( tDuration, 1 );
          else if ( mAgentsInfo[iAgent].lastAction->GetCode() == 6 )
            mAgentsInfo[iAgent].agentModel->BeamObject( tDuration, 0 );
          else if ( mAgentsInfo[iAgent].lastAction->GetCode() == 5 )
            mAgentsInfo[iAgent].agentModel->Charge( tDuration );
          else if ( mAgentsInfo[iAgent].lastAction->GetCode() == 4 ) {
            int tDir = mAgentsInfo[iAgent].lastAction->GetDirection();
            if ( tDir % 2 == 0 )
              mAgentsInfo[iAgent].agentModel->RotateTo( 0.0f, 0.0f, -90.0f, tDuration );
            else
              mAgentsInfo[iAgent].agentModel->RotateTo( 0.0f, 0.0f, 90.0f, tDuration );
          }
        }
      }
      mMutex.unlock();
    }

    void EnvironmentDisplay3D::Redraw() {
      CalculateTime();
      ProcessInput();


      for ( size_t iAgent = 0; iAgent < mAgents.size(); ++iAgent )
        mAgents[iAgent]->FrameLogic( mDeltaTime );

      glutMainLoopEvent();
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective( 60.0f, (GLfloat)width / (GLfloat) height, 100.0f, 50000.0f);

      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
      glEnable( GL_DEPTH_TEST );

      if ( !mCamMode ) {
        float tAgentX, tAgentY, tAgentZ;
        mMutex.lock();
        tAgentX = mAgentsInfo[mCurrentAgent].agentModel->GetXPos();
        tAgentY = mAgentsInfo[mCurrentAgent].agentModel->GetYPos();
        tAgentZ = mAgentsInfo[mCurrentAgent].agentModel->GetZPos();
        mMutex.unlock();

        mTargetX = tAgentX;
        mTargetY = tAgentY;
        mTargetZ = tAgentZ;
      } else {
        mTargetX = mWorld->GetCenterX();
        mTargetY = mWorld->GetCenterY();
        mTargetZ = 0.0f;
      }

      float tCamX = mTargetX + mCamRadius * cos( mCamAlpha ) * sin( mCamTheta );
      float tCamY = mTargetY + mCamRadius * sin( mCamAlpha ) * sin( mCamTheta );
      float tCamZ = mTargetZ + mCamRadius * cos( mCamTheta );

      gluLookAt( tCamX, tCamY, tCamZ, mTargetX, mTargetY, mTargetZ, 0.0f, 0.0f, 1.0f );

      InitializeLighting();
      DrawScene();
      DrawGUI();

      glutSwapBuffers();
    }

    void EnvironmentDisplay3D::DrawScene() {
      int tAgentVisit = mCurrentAgent;
      if ( !mVisited )
        tAgentVisit = -2;
      else if ( mVisited && mCamMode )
        tAgentVisit = -1;
      mWorld->DrawWorldModel( mVisitedCells, AGENT_COLORS, tAgentVisit, mGrid );
      glEnable( GL_LIGHTING );
      for ( size_t iModel = 0; iModel < mModels.size(); ++iModel )
        mModels[iModel]->DrawModel();
      glDisable( GL_LIGHTING );
      for ( size_t iAgent = 0; iAgent < mAgents.size(); ++iAgent )
        mAgents[iAgent]->DrawAgent();
    }

    void EnvironmentDisplay3D::DrawGUI() {
      float tAgentX, tAgentY, tAgentZ, tAgentHealth, tAgentCharge;
      std::string tAgentName;
      int tHopperSize, tBaseSize, tLocationSize, tScore;
      Action* tLastAction;
      mMutex.lock();
      tAgentX         = mAgentsInfo[mCurrentAgent].x - mAgentsInfo[mCurrentAgent].baseX;
      tAgentY         = mAgentsInfo[mCurrentAgent].y - mAgentsInfo[mCurrentAgent].baseY;
      tAgentZ         = mAgentsInfo[mCurrentAgent].z - mAgentsInfo[mCurrentAgent].baseZ;
      tAgentName      = mAgentsInfo[mCurrentAgent].agentName;
      tAgentHealth    = mAgentsInfo[mCurrentAgent].health;
      tAgentCharge    = mAgentsInfo[mCurrentAgent].charge;
      tHopperSize     = mAgentsInfo[mCurrentAgent].hopperSize;
      tBaseSize       = mAgentsInfo[mCurrentAgent].baseSize;
      tLocationSize   = mAgentsInfo[mCurrentAgent].locationSize;
      tScore          = mAgentsInfo[mCurrentAgent].score;
      tLastAction     = mAgentsInfo[mCurrentAgent].lastAction;
      mMutex.unlock();

      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      glOrtho( 0.0f, (GLfloat)width, 0.0f, (GLfloat)height, -1.0f, 1.0f );
      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();

      glDepthMask( GL_FALSE );
      glDisable( GL_DEPTH_TEST );

      glDisable( GL_LIGHTING );
      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
      glEnable( GL_COLOR_MATERIAL );
      glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
      glEnable( GL_TEXTURE_2D );
      glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      DrawGUIElement( 0.0f, height, 128.0f, height - 128.0f, mTopLeft );                                          // Top Left
      DrawGUIElement( width - 128.0f, 128.0f, width, 0.0f, mBottomRight );                                        // Bottom Right
      DrawGUIElement( width - 52.0f, height / 2.0f + 128.0f, width - 20.0f, height / 2.0f - 128.0f, mHealthBar ); // Health Frame
      GLuint tBattery = mBattery25;
      if ( tAgentCharge > 75.0f )
        tBattery = mBatteryFull;
      else if ( tAgentCharge > 50.0f )
        tBattery = mBattery75;
      else if ( tAgentCharge > 25.0f )
        tBattery = mBattery50;
      DrawGUIElement( width - 106.0f, height - 10.0f, width - 10.0f, height - 58.0f, tBattery );                  // Battery

      glColor3f( AGENT_COLORS[mCurrentAgent][0], AGENT_COLORS[mCurrentAgent][1], AGENT_COLORS[mCurrentAgent][2] );
      DrawGUIElement( width / 2.0f - 128.0f, height, width / 2.0f + 128.0f, height - 32.0f, mAgentLabel );        // Agent Label
      DrawGUIElement( width / 2.0f - 128.0f, 0.0f, width / 2.0f + 128.0f, 32.0f, mAgentLabel );                   // Score

      // Agent Health Bars
      glPushMatrix();
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glBindTexture( GL_TEXTURE_2D, mHealth );
      glBegin( GL_QUADS );
      for ( int iHealth = 0; iHealth < ( tAgentHealth / 5 ); ++iHealth ) {
        float x     = width - 44.0f;
        float x2    = x + 16.0f;
        float y     = ( height / 2.0f - 70.0f ) + iHealth * 10.0f;
        float y2    = y - 8.0f;
        glTexCoord2f( 0.0f, 1.0f );
        glVertex2f( x, y );
        glTexCoord2f( 1.0f, 1.0f );
        glVertex2f( x2, y );
        glTexCoord2f( 1.0f, 0.0f );
        glVertex2f( x2, y2 );
        glTexCoord2f( 0.0f, 0.0f );
        glVertex2f( x, y2 );
      }
      glEnd();
      glPopMatrix();

      glDisable( GL_BLEND );
      glDisable( GL_TEXTURE_2D );
      glEnable( GL_DEPTH_TEST );
      glDepthMask( GL_TRUE );

      // Text labels
      char buffer[32];
      glColor3f( 1.0f, 1.0f, 1.0f );
      std::string tName = tAgentName;
      DrawTitle( width / 2.0f - ( tName.length() / 2.0f * 11.0f ), height - 24.0f, tName.c_str(), 0 );

      sprintf(buffer,"Score: %i", (int)tScore );
      std::string tScoreStr = buffer;
      DrawTitle( width / 2.0f - ( tScoreStr.length() / 2.0f * 11.0f ), 10.0f, tScoreStr.c_str(), 0 );

      std::string tAction;
      if ( tAgentHealth <= 0 )
        tAction = "DESTROYED";
      else if( tAgentCharge <= 0 )
        tAction = "BATTERY DEAD";
      else if ( tLastAction && tLastAction->GetCode() >= 0 && (size_t)tLastAction->GetCode() < mActionStrings.size() )
        tAction = mActionStrings[tLastAction->GetCode()];
      else
        tAction = "UNKNOWN ACTION";
      if ( tAction == "LOOKING" )
        tAction += " " + mActionDirection[tLastAction->GetDirection()];
      DrawTitle( 10.0f, 105.0f, tAction.c_str(), 1 );

      sprintf(buffer,"Objects at location: %i", (int)tLocationSize );
      std::string tObjects = buffer;
      DrawTitle( 10.0f, 90.0f, tObjects.c_str(), 1 );

      sprintf(buffer,"Hopper Size: %i", (int)tHopperSize );
      std::string tHopper = buffer;
      DrawTitle( 10.0f, 75.0f, tHopper.c_str(), 1 );

      sprintf(buffer,"Base Size: %i", (int)tBaseSize );
      std::string tBase = buffer;
      DrawTitle( 10.0f, 60.0f, tBase.c_str(), 1 );

      sprintf(buffer,"X: %i", (int)tAgentX );
      std::string tXPos = buffer;
      DrawTitle( 10.0f, 45.0f, tXPos.c_str(), 1 );

      sprintf(buffer,"Y: %i", (int)tAgentY );
      std::string tYPos = buffer;
      DrawTitle( 10.0f, 30.0f, tYPos.c_str(), 1 );

      sprintf(buffer,"Z: %.2f", tAgentZ );
      std::string tZPos = buffer;
      DrawTitle( 10.0f, 15.0f, tZPos.c_str(), 1 );

      sprintf(buffer,"Charge: %.2f", tAgentCharge );
      std::string tCharge = buffer;
      DrawTitle( width - 100.0f, height - 70.0f, tCharge.c_str(), 1 );

      sprintf(buffer,"FPS: %.2f", mFPS );
      std::string tFPS = buffer;
      DrawTitle( width - 90.0f, 20.0f, tFPS.c_str(), 1 );

      if ( mHelp ) {
        DrawTitle( 20.0f, height - 30.0f, "[w,a,s,d] - Camera Controls", 1 );
        DrawTitle( 20.0f, height - 45.0f, "[r,f] - Camera Zoom", 1 );
        DrawTitle( 20.0f, height - 60.0f, "[q,e] - Cycle Through Agents", 1 );
        DrawTitle( 20.0f, height - 75.0f, "[g] - Toggle Grid", 1 );
        DrawTitle( 20.0f, height - 90.0f, "[v] - Toggle Visited", 1 );
        DrawTitle( 20.0f, height - 105.0f, "[c] - Toggle Camera Mode", 1 );
        DrawTitle( 20.0f, height - 120.0f, "[h] - Toggle Help", 1 );
      }

      glDisable( GL_COLOR_MATERIAL );
      glEnable( GL_DEPTH_TEST );
      glEnable( GL_LIGHTING );
      glDepthMask( GL_TRUE );
    }

    void EnvironmentDisplay3D::DrawGUIElement( float x1, float y1, float x2, float y2, GLuint texture ) {
      glPushMatrix();
      glBindTexture( GL_TEXTURE_2D, texture );
      glBegin( GL_QUADS );
      glTexCoord2f( 0.0f, 1.0f );
      glVertex2f( x1, y1 );
      glTexCoord2f( 1.0f, 1.0f );
      glVertex2f( x2, y1);
      glTexCoord2f( 1.0f, 0.0f );
      glVertex2f( x2, y2 );
      glTexCoord2f( 0.0f, 0.0f );
      glVertex2f( x1, y2 );
      glEnd();
      glPopMatrix();
    }

    void EnvironmentDisplay3D::ProcessInput() {
      for ( int iCharacter = 0; iCharacter < 256; ++iCharacter )
        LIFTED[iCharacter] = LIFTED[iCharacter] && KEYS[iCharacter];

      if ( GetKeyHeld('a') )
        mCamAlpha -= ( 1.0f * mDeltaTime );
      if ( GetKeyHeld('d') )
        mCamAlpha += ( 1.0f * mDeltaTime );
      if ( GetKeyHeld('w') ) {
        mCamTheta += ( 1.0f * mDeltaTime );
        if ( mCamTheta > 20.0f )
          mCamTheta = 20.0f;
      }
      if ( GetKeyHeld('s') ) {
        mCamTheta -= ( 1.0f * mDeltaTime );
        if ( mCamTheta < 19.0f )
          mCamTheta = 19.0f;
      }
      if ( GetKeyHeld('r') ) {
        mCamRadius -= ( 4000.0f * mDeltaTime );
        if ( mCamRadius < 2000.0f )
          mCamRadius = 2000.0f;
      }
      if ( GetKeyHeld('f') ) {
        mCamRadius += ( 4000.0f * mDeltaTime );
        if ( mCamRadius > 25000.0f )
          mCamRadius = 25000.0f;
      }

      if ( GetKeyPressed('v') )
        mVisited = !mVisited;

      if ( GetKeyPressed('g') )
        mGrid = !mGrid;

      if ( GetKeyPressed('c') )
        mCamMode = !mCamMode;

      if ( GetKeyPressed('h') )
        mHelp = !mHelp;

      if ( GetKeyPressed('q') && !GetKeyPressed('e') ) {
        mCurrentAgent ++;
        if ( (size_t)mCurrentAgent >= mAgentsInfo.size() )
          mCurrentAgent = 0;
      }
      if ( GetKeyPressed('e') && !GetKeyPressed('q') ) {
        mCurrentAgent --;
        if ( mCurrentAgent < 0 )
          mCurrentAgent = mAgentsInfo.size() - 1;
      }
    }

    void EnvironmentDisplay3D::CalculateTime() {
      mFrames         += 1;
      mCurrentTime    = std::chrono::duration_cast< std::chrono::duration<double> >( Clock::now() - mStartTime ).count();
      mDeltaTime      = mCurrentTime - mLastTime;
      mTotalTime      += mDeltaTime;
      mLastTime       = mCurrentTime;
      mFPS            = mFrames / mTotalTime;
      if ( mFrames % 10000 == 0 ) {
        mFrames     = 0;
        mFPS        = 0;
        mTotalTime  = 0;
      }
    }
  } // End: namespace Scavenger
} // End: namespace ai

#else
#endif
