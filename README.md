# Minishell

### TODO
fix enter new ✔️

fix echo $? ✔️

add signal for ctrl+ ✔️

add newline after cat ✔

fix cd  ✔️

add unset path ✔
### Bugs

test for memory leaks with:
valgrind --track-origins=yes --leak-check=full --supressions=./valgrind_filter.supp ./minishell
