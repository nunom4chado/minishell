# minishell

## Parser links
https://mywiki.wooledge.org/BashParser
https://aosabook.org/en/v1/bash.html


```
nuno@nm-tp-ws:~/Documents/minishell$ << a << b << 
en.subject.pdf  include/        minishell       src/
.git/           libft/          obj/            test
.gitignore      Makefile        README.md       
nuno@nm-tp-ws:~/Documents/minishell$ << a << b <<       c
> for a
> asdf
> a
> for b
> asdf
> b
> for c
> gdf
> a
> b
> c
nuno@nm-tp-ws:~/Documents/minishell$ << |
bash: syntax error near unexpected token `|'
nuno@nm-tp-ws:~/Documents/minishell$ << #
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ << %
> asdf
> %
nuno@nm-tp-ws:~/Documents/minishell$ << @
> asd
> @
nuno@nm-tp-ws:~/Documents/minishell$ export TEST=doc1
nuno@nm-tp-ws:~/Documents/minishell$ <<doc1
> for doc1
> $TEST
> "$TEST"
> doc1
nuno@nm-tp-ws:~/Documents/minishell$ ls << or
> afd
> or
en.subject.pdf  libft     minishell  README.md  test
include         Makefile  obj        src
nuno@nm-tp-ws:~/Documents/minishell$ ls <<a <<b
> for a
> b
> a
> for b
> sdf
> a
> b
en.subject.pdf  libft     minishell  README.md  test
include         Makefile  obj        src
nuno@nm-tp-ws:~/Documents/minishell$ ls <<a <<b
for a
b
a
for b
sdf
a
b
en.subject.pdf  libft     minishell  README.md  test
include         Makefile  obj        src
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | |
bash: syntax error near unexpected token `|'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | <<
> for o
> adsf
> o
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | <
> adf
> o
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola < o
bash: o: No such file or directory
nuno@nm-tp-ws:~/Documents/minishell$ echo ola < o |
> ls
bash: o: No such file or directory
en.subject.pdf  libft     minishell  README.md  test
include         Makefile  obj        src
nuno@nm-tp-ws:~/Documents/minishell$ echo <
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo <<
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola <<
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola | <<
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | <
> for o
> o
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | <
for o
o
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | |
bash: syntax error near unexpected token `|'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | >>
> for o
> o
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | >
> for o
> o
bash: syntax error near unexpected token `newline'
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | adsf
> for o
> o
bash: adsf: command not found
nuno@nm-tp-ws:~/Documents/minishell$ echo ola << o | |
bash: syntax error near unexpected token `|'
nuno@nm-tp-ws:~/Documents/minishell$ 
```