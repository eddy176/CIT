#include "SudokuLocalState.h"
#include <iostream>

namespace example {
  namespace Sudoku {

		LocalState::LocalState( const Board &board_in )
			: mModel( board_in )	{
		}
    
		LocalState::LocalState( const LocalState &rhs )	{
			mModel = rhs.mModel;
		}
		
		LocalState::~LocalState( )	{
		}
    
		double LocalState::Value( ) const {
      // negated to make higher values more desirable
			return static_cast< double >( -1.0 * this->mModel.CountConflicts( ) );
		}
		
		std::ostream &LocalState::Display( std::ostream &os ) const {
			this->mModel.Display( os );
			return os;
		}
    
	  const Board& LocalState::getModel( ) const {
      return this->mModel;
	  }
    
    Board& LocalState::getModel( ) {
      return this->mModel;
	  }
  }
}
