#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dvd
{
    int serial;
    int price;
    char name[21];
    char genre[10];
    char director[19];
    char state[6];
}store[500];

int checkdvd(int serialnumber);
void orderbyname(struct dvd *inventory,int size);
int partialsearch(char *source, char *pattern);
void addnewdvd();
void removedvd();
void searchdvd();
void listdvd();
void editdvd();
void hiredvd();
void quit();
void printheader();

int totaldvd=0;

int main(int argc,char *argv[])
{
    char *tempstring;
    FILE *inputfile;
    //FILE *outputfile;
    char command;
    char buffer[100];
    char cleanstring[100];
    char *emptyline;
    int i,j;
    int programstatus = 1;
    int counter;
    if ((inputfile = fopen( "input.txt", "r" ) ) == NULL )
        printf( "File could not be opened\n" );
    else
    {
        while(fgets(buffer,sizeof(buffer),inputfile)!=NULL)
        {
            emptyline = buffer;

            while(*emptyline==' ' || *emptyline=='\t') emptyline++;
            if(*emptyline != '\n')  //if line is not empty do parsing
            {
                i = 0;
                j = 0;
                while (buffer[i] != '\0') //this loop is for extra tab and space characters
                {
                    if (!((buffer[i] == ' ' || buffer[i] == '\t') && (buffer[i+1] == ' ' || buffer[i+1] == '\t')))
                    {
                        if(buffer[i] == '\t')
                            cleanstring[j] = ' ';
                        else
                            cleanstring[j] = buffer[i];
                        j++;
                    }
                    i++;
                }
                cleanstring[j] = '\0';

                tempstring = strtok(cleanstring,",");
                counter=1;

                while(tempstring != NULL)
                {
                    switch(counter)
                    {
                        case 1:
                            sscanf(tempstring,"%d",&store[totaldvd].serial);
                        break;
                        case 2:
                            sscanf(tempstring,"%d",&store[totaldvd].price);
                        break;
                        case 3:
                            strcpy(store[totaldvd].name,tempstring);
                        break;
                        case 4:
                            strcpy(store[totaldvd].genre,tempstring);
                        break;
                        case 5:
                            strcpy(store[totaldvd].director,tempstring);
                        break;
                        case 6:
                            strcpy(store[totaldvd].state,strtok(tempstring,";"));
                        break;
                    }
                    counter++;
                    tempstring = strtok(NULL,",");
                }
                totaldvd++;
            }
        }
        //printf(outputfile, "%d,%d,%s,%s,%s,%s;\n",store[0].serial, store[0].price, store[0].name,store[0].genre, store[0].director, store[0].state);
        fclose(inputfile);
    }
    while(programstatus)
    {
        printf("\n\n---HUBM DVD---\nA:  Add new dvd\nR:  Remove dvd\nS:  Search dvd\nL:  List dvd\nE:  Edit dvd\nH:  Hire dvd\nQ:  Quit\nEnter Command:");
        scanf("%c",&command);
        fflush(stdin);

        switch(command)
        {
           case 'A': case 'a':
           addnewdvd();
           break;

           case 'R': case 'r':
           removedvd();
           break;

           case 'S': case 's':
           searchdvd();
           break;

           case 'L': case 'l':
           listdvd();
           break;

           case 'E': case 'e':
           editdvd();
           break;

           case 'H': case 'h':
           hiredvd();
           break;

           case 'Q': case 'q':
           quit();
           programstatus = 0;
           break;
        }
    }
    return 0;
}

void quit()
{
    int counter;
    FILE *outputfile;
    if ((outputfile = fopen( "output.txt", "w" ) ) == NULL )
          printf( "File could not be opened\n" );
       else
       {
            for(counter = 0; counter < totaldvd; counter++)
            {
                fprintf(outputfile, "%d,%d,%s,%s,%s,%s;\n",store[counter].serial, store[counter].price, store[counter].name,store[counter].genre, store[counter].director, store[counter].state);
            }
            fclose(outputfile);
       }
}

int checkdvd(int serialnumber)
{
    int i;
    for(i = 0 ; i < totaldvd ; i++)
    {
        if(store[i].serial==serialnumber)
            return i;
    }
    return -1;
}

void addnewdvd()
{
    int serialnumber;
    char string[21];
    printf("Enter the  serial number..");
    scanf("%d",&serialnumber);
    fflush(stdin);
    if(checkdvd(serialnumber) != -1)
    {
        printf("This serial number already exists.");
    }
    else
    {
        store[totaldvd].serial=serialnumber;
        printf("\nEnter the price..");
        scanf("%d",&store[totaldvd].price);
        fflush(stdin);
        printf("\nEnter the name..");
        gets(string);
        fflush(stdin);
        strcpy(store[totaldvd].name, string);
        printf("\nEnter the genre..");
        gets(string);
        fflush(stdin);
        strcpy(store[totaldvd].genre, string);
        printf("\nEnter the director..");
        gets(string);
        fflush(stdin);
        strcpy(store[totaldvd].director, string);
        strcpy(store[totaldvd].state,"Inv");
        totaldvd++;
    }
}

