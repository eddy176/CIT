#ifndef _CUBESTATE_H_
#define _CUBESTATE_H_

#include "CubeModel.h"
#include "ai_search.h"

// UPDATED

namespace ai
{
namespace rubiks
{
class State : public ai::Search::State
{
public:
    State();
    State(const Cube &model);
    State(const State &rhs);

    void Display() const;

    virtual ~State();
    virtual bool IsEqual(const ai::Search::State *const state_in) const;
    virtual bool IsLessThan(const ai::Search::State *const state_in) const;

    bool operator==(const State &rhs) const;
    State &operator=(const State &rhs);

    const Cube &getModel() const;
    Cube &getModel();

protected:
    Cube mModel;
private:
};

} // namespace rubiks
} // namespace ai

std::ostream &operator<<(std::ostream &os, const ai::rubiks::State &state);

#endif /* _CUBESTATE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
