#include "SudokuState.h"
#include <iostream>

namespace example {
  namespace Sudoku {

    State::State( const Board& model )
      : mModel( model ) {
    }

    State::State( const State& rhs ) {
      *this = rhs;
    }

    State::~State( ) {
    }

    void State::Display( ) const {
      mModel.ToStream( std::cout );
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
    
    const Board& State::getModel( ) const {
      return mModel;
    }

    Board& State::getModel( ) {
      return mModel;
    }
    
  }
}
