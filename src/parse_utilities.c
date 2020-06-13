#include "rtv1.h"
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>

char				*read_file(const char *path, size_t *length)
{
    /*int fd;
    char *line;
    char *str;

    str = NULL;
    if ((fd = open(path, O_RDONLY)) < 0)
        return (NULL);

    while (get_next_line(fd, &line) > 0)
    {
        str = ft_append(str, line);
        free(line);
    }
    close(fd);
    return (str);
     */

    FILE *stream;
    char *contents;

//Open the stream. Note "b" to avoid DOS/UNIX new line conversion.
    stream = fopen(path, "rb");

//Seek to the end of the file to determine the file size
    fseek(stream, 0L, SEEK_END);
    *length = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

//Allocate enough memory (add 1 for the \0, since fread won't add it)
    contents = malloc(*length + 1);

//Read the file
    size_t size = fread(contents, 1, *length, stream);
    contents[size]=0; // Add terminating zero.

//Print it again for debugging

//Close the file
    fclose(stream);
    return (contents);
}