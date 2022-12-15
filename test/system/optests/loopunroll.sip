main(x) {
    var i, j, k, sum, arr;
    i = 0;
    j = 0;
    k = 0;
    sum = 0;
    arr = [100 of [100 of [100 of x]]];

    for (i : 0 .. 100) {
        for (j : 0 .. 100) {
            for (k : 0 .. 100) {
                sum = sum + arr[i][j][k];
            }
        }
    }

    return sum;
}