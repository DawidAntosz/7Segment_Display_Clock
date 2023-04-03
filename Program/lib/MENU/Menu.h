#ifndef MENU_TEST_MENU_H
#define MENU_TEST_MENU_H

typedef struct MenuItem{
    char *name;
    void (*action)();
} MenuItem;

typedef struct Menu{
    char *title;
    int numItems;
    MenuItem  *items;
} Menu;

Menu *createMenu(char *title, int numItems, MenuItem *items);

void freeMenu(Menu *menu);
void selectMenuItem(Menu *menu, int numItem);

#endif //MENU_TEST_MENU_H
