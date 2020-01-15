#include <ai_wumpus.h>

int main(int argc, char **argv)
{
  ai::Wumpus::DisplayDriver d(argc, argv);
  ai::Wumpus::Environment *env = new ai::Wumpus::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
