#include<stdio.h>
#include<string.h>
#include "contact.h"

void init_intitalization(book *add)
{
    add->count = 0;
    FILE *fp = fopen("contact.csv", "r");
    if(!fp)
    {
        puts(R "Error while opening file" Re);
        return;
    }
    fscanf(fp, "#%d\n", &add->count);
    for(int i=0; i<add->count; i++)
        fscanf(fp, "%[^,],%[^,],%[^\n]\n", add->details[i].name, add->details[i].num, add->details[i].id);
    fclose(fp);
}

int create_contact(book *add)
{
    char val;

name:
    printf(C "Enter the Name: " Re);
    scanf(" %[^\n]", add->details[add->count].name);
    if(!validate_name(add->details[add->count].name))
    {
try_name:
        if(re_enter("Name"))
            goto name;
        else
            return 0;
    }

num:
    printf(C "Enter the Phone Number: " Re);
    scanf(" %[^\n]", add->details[add->count].num);
    if(!validate_num(add->details[add->count].num))
    {
try_num:
        if(re_enter("Phone Number"))
            goto num;
        else
            return 0;
    }
    else
    {
        for(int i=0; i<add->count; i++)
            if(!strcmp(add->details[add->count].num, add->details[i].num))
            {
                puts(R "ERROR! Entered Phone Number already exist!!" Re);
                goto try_num;
            }
    }

id:
    printf(C "Enter the Email ID: " Re);
    scanf(" %[^\n]", add->details[add->count].id);
    if(!validate_id(add->details[add->count].id))
    {
try_id:
        if(re_enter("Email ID"))
            goto id;
        else
            return 0;
    }
    else
    {
        for(int i=0; i<add->count; i++)
            if(!my_strcmp(add->details[add->count].id, add->details[i].id))
            {
                puts(R "ERROR! Entered Email ID already exist!!" Re);
                goto try_id;
            }
    }
    add->count++;
    return 1;
}

void list_contacts(book *add)
{
    if(add->count == 0)
        puts(R "No contacts to show!!" Re);
    else
    {
        printf("+----------------------------------------------------------------------+\n");
        printf("!                           LIST OF CONTACTS                           !\n");
        printf("+------------------------+------------------+--------------------------+\n");
        printf("!         " C "Name" Re "           !   " C "Phone Number" Re "   !          " C "Email ID" Re "        !\n");
        printf("+------------------------+------------------+--------------------------+\n");
        for(int i=0; i<add->count; i++)
        {
            print_contact(add, i, i);
        }
    }
}

