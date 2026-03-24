/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduran-m <vduran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:54:56 by vduran-m          #+#    #+#             */
/*   Updated: 2025/07/15 17:13:33 by vduran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_number(const char **str, int sign)
{
	long long	num;

	num = 0;
	if (**str < '0' || **str > '9')
		return (0);
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		(*str)++;
		if (sign == 1 && num > INT_MAX)
			return (0);
		if (sign == -1 && (-num) < INT_MIN)
			return (0);
	}
	return (1);
}

int	check_int_range(const char *str)
{
	int	sign;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}
	else
	{
		sign = 1;
	}
	if (!parse_number(&str, sign))
		return (0);
	if (*str != '\0')
		return (0);
	return (1);
}

t_stack	*fill_stack_values(int ac, char **av)
{
	t_stack		*stack_a;
	int			nb;
	int			i;

	stack_a = NULL;
	i = 0;
	while (i < ac)
	{
		if (!check_int_range(av[i]))
			exit_error(&stack_a, NULL);
		nb = ft_atoi(av[i]);
		if (i == 0)
			stack_a = stack_new(nb);
		else
			stack_add_bottom(&stack_a, stack_new(nb));
		i++;
	}
	return (stack_a);
}

void	assign_index(t_stack *stack_a, int stack_size)
{
	t_stack	*ptr;
	t_stack	*highest;
	int		value;

	while (--stack_size > 0)
	{
		ptr = stack_a;
		value = INT_MIN;
		highest = NULL;
		while (ptr)
		{
			if (ptr->value == INT_MIN && ptr->index == 0)
				ptr->index = 1;
			if (ptr->value > value && ptr->index == 0)
			{
				value = ptr->value;
				highest = ptr;
				ptr = stack_a;
			}
			else
				ptr = ptr->next;
		}
		if (highest != NULL)
			highest->index = stack_size;
	}
}
