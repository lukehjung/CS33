#define A 5; 
#define B 7; 

typedef struct{
  int x [A][B];
  long y;
} str1;

typedef struct {
  char array [B];
  int t;
  short s [A];
} str2;

void setVal(str1 *p, str2 *q){
  long v1 = q->t;
  long v2 = q->u;
  p->y = v1+v2;
}
