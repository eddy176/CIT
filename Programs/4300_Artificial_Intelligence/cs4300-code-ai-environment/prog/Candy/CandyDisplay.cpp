#include <ai_candy.h>

int main(int argc, char **argv)
{
  ai::Candy::DisplayDriver d(argc, argv);
  ai::Candy::Environment *env = new ai::Candy::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
