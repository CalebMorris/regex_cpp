#ifndef REGEX_HPP
#define REGEX_HPP

#include <list>
#include <string>
#include <iostream>
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
		string regex_to_postfix( string patern ); //TODO 
		string toString();
	private:
		State* start;		
};

union Chain {
	Chain* next;
	State* s;
	static Chain* append( Chain* l1, Chain* l2 ) {
		Chain* old1l;
		old1l = l1;
		while(l1->next) {
			l1 = l1->next;
		}
		l1->next = l2;
		return old1l;
	}
	static void patch( Chain* l, State* s ) {
		Chain* next;
		for (; l; l = next) {
			next = l->next;
			l->s = s;
		}
	}
};

enum { Match = 256, Split = 257 };

struct State {
	int c;
	State *out;
	State *out1;
	int lastlist;
	State(int val) {
		c = val; 
		out = NULL;
		out1 = NULL;
	}
	State(int val, State* o) {
		c = val;
		out = o;
		out1 = NULL;
	}
	State(int val, State* o, State* o1) {
		c = val;
		out = o;
		out1 = o1;
	}
	static std::list<State*> step(int c, std::list<State*> current_list) {
		State* s;
		std::list<State*> next_list;
		//std::cout << "Checking " << (char)c << std::endl;
		for ( std::list<State*>::iterator i = current_list.begin(); 
			  i != current_list.end(); ++i)
		{
			s = *i;
			//std::cout << "comparing " << s->c << " to " << c << std::endl;
			if( s->c == c ) {
				addstate(&next_list, s->out);
				//std::cout << c << " matches." <<std::endl;
			}
		}
		return next_list;
	}
	static void addstate( std::list<State*>* list, State* s ) {
		if( s == NULL ) {
			return;
		}
		if( s->c == Split ) {
			addstate(list, s->out);
			addstate(list, s->out1);
			return;
		}
		list->push_back(s);
	}
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
