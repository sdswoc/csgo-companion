var express= require('express');
var app= express();

app.use('/css', express.static(__dirname + '/css'));
app.use('/js', express.static(__dirname + '/js'));
app.use('/img', express.static(__dirname + '/img'));
app.use('/html' , express.static(__dirname + '/html'));

var server = app.listen(8081, function() {
  console.log('Magic is happening on port ' + 8081);
});

app.get('/', function(req, res) {
  res.sendFile(__dirname + "/html/join.htm");
});