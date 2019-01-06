#define R ??
#define S ??
#define T ??

long A[R][S][T];

long
ele (long i, long j, long k)
{
  return A[R - i][1 - j][k - 1];
}
