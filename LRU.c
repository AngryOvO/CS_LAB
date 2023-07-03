#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int vpn;
    struct node* llink;
    struct node* rlink;
        
} listnode;

int deleteFirst(listnode* h)
{
    if(h->rlink == NULL)
    {
        return 0;
    }

    listnode* n = h->rlink;
    h->rlink = n->rlink;
    n->rlink->llink = h;
    free(n);

    return 1;
}

int deleteLast(listnode* h)
{
    if(h->rlink == NULL)
    {
        return 0;
    }

    listnode* n = h->rlink;
    listnode* tail = NULL;

    if(n->rlink == NULL)
    {
        h->rlink = NULL;
        free(n);
    }

    while(n->rlink != NULL)
    {
        tail = n;
        n = n->rlink;
    }

    tail->rlink = NULL;
    free(n);

    return 1;
}

int deleteNode(listnode* h, int num)
{
    if(h->rlink == NULL)
    {
        return 0;
    }
    
    listnode* n = h->rlink;

    while(n!= NULL)
    {
        if(n->vpn == num)
        {
            if(n == h->rlink)
            {
                deleteFirst(h);
            }
            else if(n->rlink == NULL)
            {
                deleteLast(h);
            }
            else
            {
                n->llink->rlink = n->rlink;
                n->rlink->llink = n->llink;
                free(n);
            }

            return 1;
        }
        n = n->rlink;
    }

    return 0;
}

int main(void)
{
    int size;
    int count_acc = 0;
    int count_read = 0;
    int count_write = 0;
    int count_hits = 0;
    int count_faults = 0;
    scanf("%d", &size);
    
    FILE* accesslist = fopen("access.list", "r");
    if (accesslist == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1; // 에러 처리
    }

    listnode* head = (listnode*)malloc(sizeof(listnode));
    head->vpn = -1;
    head->llink = NULL;
    head->rlink = NULL;
    
    int num;
    char type[10]; // 문자열 저장을 위한 배열
    while (fscanf(accesslist, "%d %s", &num, type) != EOF)
    {
        count_acc++;
        if (strcmp(type, "read") == 0)
        {
            count_read++;
        }
        else if (strcmp(type, "write") == 0)
        {
            count_write++;
        }

        listnode* newnode = (listnode*)malloc(sizeof(listnode));
        newnode->vpn = num;
        newnode->llink = NULL;
        newnode->rlink = NULL;

        int listsize = 0;
        listnode* tail = head;
        while(tail->rlink != NULL)
        {
            tail = tail->rlink;
            listsize++;
        }

        listnode* n = head;

        int checkhit = 0;

        while(n->rlink != NULL)
        {
            if(n->vpn == num)
            {
                count_hits++;
                checkhit = 1;
                deleteNode(head, num);
                tail->rlink = newnode;
                newnode->llink = tail;
                tail = newnode;
            }
            n = n->rlink;
        }

        if(checkhit == 0)
        {
            count_faults++;
            if(listsize < size)
            {
                tail->rlink = newnode;
                newnode->llink = tail;
                tail = newnode;
            }
            else
            {
                deleteFirst(head);
                tail->rlink = newnode;
                newnode->llink = tail;
                tail = newnode;
            }

        }
    }

    printf("Total number of access: %d\n", count_acc);
    printf("Total number of read: %d\n", count_read);
    printf("Total number of write: %d\n", count_write);
    printf("Number of page hits: %d\n", count_hits);
    printf("Number of page faults: %d\n", count_faults);
    printf("Page fault rate: %d/%d = %.3f %%\n", count_faults, count_acc, (double)count_faults/count_acc*100);

    fclose(accesslist);

    listnode* n = head;
    while(n->rlink != NULL)
    {
        listnode* temp = n;
        n = n->rlink;
        free(temp);
    }
    free(n);

    return 0;
}

