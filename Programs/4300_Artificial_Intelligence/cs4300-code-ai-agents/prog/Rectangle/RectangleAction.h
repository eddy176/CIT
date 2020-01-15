#ifndef _RECTANGLEACTION_H_
#define _RECTANGLEACTION_H_

#include "ai_search.h"
#include "RectangleModel.h"

namespace ai {
  namespace rectangle {

    class Action : public ai::Search::Action {
    public:

      Action( const Move& move );
      virtual ~Action( );
      virtual void Display( ) const;
      
      const Move& getMove( ) const;
      
    protected:
      Move mMove;
      
    private:
      
    };

  }
}

std::ostream& operator<<( std::ostream& os, const ai::rectangle::Action& action );



#endif /* _RECTANGLEACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
