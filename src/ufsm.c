#include "ufsm.h"

static ufsm_func _ufsm_get_func(struct ufsm_table *table, uint32_t table_size, ufsm_state state, ufsm_event event)
{
    uint32_t i = 0;
    ufsm_func func = NULL;

    for (i = 0; i < table_size; i++)
    {
        if (table[i].state == state && table[i].event == event)
        {
            func = table[i].func;
            break;
        }
    }

    return func;
}

ufsm_ret ufsm_init(struct ufsm *cb, struct ufsm_table *table, uint32_t table_size, ufsm_state init_state)
{
    cb->table = table;
    cb->table_size = table_size;
    cb->state = init_state;
    return UFSM_OK;
}

ufsm_ret ufsm_recv(struct ufsm *cb, ufsm_event event, void *data)
{
    ufsm_func func = NULL;

    func = _ufsm_get_func(cb->table, cb->table_size, cb->state, event);
    if (func == NULL)
    {
        return UFSM_FAIL;
    }

    cb->state = func(cb, event, data);

    return UFSM_OK;
}

ufsm_state ufsm_get_state(struct ufsm *cb)
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
