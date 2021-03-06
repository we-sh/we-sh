#ifndef SHELL_H
# define SHELL_H
# define TTY_DEVICE "/dev/tty"
# define PROGRAM_NAME "weSH"
# define CONFIGURATION_FILE ".weshrc"
# define TERMCAPS_BUFFER_MAX 4096
# define PATH_RT "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define PATH_STD "/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games"

/*
** Colors defines.
*/

# ifdef __linux__

#  define SELECTBLANC "\e]12;white\a"
#  define SELECTBLEU "\e]12;blue\a"
#  define LSOPTCOLOR "--color=auto"
# else
#  define SELECTBLANC "\033]Plffffff\033\\"
#  define SELECTBLEU "\033]Pl4040ff\033\\"
#  define LSOPTCOLOR "-G"
# endif

# define PROMPT_COLOR

# ifdef PROMPT_COLOR
#  define ANSI_COLOR_RESET_SIZE (sizeof("\033[0m") - 1)
#  define ANSI_COLOR_RESET "\033[0m"
#  define ANSI_COLOR_LIGHT_BLUE_SIZE (sizeof("\033[94m") - 1)
#  define ANSI_COLOR_LIGHT_BLUE "\033[94m"
# else
#  define ANSI_COLOR_RESET_SIZE (0)
#  define ANSI_COLOR_RESET ""
#  define ANSI_COLOR_LIGHT_BLUE_SIZE (0)
#  define ANSI_COLOR_LIGHT_BLUE ""
# endif

# define MIN(x, y) (x < y ? x : y)
# define MAX(x, y) (x > y ? x : y)

/*
** Project headers
*/

# include "shell_struct.h"
# include "list.h"
# include "htabl.h"
# include "termcaps.h"
# include "events.h"
# include "redirection.h"
# include "libft.h"
# include "logger.h"
# include "statuses.h"
# include "option.h"
# include "job.h"
# include "caps.h"
# include "parser.h"
# include "builtin.h"
# include "parser_struct.h"
# include "globbing.h"

/*
** List of current jobs
*/

t_list			g_current_jobs_list_head;

int				parser(t_sh *sh, char const *input, int mode,
						t_list *target_list_head);

/*
** builtins/
*/

int				builtin_callback(int callback, t_sh *sh, t_proc *p);
int				setenv_argv_is_valid(char const *arg);
void			builtin_usage(t_builtin const *bltin, int status);

/*
** env /
*/

char			*env_get(char **envp, char *key);
char			*env_get_path(char **envp);
char			*env_get_user(char **envp);
char			*env_get_home(char **envp);
char			*env_get_term(char **envp);
int				env_set(char ***envp, char *key, char *value, int htable_modif);
int				env_unset(char ***envp, char *argv);
int				env_index_value(char **envp, char *variable);
int				env_or_var_update_from_cmd_line(t_proc **p, t_sh **sh);
char			*env_get_value_and_remove_equal_sign(char *arg);

/*
** log_status /
*/

int				display_status(const int status, const char *prefix,
								const char *suffix);

/*
** i18n/
*/

char const		*i18n_translate(int status);

/*
** init/
*/

int				shell_init(t_sh *sh, char *envp[]);
int				shell_language(int lang);
int				shell_environment(t_sh *sh, char **envp);
char			*shell_set_prompt(t_sh *sh);
int				shell_color_mode(int color_mode);

/*
** job/
*/

int				job_available_id(void);
int				job_foreground(t_sh *sh, t_job *j, int const sigcont);
int				job_background(t_sh *sh, t_job *j, int const sigcont);
int				job_is_completed(t_job *j);
int				job_is_signaled(t_job *j);
int				job_is_stopped(t_job *j);
int				job_launch(t_sh *sh, t_job *j);
t_proc			*proc_find(pid_t pid);
void			proc_launch(t_sh *sh, t_job *j, t_proc *p);
int				proc_update_status(t_job *j, pid_t pid, int status);
t_job			*job_alloc(char const *command);
t_proc			*proc_alloc(t_sh *sh, t_job *j);
int				job_wait(t_job *j);
int				job_kill(t_sh *sh, t_job *j, int status);
void			job_list_clean(int notified);
void			job_list_clean_except_job(t_job *j);
void			job_free(t_job **j);
void			proc_free(t_proc **p);
t_job			*job_by_name(char const *name, int const foreground);
t_job			*job_by_id(int const id, int const foreground);
t_job			*job_background_nth(const t_list *head, const int index);
int				job_background_update_status(void);
int				job_display_status(t_job *j, int show_pid);
void			job_set_stopped(t_job *j, int const stopped);
t_redir			*redir_alloc(int fd);
void			redir_free(t_redir **redir);
void			redir_list_free(t_list *redir_head);
void			proc_subshell(t_sh *sh, t_job *j, t_proc *p);

