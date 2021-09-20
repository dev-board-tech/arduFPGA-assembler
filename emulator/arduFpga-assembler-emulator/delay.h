#ifndef DELAY_H
#define DELAY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t tik;
    uint32_t value;
    bool enabled;
}timer_t;

void delay_us(uint32_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);

void timer_service();
void timer_enable(timer_t *inst, bool enable);
bool timer_tik(timer_t *inst);

#endif // DELAY_H
