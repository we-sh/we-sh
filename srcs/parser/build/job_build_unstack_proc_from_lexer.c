#include "parser.h"

/*
** Unstack processus from the stack of tokens.
*/

int		ast_unstack_proc_from_lexer(t_proc *p, t_lexer *lexer, int *i)
{
	int		st;

	while (*i < lexer->size)
	{
		log_debug("unstacking token : %d / %d : \"%s\"", *i, lexer->size, lexer->tokens[*i].content);

		if (lexer->tokens[*i].code == TC_NONE && *i + 1 < lexer->size && lexer->tokens[*i + 1].type == TT_REDIR)
			st = lexer->tokens[(*i) + 1].parse(p, lexer, i);
		else // TC_* standard (... ls ...)
			st = lexer->tokens[*i].parse(p, lexer, i);
		if (lexer->tokens[*i].type == TT_JOBS || lexer->tokens[*i].code == TC_PIPE)
			break ;
		if (st != ST_OK)
		{
			log_error("error on token parsing");
			return (st);
		}
		(*i)++;
	}
	return (ST_OK);
}
