main() {
  var x, y, z;
  x = 1;
  y = 2;
  z = 3;
  x = y>z ? y+2 : x-1;
  if (x != 0) error x;
  z = y!=x ? y==13 ? 42 : 5 : y+x;
  if (z != 5) error x;
  z = y!=x ? 42 : z==3 ? 5 : y+x;
  if (z != 42) error x;
  return 0;
}
