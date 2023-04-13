#include <stdio.h>
#include <stdlib.h>

struct traveller *addTraveller(struct traveller *arr, int *numTravellers, char name[30],int age, char phoneNumber[12]);
struct flight *addFlight(struct flight *pF, int *numFlights, char type[9], char depApt[4], char arrApt[4]);

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
    int numTravellers = 0;
    int numFlights = 0;


    //Allocate memory to structure
    struct traveller *arr = (struct traveller *)malloc(numTravellers*sizeof(struct traveller));
    struct flight *pF = (struct flight *)malloc(numFlights*sizeof(struct flight));


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
                    arr = addTraveller(arr,&numTravellers,"George Bakewell-Smith", numTravellers, "07923108559");

                    printf("%s\n",arr[numTravellers-1].name);
                    printf("%d\n",arr[numTravellers-1].age);
                    printf("%s\n",arr[numTravellers-1].phoneNumber);
                    printf("\nNumber of travellers: %d\n\n",numTravellers);
                    break;

                case 1:
                    pF = addFlight(pF, &numFlights, "Outbound", "LHR", "PMI");
                    printf("%s\n",pF[numFlights-1].type);
                    printf("%s\n",pF[numFlights-1].depApt);
                    printf("%s\n",pF[numFlights-1].arrApt);
                }
                break;
            case 's':
                currentMenu += 1;
                if(currentMenu==2){
                    currentMenu = 0;
                }
                break;

            case 'q':
                finish = 1;
                printf("Test");
                break;

            default:
                printf("Type something correct");

        }
    }
    free(arr);
    free(pF);
    printf("\n\n%d",finish);
    return 0;
}

struct flight *addFlight(struct flight *pF, int *numFlights, char type[9], char depApt[4], char arrApt[4]){
    printf("Test\n");
    (*numFlights)++;
    pF = realloc(pF,*numFlights*sizeof(struct flight));

    strcpy(pF[*numFlights-1].type,type);
    strcpy(pF[*numFlights-1].depApt,depApt);
    strcpy(pF[*numFlights-1].arrApt,arrApt);

    printf("There are %d flights.\n",*numFlights);

return pF;
}

struct traveller *addTraveller(struct traveller *arr, int *numTravellers, char name[30],int age, char phoneNumber[12]){
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

    *numTravellers += 1;
    arr = realloc(arr,*numTravellers*sizeof(struct traveller));

    strcpy(arr[*numTravellers-1].name,name);
    strcpy(arr[*numTravellers-1].phoneNumber,phoneNumber);
    arr[*numTravellers-1].age = 100*(age+1);

    return arr;
}
