#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char id[20];
    char name[100];
    char author[100];
    int no_copy;
};

void clearScreen() {
    system("cls");   // for Windows
}

void control_panel() {
    clearScreen();
    printf("\n\n\t\t\t\tCONTROL PANEL");
    printf("\n\n1. ADD BOOK");
    printf("\n2. DISPLAY BOOKS");
    printf("\n3. CHECK PARTICULAR BOOK");
    printf("\n4. UPDATE BOOK");
    printf("\n5. DELETE BOOK");
    printf("\n6. EXIT");
}

void add_book() {
    clearScreen();
    struct Book book;
    FILE *file;
    
    printf("\n\n\t\t\t\tADD BOOKS\n");

    printf("Book ID: ");
    scanf("%s", book.id);
    printf("Book Name: ");
    scanf(" %s", book.name);
    printf("Author Name: ");
    scanf(" %s", book.author);
    
    // Input validation loop for No. of Books
    while (1) {
        printf("No. of Books: ");
        if (scanf("%d", &book.no_copy) == 1) {
            break; // Input is valid
        }
        else {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }

    file = fopen("D://book.txt", "a");
    if (file == NULL) {
        printf("\nFile Opening Error!");
        return;
    }

    fprintf(file, "%s %s %s %d\n", book.id, book.name, book.author, book.no_copy);
    fclose(file);
}



void show_book() {
    clearScreen();
    FILE *file;
    struct Book book;
    file = fopen("D://book.txt", "r");

    if (file == NULL) {
        printf("\nFile Opening Error!");
        return;
    }

    printf("\n\n\t\t\t\tAll BOOKS\n");
    printf("%-15s%-30s%-30s%-15s\n", "Book ID", "Book", "Author", "No. of Books");
    printf("--------------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%s %s %s %d", book.id, book.name, book.author, &book.no_copy) != EOF) {
        printf("%-15s%-30s%-30s%-15d\n", book.id, book.name, book.author, book.no_copy);
    }

    fclose(file);
    system("pause");
}

void check_book() {
    clearScreen();
    FILE *file;
    struct Book book;
    char book_id[20];
    int found = 0;

    printf("\n\n\t\t\t\tCheck Particular Book");
    file = fopen("D://book.txt", "r");

    if (file == NULL) {
        printf("\nFile Opening Error!");
        return;
    }

    printf("\n\nBook ID: ");
    scanf("%s", book_id);

    while (fscanf(file, " %s %s %s %d", book.id, book.name, book.author, &book.no_copy) != EOF) {
        if (strcmp(book_id, book.id) == 0) {
            clearScreen();
            printf("\n\n\t\t\t\tCheck Particular Book");
            printf("\n\nBook ID: %s", book.id);
            printf("\nName: %s", book.name);
            printf("\nAuthor: %s", book.author);
            printf("\nNo. of Books: %d", book.no_copy);
            printf("\n\n");
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found == 0) {
        printf("\nBook ID Not Found...");
    }

    system("pause");
}

void update_book() {
    clearScreen();
    FILE *file, *file1;
    struct Book book;
    char book_id[20];
    int found = 0;

    printf("\n\n\t\t\t\tUpdate Book Record");
    file1 = fopen("D://book1.txt", "a");
    file = fopen("D://book.txt", "r");

    if (file == NULL) {
        printf("\nFile Opening Error!");
        return;
    }

    printf("\n\nBook ID: ");
    scanf("%s", book_id);

    while (fscanf(file, " %s %[^\n]s %[^\n]s %d", book.id, book.name, book.author, &book.no_copy) != EOF) {
        if (strcmp(book_id, book.id) == 0) {
            clearScreen();
            printf("\t\t\t\tUpdate Book Record");
            printf("\n\nNew Book Name: ");
            scanf(" %[^\n]s", book.name);
            printf("Author Name: ");
            scanf(" %[^\n]s", book.author);
            printf("No. of Books: ");
            scanf("%d", &book.no_copy);
            fprintf(file1, " %s %s %s %d\n", book.id, book.name, book.author, book.no_copy);
            found = 1;
        } else {
            fprintf(file1, " %s %s %s %d\n", book.id, book.name, book.author, book.no_copy);
        }
    }

    if (found == 0) {
        printf("\nBook ID Not Found...");
    }

    fclose(file);
    fclose(file1);

    remove("D://book.txt");
    rename("D://book1.txt", "D://book.txt");
    printf("\n");
    system("pause");
}

void del_book() {
    clearScreen();
    FILE *file, *file1;
    struct Book book;
    char book_id[20];
    int found = 0;

    printf("\n\n\t\t\t\tDelete a Book");
    file1 = fopen("D://book1.txt", "a");
    file = fopen("D://book.txt", "r");

    if (file == NULL) {
        printf("\nFile Opening Error...");
        return;
    }

    printf("\n\nBook ID: ");
    scanf("%s", book_id);

    while (fscanf(file, " %s %[^\n]s %[^\n]s %d", book.id, book.name, book.author, &book.no_copy) != EOF) {
        if (strcmp(book_id, book.id) == 0) {
            clearScreen();
            printf("\n\n\t\t\t\tDelete a Book");
            printf("\n\nBook is Deleted Successfully...\n\n");
            found = 1;
        } else {
            fprintf(file1, " %s %s %s %d\n", book.id, book.name, book.author, book.no_copy);
        }
    }

    if (found == 0) {
        printf("\nBook ID Not Found...");
    }

    fclose(file);
    fclose(file1);

    remove("D://book.txt");
    rename("D://book1.txt", "D://book.txt");
    system("pause");
}

void bookShopRecord() {
    int choice;
    char x;

    while (1) {
        control_panel();
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                do {
                    add_book();
                    printf("\n\nWant to add another book? (y/n): ");
                    scanf(" %c", &x);
                } while (x == 'y');
                break;
            case 2:
                show_book();
                break;
            case 3:
                check_book();
                break;
            case 4:
                update_book();
                break;
            case 5:
                del_book();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("\n\nINVALID CHOICE\n");
        }
    }
}

int main() {
    // Function Call
    bookShopRecord();
    return 0;
}