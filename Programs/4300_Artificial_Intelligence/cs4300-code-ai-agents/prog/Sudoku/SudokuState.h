#ifndef _SUDOKUSTATE_H_
#define _SUDOKUSTATE_H_

#include "ai_search.h"
#include "SudokuModel.h"

namespace example {
  namespace Sudoku {

    class State : public ai::Search::State {
    public:
      State( const Board& model );
      State( const State& rhs );
      virtual ~State( );
      virtual void Display( ) const;
      virtual bool IsEqual(const ai::Search::State * const state_in) const;
      virtual bool IsLessThan(const ai::Search::State * const state_in) const;

      bool operator==( const State& rhs ) const;
      State& operator=( const State& rhs);

      const Board& getModel( ) const;
      Board& getModel( );
      
    protected:
      Board mModel;
      
    private:
      
    };
    
  }
}

#endif /* _SUDOKUSTATE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
