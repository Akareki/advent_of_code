#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_lens
{
	char	*label;
	int		focal;
} lens;

void	ft_list_remove_if_front(t_list **begin_list,
		void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *))
{
	t_list	*current_elem;
	t_list	*next_elem;

	current_elem = *begin_list;
	while (current_elem && cmp(current_elem->content, data_ref) == 0)
	{
		free_fct(current_elem->content);
		next_elem = current_elem->next;
		free(current_elem);
		current_elem = next_elem;
	}
	*begin_list = current_elem;
}

void	ft_list_remove_if(t_list **begin_list,
		void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *))
{
	t_list	*prev_elem;
	t_list	*current_elem;
	t_list	*next_elem;

	ft_list_remove_if_front(begin_list, data_ref, cmp, free_fct);
	if (!(*begin_list))
		return ;
	prev_elem = *begin_list;
	while (prev_elem->next)
	{
		current_elem = prev_elem->next;
		if (current_elem)
		{
			next_elem = current_elem->next;
			if (cmp(current_elem->content, data_ref) == 0)
			{
				free_fct(current_elem->content);
				free(current_elem);
				prev_elem->next = next_elem;
			}
			else
				prev_elem = current_elem;
		}
	}
}

int	label_cmp(void *content, void *ref)
{
	char *s1;
	char *s2;
	int	i = 0;

	s1 = ((lens *)content)->label;
	s2 = (char *)ref;
	while (ft_isalpha(s2[i]))
	{
		i++;
	}
	s2[i] = '\0';
	return (ft_strncmp(s1, s2, ft_strlen(s1)));

}

int	HASH(char *line)
{
	int i = 0;
	int	count = 0;

	while (line[i] && ft_isalpha(line[i]))
	{
		count += (int) line[i];
		count *= 17;
		count = count % 256;
		i++;
	}
	return (count);
}

int	focal(char *line)
{
	int	i = 0;

	while (line[i] && ft_isalpha(line[i]))
	{
		i++;
	}
	i++;
	return (ft_atoi(line + i));
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	int line;
	int	i = 0;
	int	count = 0;
	int	j = 0;
	t_list	*hashmap[256] = {0};
	t_list	*curr_lst;
	int		label_is_in;
	lens	*new_lens;

	fd = open("day15_input.txt", O_RDONLY);
	//fd = open("test.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, ',');
	while (lines[i])
	{
		if (ft_strnstr(lines[i], "-", ft_strlen(lines[i])))
		{
			ft_list_remove_if(&hashmap[HASH(lines[i])], lines[i], label_cmp, free);
		}
		label_is_in = 0;
		if (ft_strnstr(lines[i], "=", ft_strlen(lines[i])))
		{
			curr_lst = hashmap[HASH(lines[i])];
			while (curr_lst)
			{
				if (label_cmp(((lens *)curr_lst->content), lines[i]) == 0)
				{
					((lens *)curr_lst->content)->focal = focal(lines[i]);
					label_is_in = 1;
					break ;
				}
				curr_lst = curr_lst->next;
			}
			if (label_is_in == 0)
			{
				new_lens = ft_calloc(1, sizeof(lens));
				new_lens->label = ft_strdup(lines[i]);
				new_lens->focal = focal(lines[i]);
				j = 0;
				while (ft_isalpha(new_lens->label[j]))
					j++;
				new_lens->label[j] = '\0';
				ft_lstadd_back(&hashmap[HASH(lines[i])], ft_lstnew(new_lens));
			}
		}
		/*j = 0;
		while (j < 256)
		{
			if (hashmap[j])
			{
				curr_lst = hashmap[j];
				ft_printf("Box %d ", j);
				while (curr_lst)
				{
					ft_printf("[%s %d] ", ((lens *)curr_lst->content)->label, ((lens *)curr_lst->content)->focal);
					curr_lst = curr_lst->next;
				}
				write(1, "\n\n\n", 1);
			}
			j++;
		}
		write(1, "\n\n\n", 3);*/
		i++;
	}
	j = 0;
	count = 0;
	while (j < 256)
	{
		i = 1;
		curr_lst = hashmap[j];
		ft_printf("Box %d ", j);
		while (curr_lst)
		{
			ft_printf("[%s %d] ", ((lens *)curr_lst->content)->label, ((lens *)curr_lst->content)->focal);
			count += (j + 1) * i * ((lens *)curr_lst->content)->focal;
			curr_lst = curr_lst->next;
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
	ft_printf("Count : %d\n", count);
}
