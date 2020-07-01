String webpage = R"(
<!DOCTYPE html>
<html>
<head>
<title>RGB control</title>
<meta name='mobile-web-app-capable' content='yes' />
<meta name='viewport' content='width=device-width' />
</head><body style='margin: 0px; padding: 0px;'>
<center>
<h1 style='color:#08d993'><span style='color:#c03460'>Ruba</span> & <span style='color:#c3b261'>Tuqa</span> </h1>
<h2>
<span style='color:#e80703'>R</span>
<span style='color:#fc7c00'>G</span>
<span style='color:#d6ca44'>B</span>
<span style='color:#76ed00'> P</span>
<span style='color:#00fa80'>R</span>
<span style='color:#00dcd3'>O</span>
<span style='color:#009ef7'>J</span>
<span style='color:#b801f0'>E</span>
<span style='color:#ef0198'>C</span>
<span style='color:#fc016f'>T</span>
</h2>
<p><a href="/"><button style="background-color:red; border: none; color: white; padding: 8px 20px; text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;" class="button">OFF</button></a></p></center>
<canvas id="colorspace"></canvas></body>
<script type="text/javascript">
(function () {
var canvas = document.getElementById("colorspace");
var ctx = canvas.getContext("2d");
function drawCanvas() {
var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);
for(var i=0; i <= 360; i+=10) {
colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');
 }
ctx.fillStyle = colours;
ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);
var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);
luminance.addColorStop(0, '#ffffff');
luminance.addColorStop(0.05, '#ffffff');
luminance.addColorStop(0.5, 'rgba(0,0,0,0)');
luminance.addColorStop(0.95, '#000000');
luminance.addColorStop(1, '#000000');
ctx.fillStyle = luminance;
ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);
 }
var eventLocked = false;
function handleEvent(clientX, clientY) {
if(eventLocked) {
return;
 }
 function colourCorrect(v) {
return Math.round(1023-(v*v)/64);
 }
 var data = ctx.getImageData(clientX, clientY, 1, 1).data;
 var params = [
 'r=' + colourCorrect(data[0]),
 'g=' + colourCorrect(data[1]),
 'b=' + colourCorrect(data[2])
].join('&');
 var req = new XMLHttpRequest();
 req.open('POST', '?' + params, true);
 req.send();
 eventLocked = true;
 req.onreadystatechange = function() {
 if(req.readyState == 4) {
 eventLocked = false;
 }
 }
 }
canvas.addEventListener('click', function(event) {
 handleEvent(event.clientX, event.clientY, true);
 }, false);
 canvas.addEventListener('touchmove', function(event){
 handleEvent(event.touches[0].clientX, event.touches[0].clientY);
}, false);
 function resizeCanvas() {
 canvas.width = window.innerWidth;
canvas.height = window.innerHeight;
 drawCanvas();
 }
 window.addEventListener('resize', resizeCanvas, false);
 resizeCanvas();
 drawCanvas();
 document.ontouchmove = function(e) {e.preventDefault()};
 })();
</script>
</html>

)";
