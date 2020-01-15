#include "SudokuAction.h"
#include <iostream>

namespace example {
  namespace Sudoku {

    Action::Action( const int row, const int col, const int value )
      : mRow( row ), mCol( col ), mValue( value ) {
    }
    
    Action::~Action( ) {
    }
    
    void Action::Display() const {
      std::cout << mRow << "," << mCol << ":" << mValue << std::endl;
    }
      
    int Action::getRow( ) const {
      return mRow;
    }

    int Action::getColumn( ) const {
      return mCol;
    }

    int Action::getValue( ) const {
      return mValue;
    }
    
  }
}
