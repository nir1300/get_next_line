# get_next_line

A C function that returns **one line at a time** from a file descriptor, built around a single static buffer that remembers what was read but not yet returned.

```c
char *get_next_line(int fd);
```

Written for the 42 curriculum. Allowed functions: `read`, `malloc`, `free`.

## Behavior

- Each call returns the next line, **including its trailing `\n`**. The last line has no `\n` if the file doesn't end with one.
- Returns `NULL` at end of file, on a read error, or on an invalid descriptor or `BUFFER_SIZE`.
- Works on regular files, pipes and standard input.
- Works with any `BUFFER_SIZE` (from 1 up to very large values).
- The bonus version reads from several file descriptors at once without mixing their state.

## Files

| File | Contents |
|------|----------|
| `get_next_line.c`, `get_next_line.h`, `get_next_line_utils.c` | mandatory version |
| `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c` | multi-descriptor version |

## How it works

State is kept in a static pointer `dest`: the text that has been read from the file but not yet handed back to the caller. Each call goes through three steps.

1. **`read_lines`** allocates a `BUFFER_SIZE + 1` buffer and calls `read()` in a loop, appending each chunk to `dest` with `ft_strjoin`. It stops as soon as the chunk contains a newline, or when `read()` returns a short count while data is available. If `read()` returns `0` (EOF) and `dest` is empty, there is nothing left, so everything is freed and `NULL` is returned. A negative return frees everything as well.
2. **`create_line`** allocates a string up to and including the first `\n` in `dest` and returns it as the result.
3. **`ft_remainder`** allocates a new string holding everything after that `\n`, frees the old `dest`, and stores the remainder for the next call. If nothing follows the newline, `dest` is freed and reset to `NULL`.

A small `ft_free` helper centralizes cleanup (and doubles as the "join and free the old string" step), so every error path releases both the stash and the read buffer.

Because the stash survives between calls and the line is cut out of it, a line that is longer than `BUFFER_SIZE`, or a buffer that contains several lines, are handled the same way: the extra data simply stays in the stash.

### Bonus: multiple file descriptors

The bonus version replaces the single pointer with one static array, `static char *dest[1024]`, indexed by file descriptor. Each descriptor has its own stash, so calls can alternate freely between descriptors (for example 3, 4, 5, 3, 4, ...) without losing each one's reading position. It still uses a single static variable, and descriptors from 0 to 1023 are supported.

## Build and use

Compile your own program together with the sources, with or without `-D BUFFER_SIZE=n` (the header defines a default):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

Example:

```c
int     fd = open("file.txt", O_RDONLY);
char    *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```
