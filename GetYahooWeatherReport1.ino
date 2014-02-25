

#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information
// as described in the footer comment below


// the address for which a weather forecast will be retrieved
String ADDRESS_FOR_FORECAST = "721 Broadway New York City, NY 10003";

int numRuns = 1;   // execution count, so that this doesn't run forever
int maxRuns = 10;  // max number of times the Yahoo WeatherByAddress Choreo should be run
String inString = ""; 

void setup() {
  Serial.begin(9600);

  // for debugging, wait until a serial console is connected
  delay(4000);
  while (!Serial);
  Bridge.begin();

}

void loop()
{
  // while we haven't reached the max number of runs...
  if (numRuns <= maxRuns) {

    // print status
    // Serial.println("Running GetWeatherByAddress - Run #" + String(numRuns++) + "...");

    // create a TembooChoreo object to send a Choreo request to Temboo
    TembooChoreo GetWeatherByAddressChoreo;

    // invoke the Temboo client
    GetWeatherByAddressChoreo.begin();

    // add your temboo account info
    GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);

    // set the name of the choreo we want to run
    GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");

    // set choreo inputs; in this case, the address for which to retrieve weather data
    // the Temboo client provides standardized calls to 100+ cloud APIs
    GetWeatherByAddressChoreo.addInput("Address", ADDRESS_FOR_FORECAST);

    // add an output filter to extract the name of the city.
    //GetWeatherByAddressChoreo.addOutputFilter("city", "/rss/channel/yweather:location/@city", "Response");

    // add an output filter to extract the current temperature
    //GetWeatherByAddressChoreo.addOutputFilter("temperature", "/rss/channel/item/yweather:condition/@temp", "Response");
    GetWeatherByAddressChoreo.addOutputFilter("code", "/rss/channel/item/yweather:condition/@code", "Response");
    // add an output filter to extract the date and time of the last report.
    //GetWeatherByAddressChoreo.addOutputFilter("date", "/rss/channel/item/yweather:condition/@date", "Response");

    // run the choreo
    GetWeatherByAddressChoreo.run();

    // when the choreo results are available, print them to the serial monitor
    while (GetWeatherByAddressChoreo.available()) {
      GetWeatherByAddressChoreo.readStringUntil('e');
      //GetWeatherByAddressChoreo.readStringUntil('e');
      //GetWeatherByAddressChoreo.readStringUntil('e');


      String c = GetWeatherByAddressChoreo.readString();
      int num = c.toInt();
      //Serial.print(c);
      
      if  (c == "20"){
      Serial.print("test");
      }
      else{
        Serial.print("not working");
      }
      //Serial.println(c.toInt());


    }
    GetWeatherByAddressChoreo.close();

  }

  //Serial.println("Waiting...");
  //Serial.println("");
  delay(30000); // wait 30 seconds between GetWeatherByAddress calls
}


