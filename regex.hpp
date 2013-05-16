#ifndef REGEX_HPP
#define REGEX_HPP

#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
using std::string;

struct State;

class Regex {
	/* Supported operators:
		. (concat)
	*/
	public:
		/* Empty Constructor matches "" regex */
		Regex();
		Regex( string patern );
		virtual ~Regex();

		bool match( string test_string );
		//int find_first( string test_string );
		//std::list<string> find_all( string test_string );
		string regex_expand( string patern );
		string regex_to_postfix( string patern );
		string toString();
	private:
		State* start;		
};

union Chain {
	Chain* next;
	State* s;
	static Chain* append( Chain* l1, Chain* l2 );
	static void patch( Chain* l, State* s );
};

enum { Match = 256, Split = 257 };

struct State {
	int c;
	State *out;
	State *out1;
	int lastlist;
	State(int val);
	State(int val, State* o);
	State(int val, State* o, State* o1);
	static std::list<State*> step(int c, std::list<State*> current_list);
	static void addstate( std::list<State*>* list, State* s );
	string toString();
};

struct Fragment {
	State* state;
	Chain* chain;
	Fragment() {
		state = NULL;
		chain = NULL;
	}
	Fragment( State* st, Chain* ch ) {
		state = st;
		chain = ch;
	}
	static Chain* single_list( State** outp ) {
		Chain* c;
		c = (Chain*)outp;
		c->next = NULL;
		return c;
	}
};

#endif
