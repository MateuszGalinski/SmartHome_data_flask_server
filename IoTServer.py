from flask import Flask, render_template
from flask import request
import json

app = Flask(__name__)
espDataDictionary = {"humidity": 0.0, "temperature": 0.0}

@app.route("/", methods = ['GET', 'POST'])
def home_page():
    global espDataDictionary
    if request.method == 'POST':
        espData = request.get_json()
        espData = json.dumps(espData)
        espDataDictionary = json.loads(espData)
        print("Humidity: ", espDataDictionary["humidity"], "  Temperature: ", espDataDictionary["temperature"])
    return render_template('home.html', data = espDataDictionary)
    #return render_template('home.html', data = {"humidity": 0.0, "temperature": 0.0})

if __name__ == "__main__":
    app.run(debug=True, port=80)