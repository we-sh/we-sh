#ifndef SHELL_H
# define SHELL_H
# define TTY_DEVICE "/dev/tty"
# define PROGRAM_NAME "42sh"

/*
** Extern headers and structures
*/
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <curses.h>

/*
** Shell structure
*/

typedef struct	e_sh
{
	pid_t			pgid;
	int 			fd;
	struct termios 	oldter;
	struct termios 	newter;
}				t_sh;

# include "libft.h"
# include "list.h"
# include "logger.h"
# include "job.h"
# include "termcaps.h"
# include "caps.h"
# include "statuses.h"
# include "i18n.h"
# include "get_next_line.h"
# include "lexer.h"
# include "builtin.h"

/*
** List of current jobs
*/
t_list		g_current_jobs_list_head;

int				stdin_loop(t_sh *sh);
int				parse(t_sh *sh, char const *input);

/*
** builtins/
*/
int				builtin_callback(int callback, t_sh *sh, t_proc *p);

/*
** exit/
*/
void			shell_exit(int status);

/*
** i18n/
*/
char const		*i18n_translate(int status);

/*
** init/
*/
int				shell_fd(void);
int				shell_init(t_sh *sh);
int				shell_is_interactive(void);
int				shell_language(int lang);

/*
** job/
*/
int				job_foreground(t_sh *sh, t_job *j, int sigcont);
int				job_is_completed(t_job *j);
int				job_is_stopped(t_job *j);
int				job_launch(t_sh *sh, t_job *j);
t_proc			*proc_find(pid_t pid);
void			proc_launch(t_sh *sh, t_job *j, t_proc *p);
int				proc_update_status(pid_t pid, int status);
t_list			*list_node__proc_alloc(char **argv);
t_job			*job_alloc(char const *command);
int				job_wait(t_job *j);

/*
** signal/
*/
void			signal_sigchld(int sig);
int				signal_to_ignore(void);
int				signal_to_default(void);

/*
** lexer/
*/
int			lexer(char const *input, t_lexer *lexer);
t_token		*token_list(void);
int			tokenize(const char *s, t_lexer *lexer);

/*
** termcaps/
*/
int				termcaps_character_to_command_line(const size_t character_bytes_count,
											 const char *character_bytes,
											 t_list_head *command_line);
int				termcaps_display_command_line(const t_list_head *command_line);
size_t			termcaps_get_character_bytes_count(const size_t input_bytes_count,
								  const char *input_bytes,
								  size_t *out_missing_bytes_count);
int				termcaps_init(t_sh *sh);
int				termcaps_isunicode(const char c, size_t *out_character_bytes_count);
char			*termcaps_read_input(const int fd);
int				termcaps_string_to_command_line(const size_t input_buffer_size,
										  const char *input_buffer,
										  t_list_head *command_line);

#endif
