
#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define WRKFLWS 60000
#define	INPUT "day19_input.txt"
#define T_INPUT "test.txt"

typedef struct{
	int	rel;
	char category;
	int basis;
	char *dest;
} workflow;

typedef struct{
	int x;
	int m;
	int a;
	int s;
	char *workflow;
} part;

int	hash(char *name)
{
	int	count = 0;
	int i = 0;

	while (ft_isalpha(name[i]))
	{
		count += (int)name[i];
		count *= 11677;
		count %= WRKFLWS;
		i++;
	}
	return (count);
}

int main(void) {
	int fd;
	char *buf;
	char **lines;
	char *tmp;
	int line;
	int	move = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	t_list	*workflows[WRKFLWS];
	workflow	*tmp_workflow;
	char		**raw_workflow;
	part		*tmp_part;
	char		**raw_part;
	int			passed = 0;
	t_list		*tmp_list;

	while (i < WRKFLWS)
	{
		workflows[i] = NULL;
		i++;
	}
	fd = open(INPUT, O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	i = 0;
	while (lines[i] && lines[i][0] != '{')
	{
		if (workflows[hash(lines[i])])
		{
			count++;
			ft_printf("CONFLICT\n");
			return (-1);
		}
		raw_workflow = ft_split(*(ft_split(lines[i], '{') + 1), ',');
		j = 0;
		while (raw_workflow[j])
		{
			tmp_workflow = malloc(sizeof(workflow));
			if (ft_strchr(raw_workflow[j], '}'))
			{
				*ft_strchr(raw_workflow[j], '}') = '\0';
				tmp_workflow->dest = ft_strdup(raw_workflow[j]);
				tmp_workflow->rel = 0;
				tmp_workflow->basis = 0;
				tmp_workflow->category = 'N';
			}
			else
			{
				tmp_workflow->category = raw_workflow[j][0];
				tmp_workflow->rel = (raw_workflow[j][1] == '<') - (raw_workflow[j][1] == '>');
				tmp_workflow->basis = ft_atoi(raw_workflow[j] + 2);
				tmp_workflow->dest = ft_strdup(ft_strchr(raw_workflow[j], ':') + 1);
			}
			ft_lstadd_back(&workflows[hash(lines[i])], ft_lstnew(tmp_workflow));
			j++;
		}
		i++;	
	}
	count = 0;
	while (lines[i])
	{
		raw_part = ft_split(ft_strtrim(lines[i], "{}"), ',');
		tmp_part = malloc(sizeof(part));
		tmp_part->x = ft_atoi(raw_part[0] + 2);
		tmp_part->m = ft_atoi(raw_part[1] + 2);
		tmp_part->a = ft_atoi(raw_part[2] + 2);
		tmp_part->s = ft_atoi(raw_part[3] + 2);
		tmp_part->workflow = "in";
		ft_printf("%s -> ", tmp_part->workflow);
		while (tmp_part->workflow[0] != 'R' && tmp_part->workflow[0] != 'A')
		{
			tmp_list = workflows[hash(tmp_part->workflow)];
			passed = 0;
			while (passed == 0)
			{
				tmp_workflow = (workflow *)tmp_list->content;
				passed = 1;
				if (tmp_workflow->rel == 0)
					tmp_part->workflow = ft_strdup(tmp_workflow->dest);
				else
				{
					if (tmp_workflow->category == 'x' && tmp_workflow->rel * tmp_part->x < tmp_workflow->rel * tmp_workflow->basis)
						tmp_part->workflow = ft_strdup(tmp_workflow->dest);
					else if (tmp_workflow->category == 'm' && tmp_workflow->rel * tmp_part->m < tmp_workflow->rel * tmp_workflow->basis)
						tmp_part->workflow = ft_strdup(tmp_workflow->dest);
					else if (tmp_workflow->category == 'a' && tmp_workflow->rel * tmp_part->a < tmp_workflow->rel * tmp_workflow->basis)
						tmp_part->workflow = ft_strdup(tmp_workflow->dest);
					else if (tmp_workflow->category == 's' && tmp_workflow->rel * tmp_part->s < tmp_workflow->rel * tmp_workflow->basis)
						tmp_part->workflow = ft_strdup(tmp_workflow->dest);
					else
					 	passed = 0;
				}
				tmp_list = tmp_list->next;
			}
			ft_printf("%s -> ", tmp_part->workflow);
		}
		ft_printf("\n");
		if (tmp_part->workflow[0] == 'A')
			count += tmp_part->x + tmp_part->m + tmp_part->a + tmp_part->s;
		i++;	
	}
	ft_printf("Count : %d\n", count);
}
