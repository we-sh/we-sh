# ---------------------------------------------------------------------------- #
# PROJECT DATA
# ---------------------------------------------------------------------------- #

NAME		=	42sh

# ---------------------------------------------------------------------------- #

SRCS		=	\
				main.c							\
				parser/parser.c										\
				parser/alloc/parser_new.c							\
				parser/build/parser_process_build.c					\
				parser/build/job_build_unstack_lexer.c				\
				parser/build/job_build_unstack_job_from_lexer.c		\
				parser/build/job_build_unstack_proc_from_lexer.c	\
				parser/expand/expand.c								\
				parser/expand/expand_tilde.c						\
				parser/lexer/parser_process_lexer.c					\
				parser/lexer/token_list.c							\
				parser/lexer/tokenize.c								\
				parser/token/token_parse_none.c						\
				parser/token/token_parse_semi.c						\
				parser/token/token_parse_dbl_and.c					\
				parser/token/token_parse_dbl_or.c					\
				parser/token/token_parse_pipe.c						\
				parser/token/token_parse_chev_left.c				\
				parser/token/token_parse_chev_right.c				\
				parser/token/token_parse_dbl_chev_left.c			\
				parser/token/token_parse_dbl_chev_right.c			\
				parser/token/token_parse_inhib.c					\
				environment_init.c				\
				builtins/bg/builtin_bg.c		\
				builtins/cd/builtin_cd.c		\
				builtins/exit/builtin_exit.c	\
				builtins/fg/builtin_fg.c		\
				builtins/help/builtin_help.c	\
				builtins/jobs/builtin_jobs.c	\
				builtins/env/builtin_env.c		\
				builtins/setenv/builtin_setenv.c\
				builtins/setenv/builtin_setenv_argv_is_valid.c\
				builtins/termcaps/builtin_termcaps.c\
				builtins/unsetenv/builtin_unsetenv.c\
				builtins/builtin_callback.c		\
				builtins/builtin_usage.c		\
				env/env_get.c					\
				env/env_get_path.c				\
				env/env_get_user.c				\
				env/env_get_home.c				\
				env/env_get_term.c				\
				env/env_set.c					\
				env/env_unset.c					\
				env/env_index_value.c			\
				env/env_update_from_cmd_line.c	\
				display/display_status.c		\
				i18n/i18n_translate.c			\
				init/shell_init.c				\
				init/shell_language.c			\
				job/job_alloc.c					\
				job/proc_alloc.c				\
				job/job_available_id.c			\
				job/job_background.c			\
				job/job_background_nth.c		\
				job/job_background_update_status.c\
				job/job_by_id.c					\
				job/job_by_name.c				\
				job/job_display_status.c		\
				job/job_foreground.c			\
				job/job_free.c					\
				job/job_is_completed.c			\
				job/job_is_signaled.c			\
				job/job_is_stopped.c			\
				job/job_kill.c					\
				job/job_launch.c				\
				job/job_list_clean.c			\
				job/job_set_stopped.c			\
				job/job_wait.c					\
				job/proc_find.c					\
				job/proc_free.c					\
				job/proc_launch.c				\
				job/proc_update_status.c		\
				loop/loop_main.c				\
				options/option_get_value.c		\
				options/option_is_set.c			\
				options/list_node__option_alloc.c\
				options/option_free.c			\
				options/option_parse.c			\
				path/path_init_hasht.c			\
				path/path_free_hasht.c			\
				path/path_get_new_cmd.c			\
				path/path_fnv_64a_str.c			\
				path/path_hash_finder.c			\
				path/path_add_folder_content_to_hasht.c	\
				path/path_commande_not_found_in_hasht.c\
				quoting/quoting_new_context.c\
				quoting/quoting_invalid.c\
				signal/signal_to_default.c		\
				signal/signal_to_ignore.c		\
				termcaps/termcaps_context.c		\
				termcaps/termcaps_read_input.c					\
				termcaps/termcaps_get_character_bytes_count.c	\
				termcaps/termcaps_string_to_command_line.c		\
				termcaps/termcaps_character_to_command_line.c	\
				termcaps/termcaps_display_command_line.c		\
				termcaps/termcaps_isunicode.c					\
				termcaps/list_head.c							\
				termcaps/list_head_command.c					\
				termcaps/list_head_history.c					\
				termcaps/key__backspace.c						\
				termcaps/key__copy.c							\
				termcaps/key__cursor_to_begin_of_line.c			\
				termcaps/key__cursor_to_end_of_line.c			\
				termcaps/key__cursor_to_next_character.c		\
				termcaps/key__cursor_to_next_command.c			\
				termcaps/key__cursor_to_next_line.c				\
				termcaps/key__cursor_to_next_word.c				\
				termcaps/key__cursor_to_prev_character.c		\
				termcaps/key__cursor_to_prev_command.c			\
				termcaps/key__cursor_to_prev_line.c				\
				termcaps/key__cursor_to_prev_word.c				\
				termcaps/key__cut.c								\
				termcaps/key__cut_to_end_of_line.c				\
				termcaps/key__delete_command_line.c				\
				termcaps/key__delete_under_cursor.c				\
				termcaps/key__paste.c							\
				termcaps/key__select.c							\
				termcaps/key__send.c							\
				termcaps/key__share.c							\
				termcaps/key__share_words.c						\
				termcaps/key__completion.c						\
				termcaps/key__ctrl_c.c							\
				termcaps/key__clear.c							\
				termcaps/key__search_history.c					\
				termcaps/termcaps_history_search.c				\
				termcaps/termcaps_write.c						\

