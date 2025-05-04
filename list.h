// taken from the wayland-util.h
#pragma once

#include <stddef.h>

struct list {
    struct list *prev;
    struct list *next;
};

void
list_init(struct list *list);

void
list_insert(struct list *list, struct list *elm);

void
list_remove(struct list *elm);

int
list_length(const struct list *list);

int
list_empty(const struct list *list);

#define container_of(ptr, sample, member) (void *)((char *)(ptr) - ((char *)&(sample)->member - (char *)(sample)))

#define list_for_each(pos, head, member)                                                \
    for(pos = 0, pos = container_of((head)->next, pos, member); &pos->member != (head); \
            pos = container_of(pos->member.next, pos, member))

#define list_for_each_safe(pos, tmp, head, member)                       \
    for(pos = 0, tmp = 0, pos = container_of((head)->next, pos, member), \
    tmp = container_of((pos)->member.next, tmp, member);                 \
            &pos->member != (head); pos = tmp, tmp = container_of(pos->member.next, tmp, member))

#ifdef LIST_IMPLEMENTATION

void
list_init(struct list *list) {
    list->prev = list;
    list->next = list;
}

void
list_insert(struct list *list, struct list *elm) {
    elm->prev = list;
    elm->next = list->next;
    list->next = elm;
    elm->next->prev = elm;
}

void
list_remove(struct list *elm) {
    elm->prev->next = elm->next;
    elm->next->prev = elm->prev;
    elm->next = NULL;
    elm->prev = NULL;
}

int
list_length(const struct list *list) {
    struct list *e;
    int count;

    count = 0;
    e = list->next;
    while(e != list) {
        e = e->next;
        count++;
    }

    return count;
}

int
list_empty(const struct list *list) {
    return list->next == list;
}

#endif
