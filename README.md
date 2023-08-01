# SmartHome_data_flask_server

## ESP8266 Part of a program:
This ESP8266 program is designed to read data from a DHT11 temperature and humidity sensor and send this data to a server using HTTP POST requests. 
The program requires the "ESP8266WiFi" library for Wi-Fi connectivity, "ESP8266HTTPClient" for HTTP communication
and "DHT" for interfacing with the DHT11 sensor.

The necessary libraries are included:

ESP8266WiFi.h: Provides functions to connect to a Wi-Fi network.
ESP8266HTTPClient.h: Enables HTTP communication with a server.
WiFiClient.h: Implements a simple client for Wi-Fi connections.
DHT.h: Enables communication with the DHT11 temperature and humidity sensor and can be found in following repository: https://github.com/markruys/arduino-DHT

Constants and variables are defined:

DHT11_PIN: The GPIO pin number to which the DHT11 sensor is connected.
dht_sensor: An instance of the DHT class to interact with the DHT11 sensor.
ssid: The name of the Wi-Fi network (replace "YOUR SSID" with your actual SSID).
password: The password of the Wi-Fi network (replace "YOUR PASSWORD" with your actual password).
serverName: The URL of the server to which the data will be sent.

During setup():

The serial communication is initialized for debugging purposes.
The DHT sensor is set up to use the specified pin.
The ESP8266 connects to the specified Wi-Fi network.
The function waits until the Wi-Fi connection is established and prints dots to indicate progress.
After successful connection, the local IP address of the ESP8266 is printed.

The loop() function:

First checks if the Wi-Fi connection is still active.
If Wi-Fi is connected, it reads the temperature and humidity from the DHT11 sensor.
The data is then sent to the server using the sendJson() function.
The temperature and humidity values are also printed to the serial monitor for debugging.

The sendJson() function is responsible for sending data to the server:

A WiFiClient and HTTPClient instance are created.
The HTTP headers are set to indicate that the server should expect JSON data.
The temperature and humidity data are converted to a JSON format.
An HTTP POST request is made to the server with the JSON data.
The HTTP response code is printed for debugging purposes.
The HTTP and WiFi clients are closed.
Important Note: Before using this program, make sure to replace "YOUR SSID," "YOUR PASSWORD," and "Url of server showing data" with the actual values relevant to your Wi-Fi network and server URL.

Additionally, ensure that the server receiving the data is set up to handle incoming JSON data and properly store or process it as per your requirements.

## Flask part of a program:
This is a Python program using the Flask web framework. 
It creates a web server that receives data from an ESP8266 (or any client) in JSON format, 
stores the data in a global dictionary, and then displays the received data on a web page.

Import necessary modules:

Flask: This class is used to create the web application.
render_template: This function is used to render HTML templates.
request: This object contains the data from the client's HTTP request.
Create the Flask app and initialize a global dictionary:

app = Flask(__name__): This creates the Flask application.
espDataDictionary: This dictionary will store the data received from the ESP8266.
Define the route and the associated function for the home page:

@app.route("/", methods=['GET', 'POST']): This decorator binds the URL path "/" to the home_page function. The function will be called when a client accesses the root URL of the web server using either GET or POST methods.
def home_page():: This is the function that handles the request.
Process the POST request from the ESP8266:

if request.method == 'POST':: This checks if the incoming request is a POST request.
espData = request.get_json(): This retrieves the JSON data sent by the ESP8266 from the request object.
espData = json.dumps(espData): The received JSON data is converted to a JSON-formatted string.
espDataDictionary = json.loads(espData): The JSON-formatted string is converted back to a Python dictionary and stored in the espDataDictionary global variable.
The received data (humidity and temperature) is then printed on the server's console for debugging purposes.

Render the HTML template:

render_template('home.html', data=espDataDictionary): This function renders the "home.html" template with the data from espDataDictionary. The data will be accessible in the HTML template using the variable name "data."
Run the Flask app:

if __name__ == "__main__":: This ensures that the Flask app runs only if the script is executed directly and not when imported as a module.
app.run(debug=True, port=80): This starts the Flask development server with debugging enabled and listening on port 80. The web application will be accessible at http://127.0.0.1:80/ but host can be changed
to make easier to run the server on local host.

Important Note:

Make sure to have the Flask framework installed in your Python environment before running this script. You can install Flask using pip install Flask.
The code assumes that the ESP8266 sends JSON data with "humidity" and "temperature" fields to the root URL of the Flask web server. Ensure that your ESP8266 program sends the JSON data correctly to this route.
The data received from the ESP8266 will be displayed on the "home.html" template. Make sure you have the appropriate HTML template to render the data properly (exemplary template is provided in this repository).
