#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// global variable declaration
int f = 0;
int MAX_laun = 60;
int MAX_detail = 70;

// struct for student table
struct studdetails
{
    long int studno;
    char studname[50];
    char dept[20];
    int semester;
};
// struct for laundry table
struct laundry
{
    long int studno;
    char block[20];
    int roomno;
    float balance;
};

struct Nodelaundry
{
    struct laundry laundry;
    struct Nodelaundry *next;
};
struct Nodedetails
{
    struct studdetails details;
    struct Nodedetails *next;
};
typedef struct Nodelaundry Nodelaundry;
typedef struct Nodedetails Nodedetails;
typedef struct
{
    struct Nodelaundry *headptr;
    struct Nodelaundry *tailptr;
    int nodecnt;
} linkedlistlaun;
typedef struct
{
    struct Nodedetails *headptr;
    struct Nodedetails *tailptr;
    int nodecnt;
} linkedlistdetails;
// function declarations
// fn to initialise
void initlaun(linkedlistlaun *);
void initdetails(linkedlistdetails *);
// fn to check underflow
int isemptylaun(linkedlistlaun *);
int isemptydetails(linkedlistdetails *);
// fn to count number of records
int countlaun(linkedlistlaun *);
int countdetails(linkedlistdetails *);
// fn to insert records
void createlistlaundry(linkedlistlaun *, linkedlistdetails *);
void createlistdetails(linkedlistdetails *);
int inserttaillaundry(linkedlistlaun *, struct laundry *);
int inserttaildetails(linkedlistdetails *, struct studdetails *);
// fn to update records
void updatelaundry(linkedlistlaun *);
// fn to select records
void displaysortedlaundry(linkedlistlaun *);
void displaysorteddetails(linkedlistdetails *);
void displaylaundryminbalance(linkedlistlaun *);
void displaylaundrymaxbalance(linkedlistlaun *);
void displaylaundryregno(linkedlistlaun *);
void displaydetailsregno(linkedlistdetails *);
void displaydetails(linkedlistdetails *);
void displaylaundry(linkedlistlaun *);
// fn to join records
void joinspecregno(linkedlistlaun *, linkedlistdetails *, int);
void joinregno(linkedlistlaun *, linkedlistdetails *);
// fn to delete records
void deletelaun(linkedlistlaun *);
void deletedetails(linkedlistdetails *, linkedlistlaun *);
void deletealllaun(linkedlistlaun *);
void deletealldetails(linkedlistdetails *, linkedlistlaun *);
// fn to fn records
Nodedetails *finddetails(linkedlistdetails *, int);
Nodelaundry *findlaundry(linkedlistlaun *, int);
Nodelaundry *findprevlaundry(linkedlistlaun *, int);
Nodedetails *findprevdetails(linkedlistdetails *, int);
Nodelaundry *findlaundrybalance(linkedlistlaun *,float);
// fn to form arrays
int *formarrayregnolaun(linkedlistlaun *, int *);
int *formarrayregnodetails(linkedlistdetails *, int *);
float *formarraybalance(linkedlistlaun *, float *);
// fn to sort arrays
int *bubblesortregno(int, int *);
float *bubblesortbalance(int, float *);
// fn to find minimum balance
float minbalance(linkedlistlaun *);
// fn to find maximum balance
float maxbalance(linkedlistlaun *);
// fn to find sum of balance
float sumbalance(linkedlistlaun *);

// fn definitions
void initlaun(linkedlistlaun *listptr)
{
    listptr->headptr = NULL;
    listptr->tailptr = NULL;
    listptr->nodecnt = 0;
    // printf("Initialisation completed\n");
}
void initdetails(linkedlistdetails *listptr)
{
    listptr->headptr = NULL;
    listptr->tailptr = NULL;
    listptr->nodecnt = 0;
    // printf("Initialisation completed\n");
}

int isemptylaun(linkedlistlaun *listptr)
{
    if (listptr->nodecnt == 0)
        return 1;
    else
        return 0;
}
int isemptydetails(linkedlistdetails *listptr)
{
    if (listptr->nodecnt == 0)
        return 1;
    else
        return 0;
}

