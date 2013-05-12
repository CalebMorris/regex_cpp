#include "regex.hpp"

State matchstate( Match );

Regex::Regex() {
	
}
Regex::Regex( string patern ) {
	// Change to postfix
	string postfix = regex_to_postfix(patern);
	std::list<Fragment> state_stack;
	Fragment e1, e2;
	State* s;
	for ( std::string::iterator it = postfix.begin();
		  it!=postfix.end(); ++it) {
		switch(*it) {
			default:
				s = new State(*it);
				state_stack.push_back(Fragment(s, Fragment::single_list(&s->out)));
				break;
			case '.':
				e2 = *(state_stack.rbegin()); state_stack.pop_back();
				e1 = *(state_stack.rbegin()); state_stack.pop_back();
				Chain::patch(e1.chain, e2.state);
				state_stack.push_back(Fragment(e1.state, e2.chain));
				break;
			case '|':
				e2 = *(state_stack.rbegin()); state_stack.pop_back();
				e1 = *(state_stack.rbegin()); state_stack.pop_back();
				s = new State(Split, e1.state, e2.state);
				state_stack.push_back(Fragment(s, Chain::append(e1.chain,e2.chain)));
				break;
			case '?':
				e1 = *(state_stack.rbegin()); state_stack.pop_back();
				s = new State(Split, e1.state);
				state_stack.push_back(Fragment(s, Chain::append(e1.chain, Fragment::single_list(&s->out))));
				break;
			case '*':
				e1 = *(state_stack.rbegin()); state_stack.pop_back();
				s = new State(Split, e1.state);
				Chain::patch(e1.chain, s);
				state_stack.push_back(Fragment(s,Fragment::single_list(&s->out)));
				break;
			case '+':
				e1 = *(state_stack.rbegin()); state_stack.pop_back();
				s = new State(Split, e1.state);
				Chain::patch(e1.chain, s);
				state_stack.push_back(Fragment(e1.state, Fragment::single_list(&s->out1)));
				break;
		}
	}
	e1 = *(state_stack.rbegin()); state_stack.pop_back();
	if ( !state_stack.empty() ) {
		std::cout << "Too many states" << std::endl;
		start = NULL;
	}
	else {
		Chain::patch(e1.chain, &matchstate);
		start = e1.state;
	}
}
Regex::~Regex() {}

bool Regex::match( string test_string ) {
	int c;
	std::list<State*> current_list,
					  next_list,
					  t;
	//std::cout << "test_string:" << test_string << std::endl;
	State::addstate(&current_list, start);
	for ( std::string::iterator i = test_string.begin(); 
		  i != test_string.end(); ++i ) {
		c = *i & 0xFF; //Mask to only allow 0-256
		//std::cout << "match it: " << (char)c << std::endl;
		next_list = State::step(c, current_list);
		for ( std::list<State*>::iterator it = next_list.begin(); 
			  it != next_list.end(); ++it ) {
			//std::cout <<"."<< (*it)->toString() << std::endl;
		}
		t = current_list; 
		current_list = next_list;
		next_list = t;
	}

	for ( std::list<State*>::iterator i = current_list.begin(); 
		  i != current_list.end(); ++i ) {
		if( *i == &matchstate ) {
			return true;
		}
	}
	return false;
}

struct paren_chunk{
	int s_chunk;
	int or_chunk;
};

string Regex::regex_to_postfix( string patern ) {
	std::list<char> stack;
	string result = "";
	int chunk = 0, orchunk = 0;
	std::list<paren_chunk> sections;
	struct paren_chunk* p;
	for ( std::string::iterator it = patern.begin();
		  it!=patern.end(); ++it) {
		//std::cout << *it << std::endl;
		switch( *it ) {
			case '(':
				if(chunk > 1){
					--chunk;
					result.push_back('.');
				}
				p = new struct paren_chunk();
				p->s_chunk = chunk;
				p->or_chunk = orchunk;
				sections.push_back(*p);
				chunk = 0;
				orchunk = 0;
				break;
			case ')':
				if(sections.empty())
					return NULL;
				if(chunk == 0) //Nothing in between parens
					return NULL;
				while(--chunk > 0)
					result.push_back('.');
				for(; orchunk > 0; orchunk--)
					result.push_back('|');
				p = &*(sections.rbegin());
				orchunk = p->or_chunk;
				chunk = p->s_chunk;
				chunk++;
				break;
			case '?':
			case '+':
			case '*':
				result.push_back(*it); //std::cout << "\t" << *it << std::endl;
				break;
			case '|':
				if( chunk == 0 ) {
					return NULL;
				}
				while(--chunk > 0) {
					result.push_back('.');
				}
				orchunk++;
				break;
			default:
				/*any character*/
				if(chunk > 1){
					--chunk;
					result.push_back('.');
				}
				result.push_back(*it);
				chunk++;
				break;
		}
	}
	while( --chunk > 0 ) {
		result.push_back('.');
	}
	for(; orchunk > 0; orchunk--) {
		result.push_back('|');
	}
	return result;
}

string Regex::toString() {
	return start->toString();
}

string State::toString() {
	std::list<State*> queue;
	std::string result = "";
	State* current;
	if( out1 ) {
		queue.push_back(out);
		queue.push_back(out1);
	}
	else {
		queue.push_back(this);
	}
	while( !queue.empty() ) {
		current = *(queue.begin());
		queue.pop_front();
		result.push_back((char)current->c);
		result.push_back(' ');
		if( current->out ) {
			queue.push_back(current->out);
		}
		if( current->out1 ) {
			queue.push_back(current->out1);
		}
	}
	
	return result;
}