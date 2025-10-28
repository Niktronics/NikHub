#pragma once

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <NTPClient.h>

class EnviromentService {
    private:
        NTPClient &timeClient;
        void getJsonFromUrl(const char* url, JsonDocument& doc);
        const char* openWeatherAddress = "http://api.openweathermap.org/data/2.5/weather?q=Caivano,it&appid=bce9c8868331b3d8ba16035a5233a091&units=metric&lang=it";
        unsigned long lastWeatherUpdate = 0;
        String lastWeatherDescription = "Caricamento...";
    public:
        EnviromentService(NTPClient &ntp) : timeClient(ntp) {}
        String getTimeHHMM();
        String getWeatherDescription(); 
};