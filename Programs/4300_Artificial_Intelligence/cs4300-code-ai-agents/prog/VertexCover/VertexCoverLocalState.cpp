#include "VertexCoverLocalState.h"
#include <iostream>

namespace example {
  namespace VertexCover {

		LocalState::LocalState( const Model &model_in )
			: mModel( model_in )	{
		}
    
		LocalState::LocalState( const LocalState &rhs )	{
			mModel = rhs.mModel;
		}
    
		LocalState::~LocalState( )	{
		}
    
		double LocalState::Value( ) const {
      return mModel.getValue( );
		}
		
		std::ostream &LocalState::Display( std::ostream &os ) const {
			this->mModel.Display( os );
			return os;
		}
    
	  const Model& LocalState::getModel( ) const {
      return this->mModel;
	  }
    
    Model& LocalState::getModel( ) {
      return this->mModel;
	  }

  }
}
