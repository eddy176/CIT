#include "CubeException.h"

namespace ai {
  namespace rubiks {

    Exception::Exception( const std::string& msg ) 
      : std::exception(), mMsg( msg ) {
    }

    const char* Exception::what() const throw() {
      return mMsg.c_str( );
    }

  }
}
