# ufsm
utils fsm

通用状态机

一个简单的状态转换器框架

通过配置状态迁移表以及钩子函数, 实现状态机的状态迁移

## 1. 状态机的状态定义

``` c
enum fsm_state {
    STATE_0 = 0,
    STATE_1,
    STATE_MAX
};
```

## 2. 状态机的事件定义

``` c
enum fsm_event {
    EVENT_0 = 0,
    EVENT_1,
    EVENT_MAX
};
```

## 3. 状态机的状态迁移表定义

``` c
static struct ufsm_table table[] = {
    // 当前状态 接收事件 处理函数 下一个状态            执行成功后下一个状态
    {STATE_0, EVENT_1, _state_0_recv_event_1_handle, STATE_1},
    {STATE_1, EVENT_0, _state_1_recv_event_0_handle, STATE_0},
};
```

## 4. 实现相关钩子函数

``` c
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
```

## 状态机退出钩子函数(可选)

``` c
static void _state_exit_handle(struct ufsm *cb, ufsm_state state)
{
    printf("%s state:%d\n", __func__, state);
}
```

## 5. 初始化状态机

``` c
    struct ufsm cb;
    uint32_t ret = ufsm_init(&cb, table, sizeof(table)/sizeof(table[0]), STATE_0, ufsm_exit_handle);
    if (ret != UFSM_OK)
    {
        printf("ufsm_init failed\n");
        return -1;
    }
```

## 6. 发送事件

``` c
    ufsm_event_send(&cb, EVENT_1, NULL);
    ufsm_event_send(&cb, EVENT_0, NULL);
```

## 7. 状态机退出

``` c
    ufsm_exit(&cb);
```

## 8. 状态机状态查询

``` c
    ufsm_state state = ufsm_state_get(&cb);
    printf("state:0x%x\n", state);
```

## 后续计划

- [ ] 事件输入与状态迁移解耦, 输入的事件添加到队列中, 新增接口让状态机从队列中取出事件进行状态迁移

