#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *save_list;
	t_list *save_next;

	save_list = *alst;
	save_next = save_list->next;
	while (save_next)
	{
		save_next = save_list->next;
		ft_lstdelone(&save_list, del);
		save_list = save_next;
	}
	*alst = NULL;
}
