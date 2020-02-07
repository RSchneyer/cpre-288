

#include <string.h>
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"


void main(void)

{
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    timer_init();
    lcd_init();
    move_forward_smart(sensor_data, 2000, 250);


    oi_free(sensor_data); // do this once at end of main()

}
