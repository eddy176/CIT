#ifndef _SUDOKUACTION_H_
#define _SUDOKUACTION_H_

#include "ai_search.h"

namespace example {
  namespace Sudoku {

    class Action : public ai::Search::Action {
    public:
    
      Action( const int row, const int col, const int value );
      virtual ~Action( );
      virtual void Display() const;
      
      int getRow( ) const;
      int getColumn( ) const;
      int getValue( ) const;
      
    protected:
      int mRow;
      int mCol;
      int mValue;
      
    private:
      
    };

  }
}

#endif /* _SUDOKUACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
