fib(x) {
    var f;
    if(x < 2) {
        f = x;
    } else {
        f = fib(x-1) + fib(x-2);
    }

    return f;
}

main(x) {
    output fib(x);
    return 0;
}