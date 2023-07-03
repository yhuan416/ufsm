#include "ufsm.h"

uint32_t ufsm_init(struct ufsm *cb, struct ufsm_table *table, uint32_t table_size, uint32_t init_state)
{
    cb->table = table;
    cb->table_size = table_size;
    cb->state = init_state;
    return UFSM_OK;
}

uint32_t ufsm_recv(struct ufsm *cb, uint32_t event, void *data)
{
    ufsm_func func = NULL;

    for (uint32_t i = 0; i < cb->table_size; i++)
    {
        if (cb->table[i].state == cb->state && cb->table[i].event == event)
        {
            func = cb->table[i].func;
            break;
        }
    }

    if (func == NULL)
    {
        return UFSM_FAIL;
    }

    cb->state = func(cb, event, data);

    return UFSM_OK;
}

uint32_t ufsm_get_state(struct ufsm *cb)
{
    return cb->state;
}

void ufsm_set_data(struct ufsm *cb, void *data)
{
    cb->data = data;
}

void *ufsm_get_data(struct ufsm *cb)
{
    return cb->data;
}
