#include <stdio.h>
#include <unistd.h>
#include <errno.h>

typedef struct s_dim
{
	int		height;
	int		width;
	int		x;
	int		y;
	char	c;
	char	empty;
}	t_dim;


typedef struct s_micro
{
	FILE	*fd;
	char	**paint;
	t_dim	back;
	t_dim	r;
}	t_micro;

int	ft_read(t_micro *e)
{
	if (fscanf(e->fd, "%d %d %s", &e->back.width, &e->back.height, e->back.c) != 3)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (fscanf(e->fd, "%s %d %d %d %d %s", e->r.empty, &e->r.x, &e->r.y, &e->r.width, &e->r.height, e->r.c) != 6)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
}

int	ft_paint(t_micro *e)
{
	e->paint = (char **) malloc (sizeof(char *) * (e->back.height + 1));
	if (!e->paint)
		return (1);
	
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
		return (errno);
	}
	if (ft_read(&e) == 1)
		return (1);
	ft_paint(&e);
}
