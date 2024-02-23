# Fract-ol

## Understanding minilibx | Pollock painting

`Minilibx` is a tiny graphics library which allows one to do most basic things for rendering something in screens.

The `X` in `minilibx` stands for `X-server`. X-server is a program, a middle man, that acts in between the user and applications (like a browser) that want to render windows in a display.

`X-Window` is a network-oriented graphical system for Unix. One of the most common examples of such implementation would be TeamViewer.

To compile our program we will need to have the minilibx-linux folder in our directory.
Inside we will `make` to create the `minilibx_linux.a` archive.
We then need to add the following to our compilation flags: `-Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz`.
The flags are added after the .c files.
For example `cc -Wall -Werror -Wextra pollock.c -Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz`.
Or, in our makefile: `$(CC) $(CFLAGS) $(OBJ) $(MINILIBX_FLAGS) -o $(NAME)`. `$(MINILIBX_FLAGS)` are the flags above.
By the way, `-Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz`, stands for:
`-Lminilibx-linux`: This option adds the directory minilibx-linux to the library search path. It specifies where to look for libraries during the linking stage.

`-l:libmlx_Linux.a`: This option tells the linker to link against a specific library file named libmlx_Linux.a. The lib: prefix is used to specify a library file directly without the usual lib prefix and .a extension.

`-L/usr/lib`: This option adds the directory /usr/lib to the library search path, similarly to the first -L option.

`-Imlx_linux`: This option adds the directory mlx_linux to the include path. It specifies where to look for header files during the compilation stage.

`-lXext -lX11 -lm -lz`: These options specify additional libraries to link against. -lXext, -lX11 are for X Window System extensions and libraries, -lm is for the math library, and -lz is for the zlib compression library.

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


## Leaks and properly closing the program.

If we valgrind the program above it will show leaks. In fact, to properly free all the resources we will have to use 2 functions, `mlx_destroy_window` and `mlx_destroy_display`, and to free the pointers. Something like this:

```c
int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "my_window");
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}
```

If we check the `man` of these 2 new functions we see that they return `null` if an error occurs.
So to properly handle errors we can add a few lines of code that make it less readable but better built. Like:

```c
int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return(MLX_ERROR);
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "my_window");
	if (win_ptr == NULL)
	{
		free(mlx_ptr);
		return(MLX_ERROR);
	}
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}
```

But there's a problem to this approach. Because we are using mlx_loop and relying on `Control+C` to kill the process in the terminal, in order to close the window, everything after killing the process, so all the code after mlx_loop, will not be read and therefore there will still be leaks in our program.
Also note that first we use `mlx_destroy_window` and only after `mlx_destroy_display`.

## Managing Events

When using the `mlx_loop` function, minilibx allow for `events` to happen during the loop.
These events should be registered before the `mlx_loop` function is called, but they are triggered after the loop has started.
Clicking the window, moving the mouse, pressing a key, are all possible events.

In order to register events we can use a set of function called `hooks`, provided by the `minilibx API`.
There are five hook functions:

```c
int	mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
```

They have similar parameters. `win_ptr` is the pointer to a window. The window will register for the given event.
`(*func_ptr)()` is a pointer to a function that returns an int and takes undefined parameters.
- Beware, (*func_ptr)() is not the same as (*func_ptr)(void): the last means NO argument while the first means "any set of arguments".-
`param` is the address of an element you want to access in your `func_ptr` when handling events.

Let's use the code above and add a new feature: now when `esc` is pressed, the window will disappear and all the memory allocated will be properly freed.

```c
typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init;
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup Hooks */
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);

	mlx_loop(data.mlx_ptr);
	/* Exit the loop if there's no window, execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
```

We now use a structure to organize data. That is because we can only pass a single void pointer to the `hook` functions, but we might want to have multiple arguments.

The `mlx_key_hook` function is used to get a proper event. Everytime a key is released, the function executed will be the `handle_input` function.
It is inside the `handle_input` function that we check if the `key symbol` that was released corresponds to the escape key.

