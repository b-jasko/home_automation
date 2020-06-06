from flask import Flask, render_template, request
import requests

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


if __name__ == '__main__':
    app.run()
