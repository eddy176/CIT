
#include <ai_agent.h>

#include "aiSampleManual.h"
#include "aiSampleRandom.h"
#include "JetanAlphaBeta.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 'M':
          agent_program = new ai::Jetan::Manual(opts);
          break;
        case 'r':
          agent_program = new ai::Jetan::Random(opts);
          break;
        case 'K':
          agent_program = new ai::Jetan::AlphaBeta(opts);
          break;

        default:
          std::cout << "Unknown agent program " << opts->GetArgChr("agent") << std::endl
                    << "M : Manual" << std::endl
                    << "r : Random" << std::endl
                    << "K : AlphaBeta" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
