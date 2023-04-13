#include <stdio.h>
#include <stdlib.h>

struct traveller *addTraveller(struct traveller *pT, int *numTravellers);
struct flight *addFlight(struct flight *pF, int *numFlights);
struct accommodation *addAccommodation(struct accommodation *pA, int *numAccommodation);
struct insurance *addInsurance(struct insurance *pI, int *numInsurance);
void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, int numTravellers, int numFlights, int numAccommodation, int numInsurance);
int length(char *arr);

struct traveller{
    char name[30];
    int age;
    char phoneNumber[12];
};

struct flight{
    char type[13];
    char depApt[4];
    char arrApt[4];
    char depTime[5];
    char arrTime[5];
    char date[11];
    char airline[30];
    char flightNumber[20];
};

struct accommodation{
    char address[100];
    char name [30];
    char dateCI[11];
    char dateCO[11];
};

struct insurance{
    char name[30];
    char reference[30];
    char number[12];
};



void dispCurrentMenu(int currentMenu){
    switch(currentMenu){
        case 0:
            printf("Travellers\n");
            printf("-------------------\n\n");
            break;
        case 1:
            printf("Flights\n");
            printf("-------------------\n\n");
            break;
        case 2:
            printf("Accommodation\n");
            printf("-------------------\n\n");
            break;
        case 3:
            printf("Travel Insurance\n");
            printf("-------------------\n\n");
            break;
    }

}

int main()
{
    int numTravellers = 0;
    int numFlights = 0;
    int numAccommodation = 0;
    int numInsurance = 0;


    //Allocate memory to structurs
    struct traveller *pT = (struct traveller *)malloc(numTravellers*sizeof(struct traveller));
    struct flight *pF = (struct flight *)malloc(numFlights*sizeof(struct flight));
    struct accommodation *pA = (struct accommodation *)malloc(numAccommodation*sizeof(struct accommodation));
    struct insurance *pI = (struct insurance *)malloc(numInsurance*sizeof(struct insurance));


    char option;
    int currentMenu = 0, finish = 0;

    while(finish==0){
        dispCurrentMenu(currentMenu);
        printf("Press a to add item, w or s to navigate menu, q to print. Please Enter an Option:\n");
        scanf(" %c", &option);
        switch(option){
            case 'a':
                switch(currentMenu){
                case 0:
                    pT = addTraveller(pT,&numTravellers);
                    system("cls");
                    break;
                case 1:
                    pF = addFlight(pF, &numFlights);
                    system("cls");
                    break;
                case 2:
                    pA = addAccommodation(pA, &numAccommodation);
                    system("cls");
                    break;
                case 3:
                    pI = addInsurance(pI, &numInsurance);
                    system("cls");
                    break;
                }
                break;
            case 'w':
                currentMenu -= 1;
                if(currentMenu==-1){
                    currentMenu = 3;
                }
                system("cls");
                break;
            case 's':
                currentMenu += 1;
                if(currentMenu==4){
                    currentMenu = 0;
                }
                system("cls");
                break;

            case 'q':
                finish = 1;

                break;

            default:
                printf("Type something correct\n");

        }
    }
    createDoc(pT, pF, pA, pI, numTravellers, numFlights, numAccommodation, numInsurance);
    free(pT);
    free(pF);
    free(pA);
    free(pI);

    return 0;
}

int length(char *arr){
    //Calculate length of array before \n character
    int len = 0;
    while(arr[len] != '\n') {
        len++;
    }
    return len;
}

void createDoc(struct traveller *pT, struct flight *pF, struct accommodation *pA, struct insurance *pI, int numTravellers, int numFlights, int numAccommodation, int numInsurance){
    FILE *fp;
    fp = fopen("output.txt", "w"); // open the file in write mode

    if (fp == NULL) { // error checking
        printf("Error opening file\n");
        exit(1);
    }

    //Travellers
    fprintf(fp, "Travellers\n");
    fprintf(fp, "-------------------\n");
    fprintf(fp, "%-30s%-6s%-12s\n\n", "Name", "Age", "Phone Number");
    for(int i=0;i<numTravellers;i++){
        fprintf(fp, "%-30s%-6d%-12s\n", pT[i].name, pT[i].age,pT[i].phoneNumber); // write the string to the file

    }
    fprintf(fp, "\n");

    //Flights
    fprintf(fp, "Flights\n");
    fprintf(fp, "-------------------\n");
    fprintf(fp,"%-14s%-11s%-13s%-13s%-30s%-20s\n\n","Type", "Airport", "Time", "Date", "Airline", "Flight Number");
    for(int i=0;i<numFlights;i++){
        fprintf(fp, "%-14s%s->%-6s%s->%-7s%-13s%-30s%-20s\n", pF[i].type, pF[i].depApt,pF[i].arrApt, pF[i].depTime,pF[i].arrTime, pF[i].date, pF[i].airline, pF[i].flightNumber);
    }
    fprintf(fp, "\n");

    //Accommodation
    fprintf(fp, "Accommodation\n");
    fprintf(fp, "-------------------\n");
    for(int i=0;i<numAccommodation;i++){
        fprintf(fp, "%s\n", pA[i].name); // write the string to the file
        fprintf(fp, "%s\n", pA[i].address);
        fprintf(fp,"%s - %s\n\n", pA[i].dateCI, pA[i].dateCO);
    }

    //Travel Insurance
    fprintf(fp, "Travel Insurance\n");
    fprintf(fp, "-------------------\n");
    fprintf(fp,"%-30s%-30s%-25s\n\n","Name", "Reference Number", "Emergency Contact Number");
    for(int i=0;i<numInsurance;i++){
        fprintf(fp,"%-30s%-30s%-25s\n",pI[i].name,pI[i].reference,pI[i].number);
        //fprintf(fp, "%s\t", pI[i].name); // write the string to the file
        //fprintf(fp, "%s\t", pI[i].reference);
        //fprintf(fp,"%s\n", pI[i].number);
    }

    fclose(fp);

}

