#ifndef _SCAVENGERENVIRONMENTDISPLAY3D_H_
#define _SCAVENGERENVIRONMENTDISPLAY3D_H_

#include <ai_scavenger.h>
#include <mutex>
#include <time.h>
#include <chrono>

#if USE_GLUT

namespace ai {
  namespace Scavenger {
    class Environment;

    class EnvironmentDisplay3D : public ai::Agent::EnvironmentDisplay {
    public:
      // Agent Structure for storing agent states
      struct AgentInfo {
        float x; float y; float z;
        float baseX, baseY, baseZ;
        float health; float charge;
        int baseSize; int hopperSize; int locationSize;
        int score;
        std::string agentName;
        Action * lastAction;
        HoverAgent * agentModel;
      };

      EnvironmentDisplay3D( ai::Agent::Environment *env, int widthIn, int heightIn );     // Display Constructor
      virtual ~EnvironmentDisplay3D();                                                    // Display Deconstructor
      void InitializeLighting();                                                          // Initialize the Lighting
      virtual void Redraw();                                                              // Draws One Frame

      void DrawScene();                                                                   // Draws the Current Scene
      void ProcessInput();                                                                // Processes User input
      void SetEnv( ai::Agent::Environment *env_in );                                      // Sets the environment
      void DrawGUI();                                                                     // Draws the user Interface
      void DrawGUIElement( float x1, float y1, float x2, float y2, GLuint texture );      // Draws a rectangle with attached texture
      void CalculateTime();                                                               // Calculates Delta Time
    protected:
      std::mutex mMutex;                                                                  // Mutex Control
      Environment * mEnvironment;                                                         // The Environment
      float mTargetX, mTargetY, mTargetZ;                                                 // Target Position
      float mCamAlpha, mCamTheta, mCamRadius;                                             // Camera Rotation
      EnvironmentModel *mWorld;                                                           // Environment Model
      std::vector< Model* > mModels;                                                      // World Models
      TextureManager *mTextureMgr;                                                        // Texture Manager
      int mCurrentAgent;                                                                  // Current Agent
      bool mCamMode;                                                                      // Camera Mode ( True = fixed, False = follow );
      bool mGrid;                                                                         // Grid on and Off
      bool mVisited;                                                                      // Visited Squares on/off
      bool mHelp;                                                                         // Help Menu
      std::vector< std::string > mActionStrings;                                          // Action Strings
      std::vector< std::string > mActionDirection;                                        // Action Directions

      std::map< std::pair< float, float >, std::vector< bool > > mVisitedCells;           // Visited Squares

      std::vector< AgentInfo > mAgentsInfo;                                               // Agent Information
      std::vector< HoverAgent* > mAgents;                                                 // Agent Models

      GLuint  mTopLeft, mBottomRight, mBatteryFull, mBattery75, mBattery50, mBattery25,
        mHealthBar, mHealth, mAgentLabel;                                           // GUI Textures

      int mFrames;                                                                        // Number of Frames since last FPS calculation
      double mDeltaTime, mFPS, mTotalTime, mCurrentTime, mLastTime;                       // Time Management Variables
      std::chrono::high_resolution_clock::time_point mStartTime;                          // Time Management Variables
      std::chrono::high_resolution_clock::time_point mLastServerTime;                     // Last Time Recieved Server Info
      double mTotalServerTime;                                                            // Total time between server clocks
      int mTotalServerTicks;                                                              // Total number of times recieved server info
    private:
    };
  }
}

#else
#endif

#endif /* _SCAVENGERENVIRONMENTDISPLAY3D_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