# ---------------------------------------------------------------------------- #
# PROJECT CONFIGURATION
# ---------------------------------------------------------------------------- #

CFLAGS		=	\
				-g 								\
				-Wall -Wextra -Werror			\

# >>> REQUIRED FOR LIBRARIES >>> THINK ABOUT CHANGING THE *LIBS rules

CPPFLAGS	=	\
				-I $(DIRINC)					\
				-I $(DIRINCCAPS)				\
				-I $(DIRINCBLTIN)				\
				-I $(DIRLIB)libft/$(DIRINC)		\
				-I $(DIRLIB)logger/$(DIRINC)	\
				-I $(DIRLIB)libcaps/$(DIRINC)	\

LDFLAGS		=	\
				-L $(DIRLIB)logger				\
				-L $(DIRLIB)libcaps				\
				-L $(DIRLIB)libft				\

LDLIBS		=	\
				-llogger						\
				-lcaps							\
				-lft							\
				-lncurses						\

# GLOBAL SETUP
AR			=	ar
CC			=	clang
RM			=	rm
MKDIR		=	mkdir
MAKE		=	make

DIRSRC		=	./srcs/
DIROBJ		=	./.objs/
DIRINC		=	./incs/
DIRINCCAPS	=	./incs/termcaps/
DIRINCBLTIN	=	./incs/builtins/
DIRLIB		=	./libs/
DIRTST		=	./test/

# EXTRA COLOR
C_DFL		=	\033[0m
C_GRA		=	\033[30m
C_RED		=	\033[31m
C_GRE		=	\033[32m
C_YEL		=	\033[33m
C_BLUE		=	\033[34m
C_MAG		=	\033[35m
C_CYA		=	\033[36m
C_WHI		=	\033[37m

# ============================================================================ #

# ---------------------------------------------------------------------------- #
# SOURCES NORMALIZATION
# ---------------------------------------------------------------------------- #

SRC			=	$(addprefix $(DIRSRC), $(SRCS))
OBJ			=	$(addprefix $(DIROBJ), $(notdir $(SRC:.c=.o)))

# ---------------------------------------------------------------------------- #
# RULES
# ---------------------------------------------------------------------------- #

all			:	libs $(NAME)
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) build completed\n" "$(MAKE)"

$(NAME)		:	$(DIROBJ) $(OBJ)
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) linking objects\n" "$(CC)"
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

# ---------------------------------------------------------------------------- #
# CUSTOMISABLE RULES

libs		:
	@make -C $(DIRLIB)libft
	@make -C $(DIRLIB)logger
	@make -C $(DIRLIB)libcaps

fcleanlibs	:
	@make -C $(DIRLIB)libft fclean
	@make -C $(DIRLIB)logger fclean
	@make -C $(DIRLIB)libcaps fclean

test		:	re
	@cd $(DIRTST) && sh 42ShellTester.sh $$PWD/../$(NAME) --hard

submodule	:
	@git submodule init && git submodule update
	@git submodule foreach git pull origin master

norme		:
	@/usr/bin/norminette -R CheckTopCommentHeader	\
		$$(find * -name "*.[ch]" ! -path "libs/logger/*" ! -path "test/*")

# ---------------------------------------------------------------------------- #

clean		:
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) remove objects\n" "$(RM)"
	@$(RM) -rf $(DIROBJ)

fclean		:	clean
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) remove binaries\n" "$(RM)"
	@$(RM) -f $(NAME)

re			:	fclean all

$(DIROBJ)	:
	@$(MKDIR) -p $(DIROBJ)

depend		:
	@sed -e '/^#start/,/^end/d' Makefile > .mftmp && mv .mftmp Makefile
	@printf "#start\n\n" >> Makefile
	@$(foreach s, $(SRC),													\
		printf '$$(DIROBJ)'										>> Makefile	&& \
		$(CC) -MM $(s) $(CPPFLAGS)								>> Makefile	&& \
																			\
		printf '\t\t@printf "$$(C_GRE)[ $(NAME) ] '				>> Makefile && \
		printf '[ %%-6s ]$$(C_DFL) " "$(CC)"\n'					>> Makefile && \
		printf '\t\t@printf "compiling $(s)\\n"\n'				>> Makefile	&& \
																			\
		printf '\t\t@$$(CC) -c $(s) -o '						>> Makefile	&& \
		printf '$(addprefix $(DIROBJ), $(notdir $(s:.c=.o))) '	>> Makefile	&& \
		printf '$$(CPPFLAGS) $$(CFLAGS) \n\n'					>> Makefile	&& \
																			\
		printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) " "dep"				&& \
		printf "$(s) rule generated\n"										|| \
																			\
		(sed -e '/^#start/,$$d' Makefile > .mftmp && mv .mftmp Makefile		&& \
		printf "#start\n\n"										>> Makefile	&& \
		printf "$(C_RED)[ $(NAME) ] [ %-6s ]$(C_DFL) " "dep"				&& \
		printf "$(s) rule generation failed\n"								) \
	;)
	@printf "\n#end\n" >> Makefile

.PHONY	:	 libs test


# ---------------------------------------------------------------------------- #
# AUTO-GENERATED SECTION - do not modify
# ---------------------------------------------------------------------------- #

#start

#end
