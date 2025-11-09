[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver X9CXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/x9cxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

X9C102、X9C103、X9Cl04、X9C503是数字控制（XDCP）电位计。该器件由电阻阵列、滑动变阻器、控制部分和非易失性存储器组成。滑动变阻器位置由三线接口控制。电位计由99个电阻元件和滑动变阻器开关网络组成的电阻阵列实现。在每个元件之间是滑动变阻器端子访问的抽头点。滑动变阻器的位置由CS、U/D和INC输入控制。滑动变阻器的位置可以存储在非易失性存储器中，然后在随后的通电操作中调用。该器件可做为三端电位计或两端可变电阻器，用于从控制信号处理到参数调整的各种应用。

LibDriver X9CXX是LibDriver推出的X9CXX全功能驱动，该驱动提供数字电位器功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver X9CXX的源文件。

/interface目录包含了LibDriver X9CXX与平台无关的GPIO总线模板。

/test目录包含了LibDriver X9CXX驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver X9CXX编程范例。

/doc目录包含了LibDriver X9CXX离线文档。

/datasheet目录包含了X9CXX数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的GPIO总线模板，完成指定平台的GPIO总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_x9cxx_basic.h"

uint8_t res;
uint8_t s;
uint8_t step = 5;
float ohm;
float resistor = 1000.0f;
x9cxx_bool_t store_enable = X9CXX_BOOL_FALSE;

/* basic */
res = x9cxx_basic_init(X9C102);
if (res != 0)
{
    return 1;
}

...
    
/* reset to max */
res = x9cxx_basic_reset_to_max(store_enable);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: reset to max failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* get resistor */
res = x9cxx_basic_get_resistor(&s, &ohm);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: get resistor failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* output */
x9cxx_interface_debug_print("x9cxx: reset to max.\n");
x9cxx_interface_debug_print("x9cxx: step is %d.\n", s);
x9cxx_interface_debug_print("x9cxx: resistor is %0.2fohm.\n", ohm);

...
    
/* reset to min */
res = x9cxx_basic_reset_to_min(store_enable);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: reset to min failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* get resistor */
res = x9cxx_basic_get_resistor(&s, &ohm);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: get resistor failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* output */
x9cxx_interface_debug_print("x9cxx: reset to min.\n");
x9cxx_interface_debug_print("x9cxx: step is %d.\n", s);
x9cxx_interface_debug_print("x9cxx: resistor is %0.2fohm.\n", ohm);

...
    
/* increment */
res = x9cxx_basic_increment(step, store_enable);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: increment failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* get resistor */
res = x9cxx_basic_get_resistor(&s, &ohm);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: get resistor failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* output */
x9cxx_interface_debug_print("x9cxx: increment %d step.\n", step);
x9cxx_interface_debug_print("x9cxx: step is %d.\n", s);
x9cxx_interface_debug_print("x9cxx: resistor is %0.2fohm.\n", ohm);   

...
 
/* decrement */
res = x9cxx_basic_decrement(step, store_enable);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: decrement failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* get resistor */
res = x9cxx_basic_get_resistor(&s, &ohm);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: get resistor failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* output */
x9cxx_interface_debug_print("x9cxx: decrement %d step.\n", step);
x9cxx_interface_debug_print("x9cxx: step is %d.\n", s);
x9cxx_interface_debug_print("x9cxx: resistor is %0.2fohm.\n", ohm); 

...

/* set absolute step */
res = x9cxx_basic_set_absolute_step(step, store_enable);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: set absolute step failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* get resistor */
res = x9cxx_basic_get_resistor(&s, &ohm);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: get resistor failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* output */
x9cxx_interface_debug_print("x9cxx: set absolute step %d.\n", step);
x9cxx_interface_debug_print("x9cxx: step is %d.\n", s);
x9cxx_interface_debug_print("x9cxx: resistor is %0.2fohm.\n", ohm);   

...

/* set absolute resistor */
res = x9cxx_basic_set_absolute_resistor(resistor, store_enable);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: set absolute resistor failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* get resistor */
res = x9cxx_basic_get_resistor(&s, &ohm);
if (res != 0)
{
    x9cxx_interface_debug_print("x9cxx: get resistor failed.\n");
    (void)x9cxx_basic_deinit();

    return 1;
}

/* output */
x9cxx_interface_debug_print("x9cxx: set absolute resistor %0.2fohm.\n", resistor);
x9cxx_interface_debug_print("x9cxx: step is %d.\n", s);
x9cxx_interface_debug_print("x9cxx: resistor is %0.2fohm.\n", ohm);   

...

(void)x9cxx_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/x9cxx/index.html](https://www.libdriver.com/docs/x9cxx/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。