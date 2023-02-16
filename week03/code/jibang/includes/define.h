#ifndef DEFINE_H
# define DEFINE_H

# define ERROR		-1
# define NODISPLAY	0
# define DISPLAY 	1
# define READ_END	0
# define WRITE_END	1
# define TRUE		1
# define SUCCESS	1
# define FALSE		0

enum	e_token_type
{
	NONE,
	OR,
	AND,
	PIPE,
	CMD,
	OPTION,
	D_QUOTE,
	S_QUOTE,
	INP_RDIR,
	OUT_RDIR,
	APP_RDIR,
	HERE_DOC,
	PARENS,
};

enum	e_node_type
{
	TN_NONE,
	TN_OR,
	TN_AND,
	TN_PIPE,
	TN_WORD,
	TN_PARENS,
};

#endif