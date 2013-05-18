Building a regex library to help refresh my view of automata theory, coding and for use in other c++ projects.

Will mainly be in a NFA format and I'm not sure how many modern regex features I will support.

Suported Regex features:
	Concatination
	Pipe 			|
	Star 			*
	Plus 			+
	Question 		?
	Parenthesis 	()
	Grouping 		[]
	GroupingRange	[x-y]
	Multiplier		{x[,[y]]}

Partial support (not finished):
	Escape literals
	Escaped character sets

Planned support
	. matching
	Negation sets [^...]
	Alpha char sets [:...:]
	