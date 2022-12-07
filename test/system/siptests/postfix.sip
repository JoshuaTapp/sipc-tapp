main() {
    var x;
    x = 0;
    x++;
    if(x != 1) error x;
    x--;
    if(x != 0) error x;
    return 0;
}