import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

IR_SENSOR_PIN = 17
LED_PIN = 18

GPIO.setup(IR_SENSOR_PIN, GPIO.IN)
GPIO.setup(LED_PIN, GPIO.OUT)

def notify_obstacle_detected():
    print("Obstacle detected! LED ON")
    GPIO.output(LED_PIN, GPIO.HIGH)

def no_obstacle():
    print("No obstacle detected. LED OFF")
    GPIO.output(LED_PIN, GPIO.LOW)

try:
    while True:
        sensor_value = GPIO.input(IR_SENSOR_PIN)

        if sensor_value == GPIO.LOW:
            notify_obstacle_detected()
        else:
            no_obstacle()

        time.sleep(0.1)

except KeyboardInterrupt:
    print("Program interrupted")

finally:
    GPIO.cleanup()
