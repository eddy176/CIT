#include <ai_ultimatetictactoe.h>
#include <iomanip>

namespace ai
{
  namespace UltimateTicTacToe
  {
    static struct ai::Agent::Option options[] =
      {
        {"", 0, "", ""}
      };

    DisplayDriver::DisplayDriver(int argc, char **argv)
      : ai::Agent::DisplayDriver(argc, argv)
    {
      mOptions.AddOptions(options);
    }

    void DisplayDriver::SetEnvironmentDisplay(ai::Agent::Environment * env)
    {
      int width  = mOptions.GetArgInt("width");
      int height = mOptions.GetArgInt("height");
      mEnvironmentDisplay = new EnvironmentDisplay(env, width, height);
      mEnvironmentDisplaySet = true;
    }

  }
}