int countlaun(linkedlistlaun *listptr)
{
    return listptr->nodecnt;
}
int countdetails(linkedlistdetails *listptr)
{
    return listptr->nodecnt;
}

void createlistlaundry(linkedlistlaun *listptr, linkedlistdetails *listdetail)
{
    if (listptr->nodecnt == MAX_laun)
    {
        printf("\nCannot insert more elements.\nStudent count execeeded.\n\n");
        return;
    }
    int i, success, ele;
    struct laundry laundry;
    printf("\nEnter the details\n");
    printf("\nEnter the student registration number:");
    scanf("%d", &laundry.studno);
    if (findlaundry(listptr, laundry.studno) != NULL)
    {
        printf("\nPrimary key value exists already\n");
        return;
    }
    if (finddetails(listdetail, laundry.studno) == NULL)
    {
        printf("\nForeign key value not found.\n");
        return;
    }
    printf("\nEnter the hostel block\t:");
    scanf("%s", laundry.block);
    printf("\nEnter the room number\t:");
    scanf("%d", &laundry.roomno);
    printf("\nEnter the Balance amount\t:");
    scanf("%f", &laundry.balance);
    inserttaillaundry(listptr, &laundry);
}
void createlistdetails(linkedlistdetails *listptr)
{
    if (listptr->nodecnt == MAX_detail)
    {
        printf("\nCannot insert more elements.\nStudent count execeeded.\n\n");
        return;
    }
    int i, success, ele;
    struct studdetails detail;
    printf("\nEnter the details\n");
    printf("\nEnter the student registration number\t:");
    scanf("%d", &detail.studno);
    
    if (finddetails(listptr, detail.studno) != NULL)
    {
        printf("\nPrimary key value exists already\n");
        return;
    }
    printf("\nEnter the student name\t:");
    scanf("%s", detail.studname);
    printf("\nEnter the department name:");
    scanf("%s", detail.dept);
    printf("\nEnter the semester:");
    scanf("%d", &detail.semester);
    if (detail.semester > 8 || detail.semester < 1)
    {
        printf("\nCheck constriant violated.\n");
        return;
    }
    inserttaildetails(listptr, &detail);
}
int inserttaillaundry(linkedlistlaun *listptr, struct laundry *laundry)
{
    Nodelaundry *newnode = (Nodelaundry *)malloc(sizeof(Nodelaundry));
    if (newnode == NULL)
    {
        printf("\nCouldn't allocate memory\n");
        return 0;
    }
    newnode->laundry = *laundry;
    newnode->next = NULL;
    if (listptr->nodecnt == 0)
    {
        listptr->tailptr = newnode;
        listptr->headptr = newnode;
    }
    else
    {
        listptr->tailptr->next = newnode;
        listptr->tailptr = newnode;
    }
    listptr->nodecnt++;
    printf("\nRecord inserted into laundry table successfully\n");
    // printf("%d\n",listptr->nodecnt);
    return 1;
}
int inserttaildetails(linkedlistdetails *listptr, struct studdetails *detail)
{
    Nodedetails *newnode = (Nodedetails *)malloc(sizeof(Nodedetails));
    if (newnode == NULL)
    {
        printf("\nCouldn't allocate memory\n");
        return 0;
    }
    newnode->details = *detail;
    newnode->next = NULL;
    if (listptr->nodecnt == 0)
    {
        listptr->tailptr = newnode;
        listptr->headptr = newnode;
    }
    else
    {
        listptr->tailptr->next = newnode;
        listptr->tailptr = newnode;
    }
    listptr->nodecnt++;
    // printf("%d\n",listptr->nodecnt);
    printf("\nRecord inserted into student table successfully\n");
    return 1;
}

