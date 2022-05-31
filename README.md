# Minishell

### TODO
fix enter new ✔️
fix echo $? ✔️
add signal for ctrl+

//fix cat without arguments x86

fix cd

add unset path

### Bugs

test for memory leaks with:
valgrind --track-origins=yes --leak-check=full --supressions=./valgrind_filter.supp ./minishell