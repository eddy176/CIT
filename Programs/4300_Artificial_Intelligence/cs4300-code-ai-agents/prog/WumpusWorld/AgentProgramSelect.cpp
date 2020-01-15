
#include <ai_agent.h>

#include "Simpleton.h"
#include "Aristotle.h"
#include "starterGimli.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 'S':
          agent_program = new ai::Sample::Simpleton();
          break;
        case 'A':
          agent_program = new ai::Sample::Aristotle();
          break;
        case 'G':
          agent_program = new starter::Gimli(opts);
          break;

        default:
          std::cout << "Unknown agent program " << opts->GetArgChr("agent") << std::endl
                    << "S : Simpleton" << std::endl
                    << "A : Aristotle" << std::endl
                    << "G : Harbad" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
