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

static ufsm_ret _state_0_recv_event_1_handle(struct ufsm *cb, ufsm_event event, void *data)
{
    printf("%s event:0x%x %p\n", __func__, event, data);
    return UFSM_OK;
}

static ufsm_ret _state_1_recv_event_0_handle(struct ufsm *cb, ufsm_event event, void *data)
{
    printf("%s event:0x%x %p\n", __func__, event, data);
    return UFSM_OK;
}

static void ufsm_exit_handle(struct ufsm *cb, ufsm_state state)
{
    printf("%s state:0x%x\n", __func__, state);
}

static struct ufsm_table table[] = {
    {STATE_0, EVENT_1, _state_0_recv_event_1_handle, STATE_1},
    {STATE_1, EVENT_0, _state_1_recv_event_0_handle, STATE_0},
};

struct ufsm cb;

int main(int argc, char const *argv[])
{
    uint32_t ret;

    ret = ufsm_init(&cb, table, sizeof(table)/sizeof(table[0]), STATE_0, ufsm_exit_handle);
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

    ufsm_exit(&cb);

    return 0;
}
