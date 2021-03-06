# ---------------------------------------------------------------------------- #
# The purpose of the Makefile is to provide a tool to optimize the build of a  #
# project using dependency rules.                                              #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# USAGE                                                                        #
#                                                                              #
# ---------------------------------------------------------------------------- #
# First, the user must configure its environment settings.                     #
# - see 'PROJECT CONFIGURATION' to configure project directories               #
# - see 'EXTERNAL TOOLS SETTINGS' to setup default programs to use             #
#                                                                              #
# Second, configure the sources.                                               #
# - see 'TARGET SETUP' to set the name of the target and the sources           #
#                                                                              #
# Third, configure the build options.                                          #
# - see 'PROJECT COMPILATION' to setup preprocessor, flags and libraries       #
#                                                                              #
# Fourth, setup the linking rule.                                              #
# - see 'PUBLIC RULES' to modify the $(NAME) rule                              #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# To add custom rules, the concerned section is 'PUBLIC RULES'. Be sure to     #
# keep at least the rules all, $(NAME), libs, clean, fclean and re.            #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# To add a library, the procedure is the following:                            #
# - add the path to the library archive on LIBS                                #
# - add the directory preceding by -L to LDFLAGS                               #
# - add the reduced name of the library on LDLIBS preceding by -l              #
# - add the header directories to CPPFLAGS preceding by -I                     #
# The last step is to custom the libs and fcleanlibs rules to build and clean  #
# the corresponding libraries.                                                 #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
#                               /!\ WARNING /!\                                #
#                                                                              #
# The sections commented with '/!\' are critical, and must not be modified.    # 
#                                                                              #
# ---------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------- #
# PROJECT CONFIGURATION                                                        #
# ---------------------------------------------------------------------------- #
# - The 'DIR*' variables describe all directories of the project.              #
# ---------------------------------------------------------------------------- #

DIRSRC	=	srcs
DIRINC	=	incs
DIRLIB	=	libs
DIRTST	=	test
DIROBJ	=	.objs
DIRDEP	=	.deps

# ---------------------------------------------------------------------------- #
# EXTERNAL TOOLS SETTINGS                                                      #
# ---------------------------------------------------------------------------- #
# - Set the default external programs.                                         #
# ---------------------------------------------------------------------------- #

CC		=	clang
AR		=	ar
ARFLAGS	=	rc
RM		=	rm -f

# ---------------------------------------------------------------------------- #
#                                                                              #
# TARGET SETUP                                                                 #
#                                                                              #
# ---------------------------------------------------------------------------- #
# - The 'NAME' variable must contain the expected name of the output target.   #
# - The 'SRCS' variable must contain the list of the source files without the  #
# base prefix of the directory.                                                #
# ---------------------------------------------------------------------------- #

NAME	=	weSH

