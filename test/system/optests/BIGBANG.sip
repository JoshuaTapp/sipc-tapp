
arraySum(arr) {
    var s, i;
    i = 0;
    s = 0;

  for ( i : 0 .. #arr by 32) {
    s = s + arr[i];
  }
  return s;
}

bigSum(arr) {
    var s, i, j;
    i = 0;
    j = 0;
    s = 0;
    for(i : 0 .. #arr by 32) {
        for(j : 0 .. #arr[0] by 16) {
            s = s + arraySum(arr[i][j]);
        }
    }

    return s;
}

main() {
    var arr, i, j, k, s;

    s = 0;
    arr = [128 of [128 of [128 of 0]]];

    for (i : 0 .. #arr by 4) {
        for (j : 0 .. #arr[0] by 8) {
            for (j : 0 .. #arr[0][0]) {
                if ( (j + i) % 2 == 0 ) {
                    arr[i][j%2][k] = i * j + arraySum(arr[i%64][j%32]);
                }
                else {
                    if ( (j + i) % 2 == 1 ) {
                        arr[i%2][j][k] = i * j + arraySum(arr[i%32][j%16]);
                    }
                    else {
                        arr[i%13][j][k%2] = (i * j) % k;
                    }
                }
                if( (i % 128) == 0) {
                    output arr[i%8][j%4][k%2];
                }
                else {
                    arr[i][j][k] = k % 8;
                    s = s + arr[i][j%4][k];
                }
            }
        }
        if (k % 24 == 2) {
                arr[i%16][j%4][k%8] = 2;
            }
            else {
                if (i+1 == j) {
                    output arraySum(arr[i][j]);
                }
                else {
                    arr[i%64][j%32][k%2] = 1;
                }
            }
    }
  return bigSum(arr);
}
