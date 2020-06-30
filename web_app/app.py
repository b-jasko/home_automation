from flask import Flask, render_template, request
import requests
import json

sensors_data = ""

app = Flask(__name__)


@app.route('/')
def hello_world():
    return render_template("home.html")

@app.route('/send')
def send():
    window_shutter = request.args['windowShutter']

    url = "http://192.168.43.181/body"
    # url = "http://192.168.0.38/body"

    if window_shutter == 'OPEN':
        data = 'a'
    elif window_shutter == 'CLOSE':
        data = 'b'
    elif window_shutter == 'HOLD':
        data = 'c'


    r = requests.post(url=url, data=data)

    return "nothing"

@app.route('/writedata', methods = ['GET', 'POST'])
def writedata():
    global sensors_data
    sensors_data = request.get_data().decode('utf_8')
    # sensors_data = request.data
    return "nothing"

@app.route('/readdata', methods = ['GET', 'POST'])
def read():
    global sensors_data
    sensors_data_table = sensors_data.split(",")
    print(sensors_data_table)
    x = {
        "distance":sensors_data_table[0][0:5],
        "temperature":sensors_data_table[1][0:5]
    }
    sensors_data_json = json.dumps(x)
    return sensors_data_json

if __name__ == '__main__':
    app.run()
