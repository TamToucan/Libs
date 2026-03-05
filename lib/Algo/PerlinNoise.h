#ifndef ALGO_PERLIN_NOISE_H
#define ALGO_PERLIN_NOISE_H

#include <cmath>
namespace Algo {

/**
 * @warning PRECISION LOSS GOTCHA:
 * Do not pass extremely large floating-point numbers (e.g. `> 10^7`) into these
 * noise functions. Internally, Perlin Noise projects coordinates onto an
 * integer grid via `floor()`. Large floats lack the precision to express small
 * fractional differences, and integer casts can overflow 32-bit bounds. This
 * mathematically forces the algorithm to return exactly `0.0` or freeze the
 * noise pattern. When using large pseudo-random seeds, `modulo` them (e.g.,
 * `seed % 10000`) before casting to float.
 */

double noise2(double x, double y);
double noise3(double x, double y, double z);

inline double getNoise2(double x, double y, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += Algo::noise2(x, y);
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * Algo::noise2(x * 2, y * 2);
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * Algo::noise2(x * 4, y * 4);
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * Algo::noise2(x * 8, y * 8);
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * Algo::noise2(x * 16, y * 16);
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * Algo::noise2(x * 32, y * 32);
  }
  return l_noise;
}

inline double getNoise3(double x, double y, double z, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += Algo::noise3(x, y, z);
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * Algo::noise3(x * 2, y * 2, z * 2);
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * Algo::noise3(x * 4, y * 4, z * 4);
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * Algo::noise3(x * 8, y * 8, z * 8);
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * Algo::noise3(x * 16, y * 16, z * 16);
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * Algo::noise3(x * 32, y * 32, z * 32);
  }
  return l_noise;
}

///////////////////////////////////////////////////////

inline double getTurbulence2(double x, double y, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += fabs(Algo::noise2(x, y));
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * fabs(Algo::noise2(x * 2, y * 2));
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * fabs(Algo::noise2(x * 4, y * 4));
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * fabs(Algo::noise2(x * 8, y * 8));
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * fabs(Algo::noise2(x * 16, y * 16));
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * fabs(Algo::noise2(x * 32, y * 32));
  }
  return l_noise;
}

inline double getTurbulence3(double x, double y, double z, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += fabs(Algo::noise3(x, y, z));
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * fabs(Algo::noise3(x * 2, y * 2, z * 2));
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * fabs(Algo::noise3(x * 4, y * 4, z * 4));
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * fabs(Algo::noise3(x * 8, y * 8, z * 8));
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * fabs(Algo::noise3(x * 16, y * 16, z * 16));
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * fabs(Algo::noise3(x * 32, y * 32, z * 32));
  }
  return l_noise;
}

} // namespace Algo

#endif