SRCS	=	\
			main.c														\
			parser/parser.c												\
			parser/alloc/parser_new.c									\
			parser/build/parser_build_list_unstack_lexer.c				\
			parser/build/parser_build_list_unstack_lexer_none.c			\
			parser/build/parser_build_list_unstack_lexer_job.c			\
			parser/build/parser_build_list_unstack_lexer_proc.c			\
			parser/build/parser_build_list_unstack_lexer_var.c			\
			parser/build/parser_build_list_unstack_lexer_glob_brace.c	\
			parser/expand/expand.c										\
			parser/expand/expand_glob_brace.c							\
			parser/expand/expand_tilde.c								\
			parser/expand/expand_tilde_through_buffer.c					\
			parser/expand/expand_get_words.c							\
			parser/expand/expand_prepare_globbing_tokens.c				\
			parser/globbing/globbing.c									\
			parser/globbing/globbing_bracket.c							\
			parser/globbing/globbing_run_parse.c						\
			parser/globbing/globbing_run_parse_readir.c					\
			parser/globbing/globbing_add_node_to_list.c					\
			parser/globbing/globbing_add_node_alpha_to_list.c			\
			parser/globbing/globbing_exp_param_bracket.c				\
			parser/globbing/globbing_happend_to_list.c					\
			parser/globbing/globbing_load_context.c						\
			parser/globbing/globbing_bracket_exp_subsequence.c 			\
			parser/globbing/globbing_sort_list_glob.c 					\
			parser/globbing/globbing_remove_double.c 					\
			parser/globbing/globbing_bracket_recurse.c 					\
			parser/globbing/globbing_before_expand.c 					\
			parser/globbing/globbing_check.c 							\
			parser/lexer/lexer_bufferize.c								\
			parser/lexer/lexer_token_add.c								\
			parser/lexer/lexer_tokens_alloc.c							\
			parser/lexer/lexer_tokens_realloc.c							\
			parser/lexer/lexer_buffer_dump.c							\
			parser/lexer/lexer.c										\
			parser/lexer/lexer_tokenize.c								\
			parser/lexer/lexer_token_recognizer.c						\
			parser/token/token_glob_brace_parse_none.c					\
			parser/token/token_glob_brace_parse_pattern.c				\
			parser/token/token_var_parse_none.c							\
			parser/token/token_var_parse_inhib.c						\
			parser/token/token_parse_none.c								\
			parser/token/token_parse_and.c								\
			parser/token/token_parse_andgreat.c							\
			parser/token/token_parse_greatand.c							\
			parser/token/token_parse_lessand.c							\
			parser/token/token_parse_semi.c								\
			parser/token/token_parse_and_if.c							\
			parser/token/token_parse_or_if.c							\
			parser/token/token_parse_pipe.c								\
			parser/token/token_parse_less.c								\
			parser/token/token_parse_great.c							\
			parser/token/token_parse_dless.c							\
			parser/token/token_parse_dgreat.c							\
			parser/token/token_parse_inhib.c							\
			parser/token/token_parse_separator.c						\
			parser/token/token_parse_subshell.c							\
			parser/token/utils/token_glob_brace_parse_ascii_range.c		\
			parser/token/utils/token_glob_brace_parse_list.c			\
			parser/token/utils/token_glob_brace_parse_numeric_range.c	\
			parser/token/utils/token_parse_utils_get_full_word.c		\
			parser/token/utils/token_parse_utils_get_word_and_inhib.c	\
			parser/token/utils/token_parse_utils_open_new_fd.c			\
			parser/token/utils/token_parse_utils_push_command.c			\
			parser/token/utils/token_parse_utils_set_proc_fds.c			\
			parser/token/utils/token_parse_utils_skip_separators.c		\
			parser/token/utils/token_parse_utils_check_char_to_fd.c		\
			parser/token/utils/token_parse_utils_gen_token_after_dash.c	\
			parser/token/utils/token_parse_utils_heredoc.c				\
			parser/token/utils/token_globing_parse_utils_push_str.c		\
			builtins/bg/builtin_bg.c									\
			builtins/cd/builtin_cd.c									\
			builtins/cd/builtin_cd_chk_path.c							\
			builtins/cd/builtin_cd_readlink.c							\
			builtins/cd/builtin_cd_rm_dotdot.c							\
			builtins/echo/builtin_echo.c								\
			builtins/echo/builtin_echo_escape.c							\
			builtins/exit/builtin_exit.c								\
			builtins/export/builtin_export.c							\
			builtins/export/builtin_export_display.c					\
			builtins/export/builtin_export_n_option.c					\
			builtins/export/builtin_export_set.c						\
			builtins/export/builtin_export_set_no_value.c				\
			builtins/export/builtin_export_set_local_and_env.c			\
			builtins/export/builtin_export_update_local_with_value.c	\
			builtins/fg/builtin_fg.c									\
			builtins/help/builtin_help.c								\
			builtins/history/builtin_history.c							\
			builtins/history/default_history.c							\
			builtins/history/read_history.c								\
			builtins/history/write_history.c							\
			builtins/history/append_history.c							\
			builtins/history/print_history.c							\
			builtins/history/wrap_histfile.c							\
			builtins/jobs/builtin_jobs.c								\
			builtins/env/builtin_env.c									\
			builtins/language/builtin_language.c						\
			builtins/setenv/builtin_setenv.c							\
			builtins/setenv/builtin_setenv_argv_is_valid.c				\
			builtins/set_local/builtin_set_local.c						\
			builtins/set_local/builtin_local_var_set_local_loop.c		\
			builtins/set_local/builtin_local_var_add.c					\
			builtins/set_local/builtin_local_var_update.c				\
			builtins/set_local/builtin_local_var_delete.c				\
			builtins/termcaps/builtin_termcaps.c						\
			builtins/unsetenv/builtin_unsetenv.c						\
			builtins/unset/builtin_unset.c								\
			builtins/builtin_callback.c									\
			builtins/builtin_usage.c									\
			env/env_get.c												\
			env/env_get_path.c											\
			env/env_get_user.c											\
			env/env_get_home.c											\
			env/env_get_term.c											\
			env/env_set.c												\
			env/env_unset.c												\
			env/env_index_value.c										\
			env/env_or_var_update_from_cmd_line.c						\
			env/env_get_value_and_remove_equal_sign.c					\
			display/display_status.c									\
			i18n/i18n_translate.c										\
			init/shell_init.c											\
			init/shell_language.c										\
			init/shell_environment.c									\
			init/shell_set_prompt.c										\
			init/shell_color_mode.c										\
			job/job_alloc.c												\
			job/proc_alloc.c											\
			job/job_available_id.c										\
			job/job_background.c										\
			job/job_background_nth.c									\
			job/job_background_update_status.c							\
			job/job_by_id.c												\
			job/job_by_name.c											\
			job/job_display_status.c									\
			job/job_foreground.c										\
			job/job_free.c												\
			job/job_is_completed.c										\
			job/job_is_signaled.c										\
			job/job_is_stopped.c										\
			job/job_kill.c												\
			job/job_launch.c											\
			job/job_list_clean.c										\
			job/job_list_clean_except_job.c								\
			job/job_set_stopped.c										\
			job/job_wait.c												\
			job/proc_find.c												\
			job/proc_free.c												\
			job/proc_launch.c											\
			job/proc_subshell.c											\
			job/proc_update_status.c									\
			job/redir_alloc.c											\
			job/redir_free.c											\
			job/redir_list_free.c										\
			loop/loop_job_launcher.c									\
			loop/loop_main.c											\
			local_var/local_var_replace.c								\
			local_var/local_var_replace_char_or_loop.c					\
			local_var/local_var_concat.c								\
			options/option_get_value.c									\
			options/option_get_values.c									\
			options/option_is_set.c										\
			options/option_push.c										\
			options/option_free.c										\
			options/option_parse.c										\
			path/path_init_hasht.c										\
			path/path_free_hasht.c										\
			path/path_get_new_cmd.c										\
			path/path_fnv_a_str.c										\
			path/path_hash_finder.c										\
			path/path_add_folder_content_to_hasht.c						\
			path/path_commande_not_found_in_hasht.c						\
			path/path_set_struct_display.c								\
			quoting/quoting_new_context.c								\
			quoting/quoting_concat_new_input.c							\
			signal/signal_to_default.c									\
			signal/signal_to_ignore.c									\
			signal/signal_to_pgid.c										\
			termcaps/termcaps_initialize.c								\
			termcaps/termcaps_finalize.c								\
			termcaps/termcaps_line_print.c								\
			termcaps/termcaps_line_erase.c								\
			termcaps/termcaps_read_input.c								\
			termcaps/termcaps_read_loop.c								\
			termcaps/termcaps_get_character_bytes_count.c				\
			termcaps/command_add_string.c								\
			termcaps/termcaps_display_command.c							\
			termcaps/termcaps_isunicode.c								\
			termcaps/termcaps_identify_input.c							\
			termcaps/list_head.c										\
			termcaps/list_head_command.c								\
			termcaps/list_head_history.c								\
			termcaps/list_head_history_search.c							\
			termcaps/history_init.c										\
			termcaps/history_get_filename.c								\
			termcaps/history_load.c										\
			termcaps/history_write.c									\
			termcaps/key__backspace.c									\
			termcaps/key__copy.c										\
			termcaps/key__cursor_to_begin_of_line.c						\
			termcaps/key__cursor_to_end_of_line.c						\
			termcaps/key__cursor_to_next_character.c					\
			termcaps/key__cursor_to_next_command.c						\
			termcaps/key__cursor_to_next_line.c							\
			termcaps/key__cursor_to_next_word.c							\
			termcaps/key__cursor_to_prev_character.c					\
			termcaps/key__cursor_to_prev_command.c						\
			termcaps/key__cursor_to_prev_line.c							\
			termcaps/key__cursor_to_prev_word.c							\
			termcaps/key__cut.c											\
			termcaps/key__cut_to_end_of_line.c							\
			termcaps/key__delete_command.c								\
			termcaps/key__delete_under_cursor.c							\
			termcaps/key__paste.c										\
			termcaps/key__select.c										\
			termcaps/key__send.c										\
			termcaps/key__share__copy_build_copy.c						\
			termcaps/key__share__cut_build_copy.c						\
			termcaps/key__share__selection_get.c						\
			termcaps/key__share_words.c									\
			termcaps/key__completion.c									\
			termcaps/key__completion_s.c								\
			termcaps/key__completion_int.c								\
			termcaps/key__completion_match.c							\
			termcaps/key__completion_display.c							\
			termcaps/key__ctrl_c.c										\
			termcaps/key__clear.c										\
			termcaps/key__search_history.c								\
			termcaps/termcaps_write.c									\
			termcaps/events.c											\
			termcaps/events_info.c										\
			termcaps/events_word.c										\
			conf/conf_check_color_mode.c								\
			termcaps/termcaps_error.c									\
			termcaps/count_func.c										\
			conf/conf_file_init.c										\



