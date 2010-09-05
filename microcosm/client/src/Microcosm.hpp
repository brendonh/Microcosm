#ifndef __MICROCOSM_MICROCOSM
#define __MICROCOSM_MICROCOSM

// Suppress unused parameter warnings
#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

#define PI 3.1415927
#define TWOPI (2*PI)
#define DEG2RAD (PI / 180.f)
#define RAD2DEG (180.f / PI)

#endif
