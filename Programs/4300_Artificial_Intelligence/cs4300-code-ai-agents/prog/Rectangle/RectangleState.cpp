#include "RectangleState.h"
#include "ai_search.h"
#include <iostream>
#include <sstream>

namespace ai {
  namespace rectangle {

    State::State( const Model& model )
      : mModel( model ) {
    }

    State::State( const State& rhs ) {
      *this = rhs;
    }

    State::~State( ) {
    }

    void State::Display( ) const {
      std::cout << mModel.DisplayString( ) << std::endl;
    }

    bool State::IsEqual(const ai::Search::State * const state_in) const {
      const State * const state = dynamic_cast< const State * const >( state_in );
      return mModel == state->mModel;
    }

    bool State::IsLessThan(const ai::Search::State * const state_in) const {
      const State * const state = dynamic_cast< const State * const >( state_in );
      return mModel < state->mModel;
    }

    bool State::operator==( const State& rhs ) const {
      return this->IsEqual( &rhs );
    }

    State& State::operator=( const State& rhs) {
      mModel = rhs.mModel;
      return *this;
    }
    
    const Model& State::getModel( ) const {
      return mModel;
    }

    Model& State::getModel( ) {
      return mModel;
    }
      
  }
}

std::ostream& operator<<( std::ostream& os, const ai::rectangle::State& state ) {
  os << state.getModel( ).DisplayString( );
  return os;
}
