#ifndef _XYLOCATION_H_
#define _XYLOCATION_H_

namespace ai
{
  namespace XY
  {
    class Location : public ai::Agent::Location
    {
    public:
      int GetX() const;
      int GetY() const;
      void Set(int x_in, int y_in);
    protected:
      friend class Agent;
      friend class Object;
      int x;
      int y;
    private:
    };
  }
}

#endif /* _XYLOCATION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
