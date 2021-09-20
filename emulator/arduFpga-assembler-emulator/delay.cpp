
#include <QThread>
#include <time.h>
#include "delay.h"

void delay_us(uint32_t us) {
    QThread::usleep(us);
}

void delay_ms(uint16_t ms) {
    QThread::msleep(ms);
}

void delay_s(uint16_t s) {
    QThread::sleep(s);
}

void timer_enable(timer_t *inst, bool enable) {
    struct timespec tstart={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    inst->tik = ((tstart.tv_sec * 1000) + (tstart.tv_nsec / 1000000)) + inst->value;
    inst->enabled = enable;
}

bool timer_tik(timer_t *inst) {
    struct timespec tstart={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    if((int32_t)((int32_t)(tstart.tv_sec * 1000) + (int32_t)(tstart.tv_nsec / 1000000)) - (int32_t)inst->tik > 0 && inst->enabled == true) {
        timer_enable(inst, true);
        return true;
    }
    return false;
}
