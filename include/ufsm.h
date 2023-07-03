#ifndef __UFSM_H__
#define __UFSM_H__

#include <stdio.h>
#include <stdint.h>

#define UFSM_OK         (0)
#define UFSM_FAIL       (-1)

struct ufsm;
struct ufsm_table;

/**
 * @brief 状态机状态
*/
typedef uint32_t ufsm_state;
typedef uint32_t ufsm_event;

/**
 * @brief 状态机处理函数
 * @param cb 控制块指针
 * @param event 输入的事件
 * @param data 输入的数据
 * @return ufsm_state 返回下一个状态
*/
typedef ufsm_state (*ufsm_func)(struct ufsm *cb, ufsm_event event, void *data);

/**
 * @brief 状态机状态变迁表
 * @param state 当前状态
 * @param event 输入的事件
 * @param func 处理函数
*/
struct ufsm_table
{
    ufsm_state state; // 当前状态
    ufsm_event event; // 输入的事件
    ufsm_func func; // 处理函数
};

/**
 * @brief 状态机控制块
 * @param state 当前状态
 * @param table 状态变迁表
 * @param table_size 状态变迁表大小
 * @param data 用户数据
*/
struct ufsm
{
    volatile ufsm_state state;
    struct ufsm_table *table;
    uint32_t table_size;
    void *data;
};

/**
 * @brief 状态机初始化
 * @param cb 控制块指针
 * @param table 状态变迁表
 * @param table_size 状态变迁表大小
 * @param init_state 初始状态
 * @return uint32_t 返回0表示成功，返回-1表示失败
*/
uint32_t ufsm_init(struct ufsm *cb, struct ufsm_table *table, uint32_t table_size, ufsm_state init_state);

/**
 * @brief 状态机事件输入
 * @param cb 控制块指针
 * @param event 输入的事件
 * @param data 输入的数据
 * @return ufsm_state 返回0表示成功，返回-1表示失败
*/
ufsm_state ufsm_recv(struct ufsm *cb, ufsm_event event, void *data);

/**
 * @brief 获取当前状态
 * @param cb 控制块指针
 * @return ufsm_state 返回当前状态
*/
ufsm_state ufsm_get_state(struct ufsm *cb);

/**
 * @brief 设置用户数据
 * @param cb 控制块指针
 * @param data 用户数据指针
*/
void ufsm_set_data(struct ufsm *cb, void *data);

/**
 * @brief 获取用户数据
 * @param cb 控制块指针
 * @return void* 返回用户数据指针
*/
void *ufsm_get_data(struct ufsm *cb);

#endif // !__UFSM_H__