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
	struct s_module	*output[20];
	struct s_module *input[20];
	int				input_lvl[20];
	int				ffperiod;
	int				ffcumul;
	int				ff0period;
	int				ff0cumul;
	int				displayed;

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

int	gcd(int a, int b)
{
	if (b == 0)
		return (a);
	return (gcd(b, a % b));
}

int	gcm(int a, int b)
{
	if (a == 0 || b == 0)
		return (0);
	return (a * b / gcd(a, b));
}

int	push_button(module *modules[MODULES], int i)
{
	t_list		*signals;
	t_list		*old_signal;
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
				k++;
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
					k++;
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
				k++;
			}
		}
		if (receiver->type == 'm')
			machine_low_pulses += processed_signal->strength == 1;
		if (receiver->name[0] == 'j' && receiver->name[1] == 'm')
		{
			k = 0;
			ft_printf("Push %d ", i);
			while (receiver->input[k])
			{
				ft_printf("state %d ", receiver->input_lvl[k]);
				k++;
			}
			ft_printf("\n");
		}
		old_signal = signals;
		signals = signals->next;
		free(old_signal->content);
		free(old_signal);
	}
	return (machine_low_pulses);
}

void	display_module_state(module *module)
{
	int k = 0;

	if ((module->name[0] == 'r' && module->name[1] == 'o') || module->displayed || module->type != '&')
		return;
	module->displayed = 1;
	ft_printf("%s state : ", module->name);
	if (module->type == '&')
	{
		k = 0;
		while (module->input[k])
		{
			ft_printf(" %d ", module->input_lvl[k]);
			k++;
		}
	}
	if (module->type == '%')
		ft_printf(" %d", module->ffstate);
	ft_printf("\n");
	k = 0;
	while (module->input[k])
	{
		display_module_state(module->input[k]);
		k++;
	}
}


int	flip_flop_cycle(module *receiver, int i)
{
	module *sender;
	int		k = 0;
	int		cycle = 1;

	ft_printf("Conjunction : %s\n", receiver->name);
	k = 0;
	while (receiver->input[k])
	{
		sender = receiver->input[k];
		if (sender->ffstate == 1)
			sender->ffcumul++;
		if (sender->ffstate == 0)
		{
			if (sender->ffcumul > sender->ffperiod)
				sender->ffperiod = sender->ffcumul;
			sender->ffcumul = 0;
		}
		if (sender->ffstate == 0)
			sender->ff0cumul++;
		if (sender->ffstate == 1)
		{
			if (sender->ff0cumul > sender->ff0period)
				sender->ff0period = sender->ff0cumul;
			sender->ff0cumul = 0;
		}
		ft_printf("%d %s state %d 1 %d 0 %d\n", i + 1,sender->name, sender->ffstate, sender->ffperiod, sender->ff0period);
		cycle = gcm(cycle, sender->ffperiod);
		k++;
	}
	ft_printf("Cycle : %d + %d\n", cycle / 1024, cycle % 1024);
	return (cycle);
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
	module	*modules[MODULES];
	module	*tmp_module;
	module	*rec_module;
	int		machine_low_pulses = 0;
	long long	cycle = 1;

	while (i < MODULES)
	{
		modules[i] = NULL;
		i++;
	}
	fd = open(INPUT, O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	lines = ft_split(buf, '\n');
	free(buf);
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
	i = 1;
	j = 0;
	while (i < 100000 && machine_low_pulses != 1)
	{
		cycle = 1;
		j = 0;
		ft_printf("Pushes : %d\n", i + 1);
		machine_low_pulses = push_button(modules, i);
		/*tmp_module = modules[hash("bx")];
		cycle = cycle * flip_flop_cycle(tmp_module, i) / 1024;
		tmp_module = modules[hash("bc")];
		cycle = cycle * flip_flop_cycle(tmp_module, i) / 1024;
		tmp_module = modules[hash("qq")];
		cycle = cycle * flip_flop_cycle(tmp_module, i) / 1024;
		tmp_module = modules[hash("gj")];
		cycle = cycle * flip_flop_cycle(tmp_module, i) / 1024;
*/
		/*while (lines[j])
		{
			if (lines[j][0] == '%')
			{
			}
			j++;
		}*/
		ft_printf("\nMachine low pulses : %d\n", machine_low_pulses);
		i++;
	}
	printf("Cycle : %lld\n", cycle);
}
