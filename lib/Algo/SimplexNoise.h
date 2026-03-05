#ifndef ALGO_SIMPLEX_NOISE_H
#define ALGO_SIMPLEX_NOISE_H

#include <cmath>
namespace Algo {

/**
 * @warning PRECISION LOSS GOTCHA:
 * Do not pass extremely large floating-point numbers (e.g. `> 10^7`) into these
 * noise functions. Internally, Simplex Noise projects coordinates onto an
 * integer grid. Large floats lack the precision to express small fractional
 * differences, and their integer casts can overflow standard 32-bit bounds.
 * This mathematically forces the algorithm to return exactly `0.0` or freeze
 * the noise pattern. When using large pseudo-random seeds, `modulo` them (e.g.,
 * `seed % 10000`) before casting to float.
 */

double snoise2(double x, double y);
double snoise3(double x, double y, double z);
double snoise4(double x, double y, double z, double w);

inline double getSNoise2(double x, double y, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += Algo::snoise2(x, y);
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * Algo::snoise2(x * 2, y * 2);
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * Algo::snoise2(x * 4, y * 4);
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * Algo::snoise2(x * 8, y * 8);
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * Algo::snoise2(x * 16, y * 16);
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * Algo::snoise2(x * 32, y * 32);
  }
  return l_noise;
}

inline double getSNoise3(double x, double y, double z, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += Algo::snoise3(x, y, z);
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * Algo::snoise3(x * 2, y * 2, z * 2);
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * Algo::snoise3(x * 4, y * 4, z * 4);
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * Algo::snoise3(x * 8, y * 8, z * 8);
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * Algo::snoise3(x * 16, y * 16, z * 16);
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * Algo::snoise3(x * 32, y * 32, z * 32);
  }
  return l_noise;
}

inline double getSNoise4(double x, double y, double z, double w, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += Algo::snoise4(x, y, z, w);
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * Algo::snoise4(x * 2, y * 2, z * 2, w * 2);
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * Algo::snoise4(x * 4, y * 4, z * 4, w * 4);
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * Algo::snoise4(x * 8, y * 8, z * 8, w * 8);
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * Algo::snoise4(x * 16, y * 16, z * 16, w * 16);
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * Algo::snoise4(x * 32, y * 32, z * 32, w * 32);
  }
  return l_noise;
}

///////////////////////////////////////////////////////

inline double getSTurbulence2(double x, double y, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += fabs(Algo::snoise2(x, y));
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * fabs(Algo::snoise2(x * 2, y * 2));
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * fabs(Algo::snoise2(x * 4, y * 4));
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * fabs(Algo::snoise2(x * 8, y * 8));
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * fabs(Algo::snoise2(x * 16, y * 16));
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * fabs(Algo::snoise2(x * 32, y * 32));
  }
  return l_noise;
}

inline double getSTurbulence3(double x, double y, double z, int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += fabs(Algo::snoise3(x, y, z));
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * fabs(Algo::snoise3(x * 2, y * 2, z * 2));
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * fabs(Algo::snoise3(x * 4, y * 4, z * 4));
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * fabs(Algo::snoise3(x * 8, y * 8, z * 8));
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * fabs(Algo::snoise3(x * 16, y * 16, z * 16));
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * fabs(Algo::snoise3(x * 32, y * 32, z * 32));
  }
  return l_noise;
}

inline double getSTurbulence4(double x, double y, double z, double w,
                              int octaves) {
  double l_noise = 0;
  // Octaves
  if (octaves & (1 << 0)) {
    l_noise += fabs(Algo::snoise4(x, y, z, w));
  }
  if (octaves & (1 << 1)) {
    l_noise += 0.5 * fabs(Algo::snoise4(x * 2, y * 2, z * 2, w * 2));
  }
  if (octaves & (1 << 2)) {
    l_noise += 0.25 * fabs(Algo::snoise4(x * 4, y * 4, z * 4, w * 4));
  }
  if (octaves & (1 << 3)) {
    l_noise += 0.125 * fabs(Algo::snoise4(x * 8, y * 8, z * 8, w * 8));
  }
  if (octaves & (1 << 4)) {
    l_noise += 0.0625 * fabs(Algo::snoise4(x * 16, y * 16, z * 16, w * 16));
  }
  if (octaves & (1 << 5)) {
    l_noise += 0.03125 * fabs(Algo::snoise4(x * 32, y * 32, z * 32, w * 32));
  }
  return l_noise;
}

} // namespace Algo

#endif
