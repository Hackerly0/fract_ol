int add_shade(double distance, int color) {
    if (distance < 0.0)
        distance = 0.0;
    else if (distance > 1.0)
        distance = 1.0;

    double scale = 1.0 - distance;

    unsigned char t = get_t(color);
    unsigned char r = get_r(color);
    unsigned char g = get_g(color);
    unsigned char b = get_b(color);

    unsigned char new_r = (unsigned char)(r * scale + 0.5);
    unsigned char new_g = (unsigned char)(g * scale + 0.5);
    unsigned char new_b = (unsigned char)(b * scale + 0.5);

    return create_trgb(t, new_r, new_g, new_b);
}