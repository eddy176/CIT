#include <ai_scavenger.h>
#include <fstream>
#include <cmath>

#if USE_GLUT

namespace ai {
  namespace Scavenger {

    Model::Model() {
      mObjectId   = "";
      mCenterX    = 0;
      mCenterY    = 0;
      mTextureId  = 0;

      mColor[0] = mColor[1] = mColor[2] = mColor[3] = 1.0f;
      mXPos = mYPos = mZPos = 0.0f;
      mYaw = mPitch = mRoll = 0.0f;
    }

    Model::Model( std::string objId ) {
      mObjectId   = objId;
      mCenterX    = 0;
      mCenterY    = 0;
      mTextureId  = 0;

      mColor[0] = mColor[1] = mColor[2] = mColor[3] = 1.0f;
      mXPos = mYPos = mZPos = 0.0f;
      mYaw = mPitch = mRoll = 0.0f;
    }

    Model::~Model() {}

    void Model::DrawModel() {
      glPushMatrix();
      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
      glEnable( GL_COLOR_MATERIAL );
      glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
      glColor4f( mColor[0], mColor[1], mColor[2], mColor[3] );
      glDisable( GL_TEXTURE_2D );

      if ( mTextureId ) {
        glEnable( GL_TEXTURE_2D );
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        glBindTexture( GL_TEXTURE_2D, mTextureId );
      }
      glTranslatef( mXPos, mYPos, mZPos );
      glRotatef( mYaw, 1, 0, 0 );
      glRotatef( mPitch, 0, 1, 0 );
      glRotatef( mRoll, 0, 0, 1 );

      glCallList( mModelId );

      glDisable( GL_COLOR_MATERIAL );
      glDisable( GL_BLEND );
      if ( mTextureId )
        glDisable( GL_TEXTURE_2D );
      glPopMatrix();

    }

    void Model::StoreModel() {
      mModelId = glGenLists( 1 );
      glNewList( mModelId, GL_COMPILE );
      glPushMatrix();
      glTranslatef( 0.0f, 0.0f, 0.0f );
      glBegin( GL_TRIANGLES );
      for ( unsigned int iFace = 0; iFace < mFaces.size(); ++iFace) {
        glTexCoord3f( mTexCoords[(int)mFaces[iFace].t1].x, mTexCoords[(int)mFaces[iFace].t1].y, mTexCoords[(int)mFaces[iFace].t1].z );
        glNormal3f( mNormals[(int)mFaces[iFace].v1n].x, mNormals[(int)mFaces[iFace].v1n].y, mNormals[(int)mFaces[iFace].v1n].z );
        glVertex3f( mVertices[(int)mFaces[iFace].v1].x, mVertices[(int)mFaces[iFace].v1].y, mVertices[(int)mFaces[iFace].v1].z );
        glTexCoord3f( mTexCoords[(int)mFaces[iFace].t2].x, mTexCoords[(int)mFaces[iFace].t2].y, mTexCoords[(int)mFaces[iFace].t2].z );
        glNormal3f( mNormals[(int)mFaces[iFace].v2n].x, mNormals[(int)mFaces[iFace].v2n].y, mNormals[(int)mFaces[iFace].v2n].z );
        glVertex3f( mVertices[(int)mFaces[iFace].v2].x, mVertices[(int)mFaces[iFace].v2].y, mVertices[(int)mFaces[iFace].v2].z );
        glTexCoord3f( mTexCoords[(int)mFaces[iFace].t3].x, mTexCoords[(int)mFaces[iFace].t3].y, mTexCoords[(int)mFaces[iFace].t3].z );
        glNormal3f( mNormals[(int)mFaces[iFace].v3n].x, mNormals[(int)mFaces[iFace].v3n].y, mNormals[(int)mFaces[iFace].v3n].z );
        glVertex3f( mVertices[(int)mFaces[iFace].v3].x, mVertices[(int)mFaces[iFace].v3].y, mVertices[(int)mFaces[iFace].v3].z );
      }
      glEnd();
      glPopMatrix();
      glEndList();
    }

    Model::Vector3 Model::CalculateNormal( Vector3 focus, Vector3 point1, Vector3 point2 ) {
      float tx    = point1.x - focus.x;
      float ty    = point1.y - focus.y;
      float tz    = point1.z - focus.z;
      float tx2   = focus.x - point2.x;
      float ty2   = focus.y - point2.y;
      float tz2   = focus.z - point2.z;
      Vector3 tNormal;
      tNormal.x   = ty * tz2 - tz * ty2;
      tNormal.y   = tz * tx2 - tx * tz2;
      tNormal.z   = tx * ty2 - ty * tx2;
      float tMagnitude = sqrt( tNormal.x * tNormal.x + tNormal.y * tNormal.y + tNormal.z * tNormal.z);
      if ( tMagnitude != 0 ) {
        tNormal.x = tNormal.x / tMagnitude;
        tNormal.y = tNormal.y / tMagnitude;
        tNormal.z = tNormal.z / tMagnitude;
      }

      return tNormal;
    }

