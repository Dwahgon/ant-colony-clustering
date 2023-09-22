#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grid.h"

typedef struct gi_list
{
    GridItem *gi;
    struct gi_list *next;
} GridItemList;

void gilist_push(GridItemList **l, GridItem *gi)
{
    GridItemList *tmp;
    GridItemList *item = (GridItemList *)malloc(sizeof(GridItemList));
    item->gi = gi;
    item->next = NULL;

    if (!(*l))
    {
        *l = item;
    }
    else
    {
        for (tmp = *l; tmp->next; tmp = tmp->next)
            ;
        tmp->next = item;
    }
}

void gilist_free(GridItemList **l)
{
    GridItemList *tmp;
    while (l)
    {
        tmp = (*l)->next;
        free(l);
    }
    *l = NULL;
}

GridItem **gilist_to_array(GridItemList *l, int *cont)
{
    GridItemList *p_l;
    GridItem **res;
    int i;
    *cont = 0;
    for (p_l = l; p_l; p_l = p_l->next)
        (*cont)++;
    res = (GridItem **)calloc(*cont, sizeof(GridItem *));
    p_l = l;
    for (i = 0; i < *cont; i++)
    {
        res[i] = p_l->gi;
        p_l = p_l->next;
    }
    return res;
}

GridItem **parse_file(char *file_path, int data_dimensions, int *n_items)
{
    char buf[100], *s;
    int i, n, err;
    FILE *p_file;
    GridItemList *list = NULL;
    GridItem *gi = NULL;

    p_file = fopen(file_path, "r");
    if (p_file == NULL)
    {
        printf("Could not open file %s\n", file_path);
        exit(1);
    }
    while (fgets(buf, 100, p_file))
    {
        if (strchr(buf, '#'))
            continue;
        if (!gi)
        {
            gi = (GridItem *)malloc(sizeof(GridItem));
            gi_init(gi, data_dimensions);
        };

        s = buf;
        for (i = 0; i < data_dimensions; i++)
        {
            err = sscanf(s, "%lf %n", &gi->X[i], &n);
            if (err == -1)
                break;
            s += n;
        }
        if (err != -1)
        {
            err = sscanf(s, "%d", &gi->y);
            if (err == -1)
                continue;
            gilist_push(&list, gi);
            gi = NULL;
        }
    }
    fclose(p_file);
    return gilist_to_array(list, n_items);
}