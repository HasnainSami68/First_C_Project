#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bus_details
{
    char bus_id[20];
    char bus_name[20];
    char driver[40];
    int seats;
    char source[40];
    char destination[40];
    char departure_time[10];
    float fare;
} businfo;

// Function Declarations
void add_bus_details();
void view_bus_schedule();
void bus_filter(char source[20], char destination[20]);
int get_total_seats(char bus_id[]);
void bus_seats_info(char bus_id[]);
void generate_bus_seat_info(char bus_id[]);
void reserve_seat();
void update_bus_details();

int main()
{
main_menu:
    int choice;
    while (1)
    {
        printf("\n========= Welcome To Bus Online Services Portal =========\n");
        printf(" 1. Admin Login\n 2. Passenger Menu\n 3. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        getchar();

        // ================================    Admin Part      ================================================

        if (choice == 1)
        {
            int count = 1, authenticated = 0;
            char username[20], password[30];
            printf("\nYou have maximum 4 attempts to login.\n");
            while (count <= 4)
            {
                printf("\nEnter Username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Enter Password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = 0;
                if (strcmp(username, "ADMIN") == 0 && strcmp(password, "ADMIN00119922") == 0)
                {
                    authenticated = 1;
                    break;
                }
                printf("Wrong credentials. Try again.\n");
                count++;
            }
            if (!authenticated)
            {
                printf("Too many failed attempts. Exiting...\n");
                exit(1);
            }

            int option;
            while (1)
            {
                printf("\n===== ADMIN MENU =====\n");
                printf("1. Add Bus Details\n2. View Bus Schedule\n3. Update Bus Details\n4. Exit\n");
                printf("Enter Your Choice: ");
                scanf("%d", &option);
                getchar();
                switch (option)
                {
                case 1:
                    add_bus_details();
                    break;
                case 2:
                    view_bus_schedule();
                    break;
                case 3:
                    update_bus_details();
                    break;
                case 4:
                    goto main_menu;
                default:
                    printf("Invalid Option.\n");
                }
            }
        }
        // ===============================Passenger Menu ==============================================
        else if (choice == 2)
        {
            int opt;
            while (1)
            {
                printf("\n========Passenger Menu=========\n");
                printf("1. View Available Buses\n2. Book Ticket\n3. Exit\n");
                printf("Enter Your Choice: ");
                scanf("%d", &opt);
                getchar();
                switch (opt)
                {
                case 1:
                {
                    int opt2;
                    printf("1. All Bus Schedule\n2. Filter by Route\nEnter choice: ");
                    scanf("%d", &opt2);
                    getchar();
                    if (opt2 == 1)
                        view_bus_schedule();
                    else if (opt2 == 2)
                    {
                        char src[20], dest[20];
                        printf("Enter Departure City: ");
                        fgets(src, sizeof(src), stdin);
                        src[strcspn(src, "\n")] = 0;
                        printf("Enter Destination City: ");
                        fgets(dest, sizeof(dest), stdin);
                        dest[strcspn(dest, "\n")] = 0;
                        bus_filter(src, dest);
                    }
                    else
                        printf("Invalid input.\n");
                    break;
                }
                case 2:
                {
                    int choice2;
                    while (1)
                    {
                        printf("\n=== BUS RESERVATION ===\n");
                        printf("1. View Seats Info\n2. Book a Seat\n3. Back\nEnter Choice: ");
                        scanf("%d", &choice2);
                        getchar();
                        if (choice2 == 1)
                        {
                            char id[20];
                            printf("\n\nEnter Alphabetic Part Of BUS I'D here! Like BUS I'D is (ANR 3066). You Have To Enter (ANR)only as Bus I'D\n\n");
                            printf("Enter Bus ID: ");
                            fgets(id, sizeof(id), stdin);
                            id[strcspn(id, "\n")] = 0;
                            generate_bus_seat_info(id);
                        }
                        else if (choice2 == 2)
                            reserve_seat();
                        else if (choice2 == 3)
                            break;
                        else
                            printf("Invalid input.\n");
                    }
                    break;
                }
                case 3:
                    printf("Exiting Passenger Menu.\n");
                    exit(0);
                default:
                    printf("Invalid input.\n");
                }
            }
        }
        else if (choice == 3)
        {
            printf("Thank you! Goodbye.\n");
            exit(0);
        }
        else
        {
            printf("Invalid input. Try again.\n");
        }
    }
    return 0;
}

// ================= Functions Implementation ==================

void add_bus_details()
{
    businfo b[30];
    int n, choice;
    FILE *fptr;

    printf("\n1. Add Details For first Time.\n2. Append Bus Details to Existing Data\nEnter Choice: ");
    scanf("%d", &choice);
    getchar();
    fptr = (choice == 1) ? fopen("Busdata.txt", "w") : (choice == 2) ? fopen("Busdata.txt", "a")
                                                                     : NULL;

    if (!fptr)
    {
        printf("File error!\n");
        return;
    }

    printf("Number of buses to enter (max 30): ");
    scanf("%d", &n);
    getchar();
    if (n > 30)
        n = 30;

    for (int i = 0; i < n; i++)
    {
        printf("\nBus %d Details:\n", i + 1);
        printf("Bus ID: ");
        fgets(b[i].bus_id, sizeof(b[i].bus_id), stdin);
        printf("Bus Name: ");
        fgets(b[i].bus_name, sizeof(b[i].bus_name), stdin);
        printf("Driver Name: ");
        fgets(b[i].driver, sizeof(b[i].driver), stdin);
        printf("Total Seats: ");
        scanf("%d", &b[i].seats);
        getchar();
        printf("Departure From: ");
        fgets(b[i].source, sizeof(b[i].source), stdin);
        printf("Arrival At: ");
        fgets(b[i].destination, sizeof(b[i].destination), stdin);
        printf("Departure Time: ");
        fgets(b[i].departure_time, sizeof(b[i].departure_time), stdin);
        printf("Fare: ");
        scanf("%f", &b[i].fare);
        getchar();

        // Remove newlines
        strcspn(b[i].bus_id, "\n") && (b[i].bus_id[strcspn(b[i].bus_id, "\n")] = 0);
        strcspn(b[i].bus_name, "\n") && (b[i].bus_name[strcspn(b[i].bus_name, "\n")] = 0);
        strcspn(b[i].driver, "\n") && (b[i].driver[strcspn(b[i].driver, "\n")] = 0);
        strcspn(b[i].source, "\n") && (b[i].source[strcspn(b[i].source, "\n")] = 0);
        strcspn(b[i].destination, "\n") && (b[i].destination[strcspn(b[i].destination, "\n")] = 0);
        strcspn(b[i].departure_time, "\n") && (b[i].departure_time[strcspn(b[i].departure_time, "\n")] = 0);

        fprintf(fptr, "Bus ID: %s\nBus Name: %s\nDriver: %s\nTotal Seats: %d\n", b[i].bus_id, b[i].bus_name, b[i].driver, b[i].seats);
        fprintf(fptr, "Departure From: %s\nArrival At: %s\nDeparture Time: %s\nTotal Fare :%.2f\n\n", b[i].source, b[i].destination, b[i].departure_time, b[i].fare);
    }
    fclose(fptr);
    printf("\nBus details added successfully!\n");
}

void view_bus_schedule()
{
    FILE *fptr = fopen("Busdata.txt", "r");
    if (!fptr)
    {
        printf("File not found!\n");
        return;
    }
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
        putchar(ch);
    fclose(fptr);
}

void bus_filter(char source[20], char destination[20])
{
    FILE *ptr = fopen("Busdata.txt", "r");
    if (!ptr)
    {
        printf("File open error.\n");
        return;
    }

    char line[200];
    int print_bus = 0;
    printf("\nMatching Buses from %s to %s:\n\n", source, destination);

    while (fgets(line, sizeof(line), ptr))
    {
        if (strstr(line, "Departure From:") && strstr(line, source))
            print_bus = 1;
        else if (strstr(line, "Arrival At:") && (!strstr(line, destination)))
            print_bus = 0;

        if (print_bus)
            printf("%s", line);

        if (strstr(line, "Departure Time:") && print_bus)
        {
            printf("-------------------------\n");
            print_bus = 0;
        }
    }
    fclose(ptr);
}

int get_total_seats(char bus_id[])
{
    FILE *f = fopen("Busdata.txt", "r");
    char line[100], id[20];
    int seats = -1, found = 0;

    if (!f)
        return -1;

    while (fgets(line, sizeof(line), f))
    {
        if (strncmp(line, "Bus ID:", 7) == 0)
        {
            sscanf(line, "Bus ID: %s", id);
            found = strcmp(id, bus_id) == 0;
        }
        if (found && strncmp(line, "Total Seats:", 12) == 0)
        {
            sscanf(line, "Total Seats: %d", &seats);
            break;
        }
    }
    fclose(f);
    return seats;
}

void bus_seats_info(char bus_id[])
{
    int total = get_total_seats(bus_id);
    if (total == -1)
    {
        printf("Bus ID not found!\n");
        return;
    }

    int booked[100] = {0}, booked_count = 0;
    FILE *res = fopen("seats_reserved.txt", "r");
    if (res)
    {
        char id[20], name[50], cnic[30];
        int seat;
        while (fscanf(res, "%s %d %s %s", id, &seat, name, cnic) != EOF)
            if (strcmp(id, bus_id) == 0)
                booked[seat] = 1, booked_count++;
        fclose(res);
    }

    printf("\nBooked (%d): ", booked_count);
    for (int i = 1; i <= total; i++)
        if (booked[i])
            printf("%d ", i);
    printf("\nAvailable (%d): ", total - booked_count);
    for (int i = 1; i <= total; i++)
        if (!booked[i])
            printf("%d ", i);
    printf("\n");
}

void generate_bus_seat_info(char bus_id[])
{
    printf("\nShowing seat information for Bus ID: %s\n", bus_id);
    bus_seats_info(bus_id);
}

void reserve_seat()
{
    char bus_id[20], name[50], cnic[30];
    int seat, total, booked[100] = {0};

    printf("Enter Bus ID: ");
    scanf("%s", bus_id);

    total = get_total_seats(bus_id);
    if (total == -1)
    {
        printf("Invalid Bus ID!\n");
        return;
    }

    FILE *res = fopen("seats_reserved.txt", "r");
    if (res)
    {
        char id[20], tmpname[50], tmpcnic[30];
        int tmpseat;
        while (fscanf(res, "%s %d %s %s", id, &tmpseat, tmpname, tmpcnic) != EOF)
            if (strcmp(id, bus_id) == 0)
                booked[tmpseat] = 1;
        fclose(res);
    }

    generate_bus_seat_info(bus_id);
    printf("Enter Seat Number to Book: ");
    scanf("%d", &seat);
    getchar();

    if (seat < 1 || seat > total || booked[seat])
    {
        printf("Seat not available or invalid.\n");
        return;
    }

    printf("Enter Passenger Name: ");
    scanf("%s", name);
    printf("Enter CNIC: ");
    scanf("%s", cnic);

    FILE *res_out = fopen("seats_reserved.txt", "a");
    fprintf(res_out, "%s %d %s %s\n", bus_id, seat, name, cnic);
    fclose(res_out);
    printf("Seat booked successfully!\n");
}

void update_bus_details()
{
    FILE *fptr;
    businfo b[30];
    int count = 0, found = 0;
    char id_to_update[20];

    fptr = fopen("Busdata.txt", "r");
    if (!fptr)
        return;

    while (fscanf(fptr, "Bus ID: %[^\n]\n", b[count].bus_id) == 1)
    {
        fgets(b[count].bus_name, sizeof(b[count].bus_name), fptr);
        fgets(b[count].driver, sizeof(b[count].driver), fptr);
        fscanf(fptr, "Total Seats: %d\n", &b[count].seats);
        fgets(b[count].source, sizeof(b[count].source), fptr);
        fgets(b[count].destination, sizeof(b[count].destination), fptr);
        fgets(b[count].departure_time, sizeof(b[count].departure_time), fptr);
        fscanf(fptr, "Total Fare :%f\n", &b[count].fare);
        fgetc(fptr); // consume newline
        count++;
    }
    fclose(fptr);

    printf("Enter Bus ID to Update: ");
    fgets(id_to_update, sizeof(id_to_update), stdin);
    id_to_update[strcspn(id_to_update, "\n")] = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(b[i].bus_id, id_to_update) == 0)
        {
            found = 1;
            printf("New Bus Name: ");
            fgets(b[i].bus_name, sizeof(b[i].bus_name), stdin);
            printf("Driver: ");
            fgets(b[i].driver, sizeof(b[i].driver), stdin);
            printf("Seats: ");
            scanf("%d", &b[i].seats);
            getchar();
            printf("From: ");
            fgets(b[i].source, sizeof(b[i].source), stdin);
            printf("To: ");
            fgets(b[i].destination, sizeof(b[i].destination), stdin);
            printf("Time: ");
            fgets(b[i].departure_time, sizeof(b[i].departure_time), stdin);
            printf("Fare: ");
            scanf("%f", &b[i].fare);
            getchar();
            break;
        }
    }

    if (!found)
    {
        printf("Bus not found!\n");
        return;
    }

    fptr = fopen("Busdata.txt", "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(fptr, "Bus ID: %s\nBus Name: %sDriver: %sTotal Seats: %d\n", b[i].bus_id, b[i].bus_name, b[i].driver, b[i].seats);
        fprintf(fptr, "Departure From: %sArrival At: %sDeparture Time: %sTotal Fare :%.2f\n\n", b[i].source, b[i].destination, b[i].departure_time, b[i].fare);
    }
    fclose(fptr);
    printf("Bus updated successfully.\n");
}
