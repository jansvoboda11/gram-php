#ifndef GRAM_PHP_TYPE
#define GRAM_PHP_TYPE

class PhpType {
 public:
  static PhpType null();
  static PhpType boolean();
  static PhpType integer();
  static PhpType decimal();
  static PhpType string();
  static PhpType array();
  bool operator==(const PhpType& other) const;
  bool operator!=(const PhpType& other) const;
 private:
  PhpType(unsigned type);
  unsigned type;
  static const unsigned TYPE_NULL = 0;
  static const unsigned TYPE_BOOLEAN = 1;
  static const unsigned TYPE_INTEGER = 2;
  static const unsigned TYPE_DECIMAL = 3;
  static const unsigned TYPE_STRING = 4;
  static const unsigned TYPE_ARRAY = 5;
};

#endif // GRAM_PHP_TYPE
