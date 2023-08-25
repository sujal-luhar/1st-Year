#include <stdio.h>

void bubble(int B[], int n);


int main()
{
    int n=1, i, j;
    int A[n], tub;

    // printf("SIZE: ");
    // scanf("%d", &n);

    for(i=0;i<n;i++,n++)
    {
        fflush(stdin);
        scanf("%d",&tub);
        fflush(stdin);
        if(tub==0)
        {
            break;
        }
        A[i]=tub;
        
    }
    // for(i=0;i<n;i++)
    // {
    //     scanf("%d",&A[i]);
    // }
    bubble(A,n);
    for(i=0;i<n;i++)
    {
        printf("%d ",A[i]);
    }
    return 0;
}

void bubble(int B[], int n)
{
    int temp, i, j;
    int flag=1;
    for(i=0; i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(B[j]<B[j+1])
            {
                flag=0;
                temp=B[j];
                B[j]=B[j+1];
                B[j+1]=temp;
            }
            if(flag==1)
            break;
        }
    }
}
