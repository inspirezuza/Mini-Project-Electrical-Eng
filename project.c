#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// กลุ่มที่ได้รับมอบหมาย
#define MY_GROUP_A 5
#define MY_GROUP_B 6
#define STUDENT_SIZE 57

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

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generatePermutations(int arr[], int n, int r, int index, STD *STDArr[], float *mintime, int finalarr[])
{
    if (index == r)
    {
        if (STDArr[arr[0]]->Back50 + STDArr[arr[1]]->Breast50 + STDArr[arr[2]]->Fly50 + STDArr[arr[3]]->Free50 < *mintime)
        {
            *mintime = STDArr[arr[0]]->Back50 + STDArr[arr[1]]->Breast50 + STDArr[arr[2]]->Fly50 + STDArr[arr[3]]->Free50;
            for (int i = 0; i < r; i++)
            {
                finalarr[i] = arr[i];
            }
        }
    }
    else
    {

        for (int i = index; i < n; i++)
        {
            swap(&arr[i], &arr[index]);
            generatePermutations(arr, n, r, index + 1, STDArr, mintime, finalarr);
            swap(&arr[i], &arr[index]);
        }
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
    STD *STDArr[STUDENT_SIZE];
    int mygroupindex[10] = {};
    int mygroupcount = 0;
    int j = 0;
    //

    char line[200];
    int seed = 0;
    STD newStd;
    // STDList Std2023 = {0, "Student List of 2023"};
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
        strcpy(newStd.Name, name);

        RandomTime(&newStd, seed++);

        if (newStd.Group == MY_GROUP_A || newStd.Group == MY_GROUP_B)
        {
            mygroupindex[mygroupcount] = j;
            mygroupcount++;
        }

        STDArr[j] = malloc(sizeof(STD));
        *STDArr[j] = newStd;
        j++;
    }

    // แสดงผลกลุ่มของเรา
    printf("Group_%d,%d_Student_List\n", MY_GROUP_A, MY_GROUP_B);
    printf("Has_%d_students\n", mygroupcount);
    for (int i = 0; i < mygroupcount; i++)
    {
        printf("%lld %2d %-20s ", STDArr[mygroupindex[i]]->ID, STDArr[mygroupindex[i]]->Group, STDArr[mygroupindex[i]]->Name);
        printf("%.2f %.2f %.2f %.2f \n", STDArr[mygroupindex[i]]->Back50, STDArr[mygroupindex[i]]->Breast50, STDArr[mygroupindex[i]]->Fly50, STDArr[mygroupindex[i]]->Free50);
    }
    printf("\n");

    fprintf(fp2, "Group_%d,%d_Student_List\n", MY_GROUP_A, MY_GROUP_B);
    fprintf(fp2, "Has_%d_students\n", mygroupcount);
    for (int i = 0; i < mygroupcount; i++)
    {
        fprintf(fp2, "%lld %2d %-20s ", STDArr[mygroupindex[i]]->ID, STDArr[mygroupindex[i]]->Group, STDArr[mygroupindex[i]]->Name);
        fprintf(fp2, "%.2f %.2f %.2f %.2f \n", STDArr[mygroupindex[i]]->Back50, STDArr[mygroupindex[i]]->Breast50, STDArr[mygroupindex[i]]->Fly50, STDArr[mygroupindex[i]]->Free50);
    }
    fprintf(fp2, "\n");

    // แสดงผลรวม 4 คนที่ว่ายน้ำรวมกันเร็วที่สุดของกลุ่มเรา
    float mintime = 9999999;
    int finalarr[4] = {};
    generatePermutations(mygroupindex, mygroupcount, 4, 0, STDArr, &mintime, finalarr);
    printf("Group_%d,%d_Team\n", MY_GROUP_A, MY_GROUP_B);
    printf("%-20s %lld Group %3d: Back, %5.2lf s\n", STDArr[finalarr[0]]->Name, STDArr[finalarr[0]]->ID, STDArr[finalarr[0]]->Group, STDArr[finalarr[0]]->Back50);
    printf("%-20s %lld Group %3d: Breast, %5.2lf s\n", STDArr[finalarr[1]]->Name, STDArr[finalarr[1]]->ID, STDArr[finalarr[1]]->Group, STDArr[finalarr[1]]->Breast50);
    printf("%-20s %lld Group %3d: Fly, %5.2lf s\n", STDArr[finalarr[2]]->Name, STDArr[finalarr[2]]->ID, STDArr[finalarr[2]]->Group, STDArr[finalarr[2]]->Fly50);
    printf("%-20s %lld Group %3d: Free, %5.2lf s\n", STDArr[finalarr[3]]->Name, STDArr[finalarr[3]]->ID, STDArr[finalarr[3]]->Group, STDArr[finalarr[3]]->Free50);
    printf("Total time: %5.2lf + %5.2lf + %5.2lf + %5.2lf = %5.2lf\n", STDArr[finalarr[0]]->Back50, STDArr[finalarr[1]]->Breast50, STDArr[finalarr[2]]->Fly50, STDArr[finalarr[3]]->Free50, mintime);
    printf("\n");

    fprintf(fp2, "Group_%d,%d_Team\n", MY_GROUP_A, MY_GROUP_B);
    fprintf(fp2, "%-20s %lld Group %3d: Back, %5.2lf s\n", STDArr[finalarr[0]]->Name, STDArr[finalarr[0]]->ID, STDArr[finalarr[0]]->Group, STDArr[finalarr[0]]->Back50);
    fprintf(fp2, "%-20s %lld Group %3d: Breast, %5.2lf s\n", STDArr[finalarr[1]]->Name, STDArr[finalarr[1]]->ID, STDArr[finalarr[1]]->Group, STDArr[finalarr[1]]->Breast50);
    fprintf(fp2, "%-20s %lld Group %3d: Fly, %5.2lf s\n", STDArr[finalarr[2]]->Name, STDArr[finalarr[2]]->ID, STDArr[finalarr[2]]->Group, STDArr[finalarr[2]]->Fly50);
    fprintf(fp2, "%-20s %lld Group %3d: Free, %5.2lf s\n", STDArr[finalarr[3]]->Name, STDArr[finalarr[3]]->ID, STDArr[finalarr[3]]->Group, STDArr[finalarr[3]]->Free50);
    fprintf(fp2, "Total time: %5.2lf + %5.2lf + %5.2lf + %5.2lf = %5.2lf\n", STDArr[finalarr[0]]->Back50, STDArr[finalarr[1]]->Breast50, STDArr[finalarr[2]]->Fly50, STDArr[finalarr[3]]->Free50, mintime);
    fprintf(fp2, "\n");

    // แสดงผลรวม 4 คนที่ว่ายน้ำรวมกันเร็วที่สุดของคนอื่นๆรวมกัน
    int othergroupindex[STUDENT_SIZE] = {};
    int othercount = STUDENT_SIZE - 4;
    int otherstudent = 0;
    for (int i = 0; i < STUDENT_SIZE; i++)
    {
        if (i == finalarr[0] || i == finalarr[1] || i == finalarr[2] || i == finalarr[3])
        {
            otherstudent++;
            continue;
        }
        othergroupindex[i] = otherstudent++;
    }
    mintime = 9999999;
    generatePermutations(othergroupindex, othercount, 4, 0, STDArr, &mintime, finalarr);
    printf("All_Group_Team\n", MY_GROUP_A, MY_GROUP_B);
    printf("%-20s %lld Group %3d: Back, %5.2lf s\n", STDArr[finalarr[0]]->Name, STDArr[finalarr[0]]->ID, STDArr[finalarr[0]]->Group, STDArr[finalarr[0]]->Back50);
    printf("%-20s %lld Group %3d: Breast, %5.2lf s\n", STDArr[finalarr[1]]->Name, STDArr[finalarr[1]]->ID, STDArr[finalarr[1]]->Group, STDArr[finalarr[1]]->Breast50);
    printf("%-20s %lld Group %3d: Fly, %5.2lf s\n", STDArr[finalarr[2]]->Name, STDArr[finalarr[2]]->ID, STDArr[finalarr[2]]->Group, STDArr[finalarr[2]]->Fly50);
    printf("%-20s %lld Group %3d: Free, %5.2lf s\n", STDArr[finalarr[3]]->Name, STDArr[finalarr[3]]->ID, STDArr[finalarr[3]]->Group, STDArr[finalarr[3]]->Free50);
    printf("Total time: %5.2lf + %5.2lf + %5.2lf + %5.2lf = %5.2lf", STDArr[finalarr[0]]->Back50, STDArr[finalarr[1]]->Breast50, STDArr[finalarr[2]]->Fly50, STDArr[finalarr[3]]->Free50, mintime);

    fprintf(fp2, "All_Group_Team\n", MY_GROUP_A, MY_GROUP_B);
    fprintf(fp2, "%-20s %lld Group %3d: Back, %5.2lf s\n", STDArr[finalarr[0]]->Name, STDArr[finalarr[0]]->ID, STDArr[finalarr[0]]->Group, STDArr[finalarr[0]]->Back50);
    fprintf(fp2, "%-20s %lld Group %3d: Breast, %5.2lf s\n", STDArr[finalarr[1]]->Name, STDArr[finalarr[1]]->ID, STDArr[finalarr[1]]->Group, STDArr[finalarr[1]]->Breast50);
    fprintf(fp2, "%-20s %lld Group %3d: Fly, %5.2lf s\n", STDArr[finalarr[2]]->Name, STDArr[finalarr[2]]->ID, STDArr[finalarr[2]]->Group, STDArr[finalarr[2]]->Fly50);
    fprintf(fp2, "%-20s %lld Group %3d: Free, %5.2lf s\n", STDArr[finalarr[3]]->Name, STDArr[finalarr[3]]->ID, STDArr[finalarr[3]]->Group, STDArr[finalarr[3]]->Free50);
    fprintf(fp2, "Total time: %5.2lf + %5.2lf + %5.2lf + %5.2lf = %5.2lf", STDArr[finalarr[0]]->Back50, STDArr[finalarr[1]]->Breast50, STDArr[finalarr[2]]->Fly50, STDArr[finalarr[3]]->Free50, mintime);

    // close the file
    fclose(fp);
    fclose(fp2);
    return 0;
}
