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
 * @file      driver_x9cxx_output_test.c
 * @brief     driver x9cxx output test source file
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

#include "driver_x9cxx_output_test.h"
#include <stdlib.h>

static x9cxx_handle_t gs_handle;        /**< x9cxx handle */

/**
 * @brief     output test
 * @param[in] type chip type
 * @param[in] store_enable bool value
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t x9cxx_output_test(x9cxx_type_t type, x9cxx_bool_t store_enable, uint32_t times)
{
    uint8_t res;
    uint8_t counter;
    uint8_t step;
    uint32_t i;
    float ohm;
    float ohm_check;
    x9cxx_info_t info;
    
    /* link functions */
    DRIVER_X9CXX_LINK_INIT(&gs_handle, x9cxx_handle_t);
    DRIVER_X9CXX_LINK_CS_GPIO_INIT(&gs_handle, x9cxx_interface_cs_gpio_init);
    DRIVER_X9CXX_LINK_CS_GPIO_DEINIT(&gs_handle, x9cxx_interface_cs_gpio_deinit);
    DRIVER_X9CXX_LINK_CS_GPIO_WRITE(&gs_handle, x9cxx_interface_cs_gpio_write);
    DRIVER_X9CXX_LINK_UP_DOWN_GPIO_INIT(&gs_handle, x9cxx_interface_up_down_gpio_init);
    DRIVER_X9CXX_LINK_UP_DOWN_GPIO_DEINIT(&gs_handle, x9cxx_interface_up_down_gpio_deinit);
    DRIVER_X9CXX_LINK_UP_DOWN_GPIO_WRITE(&gs_handle, x9cxx_interface_up_down_gpio_write);
    DRIVER_X9CXX_LINK_INC_GPIO_INIT(&gs_handle, x9cxx_interface_inc_gpio_init);
    DRIVER_X9CXX_LINK_INC_GPIO_DEINIT(&gs_handle, x9cxx_interface_inc_gpio_deinit);
    DRIVER_X9CXX_LINK_INC_GPIO_WRITE(&gs_handle, x9cxx_interface_inc_gpio_write);
    DRIVER_X9CXX_LINK_DEBUG_PRINT(&gs_handle, x9cxx_interface_debug_print);
    DRIVER_X9CXX_LINK_DELAY_MS(&gs_handle, x9cxx_interface_delay_ms);
    DRIVER_X9CXX_LINK_DELAY_US(&gs_handle, x9cxx_interface_delay_us);
    
    /* x9cxx info */
    res = x9cxx_info(&info);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        x9cxx_interface_debug_print("x9cxx: chip is %s.\n", info.chip_name);
        x9cxx_interface_debug_print("x9cxx: manufacturer is %s.\n", info.manufacturer_name);
        x9cxx_interface_debug_print("x9cxx: interface is %s.\n", info.interface);
        x9cxx_interface_debug_print("x9cxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        x9cxx_interface_debug_print("x9cxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        x9cxx_interface_debug_print("x9cxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        x9cxx_interface_debug_print("x9cxx: max current is %0.2fmA.\n", info.max_current_ma);
        x9cxx_interface_debug_print("x9cxx: max temperature is %0.1fC.\n", info.temperature_max);
        x9cxx_interface_debug_print("x9cxx: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start output test */
    x9cxx_interface_debug_print("x9cxx: start output test.\n");
    
    /* set chip type */
    res = x9cxx_set_type(&gs_handle, type);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: set type failed.\n");
        
        return 1;
    }
    
    /* x9cxx init */
    res = x9cxx_init(&gs_handle);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: init failed.\n");
        
        return 1;
    }
    
    /* reset to min */
    res = x9cxx_reset_to_min(&gs_handle, store_enable);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: reset to min failed.\n");
        (void)x9cxx_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        /* increment */
        res = x9cxx_increment(&gs_handle, 1, store_enable);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: increment failed.\n");
            (void)x9cxx_deinit(&gs_handle);
            
            return 1;
        }
        
        /* get step counter */
        res = x9cxx_get_step_counter(&gs_handle, &counter);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: get step counter failed.\n");
            (void)x9cxx_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        x9cxx_interface_debug_print("x9cxx: increment and current step counter is %d.\n", counter);
        
        /* 5000ms */
        x9cxx_interface_delay_ms(5000);
    }
    
    /* reset to max */
    res = x9cxx_reset_to_max(&gs_handle, store_enable);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: reset to max failed.\n");
        (void)x9cxx_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        /* decrement */
        res = x9cxx_decrement(&gs_handle, 1, store_enable);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: decrement failed.\n");
            (void)x9cxx_deinit(&gs_handle);
            
            return 1;
        }
        
        /* get step counter */
        res = x9cxx_get_step_counter(&gs_handle, &counter);
        if (res != 0)
        {
            x9cxx_interface_debug_print("x9cxx: get step counter failed.\n");
            (void)x9cxx_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        x9cxx_interface_debug_print("x9cxx: decrement and current step counter is %d.\n", counter);
        
        /* 5000ms */
        x9cxx_interface_delay_ms(5000);
    }
    
    counter = rand() % 100;
    res = x9cxx_set_absolute_step_counter(&gs_handle, counter, store_enable);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: set absolute step counter failed.\n");
        (void)x9cxx_deinit(&gs_handle);
        
        return 1;
    }
    x9cxx_interface_debug_print("x9cxx: set absolute step counter %d.\n", counter);
    
    /* resistor convert to register */
    ohm = (float)(rand() % 1000) / 10.0f;
    res = x9cxx_resistor_convert_to_register(&gs_handle, ohm, &step);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: resistor convert to register failed.\n");
        (void)x9cxx_deinit(&gs_handle);
        
        return 1;
    }
    res = x9cxx_resistor_convert_to_data(&gs_handle, step, &ohm_check);
    if (res != 0)
    {
        x9cxx_interface_debug_print("x9cxx: resistor convert to data failed.\n");
        (void)x9cxx_deinit(&gs_handle);
        
        return 1;
    }
    x9cxx_interface_debug_print("x9cxx: ohm is %0.2f and converted ohm is %0.2f.\n", ohm, ohm_check);
    
    /* finish output test */
    x9cxx_interface_debug_print("x9cxx: finish output test.\n");
    (void)x9cxx_deinit(&gs_handle);
    
    return 0;
}
