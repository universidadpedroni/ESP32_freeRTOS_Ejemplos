#ifndef WIFIFUNCTIONS_H
#define WIFIFUNCTIONS_H

class wifiFunc{
    public:
        void setIPConfig(const IPAddress& ip, const IPAddress& gateway, const IPAddress& subnet);
        void begin(const char* ssid, const char* password, const char* htmlPath, const char* cssPath);
        void OverTheAirUpdate();
    private:
        IPAddress ip;
        IPAddress gateway;
        IPAddress subnet;

};


#endif