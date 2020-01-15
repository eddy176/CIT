#include <ai_mancala.h>

int main(int argc, char **argv)
{
  ai::Mancala::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
