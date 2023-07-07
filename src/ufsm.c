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

static struct ufsm_table *_ufsm_get_table(struct ufsm_table *table, uint32_t table_size, ufsm_state state, ufsm_event event)
{
    uint32_t i = 0;
    struct ufsm_table *t = NULL;

    for (i = 0; i < table_size; i++)
    {
        if (table[i].state == state && table[i].event == event)
        {
            t = &(table[i]);
            break;
        }
    }

    return t;
}

ufsm_ret ufsm_init(struct ufsm *cb, 
                    struct ufsm_table *table, 
                    uint32_t table_size, 
                    ufsm_state init_state,
                    ufsm_exit_cb exit)
{
    cb->table = table;
    cb->table_size = table_size;
    cb->state = init_state;

    cb->exit_flag = 0;
    cb->exit = exit;

    return UFSM_OK;
}

void ufsm_exit(struct ufsm *cb)
{
    cb->exit_flag = 1;

    if (cb->exit != NULL)
    {
        cb->exit(cb, cb->state);
    }
}

ufsm_ret ufsm_recv(struct ufsm *cb, ufsm_event event, void *data)
{
    ufsm_ret ret = 0;
    ufsm_state next_state = 0;
    struct ufsm_table *table = NULL;

    if (cb->exit_flag)
    {
        return UFSM_FAIL;
    }

    table = _ufsm_get_table(cb->table, cb->table_size, cb->state, event);
    if (table == NULL)
    {
        return UFSM_FAIL;
    }

    ret = table->func(cb, event, data);
    if (ret != UFSM_OK)
    {
        return UFSM_FAIL;
    }

    cb->state = table->next_state;

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
