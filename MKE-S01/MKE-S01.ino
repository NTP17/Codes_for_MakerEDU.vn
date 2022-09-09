// Thư viện cho cảm biến siêu âm MKE-S01
// The library for MKE-S01 ultrasonic sensor
#include "UltraSonicDistanceSensor.h"

// Định nghĩa hai chân ECHO và TRIG của cảm biến sẽ gắn vào chân nào của Arduino
// Define which pins will correspond to the sensor's ECHO and TRIG pin
#define ECHO 12
#define TRIG 13

// Định nghĩa chân phát tín hiệu còi báo động
// Define a pin to output alert sound
#define ALERT 11

// Bốn hằng số cho bốn ngưỡng khoảng cách
// Four constants for four distance thresholds
#define SAFE 40
#define CLOSE3 30
#define CLOSE2 20
#define CLOSE1 10

// Dùng hai chân TRIG và ECHO để khai báo một đối tượng điều khiển cảm biến
// Use TRIG and ECHO pin to define an object for controlling the connected sensor
UltraSonicDistanceSensor usonic(TRIG, ECHO);

// Một biến số nguyên chứa khoảng cách đo được
// An integer variable to store measured distance
int distance;

void setup() {
  // Không cần pinMode cho ECHO và TRIG vì hai chân này đã được khai báo cùng lúc khai báo đối tượng ở trên
  // It is not neccessary to use pinMode on ECHO and TRIG pin since that has already been done when declaring the object above 
  pinMode(ALERT, OUTPUT);
}

void loop() {
  // Kiểm tra cảm biến đã sẵn sàng chưa
  // Check if the sensor is ready
  if (usonic.available()) {

    // Lưu khoảng cách đo được ở thời gian thực
    // Store real-time distance measurement
    distance = usonic.getcm();

    // Nếu khoảng cách lớn hơn ngưỡng an toàn thì tắt báo động
    // If distance is greater than safe threshold, turn off alert
    if (distance > SAFE) digitalWrite(ALERT, LOW);

    // Nếu khoảng cách lọt vào giữa ngưỡng an toàn và ngưỡng gần thứ ba, tạo ra tiếng bíp chậm
    // If distance falls between the safe threshold and the third-closet threshold, output a slow beep
    if ((distance <= SAFE) and (distance > CLOSE3)) {
      digitalWrite(ALERT, HIGH);
      delay(250);
      digitalWrite(ALERT, LOW);
      delay(250);
    }

    // Nếu khoảng cách lọt vào khoảng gần thứ ba và gần thứ nhì, bíp nhanh gấp đôi
    // If distance falls between the third-closet threshold and the second-closet threshold, beep twice as fast
    if ((distance <= CLOSE3) and (distance > CLOSE2)) {
      digitalWrite(ALERT, HIGH);
      delay(125);
      digitalWrite(ALERT, LOW);
      delay(125);
    }

    // Nếu khoảng cách lọt vào khoảng gần nhì và gần nhất, bíp nhanh gấp 4 lần (so với ban đầu)
    // If distance falls between the second-closet threshold and the closet threshold, beep 4 times as fast (as the original beep interval)
    if ((distance <= CLOSE2) and (distance > CLOSE1)) {
      digitalWrite(ALERT, HIGH);
      delay(62.5);
      digitalWrite(ALERT, LOW);
      delay(62.5);
    }

    // Luôn bật, để còi ngân dài khi khoảng cách nhỏ hơn ngưỡng gần nhất
    // When distance is less than the closet threshold, leave alert sound always on without beeping
    if (distance <= CLOSE1) digitalWrite(ALERT, HIGH);
  }
}
