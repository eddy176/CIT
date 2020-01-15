#ifndef _CANDYENVIRONMENT_H_
#define _CANDYENVIRONMENT_H_

namespace ai
{
  namespace Candy
  {
    class Environment: public ai::Agent::Environment
    {
      friend class EnvironmentDisplay;
    public:
      enum EnvironmentEnum
        {
          EE_MIN,
          DISCRETE5, /* 5 possible bag possibilities (2 flavors) */
          UNIFORM,   /* uniform distribution, infinite bag possibilities (2 flavors) */
          MIXED_BAG, /* 2 bags from uniform distribution, mixed (2 flavors) */
          EE_MAX
        };


      Environment();
      Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in,
                  const int &environment_type_in);
      virtual ~Environment();

      virtual bool ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action);
      virtual void CalculatePerformance(ai::Agent::Agent *agent);
      virtual ai::Agent::Percept *GetPercept(ai::Agent::Agent *agent);
      virtual void Step();
      virtual void Run(const int n_steps);
      virtual ai::Agent::Location *DefaultLocation() const;
      /*
       * Handle messages with the client.
       */
      virtual bool GetUpdateMessage(ai::Agent::Message &omsg);
      virtual bool UpdateFromMessage(ai::Agent::Message &imsg);

      int GetEnvironmentType() const;

      int GetCurrentFlavor() const;
      int GetNumberOfFlavors( ) const;
      double GetFlavorProbability( const int &flavor_in ) const;

      bool SetNumberOfSamples( const int &number_of_samples_in );

      double GetBagProbability( const int &bag_in ) const;
      double GetBagFlavorProbability( const int &bag_in, const int &flavor_in ) const;
      double GetBagWrapperProbability( const int &bag_in, const int &wrapper_in ) const;
      double GetBagHoleProbability( const int &bag_in, const int &wrapper_in ) const;

    protected:
      void TextDisplay(std::ostream &os) const;

      bool PredictAgent(Agent *agent, const int &flavor_prediction, const double &probability_prediction);
      bool PredictMixedBagAgent(Agent *agent, const Action * const action);
      bool QuitAgent(Agent *agent);
      bool NoopAgent(Agent *agent);

      bool SetMixedBagSamples();


      int environment_type;
      int time_step;                             // The current time step, starting at 0
      int num_flavors;                           // The number of flavors of candy
      std::vector<double> flavor_probabilities;  // The probability of each flavor, for this world
      std::vector<int> flavor_history;           // The number of times each flavor has been drawn
      int current_flavor;                        // The most recently drawn flavor

      /* MIXED_BAG variables */
      std::vector<double>                bag_probabilities;         // The probability of each bag.
      std::vector< std::vector<double> > bag_flavor_probabilities;  // The probability of each flavor, for each bag.
      std::vector< std::vector<double> > bag_wrapper_probabilities; // The prob. of each wrapper, for each bag.
      std::vector< std::vector<double> > bag_hole_probabilities;    // The prob. of each hole, for each bag.
      int number_of_samples;
      std::vector< std::vector<int> >    samples;                   /* The current sample set.
                                                                     * The internal vectors store the
                                                                     * flavor, wrapper, hole values */
    private:
    };
  }
}


#endif /* _CANDYENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
