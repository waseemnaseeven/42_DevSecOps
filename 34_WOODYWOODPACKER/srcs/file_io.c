#include "woody.h"

/*
** map_file — opens path read-only, mmaps the entire content.
** Prints error and returns NULL on failure.
*/
void    *map_file(const char *path, size_t *out_size)
{
    int         fd;
    struct stat st;
    void        *map;

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        dprintf(STDERR_FILENO,
            "Error: cannot open '%s'\n", path);
        return NULL;
    }
    // if fstat failed OR the file is too small to be an ELF, SELFMAG = 4 and ELF is 4bytes
    if (fstat(fd, &st) < 0 || st.st_size < (off_t)SELFMAG) {
        dprintf(STDERR_FILENO,
            "Error: file too small or stat failed\n");
        close(fd);
        return NULL;
    }
    map = mmap(NULL, (size_t)st.st_size, PROT_READ,
                MAP_PRIVATE, fd, 0);
    close(fd);
    if (map == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }
    *out_size = (size_t)st.st_size;
    return map;
}

/*
** write_woody — creates/overwrites "woody" with the packed binary.
** Sets permissions to 0755 so the result is executable.
*/
void    write_woody(void *buf, size_t size) {
    int     fd;
    ssize_t written;

    fd = open(WOODY_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (fd < 0) {
        perror("open woody");
        return;
    }
    written = write(fd, buf, size);
    if (written != (ssize_t)size)
        perror("write woody");
    close(fd);
}