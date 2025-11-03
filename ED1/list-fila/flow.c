#include "flow.h"

void multiplex_flows(void) {
    Queue f1 = create_queue(), f2 = create_queue(), f3 = create_queue();

    printf("Enter values for Flow 1 (-1 to stop):\n");
    int val;
    while ((val = get_int("Value: ")) != -1) {
        add(&f1, val);
    }

    printf("Enter values for Flow 2 (-1 to stop):\n");
    while ((val = get_int("Value: ")) != -1) {
        add(&f2, val);
    }

    printf("Enter values for Flow 3 (-1 to stop):\n");
    while ((val = get_int("Value: ")) != -1) {
        add(&f3, val);
    }

    printf("\nFlow 1: ");
    print_queue(&f1);
    printf("Flow 2: ");
    print_queue(&f2);
    printf("Flow 3: ");
    print_queue(&f3);

    Queue channel = create_queue();
    Queue flow_ids = create_queue();

    if (!is_queue_empty(&f1)) {
        add(&flow_ids, 1);
    }
    if (!is_queue_empty(&f2)) {
        add(&flow_ids, 2);
    }
    if (!is_queue_empty(&f3)) {
        add(&flow_ids, 3);
    }

    while (!is_queue_empty(&flow_ids)) {
        int fid = remove_queue(&flow_ids);
        Queue *flow = (fid == 1) ? &f1 : (fid == 2) ? &f2 : &f3;
        if (!is_queue_empty(flow)) {
            int data = remove_queue(flow);
            add(&channel, data);
            add(&channel, fid);
            if (!is_queue_empty(flow)) {
                add(&flow_ids, fid);
            }
        }
    }

    printf("\nChannel (value, flow_id):\n");
    Queue temp = clone_queue(&channel);
    while (!is_queue_empty(&temp)) {
        int v = remove_queue(&temp);
        int id = remove_queue(&temp);
        printf("(%d, %d) ", v, id);
    }
    printf("\n");

    free_queue(&f1);
    free_queue(&f2);
    free_queue(&f3);
    free_queue(&channel);
    free_queue(&flow_ids);
    free_queue(&temp);
}

void demultiplex_flow(void) {
    Queue channel = create_queue();
    printf("Enter pairs (id value), id=-1 to stop:\n");
    int id, value;
    while (1) {
        id = get_int("ID: ");
        if (id == -1) {
            break;
        }
        value = get_int("Value: ");
        add(&channel, value);
        add(&channel, id);
    }

    printf("\nChannel content:\n");
    Queue temp = clone_queue(&channel);
    while (!is_queue_empty(&temp)) {
        int v = remove_queue(&temp);
        int i = remove_queue(&temp);
        printf("(%d, %d) ", v, i);
    }
    printf("\n");
    free_queue(&temp);

    Queue dest1 = create_queue(), dest2 = create_queue(),
          dest3 = create_queue();

    while (!is_queue_empty(&channel)) {
        int v = remove_queue(&channel);
        int i = remove_queue(&channel);
        if (i == 1) {
            add(&dest1, v);
        } else if (i == 2) {
            add(&dest2, v);
        } else if (i == 3) {
            add(&dest3, v);
        }
    }

    printf("Flow 1: ");
    print_queue(&dest1);
    printf("Flow 2: ");
    print_queue(&dest2);
    printf("Flow 3: ");
    print_queue(&dest3);

    free_queue(&dest1);
    free_queue(&dest2);
    free_queue(&dest3);
    free_queue(&channel);
}