[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver X9CXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/x9cxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

X9C102、X9C103、X9C104、X9C503は、デジタル制御（XDCP）ポテンショメータです。このデバイスは、抵抗アレイ、ワイパースイッチ、制御部、および不揮発性メモリで構成されています。ワイパーの位置は3線式インターフェースによって制御されます。ポテンショメータは、99個の抵抗素子とワイパースイッチングネットワークで構成される抵抗アレイによって実装されています。各素子の間と両端には、ワイパー端子にアクセスできるタップポイントがあります。ワイパー素子の位置は、CS、U/D、およびINC入力によって制御されます。ワイパーの位置は不揮発性メモリに保存され、その後の電源投入時に呼び出すことができます。このデバイスは、制御から信号処理、パラメータ調整まで、幅広い用途において、3端子ポテンショメータまたは2端子可変抵抗器として使用できます。

LibDriver X9CXXは、LibDriverがリリースしたX9CXX用のフル機能ドライバです。デジタルポテンショメータと追加機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver X9CXXのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver X9CXX用のプラットフォームに依存しないGPIOバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver X9CXXドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver X9CXXプログラミング例が含まれています。

/ docディレクトリには、LibDriver X9CXXオフラインドキュメントが含まれています。

/ datasheetディレクトリには、X9CXXデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないGPIOバステンプレートを参照して、指定したプラットフォームのGPIOバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/x9cxx/index.html](https://www.libdriver.com/docs/x9cxx/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。