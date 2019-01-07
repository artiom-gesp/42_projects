/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:30:55 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 16:38:01 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char swap_bits(unsigned char octet)
{
	unsigned char part_one;
	unsigned char part_two;

	part_one = octet << 4;
	part_two = octet >> 4;
	octet = (part_one | part_two);
	return (octet);
}
