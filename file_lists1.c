#include "shell.h"

/**
 * Add a node to the beginning of the linked list.
 *
 * @param head - Address of the pointer to the head node.
 * @param str - String field of the new node.
 * @param num - Node index used by history.
 * @return - Pointer to the new node.
 */
list_t *addNode(list_t **head, const char *str, int num)
{
    list_t *newHead;

    if (!head)
        return (NULL);

    newHead = allocateMemory(sizeof(list_t));

    if (!newHead)
        return (NULL);

    memsetMemory((void *)newHead, 0, sizeof(list_t));
    newHead->num = num;

    if (str)
    {
        newHead->str = duplicateString(str);

        if (!newHead->str)
        {
            freeMemory(newHead);
            return (NULL);
        }
    }

    newHead->next = *head;
    *head = newHead;
    return (newHead);
}

/**
 * Add a node to the end of the linked list.
 *
 * @param head - Address of the pointer to the head node.
 * @param str - String field of the new node.
 * @param num - Node index used by history.
 * @return - Pointer to the new node.
 */
list_t *addNodeEnd(list_t **head, const char *str, int num)
{
    list_t *newNode, *node;

    if (!head)
        return (NULL);

    node = *head;
    newNode = allocateMemory(sizeof(list_t));

    if (!newNode)
        return (NULL);

    memsetMemory((void *)newNode, 0, sizeof(list_t));
    newNode->num = num;

    if (str)
    {
        newNode->str = duplicateString(str);

        if (!newNode->str)
        {
            freeMemory(newNode);
            return (NULL);
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;

        node->next = newNode;
    }
    else
    {
        *head = newNode;
    }

    return (newNode);
}

/**
 * Print only the "str" element of a linked list.
 *
 * @param h - Pointer to the first node.
 * @return - Size of the list.
 */
size_t printListStr(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        writeString(h->str ? h->str : "(nil)");
        writeChar('\n');
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * Delete a node at the given index.
 *
 * @param head - Address of the pointer to the first node.
 * @param index - Index of the node to delete.
 * @return - 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    list_t *node, *prevNode;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        freeMemory(node->str);
        freeMemory(node);
        return (1);
    }

    node = *head;

    while (node)
    {
        if (i == index)
        {
            prevNode->next = node->next;
            freeMemory(node->str);
            freeMemory(node);
            return (1);
        }

        i++;
        prevNode = node;
        node = node->next;
    }

    return (0);
}

/**
 * Free all nodes of a linked list.
 *
 * @param headPtr - Address of the pointer to the head node.
 * @return - void
 */
void freeList(list_t **headPtr)
{
    list_t *node, *nextNode, *head;

    if (!headPtr || !*headPtr)
        return;

    head = *headPtr;
    node = head;

    while (node)
    {
        nextNode = node->next;
        freeMemory(node->str);
        freeMemory(node);
        node = nextNode;
    }

    *headPtr = NULL;
}
