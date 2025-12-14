
#include "ST7789.h"
#include "SD_SPI.h"

#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "ui.h"
#include "ui_helpers.h"

#include <sys/time.h>

//ADC Channels
#if CONFIG_IDF_TARGET_ESP32
#define ADC1_EXAMPLE_CHAN0          ADC1_CHANNEL_6
#define ADC2_EXAMPLE_CHAN0          ADC2_CHANNEL_0
static const char *TAG_CH[2][10] = {{"ADC1_CH6"}, {"ADC2_CH0"}};
#else
#define ADC1_EXAMPLE_CHAN0          ADC1_CHANNEL_2
#define ADC2_EXAMPLE_CHAN0          ADC2_CHANNEL_0
//static const char *TAG_CH[2][10] = {{"ADC1_CH2"}, {"ADC2_CH0"}};
#endif


int mytime() {
  struct timeval tv_now;
  gettimeofday(&tv_now, NULL);
  return tv_now.tv_sec;
}


void app_main(void)
{
    SD_Init();                 // SD must be initialized behind the LCD
    LCD_Init();
    BK_Light(50);
    LVGL_Init();               // returns the screen object
    ui_init();

/********************* Demo *********************/
    char buf[100];
    int i = 0;

    adc1_config_width(12);

    lv_coord_t array[10];
    memset(array, 50, sizeof(array));

    lv_chart_series_t* ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, array);

    int t0 = mytime();

    while (1) {
        int adc1 = adc1_get_raw(ADC1_EXAMPLE_CHAN0);
        int adc2 = adc1_get_raw(ADC1_EXAMPLE_CHAN0);

        if (i >= 10) {
          for (int j = 0; j < 9; j++) {
            array[j] =array[j+1];
            array[9] = adc1;
          }
        } else {
          array[i] = adc1;    
        }

        sprintf(buf, "%d", mytime()-t0);
        lv_label_set_text(ui_Label10, buf);

        sprintf(buf, "%d", adc1);
        lv_label_set_text(ui_adc0Value, buf);

        sprintf(buf, "%d", adc2);
        lv_label_set_text(ui_adc1Value, buf);

        lv_chart_refresh(ui_Chart1);

        
        i++;
       
        vTaskDelay(pdMS_TO_TICKS(100));

        // The task running lv_timer_handler should have lower priority
        // than that running `lv_tick_inc`
        lv_timer_handler();
    }
}
