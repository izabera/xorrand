#include <stdint.h>

uint64_t state = 2549297995355413924ULL,
         init  = 2549297995355413924ULL,
         inc   = 4865540595714422341ULL;

uint32_t pcg32() {
  uint64_t oldstate = state;
  state = oldstate * 6364136223846793005ULL + inc;
  uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
  uint32_t rot = oldstate >> 59u;
  return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

// same as wide_xorrand with n = 1
uint32_t xorrand(const char *str) {
  state = init;
  uint32_t hash = pcg32();
  while (*str) hash ^= pcg32() * *str++;
  return hash;
}

void wide_xorrand(const char *str, int n, uint32_t *buf) {
  state = init;
  for (int i = 0; i < n; i++)
    buf[i] = pcg32();
  while (*str)
    for (int i = 0, c = *str++; i < n; i++)
      buf[i] ^= pcg32() * c;
}

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc == 1) return 1;
  if (argc == 2) {
    printf("%08x\n", xorrand(argv[1]));
  }
  else {
    int width = atoi(argv[1]);
    if (!width) return 1;
    uint32_t *buf = malloc(width * sizeof(*buf));
    if (!buf) return 1;
    wide_xorrand(argv[2], width, buf);
    for (int i = 0; i < width; i++) printf("%08x", buf[i]);
    putchar('\n');
  }
  return 0;
}
