#ifndef _CANDYAGENT_H_
#define _CANDYAGENT_H_

namespace ai
{
  namespace Candy
  {
    class Agent: public ai::Agent::Agent
    {
    public:
      Agent();
      Agent(ai::Agent::Socket *sock_in);

      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);
      virtual ai::Agent::Action * MessageToAction(const ai::Agent::Message &imsg) const;
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);

      bool Predict (const int &flavor_prediction, const double &probability_prediction);
      bool PredictMixedBag (const Action * const action);
      bool Quit ( );
      bool Noop ( );

      double GetTotalError() const;
      double GetSmallestError() const;
      int    GetNumberOfPredictions() const;

    protected:
      double total_error;
      double smallest_error;
      int    number_of_predictions;

    private:
    };
  }
}

#endif /* _CANDYAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
