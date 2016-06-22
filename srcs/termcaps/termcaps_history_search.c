#include "shell.h"

int						termcaps_history_search(t_termcaps_context *context,
												t_buffer *out_match)
{
	t_list_node_history	*history;
	t_list				*pos;
	char				command_line_cur[2048];
	size_t				command_line_cur_size;
	size_t				history_offset;

	out_match->size = 0;
	out_match->bytes = NULL;
	if (context->command_line.size > context->prompt.size)
	{
		ASSERT(list_head__command_line_to_buffer(&context->command_line,
												sizeof(command_line_cur) - 1,
												&command_line_cur_size,
												 command_line_cur));
		command_line_cur[command_line_cur_size] = 0;
		history_offset = context->history.offset;
		pos = list_nth(&context->history.list, history_offset + 1);
		while ((pos = pos->prev) && pos != &context->history.list)
		{
			history = CONTAINER_OF(pos, t_list_node_history, list);
			if (ft_strstr(history->command_line.bytes,
						command_line_cur +
						context->prompt.size))
			{
				out_match->size = history->command_line.size;
				out_match->bytes = history->command_line.bytes;
				context->history.offset = history_offset;
				return (1);
			}
			history_offset--;
		}
	}
	return (0);
}
