#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct s_back
{
	int		height;
	int		width;
	int		x;
	int		y;
	char 	c[2];
}	t_back;

typedef struct s_dim
{
	float		height;
	float		width;
	float		x;
	float		y;
	char		c[2];
	char		empty[2];
}	t_dim;


typedef struct s_micro
{
	FILE	*fd;
	char	**paint;
	t_back	back;
	t_dim	r;
}	t_micro;

int	ft_read(t_micro *e)
{
	char c;
	if (fscanf(e->fd, "%d %d %s", &e->back.width, &e->back.height, e->back.c) != 3 || e->back.c[1] != '\0')
		return (1);
	if (fscanf(e->fd, "%c", &c) < 1 || c != '\n')
		return (2);
	if (fscanf(e->fd, "%s %f %f %f %f %s", e->r.empty, &e->r.x, &e->r.y, &e->r.width, &e->r.height, e->r.c) != 6 || e->r.empty[1] != '\0' || e->r.c[1] != '\0')
		return (3);
	if (fscanf(e->fd, "%c", &c) < 1 || c != '\n')
		return (4);
	if (e->r.empty[0] != 'r' && e->r.empty[0] != 'R')
		return (5);
	e->back.x = 0; e->back.y = 0;
	return (0);
}

int	ft_check(t_back s)
{
	if (s.height <= 0 || s.height > 300)
		return (1);
	if (s.width <= 0 || s.width > 300)
		return (1);
	if (s.c[0] < 32 || s.c[0] > 126)
		return (1);
	return (0);
}

int	ft_check_values(t_dim s)
{
	if (s.height <= 0 || s.height > 300)
		return (1);
	if (s.width <= 0 || s.width > 300)
		return (1);
	if (s.c[0] < 32 || s.c[0] > 126)
		return (1);
	return (0);
}

int	ft_paint_back(t_micro *e)
{
	int	i;

	i = 0;
	e->paint = (char **) malloc (sizeof(char *) * (e->back.height + 1));
	if (!e->paint)
		return (1);
	while (i < e->back.height)
	{
		e->paint[i] = (char *) malloc (sizeof(char) * (e->back.width + 1));
		if (!e->paint[i])
			return (1);
		memset(e->paint[i], e->back.c[0], e->back.width);
		i++;
	}
	return (0);
}

void	ft_paint_rect(t_micro *e)
{
	int	i, j;

	i = 0; j = 0;
	while (e->paint[i])
	{
		while (e->paint[i][j])
		{
			if (e->r.empty[0] == 'R')
			{
				if ((j >= e->r.y && j <= e->r.y + e->r.width)
					&& (i >= e->r.x && i <= e->r.x + e->r.height))
					e->paint[i][j] = e->r.c[0];
			}
			else if (((i == e->r.y || i == e->r.y + (int)e->r.height) && j >= e->r.x && j <= e->r.x + (int)e->r.width)
						|| ((j == e->r.x || j == e->r.x + (int) e->r.width) && i >= e->r.y && i <= e->r.y + (int)e->r.height))
			{
				e->paint[i][j] = e->r.c[0];
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_print(char **map)
{
	int	i, j;

	i = 0; j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}

void	ft_free(char **c)
{
	int i = 0;
	while (c[i])
	{
		if (c[i])
			free(c[i]);
		i++;
	}
	free(c);

}

int main(int argc, char **argv)
{
	t_micro	e;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (1);
	}
	if ((e.fd = fopen(argv[1], "r")) == NULL)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (ft_read(&e) == 1)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (ft_check(e.back) == 1 || ft_check_values(e.r) == 1)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (ft_paint_back(&e) == 1)
		return (1);
	ft_paint_rect(&e);
	ft_print(e.paint);
	ft_free(e.paint);
	return (0);
}
