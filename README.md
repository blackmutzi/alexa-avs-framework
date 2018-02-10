# Alexa-AVS Framework
Alexa-Voice-Service-Framework

Project Status: in Development

# planned main features
- [x] AlexaAmazonClient ( to communicate with the Amazon Server )
- [ ] AlexaWebServer ( Web API to trigger AlexaEvents )
- [ ] AlexaQtApplication ( used Web API )
- [ ] AlexaDiscordBot ( used Web API )
# alexa-amazon-client features
- [x] builtin Gstreamer pipeline  ( play Alexa Sounds )
- [x] builtin console ( starting recording to speech with alexa - Commands: start )
- [ ] builtin Cloud-Based WakeWord Recognize-Speech Profile
- [ ] builtin WakeWord Server

# installation
```sh
$ git clone https://github.com/blackmutzi/alexa-avs-framework
$ cd alexa-avs-framework
$ cmake . && make -j 4 && make install
```
# configuration
```sh
$ cd /etc/alexa/
$ mv config-example.json config.json
```
# edit config.json
Follow the steps [here](https://github.com/alexa/alexa-avs-sample-app/wiki/Raspberry-Pi) to create a amazon security profile.

After, edit client_id , client_secret and product_id and save config.json
Start /usr/bin/AlexaAmazonClient and you get a link from app. Copy the Link in your Browser. Login to your Security Profile now.
After, save your code_grant into the config.json and the configuration is finish.

Notice: refresh token must not be set, set automatic from app
```sh
{
"client_id":" YOUR_CLIENT_ID_HERE",
"client_secret":" YOUR_CLIENT_SECRET_HERE",
"code_grant":" YOUR_CODE_GRANT_HERE",
"product_id":" YOUR_PRODUCT_NAME_HERE",
"redirect_uri":"https://localhost:3000/authresponse",
"refresh_token":""
}
```
