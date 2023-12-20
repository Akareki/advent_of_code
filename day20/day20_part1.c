#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MODULES 1000
#define	INPUT "day20_input.txt"
#define T_INPUT "test.txt"

typedef struct s_module{
	char	type;
	char	name[3];
	int		ffstate;
	struct s_module	*output[10];
	struct s_module *input[10];
	int				input_lvl[10];

} module;

typedef struct	s_signal
{
	module	*sender;
	module	*receiver;
	int		strength;
}				t_signal;

int	hash(char *name)
{
	int	count = 0;
	int i = 0;

	while (ft_isalpha(name[i]) && i < 2)
	{
		count += (int)name[i];
		count *= 11677;
		count %= MODULES;
		i++;
	}
	return (count);
}

void	push_button(module *modules[MODULES], long long count[3])
{
	t_list		*signals;
	t_signal	*new_signal;
	t_signal	*processed_signal;
	module		*receiver;
	module		*sender;
	int			k = 0;
	int			conj_strength = 2;
	int			machine_low_pulses = 0;

	signals = NULL;
	new_signal = malloc(sizeof(t_signal));
	new_signal->sender = 0;
	new_signal->receiver = modules[hash("ro")];
	new_signal->strength = 1;
	ft_lstadd_back(&signals, ft_lstnew(new_signal));
	ft_printf("button -%d-> %s\n", new_signal->strength, new_signal->receiver->name);
	count[new_signal->strength]++;
	while (signals)
	{
		processed_signal = (t_signal *) signals->content;
		sender = processed_signal->sender;
		receiver = processed_signal->receiver;
		if (receiver->type == 'b')
		{
			k = 0;
			while (receiver->output[k])
			{
				new_signal = malloc(sizeof(t_signal));
				new_signal->sender = receiver;
				new_signal->receiver = receiver->output[k];
				new_signal->strength = processed_signal->strength;
				ft_lstadd_back(&signals, ft_lstnew(new_signal));
				ft_printf("%s -%d-> %s\n", new_signal->sender->name, new_signal->strength, new_signal->receiver->name);
				k++;
				count[new_signal->strength]++;
			}
		}
		if (receiver->type == '%')
		{
			if (processed_signal->strength == 1)
			{
				k = 0;
				while (receiver->output[k])
				{
					new_signal = malloc(sizeof(t_signal));
					new_signal->sender = receiver;
					new_signal->receiver = receiver->output[k];
					new_signal->strength = 1 + (receiver->ffstate == 0);
					ft_lstadd_back(&signals, ft_lstnew(new_signal));
					ft_printf("%s -%d-> %s\n", new_signal->sender->name, new_signal->strength, new_signal->receiver->name);
					k++;
					count[new_signal->strength]++;
				}
				receiver->ffstate = (receiver->ffstate + 1) % 2;
			}
		}
		if (receiver->type == '&')
		{
			k = 0;
			while (receiver->input[k] && receiver->input[k] != processed_signal->sender)
				k++;
			receiver->input_lvl[k] = processed_signal->strength;
			k = 0;
			while (receiver->input[k])
			{
				conj_strength = 1;
				if (receiver->input_lvl[k] != 2)
				{
					conj_strength = 2;
					break;
				}
				k++;
			}
			k = 0;
			while (receiver->output[k])
			{
				new_signal = malloc(sizeof(t_signal));
				new_signal->sender = receiver;
				new_signal->receiver = receiver->output[k];
				new_signal->strength = conj_strength;
				ft_lstadd_back(&signals, ft_lstnew(new_signal));
				ft_printf("%s -%d-> %s\n", new_signal->sender->name, new_signal->strength, new_signal->receiver->name);
				k++;
				count[new_signal->strength]++;
			}
		}
		if (receiver->type == 'm')
			machine_low_pulses += processed_signal->strength;
		signals = signals->next;
	}
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
	long long count[3];
	module	*modules[MODULES];
	module	*tmp_module;
	module	*rec_module;

	while (i < MODULES)
	{
		modules[i] = NULL;
		i++;
	}
	fd = open(INPUT, O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	i = 0;
	while (lines[i])
	{
		tmp_module = ft_calloc(1, sizeof(module));
		tmp_module->type = lines[i][0];
		tmp_module->name[0] = lines[i][1];
		tmp_module->name[1] = lines[i][2];
		modules[hash(tmp_module->name)] = tmp_module;
		i++;
	}
	i = 0;
	while (lines[i])
	{
		tmp_module = modules[hash(lines[i] + 1)];
		j = 0;
		k = 0;
		while (lines[i][j] != '>')
			j++;
		while (lines[i][j])
		{
			while (lines[i][j] && !ft_isalpha(lines[i][j]))
				j++;
			tmp_module->output[k] = modules[hash(lines[i] + j)];
			if (!tmp_module->output[k])
				ft_printf("%.2s does not exist\n", lines[i] + j);
			while (ft_isalpha(lines[i][j]))
				j++;
			k++;
		}
		k = 0;
		j = 0;
		while (tmp_module->output[k])
		{
			j = 0;
			while (tmp_module->output[k]->input[j])
				j++;
			tmp_module->output[k]->input[j] = tmp_module;
			k++;
		}
		i++;
	}
	i = 0;
	while (i < MODULES)
	{
		if (modules[i])
		{
			ft_printf("Module : %s Type : %c Output :", modules[i]->name, modules[i]->type);
			k = 0;
			while (modules[i]->output[k])
			{
				ft_printf(" %s ", modules[i]->output[k]->name);
				k++;
			}
			ft_printf("Input : ");
			k = 0;
			while (modules[i]->input[k])
			{
				ft_printf(" %s ", modules[i]->input[k]->name);
				k++;
			}
			ft_printf("\n");
		}
		i++;
	}
	count[1] = 0;
	count[2] = 0;
	i = 0;
	while (i < 1000)
	{
		push_button(modules, count);
		i++;
	}
	printf("Count : low : %lld  |  high : %lld  |  product : %lld\n", count[1], count[2], count[1] * count[2]);
}
