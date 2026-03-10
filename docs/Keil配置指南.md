# Keil 配置指南（v2）- UART 回环与 AGV 业务模式

本文档基于当前代码状态整理，目标是：

- 不依赖 Keil `Define` 也能切换模式
- 默认不影响 AGV 正常业务发送
- 需要时可开启硬件自收自发测试

## 1. 当前控制方式

模式开关统一在：

- `AGV_Protocol/uart_loopback/uart_loopback_config.h`

关键宏：

- `UART_LOOPBACK_TEST_ENABLE`
- `UART_LOOPBACK_HARDWARE_ENABLE`

推荐理解：

- `UART_LOOPBACK_TEST_ENABLE=0`：关闭回环测试，走正常 AGV 业务逻辑
- `UART_LOOPBACK_TEST_ENABLE=1` 且 `UART_LOOPBACK_HARDWARE_ENABLE=1`：执行硬件自收自发

## 2. 一次性工程设置（Keil）

打开 `MDK-ARM/LED.uvprojx` 后，在 `Options for Target -> C/C++ -> Include Paths` 中确认有：

- `..\AGV_Protocol\uart_frame`
- `..\AGV_Protocol\agv_uart_frame`
- `..\AGV_Protocol\uart_loopback`

并删除旧绝对路径（如果存在）：

- `D:/Desktop/STM32/LED/AGV_Protocol/uart_frame`
- `D:/Desktop/STM32/LED/AGV_Protocol/agv_uart_frame`

## 3. 每次切换模式要做的步骤

1. 编辑 `AGV_Protocol/uart_loopback/uart_loopback_config.h`
2. 按目标设置宏
3. 在 Keil `C/C++ -> Define` 中确认未强行定义 `UART_LOOPBACK_TEST_ENABLE`
4. `Rebuild all target files`

配置示例：

```c
/* AGV 正常业务模式（推荐默认） */
#define UART_LOOPBACK_TEST_ENABLE 0
#define UART_LOOPBACK_HARDWARE_ENABLE 0
```

```c
/* 硬件自收自发测试模式（需要 TX/RX 物理短接） */
#define UART_LOOPBACK_TEST_ENABLE 1
#define UART_LOOPBACK_HARDWARE_ENABLE 1
```

## 4. 验证清单

编译验证：

- 没有 `cannot open source input file "uart_frame_config.h"` 错误
- 没有 `cannot open source input file "uart_loopback_config.h"` 错误

运行验证：

- 业务模式：持续发送 AGV 控制帧
- 硬件回环模式：进入 `uart_loopback_test_execute()`，输出回环测试日志

## 5. 常见问题

Q: 我已经在配置头里设为 `0`，为什么还在跑回环测试？  
A: 通常是 Keil `Define` 里仍有 `UART_LOOPBACK_TEST_ENABLE`，会覆盖配置头默认值。

Q: 回环测试失败怎么办？  
A: 检查是否短接了 UART2 `PA2(TX)` 与 `PA3(RX)`，并确认串口参数一致。

Q: 只改 Keil 不改代码能切换吗？  
A: 可以，但不推荐。建议统一通过配置头管理，避免多人协作时配置漂移。

## 6. 关联文档

- `docs/uart_frame_include_path_调整说明.md`
- `docs/AGV 二次开发接口.md`
