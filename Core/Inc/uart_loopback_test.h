/**
 * @file uart_loopback_test.h
 * @brief UART回环测试模块头文件
 * @details 提供UART2自发自收测试功能,用于验证uart_frame协议和硬件收发
 *
 * @copyright Copyright (c) 2025
 * @date 2025-03-10
 */

#ifndef UART_LOOPBACK_TEST_H
#define UART_LOOPBACK_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>

    /* ========================================================================
     * 1. 核心测试函数
     * ======================================================================== */

    /**
     * @brief 执行UART硬件回环测试
     *
     * @return true=测试通过, false=测试失败
     */
    bool uart_loopback_test_execute(void);

    /**
     * @brief 硬件回环测试(TX-RX物理短接)
     * @details 发送数据后通过HAL_UART_Receive接收,验证收发一致性
     * @note 需要短接PA2(TX)和PA3(RX)
     *
     * @return true=测试通过, false=测试失败
     */
    bool uart_loopback_test_hardware(void);

    /* ========================================================================
     * 2. 辅助测试函数
     * ======================================================================== */

    /**
     * @brief 构造测试用的控制命令数据
     * @param ctrl 输出参数,控制命令结构体指针
     */
    void uart_loopback_build_test_data(void* ctrl);

    /**
     * @brief 逐字节比较两个缓冲区
     * @param expected 期望数据
     * @param actual 实际数据
     * @param len 比较长度
     * @return true=完全匹配, false=不匹配
     */
    bool uart_loopback_compare_bytes(const uint8_t* expected,
                                     const uint8_t* actual,
                                     size_t len);

    /* ========================================================================
     * 3. Debug输出函数
     * ======================================================================== */

    /**
     * @brief 以十六进制格式转储数据
     * @param data 数据指针
     * @param len 数据长度
     * @param prefix 前缀字符串(用于标识,如"[SEND]"或"[RECV]")
     */
    void uart_loopback_hex_dump(const uint8_t* data,
                                size_t len,
                                const char* prefix);

    /**
     * @brief 输出协议验证的详细结果
     * @param result 解析结果
     * @param frame_buf 帧缓冲区
     * @param frame_len 帧长度
     */
    void uart_loopback_print_validation(const void* result,
                                        const uint8_t* frame_buf,
                                        size_t frame_len);

    /**
     * @brief 输出解析后的控制命令数据结构
     * @param ctrl 控制命令结构体指针
     */
    void uart_loopback_print_ctrl_frame(const void* ctrl);

#ifdef __cplusplus
}
#endif

#endif /* UART_LOOPBACK_TEST_H */