void removedvd()
{
    int serialnumber;
    int i;
    printf("Enter the  serial number..");
    scanf("%d",&serialnumber);
    fflush(stdin);
    int a=checkdvd(serialnumber);
    if(a != -1)
    {
        printf("\n%d,%d,%s,%s,%s,%s",store[a].serial,store[a].price,store[a].name,store[a].genre,store[a].director,store[a].state);
        //printf("\n%d",mystrcmp(store[a].state,"Hired"));
        if(strcmp(store[a].state,"Hired")==0)
            printf("\nThis film is hired,so you can't remove that.");
        else
        {
            for(i=a ; i<totaldvd ;i++)
            {
                store[i].serial=store[i+1].serial;
                store[i].price=store[i+1].price;
                strcpy(store[i].name,store[i+1].name);
                strcpy(store[i].genre,store[i+1].genre);
                strcpy(store[i].director,store[i+1].director);
                strcpy(store[i].state,store[i+1].state);

            }
            totaldvd--;
        }
    }
    else
    {
        printf("Enter the  new serial number..");
    }
}

void listdvd()//4120
{
    orderbyname(store, totaldvd);
    printheader();
    int counter = 0;
    char key;
    int list;
    for(list = 0; list < totaldvd; list++)
    {
        printf("\n%-7d%-6d%-21s%-10s%-19s%-5s",store[list].serial,store[list].price,store[list].name,store[list].genre,store[list].director,store[list].state);
        counter++;

        if(counter == 4)
        {
            counter = 0;
            while(key != '\n')
            {
                key = getchar();
                fflush(stdin);
            }
            key = 0;
        }
    }
}

void searchdvd()
{
    int i;
    char Name[21];
    int counter = 0;
    char key;

    orderbyname(store, totaldvd);
    printf("Enter the name..");
    gets(Name);

    printheader();

    for(i = 0; i < totaldvd ; i++)
    {
        if(partialsearch(store[i].name,Name)== 1)
        {
            counter++;
            printf("\n%-7d%-6d%-21s%-10s%-19s%-5s",store[i].serial,store[i].price,store[i].name,store[i].genre,store[i].director,store[i].state);
            if(counter == 4)
            {
                counter = 0;
                while(key != '\n')
                {
                    key = getchar();
                    fflush(stdin);
                }
                key = 0;
            }

        }

    }
}

void hiredvd()
{
    int serialnumber;
    printf("Enter the  serial number..");
    scanf("%d",&serialnumber);
    fflush(stdin);
    int a=checkdvd(serialnumber);
    if(a != -1)
    {
        strcpy(store[a].state,"Hired");
    }
    else
    {
        printf("This serial number doesn't exist.Try again..");
    }
}

void editdvd()
{
    int serialnumber;
    char string[20];
    printf("Enter the  serial number..");
    scanf("%d",&serialnumber);
    fflush(stdin);
    int a=checkdvd(serialnumber);
    if(a != -1)
    {
        printf("\nSerial:%d\nPrice:%d\nName:%s\nGenre:%s\nDirector:%s\nState:%s",store[a].serial,store[a].price,store[a].name,store[a].genre,store[a].director,store[a].state);
        printf("\nEnter the new price..");
        gets(string);
        fflush(stdin);
        if(strlen(string) > 0) //if there is a character
            sscanf(string, "%d",&store[a].price);
        printf("\nEnter the new name..");
        gets(string);
        fflush(stdin);
        if(strlen(string) > 0)
            strcpy(store[a].name, string);
        printf("\nEnter the new genre..");
        gets(string);
        fflush(stdin);
        if(strlen(string) > 0)
            strcpy(store[a].genre, string);
        printf("\nEnter the new director..");
        gets(string);
        fflush(stdin);
        if(strlen(string) > 0)
            strcpy(store[a].director, string);

    }
    else
    {
        printf("This serial number doesn't exist.Try again..");
    }
}

void orderbyname(struct dvd *inventory,int size)
{
    struct dvd temp;
    int i,j;

    for(i=0;i < size; i++)
    {
        for(j=i+1;j<size;j++)
        {
            if(strcmp(inventory[i].name, inventory[j].name) > 0)
            {
                temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }
    return;
}

void printheader()
{
    printf("\n%-7s%-6s%-21s%-10s%-19s%-5s","SERIAL","PRICE","NAME","GENRE","DIRECTOR","STATE");
    printf("\n%-7s%-6s%-21s%-10s%-19s%-5s","------","-----","----","-----","--------","-----");
}

int partialsearch(char *source, char *pattern)
{
    int i;
    int sourcelength  = strlen(source);
    int patternlength = strlen(pattern);

    if(sourcelength < patternlength)
        return -1;

    for(i = 0; i < patternlength; i++)
         if(source[i] != pattern[i])
                return -1;
         return 1;
}