int search_contacts(book *add, int *ptr)
{
    char str[100], pos[add->count];
    pos[0] = '\0';
    int option, j = 0, i = 0;

    if(add->count == 0)
    {
        puts(R "\nNo contacts to show!!" Re);
        return -3;
    }

option:
    printf(C "search\n" Re "\t1.By Name\n\t2.By Mobile Number\n\t3.By Email ID\n\t4.Exit\n" C "Enter the option: " Re);
    scanf("%d", &option);
    {
        switch(option)
        {
            case 1:
                {
name:
                    printf(C "Enter the Name to search: " Re);
                    scanf(" %[^\n]", str);
                    if(!validate_name(str))
                    {
                        if(re_enter("Name"))
                            goto name;
                        else
                            return -1;
                    }
                    else
                    {
                        while(i < add->count)
                        {
                            if(!my_strcmp(add->details[i].name, str))
                            {
                                pos[j++] = i + '0';
                                pos[j] = '\0';
                            }
                            i++;
                        }
                    }
                    break;
                }
            case 2:
                {
num:
                    printf(C "Enter the Phone Number to search: " Re);
                    scanf(" %[^\n]", str);
                    if(!validate_num(str))
                    {
                        if(re_enter("Phone Number"))
                            goto num;
                        else
                            return -1;
                    }
                    else
                    {
                        while(i < add->count)
                        {
                            if(!my_strcmp(add->details[i].num, str))
                            {
                                pos[j++] = i + '0';
                                pos[j] = '\0';
                                break;
                            }
                            i++;
                        }
                    }
                    break;
                }
            case 3:
                {
id:
                    printf(C "Enter the Email ID to search: " Re);
                    scanf(" %[^\n]", str);
                    if(!validate_id(str))
                    {
                        if(re_enter("Email ID"))
                            goto id;
                        else
                            return -1;
                    }
                    else
                    {
                        while(i < add->count)
                        {
                            if(!my_strcmp(add->details[i].id, str))
                            {
                                pos[j++] = i + '0';
                                pos[j] = '\0';
                                break;
                            }
                            i++;
                        }
                    }
                    break;
                }
            case 4:
                return -2;
            default:
                {
                    puts(R "Invalid Input!!" Re);
                    goto option;
                }
        }
    }

    if(pos[0] == '\0')
        return -1;
    else if(pos[1] == '\0')
    {
        *ptr = 1;
        i = pos[0] - '0';
        printf("+------------------------+------------------+--------------------------+\n");
        printf("!         " C "Name" Re "           !   " C "Phone Number" Re "   !          " C "Email ID" Re "        !\n");
        printf("+------------------------+------------------+--------------------------+\n");
        print_contact(add, i, 0);
        return pos[0] - '0';
    }
    else
    {
        printf("+------------------------+------------------+--------------------------+\n");
        printf("!         " C "Name" Re "           !   " C "Phone Number" Re "   !          " C "Email ID" Re "        !\n");
        printf("+------------------------+------------------+--------------------------+\n");
        for(int k=0; pos[k]; k++)
        {
            i = pos[k] - '0';
            print_contact(add, i, k);
        }
pos:
        int val;
        printf(C "Multiple contacts found!!\n" Re "\tSelect one contact: ");
        scanf(" %d", &val);
        for(int k=0; pos[k]; k++)
            if(val == k+1)
                return pos[k] - '0';
        puts(R "Invalid entry!!" Re);
        goto pos;
    }
    return -1;
}

int edit_contact(book *add)
{
    printf(C "Enter contact to " Re);
    int i = search_contacts(add, &i), option;
    char str[50], val;

    if(i >= 0)
    {
option:
        printf(C "Edit Contact menu:\n" Re "\t1.Name\n\t2.Mobile number\n\t3.Mail ID\n\t4.Exit\n" C "Enter the option: " Re);
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                {
name:
                    printf(C "Enter the Name to edit: " Re);
                    scanf(" %[^\n]", str);
                    if(!validate_name(str))
                    {

                        if(re_enter("Name"))
                            goto name;
                        else
                            return 0;
                    }
                    strcpy(add->details[i].name, str);
                    break;
                }
            case 2:
                {
num:
                    printf(C "Enter the Phone Number to edit: " Re);
                    scanf(" %[^\n]", str);
                    if(!validate_num(str))
                    {
try_num:
                        if(re_enter("Phone Number"))
                            goto num;
                        else
                            return 0;
                    }
                    else
                    {
                        for(int j=0; j<add->count; j++)
                            if(!strcmp(add->details[j].num, str))
                            {
                                puts(R "ERROR! Entered Phone Number already exist!!" Re);
                                goto try_num;
                            }
                    }
                    strcpy(add->details[i].num, str);
                    break;
                }
            case 3:
                {
id:
                    printf(C "Enter the Email ID to edit: " Re);
                    scanf(" %[^\n]", str);
                    if(!validate_id(str))
                    {
try_id:
                        if(re_enter(""))
                            goto id;
                        else
                            return 0;
                    }
                    else
                    {
                        for(int j=0; j<add->count; j++)
                            if(!my_strcmp(add->details[j].id, str))
                            {
                                puts(R "ERROR! Entered Email ID already exist!!" Re);
                                goto try_id;
                            }
                    }
                    strcpy(add->details[i].id, str);
                    break;
                }
            case 4:
                return 0;
            default:
                {
                    puts(R "Invalid input!!" Re);
                    goto option;
                }
        }
    }
    else if(i == -1)
    {
        puts(R "Contacts not found!!" Re);
        return -1;
    }
    else if(i == -2)
        return -1;
    return 1;
}

