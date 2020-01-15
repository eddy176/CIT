#include <ai_scavenger.h>
#include <iomanip>

namespace ai
{
  namespace Scavenger
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
      int display = mOptions.GetArgInt("display");
      if(display == 0)
        {
          mEnvironmentDisplay = new EnvironmentDisplay(env, width, height);
        }
      else
        {
#if USE_GLUT
          mEnvironmentDisplay = new EnvironmentDisplay3D(env, width, height);
#else
#endif
        }
      mEnvironmentDisplaySet = true;
    }

  }
}
