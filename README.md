# 1. Initial Setup
Set Up the Environment:

Create your project structure with directories for headers (includes) and source files (src).
Set up a Makefile with targets for NAME, all, clean, fclean, and re.
Choose Core Files:

main.c: Entry point for the shell.
parser.c: Handles input parsing.
executor.c: Manages command execution.
builtins.c: Implements built-in commands.
signals.c: Handles signal behaviour.
utils.c: Utility functions.
Initialise Key Structures:

Define structures to manage the environment variables, commands, and pipeline info.
# 2. Prompt and Command Loop
Display a Prompt:

Use readline() to display a prompt and capture user input.
Add the input to history with add_history().
Parse Input:

Tokenise the input to separate commands and arguments.
Identify quotes (' and "), redirections (<, >, <<, >>), pipes (|), and environment variables ($).
# 3. Command Parsing
Handle Quotes:

Process single quotes to prevent interpretation of metacharacters.
Process double quotes and expand $ variables inside them.
Identify Redirections:

Parse input for redirections:
< for input redirection.
> for output redirection.
>> for appending output.
<< for heredoc (stop reading when delimiter is found).
Parse Environment Variables:

Replace $ followed by a variable name with its value using getenv().
Manage Pipes:

Split the input into separate commands connected by pipes.
# 4. Execution
Handle Builtins:

Implement built-in commands (echo, cd, pwd, export, unset, env, exit).
Determine if the command is a builtin and execute it directly.
Execute External Commands:

Search for executables using the PATH environment variable.
Use execve() to execute commands.
Implement Redirections:

Redirect input/output using dup2() and file descriptors.
Open files for reading/writing based on redirection type.
Handle Pipes:

Create pipes using pipe() and manage input/output redirection between processes.
# 5. Signal Handling
Handle Signals:

Implement signal handlers for:
SIGINT (Ctrl+C): Interrupts and redisplays the prompt.
SIGQUIT (Ctrl+): Does nothing in interactive mode.
EOF (Ctrl+D): Exits the shell gracefully.
Use a single global variable to store the signal number.
Ignore Signals in Child Processes:

Ensure the signal handlers do not interfere with child processes.
# 6. History Management
Implement History:
Use readline’s add_history() to maintain command history.
Clear history on exit using rl_clear_history().
# 7. Environment Management
Environment Variables:

Use getenv() and setenv() to manage environment variables.
Implement the export, unset, and env builtins.
Special Variables:

Handle $? to store the exit status of the last executed command.
# 8. Memory Management
Prevent Leaks:

Ensure all dynamically allocated memory (e.g., token arrays, command structures) is freed properly.
Use valgrind or similar tools to check for memory leaks.
Readline Memory Leaks:

You don’t need to fix readline leaks but avoid introducing any in your code.
# 9. Testing and Debugging
Test Redirections and Pipes:

Ensure proper input/output handling with combinations of redirections and pipes.
Test Signals:

Verify correct handling of Ctrl+C, Ctrl+D, and Ctrl+\ in both interactive and non-interactive modes.
Test Builtins and Commands:

Compare behaviour with bash for all commands and builtins.
# 10. Final Checks
Follow Norm Rules:

Avoid global variables except for the one signal variable.
Ensure the code complies with your school’s norms.
Documentation:

Add comments to explain complex logic.
Include a clear README with instructions for compiling and using the shell.
Clean Makefile:

Ensure the Makefile compiles without errors and supports proper cleaning (clean, fclean).
