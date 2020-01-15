#include <ai_tictactoe.h>

int main(int argc, char **argv)
{
  ai::TicTacToe::EnvironmentDriver d(argc, argv);
  d.Run();
  return 0;
}