int delete_contact(book *add)
{
    printf(C "Enter contact to " Re);
    int i = search_contacts(add, &i);
    char option;

    if(i >= 0)
    {
option:
        printf(C "Do you want to delete this contact ?\n" Re "\tPress Y to delete\n\tPress N to cancel\nEnter: ");
        scanf(" %c", &option);
        if(option == 'Y' || option == 'y')
        {
            for(int j=i; j<add->count; j++)
            {
                strcpy(add->details[j].name, add->details[j+1].name);
                strcpy(add->details[j].num, add->details[j+1].num);
                strcpy(add->details[j].id, add->details[j+1].id);
            }
            add->count--;
            return 1;
        }
        else if(option == 'N' || option == 'n')
            return 0;
        else
        {
            puts(R "Invalid option!!" Re);
            goto option;
        }

    }
    else if(i == -1)
    {
        puts(R "Contacts not found!!" Re);
        return -1;
    }
    else if(i == -2)
        return -1;
    return 0;
}

int sort_disp(book *add)
{
    if(add->count == 0)
    {
        puts(R "No contact to sort!!" Re);
        return 0;
    }
    int option;
option:
    printf(C "Do you want to sort\n" Re "\t1.By name\n\t2.By mobile number\n\t3.Exit\n" C "Enter the option: " Re);
    scanf("%d", &option);
    switch(option)
    {
        case 1:
            {
                sort_name(add);
                break;
            }
        case 2:
            {
                sort_num(add);
                break;
            }
        case 3:
            return 0;
        default:
            {
                puts(R "Invalid input!!" Re);
                goto option;
            }
    }
    return 1;
}

void sort_name(book *add)
{
    for(int i=0; i<add->count-1; i++)
    {
        for(int j=0; j<add->count-i-1; j++)
        {
            if(my_strcmp(add->details[j].name, add->details[j+1].name) > 0)
            {
                add->temp = add->details[j];
                add->details[j] = add->details[j+1];
                add->details[j+1] = add->temp;
            }
        }
    }
}

void sort_num(book *add)
{
    for(int i=0; i<add->count-1; i++)
    {
        for(int j=0; j<add->count-i-1; j++)
        {
            if(my_strcmp(add->details[j].num, add->details[j+1].num) > 0)
            {
                add->temp = add->details[j];
                add->details[j] = add->details[j+1];
                add->details[j+1] = add->temp;
            }
        }
    }
}

int validate_name(char name[])
{
    if(name[0] >= 0x30 && name[0] <= 0x39)
    {
        puts(R "ERROR! Name should not be numbers!!" Re);
        return 0;
    }
    return 1;
}

int validate_num(char num[])
{
    for(int i=0; num[i]; i++)
        if(!(num[i] >= 0x30 && num[i] <= 0x39))
        {
            puts(R "ERROR! Entered Phone Numbers should be only numbers!!" Re);
            return 0;
        }

    if(strlen(num) != 10)
    {
        puts(R "ERROR! Phone Number should be 10 digits!!" Re);
        return 0;
    }
    else if(num[0] < '6')
    {
        puts(R "ERROR! Phone Numbers should start between 6 to 9" Re);
        return 0;
    }
    return 1;
}

