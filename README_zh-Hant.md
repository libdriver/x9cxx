[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver X9CXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/x9cxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

X9C102、X9C103、X9Cl04、X9C503是數位控制（XDCP）電位計。 該器件由電阻陣列、滑動變阻器、控制部分和非易失性記憶體組成。 滑動變阻器位置由三線介面控制。 電位計由99個電阻元件和滑動變阻器開關網絡組成的電阻陣列實現。 在每個元件之間是滑動變阻器端子訪問的抽頭點。 滑動變阻器的位置由CS、U/D和INC輸入控制。 滑動變阻器的位置可以存儲在非易失性記憶體中，然後在隨後的通電操作中調用。 該器件可做為三端電位計或兩端可變電阻器，用於從控制信號處理到參數調整的各種應用。

LibDriver X9CXX是LibDriver推出的X9CXX全功能驅動，該驅動提供數位電位器功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver X9CXX的源文件。

/interface目錄包含了LibDriver X9CXX與平台無關的GPIO總線模板。

/test目錄包含了LibDriver X9CXX驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver X9CXX編程範例。

/doc目錄包含了LibDriver X9CXX離線文檔。

/datasheet目錄包含了X9CXX數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的GPIO總線模板，完成指定平台的GPIO總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/x9cxx/index.html](https://www.libdriver.com/docs/x9cxx/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。