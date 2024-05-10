#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "DIONE"                            // Nome da rede WIFI
#define PASSWORD "Xdrcftbhu2@"                      // Senha da rede WIFI
#define TOKEN "BBUS-ISxJVVFRH9aBqnp1aG8YQn1oS4lb5h" // TOKEN de acesso a Ubidots
#define MQTT_CLIENT_NAME "dione"                    // Nome do cliente MQTT

/****************************************
 * Definir constantes
 ****************************************/
#define VARIABLE_LABEL "myecg" // Rótulo da variável
#define DEVICE_LABEL "esp8266" // Nome do dispositivo

#define SENSOR A0 // Define A0 como SENSOR

char mqttBroker[] = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char str_sensor[10];

bool wifiStatusDisplayed = false; // Variável para controlar se o status do Wi-Fi foi exibido

/****************************************
 * Funções Auxiliares
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect()
{
  // Loop para reconectar
  while (!client.connected())
  {
    Serial.println("Attempting MQTT connection...");

    // Tentar conectar
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, ""))
    {
      Serial.println("Connected");
    }
    else
    {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Aguardar 2 segundos antes de tentar novamente
      delay(2000);
    }
  }
}

/****************************************
 * Configuração do LCD
 ****************************************/
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C do LCD 0x27, 16 colunas e 2 linhas

/****************************************
 * Funções principais
 ****************************************/
void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Atribui o pino como INPUT
  pinMode(SENSOR, INPUT);

  Serial.println();
  Serial.print("Waiting for WiFi...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);

  // Inicialização do LCD
  lcd.init();
  lcd.backlight();
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");                           // Limpa a carga útil
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL);         // Adiciona o rótulo da variável

  float myecg = analogRead(SENSOR);

  /* Ajuste a precisão para exibir mais casas decimais */
  dtostrf(myecg, 6, 3, str_sensor);

  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adiciona o valor
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);

  // Verificar status da conexão Wi-Fi
  if (!wifiStatusDisplayed && WiFi.status() == WL_CONNECTED)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi: Conectado");
    wifiStatusDisplayed = true;
    delay(2000); // Aguardar 2 segundos
  }
  else
  {
    // Exibir ritmo cardíaco no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ritmo card.: ");
    lcd.setCursor(0, 1);
    lcd.print(str_sensor);
    delay(500); // Aguardar 2 segundos
  }
}
