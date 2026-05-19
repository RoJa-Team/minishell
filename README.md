# minishell

> *"As beautiful as a shell."*

A simple shell written in C, recreating the core behaviour of `bash`. Built as part of the 42 Lisboa common core curriculum.

![Language](https://img.shields.io/badge/language-C-blue.svg)
![School](https://img.shields.io/badge/42-Lisboa-000000.svg)
![Norm](https://img.shields.io/badge/norm-passing-success.svg)

---

## About

`minishell` is a project that introduces students to process creation, file descriptor manipulation, signal handling, and parsing. The goal is to build a working shell from scratch, capable of interpreting and executing commands much like `bash` would in interactive mode.

This implementation covers the mandatory part of the subject only.

## Features

- Interactive prompt that displays while waiting for input
- Working command history (via `readline`)
- Execution of binaries via absolute path, relative path, or `PATH` lookup
- Single quotes (`'`) that prevent interpretation of all metacharacters
- Double quotes (`"`) that prevent interpretation of metacharacters except `$`
- Environment variable expansion (`$VAR`) and exit status expansion (`$?`)
- Heredoc (`<<`) with delimiter
- I/O redirections: `<`, `>`, `>>`
- Pipes (`|`) chaining multiple commands together
- Signal handling that mimics `bash` in interactive mode:
  - `Ctrl-C` — displays a new prompt on a new line
  - `Ctrl-D` — exits the shell
  - `Ctrl-\` — does nothing

### Built-ins

| Command  | Description                                |
| -------- | ------------------------------------------ |
| `echo`   | Print arguments, supports `-n` flag        |
| `cd`     | Change directory (relative or absolute)    |
| `pwd`    | Print working directory                    |
| `export` | Set environment variables                  |
| `unset`  | Remove environment variables               |
| `env`    | Display the current environment            |
| `exit`   | Exit the shell with an optional status     |

## Build

Clone the repository and run `make`:

```sh
git clone https://github.com/<your-username>/minishell.git
cd minishell
make
```

### Makefile rules

| Rule       | Description                              |
| ---------- | ---------------------------------------- |
| `make`     | Compile the project                      |
| `make clean` | Remove object files                    |
| `make fclean` | Remove object files and the binary    |
| `make re`  | `fclean` followed by `make`              |

> Requires `readline`. On most Linux distributions, install it with your package manager (`libreadline-dev` on Debian/Ubuntu). On macOS, install it via Homebrew (`brew install readline`).

## Usage

Launch the shell:

```sh
./minishell
```

You will be greeted by a prompt:

```
minishell$
```

### Examples

```sh
minishell$ echo "Hello, $USER!"
Hello, joafern22!

minishell$ ls -la | grep minishell > result.txt

minishell$ cat << EOF
> line one
> line two
> EOF
line one
line two

minishell$ export FOO=bar
minishell$ echo $FOO
bar

minishell$ exit
```

## Project structure

```
minishell/
├── Makefile
├── includes/
│   └── minishell.h
├── libft/
├── srcs/
│   ├── builtins/
│   ├── execution/
│   ├── parsing/
│   ├── signals/
│   └── main.c
└── README.md
```

## Limitations

- Only the mandatory subset is implemented — no `&&`, `||`, parentheses, or wildcards.
- Backslash (`\`) and semicolon (`;`) are not interpreted as in `bash`.
- Unclosed quotes return an error instead of prompting for continuation.

## Authors

- [@<shishudy>](https://github.com/<username1>) 
- [@<joafern22>](https://github.com/<username2>)

Developed at [42 Lisboa](https://www.42lisboa.com/).
