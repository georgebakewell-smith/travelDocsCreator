#include <stdio.h>
#include <stdlib.h>

struct traveller *addTraveller(struct traveller *arr, int *numTravellers, char name[30],int age, char phoneNumber[12]);
struct flight *addFlight(struct flight *pF, int *numFlights, char type[9], char depApt[4], char arrApt[4]);
struct accommodation *addAccommodation(struct accommodation *pA, int *numAccommodation, char name[30], char address[100], char dateCI[11], char dateCO[11]);
void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, int numTravellers, int numFlights, int numAccommodation);

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

struct accommodation{
    char address[100];
    char name [30];
    char dateCI[11];
    char dateCO[11];
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
        case 2:
            printf("Accommodation\n");
            printf("-----------\n\n");
    }

}

int main()
{
    int numTravellers = 0;
    int numFlights = 0;
    int numAccommodation = 0;


    //Allocate memory to structure
    struct traveller *arr = (struct traveller *)malloc(numTravellers*sizeof(struct traveller));
    struct flight *pF = (struct flight *)malloc(numFlights*sizeof(struct flight));
    struct accommodation *pA = (struct accommodation *)malloc(numAccommodation*sizeof(struct accommodation));


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
                    break;
                case 2:
                    pA = addAccommodation(pA, &numAccommodation, "Good Hostel", "P.Sherman 42 Wallaby Way Sydney", "31/10/1998", "10/11/1998");
                    printf("%s\n",pA[numAccommodation-1].name);
                    printf("%s\n",pA[numAccommodation-1].address);
                    printf("%s - %s\n",pA[numAccommodation-1].dateCI, pA[numAccommodation-1].dateCO);
                    break;
                }
                break;
            case 'w':
                currentMenu -= 1;
                if(currentMenu==-1){
                    currentMenu = 2;
                }
                break;
            case 's':
                currentMenu += 1;
                if(currentMenu==3){
                    currentMenu = 0;
                }
                break;

            case 'q':
                finish = 1;

                break;

            default:
                printf("Type something correct");

        }
    }
    createDoc(arr, pF, pA, numTravellers, numFlights, numAccommodation);
    free(arr);
    free(pF);

    return 0;
}

void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, int numTravellers, int numFlights, int numAccommodation){
    FILE *fp;
    fp = fopen("output.txt", "w"); // open the file in write mode

    if (fp == NULL) { // error checking
        printf("Error opening file\n");
        exit(1);
    }

    //Travellers
    fprintf(fp, "Travellers\n");
    fprintf(fp, "-----------\n");
    for(int i=0;i<numTravellers;i++){
        fprintf(fp, "%s\t", pT[i].name); // write the string to the file
        fprintf(fp, "%d\t", pT[i].age);
        fprintf(fp, "%s\t\n", pT[i].phoneNumber);
    }
    fprintf(fp, "\n");

    //Flights
    fprintf(fp, "Flights\n");
    fprintf(fp, "-----------\n");
    for(int i=0;i<numFlights;i++){
        fprintf(fp, "%s\t", pF[i].type); // write the string to the file
        fprintf(fp, "%s\->%s\n", pF[i].depApt,pF[i].arrApt);
    }
    fprintf(fp, "\n");

    //Accommodation
    fprintf(fp, "Accommodation\n");
    fprintf(fp, "-----------\n");
    for(int i=0;i<numAccommodation;i++){
        fprintf(fp, "%s\n", pA[i].name); // write the string to the file
        fprintf(fp, "%s\n", pA[i].address);
        fprintf(fp,"%s - %s\n\n", pA[i].dateCI, pA[i].dateCO);
    }

    fclose(fp);

}

struct accommodation *addAccommodation(struct accommodation *pA, int *numAccommodation, char name[30], char address[100], char dateCI[11], char dateCO[11]){

    (*numAccommodation)++;
    pA = realloc(pA,*numAccommodation*sizeof(struct accommodation));

    strcpy(pA[*numAccommodation-1].name,name);
    strcpy(pA[*numAccommodation-1].address,address);
    strcpy(pA[*numAccommodation-1].dateCI,dateCI);
    strcpy(pA[*numAccommodation-1].dateCO,dateCO);


    printf("There is %d accommodation.\n",*numAccommodation);

    return pA;
}
struct flight *addFlight(struct flight *pF, int *numFlights, char type[9], char depApt[4], char arrApt[4]){

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
