bigOp(x, y) {
    var r, i;
    i = 0;
    for (i : 0 .. 100) {
        r = r + x * y;
        x = x * y;
        y = x + y;
    }

    return r;
}

main() {
    var a, b, c, x, y, result;

    x = 10;
    y = 20;

    result = bigOp(x, y);

    a = result + x;
    b = result * y;
    c = result - x;

    return (a + b + c);
}