#include "s_shell.h"

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @t: size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t t)
{

	if (*lineptr == NULL)
	{
		if  (t > BUFSIZE)
			*n = t;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < t)
	{
		if (t > BUFSIZE)
			*n = t;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int s;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		s = read(STDIN_FILENO, &t, 1);
		if (s == -1 || (s == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (s == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (s != 0)
		input = 0;
	return (retval);
}
