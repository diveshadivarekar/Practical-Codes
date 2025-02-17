//Switch an LED using an IR sensor

	int ir = 2;
	int PinLed = 10;
	int val=0;


	void setup()
	{
		pinMode(ir, INPUT);
		pinMode(PinLed, OUTPUT);

	}

	void loop()
	{
		if(digitalRead(ir) == LOW)
		{
			digitalWrite(PinLed, HIGH);
		}
		else
		{
			digitalWrite(PinLed, LOW);
		}
	}