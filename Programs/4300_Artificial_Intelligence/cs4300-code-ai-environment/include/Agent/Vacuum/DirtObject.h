#ifndef _DIRTOBJECT_H_
#define _DIRTOBJECT_H_

namespace ai
{
  namespace Agent
  {
    class DirtObject : public XYObject
    {
    public:
      DirtObject();
      virtual Percept *GetPercept(const Location *location);
    protected:
    private:
    };
  }
}

#endif /* _DIRTOBJECT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
