#include "libft.h"

    void	*ft_realloc(void *ptr, size_t len)
    {
    	void	*real;

    	real = (void *)malloc(len);
    	if (real)
        {
            memset(real, 0, len);
    		memcpy(real, ptr, strlen(ptr));
        }
    	free(ptr);
    	return (real);
    }
