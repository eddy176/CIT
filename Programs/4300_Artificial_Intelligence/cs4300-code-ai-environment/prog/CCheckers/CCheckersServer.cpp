#include <ai_ccheckers.h>

int main(int argc, char **argv)
{
  ai::CCheckers::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
