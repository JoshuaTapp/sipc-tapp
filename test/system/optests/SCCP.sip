main() {
    var x, y, z;

    x = 5;
    y = 10;

    if (x < y)
    {
        if (x < 0)
        {
            z = x * y;
        }
        else
        {
            z = x + y;
        }
    }
    else
    {
        if (y < 0)
        {
            z = x * y;
        }
        else
        {
            z = x + y;
        }
    }

    if (x > 0 and y > 0)
    {
        z = x * y;
    }

    return z;
}