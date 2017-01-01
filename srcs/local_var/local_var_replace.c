#include "shell.h"

static char		*s_replace_from_local(t_var *ptr, char *tmp)
{
	while (ptr)
	{
		if (ft_strcmp(tmp, ptr->key) == 0)
		{
			free(tmp);
			if (ptr->value)
				return (ft_strdup(ptr->value));
		}
		ptr = ptr->next;
	}
	return (NULL);
}

static char		*s_local_var_replace_loop(t_sh *sh, char *input, int *i)
{
	t_var		*ptr;
	int			pos;
	char		*tmp;
	char		*value;

	pos = 0;
	ptr = sh->local_vars;
	while (ft_isalnum(input[pos]) || input[pos] == '_')
		pos++;
	if ((tmp = ft_strnew(pos)) == NULL)
		return (NULL);
	tmp = ft_strncpy(tmp, input, pos);
	*i = *i + pos;
	if ((value = (s_replace_from_local(ptr, tmp))) != NULL)
		return (value);
	else if ((value = env_get(sh->envp, tmp)) != NULL)
	{
		free(tmp);
		return (ft_strdup(value));
	}
	free(tmp);
	return (ft_strnew(0));
}

static int		s_local_var_replace_out_of_loop(char *input, char **output,
												int i, int i2)
{
	if (i2 != i)
	{
		if (local_var_concat(output, input + i2, i - i2) != ST_OK)
			return (ST_MALLOC);
	}
	else if (i == 0)
	{
		if ((*output = ft_strnew(0)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

static int		s_replace_char_or_loop(t_sh *sh, char *input,
										char **output, int *i)
{
	char		*tmp;
	int			ret;

	if (input[*i + 1] == '$' || input[*i + 1] == '?')
	{
		if (input[*i + 1] == '$')
			ret = sh->pgid;
		else
			ret = sh->last_exit_status;
		if ((tmp = ft_itoa(ret)) == NULL)
			return (ST_MALLOC);
		*i += 1;
	}
	else if ((tmp = s_local_var_replace_loop(sh, input + *i + 1, i)) == NULL)
		return (ST_MALLOC);
	if (local_var_concat(output, tmp, ft_strlen(tmp)) != ST_OK)
		return (ST_MALLOC);
	free(tmp);
	return (ST_OK);
}

static int		s_is_inhibited(char *start, char *c)
{
	int		odd;

	odd = 0;
	while (c != start)
	{
		c--;
		if (c[0] != '\\')
			return (odd);
		odd = (odd == 0) ? 1 : 0;
	}
	return (odd);
}

int				local_var_replace(t_sh *sh, char *input, char **output)
{
	int			i;
	int			i2;

	i = 0;
	i2 = 0;
	while (input[i])
	{
		if (input[i] == '$' && s_is_inhibited(input, input + i) == 0)
		{
			if (i2 != i)
			{
				if (local_var_concat(output, input + i2, i - i2) != ST_OK)
					return (ST_MALLOC);
			}
			if ((s_replace_char_or_loop(sh, input, output, &i)) != ST_OK)
				return (ST_MALLOC);
			i++;
			i2 = i;
		}
		else
			i++;
	}
	if ((s_local_var_replace_out_of_loop(input, output, i, i2)) == ST_MALLOC)
		return (ST_MALLOC);
	return (ST_OK);
}
