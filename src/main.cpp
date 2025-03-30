#include <WiFi.h>

// Wi-Fi 网络名称和密码
const char* ssid = "跞轩之家";
const char* password = "13763333092";

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  delay(100);

  // 开始连接 Wi-Fi
  Serial.println("正在连接到 Wi-Fi...");
  WiFi.begin(ssid, password);

  // 等待连接
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // 连接成功
  Serial.println("\nWi-Fi 已连接!");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 在主循环中可以添加其他逻辑
  delay(1000);
}