struct insurance *addInsurance(struct insurance *pI, int *numInsurance){
    (*numInsurance)++;
    pI = realloc(pI,*numInsurance*sizeof(struct insurance));

    printf("Enter Insurance Company Name:\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
    // Read the name string
    fgets(pI[*numInsurance-1].name, 30, stdin);
    pI[*numInsurance-1].name[length(pI[*numInsurance-1].name)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Reference Number:\n");
    scanf(" %s", pI[*numInsurance-1].reference);
    printf("Enter an Emergency Contact Number for the Insurance Company");
    scanf(" %s", pI[*numInsurance-1].number);

    return pI;
}

struct accommodation *addAccommodation(struct accommodation *pA, int *numAccommodation){

    (*numAccommodation)++;
    pA = realloc(pA,*numAccommodation*sizeof(struct accommodation));

    printf("Enter Accommodation Name:\n");

    int c;

    while ((c = getchar()) != '\n' && c != EOF){ }

    // Read the name string
    fgets(pA[*numAccommodation-1].name, 30, stdin);
    pA[*numAccommodation-1].name[length(pA[*numAccommodation-1].name)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Address, with each line separated by a comma:\n");
    // Read the name string
    fgets(pA[*numAccommodation-1].address, 100, stdin);
    pA[*numAccommodation-1].address[length(pA[*numAccommodation-1].address)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Check In Date:\n");
    scanf(" %s",pA[*numAccommodation-1].dateCI);
    printf("Enter Check Out Date:\n");
    scanf(" %s",pA[*numAccommodation-1].dateCO);

    printf("There is %d accommodation.\n",*numAccommodation);

    return pA;
}
struct flight *addFlight(struct flight *pF, int *numFlights){

    (*numFlights)++;
    pF = realloc(pF,*numFlights*sizeof(struct flight));
    printf("Enter Flight Type (Outbound, Inbound, or Intermediate):\n");
    scanf(" %s",pF[*numFlights-1].type);
    printf("Enter Departing Airport Code:\n");
    scanf(" %s",pF[*numFlights-1].depApt);
    printf("Enter Destination Airport Code:\n");
    scanf(" %s",pF[*numFlights-1].arrApt);
    printf("Enter Takeoff Time:\n");
    scanf(" %s",pF[*numFlights-1].depTime);
    printf("Enter Landing Time:\n");
    scanf(" %s",pF[*numFlights-1].arrTime);
    printf("Enter Date of Flight:\n");
    scanf(" %s",pF[*numFlights-1].date);
    printf("Enter Airline: \n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
    // Read the name string
    fgets(pF[*numFlights-1].airline, 30, stdin);
    pF[*numFlights-1].airline[length(pF[*numFlights-1].airline)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Flight Number:\n");
    scanf(" %s",pF[*numFlights-1].flightNumber);

    printf("There are %d flights.\n",*numFlights);

    return pF;
}

struct traveller *addTraveller(struct traveller *pT, int *numTravellers){

    (*numTravellers)++;
    pT = realloc(pT,*numTravellers*sizeof(struct traveller));
    printf("Enter traveller name:\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF){ }
    // Read the name string
    fgets(pT[*numTravellers-1].name, 30, stdin);
    pT[*numTravellers-1].name[length(pT[*numTravellers-1].name)] = '\0';  //Replace '\n' with terminator '\0'
    printf("Enter Traveller Age: \n");
    scanf(" %d", &pT[*numTravellers-1].age);
    printf("Enter traveller phone number: \n");
    scanf("%s", pT[*numTravellers-1].phoneNumber);


    return pT;
}
