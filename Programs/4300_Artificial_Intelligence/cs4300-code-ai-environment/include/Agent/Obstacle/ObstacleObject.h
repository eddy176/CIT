#ifndef _OBSTACLEOBJECT_H_
#define _OBSTACLEOBJECT_H_

namespace ai
{
  namespace Agent
  {
    class ObstacleObject : public Object
    {
    public:
      ObstacleObject();
      ObstacleObject(int tn_in, int nn_in,
		     ObstacleLocation *loc_in);
      virtual Percept *GetPercept(const Location *location);
      virtual bool     HeadingDistance(const Location *location,
				       double &heading_out,
				       double &distance_out);
      int GetTriangleNumber() const;
      int GetNodeNumber() const;
    protected:
      int triangle_number;
      int node_number;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Object>(*this);
	ar & triangle_number;
	ar & node_number;
      }
    };
  }
}

#endif /* _OBSTACLEOBJECT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
