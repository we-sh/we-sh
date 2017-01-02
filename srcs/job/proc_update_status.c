#include "shell.h"

/*
** This function saves the status of a process retrieved through
** the function `waitpid`.
**
** If the process has terminated and its standard input is piped
** with a standard output, a signal SIGUSR1 is sent to the previous
** process to tell him to close its standard output.
** Please refer to the file `signal_sigusr1.c`
*/

static void	s_send_sigusr1(t_proc *p)
{
	int		wait_i;

	wait_i = 0;
	while (wait_i < 10000000)
		wait_i++;
	kill(CONTAINER_OF(p->list_proc.prev, t_proc, list_proc)->pid, SIGUSR1);
}

static void	s_set_flags(t_job *j, t_proc *p, int const status)
{
	p->exit_status = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
		p->stopped = WSTOPSIG(status);
	else
	{
		p->stopped = 0;
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			p->completed = 1;
			if (WIFSIGNALED(status))
				p->signaled = WTERMSIG(status);
			if (p->signaled == SIGINT)
				j->is_interrupted = p->signaled;
			if (p != CONTAINER_OF(j->proc_head.next, t_proc, list_proc))
				s_send_sigusr1(p);
		}
	}
	if (job_is_stopped(j) == 1 && job_is_completed(j) == 0)
	{
		j->foreground = 0;
		j->notified = 0;
	}
}

int			proc_update_status(t_job *j, pid_t pid, int status)
{
	t_proc		*p;

	if (pid == 0 || errno == ECHILD)
	{
		errno = 0;
		return (-1);
	}
	else if (pid < 0)
		return (-1);
	if ((p = proc_find(pid)) != NULL)
	{
		s_set_flags(j, p, status);
		return (0);
	}
	return (-1);
}
