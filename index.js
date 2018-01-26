var express = require('express');
var bodyParser = require('body-parser');
var multer = require('multer');
var upload = multer();
var app = express();
var fs = require('fs');
var http = require('http');
var x = http.Server(app);
var firebase = require('firebase');
var ip = require('ip');
var user;
var name_user;
var config = {
	apiKey: "AIzaSyDuc3egBFTGAgHPaOKyvGad94joyU4pP7c",
	authDomain: "csgo-companion-kg.firebaseapp.com",
	databaseURL: "https://csgo-companion-kg.firebaseio.com",
	projectId: "csgo-companion-kg",
	storageBucket: "csgo-companion-kg.appspot.com",
	messagingSenderId: "656613294189"
};
firebase.initializeApp(config);
app.use('/css', express.static(__dirname + '/css'));
app.use('/js', express.static(__dirname + '/js'));
app.use('/img', express.static(__dirname + '/img'));
//app.use('/html' , express.static(__dirname + '/html'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true })); 
app.use(upload.array()); 
app.use(express.static('public'));

x.listen(8081, function() {
  console.log('Magic is happening on '+ip.address() + ':8081');
});

app.get('/', function(req, res) {

   //console.log(req);
   if(fs.existsSync('user.JSON')) {
   	fs.readFile('user.JSON', function(err,str){
   		user = JSON.parse(str);
   		name_user = user.name;
   		res.redirect('/html/join.htm');
   	});
   }
   else {
   	res.sendFile(__dirname + "/html/first.htm");
   }
});

app.get('/user.JSON' , function( req, res ) {
	res.sendFile(__dirname + "/user.JSON");
});

app.get('/host_info.JSON' , function( req, res ) {
	res.sendFile(__dirname + "/host_info.JSON");
});

app.post('/html/join.htm', function(req,res) {
	
	var str= JSON.stringify(req.body);
	fs.writeFile('user.JSON' , str , function(err) {
		if (err) {
      		return console.error(err);
   		}
	});
	res.redirect('/');
});

app.post('/html/admin_lobby.htm' , function(req,res) {
	var ipdb = ip.address().replace('.','-').replace('.','-').replace('.','-');
	console.log(user.name);
	console.log(ipdb);
	var obj = {};
	obj.s_name = req.body.s_name;
	obj.map = req.body.map;
	obj.s_pwd = req.body.s_pwd;
	obj.players = 1;
	obj.admin = name_user;
	obj.ip = ipdb;
	console.log(obj);
	firebase.database().ref(ipdb).set(obj);
	var list_ref = firebase.database().ref('onlineServers').push(ipdb);
	obj.key = list_ref.key;
	firebase.database().ref(ipdb+'/onlinePlayers').push(name_user);
	fs.writeFile('host_info.JSON',JSON.stringify(obj),function(){
		res.sendFile(__dirname+'/html/admin_lobby.htm');
	});
});

app.get('/check',  function(req,res) {
	var x ='{ "s_name":"Mera Server" , "map":"blabla" , "ip":"127.0.0.1" , "admin":"Kanav" }';		//Pata ni sahi hai ya nahi
	res.send(x);
	console.log("ping");
});

app.get('/html/join.htm',  function(req,res) {
	res.sendFile(__dirname + "/html/join.htm");
});

app.get('/html/host.htm', function(req,res) {
	res.sendFile(__dirname + '/html/host.htm');
});
app.get('/html/edit.htm', function(req,res) {
	res.sendFile(__dirname + '/html/edit.htm');
});
app.get('/html/admin_lobby.htm' , function(req,res) {		//Remove this request later
	res.sendFile(__dirname + '/html/admin_lobby.htm');
});

app.get('/close' , function(req, res){
	fs.unlinkSync('host_info.JSON');
	res.redirect('/');
})

app.get('/html/client_lobby.htm' , function( req , res ){
	ip = req.query.ip;
	var roomRef = firebase.database().ref(ip+'/onlinePlayers');
	roomRef.push(user.name);
	res.sendFile(__dirname + '/html/client_lobby.htm');
})