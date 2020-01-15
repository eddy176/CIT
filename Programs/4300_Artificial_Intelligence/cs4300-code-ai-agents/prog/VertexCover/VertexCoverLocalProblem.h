#ifndef _VERTEXCOVERLOCALPROBLEM_H_
#define _VERTEXCOVERLOCALPROBLEM_H_

#include "ai_local_search.h"
#include "VertexCoverModel.h"
#include "VertexCoverLocalState.h"

namespace example {
  namespace VertexCover {
    
    class LocalProblem : public ai::LocalSearch::Problem {
    public:
      LocalProblem( const Model& starting_model, const int max_try_count );
      
      /* virtual to allow destructor chaining */
      virtual ~LocalProblem();

      /* evaluates state_in to see if random restart
       * should stop.
       * Note that a state may be good enough because
       * it has reached some critical value, or because
       * enough restarts have occurred.
       *
       * returns true if restart should stop,
       * returns false if restart should continue.
       */
      virtual bool GoodEnough(const ai::LocalSearch::State * const state_in);

      /* Allocate a random state from the legal state space.
       * The returned state must be 'delete'd by the
       * calling code. This is typically the local search Algorithm.
       */
      virtual ai::LocalSearch::State *RandomState() const;

      /* Select the neighbor of state_in with the
       * highest State::Value().  Allocate the
       * state and return it.
       * The returned state must be 'delete'd by the
       * calling code. This is typically the local search Algorithm.
       *
       * neighbors_generated must be set to the number of states generated,
       * including the state returned.  This contributes to the accounting system
       * for total number of nodes generated.
       */
      virtual ai::LocalSearch::State *BestNeighbor(const ai::LocalSearch::State * const state_in, int& neighbors_generated ) const;

      /* Allocate a neighbor of state_in and return it.
       * The returned state must be 'delete'd by the
       * calling code. This is typically the local search Algorithm.
       */
      virtual ai::LocalSearch::State *RandomNeighbor(const ai::LocalSearch::State * const state_in) const;

      /* Allocate a child state from mixing the 
       * The returned state must be 'delete'd by the
       * calling code. This is typically the local search Algorithm.
       */
      virtual ai::LocalSearch::State *ChildState(const ai::LocalSearch::State * const state1_in, const ai::LocalSearch::State * const state2_in, double mix_point) const;
      
    protected:

      Model mStartingModel;
      int   mTryCount;
      int   mMaxTryCount;
      
    private:
    };
  }
}


#endif /* _VERTEXCOVERLOCALPROBLEM_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
