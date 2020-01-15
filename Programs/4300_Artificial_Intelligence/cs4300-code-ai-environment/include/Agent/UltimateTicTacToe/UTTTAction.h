#ifndef _UTTTACTION_H_
#define _UTTTACTION_H_
namespace ai
{
  namespace UltimateTicTacToe
  {
    class Action : public ai::Agent::Action
    {
    public:
      enum ActionEnum { MOVE = 1, QUIT = 2 };
      virtual bool TextDisplay(std::ostream & os) const;
      virtual bool ToMessage(ai::Agent::Message &omsg) const;
      virtual bool FromMessage(const ai::Agent::Message &imsg);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(const std::string &keyprefix, ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg);

      /*
       * Set the move coordinates
       */
      bool SetMove(const MoveData &move_in);

      /*
       * Retrieve the move coordinates
       */
      const MoveData &GetMove() const;

    protected:
      MoveData move;

    private:
    };
  }
}
#endif /* _UTTTACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
