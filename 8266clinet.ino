#include "ESP8266WiFi.h"
const char *ssid = "8266-1"; // 这里定义将要建立的WiFi名称
const char *password = "88888888";
const char *time1 = "0";//开发保留变量
void setup() {
  Serial.begin(115200);
 
  // 模式设置
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  Serial.println("Setup done");
}
 
void loop() {
  Serial.println("scan start");
 
  // 是否找到WiFi
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println("networks found");
    //重复打印
    for (int i = 0; i < n; ++i) {
      
      // 打印WiFi名称
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
      //查询主机
      if (WiFi.SSID(i) == "schoolcardcenter") {
         //如果找到则发送本机信息
         WiFi.softAP(ssid, password);
         Serial.println("find");
         const char *time1 = "1";
         Serial.print("Access Point: ");    // 通过串口监视器输出信息
         Serial.println(ssid);              // 告知用户NodeMCU所建立的WiFi名
         Serial.print("IP address: ");      // 以及NodeMCU的IP地址
         Serial.println(WiFi.softAPIP());   // 通过调用WiFi.softAPIP()可以得到NodeMCU的IP地址
         delay(5000);
      }
      else {
       //如果没有找到主机，则关闭上一循环发送的WiFi
        WiFi.softAPdisconnect();
        delay(10);
      }
    }
  }
//占位符
  Serial.println("");
 
  //等待下一循环
  delay(5000);
}
