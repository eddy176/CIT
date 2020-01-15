#if USE_GLUT

#include <ai_scavenger.h>
#include <ai_glut.h>

#include <iostream>

void FatalError( std::string msg ) {
  std::cout << "Error: " << msg << std::endl;
  exit(0);
}

TextureManager::TextureManager() {
  mTextureCount = -1;
  glGenTextures( MAX_TEXTURES, mTextureNames );
}

TextureManager::~TextureManager() {}

void TextureManager::SetTextureCount( int count ) {
  mTextureCount = count;
}

GLuint TextureManager::LoadTexture( std::string filename, bool wrap ) {
  if ( mTextureMap[filename] ){
    return mTextureMap[filename];
  } else {
    std::string tEnding = filename.substr( filename.find( '.' ) );
    const GLuint BAD_TEXTURE = (GLuint)-1;
    GLuint tTexture = BAD_TEXTURE;
    if ( tEnding == ".tga" ){
      tTexture = LoadTgaImage( filename, wrap );
    } else if ( tEnding == ".bmp" ) {
      FatalError( "BMP format is not yet Supported." );
    } else if ( tEnding == ".jpg" ) {
      FatalError( "JPG format is not yet Supported." );
    } else if( tEnding == ".png" ) {
      FatalError( "PNG format is not yet Supported." );
    } else {
      FatalError( "Unsupported File Format." );
    }

    if ( tTexture == BAD_TEXTURE || tTexture == 0 )
      FatalError( "Could Not Load Image: " + filename );

    mTextureMap[filename] = tTexture;
    return tTexture;
  }
}

GLuint TextureManager::LoadTgaImage( std::string filename, bool wrap ) {
  FILE *tFile;
  tFile = fopen( filename.c_str(), "r" );
  if ( !tFile )
    return 0;

  TGA_FOOTER tFooter;
  TGA_HEADER tHeader;

  if ( fseek( tFile, 0L - sizeof( tFooter ), SEEK_END ) || fread( &tFooter, sizeof( tFooter ), 1, tFile) != 1 )
    FatalError( "Cannot Read TGA footer" );

  if ( fseek( tFile, 0, SEEK_SET ) || fread( &tHeader,sizeof( tHeader ), 1, tFile ) != 1 )
    FatalError( "Cannot Read TGA header" );

  if ( tHeader.id && fseek( tFile, tHeader.id, SEEK_CUR ) )
    FatalError( "TGA header error" );

  int tWidth        = abs( ( tHeader.widthEnd << 8 ) | tHeader.width );
  int tHeight        = abs( ( tHeader.heightEnd << 8 ) | tHeader.height );
  int tPixelDepth    = abs( tHeader.pixelDepth );

  int tTextureType;
  if ( tPixelDepth == 24 )
    tTextureType = GL_BGR_EXT;
  else
    tTextureType = GL_BGRA_EXT;

  if ( tHeader.imageType == 1 )
    FatalError( "Indexed TGA is not yet supported" );
  if ( tHeader.imageType == 9 || tHeader.imageType == 10 || tHeader.imageType == 11 )
    FatalError( "Compressed TGA is not yet supported" );

  int tMode        = tPixelDepth / 8;
  int tTotalBytes    = tHeight * tWidth * tMode;

  GLubyte *tImageData = (GLubyte*)malloc( tTotalBytes );
  if ( tImageData == NULL )
    FatalError( "TGA memory error. Tried to Allocate " + std::to_string( (long double)tTotalBytes ) + " bytes and failed." );

  int tWidthBytes = tWidth * tMode;
  GLubyte * tData;

  for ( int iRow = 0; iRow < tHeight; ++iRow) {
    tData = tImageData + iRow * tWidthBytes;
    if ( fread( tData, tMode, tWidth, tFile) != (size_t)tWidth )
      FatalError( "Could not Read TGA Image Data" );
  }

  fclose( tFile );

  mTextureCount += 1;

  glGenTextures( 1, &mTextureNames[mTextureCount] );
  glBindTexture( GL_TEXTURE_2D, mTextureNames[mTextureCount] );

  if( wrap ){
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  } else {
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
  }

  gluBuild2DMipmaps( GL_TEXTURE_2D, 4, tWidth, tHeight, tTextureType, GL_UNSIGNED_BYTE, tImageData );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

  return mTextureNames[mTextureCount];
}

#else
#endif
