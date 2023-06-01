# get_next_line

> A function that reads a file descriptor line by line.

### Function prototype

```c
char *get_next_line(int fd);
```

The goal of *get_next_line* is to read a line from a **file descriptor**, such as a text file, and return it to the caller. It provides a convenient way to read and process large files line by line, without having to load the entire file into memory at once.

The function reads a specified number of characters at a time (*BUFFER_SIZE*) from the file descriptor until it encounters a **newline character ('\n')** or reaches the **end of the file (EOF)**. It then returns the line as a string to the caller. Subsequent calls to get_next_line() continue reading from where it left off, allowing for the sequential retrieval of lines from the file.

**get_next_line** involves dynamic memory allocation and management to handle lines of variable length. It handles different edge cases, such as handling multiple file descriptors simultaneously and managing file errors gracefully.

## Compiling

If you want to set a specific **BUFFER_SIZE** you will have to compile the function like so:
```zsh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
```