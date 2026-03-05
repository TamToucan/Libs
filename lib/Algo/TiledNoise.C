#include "TiledNoise.h"
#include "PerlinNoise.h"
#include "SimplexNoise.h"

namespace Algo {

//
// 1D
//
double tiledNoise1(double x, int octaves, double mult, double w, double time)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double l_noise =  (
            (    getNoise2(xm,time,octaves)
                    * wx )
            + (    getNoise2(xm_m,time,octaves)
                    * (x) )
    ) / (w);
    return l_noise;
}

//
// 2D
//
double tiledNoise2NoTime(double x, double y, int octaves, double mult, double w, double h)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double l_noise =  (
            (    getNoise2(xm,ym,octaves)
                    * wx
                    * hy )
            + (    getNoise2(xm_m,ym,octaves)
                    * (x)
                    * hy )
            + (    getNoise2(xm_m,ym_m,octaves)
                    * (x)
                    * (y) )
            + (    getNoise2(xm,ym_m,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

double tiledNoise2(double x, double y, int octaves, double mult, double w, double h, double time)
{    if (time == 0) return tiledNoise2NoTime(x,y,octaves,mult,w,h);
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;


    double l_noise =  (
            (    getNoise3(xm,ym,time,octaves)
                    * wx
                    * hy )
            + (    getNoise3(xm_m,ym,time,octaves)
                    * (x)
                    * hy )
            + (    getNoise3(xm_m,ym_m,time,octaves)
                    * (x)
                    * (y) )
            + (    getNoise3(xm,ym_m,time,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

//
// 3D
//
double tiledNoise3(double x, double y, double z, int octaves, double mult, double w, double h, double d)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;
    double l_noise = (
            (    getNoise3(xm,ym,zm,octaves)
                 * wx
                 * hy
                 * dz )
            + (    getNoise3(xm_m,ym,zm,octaves)
                * (x)
                * hy
                * dz )
            + (    getNoise3(xm_m,ym_m,zm,octaves)
                * (x)
                * (y)
                * dz )
            + (    getNoise3(xm,ym_m,zm,octaves)
                * wx
                * (y)
                * dz )


            + (    getNoise3(xm,ym,zm_m,octaves)
                * wx
                * hy
                * (z) )
            + (    getNoise3(xm_m,ym,zm_m,octaves)
                    * (x)
                    * hy
                    * (z) )
            + (    getNoise3(xm_m,ym_m,zm_m,octaves)
                    * (x)
                    * (y)
                    * (z) )
            + (    getNoise3(xm,ym_m,zm_m,octaves)
                    * wx
                    * (y)
                    * (z) )

            ) / (w*h*d) ;
    return l_noise;
}


//
// 1D
//
double tiledTurbulence1(double x, int octaves, double mult, double w, double time)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double l_noise =  (
            (    getTurbulence2(xm,time,octaves)
                    * wx )
            + (    getTurbulence2(xm_m,time,octaves)
                    * (x) )
    ) / (w);
    return l_noise;
}

//
// 2D
//
double tiledTurbulence2NoTime(double x, double y, int octaves, double mult, double w, double h)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double l_noise =  (
            (    getTurbulence2(xm,ym,octaves)
                    * wx
                    * hy )
            + (    getTurbulence2(xm_m,ym,octaves)
                    * (x)
                    * hy )
            + (    getTurbulence2(xm_m,ym_m,octaves)
                    * (x)
                    * (y) )
            + (    getTurbulence2(xm,ym_m,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

double tiledTurbulence2(double x, double y, int octaves, double mult, double w, double h, double time)
{    if (time == 0) return tiledTurbulence2NoTime(x,y,octaves,mult,w,h);
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;


    double l_noise =  (
            (    getTurbulence3(xm,ym,time,octaves)
                    * wx
                    * hy )
            + (    getTurbulence3(xm_m,ym,time,octaves)
                    * (x)
                    * hy )
            + (    getTurbulence3(xm_m,ym_m,time,octaves)
                    * (x)
                    * (y) )
            + (    getTurbulence3(xm,ym_m,time,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

//
// 3D
//
double tiledTurbulence3(double x, double y, double z, int octaves, double mult, double w, double h, double d)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;
    double l_noise = (
            (    getTurbulence3(xm,ym,zm,octaves)
                 * wx
                 * hy
                 * dz )
            + (    getTurbulence3(xm_m,ym,zm,octaves)
                * (x)
                * hy
                * dz )
            + (    getTurbulence3(xm_m,ym_m,zm,octaves)
                * (x)
                * (y)
                * dz )
            + (    getTurbulence3(xm,ym_m,zm,octaves)
                * wx
                * (y)
                * dz )


            + (    getTurbulence3(xm,ym,zm_m,octaves)
                * wx
                * hy
                * (z) )
            + (    getTurbulence3(xm_m,ym,zm_m,octaves)
                    * (x)
                    * hy
                    * (z) )
            + (    getTurbulence3(xm_m,ym_m,zm_m,octaves)
                    * (x)
                    * (y)
                    * (z) )
            + (    getTurbulence3(xm,ym_m,zm_m,octaves)
                    * wx
                    * (y)
                    * (z) )

            ) / (w*h*d) ;
    return l_noise;
}

//===============================================================
// SIMPLEX VERSIONS
//===============================================================

//
// 1D
//
double tiledSNoise1(double x, int octaves, double mult, double w, double time)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double l_noise =  (
            (    getSNoise2(xm,time,octaves)
                    * wx )
            + (    getSNoise2(xm_m,time,octaves)
                    * (x) )
    ) / (w);
    return l_noise;
}

//
// 2D
//
double tiledSNoise2NoTime(double x, double y, int octaves, double mult, double w, double h)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double l_noise =  (
            (    getSNoise2(xm,ym,octaves)
                    * wx
                    * hy )
            + (    getSNoise2(xm_m,ym,octaves)
                    * (x)
                    * hy )
            + (    getSNoise2(xm_m,ym_m,octaves)
                    * (x)
                    * (y) )
            + (    getSNoise2(xm,ym_m,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

double tiledSNoise2(double x, double y, int octaves, double mult, double w, double h, double time)
{    if (time==0) return tiledSNoise2NoTime(x,y,octaves,mult,w,h);
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;

    double l_noise =  (
            (    getSNoise3(xm,ym,time,octaves)
                    * wx
                    * hy )
            + (    getSNoise3(xm_m,ym,time,octaves)
                    * (x)
                    * hy )
            + (    getSNoise3(xm_m,ym_m,time,octaves)
                    * (x)
                    * (y) )
            + (    getSNoise3(xm,ym_m,time,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

//
// 3D
//
double tiledSNoise3NoTime(double x, double y, double z, int octaves, double mult, double w, double h, double d)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;
    double l_noise = (
            (    getSNoise3(xm,ym,zm,octaves)
                 * wx
                 * hy
                 * dz )
            + (    getSNoise3(xm_m,ym,zm,octaves)
                * (x)
                * hy
                * dz )
            + (    getSNoise3(xm_m,ym_m,zm,octaves)
                * (x)
                * (y)
                * dz )
            + (    getSNoise3(xm,ym_m,zm,octaves)
                * wx
                * (y)
                * dz )


            + (    getSNoise3(xm,ym,zm_m,octaves)
                * wx
                * hy
                * (z) )
            + (    getSNoise3(xm_m,ym,zm_m,octaves)
                    * (x)
                    * hy
                    * (z) )
            + (    getSNoise3(xm_m,ym_m,zm_m,octaves)
                    * (x)
                    * (y)
                    * (z) )
            + (    getSNoise3(xm,ym_m,zm_m,octaves)
                    * wx
                    * (y)
                    * (z) )

            ) / (w*h*d) ;
    return l_noise;
}

double tiledSNoise3(double x, double y, double z, int octaves, double mult, double w, double h, double d, double time)
{    if (time == 0) return tiledSNoise3NoTime(x,y,z,octaves,mult,w,h,d);
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;

    double l_noise = (
            (    getSNoise4(xm,ym,zm,time,octaves)
                 * wx
                 * hy
                 * dz )
            + (    getSNoise4(xm_m,ym,zm,time,octaves)
                * (x)
                * hy
                * dz )
            + (    getSNoise4(xm_m,ym_m,zm,time,octaves)
                * (x)
                * (y)
                * dz )
            + (    getSNoise4(xm,ym_m,zm,time,octaves)
                * wx
                * (y)
                * dz )


            + (    getSNoise4(xm,ym,zm_m,time,octaves)
                * wx
                * hy
                * (z) )
            + (    getSNoise4(xm_m,ym,zm_m,time,octaves)
                    * (x)
                    * hy
                    * (z) )
            + (    getSNoise4(xm_m,ym_m,zm_m,time,octaves)
                    * (x)
                    * (y)
                    * (z) )
            + (    getSNoise4(xm,ym_m,zm_m,time,octaves)
                    * wx
                    * (y)
                    * (z) )

            ) / (w*h*d) ;
    return l_noise;
}

//
// 4D
//
double tiledNoise4(double x, double y, double z, double ww, int octaves, double mult, double w, double h, double d, double t)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;
    double wwm = ww / t * mult;
    double tw = t - ww;
    double l_noise = (
            (    getSNoise4(xm,ym,zm,wwm,octaves)
                 * wx
                 * hy
                 * dz
                 * tw)
            + (    getSNoise4(xm_m,ym,zm,wwm,octaves)
                * (x)
                * hy
                * dz
                * tw)
            + (    getSNoise4(xm_m,ym_m,zm,wwm,octaves)
                * (x)
                * (y)
                * dz
                * tw)
            + (    getSNoise4(xm,ym_m,zm,wwm,octaves)
                * wx
                * (y)
                * dz
                * tw)


            + (    getSNoise4(xm,ym,zm_m,wwm,octaves)
                * wx
                * hy
                * (z)
                * tw)
            + (    getSNoise4(xm_m,ym,zm_m,wwm,octaves)
                * (x)
                * hy
                * (z)
                * tw)
            + (    getSNoise4(xm_m,ym_m,zm_m,wwm,octaves)
                * (x)
                * (y)
                * (z)
                * tw)
            + (    getSNoise4(xm,ym_m,zm_m,wwm,octaves)
                * wx
                * (y)
                * (z)
                * tw)
                    
            + (  getSNoise4(xm,ym,zm,wwm,octaves)
                * wx
                * hy
                * dz
                * (ww))
            + (    getSNoise4(xm_m,ym,zm,wwm,octaves)
                * (x)
                * hy
                * dz
                * (ww))
            + (    getSNoise4(xm_m,ym_m,zm,wwm,octaves)
                * (x)
                * (y)
                * dz
                * (ww))
            + (    getSNoise4(xm,ym_m,zm,wwm,octaves)
                * wx
                * (y)
                * dz
                * (ww))


            + (    getSNoise4(xm,ym,zm_m,wwm,octaves)
                * wx
                * hy
                * (z)
                * (ww))
            + (    getSNoise4(xm_m,ym,zm_m,wwm,octaves)
                * (x)
                * hy
                * (z)
                * (ww))
            + (    getSNoise4(xm_m,ym_m,zm_m,wwm,octaves)
                * (x)
                * (y)
                * (z)
                * (ww))
            + (    getSNoise4(xm,ym_m,zm_m,wwm,octaves)
                * wx
                * (y)
                * (z)
                * (ww))

            ) / (w*h*d*t) ;
    return l_noise;
}


//===================
// Turb
//==================

//
// 1D
//
double tiledSTurbulence1(double x, int octaves, double mult, double w, double time)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double l_noise =  (
            (    getSTurbulence2(xm,time,octaves)
                    * wx )
            + (  getSTurbulence2(xm_m,time,octaves)
                    * (x) )
    ) / (w);
    return l_noise;
}


//
// 2D
//
double tiledSTurbulence2NoTime(double x, double y, int octaves, double mult, double w, double h)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double l_noise =  (
            (    getSTurbulence2(xm,ym,octaves)
                    * wx
                    * hy )
            + (    getSTurbulence2(xm_m,ym,octaves)
                    * (x)
                    * hy )
            + (    getSTurbulence2(xm_m,ym_m,octaves)
                    * (x)
                    * (y) )
            + (    getSTurbulence2(xm,ym_m,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

double tiledSTurbulence2(double x, double y, int octaves, double mult, double w, double h, double time)
{    if (time==0) return tiledSTurbulence2NoTime(x,y,octaves,mult,w,h);
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;

    double l_noise =  (
            (    getSTurbulence3(xm,ym,time,octaves)
                    * wx
                    * hy )
            + (    getSTurbulence3(xm_m,ym,time,octaves)
                    * (x)
                    * hy )
            + (    getSTurbulence3(xm_m,ym_m,time,octaves)
                    * (x)
                    * (y) )
            + (    getSTurbulence3(xm,ym_m,time,octaves)
                    * wx
                    * (y) )
    ) / (w*h);
    return l_noise;
}

//
// 3D
//
double tiledSTurbulence3NoTime(double x, double y, double z, int octaves, double mult, double w, double h, double d)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;
    double l_noise = (
            (    getSTurbulence3(xm,ym,zm,octaves)
                 * wx
                 * hy
                 * dz )
            + (    getSTurbulence3(xm_m,ym,zm,octaves)
                * (x)
                * hy
                * dz )
            + (    getSTurbulence3(xm_m,ym_m,zm,octaves)
                * (x)
                * (y)
                * dz )
            + (    getSTurbulence3(xm,ym_m,zm,octaves)
                * wx
                * (y)
                * dz )


            + (    getSTurbulence3(xm,ym,zm_m,octaves)
                * wx
                * hy
                * (z) )
            + (    getSTurbulence3(xm_m,ym,zm_m,octaves)
                    * (x)
                    * hy
                    * (z) )
            + (    getSTurbulence3(xm_m,ym_m,zm_m,octaves)
                    * (x)
                    * (y)
                    * (z) )
            + (    getSTurbulence3(xm,ym_m,zm_m,octaves)
                    * wx
                    * (y)
                    * (z) )

            ) / (w*h*d) ;
    return l_noise;
}

double tiledSTurbulence3(double x, double y, double z, int octaves, double mult, double w, double h, double d, double time)
{    if (time == 0) return tiledSTurbulence3NoTime(x,y,z,octaves,mult,w,h,d);
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;

    double l_noise = (
            (    getSNoise4(xm,ym,zm,time,octaves)
                 * wx
                 * hy
                 * dz )
            + (    getSNoise4(xm_m,ym,zm,time,octaves)
                * (x)
                * hy
                * dz )
            + (    getSNoise4(xm_m,ym_m,zm,time,octaves)
                * (x)
                * (y)
                * dz )
            + (    getSNoise4(xm,ym_m,zm,time,octaves)
                * wx
                * (y)
                * dz )


            + (    getSNoise4(xm,ym,zm_m,time,octaves)
                * wx
                * hy
                * (z) )
            + (    getSNoise4(xm_m,ym,zm_m,time,octaves)
                    * (x)
                    * hy
                    * (z) )
            + (    getSNoise4(xm_m,ym_m,zm_m,time,octaves)
                    * (x)
                    * (y)
                    * (z) )
            + (    getSNoise4(xm,ym_m,zm_m,time,octaves)
                    * wx
                    * (y)
                    * (z) )

            ) / (w*h*d) ;
    return l_noise;
}

//
// 4D
//
double tiledSTurbulence4(double x, double y, double z, double ww, int octaves, double mult, double w, double h, double d, double t)
{
    double xm = x / w * mult;
    double xm_m = xm - mult;
    double wx = w - x;
    double ym = y / h * mult;
    double ym_m = ym - mult;
    double hy = h - y;
    double zm = z / d * mult;
    double zm_m = zm - mult;
    double dz = d - z;
    double wwm = ww / t * mult;
    double tw = t - ww;
    double l_noise = (
            (    getSTurbulence4(xm,ym,zm,wwm,octaves)
                 * wx
                 * hy
                 * dz
                 * tw)
            + (    getSTurbulence4(xm_m,ym,zm,wwm,octaves)
                * (x)
                * hy
                * dz
                * tw)
            + (    getSTurbulence4(xm_m,ym_m,zm,wwm,octaves)
                * (x)
                * (y)
                * dz
                * tw)
            + (    getSTurbulence4(xm,ym_m,zm,wwm,octaves)
                * wx
                * (y)
                * dz
                * tw)


            + (    getSTurbulence4(xm,ym,zm_m,wwm,octaves)
                * wx
                * hy
                * (z)
                * tw)
            + (    getSTurbulence4(xm_m,ym,zm_m,wwm,octaves)
                * (x)
                * hy
                * (z)
                * tw)
            + (    getSTurbulence4(xm_m,ym_m,zm_m,wwm,octaves)
                * (x)
                * (y)
                * (z)
                * tw)
            + (    getSTurbulence4(xm,ym_m,zm_m,wwm,octaves)
                * wx
                * (y)
                * (z)
                * tw)
                    
            + (  getSTurbulence4(xm,ym,zm,wwm,octaves)
                * wx
                * hy
                * dz
                * (ww))
            + (    getSTurbulence4(xm_m,ym,zm,wwm,octaves)
                * (x)
                * hy
                * dz
                * (ww))
            + (    getSTurbulence4(xm_m,ym_m,zm,wwm,octaves)
                * (x)
                * (y)
                * dz
                * (ww))
            + (    getSTurbulence4(xm,ym_m,zm,wwm,octaves)
                * wx
                * (y)
                * dz
                * (ww))


            + (    getSTurbulence4(xm,ym,zm_m,wwm,octaves)
                * wx
                * hy
                * (z)
                * (ww))
            + (    getSTurbulence4(xm_m,ym,zm_m,wwm,octaves)
                * (x)
                * hy
                * (z)
                * (ww))
            + (    getSTurbulence4(xm_m,ym_m,zm_m,wwm,octaves)
                * (x)
                * (y)
                * (z)
                * (ww))
            + (    getSTurbulence4(xm,ym_m,zm_m,wwm,octaves)
                * wx
                * (y)
                * (z)
                * (ww))

            ) / (w*h*d*t) ;
    return l_noise;
}


}
