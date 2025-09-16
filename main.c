#include <stdio.h>
#include "contact.h"
/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    char option; 
    int val;
    book add;

    init_intitalization(&add);

    while (1)
    {
        puts("+----------------------------------------------------------------------+");
        printf(C "Address book menu\n" Re); /* Give a prompt message for a user */
        printf("1.Add contact\n2.Edit contact\n3.Delete contact\n4.search contact\n5.Display contact\n6.Sort and Display\n7.Save and exit\n8.Exit\n");
        printf(C "Enter the option : " Re);
        scanf("%hhd", &option);

        switch(option) /* Based on choosed option */
        {
            case 1:
                {
                    if(create_contact(&add))
                        puts(G "Contact created!!" Re);
                    else
                        puts(R "Conatct not created!!" Re);
                    break;
                }
            case 2:
                {
                    if(edit_contact(&add) == 1)
                        puts(G "Contact edited!!" Re);
                    else
                        puts(R "Contact not edited!!" Re);
                    break;
                }
            case 3:
                {
                    if(delete_contact(&add) == 1)
                        puts(G "Contact deleted!!" Re);
                    else
                        puts(R "Contact not deleted!!" Re);
                    break;
                }
            case 4:
                {
                    int i = search_contacts(&add, &val);
                    if(i >= 0 & val != 1)
                    {
                        puts(G "Contact found!!" Re);
                        printf("+----------------------------------------------------------------------+\n");
                        print_contact(&add, i, 0);
                    }
                    else if(i == -1)
                        puts(R "Contact not found!!" Re);
                    break;
                }
            case 5:
                {
                    list_contacts(&add);
                    break;
                }
            case 6:
                {
                    if(sort_disp(&add))
                        list_contacts(&add);
                    else
                        puts(R "Contacts not sorted!!" Re);
                    break;
                }
            case 7:
                {
save:
                    //printf(G "Saving contacts\n" Re);
                    printf(G "INFO : Save and Exit...\n" Re);
                    save(&add);
                    return 0;
                }
            case 8:
                if(add.count)
                {
re_try:
                    printf(C "Do you want to save contacts:\n" Re "\tPress Y to save\n\tPress N to exit\nEnter: ");
                    scanf(" %c", &option);
                    if(option == 'Y' || option == 'y')
                        goto save;
                    else if(option == 'N' || option == 'n')
                        return 0;
                    puts(R "Invalid input" Re);
                    goto re_try;
                }
            default:
                printf(R "Invalid option \n" Re);
        }
    }
    return 0;
}


