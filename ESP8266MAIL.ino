#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465


#define sender_email "esp.ghs19202@gmail.com"
#define sender_password "ernx xaiv yxns cagx"

#define Recipient_email "abdelrahman.ibrahim.abuessa@gmail.com"


SMTPSession smtp;

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  smtp.debug(1);


  ESP_Mail_Session session;


  session.server.host_name = SMTP_server ;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;


  message.sender.name = "ESP8266";
  message.sender.email = sender_email;
  message.subject = "ESP8266 Testing Email";
  message.addRecipient("Microcontrollerslab",Recipient_email);

   //Send HTML message
  String htmlMsg = "<div style=\"color:#0000FF;\"><h1>MOHEMMAT!</h1><h1>19202 ON TOP</h1></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit; 

 /* 
  //Send simple text message
  String textMsg = "Hello Microcontrollerslab! This is a simple text sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit; */


  if (!smtp.connect(&session))
    return;


  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
 
}

void loop(){

}