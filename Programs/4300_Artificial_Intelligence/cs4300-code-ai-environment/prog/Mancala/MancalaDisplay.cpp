#include <ai_mancala.h>

int main(int argc, char **argv)
{
  ai::Mancala::DisplayDriver d(argc, argv);
  ai::Mancala::Environment *env = new ai::Mancala::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
