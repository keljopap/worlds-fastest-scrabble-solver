#include <string>

#define M 32

using namespace std;

/*  This class is meant to implement the theory and research presented around the
 *  Directed Acyclic Word Graph, (watch here:  "https://www.youtube.com/watch?v=TJ8SkcUSdbU")
 *  which is a rarely compiled, static representation of the entire Scrabble dictionary
 *  based on combining common prefixes, dipthongs, suffixes, etc. into the smallest possible
 *  data structure.  It essentially is an array of alphabetic mappings - all of the A words
 *  will be shown in the first section, which varying levels of depth marked by bits
 *  indicating which letter is the last child in that "generation"
 *           i.e.  [C(0)][A(1)]...[*(2)]...[R(2)] would be directly followed by:
 					[B(3)][D(3)][E(3)][P(3)][S(3)][T(3)&]
 * 					CARB, CARD, CARE, CARP, CARS, CART
 */

class DawgBuilder {
	
	public:
		bitset<M> dawg;

}