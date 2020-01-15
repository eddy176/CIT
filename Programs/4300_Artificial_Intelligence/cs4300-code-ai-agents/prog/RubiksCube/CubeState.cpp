#include "CubeState.h"
#include <iostream>
#include <sstream>

// UPDATED

namespace ai
{
namespace rubiks

{

State::State(){
    
}

State::State(const Cube &model)
    : mModel(model)
{
}

State::State(const State &rhs)
{
    *this = rhs;
}

State::~State()
{
}

void State::Display() const {
  mModel.oneWordDisplay(std::cout);
  std::cout << std::endl;
}

bool State::IsEqual(const ai::Search::State *const state_in) const
{
    const State *const state = dynamic_cast<const State *const>(state_in);
    return mModel == state->mModel;
}

bool State::IsLessThan(const ai::Search::State *const state_in) const
{
    const State *const state = dynamic_cast<const State *const>(state_in);
    return mModel < state->mModel;
}

bool State::operator==(const State &rhs) const
{
    return this->IsEqual(&rhs);
}

State &State::operator=(const State &rhs)
{
    mModel = rhs.mModel;
    return *this;
}

const Cube &State::getModel() const
{
    return mModel;
}

Cube &State::getModel()
{
    return mModel;
}

} // namespace rubiks

} // namespace ai

std::ostream &operator<<(std::ostream &os, const ai::rubiks ::State &state)
{
    state.getModel().oneWordDisplay(std::cout);
    return os;
}
