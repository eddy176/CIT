#ifndef _VACUUMACTION_H_
#define _VACUUMACTION_H_

namespace ai
{
  namespace Agent
  {
    class VacuumAction : public XYAction
    {
    public:
      enum ActionEnum { SUCK = 1, LEFT, RIGHT, UP, DOWN, EMPTY_BAG, NOOP };
      virtual bool TextDisplay(std::ostream & os) const;
    protected:
    private:
    };
  }
}

#endif /* _VACUUMACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
