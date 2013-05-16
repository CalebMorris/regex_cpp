#include "regex.hpp"

string metacharacters = "|*+?.";

State matchstate( Match );


Regex::Regex() {
	
}

Regex::Regex( string patern ) {
	// Change to postfix
	string tmp = regex_expand(patern);
	//std::cout << "tmp:" << tmp << std::endl;
	string postfix = regex_to_postfix(tmp);
	if( postfix != "" ) {
	//std::cout << "post:" << postfix << std::endl;
	std::list<Fragment> state_stack;
	Fragment e1, e2;
	State* s;
	for ( string::iterator it = postfix.begin();
		  it!=postfix.end(); ++it) {
		switch(*it) {
			default:
				if( *it == '\\') {
					++it;
				}
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
				state_stack.push_back(Fragment(s, Chain::append(e1.chain, Fragment::single_list(&s->out1))));
				break;
			case '*':
				e1 = *(state_stack.rbegin()); state_stack.pop_back();
				s = new State(Split, e1.state);
				Chain::patch(e1.chain, s);
				state_stack.push_back(Fragment(s,Fragment::single_list(&s->out1)));
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
	else {
		start = NULL;
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
	for ( string::iterator i = test_string.begin(); 
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
	if( patern == "" ) {
		return "";
	}
	for ( string::iterator it = patern.begin();
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
					return "";
				if(chunk == 0) //Nothing in between parens
					return "";
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
				if( chunk == 0 ) {
					return "";
				}
				result.push_back(*it); //std::cout << "\t" << *it << std::endl;
				break;
			case '|':
				if( (it+1) == patern.end() ) {
					return "";
				}
				if( chunk == 0 ) {
					return "";
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
				if( *it == '\\' ) {
					++it;
					if( it == patern.end() ) {
						return "";
					}
					if( find(metacharacters.begin(),metacharacters.end(),*it) != metacharacters.end() ) {
						//Escape a metacharacter
						result.push_back('\\');
					}
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

string Regex::regex_expand( string patern ) {
	string::iterator beg;
	string::iterator end;
	string::iterator ranger;
	string replacement_string;
	string result = patern;
	string element;
	int element_size;
	int a, b;
	if( *(result.rbegin()) == '\\' ) {
		return "";
	}
	beg = find(result.begin(), result.end(), '[');
	end = find(result.begin(), result.end(), ']');
	while( *(beg-1) == '\\' ) {
		beg = find(beg+1, result.end(), '[');
	}
	while( *(end-1) == '\\' ) {
		end = find(end+1, result.end(), ']');
	}
	while( beg != result.end() ) {
		if( beg == end ) break;
		if( end < beg ) {
			return "";
		}
		ranger = find(beg,end,'-');
		if( ranger != end ) {
			// Range
			int lower = *(ranger-1);
			int upper = *(ranger+1);
			if( lower > upper ) {
				return "";
			}
			replacement_string = "";
			for (int i = lower; i < upper; ++i) {
				replacement_string.push_back((char)i);
			}
			result.replace(ranger-1,ranger+1,replacement_string);
		}
		else {
			replacement_string = "(";
			for ( string::iterator i = beg+1; 
				  i != (end-1); ++i) {
				replacement_string.push_back(*i);
				replacement_string.push_back('|');
			}
			replacement_string.push_back(*(end-1));
			replacement_string.push_back(')');
			result.replace(beg,end+1,replacement_string);
			//std::cout << "result:" << result << std::endl;
			//std::cout << "replace:" << replacement_string << std::endl;
			//std::cout << "beg:" << *beg << std::endl;
			//std::cout << "end:" << *end << std::endl;
		}
		beg = find(result.begin(), result.end(), '[');
		end = find(result.begin(), result.end(), ']');
		while( *(beg-1) == '\\' ) {
			beg = find(beg+1, result.end(), '[');
		}
		while( *(end-1) == '\\' ) {
			end = find(end+1, result.end(), '[');
		}
	}

	beg = find(result.begin(), result.end(), '{');
	end = find(result.begin(), result.end(), '}');
	while( *(beg-1) == '\\' ) {
		beg = find(beg+1, result.end(), '{');
	}
	while( *(end-1) == '\\' ) {
		end = find(end+1, result.end(), '}');
	}
	while( beg != result.end() ) {
		if( beg == end ) break;
		if( end < beg || beg == result.begin() ) {
			return "";
		}
		ranger = find( beg, end, ',' );
		//TODO
		if( *(beg-1) == ')' ) {
			//element = 
		}
		else if( *(beg-2) == '\\' ) {
			//Need to do a multiple of that espace, not of just the element
			element = "";
			element.push_back(*(beg-2));
			element.push_back(*(beg-1));
			element_size = 2;
		}
		else {
			element = *(beg-1);
			element_size = 1;
		}
		//TODO parse the integers
		if( ranger != end ) {
			//std::cout << string(beg+1,ranger) << std::endl;
			//std::cout << string(ranger+1,end) << std::endl;
			std::istringstream sa(string(beg+1,ranger));
			std::istringstream sb(string(ranger+1,end));
			sa >> a;
			sb >> b;
			if( a<0) {
				return "";
			}
			replacement_string = "(";
			if( *(ranger+1) == '}' ) {
				//{a,}
				for (int j = 0; j < a; ++j) {
					replacement_string.append(element);
				}
				replacement_string.push_back('+');
			}
			else {
				//{a,b}
				if( b<a ) {
					return "";
				}
				for (int i = a; i < b; ++i) {
					for (int j = 0; j < i; ++j) {
						replacement_string.append(element);
					}
					replacement_string.push_back('|');
				}
				for (int j = 0; j < b; ++j) {
					replacement_string.append(element);
				}
			}
		}
		else {
			//std::cout << string(beg+1,end) << std::endl;
			std::istringstream sa(string(beg+1,end));
			sa >> a;
			if( a<0 ) {
				return "";
			}
			replacement_string = "(";

			//{a}
			for (int j = 0; j < a; ++j) {
				replacement_string.append(element);
			}
		}
		replacement_string.push_back(')');
		result.replace(beg-element_size,end+1,replacement_string);
		//std::cout << "result:" << result << std::endl;
		//std::cout << "replace:" << replacement_string << std::endl;
		//std::cout << "beg:" << *beg << std::endl;
		//std::cout << "end:" << *end << std::endl;

		beg = find(result.begin(), result.end(), '{');
		end = find(result.begin(), result.end(), '}');
		while( *(beg-1) == '\\' ) {
			beg = find(beg+1, result.end(), '{');
		}
		while( *(end-1) == '\\' ) {
			end = find(end+1, result.end(), '}');
		}
	}
	return result;
}

string Regex::toString() {
	return start->toString();
}

Chain* Chain::append( Chain* l1, Chain* l2 ) {
	Chain* old1l;
	old1l = l1;
	while(l1->next) {
		l1 = l1->next;
	}
	l1->next = l2;
	return old1l;
}
void Chain::patch( Chain* l, State* s ) {
	Chain* next;
	for (; l; l = next) {
		next = l->next;
		l->s = s;
	}
}

State::State(int val) {
	c = val; 
	out = NULL;
	out1 = NULL;
}

State::State(int val, State* o) {
	c = val;
	out = o;
	out1 = NULL;
}

State::State(int val, State* o, State* o1) {
	c = val;
	out = o;
	out1 = o1;
}

std::list<State*> State::step(int c, std::list<State*> current_list) {
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

void State::addstate( std::list<State*>* list, State* s ) {
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

string State::toString() {
	std::list<State*> queue;
	string result = "";
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