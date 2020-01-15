#ifndef _VERTEXCOVERLOCALSTATE_H_
#define _VERTEXCOVERLOCALSTATE_H_

#include "ai_local_search.h"
#include "VertexCoverModel.h"

namespace example {
  namespace VertexCover {

    class LocalState : public ai::LocalSearch::State {
    public:
      LocalState( const Model& model );
      LocalState( const LocalState &rhs );

      /* virtual to allow destructor chaining */
      virtual ~LocalState();

      /*
       * Calculates value of the state
       * Higher values represent states that are closer
       * to the goal state.
       */
      virtual double Value() const;

      /* Text display of state */
      virtual std::ostream &Display(std::ostream &os) const;

      const Model& getModel( ) const;
      Model& getModel( );
      
    protected:
      Model mModel;
      
    private:
    };
    

  }
}


#endif /* _VERTEXCOVERLOCALSTATE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
