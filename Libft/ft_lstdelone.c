#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list *save_list;

	save_list = *alst;
	(*del)(save_list->content, save_list->content_size);
	free(save_list);
	*alst = NULL;
}
