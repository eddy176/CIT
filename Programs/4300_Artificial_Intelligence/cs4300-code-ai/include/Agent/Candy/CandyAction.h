#ifndef _CANDYACTION_H_
#define _CANDYACTION_H_

namespace ai
{
  namespace Candy
  {
    class Action : public ai::Agent::Action
    {
    public:
      Action();
      virtual ~Action();

      virtual bool TextDisplay(std::ostream &os) const;
      virtual bool ToMessage(ai::Agent::Message &omsg) const;
      virtual bool FromMessage(const ai::Agent::Message &imsg);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(const std::string &keyprefix, ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg);

      double GetProbabilityPrediction (  ) const;
      bool SetProbabilityPrediction ( const double & probability_prediction_in );

      int GetFlavorPrediction ( ) const;
      bool SetFlavorPrediction ( const int & flavor_prediction_in );

      std::vector<double> GetBagProbabilities ( ) const;
      std::vector< std::vector<double> > GetBagFlavorProbabilities ( ) const;
      std::vector< std::vector<double> > GetBagWrapperProbabilities ( ) const;
      std::vector< std::vector<double> > GetBagHoleProbabilities ( ) const;

      bool SetBagProbabilities ( const std::vector<double> &p_in );
      bool SetBagFlavorProbabilities ( const std::vector< std::vector<double> > &p_in );
      bool SetBagWrapperProbabilities ( const std::vector< std::vector<double> > &p_in );
      bool SetBagHoleProbabilities ( const std::vector< std::vector<double> > &p_in );

      enum ActionEnum
        {
          PREDICT,           /* Predict the flavor and probability of next draw */
          PREDICT_MIXED_BAG, /* Predict the flavor, wrapper, hole and mixing probabilities of 2 bag */
          QUIT,              /* Stop playing */
          NOOP               /* Do nothing */
        };

    protected:
      double probability_prediction;
      int    flavor_prediction;

      std::vector<double>                bag_probabilities;         // The probability of each bag.
      std::vector< std::vector<double> > bag_flavor_probabilities;  // The probability of each flavor, for each bag.
      std::vector< std::vector<double> > bag_wrapper_probabilities; // The prob. of each wrapper, for each bag.
      std::vector< std::vector<double> > bag_hole_probabilities;    // The prob. of each hole, for each bag.

    private:
    };
  }
}

#endif /* _CANDYACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
