/**
 * @file uart_loopback_config.h
 * @brief UART回环测试配置文件
 * @details 定义硬件回环开关、参数和Debug选项
 *
 * @copyright Copyright (c) 2025
 * @date 2025-03-10
 */

#ifndef UART_LOOPBACK_CONFIG_H
#define UART_LOOPBACK_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    /* ========================================================================
     * 1. 测试功能开关
     * ======================================================================== */

    /**
     * @brief 测试功能总开关
     * @note  推荐直接在本文件配置:
     *        1=编译并启用回环测试逻辑
     *        0=关闭回环测试,走正常AGV业务
     *        仍兼容工程编译宏覆盖
     */
#ifndef UART_LOOPBACK_TEST_ENABLE
#define UART_LOOPBACK_TEST_ENABLE 0
#endif

    /* ========================================================================
     * 2. 硬件回环开关
     * ======================================================================== */

    /**
     * @brief 硬件自收自发开关
     * @note  1=启用硬件回环测试(TX-RX短接), 0=禁用(走正常AGV业务发送)
     */
#define UART_LOOPBACK_HARDWARE_ENABLE 0

    /* ========================================================================
     * 3. Debug输出控制
     * ======================================================================== */

    /**
     * @brief 启用详细调试信息
     * @note  1=启用, 0=禁用
     */
#define UART_LOOPBACK_DEBUG_ENABLE 1

    /**
     * @brief 启用十六进制数据转储
     * @note  1=启用, 0=禁用
     */
#define UART_LOOPBACK_HEX_DUMP_ENABLE 1

    /**
     * @brief 显示解析后的数据结构
     * @note  1=启用, 0=禁用
     */
#define UART_LOOPBACK_SHOW_PARSED_DATA 1

    /* ========================================================================
     * 4. 测试参数配置
     * ======================================================================== */

    /**
     * @brief 接收缓冲区大小(字节)
     */
#define UART_LOOPBACK_RX_BUF_SIZE 512

    /**
     * @brief 测试间隔(毫秒)
     * @note  在主循环中两次测试之间的延时
     */
#define UART_LOOPBACK_TEST_INTERVAL_MS 5000

    /**
     * @brief 接收超时时间(毫秒)
     * @note  硬件回环模式下等待接收数据的超时时间
     */
#define UART_LOOPBACK_RX_TIMEOUT_MS 1000

    /* ========================================================================
     * 5. 测试数据配置
     * ======================================================================== */

    /**
     * @brief 测试用角度值(度)
     * @note  使用特殊值便于识别(12.34°而非0.0°)
     */
#define UART_LOOPBACK_TEST_ANGLE 12.34f

    /**
     * @brief 测试用PWM占空比(%)
     * @note  使用特殊值便于识别(56而非30)
     */
#define UART_LOOPBACK_TEST_PWM 56

    /**
     * @brief 测试用脉冲数
     */
#define UART_LOOPBACK_TEST_PULSES 1234

#ifdef __cplusplus
}
#endif

#endif /* UART_LOOPBACK_CONFIG_H */
