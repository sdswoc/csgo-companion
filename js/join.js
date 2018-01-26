var database = firebase.database();
var onlineServersRef = database.ref('/onlineServers');

onlineServersRef.once('value').then( function (snap){
    var table = document.getElementById('tble');
    table.innerHTML = '<tr><th>Server Name</th><th>Map</th><th>IP</th><th>Admin</th><th>Join</th></tr>';
    snap.forEach(function (addr){
      database.ref('/'+addr.val()).once('value').then( function(svinfo) {
        table.innerHTML += '<tr><td>'+svinfo.val().s_name+'</td><td>'+svinfo.val().map+'</td><td>'+addr.val()+'</td><td>'+svinfo.val().admin+'</td><td><a class="btn" id="'+addr.val()+'" href="/html/client_lobby.htm?ip='+addr.val()+'">Join</a></td></tr>'
      })
    })
})

function joinLobby(ip){

}