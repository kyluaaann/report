from machine import Pin
from machine import UART
import urequests, ujson
import xtools, utime
xtools.connect_wifi_led()
country = "TW"
API_key = "f284445f25363bba70c13336aebf2eca"
def get_temperature(city):#取得城市的天氣資料
    url  = "http://api.openweathermap.org/data/2.5/weather?"
    url += "q=" + city + "," + country   # 城市與國別
    url += "&units=metric&lang=zh_tw&"   # 單位
    url += "appid=" + API_key
    try:
        response = urequests.get(url)
        data = ujson.loads(response.text)
        main = data["main"]
        return main["temp"]
    except:
        print("錯誤")
        return 0

com = UART(2, 9600, tx=17, rx=16)#設定資料
com.init(9600)
print('MicroPython Ready...')  # 設定完成
while True:
    if com.any() > 0:
        utime.sleep(1)
        city=com.readline().decode().strip()#從8051讀取地區資訊並從byte轉為字串
        temp = get_temperature(city)#取得城市的天氣資料
        print("儲存溫度資料: ", temp,city)
        strtemp=str(temp)#將數字轉為字串
        if len(strtemp)==2:#不滿5個字補空格
            strtemp=strtemp+"   "
        if len(strtemp)==4:#不滿5個字補空格
            strtemp=strtemp+" "
        com.write(strtemp.encode())#寫入8051