#include <ai_candy.h>
#include <fstream>
#include <iomanip>
#include <unistd.h>

namespace ai
{
  namespace Candy
  {
    static struct ai::Agent::Option options[] =
      {
        /*
          {"filename",         'f', "scav_world.txt", "World filename"},
          {"tourney",          'T', "0",              "Enable/disable tournament mode"},
          {"fully_observable", 'O', "0", "Make the world fully observable"},
        */
        {"envtype",          'e', "5",              "Environment type (5-discrete 5; 0-uniform; 2-mixed-bag)"},
        {"samples",          'm', "1000",           "Number of samples to be given."},
        {"", 0, "", ""}
      };

    EnvironmentDriver::EnvironmentDriver(int argc, char **argv, bool init_options) :
      ai::Agent::EnvironmentDriver(argc, argv, false)
    {
      this->mOptions.AddOptions(options);
      if(init_options)
        {
          this->mOptions.Initialize(argc, argv);
          this->InitRand();
        }
    }

    void EnvironmentDriver::Run()
    {
      int num_agents = this->mOptions.GetArgInt("agents");
      this->InitSockets(num_agents, this->mOptions.GetArgInt("displays"));

      int runs = this->mOptions.GetArgInt("runs");
      int number_of_samples = this->mOptions.GetArgInt("samples");
      int envtype = Environment::DISCRETE5;
      switch(this->mOptions.GetArgInt("envtype"))
        {
        case 5:
          envtype = Environment::DISCRETE5;
          break;
        case 0:
          envtype = Environment::UNIFORM;
          break;
        case 2:
          envtype = Environment::MIXED_BAG;
          break;
        default:
          break;
        }
      for(int r = 0; r < runs; r++)
        {
          Environment *env = new Environment(this->mRandomNumber, &this->mDisplaySockets, envtype);
          if(envtype == Environment::MIXED_BAG)
            {
              env->SetNumberOfSamples(number_of_samples);
            }
          int i;
          for(i = 0; i < num_agents; i++)
            {
              Agent *agent = new Agent(this->mAgentSockets[i]);
              if(this->mOptions.GetArgInt("trace"))
                {
                  agent->Trace();
                }
              else
                {
                  agent->NoTrace();
                }
              env->AddAgent(agent, 0);
            }

          env->SetDelay(this->mOptions.GetArgInt("delay"));
          env->Run(this->mOptions.GetArgInt("steps"));

          for(i = 0; i < num_agents; i++)
            {
              Agent *agent = dynamic_cast<Agent *>(env->GetAgent(i));

              if(env->GetEnvironmentType() == Environment::MIXED_BAG)
                {
                  std::cout << agent->GetName() << ": "
                            << " TotalError: " << agent->GetTotalError()
                            << " SmallestError: " << agent->GetSmallestError()
                            << " NumberOfPredictions: " << agent->GetNumberOfPredictions()
                            << " PerformanceMeasure: " << agent->GetPerformance();


                  unsigned int i,j;
                  std::cout << " ( ";
                  for(i = 0; i < 2; i++)
                    {
                      std::cout << " { bag: ";
                      std::cout << env->GetBagProbability(i);
                      std::cout << " [ flavor: ";
                      for(j = 0; j < 2; j++)

                        {
                          std::cout << env->GetBagFlavorProbability(i,j) << " ";
                        }
                      std::cout << " ]";
                      std::cout << " [ wrapper: ";
                      for(j = 0; j < 2; j++)
                        {
                          std::cout << env->GetBagWrapperProbability(i,j) << " ";
                        }
                      std::cout << " ]";
                      std::cout << " [ hole: ";
                      for(j = 0; j < 2; j++)
                        {
                          std::cout << env->GetBagHoleProbability(i,j) << " ";
                        }
                      std::cout << " ]";
                      std::cout << " }";
                    }
                  std::cout << " )";
                }
              else
                {
                  std::cout << agent->GetName() << ": "
                            << " TotalError: " << agent->GetTotalError()
                            << " SmallestError: " << agent->GetSmallestError()
                            << " NumberOfPredictions: " << agent->GetNumberOfPredictions()
                            << " PerformanceMeasure: " << agent->GetPerformance();

                  int j;
                  for(j = 0; j < env->GetNumberOfFlavors(); j++)
                    {
                      std::cout << " F" << j << ": " << env->GetFlavorProbability(j);
                    }
                }
              std::cout << std::endl;
            }

          this->mRandomNumber = env->GetRandomNumber();
          sleep(this->mOptions.GetArgInt("sleep"));
          delete env;
        }
    }
  }
}
