#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "parseuint8.h"

#ifndef uint
typedef unsigned int uint;
#endif

bool basic_test() {
  printf("basic_test\n");
  for (uint i = 0; i < 256; i++) {
    std::string input = std::to_string(i);
    input.reserve(4);
    uint8_t expected = i;
    uint8_t result;
    parse_uint8_swar(input.data(), input.size(), &result);
    if (result != expected) {
      printf("swar FAILURE %d\n", i);
      return false;
    }
    parse_uint8_fastswar(input.data(), input.size(), &result);
    if (result != expected) {
      printf("fastswar FAILURE %d\n", i);
      return false;
    }
    result = parse_uint8_fastswar_option(input.data(), input.size()).value;
    if (result != expected) {
      printf("fastswar_option FAILURE %d\n", i);
      return false;
    }
    result = parse_uint8_fastswar_rs(input.data(), input.size()).value;
    if (result != expected) {
      printf("fastswar_rs FAILURE %d\n", i);
      return false;
    }
    parse_uint8_fastswar_bob(input.data(), input.size(), &result);
    if (result != expected) {
      printf("fastswar_bob FAILURE %d\n", i);
      return false;
    }
    result = parse_uint8_fastswar_bob_option(input.data(), input.size()).value;
    if (result != expected) {
      printf("fastswar_bob_option FAILURE %d\n", i);
      return false;
    }
    result = parse_uint8_fastswar_bob_rs(input.data(), input.size()).value;
    if (result != expected) {
      printf("fastswar_bob_rs FAILURE %d\n", i);
      return false;
    }
    parse_uint8_fromchars(input.data(), input.size(), &result);
    if (result != expected) {
      printf("fromchars FAILURE %d\n", i);
      return false;
    }
    parse_uint8_naive(input.data(), input.size(), &result);
    if (result != expected) {
      printf("naive FAILURE %d\n", i);
      return false;
    }
    parse_uint8_lut(input.data(), input.size(), &result);
    if (result != expected) {
      printf("lut FAILURE %d\n", i);
      return false;
    }
  }

  for (uint i = 256; i <= 1024; i++) {
    std::string input = std::to_string(i);
    input.reserve(4);
    int r;
    uint8_t result;
    r = parse_uint8_swar(input.data(), input.size(), &result);
    if (r) {
      printf("swar FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fastswar(input.data(), input.size(), &result);
    if (r) {
      printf("fastswar FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fastswar_option(input.data(), input.size()).valid;
    if (r) {
      printf("fastswar_option FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fastswar_rs(input.data(), input.size()).valid;
    if (r) {
      printf("fastswar_rs FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fastswar_bob(input.data(), input.size(), &result);
    if (r) {
      printf("fastswar_bob FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fastswar_bob_option(input.data(), input.size()).valid;
    if (r) {
      printf("fastswar_bob_option FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fastswar_bob_rs(input.data(), input.size()).valid;
    if (r) {
      printf("fastswar_bob_rs FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fromchars(input.data(), input.size(), &result);
    if (r) {
      printf("fromchars FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_naive(input.data(), input.size(), &result);
    if (r) {
      printf("naive FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_lut(input.data(), input.size(), &result);
    if (r) {
      printf("lut FAILURE %d\n", i);
      return false;
    }
  }
  for (uint i = 0; i <= 0xffffff; i++) {
    int r1, r2;
    uint8_t result;
    r1 = parse_uint8_fastswar((const char *)&i, 1, &result);
    r2 = parse_uint8_naive((const char *)&i, 1, &result);
    if (r1 != r2) {
      printf("fastswar mismatch1 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar((const char *)&i, 2, &result);
    r2 = parse_uint8_naive((const char *)&i, 2, &result);
    if (r1 != r2) {
      printf("fastswar mismatch2 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar((const char *)&i, 3, &result);
    r2 = parse_uint8_naive((const char *)&i, 3, &result);
    if (r1 != r2) {
      printf("fastswar mismatch3 %d\n", i);
      return false;
    }

    r1 = parse_uint8_fastswar_option((const char *)&i, 1).valid;
    r2 = parse_uint8_naive((const char *)&i, 1, &result);
    if (r1 != r2) {
      printf("fastswar_option mismatch1 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_option((const char *)&i, 2).valid;
    r2 = parse_uint8_naive((const char *)&i, 2, &result);
    if (r1 != r2) {
      printf("fastswar_option mismatch2 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_option((const char *)&i, 3).valid;
    r2 = parse_uint8_naive((const char *)&i, 3, &result);
    if (r1 != r2) {
      printf("fastswar_option mismatch3 %d\n", i);
      return false;
    }

    r1 = parse_uint8_fastswar_rs((const char *)&i, 1).valid;
    r2 = parse_uint8_naive((const char *)&i, 1, &result);
    if (r1 != r2) {
      printf("fastswar_rs mismatch1 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_rs((const char *)&i, 2).valid;
    r2 = parse_uint8_naive((const char *)&i, 2, &result);
    if (r1 != r2) {
      printf("fastswar_rs mismatch2 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_rs((const char *)&i, 3).valid;
    r2 = parse_uint8_naive((const char *)&i, 3, &result);
    if (r1 != r2) {
      printf("fastswar_rs mismatch3 %d\n", i);
      return false;
    }

    r1 = parse_uint8_fastswar_bob((const char *)&i, 1, &result);
    r2 = parse_uint8_naive((const char *)&i, 1, &result);
    if (r1 != r2) {
      printf("fastswar_bob mismatch1 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_bob((const char *)&i, 2, &result);
    r2 = parse_uint8_naive((const char *)&i, 2, &result);
    if (r1 != r2) {
      printf("fastswar_bob mismatch2 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_bob((const char *)&i, 3, &result);
    r2 = parse_uint8_naive((const char *)&i, 3, &result);
    if (r1 != r2) {
      printf("fastswar_bob mismatch3 %d\n", i);
      return false;
    }

    r1 = parse_uint8_fastswar_bob_option((const char *)&i, 1).valid;
    r2 = parse_uint8_naive((const char *)&i, 1, &result);
    if (r1 != r2) {
      printf("fastswar_bob_option mismatch1 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_bob_option((const char *)&i, 2).valid;
    r2 = parse_uint8_naive((const char *)&i, 2, &result);
    if (r1 != r2) {
      printf("fastswar_bob_option mismatch2 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_bob_option((const char *)&i, 3).valid;
    r2 = parse_uint8_naive((const char *)&i, 3, &result);
    if (r1 != r2) {
      printf("fastswar_bob_option mismatch3 %d\n", i);
      return false;
    }

    r1 = parse_uint8_fastswar_bob_rs((const char *)&i, 1).valid;
    r2 = parse_uint8_naive((const char *)&i, 1, &result);
    if (r1 != r2) {
      printf("fastswar_bob_rs mismatch1 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_bob_rs((const char *)&i, 2).valid;
    r2 = parse_uint8_naive((const char *)&i, 2, &result);
    if (r1 != r2) {
      printf("fastswar_bob_rs mismatch2 %d\n", i);
      return false;
    }
    r1 = parse_uint8_fastswar_bob_rs((const char *)&i, 3).valid;
    r2 = parse_uint8_naive((const char *)&i, 3, &result);
    if (r1 != r2) {
      printf("fastswar_bob_rs mismatch3 %d\n", i);
      return false;
    }

    r1 = parse_uint8_lut((const char *)&i, 1, &result);
    r2 = parse_uint8_naive((const char *)&i, 1, &result);
    if (r1 != r2) {
      printf("lut mismatch1 %d\n", i);
      return false;
    }
    r1 = parse_uint8_lut((const char *)&i, 2, &result);
    r2 = parse_uint8_naive((const char *)&i, 2, &result);
    if (r1 != r2) {
      printf("lut mismatch2 %d\n", i);
      return false;
    }
    r1 = parse_uint8_lut((const char *)&i, 3, &result);
    r2 = parse_uint8_naive((const char *)&i, 3, &result);
    if (r1 != r2) {
      printf("lut mismatch3 %d\n", i);
      return false;
    }
  }

  printf("SUCCESS\n");
  return true;
}

int main() {
  make_lut();
  return (basic_test()) ? EXIT_SUCCESS : EXIT_FAILURE;
}
