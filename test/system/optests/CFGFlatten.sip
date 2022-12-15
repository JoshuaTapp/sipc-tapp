abc(x){
    // do nothing
    output x;
    output x + x;
    output x * x;
    return 15 - x;
}

xyz(x) {
    // do nothing
    output x;
    output x + x;
    output x * x;
    return 15 + x;
}

main() {
    var x, y, z;
    x = 5;
    y = 6;


    if (x < (y + abc(y) ))
    {
        z = x + y + xyz(x);
    }
    else
    {
        z = x * y + abc(y);
    }

    return z;
}
