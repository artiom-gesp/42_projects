/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:05:08 by agesp             #+#    #+#             */
/*   Updated: 2018/11/07 11:23:56 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int j;
	int k;

	j = 0;
	if (needle[0] == '\0')
		return (char *)(haystack);
	if (haystack[0] == '\0')
		return (0);
	while (haystack[j] != '\0')
	{
		k = 0;
		while (needle[k] != '\0' && needle[k] == haystack[j + k])
		{
			k++;
			if (!needle[k])
			{
				return (char*)&haystack[j];
			}
		}
		j++;
	}
	return (0);
}
