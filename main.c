#include <stdio.h>
#include <stdlib.h>

struct traveller addTraveller(char name[30],int age, char phoneNumber[12]);
struct flight addFlight(char type[9],char depApt[4],char arrApt[4]);

struct traveller{
    char name[30];
    int age;
    char phoneNumber[12];
};
struct flight{
    char type[9];
    char depApt[4];
    char arrApt[4];
};
void dispCurrentMenu(int currentMenu){
    switch(currentMenu){
        case 0:
            printf("Travellers\n");
            printf("-----------\n\n");
            break;
        case 1:
            printf("Flights\n");
            printf("-----------\n\n");
            break;
    }

}

int main()
{
    struct traveller t1;
    struct flight f1;
    struct traveller t2;
    struct flight f2;
    char option;
    int currentMenu = 0, finish = 0;
    while(finish==0){
        dispCurrentMenu(currentMenu);
        printf("Please Enter an Option\n");
        scanf(" %c", &option);
        switch(option){
            case 'a':
                switch(currentMenu){
                case 0:
                    t1 = addTraveller("George Bakewell-Smith", 24, "07923108559");
                    t2 = addTraveller("James Senior", 22, "0792310855");
                    printf("%s\n",t2.name);
                    printf("%d\n",t2.age);
                    printf("%s\n",t2.phoneNumber);
                    break;
                case 1:
                    f1 = addFlight("Outbound","LHR","PMI");
                    f2 = addFlight("Inbound","PMI","LHR");
                    printf("%s->%s\n",f2.depApt,f2.arrApt);
                    break;
                }
                break;

            case 'w':
                currentMenu -= 1;
                if(currentMenu==-1){
                    currentMenu = 1;
                }

                break;
            case 's':
                currentMenu +=1;
                if(currentMenu==2){
                    currentMenu = 0;
                }

                break;

            case 'q':
                finish = 1;

            default:
                printf("Type something correct");
        }
    }
    return 0;
}

struct flight addFlight(char type[9],char depApt[4],char arrApt[4]){
    struct flight f;
    strcpy(f.type,type);
    strcpy(f.depApt,depApt);
    strcpy(f.arrApt,arrApt);

    return f;
}

struct traveller addTraveller(char name[30],int age, char phoneNumber[12]){
    struct traveller t;
    /*
    int age;
    char name[30];
    char phoneNumber[11];
    printf("Enter traveller name: \n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    // Read the name string
    fgets(t.name, 30, stdin);
    printf("Enter Traveller Age: \n");
    scanf(" %d", &t.age);
    printf("Enter traveller phone number: \n");
    scanf("%s", t.phoneNumber);*/

    strcpy(t.name,name);
    strcpy(t.phoneNumber,phoneNumber);
    t.age = age;

    return t;
}