void updatelaundry(linkedlistlaun *listptr)
{
    long int regno;
    printf("\nEnter the register number of the student for whom you want to update\t:");
    scanf("%d", &regno);
    if (findlaundry(listptr, regno) == NULL)
    {
        printf("\nRegister number not found\n");
        return;
    }
    else
    {
        char service[20];
        float weight, amtpressing;
        int no_of_clothes;
        Nodelaundry *temp = findlaundry(listptr, regno);
        printf("\nSERVICES AVAILABLE\n\n1.washing\n2.pressing\n\n");
        printf("\nEnter the service opted\t:");
        scanf("%s", &service);
        if (strcmp(service, "washing") == 0 || strcmp(service,"1")==0)
        {
            printf("\nEnter the weight of clothes\t:");
            scanf("%f", &weight);
            if (weight > 0 && weight <= 5)
            {
                temp->laundry.balance = temp->laundry.balance - 165;
                printf("\nValue updated successfully.\n");
            }
            else if (weight > 5 && weight <= 8)
            {
                temp->laundry.balance = temp->laundry.balance - 235;
                printf("\nValue updated successfully.\n");
            }
            else
            {
                printf("\nInvalid weight range\n");
            }
        }
        else if (strcmp(service, "pressing") == 0 || strcmp(service,"2")==0)
        {
            printf("\nEnter the number of clothes\t:");
            scanf("%d", &no_of_clothes);
            amtpressing = 7 * no_of_clothes;
            temp->laundry.balance = temp->laundry.balance - amtpressing;
            printf("\nValue updated successfully.\n");
        }
        else
        {
            printf("\nInvalid service\n");
        }
        
    }
}

void displaysortedlaundry(linkedlistlaun *listptr)
{
    int num = countlaun(listptr);
    int arr[num];
    int *arrregno = formarrayregnolaun(listptr, arr);
    arrregno = bubblesortregno(num, arrregno);
    for (int i = 0; i < num; i++)
    {
        Nodelaundry *current = findlaundry(listptr, arrregno[i]);
        printf("Regno\t\t:%d\n", current->laundry.studno);
        printf("Hostel block\t:%s\n", current->laundry.block);
        printf("Room number\t:%d\n", current->laundry.roomno);
        printf("Balance\t\t:%f\n\n", current->laundry.balance);
    }
}

void displaysorteddetails(linkedlistdetails *listptr)
{
    int num = countdetails(listptr);
    int arr[num];
    int *arrregno = formarrayregnodetails(listptr, arr);
    arrregno = bubblesortregno(num, arrregno);
    for (int i = 0; i < num; i++)
    {
        Nodedetails *current = finddetails(listptr, arrregno[i]);
        printf("Register number\t:%d\n", current->details.studno);
        printf("Name\t:%s\n", current->details.studname);
        printf("Department\t:%s\n", current->details.dept);
        printf("Semester\t:%d\n\n", current->details.semester);
    }
}

void displaysortedlaundrybalance(linkedlistlaun *listptr)
{
    int num = countlaun(listptr);
    float arr[num];
    float *arrbalance = formarraybalance(listptr, arr);
    for(int i=0;i<num;i++)
    {
        printf("%f\n",arrbalance[i]);
    }
    arrbalance = bubblesortbalance(num, arrbalance);
    for(int i=0;i<num;i++)
    {
        printf("%f\n",arrbalance[i]);
    }
    for (int i = 0; i < num; i++)
    {
        Nodelaundry *current = findlaundrybalance(listptr, arrbalance[i]);
        printf("Regno\t\t:%d\n", current->laundry.studno);
        printf("Hostel block\t:%s\n", current->laundry.block);
        printf("Room number\t:%d\n", current->laundry.roomno);
        printf("Balance\t\t:%f\n\n", current->laundry.balance);
    }
}

