#ifndef _RECTANGLESTATE_H_
#define _RECTANGLESTATE_H_

#include "RectangleModel.h"
#include "ai_search.h"

namespace ai {
  namespace rectangle {
    class State : public ai::Search::State {
    public:
      State( const Model& model );
      State( const State& rhs );
      virtual ~State( );
      virtual void Display( ) const;
      virtual bool IsEqual(const ai::Search::State * const state_in) const;
      virtual bool IsLessThan(const ai::Search::State * const state_in) const;

      bool operator==( const State& rhs ) const;
      State& operator=( const State& rhs);

      const Model& getModel( ) const;
      Model& getModel( );
      
    protected:
      Model mModel;
      
    private:
      
    };
    
  }
}

std::ostream& operator<<( std::ostream& os, const ai::rectangle::State& state );

#endif /* _RECTANGLESTATE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
