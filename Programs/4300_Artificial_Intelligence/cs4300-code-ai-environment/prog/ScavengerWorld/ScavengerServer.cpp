#include <ai_scavenger.h>

int main(int argc, char **argv)
{
  ai::Scavenger::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
