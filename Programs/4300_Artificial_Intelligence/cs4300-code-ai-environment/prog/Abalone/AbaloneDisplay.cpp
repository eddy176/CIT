#include <ai_abalone.h>

int main(int argc, char **argv)
{
  ai::Abalone::DisplayDriver d(argc, argv);
  ai::Abalone::Environment *env = new ai::Abalone::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