void displaylaundry(linkedlistlaun *listptr)
{

    if (isemptylaun(listptr))
    {
        printf("No records\n");
        return;
    }

    Nodelaundry *current = listptr->headptr;

    while (current != NULL)
    {
        printf("Regno\t\t:%d\n", current->laundry.studno);
        printf("Hostel block\t:%s\n", current->laundry.block);
        printf("Room number\t:%d\n", current->laundry.roomno);
        printf("Balance\t\t:%f\n\n", current->laundry.balance);
        // printf("Balance:%f\n",current->laundry.balance);
        current = current->next;
    }
    // printf("%d",listptr->nodecnt);
    return;
}
void displaydetails(linkedlistdetails *listptr)
{

    if (isemptydetails(listptr))
    {
        printf("\nNo records\n\n");
        return;
    }

    Nodedetails *current = listptr->headptr;

    while (current != NULL)
    {
        printf("Register number\t:%d\n", current->details.studno);
        printf("Name block\t:%s\n", current->details.studname);
        printf("Department\t:%s\n", current->details.dept);
        printf("Semester\t:%d\n\n", current->details.semester);
        // printf("Balance:%f\n",current->laundry.balance);
        current = current->next;
    }
    // printf("%d",listptr->nodecnt);
    return;
}
void displaylaundryregno(linkedlistlaun *listptr)
{

    if (isemptylaun(listptr))
    {
        printf("\nNo records\n\n");
        return;
    }
    int regno;
    printf("\nEnter the register number for which you want the records\t:");
    scanf("%d", &regno);
    if (findlaundry(listptr, regno) == NULL)
    {
        printf("\nRecord not found\n");
        return;
    }
    Nodelaundry *current = listptr->headptr;

    while (current != NULL)
    {
        if (current->laundry.studno == regno)
        {
            printf("Regno\t\t:%d\n", current->laundry.studno);
            printf("Hostel block\t:%s\n", current->laundry.block);
            printf("Room number\t:%d\n", current->laundry.roomno);
            printf("Balance\t\t:%f\n", current->laundry.balance);
        }
        // printf("Balance:%f\n",current->laundry.balance);
        current = current->next;
    }
    // printf("%d",listptr->nodecnt);
    return;
}

void displaylaundrymaxbalance(linkedlistlaun *listptr)
{

    if (isemptylaun(listptr))
    {
        printf("\nNo records\n");
        return;
    }
    Nodelaundry *current = listptr->headptr;
    float max = maxbalance(listptr);
    while (current != NULL)
    {
        if (current->laundry.balance == max)
        {
            printf("Regno\t\t:%d\n", current->laundry.studno);
            printf("Hostel block\t:%s\n", current->laundry.block);
            printf("Room number\t:%d\n", current->laundry.roomno);
            printf("Balance\t\t:%f\n\n", current->laundry.balance);
        }
        // printf("Balance:%f\n",current->laundry.balance);
        current = current->next;
    }
    // printf("%d",listptr->nodecnt);
    return;
}
void displaylaundryminbalance(linkedlistlaun *listptr)
{

    if (isemptylaun(listptr))
    {
        printf("\nNo records\n");
        return;
    }
    Nodelaundry *current = listptr->headptr;
    float min = minbalance(listptr);
    while (current != NULL)
    {
        if (current->laundry.balance == min)
        {
            printf("Regno:%d\n", current->laundry.studno);
            printf("Hostel block:%s\n", current->laundry.block);
            printf("Room number:%d\n", current->laundry.roomno);
            printf("Balance:%f\n\n", current->laundry.balance);
        }
        // printf("Balance:%f\n",current->laundry.balance);
        current = current->next;
    }
    // printf("%d",listptr->nodecnt);
    return;
}
void displaydetailsregno(linkedlistdetails *listptr)
{

    if (isemptydetails(listptr))
    {
        printf("\nNo records\n");
        return;
    }
    int regno;
    printf("\nEnter the register number for which you want the records:");
    scanf("%d", &regno);
    if (finddetails(listptr, regno) == NULL)
    {
        printf("\nRecord not found\n");
        return;
    }
    Nodedetails *current = listptr->headptr;

    while (current != NULL)
    {
        if(current->details.studno==regno){
        printf("Register number:%d\n", current->details.studno);
        printf("Name:%s\n", current->details.studname);
        printf("Department:%s\n", current->details.dept);
        printf("Semester:%d\n\n", current->details.semester);
        // printf("Balance:%f\n",current->laundry.balance);
        }
        current = current->next;
    }
    // printf("%d",listptr->nodecnt);
    return;
}

