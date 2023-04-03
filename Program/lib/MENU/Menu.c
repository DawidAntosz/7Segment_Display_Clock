#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"

Menu *createMenu(char *title, int numItems, MenuItem *items){
    Menu *menu = (Menu *) malloc(sizeof(Menu));
    menu->title = (char *) malloc(strlen(title)+1);
    strcpy(menu->title, title);
    menu->numItems = numItems;
    menu->items = (MenuItem *) malloc(numItems * sizeof(MenuItem));

    for(int i=0; i < numItems; i++){
        menu->items[i].name = (char *) malloc(strlen(items[i].name) + 1);
        strcpy(menu->items[i].name, items[i].name);
        menu->items[i].action = items[i].action;
    }

    return menu;
}

void selectMenuItem(Menu *menu, int numItem){
    //print on uart - name - and data from action
    menu->items[numItem].action();
}

void freeMenu(Menu *menu){
    free(menu->title);
    for(int i=0; i < menu->numItems; i++){
        free(menu->items[i].name); // alokowane dynamicznie- wiec zwalniam pamięć.
    }// items.action - zawiera wskaźnik nie alokowany dynamicznie  -inicjalizacja przy tworzeniu
    free(menu->items);
    free(menu);
}