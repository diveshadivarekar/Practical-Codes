import RPi.GPIO as GPIO
import Adafruit_DHT
import time

GPIO.setmode(GPIO.BCM)

BUZZER_PIN = 17 
DHT_SENSOR = Adafruit_DHT.DHT11 
DHT_PIN = 4 

GPIO.setup(BUZZER_PIN, GPIO.OUT)

TEMP_THRESHOLD = 30

def sound_buzzer():
    print("Threshold exceeded! Buzzer ON!")
    GPIO.output(BUZZER_PIN, GPIO.HIGH)

def stop_buzzer():
    print("Buzzer OFF")
    GPIO.output(BUZZER_PIN, GPIO.LOW)

def monitor_temperature():
    try:
        while True:
            humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)

            if temperature is not None:
                print(f'Temperature: {temperature:.2f}°C, Humidity: {humidity:.2f}%')

                if temperature > TEMP_THRESHOLD:
                    sound_buzzer()
                else:
                    stop_buzzer()
            else:
                print('Failed to get reading from the sensor')

            time.sleep(2)

    except KeyboardInterrupt:
        print("Program interrupted")

    finally:
        GPIO.cleanup()

monitor_temperature()
