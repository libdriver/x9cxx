/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-10-19
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/10/19  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_x9cxx_basic.h"
#include "driver_x9cxx_output_test.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     x9cxx full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t x9cxx(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"resistor", required_argument, NULL, 1},
        {"save", required_argument, NULL, 2},
        {"step", required_argument, NULL, 3},
        {"type", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknow";
    x9cxx_bool_t store_enable = X9CXX_BOOL_FALSE;
    uint8_t step = 1;
    float resistor = 1000.0f;
    uint32_t times = 3;
    x9cxx_type_t chip_type = X9C102;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* resistor */
            case 1 :
            {
                /* set the resistor */
                resistor = (float)atof(optarg);
                
                break;
            }
            
            /* save */
            case 2 :
            {
                /* set the save */
                if (strcmp("true", optarg) == 0)
                {
                    store_enable = X9CXX_BOOL_TRUE;
                }
                else if (strcmp("false", optarg) == 0)
                {
                    store_enable = X9CXX_BOOL_FALSE;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* step */
            case 3 :
            {
                /* set the step */
                step = (uint8_t)atol(optarg);
                
                break;
            }
            
            /* type */
            case 4 :
            {
                /* set the type */
                if (strcmp("X9C102", optarg) == 0)
                {
                    chip_type = X9C102;
                }
                else if (strcmp("X9C103", optarg) == 0)
                {
                    chip_type = X9C103;
                }
                else if (strcmp("X9C503", optarg) == 0)
                {
                    chip_type = X9C503;
                }
                else if (strcmp("X9C104", optarg) == 0)
                {
                    chip_type = X9C104;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* times */
            case 5 :
            {
                /* set the times */
                times = (uint32_t)atol(optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_output", type) == 0)
    {
        /* run output test */
        if (x9cxx_output_test(chip_type, store_enable, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_max", type) == 0)
    {
        uint8_t res;
        uint8_t s;
        float ohm;

        /* basic */
        res = x9cxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }

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
        
        return 0;
    }
    else if (strcmp("e_min", type) == 0)
    {
        uint8_t res;
        uint8_t s;
        float ohm;
        
        /* basic */
        res = x9cxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }

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
        
        return 0;
    }
    else if (strcmp("e_inc", type) == 0)
    {
        uint8_t res;
        uint8_t s;
        float ohm;
        
        /* basic */
        res = x9cxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* reset to min */
        res = x9cxx_basic_reset_to_min(X9CXX_BOOL_FALSE);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: reset to min failed.\n");
            (void)x9cxx_basic_deinit();
            
            return 1;
        }
        
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
        
        return 0;
    }
    else if (strcmp("e_dec", type) == 0)
    {
        uint8_t res;
        uint8_t s;
        float ohm;
        
        /* basic */
        res = x9cxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* reset to max */
        res = x9cxx_basic_reset_to_max(X9CXX_BOOL_FALSE);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: reset to max failed.\n");
            (void)x9cxx_basic_deinit();
            
            return 1;
        }
        
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
        
        return 0;
    }
    else if (strcmp("e_step", type) == 0)
    {
        uint8_t res;
        uint8_t s;
        float ohm;
        
        /* basic */
        res = x9cxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* reset to min */
        res = x9cxx_basic_reset_to_min(X9CXX_BOOL_FALSE);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: reset to min failed.\n");
            (void)x9cxx_basic_deinit();
            
            return 1;
        }
        
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
        
        return 0;
    }
    else if (strcmp("e_res", type) == 0)
    {
        uint8_t res;
        uint8_t s;
        float ohm;
        
        /* basic */
        res = x9cxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* reset to min */
        res = x9cxx_basic_reset_to_min(X9CXX_BOOL_FALSE);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: reset to min failed.\n");
            (void)x9cxx_basic_deinit();
            
            return 1;
        }
        
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
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        x9cxx_interface_debug_print("Usage:\n");
        x9cxx_interface_debug_print("  x9cxx (-i | --information)\n");
        x9cxx_interface_debug_print("  x9cxx (-h | --help)\n");
        x9cxx_interface_debug_print("  x9cxx (-p | --port)\n");
        x9cxx_interface_debug_print("  x9cxx (-t output | --test=output) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--times=<number>]\n");
        x9cxx_interface_debug_print("  x9cxx (-e max | --example=max) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>]\n");
        x9cxx_interface_debug_print("  x9cxx (-e min | --example=min) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>]\n");
        x9cxx_interface_debug_print("  x9cxx (-e inc | --example=inc) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]\n");
        x9cxx_interface_debug_print("  x9cxx (-e dec | --example=dec) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]\n");
        x9cxx_interface_debug_print("  x9cxx (-e step | --example=step) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--step=<number>]\n");
        x9cxx_interface_debug_print("  x9cxx (-e res | --example=res) [--type=<X9C102 | X9C103 | X9C503 | X9C104>] [--save=<true | false>] [--resistor=<ohm>]\n");
        x9cxx_interface_debug_print("\n");
        x9cxx_interface_debug_print("Options:\n");
        x9cxx_interface_debug_print("  -e <max | min | inc | dec | step | res>, --example=<max | min | inc | dec | step | res>\n");
        x9cxx_interface_debug_print("                          Run the driver example.\n");
        x9cxx_interface_debug_print("  -h, --help              Show the help.\n");
        x9cxx_interface_debug_print("  -i, --information       Show the chip information.\n");
        x9cxx_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        x9cxx_interface_debug_print("      --resistor=<ohm>    Set the resistor value.([default: 1000.0])\n");
        x9cxx_interface_debug_print("      --save=<true | false>\n");
        x9cxx_interface_debug_print("                          Save the settings to eeprom.([default: false])\n");
        x9cxx_interface_debug_print("      --step=<number>     Set the chip step.([default: 1])\n");
        x9cxx_interface_debug_print("  -t <output>, --test=<output>\n");
        x9cxx_interface_debug_print("                          Run the driver test.\n");
        x9cxx_interface_debug_print("      --times=<number>    Set the test times.([default: 3])\n");
        x9cxx_interface_debug_print("      --type=<X9C102 | X9C103 | X9C503 | X9C104>\n");
        x9cxx_interface_debug_print("                          Set the chip type.([default: X9C102])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        x9cxx_info_t info;
        
        /* print x9cxx info */
        x9cxx_info(&info);
        x9cxx_interface_debug_print("x9cxx: chip is %s.\n", info.chip_name);
        x9cxx_interface_debug_print("x9cxx: manufacturer is %s.\n", info.manufacturer_name);
        x9cxx_interface_debug_print("x9cxx: interface is %s.\n", info.interface);
        x9cxx_interface_debug_print("x9cxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        x9cxx_interface_debug_print("x9cxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        x9cxx_interface_debug_print("x9cxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        x9cxx_interface_debug_print("x9cxx: max current is %0.2fmA.\n", info.max_current_ma);
        x9cxx_interface_debug_print("x9cxx: max temperature is %0.1fC.\n", info.temperature_max);
        x9cxx_interface_debug_print("x9cxx: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        x9cxx_interface_debug_print("x9cxx: CS connected to GPIO22(BCM).\n");
        x9cxx_interface_debug_print("x9cxx: UD connected to GPIO17(BCM).\n");
        x9cxx_interface_debug_print("x9cxx: INC connected to GPIO27(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = x9cxx(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        x9cxx_interface_debug_print("x9cxx: run failed.\n");
    }
    else if (res == 5)
    {
        x9cxx_interface_debug_print("x9cxx: param is invalid.\n");
    }
    else
    {
        x9cxx_interface_debug_print("x9cxx: unknown status code.\n");
    }

    return 0;
}
