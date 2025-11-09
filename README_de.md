[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver X9CXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/x9cxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Die X9C102, X9C103, X9C104 und X9C503 sind digital gesteuerte Potentiometer (XDCP). Das Bauteil besteht aus einem Widerstandsarray, Schleiferschaltern, einer Steuereinheit und einem nichtflüchtigen Speicher. Die Schleiferposition wird über eine Drei-Draht-Schnittstelle gesteuert. Das Potentiometer ist mit einem Widerstandsarray aus 99 Widerstandselementen und einem Schleiferschaltnetzwerk realisiert. Zwischen jedem Element und an beiden Enden befinden sich Abgriffe, die mit dem Schleiferanschluss verbunden sind. Die Schleiferposition wird über die Eingänge CS, U/D und INC gesteuert. Die Schleiferposition kann im nichtflüchtigen Speicher gespeichert und beim nächsten Einschalten wieder abgerufen werden. Das Bauteil kann als Dreipol-Potentiometer oder als Zweipol-Variabler Widerstand in einer Vielzahl von Anwendungen eingesetzt werden, von der Steuerung über die Signalverarbeitung bis hin zur Parametereinstellung.

LibDriver X9CXX ist ein umfassender Treiber für X9CXX, entwickelt von LibDriver. Er bietet ein digitales Potentiometer und weitere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver X9CXX-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver X9CXX GPIO.

/test enthält den Testcode des LibDriver X9CXX-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver X9CXX-Beispielcode.

/doc enthält das LibDriver X9CXX-Offlinedokument.

/Datenblatt enthält X9CXX-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige GPIO-Schnittstellenvorlage und stellen Sie Ihren Plattform-GPIO-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/x9cxx/index.html](https://www.libdriver.com/docs/x9cxx/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.