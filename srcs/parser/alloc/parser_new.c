#include "parser.h"

/*
** Create a new parser structure and initialize its fields.
** The input string is duplicated and the other are allocated.
*/

static t_token g_token_redir_dless = {
	"<<",
	2,
	TT_REDIR,
	TC_DLESS,
	token_parse_dless
};

static t_token g_token_redir_dgreat = {
	">>",
	2,
	TT_REDIR,
	TC_DGREAT,
	token_parse_dgreat
};

static t_token g_token_jobs_or_if = {
	"||",
	2,
	TT_JOBS,
	TC_OR_IF,
	token_parse_or_if
};

static t_token g_token_jobs_and_if = {
	"&&",
	2,
	TT_JOBS,
	TC_AND_IF,
	token_parse_and_if
};

static t_token g_token_error_dsemi = {
	";;",
	2,
	TT_ERROR,
	TC_DSEMI,
	token_parse_none
};

static t_token g_token_redir_clobber = {
	">|",
	2,
	TT_REDIR,
	TC_CLOBBER,
	token_parse_great
};

static t_token g_token_redir_andgreat = {
	"&>",
	2,
	TT_REDIR,
	TC_ANDGREAT,
	token_parse_andgreat
};

static t_token g_token_redir_greatand = {
	">&",
	2,
	TT_REDIR,
	TC_GREATAND,
	token_parse_greatand
};

static t_token g_token_redir_lessand = {
	"<&",
	2,
	TT_REDIR,
	TC_LESSAND,
	token_parse_lessand
};

static t_token g_token_jobs_semi = {
	";",
	1,
	TT_JOBS,
	TC_SEMI,
	token_parse_semi
};

static t_token g_token_redir_great = {
	">",
	1,
	TT_REDIR,
	TC_GREAT,
	token_parse_great
};

static t_token g_token_redir_less = {
	"<",
	1,
	TT_REDIR,
	TC_LESS,
	token_parse_less
};

static t_token g_token_redir_pipe = {
	"|",
	1,
	TT_REDIR,
	TC_PIPE,
	token_parse_pipe
};

static t_token g_token_special_and = {
	"&",
	1,
	TT_SPECIAL,
	TC_AND,
	token_parse_and
};

static t_token g_token_inhibitor_dquote = {
	"\"",
	1,
	TT_INHIBITOR,
	TC_DQUOTE,
	token_parse_inhib
};

static t_token g_token_inhibitor_quote = {
	"'",
	1,
	TT_INHIBITOR,
	TC_QUOTE,
	token_parse_inhib
};

static t_token g_token_separator_space = {
	" ",
	1,
	TT_SEPARATOR,
	TC_SPACE,
	token_parse_separator
};

static t_token g_token_separator_tab = {
	"\t",
	1,
	TT_SEPARATOR,
	TC_TAB,
	token_parse_separator
};

static t_token g_token_separator_newline = {
	"\n",
	1,
	TT_SEPARATOR,
	TC_NEWLINE,
	token_parse_separator
};

static t_token g_token_name_backslash = {
	"\\",
	1,
	TT_NAME,
	TC_BACKSLASH,
	token_parse_none
};

static t_token g_token_name_bquote = {
	"`",
	1,
	TT_NAME,
	TC_BQUOTE,
	token_parse_none
};

static t_token g_token_name_lbrace = {
	"{",
	1,
	TT_NAME,
	TC_LBRACE,
	token_parse_none
};

static t_token g_token_name_rbrace = {
	"}",
	1,
	TT_NAME,
	TC_RBRACE,
	token_parse_none
};



static t_token g_token_globing_inhibitor_dquote = {
	"\"",
	1,
	TT_INHIBITOR,
	TC_DQUOTE,
	token_globing_parse_inhib
};

static t_token g_token_globing_inhibitor_quote = {
	"'",
	1,
	TT_INHIBITOR,
	TC_QUOTE,
	token_globing_parse_inhib
};

static t_token g_token_globing_name_tilde = {
	"~",
	1,
	TT_NAME,
	TC_TILDE,
	token_globing_parse_none
};

static t_token g_token_globing_name_backslash = {
	"\\",
	1,
	TT_NAME,
	TC_BACKSLASH,
	token_globing_parse_none
};


static int	s_build_token_globing(t_parser *parser)
{
	int		i;

	i = 0;
	parser->token_list[i++] = &g_token_globing_inhibitor_dquote;
	parser->token_list[i++] = &g_token_globing_inhibitor_quote;
	parser->token_list[i++] = &g_token_globing_name_tilde;
	parser->token_list[i++] = &g_token_globing_name_backslash;
	parser->token_list[i++] = NULL;
	return (ST_OK);
}

static int	s_build_token_command_line(t_parser *parser)
{
	int		i;

	i = 0;
	parser->token_list[i++] = &g_token_redir_dless;
	parser->token_list[i++] = &g_token_redir_dgreat;
	parser->token_list[i++] = &g_token_jobs_or_if;
	parser->token_list[i++] = &g_token_jobs_and_if;
	parser->token_list[i++] = &g_token_error_dsemi;
	parser->token_list[i++] = &g_token_redir_clobber;
	parser->token_list[i++] = &g_token_redir_andgreat;
	parser->token_list[i++] = &g_token_redir_greatand;
	parser->token_list[i++] = &g_token_redir_lessand;
	parser->token_list[i++] = &g_token_jobs_semi;
	parser->token_list[i++] = &g_token_redir_great;
	parser->token_list[i++] = &g_token_redir_less;
	parser->token_list[i++] = &g_token_redir_pipe;
	parser->token_list[i++] = &g_token_special_and;
	parser->token_list[i++] = &g_token_inhibitor_dquote;
	parser->token_list[i++] = &g_token_inhibitor_quote;
	parser->token_list[i++] = &g_token_name_backslash;
	parser->token_list[i++] = &g_token_separator_space;
	parser->token_list[i++] = &g_token_separator_tab;
	parser->token_list[i++] = &g_token_separator_newline;
	parser->token_list[i++] = &g_token_name_rbrace;
	parser->token_list[i++] = &g_token_name_lbrace;
	parser->token_list[i++] = &g_token_name_bquote;
	parser->token_list[i++] = NULL;
	return (ST_OK);
}

int	parser_new(t_parser **parser, const char *in, t_sh *sh, int mode)
{
	if (!in)
		return (ST_EINVAL);
	if (!(*parser = ft_memalloc(sizeof(t_parser))))
		return (ST_MALLOC);
	if (!((*parser)->in = ft_strdup(in)))
		return (ST_MALLOC);
	if (!((*parser)->lexer = ft_memalloc(sizeof(t_lexer))))
		return (ST_MALLOC);
	(*parser)->lexer->sh = sh;
	// TODO : make dynamic token list
	(*parser)->mode = mode;
	(*parser)->target_list_head = NULL;
	(*parser)->sh = sh;

	if (mode == F_PARSING_GLOBING)
		s_build_token_globing(*parser);
	else
		s_build_token_command_line(*parser);

	// assign the unstack function according to the parsing mode
	if (mode == F_PARSING_TERMCAPS)
		(*parser)->unstack_func = NULL;
	else if (mode == F_PARSING_JOBS)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_job;
	else if (mode == F_PARSING_PROCS)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_proc;
	else if (mode == F_PARSING_NONE)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_none;
	else if (mode == F_PARSING_GLOBING)
		(*parser)->unstack_func = &parser_build_list_unstack_lexer_globing;
	else
	{
		log_error("parsing mode not yet supported (%d)", mode);
		return (ST_EINVAL);
	}

	return (ST_OK);
}
