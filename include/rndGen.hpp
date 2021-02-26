/* file: rndGen.hpp */

#ifndef __RND_GEN_HPP_INCLUDED__
#define __RND_GEN_HPP_INCLUDED__

#include <random>

class RndGen {
	public:
		RndGen(int, int);
		int getNum();
	private:
		int min;
		int max;
		std::random_device rd; 
};

#endif