void joinspecregno(linkedlistlaun *listlaun, linkedlistdetails *listdetail, int regno)
{

    if (isemptylaun(listlaun) || isemptydetails(listdetail))
    {
        printf("\nNo records\n");
        return;
    }
    Nodelaundry *current = findlaundry(listlaun, regno);

    Nodedetails *temp = finddetails(listdetail, regno);
    if (current == NULL || temp == NULL)
    {
        printf("\nRegister number not found\n");
        return;
    }
    printf("Regno:%d\n", current->laundry.studno);
    printf("Name:%s\n", temp->details.studname);
    printf("Department:%s\n", temp->details.dept);
    printf("Semester:%d\n", temp->details.semester);
    printf("Hostel block:%s\n", current->laundry.block);
    printf("Room number:%d\n", current->laundry.roomno);
    printf("Balance:%f\n\n", current->laundry.balance);

    return;
}
void joinregno(linkedlistlaun *listlaun, linkedlistdetails *listdetail)
{

    if (isemptylaun(listlaun) || isemptydetails(listdetail))
    {
        printf("\nNo records\n");
        return;
    }
    Nodelaundry *current = listlaun->headptr;

    while (current != NULL)
    {
        Nodedetails *temp = finddetails(listdetail, current->laundry.studno);

        printf("Regno:%d\n", current->laundry.studno);
        printf("Name:%s\n", temp->details.studname);
        printf("Department:%s\n", temp->details.dept);
        printf("Semester:%d\n", temp->details.semester);
        printf("Hostel block:%s\n", current->laundry.block);
        printf("Room number:%d\n", current->laundry.roomno);
        printf("Balance:%f\n\n", current->laundry.balance);

        // printf("Balance:%f\n",current->laundry.balance);
        current = current->next;
    }
    // printf("%d",listptr->nodecnt);
    return;
}

void deletelaun(linkedlistlaun *listptrlaun)
{
    struct laundry *laundry;
    int regno;
    printf("\nEnter the register number of the student to delete\t:");
    scanf("%d", &regno);
    if (findlaundry(listptrlaun, regno) == NULL)
    {
        printf("\nRecord not found\n");
        return;
    }
    else if (findprevlaundry(listptrlaun, regno) == NULL)
    {
        //Nodelaundry *temp = listptrlaun->headptr;
        listptrlaun->headptr = listptrlaun->headptr->next;
        listptrlaun->nodecnt--;
        printf("Record deleted successfully\n");
    }
    else
    {

        Nodelaundry *temp = findprevlaundry(listptrlaun, regno);
        //Nodelaundry *temp1=findlaundry(listptrlaun, regno);
        temp->next =temp->next->next;
        listptrlaun->nodecnt--;
        printf("Record deleted successfully\n");
    }
    
}
void deletedetails(linkedlistdetails *listptrdet, linkedlistlaun *listptrlaun)
{
    struct details *detail;
    int regno;
    printf("\nEnter the register number of the student to delete\t:");
    scanf("%d", &regno);
    if (finddetails(listptrdet, regno) == NULL)
    {
        printf("Record not found\n");
        return;
    }
    if (findlaundry(listptrlaun, regno) != NULL)
    {
        printf("Foreign key value associated.\nCannot delete.\n");
        return;
    }
    else if (findprevdetails(listptrdet, regno) == NULL)
    {
        Nodedetails *temp = listptrdet->headptr;
        listptrdet->headptr = temp->next;
        listptrdet->nodecnt--;
        printf("Record deleted successfully\n");
    }
    else
    {

        Nodedetails *temp = findprevdetails(listptrdet, regno);
        temp->next = temp->next->next;
        listptrdet->nodecnt--;
        printf("Record deleted successfully\n");
    }
}
void deletealllaun(linkedlistlaun *listptr)
{
    initlaun(listptr);
    printf("\nAll records in laundry table deleted successfully\n");
    return;
}
void deletealldetails(linkedlistdetails *listptrdetail, linkedlistlaun *listptrlaun)
{
    if (isemptylaun(listptrlaun))
    {
        initdetails(listptrdetail);
        printf("\nAll records in student table deleted successfully\n");
    }
    else
        printf("\nRecords cannot be deleted.Foreign key values associated with laundry table\n");
    return;
}

