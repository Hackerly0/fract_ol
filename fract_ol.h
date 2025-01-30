#ifndef  FRACT_OL_H
#define FRACT_OL_H

#include <mlx.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysymdef.h>

#define ON_KEYDOWN 2
#define ON_KEYUP 3
#define ON_MOUSEDOWN 4
#define ON_MOUSEUP 5
#define ON_MOUSEMOVE 6
#define ON_EXPOSE 12
#define ON_DESTROY 17
#define MAX_ITER 100
#define MAX_IMG 2.0
#define MAX_REAL 2.0
#define MIN_IMG -2.0
#define MIN_REAL -2.0
#define HEIGHT 600
#define WIDTH 800

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_data;

typedef struct s_vars {
    void    *mlx;
    void    *win;
    double  zoom;
    double  offset_x;
    double  offset_y;
    t_data  img;
} t_vars;

int mandelbrot(double c_re, double c_im);
//void    draw_mandelbrot(t_data *img);
void    draw_mandelbrot(t_data *img, t_vars *vars);
void	draw_julia(t_data *img, t_vars *vars, double c_re_julia, double c_im_julia);
int     julia(double z_re, double z_im, double c_re, double c_im);
int     handle_mouse(int button, int x, int y, void *param);
int     handle_keypress(int keycode, void *param);
int     close_window(void *param);

#endif