# ---------------------------------------------------------------------------- #
# PROJECT COMPILATION                                                          #
# ---------------------------------------------------------------------------- #
# - The 'LIBS' tells the compiler where to find libraries.                     #
# - The 'LDFLAGS' tells the linker where to find external libraries (-L flag). #
# - The 'LDLIBS' tells the linker the prefix of external libraries (-l flag).  #
# - The 'CPPFLAGS' tells the compiler where to find preprocessors (-I flag).   #
# - The 'CFLAGS' configures the compiler options.                              #
# ---------------------------------------------------------------------------- #

LIBS        =   \
                $(DIRLIB)/libft/libft.a         \
                $(DIRLIB)/logger/liblogger.a    \
                $(DIRLIB)/libcaps/libcaps.a     \

LDFLAGS		=	\
				-L $(DIRLIB)/logger				\
				-L $(DIRLIB)/libcaps			\
				-L $(DIRLIB)/libft				\

LDLIBS		=	\
				-llogger						\
				-lcaps							\
				-lft							\
				-ltermcap						\

CPPFLAGS	=	\
				-I $(DIRINC)					\
				-I $(DIRINC)/termcaps/			\
				-I $(DIRINC)/builtins/			\
				-I $(DIRLIB)/libft/$(DIRINC)	\
				-I $(DIRLIB)/logger/$(DIRINC)	\
				-I $(DIRLIB)/libcaps/$(DIRINC)	\

