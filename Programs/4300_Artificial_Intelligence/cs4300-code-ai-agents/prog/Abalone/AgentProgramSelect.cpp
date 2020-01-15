
#include <ai_agent.h>

#include "RandomPick.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 'r':
          agent_program = new ai::Sample::RandomPick();
          break;

        default:
          std::cout << "Unknown agent program " << opts->GetArgChr("agent") << std::endl
                    << "r : RandomPick" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
