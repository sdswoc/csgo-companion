document.getElementById('s_name').innerHTML = host_info.s_name;
document.getElementById('map').innerHTML = host_info.map;
document.getElementById('s_pwd').innerHTML = host_info.s_pwd;

function logger(x) {
	document.getElementById('msgs').innerHTML += '<li class="list-group-item">' + x + '</li>'
}
playersRef = firebase.database().ref(host_info.ip + '/onlinePlayers');
playersRef.on('value', function(snap){
	document.getElementById('players').innerHTML = '';
	snap.forEach(function(player){
		document.getElementById('players').innerHTML += '<li class="list-group-item">'+player.val()+'<button class="btn btn-danger" style="float: right;">Kick</button></li>';
		logger('A player joined!');
	})
});

function closeLobby() {
	firebase.database().ref(host_info.ip).remove();
	firebase.database().ref('onlineServers/'+host_info.key).remove();
	window.location.href = '/close';
}