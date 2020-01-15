#ifndef _SUDOKUSOLVER_H_
#define _SUDOKUSOLVER_H_

#include <exception>
#include <iostream>

namespace example {
  namespace Sudoku {

    class Exception: public std::exception {
    public:
      Exception( const std::string& msg );
      virtual const char* what() const throw();
    protected:
      std::string mMsg;
    };


    void process_input_stream( std::istream& is );
  }
}

#endif /* _SUDOKUSOLVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
