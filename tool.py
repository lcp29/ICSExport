import re
import json
import requests
from datetime import datetime
from datetime import timedelta
from ics import Calendar, Event

cookie = 'JSESSIONID=1B4723B2D14A74A1B71528B9D294F9A0; route=cb5f888c9cb0d85c260c8284847d46e6'
url = 'http://jw.hitsz.edu.cn/xszykb/queryxszykbzhou'
year = '2024-2025'
semester = '1'
first_day = '2024-08-26'

# times in a day
times = [(8,  0 , 9,  45),
         (10, 0 , 11, 45),
         (14, 0 , 15, 45),
         (16, 0 , 17, 45),
         (18, 45, 20, 30),
         (20, 45, 22, 30)]

headers = {
    'Accept': '*/*', 
    'Accept-Encoding': 'gzip, deflate', 
    'Accept-Language': 'zh-CN,zh-Hans;q=0.9', 
    'Connection': 'keep-alive', 
    'Content-Length': '22', 
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8', 
    'Cookie': cookie,
    'Host': 'jw.hitsz.edu.cn', 
    'Origin': 'http://jw.hitsz.edu.cn', 
    'Proxy-Connection': 'keep-alive', 
    'Referer': 'http://jw.hitsz.edu.cn/authentication/main', 
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.6 Safari/605.1.15', 
    'X-Requested-With': 'XMLHttpRequest', 
}

payload = {
    'xn': year,
    'xq': semester,
    'zc': '1'
}

semester_calender = Calendar()

for week in range(1, 17):
    # get calender
    payload['zc'] = str(week)
    result = requests.post(url, headers=headers, data=payload)
    result_json = json.loads(result.content.decode('utf-8'))
    result = []
    for item in result_json:
        if item['XB'] != 0:
            key = item['KEY']
            r = re.findall(r'xq([0-9])+_jc([0-9])+', key)
            result += [(item['SKSJ'], week, int(r[0][0]), int(r[0][1]))]
    # print(result)
    # generate ics objects
    monday = datetime.fromisoformat(f'{first_day}T00:00:00+08:00') + timedelta(weeks=week-1)
    print(monday)
    events = []
    for event in result:
        eobj = Event()
        eobj.name = event[0].split('\n')[0]
        eobj.description = event[0]
        starttime = monday + timedelta(days=event[2] - 1, hours=times[event[3] - 1][0], minutes=times[event[3] - 1][1])
        eobj.begin = starttime
        endtime = monday + timedelta(days=event[2] - 1, hours=times[event[3] - 1][2], minutes=times[event[3] - 1][3])
        eobj.end = endtime
        eobj.location = re.findall(r'\[(.*?)\]', eobj.description)[-1]
        semester_calender.events.add(eobj)

with open('semester.ics', 'w+') as f:
    f.writelines(semester_calender.serialize())



