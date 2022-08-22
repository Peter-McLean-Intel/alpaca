#include <doctest.hpp>
#include <serialize/serialize.h>

using doctest::test_suite;

#define CONSTRUCT_EXPECTED_VALUE(type, value)                                  \
  type expected_value = value;                                                 \
  std::vector<uint8_t> expected;                                               \
  std::copy(                                                                   \
      static_cast<const char *>(static_cast<const void *>(&expected_value)),   \
      static_cast<const char *>(static_cast<const void *>(&expected_value)) +  \
          sizeof expected_value,                                               \
      std::back_inserter(expected));

TEST_CASE("Deserialize int8_t" * test_suite("signed_integer")) {
  struct my_struct {
    int8_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{5};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 2);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 5);
  }
}

TEST_CASE("Deserialize int16_t (stored as int8_t)" *
          test_suite("signed_integer")) {
  struct my_struct {
    int16_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{99};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 2);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 99);
  }
}

TEST_CASE("Deserialize int16_t" * test_suite("signed_integer")) {
  struct my_struct {
    int16_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{512};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 3);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 512);
  }
}

TEST_CASE("Deserialize int32_t (packed as int8_t)" *
          test_suite("signed_integer")) {
  struct my_struct {
    int32_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{5};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 2);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 5);
  }
}

TEST_CASE("Deserialize int32_t (packed as int16_t)" *
          test_suite("signed_integer")) {
  struct my_struct {
    int32_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{1600};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 3);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 1600);
  }
}

TEST_CASE("Deserialize int32_t" * test_suite("signed_integer")) {
  struct my_struct {
    int32_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{75535};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 5);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 75535);
  }
}

TEST_CASE("Deserialize int64_t (packed as int8_t)" *
          test_suite("signed_integer")) {
  struct my_struct {
    int64_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{5};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 2);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 5);
  }
}

TEST_CASE("Deserialize int64_t (packed as int16_t)" *
          test_suite("signed_integer")) {
  struct my_struct {
    int64_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{12345};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 3);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 12345);
  }
}

TEST_CASE("Deserialize int64_t (packed as int32_t)" *
          test_suite("signed_integer")) {
  struct my_struct {
    int64_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{12345678};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 5);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 12345678);
  }
}

TEST_CASE("Deserialize int64_t" * test_suite("signed_integer")) {
  struct my_struct {
    int64_t value;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{5294967295};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 9);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.value == 5294967295);
  }
}

TEST_CASE("Deserialize signed integer types" * test_suite("integer")) {
  struct my_struct {
    int8_t a;
    int16_t b;
    int32_t c;
    int64_t d;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{-5, -12345, -12345678, -5294967295};
    bytes = serialize(s);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.a == -5);
    REQUIRE(result.b == -12345);
    REQUIRE(result.c == -12345678);
    REQUIRE(result.d == -5294967295);
  }
}

TEST_CASE("Deserialize signed and unsigned integer types" *
          test_suite("integer")) {
  struct my_struct {
    int8_t a;
    int16_t b;
    int32_t c;
    int64_t d;
    uint8_t e;
    uint16_t f;
    uint32_t g;
    uint64_t h;
  };

  std::vector<uint8_t> bytes;

  // serialize
  {
    my_struct s{-5, -12345, -12345678, -5294967295,
                5,  12345,  12345678,  5294967295};
    bytes = serialize(s);
    REQUIRE(bytes.size() == 31);
  }

  // deserialize
  {
    auto result = deserialize<my_struct>(bytes);
    REQUIRE(result.a == -5);
    REQUIRE(result.b == -12345);
    REQUIRE(result.c == -12345678);
    REQUIRE(result.d == -5294967295);
    REQUIRE(result.e == 5);
    REQUIRE(result.f == 12345);
    REQUIRE(result.g == 12345678);
    REQUIRE(result.h == 5294967295);
  }
}