/*
** loop/
*/

int				loop_main(t_sh *sh);
int				loop_job_launcher(t_sh *sh, char *input);

/*
** options/
*/

int				option_is_set(t_list *list_option_head, int option_index);
char			*option_get_value(t_list *list_option_head, int option_index);
char			**option_get_values(t_list *list_option_head, int option_index);
int				option_parse(t_list *list_head,
					t_option const **available_options,
					char ***argv, size_t start);
int				option_push(t_list *list_head, t_option const *option_ref,
											char **argv, size_t i);
void			option_free(t_option **opt);

/*
** path
*/

int				path_init_hasht(char **envp);
int				path_hash_finder(char **envp, char **commande);
int				path_add_folder_content_to_hasht(char *name,
													char *dirname,
													t_display_h *display,
													char **envp);
void			path_free_hasht(void);
int				path_commande_not_found_in_hasht(char **envp, char **cmd);
int				path_get_new_cmd(char **commande, char *name, char *path);
void			path_set_struct_display(t_display_h *display);

/*
** quoting
*/

int				quoting_new_context(t_termcaps_context *context, int tokenid);
int				concat_new_input(char **cmd,
									t_termcaps_context *chld,
									char **tmp);

/*
** signal/
*/

int				signal_to_ignore(void);
int				signal_to_default(void);
int				signal_to_pgid(int pgid);

/*
** termcaps/
*/

int				termcaps_initialize(t_sh *sh, const char *prompt,
									t_termcaps_context *context);
int				termcaps_finalize(t_termcaps_context *context);
int				command_add(const size_t char_bytes_cnt,
											const char *character_bytes,
											t_list_head *command);
int				termcaps_display_command(const t_termcaps_context *cont);
size_t			termcaps_get_character_bytes_count(const size_t input_bytes_cnt,
								const char *input_bytes,
								size_t *out_missing_bytes_count);
int				termcaps_isunicode(const char c, size_t *out_char_bytes_cnt);
char			*termcaps_read_input(t_termcaps_context *context);
int				command_add_string(const size_t input_buffer_size,
										const char *input_buffer,
										t_list_head *command);
int				termcaps_write(int fd, char *buffer, size_t buffer_size);
int				termcaps_line_print(t_termcaps_context *context,
									t_buffer *history_search);
void			termcaps_line_erase(t_termcaps_context *context,
									const t_buffer history_search);
void			termcaps_identify_input(const unsigned int c,
										t_input_type *input_type,
										size_t *input_size_missing);
int				termcaps_read_loop(t_termcaps_context *context,
									size_t input_buffer_size,
									size_t input_size_missing);

t_node_dir		*node_dir__create(const struct dirent *ep);
void			list_dir__destroy(t_list *head);
int				get_matchs(char *path, char *lookfor,
							t_list *matchs, size_t *ref_size);
int				match_binaries(char **envp, char *lookfor,
							t_list *matchs, size_t *ref_size);
int				int_key_completion(char **envp, char *buf,
								t_list *matchs, char **lookfor);
int				display_completion(const size_t command_size,
									const int fd,
									t_list *matchs,
									const int ref_size);

/*
** conf
*/

int				conf_file_init(char **env);
int				conf_check_color_mode(char **env);

/*
** local_var
*/
int				local_var_replace(t_sh *sh, char *input, char **output);
int				local_var_replace_char_or_loop(t_sh *sh, char *input,
										char **output, int *i);
int				local_var_concat(char **output, char *input, int len);
#endif
