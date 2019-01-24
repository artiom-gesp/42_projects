void	sort_three(t_push *a, t_push *b)
{
	if (get_nb_elem(b) == 1)
	{
		push(b, a, 1, 1);
		rotate(a, 1, 1);
		return ;
	}
	if (get_nb_elem(b) == 2)
	{
		if (is_sorted(b))
		{
			push(b, a, 1, 1);
		rotate(a, 1, 1);
			push(b, a, 1, 1);
		rotate(a, 1, 1);
		}
		else
		{
			swap(b, 1, 2);
			push(b, a, 1, 1);
		rotate(a, 1, 1);
			push(b, a, 1, 1);
		rotate(a, 1, 1);
		}
		return ;
	}
	if (get_nb_elem(b) == 20)
	{
		b = get_top_list(b);
/*cba*/	if (is_rev_sorted(b))
		{
			swap(b, 1, 2);
			rev_rotate(b, 1, 2);
		}
/*acb*/	else if (b->data < b->next->data && b->next->data > b->next->next->data
		&& b->data < b->next->next->data)
		{
			rev_rotate(b, 1, 2);
			swap(b, 1, 2);
		}
/*cab*/	else if (b->data > b->next->data && b->next->data < b->next->next->data
				&& b->data > b->next->next->data)
		{
			rotate(b, 1, 2);
		}
/*bac*/	else if (b->data > b->next->data  && b->next->data < b->next->next->data)
		{
			swap(b, 1, 2);
		}
/*bca*/	else if (b->data < b->next->data && b->next->data > b->next->next->data)
		{
			rev_rotate(b, 1, 2);
		}
		push(b, a, 1, 1);
		rotate(a, 1, 1);
		push(b, a, 1, 1);
		rotate(a, 1, 1);
		push(b, a, 1, 1);
		rotate(a, 1, 1);
	}
}

int		find_closest(t_push *b, int data, int i, int j)
{
	int first;
	int second;
	int third;
	t_push *c;
	t_push *d;

	i = 0;
	c = copy_pile(b, 1);
	d = copy_pile(b, 0);
	get_mediane(c, d, 0);
	c = get_top_list(c);
	while (c->data != data)
		rotate(c, 0, 0);
	if (get_nb_elem(c) > 20)
	{
	first = c->next->data;
	second = c->next->next->data;
	third = c->next->next->next->data;
	}
	else 
		return (0);
	b = get_top_list(b);
	while (b->data != first && b->next)
	{
		b = b->next;
		i++;
	}
	j = i;
	i = 0;
	b = get_top_list(b);
	while (b->data != second && b->next)
	{
		b = b->next;
		i++;
	}
	j = get_closest(i, j, get_list_len(b));
	b = get_top_list(b);
	i = 0;
	while (b->data != third && b->next)
	{
		b = b->next;
		i++;
	}
	j = get_closest(i, j, get_list_len(b));
	if ( 4 * j > get_list_len(b))
		return (2);
	return (1);
}


int		get_closest(int first, int second, int len)
{
	if (first <= len && second <= len)
		return (first < second ? first : second);
	else if (first < len && second > len)
		return (first < len - (second - len) ? first : second);
	else if (first > len && second < len)
		return (len - (first - len) < second ? first : second);
	return (first < second ? second : first);

}

