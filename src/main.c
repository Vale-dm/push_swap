/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduran-m <vduran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:53:07 by vduran-m          #+#    #+#             */
/*   Updated: 2025/07/17 18:25:04 by vduran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_stack **stack_a, t_stack **stack_b, int stack_size)
{
	if (stack_size == 2 && !is_sorted(*stack_a))
		do_sa(stack_a);
	else if (stack_size == 3)
		tiny_sort(stack_a);
	else if (stack_size > 3 && !is_sorted(*stack_a))
		sort(stack_a, stack_b);
}

char	*join_all_args(int ac, char **av)
{
	int		i;
	char	*joined;
	char	*tmp;

	i = 0;
	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	while (i < ac)
	{
		tmp = ft_strjoin(joined, av[i]);
		free(joined);
		joined = tmp;
		if (!joined)
			return (NULL);
		if (i++ < ac - 1)
		{
			tmp = ft_strjoin(joined, " ");
			free(joined);
			joined = tmp;
			if (!joined)
				return (NULL);
		}
	}
	return (joined);
}

char	**join_args(int ac, char **av)
{
	char	*joined;
	char	**split;

	joined = join_all_args(ac, av);
	if (!joined)
		return (NULL);
	split = ft_split(joined, ' ');
	free(joined);
	return (split);
}

int	prepare_validate(int ac, char **av, char ***args)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '\0')
		{
			write(2, "Error\n", 6);
			return (0);
		}
		i++;
	}
	*args = join_args(ac - 1, av + 1);
	if (!(*args) || !is_correct_input(*args))
	{
		free_args(*args);
		write(2, "Error\n", 6);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**args;
	int		stack_size;

	stack_a = NULL;
	stack_b = NULL;
	if (ac < 2)
		return (0);
	if (only_spaces_args(ac, av))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (!prepare_validate(ac, av, &args))
		return (0);
	stack_a = fill_stack_values(ft_count_args(args), args);
	free_args(args);
	stack_size = get_stack_size(stack_a);
	assign_index(stack_a, stack_size + 1);
	push_swap(&stack_a, &stack_b, stack_size);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
