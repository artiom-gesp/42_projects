#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *save_list;
	t_list *save_next;

	save_list = lst;
	save_next = lst;
	if (lst)
		while (save_list)
		{
			save_next = save_list->next;
			(*f)(save_list);
			save_list = save_next;
		}
}
