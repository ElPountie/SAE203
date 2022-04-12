#ifndef header_h
#define header_h

String page =
"<!DOCTYPE HTML>\r\n"
"<html lang="en">\r\n"
"<head>\r\n"
"  <meta charset='utf-8'>\r\n"
"  <meta name='viewport' content='width=device-width'>\r\n"
"  <title>Send Text to ESP-01 / NeoMatrix / v2</title>\r\n"
"  <link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7' crossorigin='anonymous'>\r\n"
"  <link rel='stylesheet' href='https://raw.githubusercontent.com/bgrins/spectrum/master/spectrum.css/%22%3E'>/r/n"
"  <style>#sentMsgs{display:inline-block;margin:0 15px 20px;padding:10px 20px;min-height:60px;background-color:#777;color:lime;border:1px solid gray;clear:both;}.adjust-text{margin:20px 0 0;padding:0 20px;}.clearfix{clear:both;}</style>\r\n"
"</head>\r\n\r\n"
"<body style='background:#EFEFEF;'>\r\n"
"\r\n"
"   <form>\r\n"
"     <div class='col-md-4'>\r\n"
"       <h3>Enter Text to Send on the NeoPixel Matrix: <input type='text' id='color-picker'></h3>\r\n"
"       <div class='input-group'>\r\n"
"         <input type='text' name='line' id='line' class='form-control' maxlength='60'>\r\n"
"         <div class='input-group-btn'>\r\n"
"           <button class='btn btn-default' id='send-text'>Send Text</button>\r\n"
"         </div>\r\n"
"       </div>\r\n"
"     </div>\r\n"
"   </form><br>\r\n\r\n"
"   <div class='col-md-4 adjust-text clearfix'><h4>Messages Sent</h4></div>\r\n"
"   <div id='sentMsgs' class='col-md-4' contentEditable='true'></div>\r\n"
"\r\n"
" <script src='https://ajax.googleapis.com/ajax/libs/jquery/2.2.2/jquery.min.js/%22%3E'</script>\r\n"
" <script src='https://raw.githubusercontent.com/bgrins/spectrum/master/spectrum.js/%22%3E'</script>\r\n"
" <script>\r\n"
"   // This will build up a queue and send or just timeout if the messages are too many or the message is too long\r\n"
"   function sendMsg(){\r\n"
"     var line = $('#line');\r\n"
"     var color = '';\r\n"
"     var colorPicker = $('#color-picker');\r\n"
"     var msg = line.val().replace(';','');\r\n"
"     if(colorPicker.val() == ''){ color = '&rgb=80,255,0'; }\r\n"
"     else{ color = '&'+colorPicker.val().replace('(','=').replace(/\)| /g,''); }\r\n"
"\r\n"
"     var url2Send = '/?line='+msg+color;\r\n"
"     line.val('');\r\n"
"     if(typeof msg !== 'undefined' && msg.trim() !== ''){\r\n"
"       $.ajax({ url: url2Send }).done(function(){ $('#sentMsgs').prepend('Message Sent: '+msg+'<br>\n'); console.log('Message Sent: '+msg+' ['+color+']'); });\r\n"
"     }\r\n"
"   }\r\n"
"   $(document).keypress(function(e){ if(e.which === 13){ sendMsg(); e.preventDefault(); } });\r\n"
"   $('#send-text').click(function(e){ sendMsg(); e.preventDefault(); });\r\n"
"   $('#color-picker').spectrum({preferredFormat:'rgb',clickoutFiresChange:true,color:'#50FF00'});\r\n"
" </script>\r\n"
"\r\n"
"</body>\r\n"
"</html>\r\n";

#endif

#define page "<!DOCTYPE html>"
"<html lang'en'>"
"<head>"
    "<meta charset='UTF-8'>"
    "<meta http-equiv='X-UA-Compatible' content='IE=edge'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<link href='./style.css' rel='stylesheet'>"
    "<title>Manager</title>"
    "<style>"
        "@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@100&display=swap');"
        
        "*{"
            "font-family:'Roboto', sans-serif;;"
           " margin: 0;"
            "transition: 2s linear;"
        "}"
        
        "hr{"
            "background-color: black;"
            "height : 5px;"
           " margin : 0;"
       " }"
        
        "."
       ".top{"
            "background-color: rgb(13, 133, 239);"
            "text-align: center;"
            "height : 10rem"
        "}"
        
        ".top h1 {"
            "padding-top: 15%;"
        "}"
        
        ".mid{"
            "display: flex;"
            "justify-content: space-around;"
            "align-items: center;"
            "background-color: rgb(222, 220, 220);"
            "height : 400px ;"
        "}"
        
        "footer{"
            "background-color: black;"
            "width : 100%;"
            "height: 100px;"
        "}"
        
        ".card{"
            "background-color: rgb(202, 200, 200);"
            "height : 60%;"
            "text-align: center;"
            "width : 160px;"
            "border-radius: 5%;"
        "}"
        
        ".card h2{"
            "padding-top: 5%;"
"}</style>"
"</head>"
"<body>"
    "<div class='top'> <h1>Parking Manager : </h1></div>"
    "<hr>"
    "<div class='mid'>"
        "<div class='card'>"
            "<h2>Place 1</h2>"

        "</div>"
        "<div class='card'>"
            "<h2>Place 2</h2>"
        "</div>"
    "</div>"
    "<footer></footer>"
    
"</body>"
"</html>"