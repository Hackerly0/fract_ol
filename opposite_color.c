int get_opposite_color(int color) {
    unsigned char t = get_t(color);
    unsigned char r = 255 - get_r(color);
    unsigned char g = 255 - get_g(color);
    unsigned char b = 255 - get_b(color);
    return create_trgb(t, r, g, b);
}