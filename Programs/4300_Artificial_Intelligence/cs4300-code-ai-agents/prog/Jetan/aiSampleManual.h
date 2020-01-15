#ifndef _AISAMPLEMANUAL_H_
#define _AISAMPLEMANUAL_H_
#include <ai_jetan.h>
namespace ai
{
  namespace Jetan
  {
    class Manual : public ai::Agent::AgentProgram
    {
    public:
      Manual(ai::Agent::Options *opts);
      ~Manual();
      virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
    protected:
    private:
    };
  }
}
#endif /* _AISAMPLEMANUAL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
