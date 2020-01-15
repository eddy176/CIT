#include <ai_ccheckers.h>
#include <iomanip>
#include <unistd.h>

namespace ai
{
  namespace CCheckers
  {
    static struct ai::Agent::Option options[] =
      {
        {"tourney", 'T', "0", "Enable/disable tournament mode"},
        {"", 0, "", ""}
      };

    EnvironmentDriver::EnvironmentDriver(int argc, char **argv, bool init_options) : ai::Agent::EnvironmentDriver(argc, argv, false)
    {
      mOptions.AddOptions(options);
      if(init_options)
        {
          mOptions.Initialize(argc, argv);
          InitRand();
        }
    }

    void EnvironmentDriver::Run()
    {
      InitSockets(2, mOptions.GetArgInt("displays"));

      int runs = mOptions.GetArgInt("runs");
      bool tourney = mOptions.GetArgInt("tourney");
      if(tourney)
        runs *= 2;
      for(int r = 0; r < runs; r++)
        {
          Environment *env = new Environment(mRandomNumber, &mDisplaySockets);

          Agent *agent1 = new Agent(mAgentSockets[0]);
          Agent *agent2 = new Agent(mAgentSockets[1]);

          if(mOptions.GetArgInt("trace"))
            {
              agent1->Trace();
              agent2->Trace();
            }
          else
            {
              agent1->NoTrace();
              agent2->NoTrace();
            }

          if(tourney && (r%2))
            {
              env->AddAgent(agent2);
              env->AddAgent(agent1);
            }
          else
            {
              env->AddAgent(agent1);
              env->AddAgent(agent2);
            }

          env->SetDelay(mOptions.GetArgInt("delay"));
          env->Run(mOptions.GetArgInt("steps"));

          BasicBoard final_board(env->GameBoard());
          int winner = final_board.HaveWinner();
          int score  = final_board.Forwardness(1) - final_board.Forwardness(2);
          std::vector<double> times = final_board.GetPlayerTimes();
          bool trapped_1 = false;
          bool trapped_2 = false;
          if(winner == 0 && score < 0)
            {
              trapped_1 = true;
            }
          if(winner == 0 && score > 0)
            {
              trapped_2 = true;
            }

          std::cout << "Agt: " << " " << 1 << " "
                    << "Win: " << (winner == 1) << " "
                    << std::setw(12) << env->GetAgent(0)->GetName() << " "
                    << "Score: " << std::setw(3)  << score << " "
                    << std::setprecision(1) << std::setiosflags(std::ios::fixed)
                    << "Time: " << std::setw(4) << times[0] << " "
                    << "Moves: " << std::setw(3)  << final_board.GetTotalMoves() << " "
                    << "Trap:  " << std::setw(1)  << trapped_1
                    << std::endl;

          std::cout << "Agt: " << " " << 2 << " "
                    << "Win: " << (winner == 2) << " "
                    << std::setw(12) << env->GetAgent(1)->GetName() << " "
                    << "Score: " << std::setw(3)  << -score << " "
                    << std::setprecision(1) << std::setiosflags(std::ios::fixed)
                    << "Time: " << std::setw(4) << times[1] << " "
                    << "Moves: " << std::setw(3)  << final_board.GetTotalMoves() << " "
                    << "Trap:  " << std::setw(1)  << trapped_2
                    << std::endl;

          mRandomNumber = env->GetRandomNumber();
          sleep(mOptions.GetArgInt("sleep"));
          delete env;
        }
    }
  }
}
