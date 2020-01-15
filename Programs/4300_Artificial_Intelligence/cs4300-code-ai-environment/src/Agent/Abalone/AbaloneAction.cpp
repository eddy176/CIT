#include <ai_abalone.h>
#include <cstdio>

namespace ai {
	namespace Abalone {
	
		bool Action::TextDisplay(std::ostream & os) const {
			std::string str = "";

			switch(GetCode()) {
				case MOVE:
					str = "Move ";
					{
					char c_str[64];
					std::sprintf(c_str, "[%d] {", move.number);
					str += c_str;
					for (unsigned int i = 0; i < move.number; i++) {
						std::sprintf(c_str, "(%2d,%2d)=>(%2d,%2d),", move.from_x[i], move.from_y[i], move.to_x[i], move.to_y[i]);
						str += c_str;
					}
					std::sprintf(c_str, "}");
					str += c_str;
					}
					break;
				case QUIT:
					str = "Quit";
					break;
				default:
					DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
					return false;
			}
		os << str;
		return true;
	}

	bool Action::ToMessage(ai::Agent::Message &omsg) const {
		if(!omsg.SetName(ai::Agent::MESSAGE_ACTION_NAME))
			return false;
		
		ADD_TO_MSG("CODE", action_code, omsg);
		switch(action_code) {
			case MOVE:
        ADD_ARRAY_TO_MSG("MARBLES FROMX", move.from_x, move.number, omsg);
        ADD_ARRAY_TO_MSG("MARBLES FROMY", move.from_y, move.number, omsg);
        ADD_ARRAY_TO_MSG("MARBLES TOX", move.to_x, move.number, omsg);
        ADD_ARRAY_TO_MSG("MARBLES TOY", move.to_y, move.number, omsg);

				break;
			case QUIT:
				// OK, no other data
				break;
			default:
				DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
				return false;
		}

		DBGP_MSG(LOG_STREAM(std::cerr) << "Message: " << omsg << std::endl);
		return true;
	}

	bool Action::FromMessage(const ai::Agent::Message &imsg) {
		if(imsg.GetName() != ai::Agent::MESSAGE_ACTION_NAME)
		return false;

		SET_FROM_MSG("CODE", action_code, imsg);
		switch(action_code) {
			case MOVE:
        SET_ARRAY_FROM_MSG("MARBLES FROMX", move.from_x, move.number, imsg);
        SET_ARRAY_FROM_MSG("MARBLES FROMY", move.from_y, move.number, imsg);
        SET_ARRAY_FROM_MSG("MARBLES TOX", move.to_x, move.number, imsg);
        SET_ARRAY_FROM_MSG("MARBLES TOY", move.to_y, move.number, imsg);

				break;
			case QUIT:
				// OK, no other data
				break;
			default:
				DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
				return false;
		}
		return true;
	}

	bool Action::AddToMessageIfChanged(const std::string &keyprefix, ai::Agent::Message &omsg, ai::Agent::Message &old_msg) {
		DBGP_E(LOG_STREAM(std::cerr) << "Implement this method to remove this error" << std::endl);
		{
		int *x = 0;
		*x = 1;
		}
		return false;
	}

	bool Action::SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg) {
		DBGP_E(LOG_STREAM(std::cerr) << "Implement this method to remove this error" << std::endl);
		{
		int *x = 0;
		*x = 1;
		}
		return false;
	}

	bool Action::SetMove(const MoveData &move_in) {
		move = move_in;
		return true;
	}

	const MoveData &Action::GetMove() const {
		return move;
	}

	}
}
