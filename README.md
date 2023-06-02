# MongoDB Nodemcu Integration

This project demonstrates the integration of MongoDB with Arduino using the ESP8266 WiFi module. It allows you to perform various MongoDB operations such as finding, inserting, updating, and deleting documents in a MongoDB database.

## Prerequisites

- Arduino IDE installed
- ESP8266 WiFi module
- WiFi network credentials
- MongoDB Atlas account
- MongoDB API URL and API key

## Getting Started

1. Clone or download the repository to your local machine.

2. Open the Arduino IDE.

3. Connect your Arduino board to your computer.

4. Install the necessary libraries by navigating to **Sketch > Include Library > Manage Libraries** and searching for the following libraries:
   - `ESP8266WiFi`
   - `ESP8266WiFiMulti`
   - `ESP8266HTTPClient`
   - `WiFiClientSecureBearSSL`

5. Modify the following variables in the `main.ino` file:
   - `WIFI_SSID`: Set this to your WiFi network name.
   - `WIFI_PASSWORD`: Set this to your WiFi network password.
   - `MONGODB_API_URL`: Set this to your MongoDB API URL.
   - `MONGODB_API_KEY`: Set this to your MongoDB API key.

6. Upload the code to your Arduino board by clicking on the **Upload** button in the Arduino IDE.

7. Open the Serial Monitor by clicking on the **Serial Monitor** button in the Arduino IDE.

8. Power on the ESP8266 WiFi module and wait for it to establish a connection to your WiFi network. The Serial Monitor will display the connection status.

9. Once the WiFi connection is established, the code will connect to the MongoDB database and perform various MongoDB operations.

10. View the Serial Monitor output to see the results of the MongoDB operations.

11. The code will repeat the MongoDB operations every 5 seconds. You can adjust the delay by modifying the `delay(5000);` statement in the `loop()` function.

## Usage

The code demonstrates the usage of the following MongoDB operations:

- `findOne`: Retrieves a single document that matches the specified filter.
- `insertOne`: Inserts a single document into the specified collection.
- `updateOne`: Updates a single document that matches the specified filter with the provided updates.
- `deleteOne`: Deletes a single document that matches the specified filter.
- `findMany`: Retrieves multiple documents that match the specified filter.
- `insertMany`: Inserts multiple documents into the specified collection.
- `updateMany`: Updates multiple documents that match the specified filter with the provided updates.
- `deleteMany`: Deletes multiple documents that match the specified filter.

You can customize the MongoDB database, collection, and filter parameters in the code to suit your specific requirements.

## Troubleshooting

- If you encounter any issues with the WiFi connection, ensure that you have provided the correct WiFi network credentials.
- Double-check that you have entered the correct MongoDB API URL and API key.
- If you're unable to establish a connection to the MongoDB database, ensure that your network allows outbound connections to the MongoDB API URL.
