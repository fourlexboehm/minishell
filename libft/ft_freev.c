#include "libft.h"

//freev(ptr, N, TRUE); /* if known length */
//freev(ptr, -1, TRUE); /* if NULL-terminated */
//freev(ptr, -1, FALSE); /* to keep array */


void ft_freev(void **ptr, int len, bool free_seg)
{
	if (len < 0)
		while (*ptr)
		{
			free(*ptr);
			*ptr++ = NULL;
		}
	else
		while (len)
		{
			free(ptr[len]);
			ptr[len--] = NULL;
		}
	if (free_seg)
		free(ptr);
}
