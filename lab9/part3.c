#define N = 10 //Error
#define INC(x) x+1
#define SUB(x,y) x-y
#define SQR(x) ((x)*(x))
#define CUBE(x) (SQR(x)*(x))
#define M1(x,y) x##y (concat)
#define M2(x,y) #x #y (string)

int main(void){

    int a[N], i, j, k , m;
#ifdef N
    i = j; 
#else 
    j = i; 
#endif

    i = 10 * INC(j);      

    i = SUB(j, k);
    i = SQR(SQR(j));
    i = CUBE(j);
    i = M1(j, k);
    puts(M2(i, j));

#undef SQR
    i = SQR(j);
#define SQR
    i = SQR(j);

    return 0;
}


int main(void){

    int a[= 10], i, j, k , m;

    i = j; // Error

    i = 10 * j+1;      

    i = j - k
    i = ((j)*(j))*((j)*(j));
    i = (j*j)*(j);
    i = j##k
    puts(#i #j);


    i = SQR(j); //Error
    i = (j);

    return 0;
}
