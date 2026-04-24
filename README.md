 **

### FreeMODBUS RTU Slave Demo for STM32 Nucleo-64 board
** 

 **项目简介** 
本项目展示了如何在 STM32 Nucleo 系列开发板上移植并运行 FreeMODBUS 协议栈，实现 Modbus RTU 从站功能。程序初始化后，将保持寄存器设置为特定初始值，并通过 UART3 接口响应主站的 Modbus 请求

 **硬件依赖** 

1. 开发板: STM32 Nucleo-64 (芯片型号为STM32G474RET6)
2. 通信接口: USART3 (用于 Modbus RTU 通信)
3. 定时器: TIM7 (用于 FreeMODBUS 的3.5字符延时帧结束判定)

 **编译与烧录** 

1. 使用keil打开FreeMODBUS.uvprojx工程文件
2. 点击rebuild进行编译
3. neucleo-64 board通过type-c转USB接线连至PC
4. 点击load，将程序烧录至开发板

 **测试方法** 

1. 硬件连接:使用杜邦线将USB转串口连接器的TX引脚连接至开发板的PB11引脚（UART_RX），将连接器的RX引脚连接至开发板的PB10引脚（UART_TX），将连接器的GND引脚连接至开发板的任意一个GND引脚

2. 软件调试：使用Modbus Poll软件打开neucleo_modbus_test.mbp文件，即可测通并使PC成为主机与开发板进行基于MODBUS协议的通信

    连接参数：
    波特率: 115200
    数据位: 8
    停止位: 1
    校验: None
    从站 ID: 1

3. 开发板的引脚分布参照hardware_doc文件夹中的nucleo-64 boards user manual.pdf文件中的Figure 18








