#ifndef _ABALONEENVIRONMENTDRIVER_H_
#define _ABALONEENVIRONMENTDRIVER_H_

namespace ai {
	namespace Abalone {
		class EnvironmentDriver : public ai::Agent::EnvironmentDriver {
			public:
				EnvironmentDriver(int argc, char **argv, bool init_options = true);
				virtual void Run();
			protected:
			private:
		};
	}
}

#endif /* _ABALONEENVIRONMENTDRIVER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
