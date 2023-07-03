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

static ufsm_state state_0(struct ufsm *cb, ufsm_event event, void *data)
{
    ufsm_state next_state = STATE_1;
    printf("%s event:0x%x %p\n", __func__, event, data);
    return next_state;
}

static ufsm_state state_1(struct ufsm *cb, ufsm_event event, void *data)
{
    ufsm_state next_state = STATE_0;
    printf("%s event:0x%x %p\n", __func__, event, data);
    return next_state;
}

static struct ufsm_table table[] = {
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
