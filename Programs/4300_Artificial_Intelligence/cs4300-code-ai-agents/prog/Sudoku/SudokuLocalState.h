#ifndef _SUDOKULOCALSTATE_H_
#define _SUDOKULOCALSTATE_H_

#include "ai_local_search.h"
#include "SudokuModel.h"

namespace example {
  namespace Sudoku {

    class LocalState : public ai::LocalSearch::State {
    public:
      LocalState( const Board& model );
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

      const Board& getModel( ) const;
      Board& getModel( );
      
    protected:
      Board mModel;
      
    private:
    };
    
  }
}

#endif /* _SUDOKULOCALSTATE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
