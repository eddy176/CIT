#pragma once
#include <iostream>

#define ShowMessages 0	// 0 or 1
#include <iostream>
#if ShowMessages
#define MSG(X) std::cout << X << std::endl;
#else
#define MSG(X) ;
#endif

