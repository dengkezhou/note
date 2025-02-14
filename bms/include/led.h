
#ifndef __IROM_LED_H__
#define __IROM_LED_H__

extern void init_led(void);
extern void inline led_on(void);
extern void inline led_off(void);
extern void inline led_ctrl(int on);

#endif /* __IROM_LED_H__ */
