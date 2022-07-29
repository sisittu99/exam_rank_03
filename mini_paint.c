#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_back
{
	int width;
	int height;
	char c;
	char **map;
} t_back;

typedef struct s_c
{
	char empty;
	float x;
	float y;
	float r;
	char c;
} t_c;

void ft_free(t_back *b)
{
	int i = 0;

	if (b->map != NULL)
	{
		while (b->map[i] != NULL)
		{
			if (b->map[i] != NULL)
				free(b->map[i]);
			i++;
		}
		free(b->map);
	}
}

int	ft_perror(char *s, t_back *b)
{
	int i = 0;

	while (s[i])
		i++;
	write(1, s, i);
	ft_free(b);
	return (1);
}

int	ft_init_map(t_back *b)
{
	int i = 0;
	int j = 0;

	while (i < b->height)
	{
		b->map[i] = (char *) malloc(sizeof(char) * (b->width + 1));
		if (b->map[i] == NULL)
			return (1);
		while (j < b->width)
		{
			b->map[i][j] = b->c;
			j++;
		}
		b->map[i][j] = '\0';
		j = 0;
		i++;
	}
	b->map[i] = NULL;
	return (0);
}

int	ft_back(t_back *b, FILE *f)
{

	int val = fscanf(f, " %d %d %c\n", &b->width, &b->height, &b->c);

	if (val < 3)
		return (1);
	if (b->width < 1 || b->width > 300)
		return (1);
	if (b->height < 1 || b->height > 300)
		return (1);

	b->map = (char **) malloc(sizeof(char *) * (b->height + 1));
	if (b->map == NULL)
		return (1);
	return (ft_init_map(b));
}

void	ft_cycle(t_c *circle, t_back *b)
{
	int i = 0;
	int j = 0;
	float d = 0;

	while (b->map[i] != NULL)
	{
		while (b->map[i][j] != '\0')
		{
			d = sqrtf(powf(j - circle->x, 2) + powf(i - circle->y, 2)) - circle->r;
			if (d <= 0.0)
				if ((d > -1.0 && circle->empty == 'c') || circle->empty == 'C')
					b->map[i][j] = circle->c;
			j++;
		}
		j = 0;
		i++;
	}
}

int	ft_circle(t_c *circle, t_back *b, FILE *f)
{
	int val = 5;

	while (val == 5)
	{
		val = fscanf(f, "%c %f %f %f %c\n", &circle->empty, &circle->x, &circle->y, &circle->r, &circle->c);
		if (val == -1)
			return (0);
		if (val < 5)
			return (1);
		if (circle->empty != 'c' && circle->empty != 'C')
			return (1);
		if (circle->r <= 0.0)
			return (1);
		ft_cycle(circle, b);
	}
	return (0);
}

void	ft_print_map(t_back *b)
{
	int i = 0;
	int j = 0;

	while (b->map[i] != NULL)
	{
		while (b->map[i][j] != '\0')
		{
			write(1, &b->map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		j = 0;
		i++;
	}
	ft_free(b);
}

int main(int argc, char **argv)
{
	t_back b;
	t_c circle;
	FILE *f;

	if (argc != 2)
		return (ft_perror("Error: argument\n", &b));
	f = fopen(argv[1], "r");
	if (f == NULL)
		return (ft_perror("Error: Operation file corrupted\n", &b));
	if (ft_back(&b, f) != 0)
		return (ft_perror("Error: Operation file corrupted\n", &b));
	if (ft_circle(&circle, &b, f) != 0)
		return (ft_perror("Error: Operation file corrupted\n", &b));
	ft_print_map(&b);
	fclose(f);
}
