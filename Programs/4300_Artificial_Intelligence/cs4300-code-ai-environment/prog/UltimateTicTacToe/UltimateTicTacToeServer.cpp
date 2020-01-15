#include <ai_ultimatetictactoe.h>

int main(int argc, char **argv)
{
  ai::UltimateTicTacToe::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