We also use `mlx_loop_hook`, and it is triggered when there's no event processed. It is especially useful to draw things continuously on the screen.
Even though we haven't used it in the example above, we need to include it otherwise the loop would never have ended. That's related to how the `mlx_loop is implemented`.

When using the above code, we see that the `mlx_key_hook` waits that a key is released, not that it is pressed.
Let's look at the `mlx_hook` function. It takes extra parameters. - int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param); -

`x_event` is an integer corresponding to the name of the `X event`. All the event names are found in the `X11/X.h` header.
`x_mask` is a bit mask corresponding to the X event. The list of all available masks is also defined in the same header.
Let's change the program to add an `event handler` for the `KeyPress` event.

```c
#include <X11/X.h>

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup Hooks */
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);
	/* Exit the loop if there's no window, execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
```

Each hook now has it's own handler, the previously used `key_release` and the newly added `key_press`.

## Colors

Minilibx complies with the `true color` standard. It's an RGB color model standard with 256 shades for red, green and blue.
With minilibx we need to make the color fit into an `int` datatype. It will therefore be 32 bits in our system.
We need to encode our color into an in by setting the three least significant bits to the amount of red, green and blue. We can encode our int in two different ways.

### Setting the bits directly

We can set the bits of the integer directly, using the `<<` (left shift) operator, as shown below:

```c
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
```

For example:

```c
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	main(void)
{
	int	encoded_color;

	encoded_color = encode_rgb(255, 128, 64);
	printf("Encoded RGB color: %06X\n", encoded_color);
}
```

It will print: `Encoded RGB color: FF8040` (which is a kind of orange).
Also, %06X, indicates the output should be formatted as a hexadecimal number with at least 06 digits, padded with leading zeros if necessary.

Note that when using this system, we attribute a number from 0 to 255 to each of the RGB colors. 255 being the maximum of that color. That is because each of the colors is an 8-bit number.
When using encode_rgb, we are setting each of the 8-bits to the correct value, meaning that in the end we have a single 32-bit number (8 bits for red, 8 bits for green, 8 bits for blue and 8 for transparency).

### Using the hexadecimal notation

Hexadecimal values like the one used in the Pollock example (0x00ACA6) are widely used because it allow us to distinguish the bytes that form an integer.

We can think about an hexadecimal number as groups of two digits. Each group represents an entire byte, or 8-bits.

For example if we assign `0x00FF00FF` to an integer, we can see that RED is FF (255), Green is 0 and Blue is FF (255).
In `0x00ACA6`, Red is 0, Green is AC (172) and Blue is A6 (166).

That's because we have 16 digits to represent a number (0123456789ABCDEF).

However this solution is only useful if we already know what color we want to use at compile time.
If the color is provided for example by the user or any other source, then we need to use the encode_rgb function.

### Let's use the pixel!

```c
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	render(t_data *data)
{
	/* If window has been destroyed, we don't want to put the pixel! */
	if (data->win_ptr != NULL)
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, WIDTH / 2, HEIGHT / 2, RED_PIXEL);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup Hooks */
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* Exit the loop if there's no window, execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
```

We need to put the `if` statement before the `mlx_pixel_put` function, to ensure we're not trying to put a pixel in a non existing window.
Also we need to ensure that our `win_ptr` is set to null after the call to `mlx_destroy_window` to make this check actually work (and get rid of leaks - not sure why).

### Let's draw a rectangle!

One possible implementation:

```c
typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
} t_rect;

/* X and Y coordinates correspond to it's upper left corner. */

int	render_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	if (data->win_ptr == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		i++;
	}
	return (0);
}
```

In order to render the rectangles, we need to modify the `render` function:

```c
int	render(t_data *data)
{
	render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});

	return (0);
}
```

These `render_rect` function will display two rectangles: one in the upper left corner and one in the bottom right corner.
`(t_rect){}` is what is called a `compound literal`. Since C99, this is how we initialize structures without having to manually assign each member.
We're directly passing a structure by value here.

