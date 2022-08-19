// Định nghĩa một chân số cho đèn LED, một giá trị ngưỡng để phát hiện trời tối (200 cho quang trở, 500 cho diode cảm quang), và một chân tương tự cho cảm biến ánh sáng.
// Define a digial pin for LED, a threshold for detecting darkness (200 for LDR, 500 for photodiode), and an analog pin for sensing brightness.
#define LED 9
#define threshold 200
#define LDR A1

// Chỉ cần pinMode cho chân số, chân tương tự không cần pinMode.
// Only digital pins need pinMode-ing, no need for analog pins.
void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
// Tạo một biến số nguyên để lưu số đo từ quang trở/diode cảm quang.
// Create an integer variable to store readings from LDR/photodiode.
  int brightness = analogRead(LDR);

// Xung quanh càng tối, số đo càng tăng. Một khi đạt ngưỡng định mức (nói cách khác, xung quanh đủ tối) thì bật đèn LED. Ngược lại, nếu số đo thấp hơn ngưỡng thì tắt đèn.
// The darker the area, the greater the number. Upon reaching the defined threshold (aka. area is dark enough), turn on the LED. Otherwise, turn it off.
  if (brightness > threshold) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
}
