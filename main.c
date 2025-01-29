#include "fract_ol.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int handle_mouse(int button, int x, int y, void *param) {
    t_vars *vars = (t_vars *)param;
    double zoom_factor = (button == 4) ? 0.8 : 1.2; // Scroll up (4) zooms in, down (5) zooms out

    // Calculate fractal coordinates of the mouse position
    double real_range = (MAX_REAL - MIN_REAL) / vars->zoom;
    double img_range = (MAX_IMG - MIN_IMG) / vars->zoom;
    double mouse_real = MIN_REAL + (x / (double)WIDTH) * real_range + vars->offset_x * real_range;
    double mouse_img = MIN_IMG + (y / (double)HEIGHT) * img_range + vars->offset_y * img_range;

    // Apply zoom
    vars->zoom *= zoom_factor;

    // Recalculate offset to keep the mouse position centered
    real_range = (MAX_REAL - MIN_REAL) / vars->zoom;
    img_range = (MAX_IMG - MIN_IMG) / vars->zoom;
    vars->offset_x = (mouse_real - MIN_REAL) / real_range - (x / (double)WIDTH);
    vars->offset_y = (mouse_img - MIN_IMG) / img_range - (y / (double)HEIGHT);

    // Redraw the fractal with new parameters
    draw_mandelbrot(&vars->img, vars); // Pass vars here
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return 0;
}

int handle_keypress(int keycode, void *param) {
    t_vars *vars = (t_vars *)param;

    if (keycode == 65307) {
        mlx_destroy_image(vars->mlx, vars->img.img);
        mlx_destroy_window(vars->mlx, vars->win);
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
        exit(0);
    }
    return (0);
}

int close_window(void *param)
{
    t_vars *vars = (t_vars *)param;

    mlx_destroy_image(vars->mlx, vars->img.img);
    mlx_destroy_window(vars->mlx, vars->win);
    mlx_destroy_display(vars->mlx);
    free(vars->mlx);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc >= 1)
    {
        t_vars *vars;

        vars = malloc(sizeof(t_vars));
        vars->mlx = mlx_init();
        vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Julia Set");
        vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
        vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
                                      &vars->img.line_length, &vars->img.endian);
        vars->zoom = 1.0;
        vars->offset_x = 0.0;
        vars->offset_y = 0.0;

        // Add mouse hook
        mlx_mouse_hook(vars->win, handle_mouse, vars);

        //draw_mandelbrot(&vars->img);
        draw_mandelbrot(&vars->img, vars);
        //draw_julia(&vars->img, 0.4, -0.6);
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
        mlx_hook(vars->win, 2, 1L << 0, handle_keypress, vars); // Pass vars directly
        mlx_hook(vars->win, 17, 0, close_window, vars);         // Pass vars directly
        mlx_loop(vars->mlx);
    }
    return 0;
}