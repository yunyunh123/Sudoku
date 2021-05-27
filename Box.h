#pragma
class Box {
public:
  Box(int n, int r, int c, bool fixedVal);
  void fillAns(int n);

private:
  int num;
  int row; // should this be public or private?
  int col;
  bool fixed; // given value or not?
};

