main() {
    var a;
    a = [5, 6, 7, 8];
    if(a[0] != 5) error a[0];
    if(a[1] != 6) error a[1];
    if(a[2] != 7) error a[2];
    if(a[3] != 8) error a[3];
    if(#a != 4) error #a;
    return 0;
}
