bool loadConfig() {                                                // Завантаження даних збереженних в файлі config.json
  File configFile = SPIFFS.open("/config.json", "r");              // Відкриваемо файл на читання
  if(!configFile) {                                                // якщо файл не знайдено ствоюємого його та записуємо в ньго данні з наших змінних
    if(printCom) Serial.println("Failed to open config file");
    saveConfig();                                                  // Створюємо файл
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  size_t size = configFile.size();                                 // Перевіряємо ромір файлу, будемо використовувати файл довжиною в 1024 байта
  if(size > 2048) {
    if(printCom) Serial.println("Config file size is too large");
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  jsonConfig = configFile.readString();                            // завантажуємо файл конфігурації в глобальну змінну
  DynamicJsonBuffer jsonBuffer;                                    // Резервуємо память для json обекту буфер може розти по мірі необхідності переважно для ESP8266 
  configFile.close();
  JsonObject& root = jsonBuffer.parseObject(jsonConfig);
  ssidAP = root["ssidAP"].as<String>();
  passwordAP = root["passwordAP"].as<String>();                     // Так отримуємо рядок
  ssid = root["ssid"].as<String>();
  password = root["password"].as<String>();
  ntpServerName = root["ntpServerName"].as<String>();
  timeZone = root["timeZone"];                                     // Так отримуємо число
  isDayLightSaving = root["isDayLightSaving"];
  kuOn = root["kuOn"];
  kuOff = root["kuOff"];
  weatherKey = root["weatherKey"].as<String>();
  weatherHost = root["weatherHost"].as<String>();
  cityID = root["cityID"].as<String>();
  weatherLang = root["weatherLang"].as<String>();
  outForecast = root["outForecast"];
  timeScrollStart = root["timeScrollStart"];
  timeScrollStop = root["timeScrollStop"];
  timeScrollSpeed = root["timeScrollSpeed"];
  ds18b20 = root["ds18b20"];
  ds18b20Out = root["ds18b20Out"];
  rotate0 = root["rotate0"];
  rotate1 = root["rotate1"];
  updateOTA = root["updateOTA"];
  volBrightnessD = root["volBrightnessD"];
  volBrightnessN = root["volBrightnessN"];
  timeDay = root["timeDay"];
  timeNight = root["timeNight"];
  volBrightnessAuto = root["volBrightnessAuto"];
  clockNight = root["clockNight"];
  buzzerSet = root["buzzerSet"];
  mqttOn = root["mqttOn"];
  snprintf(mqtt_server, 24, "%s", (root["mqtt_server"].as<String>()).c_str());
  mqtt_port = root["mqtt_port"];
  snprintf(mqtt_user, 24, "%s", (root["mqtt_user"].as<String>()).c_str());
  snprintf(mqtt_pass, 24, "%s", (root["mqtt_pass"].as<String>()).c_str());
  snprintf(mqtt_name, 24, "%s", (root["mqtt_name"].as<String>()).c_str());
  snprintf(mqtt_pub_temp, 24, "%s", (root["mqtt_pub_temp"].as<String>()).c_str());
  snprintf(mqtt_pub_tempUl, 24, "%s", (root["mqtt_pub_tempUl"].as<String>()).c_str());
  snprintf(mqtt_pub_hum, 24, "%s", (root["mqtt_pub_hum"].as<String>()).c_str());
  snprintf(mqtt_pub_press, 24, "%s", (root["mqtt_pub_press"].as<String>()).c_str());
  snprintf(mqtt_pub_alt, 24, "%s", (root["mqtt_pub_alt"].as<String>()).c_str());
  snprintf(mqtt_sub, 24, "%s", (root["mqtt_sub"].as<String>()).c_str());
  snprintf(mqtt_sub_inform, 24, "%s", (root["mqtt_sub_inform"].as<String>()).c_str());
  printCom = root["printCom"];
  sensorDom = root["sensorDom"];
  sensorUl = root["sensorUl"];
  sensorHumi = root["sensorHumi"];
  sensorPrAl = root["sensorPrAl"];
  lang = root["lang"];
  alarme[0][0] = root["al_0_0"];
  alarme[0][1] = root["al_0_1"];
  alarme[0][2] = root["al_0_2"];
  alarme[1][0] = root["al_1_0"];
  alarme[1][1] = root["al_1_1"];
  alarme[1][2] = root["al_1_2"];
  alarme[2][0] = root["al_2_0"];
  alarme[2][1] = root["al_2_1"];
  alarme[2][2] = root["al_2_2"];
  alarme[3][0] = root["al_3_0"];
  alarme[3][1] = root["al_3_1"];
  alarme[3][2] = root["al_3_2"];
  alarme[4][0] = root["al_4_0"];
  alarme[4][1] = root["al_4_1"];
  alarme[4][2] = root["al_4_2"];
  memory_date[0][0] = root["md_0_0"];
  memory_date[0][1] = root["md_0_1"];
  memory_date[1][0] = root["md_1_0"];
  memory_date[1][1] = root["md_1_1"];
  memory_date[2][0] = root["md_2_0"];
  memory_date[2][1] = root["md_2_1"];
  memory_date[3][0] = root["md_3_0"];
  memory_date[3][1] = root["md_3_1"];
  memory_date[4][0] = root["md_4_0"];
  memory_date[4][1] = root["md_4_1"];
  memory_date[5][0] = root["md_5_0"];
  memory_date[5][1] = root["md_5_1"];
  memory_date[6][0] = root["md_6_0"];
  memory_date[6][1] = root["md_6_1"];
  memory_date[7][0] = root["md_7_0"];
  memory_date[7][1] = root["md_7_1"];
  memory_date[8][0] = root["md_8_0"];
  memory_date[8][1] = root["md_8_1"];
  snprintf(memory_date_mes0, 51, "%s", (root["md_0_2"].as<String>()).c_str());
  snprintf(memory_date_mes1, 51, "%s", (root["md_1_2"].as<String>()).c_str());
  snprintf(memory_date_mes2, 51, "%s", (root["md_2_2"].as<String>()).c_str());
  snprintf(memory_date_mes3, 51, "%s", (root["md_3_2"].as<String>()).c_str());
  snprintf(memory_date_mes4, 51, "%s", (root["md_4_2"].as<String>()).c_str());
  snprintf(memory_date_mes5, 51, "%s", (root["md_5_2"].as<String>()).c_str());
  snprintf(memory_date_mes6, 51, "%s", (root["md_6_2"].as<String>()).c_str());
  snprintf(memory_date_mes7, 51, "%s", (root["md_7_2"].as<String>()).c_str());
  snprintf(memory_date_mes8, 51, "%s", (root["md_8_2"].as<String>()).c_str());
  memory_hour_start = root["memory_hour_start"];
  memory_hour_end = root["memory_hour_end"];
  fontCLOCK = root["fontCLOCK"];
  fontSizeCLOCK = root["fontSizeCLOCK"];
  fontSizeData = root["fontSizeData"];
  textDown = root["textDown"];
  dataDown = root["dataDown"];
  corrTempD = root["corrTempD"];
  corrTempU = root["corrTempU"];
  corrHumi  = root["corrHumi"];
  corrPress = root["corrPress"];
  NUM_MAX0 = root["NUM_MAX0"];
  NUM_MAX1 = root["NUM_MAX1"];
  save2time = root["save2time"];
  if(printCom) {
    printTime();
    Serial.print("Load Config : ");
    Serial.println(jsonConfig);
  }
  return true;
}
//=================================================================
bool saveConfig() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);
  json["ssidAP"] = ssidAP;
  json["passwordAP"] = passwordAP;
  json["ssid"] = ssid;
  json["password"] = password;
  json["ntpServerName"] = ntpServerName;
  json["timeZone"] = timeZone;
  json["isDayLightSaving"] = isDayLightSaving;
  json["kuOn"] = kuOn;
  json["kuOff"] = kuOff;
  json["weatherKey"] = weatherKey;
  json["weatherHost"] = weatherHost;
  json["cityID"] = cityID;
  json["weatherLang"] = weatherLang;
  json["outForecast"] = outForecast;
  json["timeScrollStart"] = timeScrollStart;
  json["timeScrollStop"] = timeScrollStop;
  json["timeScrollSpeed"] = timeScrollSpeed;
  json["ds18b20"] = ds18b20;
  json["ds18b20Out"] = ds18b20Out;
  json["rotate0"] = rotate0;
  json["rotate1"] = rotate1;
  json["updateOTA"] = updateOTA;
  json["volBrightnessD"] = volBrightnessD;
  json["volBrightnessN"] = volBrightnessN;
  json["timeDay"] = timeDay;
  json["timeNight"] = timeNight;
  json["volBrightnessAuto"] = volBrightnessAuto;
  json["clockNight"] = clockNight;
  json["buzzerSet"] = buzzerSet;
  json["mqttOn"] = mqttOn;
  json["mqtt_server"] = mqtt_server;
  json["mqtt_port"] = mqtt_port;
  json["mqtt_user"] = mqtt_user;
  json["mqtt_pass"] = mqtt_pass;
  json["mqtt_name"] = mqtt_name;
  json["mqtt_pub_temp"] = mqtt_pub_temp;
  json["mqtt_pub_tempUl"] = mqtt_pub_tempUl;
  json["mqtt_pub_hum"] = mqtt_pub_hum;
  json["mqtt_pub_press"] = mqtt_pub_press;
  json["mqtt_pub_alt"] = mqtt_pub_alt;
  json["mqtt_sub"] = mqtt_sub;
  json["mqtt_sub_inform"] = mqtt_sub_inform;
  json["printCom"] = printCom;
  json["sensorDom"] = sensorDom;
  json["sensorUl"] = sensorUl;
  json["sensorHumi"] = sensorHumi;
  json["sensorPrAl"] = sensorPrAl;
  json["lang"] = lang;
  json["al_0_0"] = alarme[0][0];
  json["al_0_1"] = alarme[0][1];
  json["al_0_2"] = alarme[0][2];
  json["al_1_0"] = alarme[1][0];
  json["al_1_1"] = alarme[1][1];
  json["al_1_2"] = alarme[1][2];
  json["al_2_0"] = alarme[2][0];
  json["al_2_1"] = alarme[2][1];
  json["al_2_2"] = alarme[2][2];
  json["al_3_0"] = alarme[3][0];
  json["al_3_1"] = alarme[3][1];
  json["al_3_2"] = alarme[3][2];
  json["al_4_0"] = alarme[4][0];
  json["al_4_1"] = alarme[4][1];
  json["al_4_2"] = alarme[4][2];
  json["md_0_0"] = memory_date[0][0];
  json["md_0_1"] = memory_date[0][1];
  json["md_1_0"] = memory_date[1][0];
  json["md_1_1"] = memory_date[1][1];
  json["md_2_0"] = memory_date[2][0];
  json["md_2_1"] = memory_date[2][1];
  json["md_3_0"] = memory_date[3][0];
  json["md_3_1"] = memory_date[3][1];
  json["md_4_0"] = memory_date[4][0];
  json["md_4_1"] = memory_date[4][1];
  json["md_5_0"] = memory_date[5][0];
  json["md_5_1"] = memory_date[5][1];
  json["md_6_0"] = memory_date[6][0];
  json["md_6_1"] = memory_date[6][1];
  json["md_7_0"] = memory_date[7][0];
  json["md_7_1"] = memory_date[7][1];
  json["md_8_0"] = memory_date[8][0];
  json["md_8_1"] = memory_date[8][1];
  json["md_0_2"] = memory_date_mes0;
  json["md_1_2"] = memory_date_mes1;
  json["md_2_2"] = memory_date_mes2;
  json["md_3_2"] = memory_date_mes3;
  json["md_4_2"] = memory_date_mes4;
  json["md_5_2"] = memory_date_mes5;
  json["md_6_2"] = memory_date_mes6;
  json["md_7_2"] = memory_date_mes7;
  json["md_8_2"] = memory_date_mes8;
  json["memory_hour_start"] = memory_hour_start;
  json["memory_hour_end"] = memory_hour_end;
  json["fontCLOCK"] = fontCLOCK;
  json["fontSizeCLOCK"] = fontSizeCLOCK;
  json["fontSizeData"] = fontSizeData;
  json["textDown"] = textDown;
  json["dataDown"] = dataDown;
  json["corrTempD"] = corrTempD;
  json["corrTempU"] = corrTempU;
  json["corrHumi"] = corrHumi;
  json["corrPress"] = corrPress;
  json["NUM_MAX0"] = NUM_MAX0;
  json["NUM_MAX1"] = NUM_MAX1;
  json["save2time"] = save2time;
  jsonConfig = "";
  json.printTo(jsonConfig);
  File configFile = SPIFFS.open("/config.json", "w");                // Відкриваємо файл для запису
  if(!configFile) {
    configFile.close();
    return false;
  }
  json.printTo(configFile);
  if(printCom) {
    printTime();
    Serial.print("Save Config : ");
    Serial.println(jsonConfig);
  }
  configFile.close();
  bip();
  return true;
}
//----------------------------------------------------------------------------
bool loadTimeFFS() {
  File timeFile = SPIFFS.open("/time.json", "r");
  if(!timeFile) {
    if(printCom) Serial.println("Failed to open time file");
    saveTimeFFS();
    timeFile.close();
    return false;
  }
  size_t size = timeFile.size();
  if(size>1024) {
    if(printCom) Serial.println("Time file size is too large");
    timeFile.close();
    return false;
  }
  jsonTime = timeFile.readString();
  DynamicJsonBuffer jsonBuffer;
  timeFile.close();
  JsonObject& root = jsonBuffer.parseObject(jsonTime);
  hour = root["hour"];
  minute = root["minute"];
  dayOfWeek = root["dayOfWeek"];
  day = root["day"];
  month = root["month"];
  year = root["year"];
  if(printCom) {
    printTime();
    Serial.print("Load Time : ");
    Serial.println(jsonTime);
  }
  return true;
}
//=================================================================
bool saveTimeFFS() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(jsonTime);
  json["hour"] = hour;
  json["minute"] = minute;
  json["dayOfWeek"] = dayOfWeek;
  json["day"] = day;
  json["month"] = month;
  json["year"] = year;
  jsonTime = "";
  json.printTo(jsonTime);
  File timeFile = SPIFFS.open("/time.json", "w");                // Відкриваємо файл для запису
  if(!timeFile) {
    timeFile.close();
    return false;
  }
  json.printTo(timeFile);
  if(printCom) {
    printTime();
    Serial.print("Save Time : ");
    Serial.println(jsonTime);
  }
  timeFile.close();
  return true;
}
