#ifndef _OBSTACLELOCATION_H_
#define _OBSTACLELOCATION_H_

namespace ai
{
  namespace Agent
  {
    class ObstacleLocation : public Location
    {
    public:
      double GetX() const;
      double GetY() const;
      void Set(double x_in, double y_in);
    protected:
      double x;
      double y;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Location>(*this);
	ar & x;
	ar & y;
      }
    };
  }
}

#endif /* _OBSTACLELOCATION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
