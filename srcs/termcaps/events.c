#include "shell.h"

#define EVENT_NOT_FOUND					"event not found"

static int	s_replace_event(t_termcaps_context *context,
							size_t buf_size_max,
							t_buffer *buf,
							size_t buf_offset)
{
	char		*pt;
	t_event		info;
	t_buffer	event;
	size_t		size_left;

	pt = buf->bytes + buf_offset;
	if (!event_info(&context->history, pt, &info) ||
		!history_get(&context->history, info.history_index, &event) ||
		!event_word(&info, &event))
	{
		termcaps_error(context, pt, info.token_size, EVENT_NOT_FOUND);
		return (0);
	}
	size_left = buf->size - buf_offset + info.token_size;
	if (buf_offset + event.size + size_left >= buf_size_max)
	{
		termcaps_error(context, "", 0, "Command line too big");
		return (0);
	}
	ft_memmove(pt + event.size, pt + info.token_size, size_left);
	ft_memcpy(pt, event.bytes, event.size);
	buf->size += event.size - info.token_size;
	buf->bytes[buf->size] = '\0';
	return (event.size);
}

static int	s_replace_command(t_termcaps_context *context,
							t_buffer *buf)
{
	termcaps_display_command(context);
	termcaps_write(context->fd, "\n", sizeof("\n") - 1);
	command_clear(&context->command);
	command_add_string(
			context->prompt.size, context->prompt.bytes, &context->command);
	command_add_string(buf->size, buf->bytes, &context->command);
	return (1);
}

static void	s_inib_teardown(t_inib *inib)
{
	inib[0].open = '\'';
	inib[0].close = '\'';
	inib[0].state = 0;
}

static int	s_inib(char c, t_inib *inib)
{
	size_t	i;

	if (!(i = 0) && c == '\\')
		return (1);
	while (i < TERMCAPS_INIB_COUNT)
	{
		if (inib[i].state == 1)
		{
			if (c == inib[i].close)
				inib[i].state = 0;
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < TERMCAPS_INIB_COUNT)
	{
		if (c == inib[i].open)
		{
			inib[i].state = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int			replace_events(t_termcaps_context *context,
							const size_t buf_size_max,
							t_buffer *buf)
{
	size_t	buf_offset;
	size_t	event_size;
	t_inib	inib[TERMCAPS_INIB_COUNT];

	s_inib_teardown(inib);
	event_size = 0;
	buf_offset = 0;
	while (buf_offset < buf->size)
	{
		if (!s_inib(buf->bytes[buf_offset], inib) &&
			buf->bytes[buf_offset] == '!' && buf_offset + 1 < buf->size &&
			!ft_isspace(buf->bytes[buf_offset + 1]))
		{
			if ((event_size =
				s_replace_event(context, buf_size_max, buf, buf_offset)) == 0)
				return (0);
			buf_offset += event_size;
		}
		buf_offset++;
	}
	return (event_size ? !s_replace_command(context, buf) : 1);
}
