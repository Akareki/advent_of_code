
#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAP_SIZE 1000

typedef struct{
	int i;
	int j;
	int dir;
	int	heat;
} node;

void	lst_add_prio(t_list **list, node *curr_node)
{
	t_list *curr_elem;
	t_list *new_elem;

	new_elem = ft_lstnew(curr_node);
	if (!(*list))
	{
		*list = new_elem;
		return;
	}
	if (((node *)((*list)->content))->heat > curr_node->heat)
	{
		new_elem->next = *list;
		*list = new_elem;
		return;
	}
	curr_elem = *list;
	while (curr_elem->next && ((node *)curr_elem->next->content)->heat <= curr_node->heat)
		curr_elem = curr_elem->next;
	new_elem->next = curr_elem->next;
	curr_elem->next = new_elem;
}

int main(void) {
	int fd;
	char buf[100000];
	char **lines[5];
	char *tmp;
	int line;
	int	move = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int dir = 0;
	int heat = 0;
	int count = 0;
	t_list *nodes;
	node	*curr_node;
	node	*new_node;

	fd = open("day17_input.txt", O_RDONLY);
	read(fd, buf, 100000);
	while (i < 5)
	{
		lines[i] = ft_split(buf, '\n');
		i++;
	}
	nodes = NULL;
	curr_node = malloc(sizeof(node));
	curr_node->i = 0;
	curr_node->j = 0;
	curr_node->dir = 0;
	curr_node->heat = 0;
	lst_add_prio(&nodes, curr_node);
	curr_node = malloc(sizeof(node));
	curr_node->i = 0;
	curr_node->j = 0;
	curr_node->dir = 1;
	curr_node->heat = 0;
	lst_add_prio(&nodes, curr_node);
	while (nodes)
	{
		curr_node = (node *)nodes->content;
		dir = curr_node->dir;
		i = curr_node->i;
		j = curr_node->j;
		heat = curr_node->heat;
		if (lines[dir][i][j] != -1)
		{
			if (i == 140 && j == 140)
			{
				ft_printf("i : %d j : %d dir : %d heat : %d\n", i, j, dir, heat);
				return (0);
			}
			lines[dir][i][j] = -1;
			if (dir == 0 || dir == 2)
			{
				k = 1;
				while (k <= 3 && i - k >= 0)
				{
					heat += lines[4][i - k][j] - '0';
					new_node = malloc(sizeof(node));
					new_node->i = i - k;
					new_node->j = j;
					new_node->dir = 3;
					new_node->heat = heat;
					lst_add_prio(&nodes, new_node);
					k++;
				}
				k = 1;
				heat = curr_node->heat;
				while (k <= 3 && lines[dir][i + k])
				{
					heat += lines[4][i + k][j] - '0';
					new_node = malloc(sizeof(node));
					new_node->i = i + k;
					new_node->j = j;
					new_node->dir = 1;
					new_node->heat = heat;
					lst_add_prio(&nodes, new_node);
					k++;
				}
			}
			heat = curr_node->heat;
			if (dir == 1 || dir == 3)
			{
				k = 1;
				while (k <= 3 && j - k >= 0)
				{
					heat += lines[4][i][j - k] - '0';
					new_node = malloc(sizeof(node));
					new_node->i = i;
					new_node->j = j - k;
					new_node->dir = 2;
					new_node->heat = heat;
					lst_add_prio(&nodes, new_node);
					k++;
				}
				k = 1;
				heat = curr_node->heat;
				while (k <= 3 && lines[dir][i][j + k])
				{
					heat += lines[4][i][j + k] - '0';
					new_node = malloc(sizeof(node));
					new_node->i = i;
					new_node->j = j + k;
					new_node->dir = 0;
					new_node->heat = heat;
					lst_add_prio(&nodes, new_node);
					k++;
				}
			}
		}
		nodes = nodes->next;
	}
}
