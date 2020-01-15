#ifndef _RECTANGLEAPPDATA_H_
#define _RECTANGLEAPPDATA_H_

#include "RectangleAppConfig.h"
#include "RectangleModel.h"
#include "RectangleCommand.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <exception>

namespace ai {
  namespace rectangle {

    class Exception: public std::exception {
    public:
      Exception( const std::string& msg );
      virtual const char* what() const throw();
    protected:
      std::string mMsg;
    };

    struct AppData {

      AppData( std::istream &is_in, std::ostream &os_in );
      AppConfig config;
      Model model;
      std::istream &is;
      std::ostream &os;

      std::vector< std::string > words;  // for line-by-line processing
      std::map< std::string, ActionRecord > actions;
      bool    done;

    };
  }
}



#endif /* _RECTANGLEAPPDATA_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
