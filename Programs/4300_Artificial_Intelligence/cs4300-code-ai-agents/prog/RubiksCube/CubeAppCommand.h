#ifndef _CUBEAPPCOMMAND_H_
#define _CUBEAPPCOMMAND_H_

#include <string>

namespace ai {
  namespace rubiks {

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

  }
}


#endif /* _CUBEAPPCOMMAND_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
