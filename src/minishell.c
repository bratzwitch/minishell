#include "../include/minishell.h"

/* The signal handler should not access or modify the main data structures of your program.
	This is because signal handlers can interrupt your program at any point,
	potentially causing data corruption or inconsistent states if they modify shared data. */

volatile sig_atomic_t received_sig = 0;

char *ft_prompt(t_prompt *prompt)
{
	char *input;

	input = NULL;
	if (isatty(STDIN_FILENO)) // isatty - test whether a file descriptor refers to a terminal
		input = readline("minishell$>");
	if (input == NULL) // detect EOF; handle ctrl+D
	{
		ft_putendl_fd("Vp*zdu brother.(remove once done)", 1);
		free(prompt->path);
		ft_free(prompt->env_copy);
		rl_clear_history();
		exit(received_sig);
	}
	return (input);
}

int save_stdinout(int *fdin_copy, int *fdout_copy)
{
	if (fdin_copy && ((*fdin_copy = dup(STDIN_FILENO)) == -1))
	{
		perror("Error redirecting input.");
		close(*fdin_copy);
		return (-1);
	}
	if (fdout_copy && ((*fdout_copy = dup(STDOUT_FILENO)) == -1))
	{
		perror("Error redirecting input.");
		close(*fdout_copy);
		return (-1);
	}
	return (0);
}

void restore_stdinout(int *fdin_copy, int *fdout_copy)
{
	if (fdin_copy)
	{
		if (dup2(*fdin_copy, STDIN_FILENO) == -1)
			perror("dup2 fdin");
		close(*fdin_copy);
	}
	if (fdout_copy)
	{
		if (dup2(*fdout_copy, STDOUT_FILENO) == -1)
			perror("dup2 fdout");
		close(*fdout_copy);
	}
}

void handle_single_cmd(t_prompt *prompt)
{
	pid_t pid;
	pid = 0;
	int fdin_copy;
	int fdout_copy;

	if (save_stdinout(&fdin_copy, &fdout_copy) == -1)
		return;
	received_sig = builtins(prompt, prompt->token_lst, prompt->env_copy);
	if (!received_sig || received_sig == 1)
	{
		restore_stdinout(&fdin_copy, &fdout_copy);
		return;
	}
	else if (!(prompt->path = validator(prompt->token_lst->value)) && !(ft_is_special_character(prompt->input)))
	{
		printf("minishell: command not found: %s\n", prompt->token_lst->value);
		restore_stdinout(&fdin_copy, &fdout_copy);
		return;
	}
	else
	{
		pid = create_child_process();
		if (pid == 0)
			handle_child_process(prompt, prompt->env_copy);
		else
			handle_parent_process(pid, &prompt->exit_status, prompt);
	}
	free(prompt->path);
	restore_stdinout(&fdin_copy, &fdout_copy);
}

int main(int argc, char **argv, char **env)
{
	t_prompt prompt;

	(void)argc;
	(void)argv;

	prompt.path = NULL;
	prompt.env_copy = copy_env(env);
	setup_handlers();
	while (1)
	{
		if (!(prompt.input = ft_prompt(&prompt)))
			break;
		if ((prompt.token_lst = lexer(prompt.input)))
		{
			if (is_pipe(prompt.token_lst))
				piping(&prompt);
			else
				handle_single_cmd(&prompt);
		}
		add_history(prompt.input);
		free(prompt.input);
		lst_cleanup(&prompt.token_lst, free_token);
	}
	return (0);
}

// A lexer, short for lexical analyser.

// Readline and Terminal Handling
// readline(prompt): Reads a line of input from the user,
//	displaying the given prompt. Allows for command-line editing and history navigation.
// rl_clear_history(): Clears the history of commands stored by readline.
// rl_on_new_line(): Updates the internal state of readline to indicate a new line has started (used with custom line-handling logic).
// rl_replace_line(text,
//	clear_undo): Replaces the current line in the readline buffer with text. If clear_undo is non-zero,
//	it clears the undo history.
// rl_redisplay(): Refreshes the readline display to show the current state of the input buffer.
// add_history(line): Adds a line to the readline history.

