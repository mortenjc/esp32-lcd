
idf_component_register(
                         SRCS "../UI2/ui_helpers.c"
                              "../UI2/ui.c"
                              "../UI2/screens/ui_Screen1.c"
                              "../UI2/images/ui_img_wifi_png.c"
                              "main.c"
                              "sdcard.c"
                              "LCD_Driver/Vernon_ST7789T/Vernon_ST7789T.c"
                              "LCD_Driver/ST7789.c"
                              "LVGL_Driver/LVGL_Driver.c"
                              "SD_Card/SD_SPI.c"
                              "Wireless/wireless.c"

                         INCLUDE_DIRS
                              "./LCD_Driver/Vernon_ST7789T"
                              "./LCD_Driver"
                              "./LVGL_Driver"
                              "./SD_Card"
                              "."
                              "../UI2"
                       )
