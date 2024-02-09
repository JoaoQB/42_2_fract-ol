# Fract-ol

## Understanding minilibx | Pollock painting

`Minilibx` is a tiny graphics library which allows one to do most basic things for rendering something in screens.

The `X` in `minilibx` stands for `X-server`. X-server is a program, a middle man, that acts in between the user and applications (like a browser) that want to render windows in a display.

`X-Window` is a network-oriented graphical system for Unix. One of the most common examples of such implementation would be TeamViewer.

`mlx_init()` is a function that starts the connection with the graphical server and returns a pointer to the connection.

`mlx_new_window()` is a function that creates a new window. It takes a few parameters:

void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
- `mlx_ptr` would be our `mlx_connection`, the pointer created with `mlx_init()`.
- `size_x` and `size_y` are the horizontal and vertical size of the window to be created.
- `*title`, the name that appears on top of our new window.

Example:
```c
mlx_new_window(mlx_connection,
				500,
				500,
				"my first window");
```

When compiling and executing the following program:

```c
int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection, 500, 500, "my first window");
}
```
Nothing happens. And that's because the program starts a new window, but immediately reaches the end of the code and closes it. So we need a loop to keep the window open, using `mlx_loop()`.

```c
int mlx_loop(void *mlx_ptr)
```
takes as a parameter our `mlx_connection` pointer.

So now, running:

```c
int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection, 500, 500, "my first window");
	mlx_loop(mlx_connection);
}
```
creates a window that is permanently open because it is in an infinite loop. The only way to close it for now is to control+c in the terminal where executing the program.

Let's start by trying to print a pixel in the center of our window, using `mlx_pixel_put()`.

```c
int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color)
```
Example:
```c
mlx_pixel_put(mlx_connection, mlx_window, 250, 250, 0x00ACA6);
```
`0x00ACA6` is an integer representing a color, taken from a RGB color code table ([RGB Color Codes](https://www.rapidtables.com/web/color/RGB_Color.html)).

Running:

```c
int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection, 500, 500, "my first window");
	mlx_pixel_put(mlx_connection, mlx_window, 250, 250, 0x00ACA6);
	mlx_loop(mlx_connection);
}
```
gives back a window with a blueish pixel in the center. Let's make a line!

```c
int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		i;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection, 500, 500, "my first window");
	i = 0;
	while (i < 100)
	{
		mlx_pixel_put(mlx_connection, mlx_window, **250 + i**, 250, 0x00ACA6);
		i++;
	}
	mlx_loop(mlx_connection);
}
```

Now a square:
```c
#define WIDTH 500
#define HEIGHT 500

int	main(void)
{
								500,
								"my first window");
	x = 0;
	y = 50;
	while (y < HEIGHT - 50)
	{
		x = 50;
		while (x < WIDTH - 50)
		{
			mlx_pixel_put(mlx_connection,
							mlx_window,
							x,
							y,
							0x00ACA6);
			x++;
		}
		y++;
	}
	mlx_loop(mlx_connection);
}
```

or even better, for future changes:
```c
#define WIDTH 500
#define HEIGHT 500

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		x;
	int		y;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								WIDTH,
								HEIGHT,
								"my first window");
	x = 0;
	y = HEIGHT * 0.1;
	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(mlx_connection,
							mlx_window,
							x,
							y,
							0x00ACA6);
			x++;
		}
		y++;
	}
	mlx_loop(mlx_connection);
}
```

Now to finish our "pollock" painting we will use the rand() function from <stdlib.h> which will give us a random integer for our color integer. Like this:

```c
int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		x;
	int		y;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								WIDTH,
								HEIGHT,
								"my first window");
	x = 0;
	y = HEIGHT * 0.1;
	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(mlx_connection,
							mlx_window,
							x,
							y,
							rand() % 0x1000000);
			x++;
		}
		y++;
	}
	mlx_loop(mlx_connection);
}
```

To finish let's title our creation using mlx_string_put();

```c
int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		x;
	int		y;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								WIDTH,
								HEIGHT,
								"my first window");
	x = 0;
	y = HEIGHT * 0.1;
	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(mlx_connection,
							mlx_window,
							x,
							y,
							rand() % 0x1000000);
			x++;
		}
		y++;
	}
	mlx_string_put(mlx_connection,
					mlx_window,
					WIDTH * 0.8,
					HEIGHT * 0.95,
					rand() % 0x1000000,
					"My pollock");
	mlx_loop(mlx_connection);
}
```

We do a final fix so our rand() function works properly and:

```c
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <time.h>

#define WIDTH 500
#define HEIGHT 500

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		x;
	int		y;

	srand(time(NULL));
	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								WIDTH,
								HEIGHT,
								"my first window");
	x = 0;
	y = HEIGHT * 0.1;
	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(mlx_connection,
							mlx_window,
							x,
							y,
							rand() % 0x1000000);
			x++;
		}
		y++;
	}
	mlx_string_put(mlx_connection,
					mlx_window,
					WIDTH * 0.8,
					HEIGHT * 0.95,
					rand() % 0x1000000,
					"My pollock");
	mlx_loop(mlx_connection);
}
```

Voila!!!


##
