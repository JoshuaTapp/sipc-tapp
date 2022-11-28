main() {
  var x;
  x = 7;
  x++;
  output x;
  if (x != 8) error x;
  x--;
  output x;
  if (x != 7) error x;
  return 0;
}
