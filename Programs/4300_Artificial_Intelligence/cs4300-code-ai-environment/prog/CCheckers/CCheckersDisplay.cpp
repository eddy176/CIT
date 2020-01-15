#include <ai_ccheckers.h>

int main(int argc, char **argv)
{
  ai::CCheckers::DisplayDriver d(argc, argv);
  ai::CCheckers::Environment *env = new ai::CCheckers::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
