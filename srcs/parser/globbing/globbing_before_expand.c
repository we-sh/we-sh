#include <shell.h>

static char			*s_globbing_increment_range(unsigned char range_start,
												unsigned char range_end,
												int len)
{
	char			*new_value;
	char			tmp_start;
	int				j;

	j = 0;
	tmp_start = range_start;
	if ((new_value = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (tmp_start <= range_end)
	{
		if (tmp_start)
		{
			new_value[j] = tmp_start;
			j++;
		}
		tmp_start++;
	}
	new_value[j] = '\0';
	return (new_value);
}

static int			s_concat_expand_range(t_tmp **concat,
											char *new_value,
											int i)
{
	char			*tmp_value;

	if (i > 0)
	{
		if ((tmp_value = ft_strnew(i)) == NULL)
			return (ST_MALLOC);
		tmp_value = ft_strncpy(tmp_value, (*concat)->value, i);
		free((*concat)->value);
		if (((*concat)->value = ft_strjoin(tmp_value, new_value)) == NULL)
			return (ST_MALLOC);
		free(tmp_value);
	}
	else
	{
		free((*concat)->value);
		if (((*concat)->value = ft_strdup(new_value)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

static int			s_globbing_expand_range(t_tmp **concat, int i, int *len)
{
	unsigned char	range_start;
	unsigned char	range_e;
	char			*new_value;

	range_start = (*concat)->value[i];
	range_e = (*concat)->value[i + 2];
	*len = range_e - range_start;
	if (*len <= 0)
		return (-1);
	else
	{
		if ((new_value = s_globbing_increment_range(range_start, range_e, *len))
			== NULL)
			return (ST_MALLOC);
	}
	if (s_concat_expand_range(concat, new_value, i) == ST_MALLOC)
		return (ST_MALLOC);
	free(new_value);
	return (ST_OK);
}

int					globbing_before_expand(t_tmp **concat, int i, int len)
{
	char			*tmp_value_after_range;
	char			*tmp_concat_value;
	int				ret;

	if ((tmp_value_after_range = ft_strdup((*concat)->value + i + 3)) == NULL)
		return (ST_MALLOC);
	if ((ret = s_globbing_expand_range(concat, i, &len)) != -1)
	{
		if (ret == ST_MALLOC)
			return (ST_MALLOC);
		if ((tmp_concat_value = ft_strdup((*concat)->value)) == NULL)
			return (ST_MALLOC);
		free((*concat)->value);
		if (((*concat)->value =
			ft_strjoin(tmp_concat_value, tmp_value_after_range)) == NULL)
			return (ST_MALLOC);
		free(tmp_concat_value);
		len = ft_strlen((*concat)->value);
		i += ret;
	}
	free(tmp_value_after_range);
	return (ST_OK);
}
