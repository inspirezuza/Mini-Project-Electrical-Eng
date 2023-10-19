#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student STD;

struct Student
{
    long long ID;
    char Name[100];
    int Group;
    float Back50; // Back Stroke Swimming best time
    float Breast50;
    float Fly50;
    float Free50;
    STD *next;
};

typedef struct StudentList
{
    int count;          // total number of STD in this list
    char ListType[100]; // list type
    STD *First;         // the first STD in this list
    STD *Last;          // the last STD in this list
} STDList;

void AddList(STDList *plist, STD newSTD)
{
    STD *p = (STD *)malloc(sizeof(STD));
    if (p == NULL)
    {
        printf("out of memory 10");
        exit(10);
    }
    *p = newSTD; // copy entire struct
    if (plist->count == 0)
    { // empty list
        plist->count = 1;
        plist->First = p;
        plist->Last = p;
    }
    else
    { // at least 1 student in the list
        plist->count++;
        plist->Last->next = p;
        plist->Last = p;
    }
}

long long int A2I(char *s)
{
    int i = 0;
    long long num = 0;
    while (s[i])
    {
        num = 10 * num + s[i] - '0';
        i++;
    }
    return num;
}
void RandomTime(STD *p, int randseed)
{
    srand(randseed);
    p->Back50 = 26 + (double)(rand() % 100) * 0.1;
    p->Breast50 = 28 + (double)(rand() % 1000) * 0.01;
    p->Fly50 = 24 + (double)(rand() % 1000) * 0.01;
    p->Free50 = 22 + (double)(rand() % 1000) * 0.01;
}

void PrintList(STDList *plist)
{
    printf("\nList %s\n", plist->ListType);
    if (plist->count)
    {
        printf("has %d students\n", plist->count);
        int i;
        STD *p = plist->First;
        for (i = 0; i < plist->count; i++)
        {
            printf("ID = %lld, Name = %-20s, group %3d, Time: %5.2f %5.2f %5.2f %5.2f s\n", p->ID, p->Name, p->Group, p->Back50, p->Breast50, p->Fly50, p->Free50);
            p = p->next;
        }
        printf("End of List\n\n");
    }
    else
    {
        printf("is Empty List\n");
    }
}

void PrintArray(STD *STDArr[], int size)
{
    if (size > 0)
    {
        printf("Array has %d students\n", size);
        int i;
        STD *p;
        for (i = 0; i < size; i++)
        {
            p = STDArr[i];
            printf("ID = %lld, Name = %-20s, group %3d, Time: %5.2f %5.2f %5.2f %5.2f s\n", p->ID, p->Name, p->Group, p->Back50, p->Breast50, p->Fly50, p->Free50);
        }
        printf("End of Array\n\n");
    }
    else
    {
        printf("is Empty Array\n");
    }
}

void PrintArray2(STD **STDArr[], int size)
{
    if (size > 0)
    {
        printf("Array has %d students\n", size);
        int i;
        STD *p;
        for (i = 0; i < size; i++)
        {
            p = *STDArr[i];
            printf("ID = %lld, Name = %-20s, group %3d, Time: %5.2f %5.2f %5.2f %5.2f s\n", p->ID, p->Name, p->Group, p->Back50, p->Breast50, p->Fly50, p->Free50);
        }
        printf("End of Array\n\n");
    }
    else
    {
        printf("is Empty Array\n");
    }
}

void SortFree(STD **STDArr[], int size)
{
    int i, j, flag = 0;
    for (i = 0; i < size - 1; i++)
    {
        flag = 0;
        for (j = 0; j < size - i - 1; j++)
        {
            if ((*STDArr[j])->Free50 > (*STDArr[j + 1])->Free50)
            {
                flag = 1;
                STD **temp = STDArr[j];
                STDArr[j] = STDArr[j + 1];
                STDArr[j + 1] = temp;
            }
        }
        if (flag == 0)
            break;
    }
}

int main()
{
    char filename[40] = "2023_1_List.txt", filename2[40] = "test.txt";
    //    printf("input file name: ");
    //    gets(filename);
    FILE *fp = fopen(filename, "r");
    //    printf("output file name: ");
    //    gets(filename2);
    FILE *fp2 = fopen(filename2, "w");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    if (fp2 == NULL)
    {
        printf("Error: could not open file %s", filename2);
        return 1;
    }
    // read one character at a time and
    // display it to the output
    //    char ch;
    //    while ((ch = fgetc(fp)) != EOF)
    //        putchar(ch);

    //
    STD *STDArr[57];
    int j = 0;
    //

    char line[200];
    int seed = 0;
    STD newStd;
    STDList Std2023 = {0, "Student List of 2023"};
    while (fgets(line, 200, fp) != NULL)
    {
        //        printf("%s",line);
        //        fprintf(fp2,"%s",line);
        int i = 0, g = 0;
        char ID[11] = {0}, name[20] = {0}, *n = name;
        for (i = 0; i < 10; i++)
        {
            ID[i] = line[i];
        }
        //        printf("%s\n",ID);
        newStd.ID = A2I(ID);
        //        printf("%lld\n",newStd.ID);

        i++;
        while (line[i] != '\t')
        {
            g = 10 * g + line[i] - '0';
            i++;
        }
        //        printf("%d\n",g);
        newStd.Group = g;

        i++;
        //        printf("%s",&line[i]);
        while (line[i] != '@')
        {
            *n++ = line[i];
            i++;
        }
        name[0] = name[0] + 'A' - 'a';
        i = 1;
        while (name[++i] != '.')
            ;
        name[i++] = ' ';
        while (name[i])
        {
            name[i] = name[i] + 'A' - 'a';
            i++;
        }
        //        printf("%s\n",name);
        strcpy(newStd.Name, name);

        RandomTime(&newStd, seed++);
        printf("%lld %2d %-20s ", newStd.ID, newStd.Group, newStd.Name);
        printf("%.2f %.2f %.2f %.2f \n", newStd.Back50, newStd.Breast50, newStd.Fly50, newStd.Free50);

        //
        STDArr[j] = malloc(sizeof(STD));
        *STDArr[j] = newStd;
        j++;
        //

        fprintf(fp2, "%lld %2d %-20s ", newStd.ID, newStd.Group, newStd.Name);
        fprintf(fp2, "%.2f %.2f %.2f %.2f \n", newStd.Back50, newStd.Breast50, newStd.Fly50, newStd.Free50);
        AddList(&Std2023, newStd);
    }

    PrintList(&Std2023);
    printf("Original Array\n");
    PrintArray(STDArr, sizeof(STDArr) / sizeof(STD *));

    STD **FreeArray[57];
    for (int k = 0; k < 57; k++)
    {
        FreeArray[k] = &STDArr[k];
    }
    SortFree(FreeArray, 57);
    printf("Sorted by Free Style Times (Fastest First)\n");
    PrintArray2(FreeArray, 57);

    printf("Original Array\n");
    PrintArray(STDArr, sizeof(STDArr) / sizeof(STD *));

    // close the file
    fclose(fp);
    fclose(fp2);
    return 0;
}
