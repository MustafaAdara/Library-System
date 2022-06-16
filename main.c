#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;
typedef struct books
{
    int ID ;
    char book_name[20];
    int quantity;
};
struct books BOOK[20];
int counter=0;

void Add ()
{
    fptr=fopen("books.TXT","a");
    if(fptr==NULL)
    {
        printf("\t\tcan not open the file\n");
    }
    else
    {
        fscanf(fptr,"%d%s%d",&BOOK[counter].ID,BOOK[counter].book_name,&BOOK[counter].quantity);
        printf("\t\tEnter the book ID: \n\t\t>>>: ");
        scanf("%d",&BOOK[counter].ID);
        printf("\t\tEnter the name of the book: \n\t\t>>>: ");
        fflush(stdin);
        gets(BOOK[counter].book_name);
        printf("\t\tEnter the quantity of the books: \n\t\t>>>: ");
        scanf("%d",&BOOK[counter].quantity);
        fprintf(fptr,"%d\t%s\t%d\n",BOOK[counter].ID,BOOK[counter].book_name,BOOK[counter].quantity);
        fclose(fptr);
    }
}

void delete_book()
{
    fptr=fopen("books.TXT","r");
    FILE *ptr=fopen("temp.TXT","w");
    if((fptr && ptr )==NULL)
    {
        printf("\t\tCan not open the file\n");
    }
    else
    {
        int id;
        printf("\t\tEnter id of the book to delete: \n\t\t>>>: ");
        scanf("%d",&id);
        while(!feof(fptr))
        {
            fscanf(fptr,"%d%s%d",&BOOK[counter].ID,BOOK[counter].book_name,&BOOK[counter].quantity);
            if (id == BOOK[counter].ID)
            {
                continue;
            }
            else
            {
                fprintf(ptr,"\n%d\t%s\t%d",BOOK[counter].ID,BOOK[counter].book_name,BOOK[counter].quantity);
            }
        }
        counter++;
    }
    fclose(fptr);
    fclose(ptr);
    fptr=fopen("books.TXT","w");
    ptr=fopen("temp.TXT","r");
    if((fptr && ptr )== NULL)
    {
        printf("\t\tCan not open the file\n");
    }
    else
    {
        while(!feof(ptr))
        {
            fscanf(ptr,"%d%s%d",&BOOK[counter].ID,BOOK[counter].book_name,&BOOK[counter].quantity);
            fprintf(fptr,"%d\t%s\t%d\n",BOOK[counter].ID,BOOK[counter].book_name,BOOK[counter].quantity);
        }
        counter++;
        fclose(fptr);
        fclose(ptr);
        remove("temp.TXT");
    }
    printf("\t\t __Done__\n");
}

int search_by_ID(int id, int start)
{
    if (BOOK[start].ID == NULL)
        return -1;
    if (id == BOOK[start].ID)
        return start;
    else
        return search_by_ID(id, start + 1);
}

void  search_by_name()
{
    fptr=fopen("books.TXT","r");
    fscanf(fptr,"%d%s%d",&BOOK[counter].ID,BOOK[counter].book_name,&BOOK[counter].quantity);
    int Z=0,res;
    char name[20];
    printf("\t\tenter name of the book to search about: \n\t\t>>>: ");
    fflush(stdin);
    scanf("%s",name);
    while(!feof(fptr))
    {
        fscanf(fptr,"%d%s%d",&BOOK[counter].ID,BOOK[counter].book_name,&BOOK[counter].quantity);
        res=strcmp(BOOK[counter].book_name,name);
        if (res==0)
        {
            printf("\n\t\tID:  %d\tName:  %s\tQuantity: %d\n",BOOK[counter].ID,BOOK[counter].book_name,BOOK[counter].quantity);
            Z=1;
            break;
        }
    }
    if (Z==0)
    {
        printf("\t\tNot founded\n");
    }
    fclose(fptr);
}

void  print_sorted()
{
    fptr=fopen("books.TXT","r");
    while(!feof(fptr))
    {
        fscanf(fptr,"%d%s%d",&BOOK[counter].ID,BOOK[counter].book_name,&BOOK[counter].quantity);
        counter++;
    }
    struct books temp;
    int i;
    for(i=0; i<counter; i++)
    {
        for (int j=i+1; j<counter; j++)
        {
            if (strcmp(BOOK[i].book_name,BOOK[j].book_name)>0)
            {
                strcpy(temp.book_name,BOOK[i].book_name);
                strcpy(BOOK[i].book_name,BOOK[j].book_name);
                strcpy(BOOK[j].book_name,temp.book_name);

                temp.ID=BOOK[i].ID;
                BOOK[i].ID=BOOK[j].ID;
                BOOK[j].ID=temp.ID;

                temp.quantity=BOOK[i].quantity;
                BOOK[i].quantity=BOOK[j].quantity;
                BOOK[j].quantity=temp.quantity;
            }
        }
    }
    for (i=0; i<counter; i++)
    {
        printf("\n\t\tID:  %d\t Name:  %s\tQuantity: %d\n",BOOK[i].ID,BOOK[i].book_name,BOOK[i].quantity);
    }
    fclose(fptr);
}
void print_unsorted()
{
    fptr=fopen("books.TXT","r");
    if(fptr==NULL)
    {
        printf("\t\tcan not open the file\n");
    }
    else
    {
        while(!feof(fptr))
        {
            fscanf(fptr,"%d%s%d",&BOOK[counter].ID,BOOK[counter].book_name,&BOOK[counter].quantity);
            printf("\n\t\tID:  %d\tName:  %s\tQuantity: %d\n",BOOK[counter].ID,BOOK[counter].book_name,BOOK[counter].quantity);
        }
    }
    fclose(fptr);
}
int main()
{
    printf("\n\t\t-------------------------------------------\n");
    printf("\t\t\t**Welcome To The Library**\n");
    printf("\t\t-------------------------------------------\n\n");
    char o;
    printf("\t\t>>> if you want do operation click Y/y \n\n\t\t>>>: ");
    scanf("%c",&o);
    int x;
    while (o=='Y' || o=='y')
    {
        printf("\n\t\tchoose an operation : \n\n");
        printf("\t\t1: Add new book \n");
        printf("\t\t2: Delete book by ID \n");
        printf("\t\t3: Search for book by ID \n");
        printf("\t\t4: Search for book by name \n");
        printf("\t\t5: Print books sorted by name \n");
        printf("\t\t6: Print books \n\n\t\t>>>: ");
        scanf("%d",&x);
        switch(x)
        {
        case 1:
            Add();
            break;
        case 2:
            delete_book();
            break;
        case 3:
        {
            int id;
            printf("\t\tEnter ID to search about: \n\t\t>>>: ");
            scanf("%d",&id);
            int start =search_by_ID(id,0);
            if (start != -1)
            {
                printf("\t\tBook ID: %d\n\t\tBook Name: %s\n\t\tBook quantity: %d\n",BOOK[start].ID,BOOK[start].book_name,BOOK[start].quantity);
            }
            else
            {
                printf("\t\tbook not founded\n");
            }
            break;
        }
        case 4:
            search_by_name();
            break;
        case 5:
            print_sorted();
            break;
        case 6:
            print_unsorted();
            break;
        default :
            printf("\t\tWrong Choice\n");
        }
        printf("\n\t\tif you want another operation click Y/y or n to quit \n\n\t\t>>>: ");
        fflush(stdin);
        scanf("%c",&o);
    }
    return 0;
}
