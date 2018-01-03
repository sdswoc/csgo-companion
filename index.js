var express = require('express');
var bodyParser = require('body-parser');
var multer = require('multer');
var upload = multer();
var app = express();
var fs = require('fs');
var http = require('http');
var x = http.Server(app);
var io = require('socket.io')(x);

app.use('/css', express.static(__dirname + '/css'));
app.use('/js', express.static(__dirname + '/js'));
app.use('/img', express.static(__dirname + '/img'));
//app.use('/html' , express.static(__dirname + '/html'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true })); 
app.use(upload.array()); 
app.use(express.static('public'));

x.listen(8081, function() {
  console.log('Magic is happening on port ' + 8081);
});

app.get('/', function(req, res) {

   //console.log(req);
   if(fs.existsSync('user.JSON')) {
   	res.redirect('/html/join.htm');

   }
   else {
   	res.sendFile(__dirname + "/html/first.htm");
   }
});

app.get('/user.JSON' , function( req, res ) {
	res.sendFile(__dirname + "/user.JSON");
});

app.post('/html/join.htm', function(req,res) {
	
	var str= JSON.stringify(req.body);
	fs.writeFile('user.JSON' , " user = " + str , function(err) {
		if (err) {
      		return console.error(err);
   		}
	});
	res.redirect('/html/join.htm');
});

app.post('/html/admin_lobby.htm' , function(req,res) {
	var s_name = req.body.s_name;
	var map = req.body.map;
	var s_pwd = req.body.s_pwd;

});

app.get('/check',  function(req,res) {
	var x ='{ "s_name":"Mera Server" , "map":"blabla" , "ip":"127.0.0.1" , "admin":"Kanav" }';
	res.send(x);
	console.log("ping");
});

app.get('/html/join.htm',  function(req,res) {
	res.sendFile(__dirname + "/html/join.htm");
		var isDone = false;
		var options = {
	  		host: '127.0.0.1' ,
	  		path: '/check',
	  		port: '8081'
		};
		http.get(options, function(res) {
			var body="";
	  		res.on('data', function(chunk) {
	        	body+=chunk;
	  		}).on('end', function() {
	    		console.log(body);
	    		io.on('connection', function(socket) {
	    			if(isDone==false)
	    			{
	    				socket.emit('avail', body);
	    				console.log('emmited');
	    				isDone=true;
	    			}
				});
	    	})
		})
	
});

app.get('/html/host.htm', function(req,res) {
	res.sendFile(__dirname + '/html/host.htm');
});
app.get('/html/edit.htm', function(req,res) {
	res.sendFile(__dirname + '/html/edit.htm');
});
app.get('/html/admin_lobby.htm' , function(req,res) {
	res.sendFile(__dirname + '/html/admin_lobby.htm');
});