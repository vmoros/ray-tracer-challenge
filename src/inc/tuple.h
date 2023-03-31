class Tuple {
 public:
  double x;
  double y;
  double z;
  int w;

  Tuple(double x, double y, double z, int w);
  static Tuple Point(double x, double y, double z);
  static Tuple Vector(double x, double y, double z);

  Tuple operator+(Tuple other) const;
  Tuple operator-(Tuple other) const;
  Tuple operator-() const;

  bool isPoint() const;
  bool isVector() const;
  bool operator==(Tuple other) const;
};