// Input/Output
// printf(format, ...): Formats and prints output to standard output (stdout).
// write(fd, buf, count): Writes count bytes from buf to the file descriptor fd.
// perror(message): Prints an error message to standard error (stderr) with the string corresponding to errno.
// strerror(errno): Returns a string describing the error code stored in errno.

// File Handling
// access(path, mode): Checks a file's accessibility (e.g., read, write,
// execute permissions) for the calling process.
// open(path, flags, mode): Opens a file with specified flags (e.g.,
// O_RDONLY) and mode (permissions, if created).
// read(fd, buf, count): Reads count bytes from file descriptor fd into buf.
// close(fd): Closes the file descriptor fd.

// Process Management
// fork(): Creates a new process by duplicating the calling process. The child process gets a return value of 0,
// and the parent gets the child's PID.
// wait(status): Waits for a child process to terminate and stores its exit status in status.
// waitpid(pid, status,
// options): Waits for a specific child process (identified by pid) to terminate.
// wait3(status, options, rusage): Like wait,
// but also retrieves resource usage statistics.
// wait4(pid, status, options, rusage): Like waitpid,
// but retrieves resource usage statistics.
// kill(pid, sig): Sends the signal sig to the process with the process ID pid.
// exit(status): Terminates the calling process with the given status.

// Signals
// signal(sig, handler): Sets a signal handler for signal sig.
// sigaction(sig, act,
// oldact): More advanced alternative to signal; allows for detailed signal handling.
// sigemptyset(set): Initializes a signal set to exclude all signals.
// sigaddset(set, sig): Adds a signal sig to a signal set.

// File and Directory Information
// stat(path, buf): Retrieves information about a file (e.g., size,
////permissions) and stores it in buf.
// lstat(path, buf): Like stat, but if the file is a symbolic link,
// it retrieves information about the link itself.
// fstat(fd, buf): Like stat, but works on an open file descriptor fd.
// unlink(path): Deletes a file (removes its directory entry).

// Working with Directories
// opendir(name): Opens a directory stream corresponding to the directory name.
// readdir(dirp): Reads the next directory entry from the directory stream dirp.
// closedir(dirp): Closes a directory stream.

// Environment Variables
// getenv(name): Retrieves the value of an environment variable by its name.

// Terminal Control
// isatty(fd): Checks if the file descriptor fd refers to a terminal device.
// ttyname(fd): Returns the name of the terminal associated with the file descriptor fd.
// ttyslot(): Returns the index of the terminal associated with the current process.
// ioctl(fd, request,
//...): Performs device-specific input/output control operations on fd.

// Terminal Settings
// tcsetattr(fd, optional_actions, termios_p): Sets terminal attributes for fd.
// tcgetattr(fd, termios_p): Retrieves the terminal attributes for fd.

// Termcap (Terminal Capability)
// tgetent(buffer,
// termtype): Loads the terminal capabilities database entry for termtype.
// tgetflag(capname): Checks if a terminal capability (boolean) is supported.
// tgetnum(capname): Retrieves the numeric value of a terminal capability.
// tgetstr(capname, area): Retrieves the string value of a terminal capability.
// tgoto(cap, col,
// row): Computes a cursor movement string based on terminal capabilities.
// tputs(str, affcnt, putc): Outputs a string with padding to the terminal.

/*  EXECVE
The execve function is indeed a system call,
	which is a special type of function.
	System Call: A system call is a function provided by the operating system that
	allows a program to request a service from the kernel.
Execve replaces the current process image with a new process image. whatever it means.
Prototype:
	int execve(const char *pathname, char *const argv[], char *const envp[]);
		pathname: The path to the binary executable file you want to execute (e.g.,
			/bin/ls).
		argv[]: An array of arguments passed to the program, where:
			argv[0] is typically the name of the program.
			The array must end with a NULL pointer.
		envp[]: An array of environment variables for the program,
			also terminated by a NULL pointer.
	Returns:
		On success: execve does not return (the process image is replaced).
		On failure: It returns -1 and sets errno.
*/