#include <assert.h>
#include "student.h"

int student_compare(struct ll_node *student_one, struct ll_node *student_two) {
    double result = LL_ENTRY(student_one, struct student, node)->gpa - LL_ENTRY(student_two, struct student, node)->gpa;
    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    } else {
        return 0;
    }
}

struct student *student_worst_performer(struct student *list) {
    assert(list != NULL);
    struct ll_node *worst = ll_min(&(list->node), student_compare);

    // Be careful of return type. This is how to get the student pointer from an ll_node (function is basically saying, i have this pointer 
    // to a "node" and I want the pointer to a struct student that has this node as one of its fields)
    return LL_ENTRY(worst, struct student, node);
}

struct student *student_valedictorian(struct student *list) {
    assert(list != NULL);
    struct ll_node *best = ll_max(&(list->node), student_compare);
    return LL_ENTRY(best, struct student, node);
}

bool student_identify_honour_roll(struct ll_node *node) {
    if (LL_ENTRY(node, struct student, node)->gpa >= 3.50) {
        return false;
    }
    return true;
}

struct student *student_honour_roll(struct student *list) {
    assert(list != NULL);
    struct ll_node *honor_roll = ll_filter(&(list->node), student_identify_honour_roll);

    // Be careful to return NULL if needed instead of trying to find the student pointer for the node
    if (honor_roll == NULL) {
        return NULL;
    }
    return LL_ENTRY(honor_roll, struct student, node);
}
