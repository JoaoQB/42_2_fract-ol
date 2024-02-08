# Fract-ol

## Understanding minilibx

Minilibx is a tiny graphics library which allows one to do most basic things for rendering something in screens.

The X in minilibx stands for X-server. X-server is a program, a middle man, that acts in between the user and applications (like a browser) that want to render windows in a display.

X-Window is a network-oriented graphical system for unix. One of the most common examples of such implementation would be TeamViewer.

mlx_init() is a function that starts the connection with the graphical server and returns a pointer to the connection.

mlx_new_window() is a function that creates a new window. It takes a few parameters:

void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)

*mlx_ptr would be our mlx_connection, the pointer created with mlx_init().
size_x and size_y are the horizontal and vertical size of the window to be created.
*title, the name that appears on top of our new window.

i.e. mlx_new_window(mlx_connection, 500, 500, "my first window");

When compiling and executing the following program:

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection, 500, 500, "my first window");
}

Nothing happens. And that's because the program starts a new window, but immediately reaches the end of the code and closes it. So we need a loop to keep the window open, using mlx_loop().

int mlx_loop(void *mlx_ptr), takes as a parameter our mlx_connection pointer.

So now, running:

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection, 500, 500, "my first window");
	mlx_loop(mlx_connection);
}

creates a window that is permanently open because it is in an infinite loop. the only way to close it for now is to control+c in the terminal where executing the program.

Let's start by trying to print a pixel in the center of our window, using mlx_pixel_put() - int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color).
i.e. mlx_pixel_put(mlx_connection, mlx_window, 250, 250, 0x00ACA6);
00ACA6 is an integer representing a color, taken from a rgb color code table (https://www.rapidtables.com/web/color/RGB_Color.html).

Running:

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								500,
								500,
								"my first window");
	mlx_pixel_put(mlx_connection,
					mlx_window,
					250,
					250,
					0x00ACA6);
	mlx_loop(mlx_connection);
}

gives back a window with a blueish pixel in the center.
Let's make a line!

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		i;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								500,
								500,
								"my first window");
	i = 0;
	while (i < 100)
	{
		mlx_pixel_put(mlx_connection,
						mlx_window,
						<strong>250 + i</strong>,
						250,
						0x00ACA6);
		mlx_loop(mlx_connection);
		i++;
	}
}
