#ifndef _RECTANGLECOMMAND_H_
#define _RECTANGLECOMMAND_H_

#include <string>

namespace ai {
  namespace rectangle {

    // forward declaration of AppData
    struct AppData;
    typedef int (*ActionFunctionType)( AppData& data );
    struct ActionRecord {
    public:
      ActionFunctionType action;  // the function
      std::string        name;    // the keyword
      std::string        usage;   // usage message
      std::string        help;    // help message
    };

    enum ExitStatus { EXIT_OK, EXIT_USAGE, EXIT_HELP, EXIT_USAGE_HELP, EXIT_EXIT, EXIT_THROW };

    /* RectangleSearch.cpp */
    int search( AppData& data );

  }
}


#endif /* _RECTANGLECOMMAND_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
