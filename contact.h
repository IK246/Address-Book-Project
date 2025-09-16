#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact_data
{
    char name[32];
    char num[11];
    char id[35];
}data;
//typedef struct Contact_data data;

typedef struct Address_book
{
    data details[100], temp;

    int count;
}book;
//typedef struct Address_book book;

/* Function declarations */
void init_intitalization(book *);
int create_contact(book *);
void list_contacts(book *);
int search_contacts(book *, int *);
int edit_contact(book *);
int delete_contact(book *);
int sort_disp(book *);
int sort_disp(book *);
void print_contact(book *, int, int);
void save(book *);

// Validations
int validate_name(char []);
int validate_num(char []);
int validate_id(char []);

// display contact
void display(book *, int);

// retry
int re_enter(char *);

// sort contact
void sort_name(book *);
void sort_num(book *);

// own string function
char *my_strstr(char [], char [], int *);
int my_strcmp(char [], char []);

// text color
#define R "\x1b[31m"
#define G "\x1b[32m"
#define C "\x1b[36m"
#define Re "\x1b[0m"

#endif // CONTACT_H
// CONTACT_H        

