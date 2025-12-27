
import time
import machine

led = machine.Pin(8, machine.Pin.OUT)
led_state = 0

M = {}
def fibn(n):
    if n == 0 or n == 1:
        return 1

    if n in M:
        return M[n]
    
    f = fibn(n - 2) + fibn(n - 1)
    M[n] = f
    return f


i = 1
while True:
    led.value(led_state)
    led_state ^= 1
    f = fibn(i)
    print('fib(%d) = %d' % (i, f))
    time.sleep(0.05)
    
    i += 1