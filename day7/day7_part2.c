#include "libftprintf/ft_printf.h"
#include "libftprintf/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	is_in_pos(char *s, char c)
{
	int i = 0;
	int pos = -1;

	while (s[i] && s[i] != ' ')
	{
		if (s[i] == c)
		{
			pos = i;
			return pos;
		}
		i++;
	}
	return (pos);
}

int	max_repeat(char *s)
{
	int i = 0;
	int j = 1;
	int repeat = 0;
	int card_repeat = 0;

	while (s[i] && s[i] != ' ')
	{
		card_repeat = 1;
		j = 1;
		while (s[i] != 'J' && s[i + j] != ' ' && is_in_pos(&s[i + j], s[i]) != -1)
		{
			j += is_in_pos(&s[i + j], s[i]) + 1;
			card_repeat++;
		}
		if (card_repeat > repeat)
			repeat = card_repeat;
		i++;
	}
	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == 'J')
			repeat++;
		i++;
	}
	if (repeat == 6)
		return 5;
	return repeat;
}

int	card_kinds(char *s)
{
	int i = 4;
	int j = 1;
	int card_kinds = 0;

	while (i >= 0)
	{
		if (s[i] != 'J' && is_in_pos(s + i + 1, s[i]) == -1)
			card_kinds++;
		i--;
	}
	if (card_kinds == 0)
		card_kinds = 1;
	return card_kinds;
}

int	cardcmp(char *h1, char *h2)
{
	int i = 0;

	while (h1[i] == h2[i] && h1[i] != ' ')
		i++;
	return (is_in_pos("AKQT98765432J", h2[i]) - is_in_pos("AKQT98765432J", h1[i]));
	
}

int	hand_comp(char *h1, char *h2)
{
	int cmp;

	if ((cmp = max_repeat(h1) - max_repeat(h2)) != 0) 
		return cmp;
	if ((cmp = card_kinds(h1) - card_kinds(h2)) != 0)
		return (-cmp);
	return (cardcmp(h1, h2));
}

int main(void) {
	int fd;
	char *buf;
	char **hands;
	char *tmp;
	int i;
	long long count = 0;
	int comb = 1000;
	int swap = 0;

	fd = open("day7_input.txt", O_RDONLY);
	buf = malloc(100000);
	read(fd, buf, 100000);
	hands = ft_split(buf, '\n');
	i = 0;
	while (comb > 1 || swap == 1)
	{
		comb = (comb * 3) / 4;
		if (comb < 1)
			comb = 1;
		i = 0;
		swap = 0;
		while (i < 1000 - comb)
		{
			if (hand_comp(hands[i], hands[i + comb]) > 0)
			{
				tmp = hands[i];
				hands[i] = hands[i + comb];
				hands[i + comb] = tmp;
				swap = 1;
			}
			i++;
		}
		ft_printf("%d\n", i);
	}
	i = 0;
	while (hands[i])
	{
		count += (i + 1) * ft_atoi(hands[i] + 5);
		printf("Hand : %s Max repeat : %d Card kinds : %d\n", hands[i], max_repeat(hands[i]), card_kinds(hands[i]));
		i++;
	}
	printf("Count = %lld", count);
}
