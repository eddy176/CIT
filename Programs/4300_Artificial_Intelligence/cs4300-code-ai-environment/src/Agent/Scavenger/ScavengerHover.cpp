#if USE_GLUT

#include <ai_scavenger.h>
#include <cmath>

namespace ai {
  namespace Scavenger {

    HoverAgent::HoverAgent( float x, float y, float z ) {
      mRed = mGreen = mBlue = 1.0f;
      mYaw = mPitch = mRoll = 0.0f;
      mDestX = mDestY = mDestZ = 0.0f;
      mDestYaw = mDestPitch = mDestRoll = 0.0f;
      mOriginYaw = mOriginPitch = mOriginRoll = 0.0f;

      mHoverZ             = z;
      mXOrigin            = x;
      mYOrigin            = y;
      mZOrigin            = z;
      mXPos               = x;
      mYPos               = y;
      mZPos               = z;

      mBeamType           = 0;
      mBeamAnimTime       = 0;
      mCurrentTime        = 0.0f;
      mMoveAnimTime       = 0.0f;
      mRotateAnimTime     = 0.0f;
      mScanAnimTime       = 0.0f;
      mChargeAnimTime     = 0.0f;
      mDeathAnimTime      = 0.0f;
      mCharging           = false;
      mScanning           = false;
      mRotating           = false;
      mMoving             = false;
      mBeaming            = false;
      mAlive              = true;
      mDieing             = false;

      mTextureMgr         = new TextureManager();
      mBeamTexture        = mTextureMgr->LoadTexture( "ScavengerData/beam.tga", true );
      mObjectTexture      = mTextureMgr->LoadTexture( "ScavengerData/object.tga", false );
      mScanTexture        = mTextureMgr->LoadTexture( "ScavengerData/scanner.tga", false );
      mChargeTexture      = mTextureMgr->LoadTexture( "ScavengerData/charge.tga", false );

      mBody               = new Model();
      mAccents            = new Model();
      mProp1              = new Model();
      mProp2              = new Model();
      mProp3              = new Model();
      mProp4              = new Model();
      mBeam               = new Model();
      mObject             = new Model();
      mScan               = new Model();
      mCharge             = new Model();

      mBeam->LoadModel( "ScavengerData/dronebeam.obj", mBeamTexture );
      mObject->LoadModel( "ScavengerData/object.obj", mObjectTexture );
      mScan->LoadModel( "ScavengerData/scanner.obj", mScanTexture );
      mCharge->LoadModel( "ScavengerData/charge.obj", mChargeTexture );

      mProp2->SetModelId( mProp1->GetModelId() );
      mProp3->SetModelId( mProp1->GetModelId() );
      mProp4->SetModelId( mProp1->GetModelId() );

      mProp1->SetPosition( -0.398, 161.587, 0.0 );
      mProp2->SetPosition( 159.682, 6.752, 0.0 );
      mProp3->SetPosition( 0.316, -161.847, 0.0 );
      mProp4->SetPosition( -159.899, 5.913, 0.0 );
      mScan->SetPosition( 0.0f, 0.0f, 160.0f );
      mObject->SetPosition( 0.0f, 0.0f, -15.0f );

      mBeam->SetColor( 0.0f, 1.0f, 1.0f, 1.0f );
    }

    void HoverAgent::InstanceModel( GLuint model, GLuint modelTex, GLuint accents, GLuint prop ) {
      mBody->SetModelId( model );
      mAccents->SetModelId( accents );
      mProp1->SetModelId( prop );
      mProp2->SetModelId( prop );
      mProp3->SetModelId( prop );
      mProp4->SetModelId( prop );

      mBody->SetTextureId( modelTex );
      mProp1->SetTextureId( modelTex );
      mProp2->SetTextureId( modelTex );
      mProp3->SetTextureId( modelTex );
      mProp4->SetTextureId( modelTex );
    }

    void HoverAgent::SetColor( float red, float green, float blue, float alpha ) {
      mAccents->SetColor( red, green, blue, alpha );
    }

    void HoverAgent::SetPosition( float x, float y, float z ) {
      mXOrigin = x;
      mYOrigin = y;
      mZOrigin = z;
    }
    void HoverAgent::SetRotation( float y, float p, float r ) {
      mYaw    = y;
      mPitch  = p;
      mRoll   = r;
    }

    void HoverAgent::MoveTo( float x, float y, float z, float duration ) {
      if ( !mMoving ) {
        mDestX          = x;
        mDestY          = y;
        mDestZ          = z;
        mXOrigin        = mXPos;
        mYOrigin        = mYPos;
        mZOrigin        = mZPos;
        mMoveDuration   = duration;
        mMoving         = true;
        mMoveAnimTime   = 0.0f;
      }
    }

    void HoverAgent::RotateTo( float y, float p, float r, float duration ) {
      if ( !mRotating ) {
        mDestYaw        = mOriginYaw + y;
        mDestPitch      = mOriginPitch + p;
        mDestRoll       = mOriginRoll + r;
        mRotateDuration = duration;
        mOriginYaw      = mYaw;
        mOriginPitch    = mPitch;
        mOriginRoll     = mRoll;
        mRotateAnimTime = 0.0f;
        mRotating       = true;
      }
    }

    void HoverAgent::BeamObject( float duration, int type ) {
      if ( !mBeaming ) {
        if ( type == 0 )
          mObject->SetPosition( 0.0f, 0.0f, -15.0f );
        else
          mObject->SetPosition( 0.0f, 0.0f, 160.0f );
        mBeaming        = true;
        mBeamDuration   = duration;
        mBeamAnimTime   = 0.0f;
        mBeamType       = type;
      }
    }

