#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
struct CAR
{
    char *company;
    char *model;
    char *color;
    int price;
};
typedef struct CAR car;

char* CleanString(char *str)
{
    free(str);
    str = NULL;
    return str;
}

car* CleanStruct(car* struc)
{
    free(struc);
    struc = NULL;
    return struc;
}

char* Assign(char* str)
{
    char* res = NULL;
    int l = strlen(str);
    res = (char*) malloc((l + 1) * sizeof(char));
    int i;
    for (i = 0; i < l; i++)
    {
        res[i] = str[i];
    }
    res[i] = '\0';
    return res;
}

car Split(char* str, int len, char sep)
{
car res;
char* str1 = NULL;
int i;
int f = 0;
int m = 0;
int j = 0;
char* numb = NULL;
numb = (char*)malloc(10 * sizeof(char));
str = (char*) realloc(str, (len + 2) * sizeof(char));
str[len] = sep;
len++;
str[len] = '\0';



str1 = (char *) malloc(len * sizeof(char));

res.company = NULL;
res.model = NULL;
res.color = NULL;

i = 0;

while (i < len)
    {
        if (str[i] != sep)
        {
            str1[j] = str[i];
            j++;
        }
        else
        {
            str1[j] = '\0';
            str1 = (char*) realloc(str1, (strlen(str1) + 1) * sizeof(char));
            m++;
            f = 1;
        }

        if (m == 1 && f == 1)
        {

            res.company = Assign(str1);
            j = 0;
            str1 = CleanString(str1);
            str1 = (char*) malloc(len * sizeof(char));
        }

        if (m == 2 && f == 1)
        {
            res.model = Assign(str1);
            j = 0;
            str1 = CleanString(str1);
            str1 = (char*) malloc(len * sizeof(char));
        }

        if (m == 3 && f == 1)
        {
            res.color = Assign(str1);
            j = 0;
            str1 = CleanString(str1);
            str1 = (char*) malloc(len * sizeof(char));
        }

        if (m == 4 && f == 1)
        {
            numb = Assign(str1);
            res.price = atoi(numb);
            j = 0;
            numb = CleanString(numb);
            str1 = CleanString(str1);
        }
        f = 0;
        i++;
    }
return res;
}

car* ABC(car* a, int n)
{
    car* res = a;
    car t;
    int i;
    int j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(res[i].company, res[j].company) > 0)
            {
                t = res[i];
                res[i] = res[j];
                res[j] = t;
            }
        }
    }
    return res;
}

void FindAndPrint(car* shop, int n, int n1, int n2, char* col)
{
    car* res = NULL;
    car t;
    int i;
    int j;
    int f = 0;
    res = (car*)malloc(n * sizeof(car));
    i = 0;
    while (i < n)
    {
        if ((strcmp(shop[i].color, col) == 0) && shop[i].price <= n2 && shop[i].price >= n1)
        {
            res[f] = shop[i];
            f++;
        }
        i++;
    }
    res = (car*)realloc(res, f * sizeof(car));
    if (f > 0)
    {
        for (i = 0; i < f - 1; i++)
        {
            for (j = i + 1; j < f; j++)
            {
                if (res[i].price > res[j].price)
                {
                    t = res[i];
                    res[i] = res[j];
                    res[j] = t;
                }
            }
        }
        /*for (i = 0; i < f; i++)
        {
            printf("\n\nCompany: %s", res[i].company);
            printf("\nModel: %s", res[i].model);
            printf("\nColor: %s", res[i].color);
            printf("\nPrice: %d$", res[i].price);
        }*/
        printf("\n");
        for (i = 0; i < f; i++)
            printf("|%10s     ", res[i].company);
        printf("|\n");
        for (i = 0; i < f; i++)
            printf("|%10s     ", res[i].model);
        printf("|\n");
        for (i = 0; i < f; i++)
            printf("|%10s     ", res[i].color);
        printf("|\n");
        for (i = 0; i < f; i++)
            printf("|%9d$     ", res[i].price);
        printf("|\n");
    }
    else
        printf("There is no car like this");
    res = CleanStruct(res);
}

int main()
{
    FILE *in;
    int n;
    char *str1 = NULL;
    int i;
    char sep = '|';
    int slen;
    int j;
    char c;
    char* col = NULL;
    int n1, n2;
    int ans;
    car* shop = NULL;


    if ((in = fopen("cars.txt", "r")) != NULL)
    {
        n = 0;
        c = fgetc(in);
        while(c != EOF)
        {
            if (c == '\n')
                n++;
            c = fgetc(in);
        }
        n++;
        shop =(car*)malloc(n * sizeof(car));
        rewind(in);
        shop = (car*) malloc(n * sizeof(car));
        for (i = 0; i < n; i++)
        {
            str1 = (char *) malloc(MAX * sizeof(char));
            j = 0;
            str1[j] = fgetc(in);
            while (str1[j] !='\n' && str1[j] != EOF)
            {
                j++;
                str1[j] = fgetc(in);
            }

            str1[j] = '\0';

            str1 = (char*) realloc(str1, (strlen(str1) + 1) * sizeof(char));

            slen = strlen(str1);

            str1 = (char *) realloc(str1, slen * sizeof(char));

            shop[i] = Split(str1, slen, sep);

            str1 = CleanString(str1);
        }

        if (fclose(in) == EOF)
            printf("\nError closing!\n");
    }
    else
    {
        printf("\nError opening\n");
        return 0;
    }

    shop = ABC(shop, n);

    /*for (i = 0; i < n; i++)
    {
        printf("\n\nCompany: %s", shop[i].company);
        printf("\nModel: %s", shop[i].model);
        printf("\nColor: %s", shop[i].color);
        printf("\nPrice: %d$", shop[i].price);
    }*/
    ans = 1;
    printf("\nDo you want find your dream car? (1 - yes, 0 - no)\n");
    scanf("%d", &ans);

    while (ans == 1)
    {
        col = (char *) malloc(15 * sizeof(char));
        printf("\nWrite the color you want: ");
        scanf("%s", col);
        col = (char *) realloc(col, (strlen(col) + 1) * sizeof(char));

        printf("\nWrite the price range you want\n\n");
        printf("Lower price:");
        scanf("%d", &n1);
        printf("Higher price:");
        scanf("%d", &n2);

        FindAndPrint(shop, n, n1, n2, col);
        col = CleanString(col);
        /*while (i < n)
        {
            if ((strcmp(shop[i].color, col) == 0) && shop[i].price <= n2 && shop[i].price >= n1)
            {
                printf("\n\nCompany: %s", shop[i].company);
                printf("\nModel: %s", shop[i].model);
                printf("\nColor: %s", shop[i].color);
                printf("\nPrice: %d$", shop[i].price);
                f = 1;
            }
            i++;
        }
        if (f == 0)
            printf("\nThere is no car like this");*/
        printf("\n\nDo you want to repeat? (1 - yes, 0 - no)\n");

        scanf("%d", &ans);
    }

    printf("Have a nice day!");

    str1 = CleanString(str1);
    shop = CleanStruct(shop);
    return 0;
}