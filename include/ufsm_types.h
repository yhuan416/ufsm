#ifndef __UFSM_TYPES_H__
#define __UFSM_TYPES_H__

#include <stdint.h>

#define UFSM_OK         (0)
#define UFSM_FAIL       (-1)

typedef uint32_t ufsm_ret;

/**
 * @brief 状态机状态
*/
typedef uint32_t ufsm_state;

/**
 * @brief 状态机事件
*/
typedef uint32_t ufsm_event;

#endif // !__UFSM_TYPES_H__