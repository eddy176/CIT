#ifndef _SCAVENGERMODEL_
#define _SCAVENGERMODEL_

#include <ai_glut.h>

#if USE_GLUT
namespace ai {
  namespace Scavenger {
    class Model {
    public:
      struct Vector3 {
        float x;
        float y;
        float z;
      };
      struct Face3 {
        float v1;
        float v2;
        float v3;
        std::vector< GLfloat> color;
        std::string material;
        int t1;
        int t2;
        int t3;
        int v1n;
        int v2n;
        int v3n;
        GLuint texture;
        GLuint modelId;
      };

      Model();                                                                            // Constructor
      Model( std::string objId );                                                         // Constructor
      virtual ~Model();                                                                   // Deconstructor

      virtual void DrawModel();                                                           // DrawModel to Screen
      void StoreModel();                                                                  // Stores Model on GPU
      Vector3 CalculateNormal( Vector3 focus, Vector3 point1, Vector3 point2 );           // Calculates the normal of a point
      std::string GetId();                                                                // Returns Model Id

      float GetCenterX();                                                                 // Returns the Center X Position
      float GetCenterY();                                                                 // Returns the Center Y Position

      bool LoadModel( std::string filename , GLuint texture );                            // Loads a model from a file
      void SetModelId( GLuint modelId );                                                  // Instanced Model
      GLuint GetModelId();                                                                // Returns the ModelId
      void SetTextureId( GLuint id );                                                     // Sets the models texture
      void SetColor( float red, float green, float blue, float alpha );                   // Sets the models color
      void SetPosition( float x, float y, float z );                                      // Sets the models position
      void SetRotation( float y, float p, float r );                                      // Sets the models orientation
      float GetYaw();                                                                     // Returns the model's yaw
      float GetPitch();                                                                   // Returns the model's pitch
      float GetRoll();                                                                    // Returns the model's roll
    protected:
      GLfloat mColor[4];                                                                  // Model Color
      std::string mObjectId;                                                              // Object string Id
      GLuint mModelId;                                                                    // OpenGL Model Id
      GLuint mTextureId;                                                                  // OpenGL Texture Id
      float mXPos, mYPos, mZPos;                                                          // Object Position
      float mYaw, mPitch, mRoll;                                                          // Object Orientation
      std::vector< Vector3 >  mVertices;                                                  // List of Vertices
      std::vector< Face3 >    mFaces;                                                     // List of Faces
      std::vector< Vector3 >  mNormals;                                                   // List of Normals
      std::vector< Vector3 >  mTexCoords;                                                 // List of Texture Coordinates
      float mCenterX, mCenterY;                                                           // Center of the Map
    private:
    };
  }
}

#else
#endif

#endif // _SCAVENGERMODEL
/* Local Variables: */
/* mode:c++         */
/* End:             */
