/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduran-m <vduran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:34:37 by vduran-m          #+#    #+#             */
/*   Updated: 2025/06/08 12:57:43 by vduran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl	*ft_splitnode(t_gnl*lst, char *nl)
{
	t_gnl			*new;
	unsigned int	i;

	if (lst == NULL || nl == NULL)
		return (NULL);
	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	i = 0;
	nl++;
	while (nl[i] != '\0')
	{
		(new->buf)[i] = nl[i];
		if (i == 0)
			nl[i] = '\0';
		i++;
	}
	(new->buf)[i] = '\0';
	return (new);
}

char	*ft_list_to_string(t_gnl*lst)
{
	size_t	len;
	size_t	i;
	size_t	j;
	t_gnl	*lstcpy;
	char	*string;

	lstcpy = lst;
	len = ft_lstlen(lst);
	if (len <= 0)
		return (ft_lstreset(lstcpy));
	string = malloc(sizeof(*string) * (len + 1));
	if (string == NULL)
		return (ft_lstreset(lstcpy));
	lst = lstcpy;
	i = 0;
	while (lst != NULL && i < len)
	{
		j = 0;
		while ((lst->buf)[j] != '\0')
			string[i++] = (lst->buf)[j++];
		lst = lst->next;
	}
	string[i] = '\0';
	ft_lstreset(lstcpy);
	return (string);
}

void	ft_gnl_check(char **nl, t_gnl**start, t_gnl*lst)
{
	*nl = NULL;
	*start = NULL;
	if (lst != NULL)
	{
		*start = lst;
		*nl = ft_strchr(lst->buf, '\n');
	}
}

int	ft_extend_list_and_move_lst(t_gnl**lst, t_gnl**start)
{
	t_gnl	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		ft_lstreset(*start);
		return (0);
	}
	new->next = NULL;
	if (*lst == NULL)
		*start = new;
	else
		(*lst)->next = new;
	*lst = new;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl	*lst;
	t_gnl			*start;
	char			*nl;
	ssize_t			red;

	red = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_gnl_check(&nl, &start, lst);
	while (nl == NULL && red > 0)
	{
		if (ft_extend_list_and_move_lst(&lst, &start) == 0)
			return (NULL);
		red = read(fd, lst->buf, BUFFER_SIZE);
		if (red < 0)
		{
			lst = NULL;
			return (ft_lstreset(start));
		}
		(lst->buf)[red] = '\0';
		nl = ft_strchr(lst->buf, '\n');
	}
	lst = ft_splitnode(lst, nl);
	return (ft_list_to_string(start));
}
/*
int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc > 1)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening file");
            return (1); // Return error code
        }
    }
    else
    {

        fd = 0; // stdin file descriptor is 0
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    if (fd != 0)
        close(fd);

    return (0);
}
*/