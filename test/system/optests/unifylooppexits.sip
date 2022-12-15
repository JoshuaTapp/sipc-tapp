main(x) {
    var n, i, sum, rec, arr;
    n = 10000;
    i = 0;
    sum = 0;

    arr = [100 of x];

    while(n > i) {
        if (sum % x == 0) {
            arr[(i%100)] = sum + x;
        }
        else {
            sum = sum + i;
        }
        i = i + 1;
    }

    return sum;
}