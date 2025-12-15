

idf_component_register(
                         SRCS "../UI/ui_helpers.c"
                              "../UI/ui.c"
                              "../UI/screens/ui_Screen1.c"
                              "../UI/images/ui_img_shot_png.c"
                              "main.c"
                              "sdcard.c"
                              "LCD_Driver/Vernon_ST7789T/Vernon_ST7789T.c" 
                              "LCD_Driver/ST7789.c"
                              "LVGL_Driver/LVGL_Driver.c"
                              "SD_Card/SD_SPI.c"

                         INCLUDE_DIRS 
                              "./LCD_Driver/Vernon_ST7789T" 
                              "./LCD_Driver" 
                              "./LVGL_Driver" 
                              "./SD_Card"
                              "."
                              "../UI"
                       )
