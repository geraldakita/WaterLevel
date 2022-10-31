char page[] PROGMEM = R"====(
 <!DOCTYPE html>
<html>

<head>
    <title>Dashboard</title>
    <style>
        body {
            margin-top: 50px;
            font-family: Arial
        }

        body {
            font-size: 20px;
            text-align: center
        }

        .btn {
            display: block;
            width: 280px;
            margin: auto;
            padding: 30px
        }

        .btn {
            font-size: 30px;
            color: black;
            text-decoration: none
        }

        .off {
            background-color: SkyBlue
        }

        .on {
            background-color: LightSteelBlue
        }

        td {
            font-size: 30px;
            margin-top: 50px;
            margin-bottom: 5px
        }

        p {
            font-size: 30px;
            margin-top: 50px;
            margin-bottom: 5px
        }
    </style>
</head>

<body>
    <div style="color: white; background-color: brown; text-align: center; padding: 10px;">
        <h1>Water Level Monitoring</h1>
    </div>

    <table style="width: 100%;">
        <tr>
            <td
                style="color: white; background-color: black; text-align: center; width: fit-content; height: fit-content; padding: 50px;">
                Tank 1<br>
                <p style="font-size: 50%">Enter a unique tempID: <br><input type="text" id="theText1"></p>
                <button onclick="updateByAJAX_dbData1()">Get Info</button>
                <p id="tank1" style="font-size: 50%;"></p>
            </td>
            <td
                style="color: white; background-color: black; text-align: center; width: fit-content; height: fit-content; padding: 50px;">
                Tank 2<br>
                <p style="font-size: 50%">Enter a unique tempID: <br><input type="text" id="theText2"></p>
                <button onclick="updateByAJAX_dbData2()">Get Info</button>
                <p id="tank2" style="font-size: 50%;"></p>
            </td>
        </tr>
    </table><br><br>
    <p id = "waterLevel"></p>
    <div>
        <h1 style="text-align: center">Motor Control</h1>
        <table style="text-align: center; width: 100%;">
            <tr>
                <td style="padding: 10px">Auto Mode</td>
                <td style="padding: 10px">Manual Mode</td>
            </tr>
            <tr>
                <td><button id='AutoStart' onclick='autoStart(id)'>ON
                </button></td>
                <td><button id='ManualStart' onclick='manStart(id)'>START
                </button></td>
            </tr>
            <tr>
                <td></td>
                <td><button id='ManualStop' onclick='manStop(id)'>STOP
                </button></td>
            </tr>

        </table>

    </div>
    <script>
        setInterval(function() {waterLevel();},500);
        function waterLevel(){
          var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById("waterLevel").innerHTML = this.
                        responseText;
            };
            xhr.open('GET', "waterLevel", true);
            xhr.send();
        }
        function autoStart(butn) {
            var URL, variab, text;
            if (butn == 'AutoStart') {
                URL = 'AutoStart';
            }
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById(variab).innerHTML = this.
                        responseText;
            };
            xhr.open('GET', URL, true);
            xhr.send();
        }
        function manStart(butn){
            if (butn == 'ManualStart') {
                URL = 'ManualStart';
            }
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById(variab).innerHTML = this.
                        responseText;
            };
            xhr.open('GET', URL, true);
            xhr.send();
        }
        function manStop(butn){
            if (butn == 'ManualStop') {
                URL = 'ManualStop';
            }
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById(variab).innerHTML = this.
                        responseText;
            };
            xhr.open('GET', URL, true);
            xhr.send();
        }
    </script>
    <script type="text/javascript">
   function updateByAJAX_dbData1(){
      const xhttp=new XMLHttpRequest();
      xhttp.onload=function(){
        document.getElementById("tank1").innerText=this.responseText;
      }
      id=document.getElementById("theText1").value;
      console.log(id);
      xhttp.open("GET", "http://172.20.10.8/waterlevel/db.php?id="+id);
      xhttp.send();
    }
    function updateByAJAX_dbData2(){
      const xhttp=new XMLHttpRequest();
      xhttp.onload=function(){
        document.getElementById("tank2").innerText=this.responseText;
      }
      id=document.getElementById("theText2").value;
      console.log(id);
      xhttp.open("GET", "http://172.20.10.8/waterlevel/db.php?id="+id);
      xhttp.send();
    }

  </script>
</body>








</html>
)====";
