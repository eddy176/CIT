#include <ai_wumpus.h>

int main(int argc, char **argv)
{
  ai::Wumpus::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
