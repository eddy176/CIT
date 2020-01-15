#include <ai_scavenger.h>

int main(int argc, char **argv)
{
  ai::Scavenger::DisplayDriver d(argc, argv);
  ai::Scavenger::Environment *env = new ai::Scavenger::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