    void HoverAgent::ScanObject( float duration ) {
      if ( !mScanning ) {
        mScanning       = true;
        mScanDuration   = duration;
        mScanAnimTime   = 0.0f;
      }
    }

    void HoverAgent::Charge( float duration ) {
      if ( !mCharging ) {
        mCharging       = true;
        mChargeAnimTime = 0.0f;
        mChargeDuration = duration;
        mCharge->SetPosition( 0.0f, 0.0f, 0.0f );
      }
    }

    void HoverAgent::Death( float duration ) {
      if ( !mDieing ) {
        mDieing         = true;
        mDeathAnimTime  = 0.0f;
        mDeathDuration  = duration;
      }
    }

    void HoverAgent::DrawAgent() {
      glEnable( GL_LIGHTING );
      glPushMatrix();
      glTranslatef( mXPos, mYPos, mZPos );
      if ( mBeaming )
        mObject->DrawModel();
      glPopMatrix();
      glPushMatrix();
      glTranslatef( mXPos, mYPos, mHoverZ );
      glRotatef( mYaw, 1, 0, 0 );
      glRotatef( mPitch, 0, 1, 0 );
      glRotatef( mRoll, 0, 0, 1 );

      mBody->DrawModel();
      mAccents->DrawModel();
      mProp1->DrawModel();
      mProp2->DrawModel();
      mProp3->DrawModel();
      mProp4->DrawModel();

      glDisable( GL_LIGHTING );
      if ( mBeaming )
        mBeam->DrawModel();
      if ( mScanning )
        mScan->DrawModel();
      if ( mCharging )
        mCharge->DrawModel();

      glPopMatrix();
    }

    void HoverAgent::FrameLogic( double deltaTime ) {
      mCurrentTime += deltaTime;

      if ( mAlive ) {
        if ( mDieing && mDeathAnimTime >= mDeathDuration ) {
          mAlive = false;
        } else if ( mDieing ) {
          mZPos = mZOrigin - 160.0 * ( mDeathAnimTime / mDeathDuration );
          mDeathAnimTime += deltaTime;
        }

        if ( mMoving && ( mMoveAnimTime / mMoveDuration >= 1.0 ) ) {
          mXOrigin        = mXPos;
          mYOrigin        = mYPos;
          mZOrigin        = mZPos;
          mMoving         = false;
          mMoveAnimTime   = 0;
        } else if ( mMoving ) {
          float tPos      = mMoveAnimTime / mMoveDuration;
          mXPos           = ( 1 - tPos ) * mXOrigin + tPos * mDestX;
          mYPos           = ( 1 - tPos ) * mYOrigin + tPos * mDestY;
          mZPos           = ( 1 - tPos ) * mZOrigin + tPos * mDestZ;
          mMoveAnimTime   += deltaTime;
        }

        if ( mRotating && ( mRotateAnimTime / mRotateDuration >= 1.0 ) ) {
          mOriginYaw      = mYaw;
          mOriginPitch    = mPitch;
          mOriginRoll     = mRoll;
          mRotating       = false;
          mRotateAnimTime = 0;
        } else if ( mRotating ) {
          float tPerc     = mRotateAnimTime / mRotateDuration;
          mYaw            = mOriginYaw + ( mDestYaw - mOriginYaw ) * tPerc;
          mPitch          = mOriginPitch + ( mDestPitch - mOriginPitch ) * tPerc;
          mRoll           = mOriginRoll + ( mDestRoll - mOriginRoll ) * tPerc;
          mRotateAnimTime += deltaTime;
        }

        if ( mBeaming && mBeamAnimTime >= mBeamDuration ) {
          mBeamDuration   = 0;
          mBeamAnimTime   = 0;
          mBeaming        = false;
        } else if ( mBeaming ) {
          if ( mBeamType == 0 )
            mObject->SetPosition( 0.0f, 0.0f, 160.0f * ( mBeamAnimTime / mBeamDuration ) - 15.0f );
          else
            mObject->SetPosition( 0.0f, 0.0f, 160.0f - 160.0f * ( mBeamAnimTime / mBeamDuration ) - 15.0f );
          mBeamAnimTime   += deltaTime;
        }

        if ( mScanning && mScanAnimTime >= mScanDuration ) {
          mScanning       = false;
          mScanAnimTime   = 0.0f;
          mScanDuration   = 0.0f;
        } else if ( mScanning ) {
          mScanAnimTime   += deltaTime;
          mScan->SetRotation( 0.0f, 45.0f * (float)cos( ( mScanAnimTime / mScanDuration ) * 2.0f * 3.14159f ), 0.0f );
        }

        if ( mCharging && mChargeAnimTime >= mChargeDuration ) {
          mCharging       = false;
          mChargeAnimTime = 0.0f;
          mChargeDuration = 0.0f;
        } else if ( mCharging ) {
          mCharge->SetPosition( 0.0f, 0.0f, 160.0f * ( mChargeAnimTime / mChargeDuration ) );
          mChargeAnimTime += deltaTime;
        }

        mHoverZ = mZPos + cos( mCurrentTime ) * 25;
        mProp1->SetRotation( 0.0f, 0.0f, mCurrentTime * 2000.0f );
        mProp2->SetRotation( 0.0f, 0.0f, mCurrentTime * 2000.0f );
        mProp3->SetRotation( 0.0f, 0.0f, mCurrentTime * 2000.0f );
        mProp4->SetRotation( 0.0f, 0.0f, mCurrentTime * 2000.0f );

      }
    }

    float HoverAgent::GetXPos() {
      return mXPos;
    }

    float HoverAgent::GetYPos() {
      return mYPos;
    }

    float HoverAgent::GetZPos() {
      return mZPos;
    }

  } // End: namespace Scavenger
} // End: namespace ai

#else
#endif
