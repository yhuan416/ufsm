#include "stdio.h"
#include "stdint.h"

#include "ufsm.h"

enum fsm_state {
    STATE_0 = 0,
    STATE_1,
    STATE_MAX
};

enum fsm_event {
    EVENT_0 = 0,
    EVENT_1,
    EVENT_MAX
};

uint32_t state_0(struct ufsm *cb, uint32_t event, void *data)
{
    uint32_t state = STATE_1;
    printf("state_0\n");
    return state;
}

uint32_t state_1(struct ufsm *cb, uint32_t event, void *data)
{
    uint32_t state = STATE_0;
    printf("state_1\n");
    return state;
}

struct ufsm_table table[] = {
    {STATE_0, EVENT_1, state_0},
    {STATE_1, EVENT_0, state_1},
};

struct ufsm cb;

int main(int argc, char const *argv[])
{
    uint32_t ret;

    ret = ufsm_init(&cb, table, sizeof(table)/sizeof(table[0]), STATE_0);
    if (ret != UFSM_OK)
    {
        printf("ufsm_init failed\n");
        return -1;
    }

    ret = ufsm_recv(&cb, EVENT_1, NULL);
    if (ret != UFSM_OK)
    {
        printf("ufsm_recv failed\n");
        return -1;
    }

    ret = ufsm_recv(&cb, EVENT_0, NULL);
    if (ret != UFSM_OK)
    {
        printf("ufsm_recv failed\n");
        return -1;
    }

    return 0;
}
