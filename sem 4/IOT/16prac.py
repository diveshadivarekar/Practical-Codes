import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

LED_PINS = [17, 18]

for pin in LED_PINS:
    GPIO.setup(pin, GPIO.OUT)

def blink_leds():
    try:
        while True:
            for pin in LED_PINS:
                GPIO.output(pin, GPIO.HIGH)
            print("LEDs ON")
            time.sleep(1)

            for pin in LED_PINS:
                GPIO.output(pin, GPIO.LOW)
            print("LEDs OFF")
            time.sleep(1)

    except KeyboardInterrupt:
        print("Program interrupted")

    finally:
        GPIO.cleanup()

blink_leds()
