#ifndef _OBSTACLEACTION_H_
#define _OBSTACLEACTION_H_

namespace ai
{
  namespace Agent
  {
    class ObstacleAction : public Action
    {
    public:
      enum ActionEnum { GO = 1, STOP };
      virtual bool TextDisplay(std::ostream & os) const;

      bool SetDirection(double dir_in);
      bool SetDistance(double dist_in);
      double GetDirection() const;
      double GetDistance() const;
    protected:
      double direction;
      double distance;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Action>(*this);
	ar & direction;
	ar & distance;
      }
    };
  }
}

#endif /* _OBSTACLEACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
