#define mic A1        // Định nghĩa một chân Analog cho cảm biến âm thanh MKE-S06
                      // Define an Analog pin for MKE-S06 sound sensor

#define LED 9         // Định nghĩa một chân Digital cho mạch đèn LED
                      // Define a Digital pin for LED module

#define debounce 200  // Định nghĩa một khoảng thời gian chờ để ổn định tín hiệu âm thanh sau một tiếng vỗ
                      // Define a duration for audio signal to stablize after one clap

#define wait 1000     // Định nghĩa một khoảng thời gian đợi giữa những lần bật tắt đèn
                      // Define a cooldown duration after toggling the LED

#define interval 500  // Định nghĩa khoảng thời gian chờ tối đa giữa hai tiếng vỗ tay
                      // Define a maximum interval between two claps

#define threshold 100 // Định nghĩa ngưỡng phát hiện một tiếng vỗ tay
                      // Define a voltage threshold to recognize a clap

bool state = LOW;           // Một biến kiểu boolean để lưu trạng thái của đèn
                            // A boolean variable to store the LED's state

unsigned long duration = 0; // Một biến số nguyên lớn để theo dõi hệ thống theo thời gian thực
                            // A large integer to store real-time values

void setup() {
  pinMode(LED, OUTPUT); // Khai báo vai trò của chân số 9 (chân sẽ gắn đèn vào) là chân xuất tín hiệu. Các chân Analog không cần khai báo
                        // Assign pin 9 (to which the LED will be connected) to output signals. Analog pins do not need this line

  delay(1100);          // Đợi các chân Analog sẵn sàng
                        // Wait for Analog pins to get ready
}

void loop() {
  if (analogRead(mic) <= threshold) {        // Nếu nhận được một tiếng vỗ tay (phát hiện một tín hiệu âm thanh đủ lớn) Lưu ý: Với cảm biến âm thanh MKE-S06, số đo càng thấp, âm thanh càng to
                                             // If a clap is heard (a loud enough sound signal is received) Note: With the MKE-S06 sound sensor, the lower the output, the louder the sound

    delay(debounce);                         // Đợi tín hiệu ổn định
                                             // Wait for signal to stablize

    duration = millis();                     // Hàm millis() cho ta biết chương trình đã chạy được bao lâu kể từ khi bật nguồn hoặc reset. Tận dụng hàm này để lưu lại những thời điểm quan trọng, ví dụ như ngay khi phát hiện tiếng vỗ tay
                                             // millis() function tells us how long has the program been running since power on or last reset. Use it to save important time points, such as immediately after detecting a clap

    while (millis() - duration < interval) { // Nếu chưa vượt quá thời gian chờ tối đa đã định nghĩa ở trên thì tiếp tục đợi tiếng vỗ tay thứ hai, vượt quá rồi thì quay lại từ đầu để chờ tiếng vỗ tay đầu tiên
                                             // Wait for a second clap as long as waiting time does not exceed the define interval. If exceeds, go back to waiting for the first clap

      if (analogRead(mic) <= threshold) {
        // Nếu phát hiện tiếng vỗ tay thứ hai thành công, thì đảo ngược trạng thái của đèn LED (tắt thành bật, bật thành tắt), đợi một khoảng đã định nghĩa, và quay về chờ tiếng vỗ đầu tiên
        // If two claps are successfully detected, invert the LED's state (on becomes off, off becomes on), enters cooldown period as defined above, then go back to wait for the first clap again
        state = !state; 
        digitalWrite(LED, state);
        delay(wait);
        break;
      }
    }
  }
}
