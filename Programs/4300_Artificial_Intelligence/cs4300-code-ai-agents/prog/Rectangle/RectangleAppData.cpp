#include "RectangleAppData.h"

namespace ai {
  namespace rectangle {

    Exception::Exception( const std::string& msg ) 
      : std::exception(), mMsg( msg ) {
    }

    const char* Exception::what() const throw() {
      return mMsg.c_str( );
    }

    AppData::AppData( std::istream &is_in, std::ostream &os_in ) 
      : is( is_in ),
        os( os_in ),
        done( false ) {
      model.Reset( config.rectangleWidth( ), config.rectangleHeight( ) );
    }
  }
}