Nodelaundry* findlaundry(linkedlistlaun *listptr, int regno)
{
    Nodelaundry *temp = listptr->headptr;
    while (temp != NULL)
    {
        if (temp->laundry.studno == regno)
        {
            return temp;
        }
        Nodelaundry *temp1 = temp->next;
        temp = temp1;
    }
    return temp;
}
Nodelaundry *findlaundrybalance(linkedlistlaun *listptr, float balance)
{

    Nodelaundry *temp = listptr->headptr;
    while (temp != NULL)
    {
        if (temp->laundry.balance == balance)
        {
            
            return temp;
        }
        Nodelaundry *temp1 = temp->next;
        temp = temp1;
    }
    return temp;
}
Nodedetails *finddetails(linkedlistdetails *listptr, int regno)
{
    Nodedetails *temp = listptr->headptr;
    while (temp != NULL)
    {
        if (temp->details.studno == regno)
        {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}
Nodelaundry *findprevlaundry(linkedlistlaun *listptr, int regno)
{
    struct laundry *laundry;
    Nodelaundry *temp = listptr->headptr;
    while (temp->next != NULL)
    {
        Nodelaundry *temp1 = temp->next;
        if (temp1->laundry.studno == regno)
        {
            //- printf("previous")
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}
Nodedetails *findprevdetails(linkedlistdetails *listptr, int regno)
{
    Nodedetails *temp = listptr->headptr;
    while (temp->next != NULL)
    {
        Nodedetails *temp1 = temp->next;
        if (temp1->details.studno == regno)
        {
            //- printf("previous")
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

int *formarrayregnolaun(linkedlistlaun *listptr, int *arrregno)
{

    int i = 0;
    int num = countlaun(listptr);
    if (!isemptylaun(listptr))
    {
        Nodelaundry *current = listptr->headptr;

        while (current != NULL && i < num)
        {
            arrregno[i] = current->laundry.studno;
            current = current->next;
            i++;
        }
    }
    return arrregno;
}
int *formarrayregnodetails(linkedlistdetails *listptr, int *arrregno)
{

    int i = 0;
    int num = countdetails(listptr);
    if (!isemptydetails(listptr))
    {
        Nodedetails *current = listptr->headptr;

        while (current != NULL && i < num)
        {
            arrregno[i] = current->details.studno;
            current = current->next;
            i++;
        }
    }
    return arrregno;
}
float *formarraybalance(linkedlistlaun *listptr, float *arrbalance)
{

    int i = 0;
    int num = countlaun(listptr);
    if (!isemptylaun(listptr))
    {
        Nodelaundry *current = listptr->headptr;

        while (current != NULL && i < num)
        {
            arrbalance[i] = current->laundry.balance;
            current = current->next;
            // printf("%f",arrbalance[i]);
            i++;
        }
    }
    return arrbalance;
}

int *bubblesortregno(int n, int *arr)
{
    int i, j, k, a1, a2;

    for (a1 = 0; a1 < n; a1++)
    {
        for (a2 = 0; a2 < n - a1 - 1; a2++)
        {
            if (arr[a2] > arr[a2 + 1])
            {
                int temp = arr[a2 + 1];
                arr[a2 + 1] = arr[a2];
                arr[a2] = temp;
            }
        }
    }
    return arr;
}
float *bubblesortbalance(int n, float *arr)
{
    int i, j, k, a1, a2;

    for (a1 = 0; a1 < n; a1++)
    {
        for (a2 = 0; a2 < n - a1 - 1; a2++)
        {
            if (arr[a2] > arr[a2 + 1])
            {
                int temp = arr[a2 + 1];
                arr[a2 + 1] = arr[a2];
                arr[a2] = temp;
            }
        }
    }
    return arr;
}

float minbalance(linkedlistlaun *listptr)
{
    int num = countlaun(listptr);

    float arrbalance[num];
    float *arrbal = formarraybalance(listptr, arrbalance);

    arrbal = bubblesortbalance(num, arrbalance);
    if (num == 0)
        return -99;
    // printf("Minimum balance:%f",arrbalance[0]);
    return arrbal[0];
}
float maxbalance(linkedlistlaun *listptr)
{
    int num = countlaun(listptr);
    float arrbalance[num];
    float *arrbal = formarraybalance(listptr, arrbalance);

    arrbal = bubblesortbalance(num, arrbalance);
    if (num == 0)
        return -99;

    return arrbal[num - 1];
}
float sumbalance(linkedlistlaun *listptr)
{
    float sum = 0;
    if (isemptylaun(listptr))
    {

        return -99;
    }
    Nodelaundry *current = listptr->headptr;

    while (current != NULL)
    {
        sum = sum + current->laundry.balance;
        Nodelaundry *currnext = current->next;
        current = currnext;
    }
    // printf("Sum of Balance:%f\n",sum);
    return sum;
}
// main fn
int main()
{
    linkedlistlaun listlaun;
    linkedlistdetails listdetails;
    initlaun(&listlaun);
    initdetails(&listdetails);

    int regno, choice, inchoice, cnt;
    float m;
    // displaying the options available
    printf("====================================================================================================================\n");
    printf("\t\t\t\t\t\t\tTHE QUERY RETRIEVER\t\t\t\t\t\n");
    printf("====================================================================================================================\n\n");
    printf("\nOPTIONS\n\n1.Insert\n2.Update Balance\n3.Select\n4.Join\n5.Delete\n6.Count\n7.Balance sum\n8.Minimum Balance\n9.Maximum balance\n10.Exit\n\n");
    while (1)
    {
        printf("\nEnter your choice\t:");
        scanf("%d", &choice); // getting choice
        switch (choice)
        {
        // insert
        case 1:
            printf("\nYou have chosen to insert\n");
            printf("\nOPTIONS ON INSERTING\n\n1.Insert into laundry table\n2.Insert into student table\n");
            printf("\nEnter your choice\t:");
            scanf("%d", &inchoice);
            switch (inchoice)
            {
            case 1:
                printf("\nYou have chosen to insert into laundry table\n");
                createlistlaundry(&listlaun, &listdetails);
                break;
            case 2:
                printf("\nYou have chosen to insert into student table\n");
                createlistdetails(&listdetails);
                break;
            default:
                printf("\nInvalid option\n");
                break;
            }
            break;
        // update
        case 2:
            printf("\nYou have chosen to update balance in laundry table\n");
            updatelaundry(&listlaun);
            break;
        // select
        case 3:
            printf("\nYou have chosen to select records\n");
            printf("\nOPTIONS ON SELECT\n1.select * laundry\n2.select * student\n3.select from laundry based on regno\n4.select * from student based on regno\n5.select * from laundry based on maximum balance\n6.slect * from laundry based on mininmum balance\n7.select from laundry order by regno\n8.select from student order by regno\n9.select from laundry and student based on regno\n10.select from laundry order by balance\n");
            printf("\nEnter your choice\t:");
            scanf("%d", &inchoice);
            switch (inchoice)
            {
            case 1:
                printf("\nYou have chosen to select * from laundry\n\n");
                displaylaundry(&listlaun);
                break;
            case 2:
                printf("\nYou have chosen to select * from details\n\n");
                displaydetails(&listdetails);
                break;
            case 3:
                printf("\nYou have chosen to select from laundry based on regno\n\n");
                displaylaundryregno(&listlaun);
                break;
            case 4:
                printf("\nYou have chosen to select from students based on regno\n\n");
                displaydetailsregno(&listdetails);
                break;
            case 5:
                printf("\nYou have chosen to select from laundry based on maximum balance\n\n");
                displaylaundrymaxbalance(&listlaun);
                break;
            case 6:
                printf("\nYou have chosen to select from laundry based on minimum balance\n\n");
                displaylaundryminbalance(&listlaun);
                break;
            case 7:
                printf("\nYou have chosen select from laundry order by regno\n\n");
                displaysortedlaundry(&listlaun);
                break;
            case 8:
                printf("\nYou have chosen select from student order by regno\n\n");
                displaysorteddetails(&listdetails);
                break;
            case 9:
                printf("\nYou have chosen select from laundry and student based on regno\n\n");
                printf("\nEnter the register number\t:");
                scanf("%d", &regno);
                joinspecregno(&listlaun, &listdetails, regno);
                break;
            case 10:
                printf("\nYou have chosen select from laundry order by balance\n\n");
                displaysortedlaundrybalance(&listlaun);
                break;
            default:
                printf("\nInvalid option\n");
                break;
            }
            break;
        // join
        case 4:
            printf("\nYou have chosen to join based on register number\n\n");
            joinregno(&listlaun, &listdetails);
            break;
        // delete
        case 5:
            printf("\nYou have chosen to delete\n");
            printf("\nOPTIONS ON DELETE\n\n1.Delete all records from laundry\n2.Delete all records from student\n");
            printf("\nEnter your choice\t:");
            scanf("%d", &inchoice);
            switch (inchoice)
            {
            /*case 1:
                printf("\nYou have chosen to delete from laundry based on regno\n");
                deletelaun(&listlaun);
                break;*/
            /*case 1:
                printf("\nYou have chosen to delete from student based on regno\n");
                deletedetails(&listdetails, &listlaun);
                break;*/
            case 1:
                printf("\nYou have chosen to delete all records from laundry\n");
                deletealllaun(&listlaun);
                break;
            case 2:
                printf("\nYou have chosen to delete all records from students\n");
                deletealldetails(&listdetails, &listlaun);
                break;
            default:
                printf("\nInvalid choice\n");
                break;
            }
            break;
        // count
        case 6:
            printf("\nYou have chosen to count\n");
            printf("\nOPTIONS IN COUNT\n\n1.count * from laundry\n2.count * from student\n");
            printf("\nEnter you choice\t:");
            scanf("%d", &inchoice);
            switch (inchoice)
            {
            case 1:
                printf("\nYou have chosen count * from laundry\n");
                cnt = countlaun(&listlaun);
                printf("\nThe total records in laundry table is %d\n", cnt);
                break;
            case 2:
                printf("\nYou have chosen count * from student\n");
                cnt = countdetails(&listdetails);
                printf("\nThe total records in student table is %d\n", cnt);
                break;
            default:
                printf("\nInvalid choice\n");
                break;
            }
            break;
        // sum balnce
        case 7:
            printf("\nYou have chosen to sum the balance amount in laundry table\n");
            float s = sumbalance(&listlaun);
            if (s == -99)
                printf("\nNo records in laundry table\n");
            else
                printf("\nThe sum of balance is:%f\n", s);
            break;
        // minimum balance
        case 8:
            printf("\nYou have chosen to find minimum balance amount in laundry table\n");
            m = minbalance(&listlaun);
            if (m == -99)
                printf("\nNo records in laundry table\n");
            else
                printf("\nThe minimum balance is:%f\n", m);
            break;
        // maximum balance
        case 9:
            printf("\nYou have chosen to find maximum balance amount in laundry table\n");
            m = maxbalance(&listlaun);
            if (m == -99)
                printf("\nNo records in laundry table\n");
            else
                printf("\nThe maximum balance is:%f\n", m);
            break;
        case 10:
            printf("\nExiting....");
            exit(1);
        default:
        printf("\nInvalid choice!\n\n");
            break;
        }
    }
    return 0;
}