int validate_id(char id[])
{
    char cp_id[50], *token;
    int flag1 = 0, flag2 = 0, count = 0, i;

    for(i=0; id[i]; i++)
    {
        if(id[0] == '@' || id[0] == '.')
        {
            printf(R "ERROR! Email ID should not start at %c\n", id[0]);
            printf("%c !!\n", id[0]);
            return 0;
        }
        if(id[i] == '@')
            flag1++;
        if(id[i] == '.')
            flag2++;
    }

    if(flag2 > 1)
    {
        puts(R "ERROR! Email ID should contain only one .!!" Re);
        return 0;
    }
    if(flag1 > 1)
    {
        puts(R "ERROR! Email ID should contain only one @!!" Re);
        return 0;
    }  
    if(flag1 == 0)
    {
        puts(R "ERROR! Email ID should contain @!!" Re);
        return 0;
    }
    if(!((token = my_strstr(id, ".com", &count)) || (token = my_strstr(id, ".in", &count)) || (token = my_strstr(id, ".net", &count))))
    {
        puts(R "ERROR! Email should contain Top-Level domain!!" Re);
        return 0;
    }
    else
    {
        if(!count)
        {
            puts(R "ERROR! Top-Level domain is misplaced!!" Re);
            return 0;
        }
        if(token[-1] == '@')
        {
            puts(R "ERROR! Domain name should be prsent!!" Re);
            return 0;
        }
    }

    token = strtok((strcpy(cp_id, id)), "@");
    for(i=0; token[i]; i++)
        if(token[i] >= 'A' && token[i] <= 'Z')
        {
            puts(R "ERROR! Email ID should not contain uppercase!!" Re);
            return 0;
        }

    token = strtok(NULL, ".");
    for(i=0; token[i]; i++)
        if(!((token[i] >= 'a' && token[i] <= 'z') || (token[i] >= 'A' && token[i] <= 'Z')))
        {
            puts(R "ERROR! Invalid domain name in Email ID!!" Re);
            return 0;
        }
    return 1;
}

char *my_strstr(char str1[], char str2[], int *count)
{
    int flag;
    for(int i=0; str1[i]; i++)
    {
        flag = 1;
        for(int j=0; str2[j]; j++)
        {
            if(str1[i+j] != str2[j])
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            if(i == strlen(str1)-strlen(str2))
                *count = 1;
            return str1+i;
        }
    }
    return NULL;
}

int my_strcmp(char str1[], char str2[])
{
    char str3[30], str4[30];
    strcpy(str3, str1);
    strcpy(str4, str2);
    for(int i=0; str3[i] || str4[i]; i++)
    {
        if(str3[i] >= 'A' && str3[i] <= 'Z' && str3[i])
            str3[i] += 32;
        if(str4[i] >= 'A' && str4[i] <= 'Z' && str4[i])
            str4[i] += 32;
    }
    for(int i=0; str3[i] || str4[i]; i++)
    {
        if(str3[i] != str4[i])
            return str3[i] - str4[i];
    }
    return 0;
}

int re_enter(char *str)
{ 
    char val;

try_again:
    printf(C "Do you want to re-enter the %s\n" Re "\tPress Y to re-enter\n\tPress N to exit\nEnter: ", str);
    scanf(" %c", &val);
    if(val == 'Y' || val == 'y')
        return 1;
    else if(val == 'N' || val == 'n')
        return 0;
    else
    {
        puts(R "Invalid input!!" Re);
        goto try_again;
    }
}

void print_contact(book *add, int i, int k)
{
    printf("!%d.%-22s!%-18s!%-26s!\n",
            k+1,
            add->details[i].name,
            add->details[i].num,
            add->details[i].id);
    printf("+------------------------+------------------+--------------------------+\n");
}

void save(book *add)
{
    FILE *fp = fopen("contact.csv", "w");
    if(!fp)
    {
        puts(R "Error while opening file in load" Re);
        return;
    }
    fprintf(fp, "#%d\n", add->count);
    for(int i=0; i<add->count; i++)
        fprintf(fp, "%s,%s,%s\n", add->details[i].name, add->details[i].num, add->details[i].id);
    fclose(fp);
}
