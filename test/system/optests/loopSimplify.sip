main(x) {
    var arr, sum, i;

    arr = [1, 2, 3, 4, x, 6, 7, 8, 9, 10];
    sum = 0;
    i = 0;

    for (i : 0 .. 10) {
        if((arr[i] % 2) == 0) {
            sum = sum + arr[i];
        }
    }

    return sum;
}