import json
from urllib.request import urlopen

import requests
import urllib3
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

APP_KEY = ""
APP_SECRET = ""

header = {"content-type": "application/x-www-form-urlencoded"}
param = {"grant_type":"client_credentials", "appkey":APP_KEY, "appsecretkey":APP_SECRET,"scope":"oob"}
PATH = "oauth2/token"
BASE_URL = "https://openapi.ebestsec.co.kr:8080"
    
URL = f"{BASE_URL}/{PATH}"

request = requests.post(URL, verify=False, headers=header, params=param)
ACCESS_TOKEN = request.json()["access_token"]
header = {
    "content-type":"application/json; charset=utf-8",
    "authorization": f"Bearer {ACCESS_TOKEN}",
    "tr_cd":"t0424",
    "tr_cont":"N",
    "tr_cont_key":"",
}

body = {
    "t0424InBlock" :
    {
        "prcgb" : "",
        "chegb" : "",
        "dangb" : "",
        "charge" : "",
        "cts_expcode" : ""
    }
}

PATH = "stock/accno"
URL = f"{BASE_URL}/{PATH}"

requset = requests.post(URL, headers=header, data=json.dumps(body))
requset.json()

print(requset.json()["t0424OutBlock"])