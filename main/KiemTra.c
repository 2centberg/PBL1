#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    FILE *in = fopen("D:\\PBL1\\Main\\MATRAN.RAND", "r");
    FILE *out = fopen("D:\\PBL1\\Main\\MATRAN.OUT", "r");
    fscanf(in, "%d", &n);
    double** a, ** b, ** c;
    a = (double**)malloc((n + 1) * sizeof(double*));
    b = (double**)malloc((n + 1) * sizeof(double*));
    c = (double**)malloc((n + 1) * sizeof(double*));
    for (int i = 1; i <= n; i++) {
        a[i] = (double*)malloc((n+1) * sizeof(double*));
        b[i] = (double*)malloc((n+1) * sizeof(double*));
        c[i] = (double*)malloc((n+1) * sizeof(double*));
    }
    for (int i = 1;i <= n;i++)
        for(int j=1;j<=n;j++) 
        {
            fscanf(in, "%lf", &a[i][j]);
            fscanf(out, "%lf", &b[i][j]);
        }
    fclose(in); fclose(out);
    for (int i = 1;i<=n;i++)
        for(int j=1;j<=n;j++) 
        {
            c[i][j] = 0;
            for (int k=1;k<=n;k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    FILE *tich = fopen("D:\\PBL1\\Main\\MATRAN.TICH", "w"); 
    for (int i = 1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) 
        {
            fprintf(tich, "%+-1.3lf\t",c[i][j]);
        }
        fputc('\n', tich);
    }
    fclose(tich);
}