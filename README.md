xorrand
=======

a family of hash functions

simple pseudocode:

```
rng.init(1234)
hash = rng()
for c in string:
  hash ^= rng() * c
```

xorrand hash functions have several good properties:
- can produce arbitrarily long hashes with minimal effort by generating more
  random numbers in the loop and saving them in an array
- can be recomputed efficiently for small changes in the file, if the loop uses
  invertible operations such as xor and the rng can jump ahead efficiently
- can easily create a family of n different hash functions by starting with n
  different seeds for bloom filters
- good entropy and avalanche effect for free
