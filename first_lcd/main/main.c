//
#include "ST7789.h"
#include "SD_SPI.h"
#include "Wireless/Wireless.h"
#include "driver/adc.h"
#include "sdcard.h"
#include "ui.h"

#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>


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


int list_files(void) {
  DIR *dp;
  struct dirent *ep;
  dp = opendir ("/sdcard");
  if (dp != NULL) {
    while ((ep = readdir (dp)) != NULL) {
      if (ep->d_type == DT_REG) {
        printf("file %s\n", ep->d_name);
      }
    }

    (void) closedir (dp);
    return 0;
  } else {
    perror ("Couldn't open the directory");
    return -1;
  }
}


void mjcdemo2(void) {
  lv_disp_load_scr(ui_Screen2);
  char buf[100];
  for (int i = 1; i<500; i+= 24) {
    sprintf(buf, "B:/sdcard/matrix/%05d.png", i);
    //sprintf(buf, "B:/sdcard/mat%03d.png", i);
    //printf("%s\n", buf);
    lv_img_set_src(ui_Image2, buf);
    vTaskDelay(pdMS_TO_TICKS(5));
    lv_timer_handler();
  }
}



void mjcdemo1() {
  lv_disp_load_scr(ui_Screen1);
  char buf[100];
  int i = 0;

  adc1_config_width(12);

  lv_coord_t array[10];
  memset(array, 50, sizeof(array));

  lv_chart_series_t* ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, array);

  int t0 = mytime();

  while (i < 100) {
    int adc1 = adc1_get_raw(ADC1_EXAMPLE_CHAN0);
    int adc2 = adc1_get_raw(ADC1_EXAMPLE_CHAN0);

    if (i >= 10) {
      for (int j = 0; j < 9; j++) {
        array[j] =array[j+1];
        array[9] = adc2;
      }
    } else {
      array[i] = adc2;
    }

    sprintf(buf, "%d", mytime() - t0);
    lv_label_set_text(ui_Label10, buf);

    sprintf(buf, "%d", adc1);
    lv_label_set_text(ui_adc0Value, buf);

    sprintf(buf, "%d", adc2);
    lv_label_set_text(ui_adc1Value, buf);

    lv_chart_refresh(ui_Chart1);

    i++;

    vTaskDelay(pdMS_TO_TICKS(100));
    lv_timer_handler();
  }
}


void app_main(void) {
  Wireless_Init();
  vTaskDelay(pdMS_TO_TICKS(1000));
  SD_Init();
  LCD_Init();
  BK_Light(50);
  LVGL_Init();
  ui_init();

  listdirs();
  list_files();

  while (1) {
    mjcdemo2();
    mjcdemo1();
  }
}
