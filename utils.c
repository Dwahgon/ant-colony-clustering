int mod(int x, int y)
{
    int m = x % y;
    return m < 0 ? ((y < 0) ? m - y : m + y) : m;
}

int dir_to_hdir(int dir)
{
    return (dir == 0 || dir == 1 || dir == 8) - (dir >= 3 && dir <= 5);
}

int dir_to_vdir(int dir)
{
    return (dir >= 5 && dir <= 7) - (dir >= 1 && dir <= 3);
}