A `compound literal` allows us to create an unnamed object of a specified type and initialize it with values all in one go. It's primarly used when one needs to pass temporary data to functions or initialize a structure without declaring separate variables.

Syntax:

```c
(type){initializer}
```

For example in the code above:

```c
(t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL}
```

Benefits of `compound literals`:

Concise initialization: Allows to initialize structures in a single line, reducing code clutter.
Temporary objects: We can pass temporary data directly to functions without declaring seperate variables, improving code readability.

Alternative without `compound literals`:

We would have to declare a separate variable to hold values and then pass that variable to the function. I.e:

```c
t_rect	rect;

rect.x = WINDOW_WIDTH - 100;
rect.y = WINDOW_HEIGHT - 100;
rect.width = 100;
rect.height = 100;
rect.color = GREEN_PIXEL;

render_rect(data, rect);
```

This achieves the same result but requires more lines of code and introduces an aditional variable (rect).
This is less efficient in terms of code readability, mantainability, especially dor temporary or one-time use cases.


### Drawbacks of our approach

To visualize what's wrong let's implement a render_background function that will change the background color of the window.

```c
void	render_background(t_data *data, int color)
{
	int	i;
	int	j;

	if (data->win_ptr == NULL)
		return ;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
		++i;
	}
}
```
Add it to the render function:

```c
int	render(t_data *data)
{
	if (data->win_ptr != NULL)
	{
		render_background(data, WHITE_PIXEL);
		render_rect(data, (t_rect){WIDTH - 100, HEIGHT - 100, 100, 100, GREEN_PIXEL});
		render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});

		return (0);
	}
	return (0);
}
```

Compiling and running the program we get horrible flickering.
That's because `mlx_pixel_put` draws the pixel on the window directly, and whoever is looking at the window will see the change instantly.
We want instead to wait for the whole background and then the whole rectangles to be drawn, and then push that on the window.
Since everything here was done without delay, it gives us the flickering effect.
Fortunately the minilibx provides us with a solution to both problems.

### Using minilibx to draw on screen

One of the prefered ways to draw on a screen is using images. The objective is to first create an image (a collection of pixels) and edit its pixels directly.
When done, we can then push the whole image to the window and the graphics should be properly rendered.
Because minilibx allows us to share images with the `X server` through memory, using a pointer we can change the pixels directly much much faster.

Let's use the function `mlx_new_image` to create a new image.
```c
void	*mlx_new_image(void *mlx_ptr, int width, int height);
```

To do that we first need to create a `t_image` type struct to hold all the stuff we need to work with an mlx image.

```c
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; // Bits per pixel
	int		line_len;
	int		endian;
} t_img;
```

Add that to our t_data object.

```c
typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;
```

Creating the image:

```c
data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
```

Now we have the image, but we still need some information to make it work.
We'll specially need the address of the image in the shared memory, in order to change the pixels on it directly.
We'll also need some additional info to helps us with calculations (`bpp`, `line_len` and `endian` member values).
To do so we can use `mlx_get_data_addr`.

```c
char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
```

We pass it the img we've got from `mlx_new_image`. The last three arguments we pass the address of an int variable. The function will set the integers correctly.
It's a way to return multiple values.

Also, `mlx_get_data_addr` function return the actual address of the image as an array of pixels.
We get a pointer to char, which means we will navigate an array one byte at a time, and not one pixel, as we saw before a pixel usually takes more than a byte.

```c
int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	printf("bpp: %d\n", data.img.bpp);
	printf("line_len: %d\n", data.img.line_len);
	printf("endian: %d\n", data.img.endian);
	printf("Image address: %p\n", data.img.addr);

	/* Setup Hooks */
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* Exit the loop if there's no window, execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
```

Now the complicated part. We need to retrieve a pixel at some x and y coordinates, but we don't have a two-dimensional array.
On top of that we are dealing with bytes, but one pixel takes more than a byte because we're using the true colors standard.
This amount is given by the bpp (bits) value we get from `mlx_get_data_addr`.
However we don't know how many bytes an int really is so we can't cast the pointer safely.

Finding the pixel's first byte's address
