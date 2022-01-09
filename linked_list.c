#include <assert.h>
#include "linked_list.h"

void ll_init(struct ll_node *node) {
    assert(node != NULL);
    node->next = NULL;
    node->prev = NULL;
}

bool ll_has_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next != NULL;
}

bool ll_has_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev != NULL;

}

struct ll_node *ll_next(struct ll_node *node) {
    assert(node != NULL);
    return node->next;
}

struct ll_node *ll_prev(struct ll_node *node) {
    assert(node != NULL);
    return node->prev;
}

size_t ll_size(struct ll_node *head) {
    // Pass by value so address of pointer passed in is copied to the pointer head
    assert(head != NULL);
    size_t size = 0;
    while (head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

struct ll_node *ll_head(struct ll_node *list) {
    assert(list != NULL);
    while (list->prev != NULL) {
        list = list->prev;
    }
    return list;
}

struct ll_node *ll_tail(struct ll_node *list) {
    assert(list != NULL);
    while (list->next != NULL) {
        list = list->next;
    }
    return list;
}

struct ll_node *ll_get(struct ll_node *node, size_t index) {
    assert(node != NULL);
    size_t count = 0;
    while (node != NULL && count != index) {
        node = node->next;
        count++;
    }
    return node;
}

static void ll_insert_first_help(struct ll_node *new, struct ll_node *first) {
    first->prev = new;
    new->next = first;
    new->prev = NULL;
}

void ll_insert_before(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    if (existing->prev == NULL) {
        ll_insert_first_help(new, existing);
    } else {
        existing->prev->next = new;
        new->prev = existing->prev;
        new->next = existing;
        existing->prev = new;
    }
}

static void ll_insert_last_help(struct ll_node *new, struct ll_node *last) {
    last->next = new;
    new->prev = last;
    new->next = NULL;
}

void ll_insert_after(struct ll_node *new, struct ll_node *existing) {
    assert(new != NULL);
    assert(existing != NULL);
    if (existing->next == NULL) {
        ll_insert_last_help(new, existing);
    } else {
        existing->next->prev = new;
        new->next = existing->next;
        existing->next = new;
        new->prev = existing;
    }
}

void ll_insert_first(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    list = ll_head(list);
    ll_insert_first_help(new, list);
}

void ll_insert_last(struct ll_node *new, struct ll_node *list) {
    assert(new != NULL);
    assert(list != NULL);
    list = ll_tail(list);
    ll_insert_last_help(new, list);
}

void ll_remove(struct ll_node *node) {
    assert(node != NULL);
    if (!(node->next == NULL && node->prev == NULL)) {
        if (node->next == NULL) {
            node->prev->next = NULL;
        } else if (node->prev == NULL) {
            node->next->prev = NULL;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
}

struct ll_node *ll_min(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    struct ll_node *min = list;
    list = list->next;
    while (list != NULL) {
        int compare = comparator(list, min);
        if (compare < 0) {
            min = list;
        }
        list = list->next;
    }
    return min;
}

struct ll_node *ll_max(struct ll_node *list, ll_comparator_t comparator) {
    assert(list != NULL);
    assert(comparator != NULL);
    struct ll_node *max = list;
    list = list->next;
    while (list != NULL) {
        int compare = comparator(list, max);
        if (compare > 0) {
            max = list;
        }
        list = list->next;
    }
    return max;
}

struct ll_node *ll_filter(struct ll_node *list, ll_predicate_t predicate) {
    assert(list != NULL);
    assert(predicate != NULL);
    struct ll_node *temp;
    size_t removed = 0;
    size_t total = 0;
    while (list != NULL) {
        if (predicate(list)) {
            removed++;
            ll_remove(list);
        }
        total++;
        temp = list;
        list = list->next;
    }
    if (removed == total) {
        return NULL;
    } else {
        return ll_head(temp);
    }
}
