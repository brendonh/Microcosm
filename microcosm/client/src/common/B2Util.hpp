#pragma once
#ifndef __MICROCOSM_COMMON_B2UTIL
#define __MICROCOSM_COMMON_B2UTIL

inline b2Vec2 rad2vec(float r) {
  return b2Vec2(cos(r), sin(r));
}

inline float vec2rad(b2Vec2 v) {
   return atan2(v.y, v.x);
}

#endif