CFLAGS		=	\
				-g								\
				-Wall -Wextra -Werror			\

# ---------------------------------------------------------------------------- #
# /!\ SOURCE NORMALIZATION AND COMPILATION RULES /!\                           #
# ---------------------------------------------------------------------------- #

DEPFLAGS	=	\
				-MT $@ -MMD -MP -MF $(DIRDEP)/$*.Td	\

COMPILE.c	=	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

POSTCOMPILE	=	mv -f $(DIRDEP)/$*.Td $(DIRDEP)/$*.d

SRC	        =	$(addprefix $(DIRSRC)/, $(SRCS))
OBJ         =	$(addprefix $(DIROBJ)/, $(SRCS:.c=.o))

$(DIROBJ)	:
	@mkdir -p $(DIROBJ)

$(DIRDEP)	:
	@mkdir -p $(DIRDEP)

# ---------------------------------------------------------------------------- #
# PUBLIC RULES                                                                 #
# ---------------------------------------------------------------------------- #
# The rules must contain at least :                                            #
# - all        make libs and target                                            #
# - $(NAME)    make binaries and target                                        #
# - libs       build static libraries                                          #
# - clean      remove binaries                                                 #
# - fclean     remove binaries and target                                      #
# - fcleanlibs apply fclean rule on libraries                                  #
# - re         remove binaries, target and libraries and build the target      #
#                                                                              #
# To compile a static library, the $(NAME) rule should be :                    #
#     '$(AR) $(ARFLAGS) $(NAME) $(OBJ)'                                        #
#     'ranlib $(NAME)'                                                         #
#                                                                              #
# To compile a C binary, the $(NAME) rule should be :                          #
#     '$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)'                           #
# ---------------------------------------------------------------------------- #

