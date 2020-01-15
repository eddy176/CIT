#ifndef _AISAMPLERANDOM_H_
#define _AISAMPLERANDOM_H_
#include <ai_abalone.h>
namespace ai
{
  namespace SampleAbalone
  {
    class Random : public ai::Agent::AgentProgram
    {
    public:
      Random(ai::Agent::Options *opts);
      ~Random();
      virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
    protected:
    private:
    };
  }
}
#endif /* _AISAMPLERANDOM_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
