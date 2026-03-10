# uart_frame Include Path 调整说明

本文档用于配合当前仓库改动：

- 已只保留一份配置文件：`AGV_Protocol/agv_uart_frame/uart_frame_config.h`
- 已删除重复文件：`AGV_Protocol/uart_frame/uart_frame_config.h`

因为 `uart_frame.h` 内部是 `#include "uart_frame_config.h"`，所以编译器必须能在 Include Path 里找到 `agv_uart_frame` 目录。

## 1. 你需要改什么

在 Keil 的 `Options for Target -> C/C++ -> Include Paths` 中，确保包含以下相对路径：

- `..\AGV_Protocol\uart_frame`
- `..\AGV_Protocol\agv_uart_frame`
- `..\AGV_Protocol\uart_loopback`（如果你还在使用回环测试）

同时删除失效的绝对路径（如果存在）：

- `D:/Desktop/STM32/LED/AGV_Protocol/uart_frame`
- `D:/Desktop/STM32/LED/AGV_Protocol/agv_uart_frame`

## 2. 后续必做步骤（按顺序）

完成 Include Path 后，请继续做下面步骤，避免“路径对了但行为不对”。

1. 打开 `AGV_Protocol/uart_loopback/uart_loopback_config.h`
2. 按你的目标设置开关：

```c
/* 纯AGV业务模式(推荐默认) */
#define UART_LOOPBACK_TEST_ENABLE 0
#define UART_LOOPBACK_HARDWARE_ENABLE 0
```

```c
/* 硬件自收自发测试模式(TX/RX短接) */
#define UART_LOOPBACK_TEST_ENABLE 1
#define UART_LOOPBACK_HARDWARE_ENABLE 1
```

3. 打开 Keil `Options for Target -> C/C++ -> Define`
4. 删除 `UART_LOOPBACK_TEST_ENABLE`（如果你曾在 Keil 里配置过）
5. `Rebuild all target files`
6. 确认编译通过并按下方验证项检查

说明：

- 现在支持“只改配置头，不改 Keil 宏”。
- 如果 Keil 里仍定义了同名宏，会覆盖配置头默认值，导致行为和你预期不一致。

## 3. 推荐顺序

建议 `agv_uart_frame` 放在 `uart_frame` 之后或之前都可以；当前只有一份 `uart_frame_config.h`，不会再出现命中歧义。

推荐最终形式（示例）：

```text
..\Core\Inc;
..\Drivers\STM32H7xx_HAL_Driver\Inc;
..\Drivers\STM32H7xx_HAL_Driver\Inc\Legacy;
..\Drivers\CMSIS\Device\ST\STM32H7xx\Include;
..\Drivers\CMSIS\Include;
..\AGV_Protocol\uart_frame;
..\AGV_Protocol\agv_uart_frame;
..\AGV_Protocol\uart_loopback
```

## 4. 修改步骤（Keil）

1. 打开工程：`MDK-ARM/LED.uvprojx`
2. 打开 `Options for Target 'LED'`（快捷键 `Alt+F7`）
3. 进入 `C/C++` 标签页
4. 在 `Include Paths` 中删除旧绝对路径，添加上面的相对路径
5. 点击 `OK` 保存
6. `Rebuild all target files`

## 5. 验证是否改对

编译通过且没有下面这类错误，说明 Include Path 已正确：

```text
cannot open source input file "uart_frame_config.h"
```

也可以额外做一个快速检查：

- 打开 `AGV_Protocol/uart_frame/uart_frame.h`
- 确认 `#include "uart_frame_config.h"` 不报红

另外，按模式验证运行行为：

- `UART_LOOPBACK_TEST_ENABLE=0`：主循环持续走 AGV 正常发送逻辑
- `UART_LOOPBACK_TEST_ENABLE=1` 且 `UART_LOOPBACK_HARDWARE_ENABLE=1`：执行硬件自收自发

## 6. 常见误区

- 只加 `..\AGV_Protocol\uart_frame` 不够：因为配置文件现在在 `..\AGV_Protocol\agv_uart_frame`
- 使用机器私有绝对路径：别人拉仓后会编译失败
- 同时保留两份 `uart_frame_config.h`：容易因为搜索顺序导致配置不一致
- Keil `Define` 里保留了 `UART_LOOPBACK_TEST_ENABLE`：会覆盖配置头设置