    std::string Model::GetId() {
      return mObjectId;
    }

    float Model::GetCenterX() {
      return mCenterX;
    }

    float Model::GetCenterY() {
      return mCenterY;
    }

    bool Model::LoadModel( std::string filename , GLuint texture ) {
      mTextureId  = texture;

      std::string   tLine;
      std::ifstream tFile(filename);

      if ( tFile.is_open() ) {
        while ( tFile.good() ) {
          getline( tFile, tLine );
          std::string     tToken;
          std::istringstream  tStringStream( tLine );

          getline( tStringStream, tToken, ' ' );
          if ( tToken == "v" ) {
            Vector3 tVert;
            getline( tStringStream, tToken, ' ' );
            getline( tStringStream, tToken, ' ' );
            tVert.x = (float)atof( tToken.c_str() );
            getline( tStringStream, tToken, ' ' );
            tVert.y = (float)atof( tToken.c_str() );
            getline( tStringStream, tToken, ' ' );
            tVert.z = (float)atof( tToken.c_str() );
            mVertices.push_back( tVert );
          } else if ( tToken == "vn" ) {
            Vector3 tNorm;
            getline( tStringStream, tToken, ' ' );
            tNorm.x = (float)atof( tToken.c_str() );
            getline( tStringStream, tToken, ' ' );
            tNorm.y = (float)atof( tToken.c_str() );
            getline( tStringStream, tToken, ' ' );
            tNorm.z = (float)atof( tToken.c_str() );
            mNormals.push_back( tNorm );
          } else if( tToken == "vt" ) {
            Vector3 tTexCoords;
            getline( tStringStream, tToken, ' ' );
            tTexCoords.x = (float)atof( tToken.c_str() );
            getline( tStringStream, tToken, ' ' );
            tTexCoords.y = (float)atof( tToken.c_str() );
            getline( tStringStream, tToken, ' ' );
            tTexCoords.z = (float)atof( tToken.c_str() );
            mTexCoords.push_back( tTexCoords );
          } else if( tToken == "f" ) {
            size_t  tCurrent;
            size_t  tNext;
            Face3 tFace;

            getline( tStringStream, tToken, ' ' );
            tCurrent  = 0;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.v1  = (int)atof( tToken.substr( tCurrent, tNext - tCurrent ).c_str() ) - 1;
            tCurrent  = tNext + 1;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.t1  = (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
            tCurrent  = tNext + 1;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.v1n = (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;

            getline( tStringStream, tToken, ' ' );
            tCurrent  = 0;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.v2  = (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
            tCurrent  = tNext + 1;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.t2  = (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str() ) - 1;
            tCurrent  = tNext + 1;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.v2n = (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;

            getline( tStringStream, tToken, ' ' );
            tCurrent  = 0;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.v3  = (int)atof( tToken.substr( tCurrent, tNext - tCurrent ).c_str()) - 1;
            tCurrent  = tNext + 1;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.t3  = (int)atof( tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;
            tCurrent  = tNext + 1;
            tNext   = tToken.find_first_of( '/', tCurrent );
            tFace.v3n = (int)atof(tToken.substr( tCurrent, tNext - tCurrent).c_str()) - 1;

            this->mFaces.push_back( tFace );
          }
        }
        tFile.close();
        StoreModel();
        return true;
      } else
        return false;
    }

    void Model::SetTextureId( GLuint id ) {
      mTextureId = id;
    }

    GLuint Model::GetModelId() {
      return mModelId;
    }

    void Model::SetModelId( GLuint modelId ) {
      mModelId = modelId;
    }

    void Model::SetColor( float red, float green, float blue, float alpha ) {
      mColor[0] = red;
      mColor[1] = green;
      mColor[2] = blue;
      mColor[3] = alpha;
    }

    void Model::SetPosition( float x, float y, float z ) {
      mXPos = x;
      mYPos = y;
      mZPos = z;
    }

    void Model::SetRotation( float yaw, float pitch, float roll ) {
      mYaw    = yaw;
      mPitch  = pitch;
      mRoll   = roll;
    }

    float Model::GetYaw() {
      return mYaw;
    }

    float Model::GetPitch() {
      return mPitch;
    }

    float Model::GetRoll() {
      return mRoll;
    }
  }
}
#else
#endif