all			:	libs $(NAME)
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "finish to build $(NAME)"

$(NAME)		:	$(DIROBJ) $(DIRDEP) $(OBJ) $(LIBS)
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "link objects..."
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

libs		:
	@make -C $(DIRLIB)/libft
	@make -C $(DIRLIB)/logger
	@make -C $(DIRLIB)/libcaps

fcleanlibs	:
	@make -C $(DIRLIB)/libft fclean
	@make -C $(DIRLIB)/logger fclean
	@make -C $(DIRLIB)/libcaps fclean

clean		:
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "remove objects..."
	@$(RM) -r $(DIROBJ)
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "remove dependencies..."
	@$(RM) -r $(DIRDEP)

fclean		:	clean
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "remove target..."
	@$(RM) $(NAME)

re			:	fcleanlibs fclean all

# ---------------------------------------------------------------------------- #
# CUSTOM RULES                                                                 #
# ---------------------------------------------------------------------------- #

test		:	re
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "run tests..."
	@cd $(DIRTST) && bash 42ShellTester.sh $$PWD/../$(NAME) --hard

submodule	:
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "retrieve submodules..."
	@git submodule init && git submodule update
	@git submodule foreach git checkout master
	@git submodule foreach git pull --rebase origin master

norme		:
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "run norminette..."
	@printf "\033[33m[ %s ]\033[0m %s\n" "$(NAME)" "missing headers not check"
	@/usr/bin/norminette -R CheckTopCommentHeader	\
		$$(find * -name "*.[ch]" ! -path "test/*")
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "run norminette..."
	@printf "\033[33m[ %s ]\033[0m %s\n" "$(NAME)" "missing headers not check"

# ---------------------------------------------------------------------------- #
# /!\ PRIVATE RULES /!\                                                        #
# ---------------------------------------------------------------------------- #

$(DIROBJ)/%.o	:	$($(DIRSRC)/%.c
$(DIROBJ)/%.o	:	$(DIRSRC)/%.c $(DIRDEP)/%.d
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(word 2,$^))
	@printf "\033[32m[ %s ]\033[0m %s\n" "$(NAME)" "compiling $<..."
	@$(COMPILE.c) $(OUTPUT_OPTION) $<
	@$(POSTCOMPILE)

$(DIRDEP)/%.d	:	;
.PRECIOUS		:	$(DIRDEP)/%.d

-include $(patsubst %,$(DIRDEP)/%.d,$(basename $(SRC)))

# ---------------------------------------------------------------------------- #

.PHONY	:	all clean fclean re $(DIROBJ)/%.o $(DIRDEP)/%.d libs

# ---------------------------------------------------------------------------- #
