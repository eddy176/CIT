#ifndef _CUBEEXCEPTION_H_
#define _CUBEEXCEPTION_H_
#include <exception>
#include <string>

namespace ai {
  namespace rubiks {

    class Exception: public std::exception {
    public:
      Exception( const std::string& msg );
      virtual const char* what() const throw();
    protected:
      std::string mMsg;
    };

  }
}

#endif /* _CUBEEXCEPTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
