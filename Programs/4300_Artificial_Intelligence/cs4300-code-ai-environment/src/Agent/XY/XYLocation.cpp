#include <ai_xy.h>

namespace ai
{
  namespace XY
  {
    int Location::GetX() const
    {
      return x;
    }

    int Location::GetY() const
    {
      return y;
    }

    void Location::Set(int x_in, int y_in)
    {
      x = x_in;
      y = y_in;
    }

  }
}
