#include <ai_jetan.h>

int main(int argc, char **argv)
{
  ai::Jetan::DisplayDriver d(argc, argv);
  ai::Jetan::Environment *env = new ai::Jetan::Environment();
  d.SetEnvironment(env);
  d.Run();
  return 0;
}
