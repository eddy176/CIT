#ifndef _SCAVENGERHOVER_H_
#define _SCAVENGERHOVER_H_

#include <ai_scavenger.h>

#if USE_GLUT

namespace ai {
  namespace Scavenger {

    class HoverAgent {
    public:
      HoverAgent( float x, float y, float z );                                            // Constructor

      void InstanceModel(  GLuint model,   GLuint modelTex,
                           GLuint accents, GLuint prop );                                 // Loads Models from an Instance
      void SetColor( float red, float green, float blue, float alpha );                   // Sets the Color of the accents
      void SetPosition( float x, float y, float z );                                      // Sets the position of the model
      void SetRotation( float y, float p, float r );                                      // Sets the rotation of the model
      float GetXPos();                                                                    // Returns the X Position of the model
      float GetYPos();                                                                    // Returns the Y Position of the model
      float GetZPos();                                                                    // Returns the Z Position of the model

      void DrawAgent();                                                                   // Draws the Agent to the screen
      void FrameLogic( double deltaTime );                                                // Executes one frame of logic
      void MoveTo( float x, float y, float z, float duration );                           // Tells the model to move to a location
      void RotateTo( float y, float p, float r, float duration );                         // Tells the model to rotate over duration
      void BeamObject( float duration, int type );                                        // Tells model to perform Beam Animation
      void ScanObject( float duration );                                                  // Tells model to perform scan Animation
      void Charge( float duration );                                                      // Tells model to perform charge Animation
      void Death( float duration );                                                       // Tells model to perform death Animation
    protected:
    private:
      bool mAlive;                                                                        // Agent Alive
      bool mMoving, mRotating, mBeaming, mScanning, mCharging, mDieing;                   // Determines if an animation is playing
      float mDeathAnimTime, mDeathDuration;                                               // Duration and current time of Animation
      float mChargeAnimTime, mChargeDuration;                                             // Duration and current time of Animation
      float mScanAnimTime, mScanDuration;                                                 // Duration and current time of Animation
      float mBeamAnimTime, mBeamDuration;                                                 // Duration and current time of Animation
      int mBeamType;                                                                      // Type of Beam Animation 0 = pickup, 1 = drop
      float mRotateAnimTime, mMoveAnimTime, mRotateDuration, mMoveDuration;               // Duration and current time of Animation
      float mDestX, mDestY, mDestZ;                                                       // Location that model is moving to
      float mDestYaw, mDestPitch, mDestRoll;                                              // Rotation that model is rotating to
      float mOriginYaw, mOriginPitch, mOriginRoll;                                        // Rotation that model is rotating from
      float mHoverZ;                                                                      // Current draw Z for hover animation
      float mRed, mGreen, mBlue;                                                          // Agent color
      float mXOrigin, mYOrigin, mZOrigin;                                                 // Location that mode is moving from
      float mXPos, mYPos, mZPos;                                                          // Current position of model
      float mYaw, mPitch, mRoll;                                                          // Current rotation of model
      float mCurrentTime;                                                                 // Current time
      TextureManager* mTextureMgr;                                                        // Texture Manager
      GLuint mObjectTexture, mBeamTexture, mScanTexture, mChargeTexture;    // Model Textures
      Model *mBody, *mAccents, *mBeam, *mObject, *mScan, *mCharge;                        // Model body and animation parts
      Model *mProp1, *mProp2, *mProp3, *mProp4;                                           // Model props
    };
  } // End: namespace Scavenger
} // End: namespace ai

#else
#endif

#endif /* _SCAVENGERHOVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
