#include <stdio.h>

struct food {
    int quantity;
    float price;
};

int main() {
    struct food porota, veg, water;
    int people;
    float total;
    //porota
    printf("Quantity Of Porota: ");
    scanf("%d", &porota.quantity);
    printf("Unit of price: ");
    scanf("%f", &porota.price);
    
    //veg
    printf("Quantity Of Vegetable: ");
    scanf("%d", &veg.quantity);
    printf("Unit of price: ");
    scanf("%f", &veg.price);
    
    //water
    printf("Quantity Of Mineral Water: ");
    scanf("%d", &water.quantity);
    printf("Unit of price: ");
    scanf("%f", &water.price);
    
    //Number of poeple   
    printf("Number of people: ");
    scanf("%d", &people);
   
    total = ((porota.quantity * porota.price) + (veg.quantity * veg.price) + (water.quantity * water.price)) / people;
    printf("Individual people will pay: %.2f tk", total);
    
    return 0;
}
