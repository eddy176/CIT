#include "RectangleAction.h"
#include <iostream>

namespace ai {
  namespace rectangle {

    Action::Action( const Move& move ) 
      : mMove( move ) {
    }

    Action::~Action( ) {
    }

    void Action::Display( ) const {
      std::cout << mMove.DisplayString( ) << std::endl;
    }

    const Move& Action::getMove( ) const {
      return mMove;
    }

  }
}

std::ostream& operator<<( std::ostream& os, const ai::rectangle::Action& action ) {
  os << action.getMove( ).DisplayString( );
  return os;
}
