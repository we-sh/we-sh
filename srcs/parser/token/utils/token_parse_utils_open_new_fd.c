#include <sys/stat.h>
#include "parser.h"
#include "builtin_cd.h"

static int	s_check_symlink(char *f)
{
	t_stat			stat;
	int				status;
	char			*path;

	if ((path = ft_strdup(f)) == NULL)
		return (ST_MALLOC);
	if ((status = builtin_cd_chk_path(&path, 1)) == ST_OK)
	{
		status = ST_ENOENT;
		if (access(f, F_OK) == -1)
			status = ST_ENOENT;
		else if (access(path, X_OK) == -1)
			status = ST_EACCES;
		if (lstat(path, &stat) == 0)
		{
			if (S_ISDIR(stat.st_mode))
				status = ST_EISDIR;
		}
	}
	free(path);
	return (status);
}

int			token_parse_utils_open_new_fd(t_proc *p, char *f, int *fd, int flag)
{
	t_stat			stat;
	int				status;
	char			*path;
	int				ret;

	path = NULL;
	if ((ret = local_var_replace(p->sh, f, &path)) != ST_OK)
		return (ret);
	if ((*fd = open(path, flag, 0644)) < 0)
	{
		status = ST_ENOENT;
		if (access(path, F_OK) != -1 && access(path, X_OK) == -1)
			status = ST_EACCES;
		if (lstat(path, &stat) == 0)
		{
			if (S_ISDIR(stat.st_mode))
				status = ST_EISDIR;
			else if (S_ISLNK(stat.st_mode))
				status = s_check_symlink(f);
		}
		display_status(status, path, NULL);
		p->is_valid = -1;
	}
	free(path);
	return (ST_OK);
}
