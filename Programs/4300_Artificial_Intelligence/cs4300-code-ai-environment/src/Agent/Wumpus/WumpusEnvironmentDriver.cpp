#include <ai_wumpus.h>
#include <unistd.h>

namespace ai
{
  namespace Wumpus
  {
    static struct ai::Agent::Option options[] =
      {
        {"height",           'h', "4", "World height"},
        {"width",            'w', "4", "World width"},
        {"max-height",       'i', "0", "Max world height (if > height) choose randomly"},
        {"max-width",        'x', "0", "Max world width (if > width) choose randomly"},
        {"pit-probability",  'P', "0.2", "Probability of a pit in each cell"},
        {"nirvana",          'n', "0", "Nirvana mode"},
        {"drwho",            'W', "0", "Dr. Who mode"},
        {"", 0, "", ""}
      };

    EnvironmentDriver::EnvironmentDriver(int argc, char **argv, bool init_options)
      : ai::Agent::EnvironmentDriver(argc, argv, false)
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
      InitSockets(1, mOptions.GetArgInt("displays"));

      int total_performance    = 0;
      int number_of_deaths     = 0;
      int number_of_gold_finds = 0;
      std::string agent_name = "Unknown";
      int runs = mOptions.GetArgInt("runs");
      for(int r = 0; r < runs; r++)
        {
          int w0 = mOptions.GetArgInt("width");
          int w1 = mOptions.GetArgInt("max-width");
          int h0 = mOptions.GetArgInt("height");
          int h1 = mOptions.GetArgInt("max-height");
          int w = w0;
          int h = h0;
          if(w1 > w0) {
            w = w0 + static_cast<int>(mRandomNumber.Rand() * (w1-w0+1));
            if(w > w1) {
              w = w1;
            }
          }
          if(h1 > h0) {
            h = h0 + static_cast<int>(mRandomNumber.Rand() * (h1-h0+1));
            if(h > h1) {
              h = h1;
            }
          }
          if((r % 1) == 0) { std::cerr << "Run number " << r << " w,h " << w << "," << h << " pp " << mOptions.GetArgFlt("pit-probability") << std::endl; }
          Environment *env   = new Environment(mRandomNumber,
                                               w,
                                               h,
                                               mOptions.GetArgFlt("pit-probability"),
                                               mOptions.GetArgInt("nirvana"),
                                               mOptions.GetArgInt("drwho"),
                                               &mDisplaySockets);

          Agent *agent = new Agent(mAgentSockets[0]);
          if(mOptions.GetArgInt("trace"))
            {
              agent->Trace();
            }
          else
            {
              agent->NoTrace();
            }
          env->AddAgent(agent);
          env->SetDelay(mOptions.GetArgInt("delay"));
          env->Run(mOptions.GetArgInt("steps"));

          int performance = env->GetPerformance(agent);
          agent_name = agent->GetName();
          std::cerr << "Performance: " << performance << std::endl;
          total_performance += performance;
          if(performance < -200)
            {
              number_of_deaths ++;
            }
          else if(performance > 100)
            {
              number_of_gold_finds ++;
            }
          mRandomNumber = env->GetRandomNumber();
          sleep(mOptions.GetArgInt("sleep"));
          delete env;
        }

      std::cout << agent_name << ": Games "
                << runs << " Deaths "
                << number_of_deaths << " Golds "
                << number_of_gold_finds << " Performance "
                << (total_performance/runs)
                << std::endl;
    }
  }
}
