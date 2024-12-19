#include <stdio.h>
#include <stdlib.h>

void run() {
    const char *message = "Good... Wait what?\n";
    const char *command = "/bin/sh";

    fwrite(message, 19, 1, stdout);

    system(command);
}

int		main(void)
{
	char	buffer[80];

	gets(buffer);
	return (0);
}
