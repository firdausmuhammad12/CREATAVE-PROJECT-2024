#define MQ2_PIN 4
#define buzzer 2
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(MQ2_PIN, INPUT);
pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int mq2Value = analogRead(MQ2_PIN);
Serial.print("MQ2 value: ");
Serial.println(mq2Value);
if (mq2Value >= 500){
 Serial.println("gas terdeteksi");
 digitalWrite(buzzer, HIGH);
}else{
  Serial.println("kondisi aman");
  digitalWrite(buzzer, LOW);
}
delay(1000);
}
