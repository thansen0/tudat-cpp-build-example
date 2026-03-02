#ifndef SOFA_STUB_SOFA_H
#define SOFA_STUB_SOFA_H

#ifdef __cplusplus
extern "C" {
#endif

static inline double iauFad03(double t) { (void)t; return 0.0; }
static inline double iauFaf03(double t) { (void)t; return 0.0; }
static inline double iauFal03(double t) { (void)t; return 0.0; }
static inline double iauFalp03(double t) { (void)t; return 0.0; }
static inline double iauFaom03(double t) { (void)t; return 0.0; }
static inline double iauGmst06(double uta, double utb, double tta, double ttb)
{ (void)uta; (void)utb; (void)tta; (void)ttb; return 0.0; }
static inline double iauGmst00(double uta, double utb, double tta, double ttb)
{ (void)uta; (void)utb; (void)tta; (void)ttb; return 0.0; }
static inline double iauEe00a(double date1, double date2) { (void)date1; (void)date2; return 0.0; }
static inline double iauEe00b(double date1, double date2) { (void)date1; (void)date2; return 0.0; }
static inline double iauEe06a(double date1, double date2) { (void)date1; (void)date2; return 0.0; }
static inline void iauPnm80(double date1, double date2, double rmatpn[3][3])
{
    (void)date1; (void)date2;
    for (int i = 0; i < 3; ++i) { for (int j = 0; j < 3; ++j) { rmatpn[i][j] = (i == j) ? 1.0 : 0.0; } }
}
static inline void iauPrec76(double ep01, double ep02, double ep11, double ep12, double* zeta, double* z, double* theta)
{
    (void)ep01; (void)ep02; (void)ep11; (void)ep12;
    if (zeta) { *zeta = 0.0; } if (z) { *z = 0.0; } if (theta) { *theta = 0.0; }
}
static inline double iauEra00(double dj1, double dj2) { (void)dj1; (void)dj2; return 0.0; }
static inline void iauBp06(double date1, double date2, double rb[3][3], double rp[3][3], double rbp[3][3])
{
    (void)date1; (void)date2;
    for (int i = 0; i < 3; ++i) { for (int j = 0; j < 3; ++j) { rb[i][j] = (i == j); rp[i][j] = (i == j); rbp[i][j] = (i == j); } }
}
static inline void iauBp00(double date1, double date2, double rb[3][3], double rp[3][3], double rbp[3][3])
{
    iauBp06(date1, date2, rb, rp, rbp);
}
static inline void iauXys00a(double date1, double date2, double* x, double* y, double* s)
{
    (void)date1; (void)date2; if (x) { *x = 0.0; } if (y) { *y = 0.0; } if (s) { *s = 0.0; }
}
static inline void iauXys00b(double date1, double date2, double* x, double* y, double* s)
{
    iauXys00a(date1, date2, x, y, s);
}
static inline void iauXys06a(double date1, double date2, double* x, double* y, double* s)
{
    iauXys00a(date1, date2, x, y, s);
}
static inline int iauJd2cal(double dj1, double dj2, int* iy, int* im, int* id, double* fd)
{
    (void)dj1; (void)dj2;
    if (iy) { *iy = 2000; } if (im) { *im = 1; } if (id) { *id = 1; } if (fd) { *fd = 0.0; }
    return 0;
}
static inline int iauDat(int iy, int im, int id, double fd, double* deltat)
{
    (void)iy; (void)im; (void)id; (void)fd;
    if (deltat) { *deltat = 0.0; }
    return 0;
}
static inline double iauDtdb(double date1, double date2, double ut, double elong, double u, double v)
{
    (void)date1; (void)date2; (void)ut; (void)elong; (void)u; (void)v;
    return 0.0;
}
static inline double iauSp00(double date1, double date2) { (void)date1; (void)date2; return 0.0; }

#ifdef __cplusplus
}
#endif

#endif
