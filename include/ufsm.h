#ifndef __UFSM_H__
#define __UFSM_H__

#include <stdio.h>
#include <stdint.h>

#include "ufsm_types.h"

struct ufsm;
struct ufsm_table;

/**
 * @brief 状态机处理函数
 * @param cb 控制块指针
 * @param event 输入的事件
 * @param data 输入的数据
 * @return ufsm_ret UFSM_OK 成功, 进行状态切换
 *                  other   失败, 不进行状态切换
*/
typedef ufsm_ret (*ufsm_func)(struct ufsm *cb, ufsm_event event, void *data);

/**
 * @brief 状态机结束状态处理函数
 * @param cb 控制块指针
 * @param state 结束时当前状态
*/
typedef void (*ufsm_exit_cb)(struct ufsm *cb, ufsm_state state);

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
    ufsm_state next_state; // 下一个状态
};

/**
 * @brief 状态机控制块
 * @param state 当前状态
 * @param table 状态变迁表
 * @param table_size 状态变迁表大小
 * @param exit 状态机结束状态处理函数
 * @param data 用户数据
*/
struct ufsm
{
    volatile ufsm_state state;
    struct ufsm_table *table;
    uint32_t table_size;
    uint32_t exit_flag;
    ufsm_exit_cb exit;
    void *data;
};

/**
 * @brief 状态机初始化
 * @param cb 控制块指针
 * @param table 状态变迁表
 * @param table_size 状态变迁表大小
 * @param init_state 初始状态
 * @param exit 状态机结束状态处理函数
 * @return ufsm_ret 返回0表示成功，返回-1表示失败
*/
ufsm_ret ufsm_init(struct ufsm *cb, struct ufsm_table *table, uint32_t table_size, ufsm_state init_state, ufsm_exit_cb exit);

/**
 * @brief 状态机退出
 * @param cb 控制块指针
*/
void ufsm_exit(struct ufsm *cb);

/**
 * @brief 状态机事件输入
 * @param cb 控制块指针
 * @param event 输入的事件
 * @param data 输入的数据
 * @return ufsm_ret 返回0表示成功，返回-1表示失败
*/
ufsm_ret ufsm_recv(struct ufsm *cb, ufsm_event event, void *data);

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