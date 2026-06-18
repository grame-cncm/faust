### Exp 2 and Exp 10 optimizations (maybe Log 2 and Log 10 too)

`C++` fast math reference in `fastmath.cpp`

```
float fast_exp10f(float x)
{
    return powFastLookup(x, 3.32192809488736f, pow_table, pow_precision);
}
```

```
float fast_exp2f(float x)
{
    return powFastLookup(x, 1.0f, pow_table, pow_precision);
}
```

```
/**
 * Get pow (fast!).
 *
 * @val        power to raise radix to
 * @ilog2      one over log, to required radix, of two
 * @pTable     length must be 2 ^ precision
 * @precision  number of mantissa bits used, >= 0 and <= 18
 */
static float powFastLookup(const float val, const float ilog2, const uint32_t* pTable,
                           const uint32_t precision)
{
    /* build float bits */
    const int32_t i = (int32_t)((val * (_2p23 * ilog2)) + (127.0f * _2p23));

    /* replace mantissa with lookup */
    const int32_t it = (i & 0xFF800000) | pTable[(i & 0x7FFFFF) >>  /* E */
                                                 (23 - precision)]; /* F */

    /* convert bits to float */
    return *(const float*)(&it);
}
```
