#ifndef _CUBEACTION_H_
#define _CUBEACTION_H_

// UPDATED

#include "ai_search.h"
#include "CubeModel.h"

namespace ai
{
namespace rubiks
{

class Action : public ai::Search::Action
{
public:
    Action();
    Action(const Move &move);
    virtual ~Action();
    virtual void Display() const;

    const Move &getMove() const;

protected:
    Move mMove;
    };

} // namespace rubiks
} // namespace ai

std::ostream &operator<<(std::ostream &os, const ai::rubiks::Action &action);

#endif /* _CUBEACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
