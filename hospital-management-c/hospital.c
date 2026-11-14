#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

/* ---------------- PATIENT LINKED LIST ---------------- */

struct Patient
{
    int id;
    char name[50];
    int age;
    char disease[50];
    struct Patient *next;
};

struct Patient *phead = NULL;

/* ---------------- DOCTOR LINKED LIST ---------------- */

struct Doctor
{
    int id;
    char name[50];
    char specialization[50];
    struct Doctor *next;
};

struct Doctor *dhead = NULL;

/* ---------------- APPOINTMENT QUEUE ---------------- */

struct Queue
{
    int patientID;
    struct Queue *next;
};

struct Queue *front = NULL;
struct Queue *rear = NULL;

/* ---------------- EMERGENCY PRIORITY QUEUE ---------------- */

struct Emergency
{
    int patientID;
    int priority;
};

struct Emergency emergency[MAX];
int ecount = 0;

/* ---------------- PATIENT REGISTRATION ---------------- */

void registerPatient()
{
    struct Patient *temp = (struct Patient *)malloc(sizeof(struct Patient));

    printf("Enter Patient ID: ");
    scanf("%d", &temp->id);

    printf("Enter Name: ");
    scanf("%s", temp->name);

    printf("Enter Age: ");
    scanf("%d", &temp->age);

    printf("Enter Disease: ");
    scanf("%s", temp->disease);

    temp->next = NULL;

    if (phead == NULL)
        phead = temp;
    else
    {
        struct Patient *ptr = phead;

        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = temp;
    }

    printf("Patient Registered Successfully\n");
}

/* ---------------- DISPLAY PATIENT ---------------- */

void displayPatients()
{
    struct Patient *ptr = phead;

    if (ptr == NULL)
    {
        printf("No Patients Found\n");
        return;
    }

    while (ptr != NULL)
    {
        printf("\nID:%d Name:%s Age:%d Disease:%s\n",
               ptr->id, ptr->name, ptr->age, ptr->disease);

        ptr = ptr->next;
    }
}

/* ---------------- ADD DOCTOR ---------------- */

void addDoctor()
{
    struct Doctor *temp = (struct Doctor *)malloc(sizeof(struct Doctor));

    printf("Enter Doctor ID: ");
    scanf("%d", &temp->id);

    printf("Enter Doctor Name: ");
    scanf("%s", temp->name);

    printf("Enter Specialization: ");
    scanf("%s", temp->specialization);

    temp->next = NULL;

    if (dhead == NULL)
        dhead = temp;
    else
    {
        struct Doctor *ptr = dhead;

        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = temp;
    }

    printf("Doctor Added Successfully\n");
}

/* ---------------- DISPLAY DOCTORS ---------------- */

void displayDoctors()
{
    struct Doctor *ptr = dhead;

    if (ptr == NULL)
    {
        printf("No Doctors Available\n");
        return;
    }

    while (ptr != NULL)
    {
        printf("\nDoctor ID:%d Name:%s Specialization:%s\n",
               ptr->id, ptr->name, ptr->specialization);

        ptr = ptr->next;
    }
}

/* ---------------- ADD APPOINTMENT (QUEUE) ---------------- */

void addAppointment()
{
    struct Queue *temp = (struct Queue *)malloc(sizeof(struct Queue));

    printf("Enter Patient ID for Appointment: ");
    scanf("%d", &temp->patientID);

    temp->next = NULL;

    if (rear == NULL)
    {
        front = rear = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }

    printf("Appointment Added\n");
}

/* ---------------- ATTEND APPOINTMENT ---------------- */

void attendAppointment()
{
    if (front == NULL)
    {
        printf("No Appointments\n");
        return;
    }

    struct Queue *temp = front;

    printf("Attending Patient ID: %d\n", temp->patientID);

    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);
}

/* ---------------- ADD EMERGENCY ---------------- */

void addEmergency()
{
    int id, priority;

    printf("Enter Patient ID: ");
    scanf("%d", &id);

    printf("Enter Priority (1-High 2-Medium 3-Low): ");
    scanf("%d", &priority);

    emergency[ecount].patientID = id;
    emergency[ecount].priority = priority;

    ecount++;

    printf("Emergency Patient Added\n");
}

/* ---------------- PROCESS EMERGENCY ---------------- */

void processEmergency()
{
    if (ecount == 0)
    {
        printf("No Emergency Cases\n");
        return;
    }

    int highest = 0;

    for (int i = 1; i < ecount; i++)
    {
        if (emergency[i].priority < emergency[highest].priority)
            highest = i;
    }

    printf("Treating Emergency Patient ID: %d\n",
           emergency[highest].patientID);

    for (int i = highest; i < ecount - 1; i++)
        emergency[i] = emergency[i + 1];

    ecount--;
}

/* ---------------- BILLING MODULE ---------------- */

void generateBill()
{
    int id;
    float consultation = 500;
    float medicine, test;

    printf("Enter Patient ID: ");
    scanf("%d", &id);

    printf("Enter Medicine Charges: ");
    scanf("%f", &medicine);

    printf("Enter Test Charges: ");
    scanf("%f", &test);

    float total = consultation + medicine + test;

    printf("\n------ BILL INVOICE ------\n");
    printf("Patient ID: %d\n", id);
    printf("Consultation: %.2f\n", consultation);
    printf("Medicine: %.2f\n", medicine);
    printf("Tests: %.2f\n", test);
    printf("Total Bill: %.2f\n", total);
}

/* ---------------- DISCHARGE PATIENT ---------------- */

void dischargePatient()
{
    int id;

    printf("Enter Patient ID to Discharge: ");
    scanf("%d", &id);

    struct Patient *temp = phead;
    struct Patient *prev = NULL;

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Patient Not Found\n");
        return;
    }

    if (prev == NULL)
        phead = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Patient Discharged Successfully\n");
}

/* ---------------- MAIN FUNCTION ---------------- */

int main()
{
    int choice;

    while (1)
    {
        printf("\n---- HOSPITAL MANAGEMENT SYSTEM ----\n");
        printf("1.Register Patient\n");
        printf("2.Display Patients\n");
        printf("3.Add Doctor\n");
        printf("4.Display Doctors\n");
        printf("5.Add Appointment\n");
        printf("6.Attend Appointment\n");
        printf("7.Add Emergency\n");
        printf("8.Process Emergency\n");
        printf("9.Generate Bill\n");
        printf("10.Discharge Patient\n");
        printf("11.Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerPatient();
            break;
        case 2:
            displayPatients();
            break;
        case 3:
            addDoctor();
            break;
        case 4:
            displayDoctors();
            break;
        case 5:
            addAppointment();
            break;
        case 6:
            attendAppointment();
            break;
        case 7:
            addEmergency();
            break;
        case 8:
            processEmergency();
            break;
        case 9:
            generateBill();
            break;
        case 10:
            dischargePatient();
            break;
        case 11:
            exit(0);
        default:
            printf("Invalid Choice\n");
        }
    }

    return 0;
}
