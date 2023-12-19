
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
	int x_min;
	int x_max;
	int m_min;
	int m_max;
	int a_min;
	int a_max;
	int s_min;
	int s_max;
	char *workflow;
} t_part_range;

int	min(int a, int b)
{
	return ((a <= b) * a + (a > b) * b);
}

int	max(int a, int b)
{
	return ((a >= b) * a + (a < b) * b);
}

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

long long	follow_workflows(t_list *workflows[WRKFLWS], t_part_range part_range)
{
	t_list *list;
	workflow *tmp_workflow;
	long long count = 0;
	t_part_range new_part_range;

	ft_printf("xmin : %d xmax : %d\n", part_range.x_min, part_range.x_max);
	ft_printf("mmin : %d mmax : %d\n", part_range.m_min, part_range.m_max);
	ft_printf("amin : %d amax : %d\n", part_range.a_min, part_range.a_max);
	ft_printf("smin : %d smax : %d\n", part_range.s_min, part_range.s_max);
	if (part_range.workflow[0] == 'A')
	{
		ft_printf("workflow : %s\n", part_range.workflow);
		count = 1;
		count *= 1 + part_range.x_max - part_range.x_min;
		count *= 1 + part_range.m_max - part_range.m_min;
		count *= 1 + part_range.a_max - part_range.a_min;
		count *= 1 + part_range.s_max - part_range.s_min;
		printf("Count : %lld\n", count / 1000000000000);
		ft_printf("\n");
		return (count);
	}
	else if (part_range.workflow[0] == 'R')
	{
		ft_printf("workflow : %s\n", part_range.workflow);
		return (0);
	}
	list = workflows[hash(part_range.workflow)];
	while (list)
	{
		ft_printf("workflow : %s\n", part_range.workflow);
		tmp_workflow = (workflow *)list->content;
		if (tmp_workflow->rel == 0)
		{
			new_part_range = part_range;
			new_part_range.workflow = ft_strdup(tmp_workflow->dest);
			count += follow_workflows(workflows, new_part_range);
		}
		if (tmp_workflow->rel == 1)
		{
			if (tmp_workflow->category == 'x' && tmp_workflow->basis > part_range.x_min && tmp_workflow->basis < part_range.x_max)
			{
				new_part_range = part_range;
				new_part_range.x_max = min(new_part_range.x_max, tmp_workflow->basis - 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.x_min = tmp_workflow->basis;
			}
			if (tmp_workflow->category == 'm' && tmp_workflow->basis > part_range.m_min && tmp_workflow->basis < part_range.m_max)
			{
				new_part_range = part_range;
				new_part_range.m_max = min(new_part_range.m_max, tmp_workflow->basis - 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.m_min = tmp_workflow->basis;
			}
			if (tmp_workflow->category == 'a' && tmp_workflow->basis > part_range.a_min && tmp_workflow->basis < part_range.a_max)
			{
				new_part_range = part_range;
				new_part_range.a_max = min(new_part_range.a_max, tmp_workflow->basis - 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.a_min = tmp_workflow->basis;
			}
			if (tmp_workflow->category == 's' && tmp_workflow->basis > part_range.s_min && tmp_workflow->basis < part_range.s_max)
			{
				new_part_range = part_range;
				new_part_range.s_max = min(new_part_range.s_max, tmp_workflow->basis - 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.s_min = tmp_workflow->basis;
			}
		}
		if (tmp_workflow->rel == -1)
		{
			if (tmp_workflow->category == 'x' && tmp_workflow->basis > part_range.x_min && tmp_workflow->basis < part_range.x_max)
			{
				new_part_range = part_range;
				new_part_range.x_min = max(new_part_range.x_min, tmp_workflow->basis + 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.x_max = tmp_workflow->basis;
			}
			if (tmp_workflow->category == 'm' && tmp_workflow->basis > part_range.m_min && tmp_workflow->basis < part_range.m_max)
			{
				new_part_range = part_range;
				new_part_range.m_min = max(new_part_range.m_min, tmp_workflow->basis + 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.m_max = tmp_workflow->basis;
			}
			if (tmp_workflow->category == 'a' && tmp_workflow->basis > part_range.a_min && tmp_workflow->basis < part_range.a_max)
			{
				new_part_range = part_range;
				new_part_range.a_min = max(new_part_range.a_min, tmp_workflow->basis + 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.a_max = tmp_workflow->basis;
			}
			if (tmp_workflow->category == 's' && tmp_workflow->basis > part_range.s_min && tmp_workflow->basis < part_range.s_max)
			{
				new_part_range = part_range;
				new_part_range.s_min = max(new_part_range.s_min, tmp_workflow->basis + 1);
				new_part_range.workflow = ft_strdup(tmp_workflow->dest);
				count += follow_workflows(workflows, new_part_range);
				part_range.s_max = tmp_workflow->basis;
			}
		}
		list = list->next;
	}
	printf("Return count : %lld\n", count / 1000000000000);
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
	long long count = 0;
	t_list	*workflows[WRKFLWS];
	workflow	*tmp_workflow;
	char		**raw_workflow;
	t_part_range	tmp_part;
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
	tmp_part.x_min = 1;
	tmp_part.m_min = 1;
	tmp_part.a_min = 1;
	tmp_part.s_min = 1;
	tmp_part.x_max = 4000;
	tmp_part.m_max = 4000;
	tmp_part.a_max = 4000;
	tmp_part.s_max = 4000;
	tmp_part.workflow = "in";
	count = follow_workflows(workflows, tmp_part);
	printf("Count : %lld\n", count);
}
