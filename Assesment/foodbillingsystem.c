#include <stdio.h>
#include <string.h>

 main() {
    int i,code, quantity, total = 0;
    char again;

    
    char items[4][20] = {"CheeseCake", "PinkSaucepasta", "borito", "ColdCoffee"};
    int prices[4] = {150, 100, 80, 50};

    
    printf("--------- Food Menu ---------\n");
    printf("Code\tItem\t\tPrice\n");
    
    for (i = 0; i < 4; i++) {
        printf("%d\t%-10s\tRs. %d\n", i + 1, items[i], prices[i]);
    }
    printf("-----------------------------\n");

    
    again = 'y';
    while (again == 'y' || again == 'Y') {
        printf("\nEnter the food code (1-4): ");
        scanf("%d", &code);

        if (code >= 1 && code <= 4) {
            printf("You selected: %s\n", items[code - 1]);
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            total += prices[code - 1] * quantity;
        } else {
            printf("Invalid code! Please select between 1 and 4.\n");
        }

        printf("Do you want to order more? (y/n): ");
        scanf(" %c", &again); 
    }

    
    printf("\n========= BILL =========\n");
    printf("Total Amount: Rs. %d\n", total);
    printf("Thanks for visiting!\n");

}

