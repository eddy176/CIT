

var getSightingsFromSocket = function() {
  var data = {
        resource: 'sighting', 
        action: 'list'
    };
  socket.send(JSON.stringify(data));
};

var createSighting = function(sighting) {
  var data = `location=${encodeURIComponent(sighting.location)}`;
  data += `&approx_height=${encodeURIComponent(sighting.approx_height)}`;
  data += `&body_type=${encodeURIComponent(sighting.body_type)}`;
  data += `&group_size=${encodeURIComponent(sighting.group_size)}`;
  data += `&skin_color=${encodeURIComponent(sighting.skin_color)}`;

  return fetch('http://localhost:8080/sightings', {
    method: 'POST',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    // credentials: 'include',
    body: data
  });
};

var getSightings = function() {
  return fetch('http://localhost:8080/sightings');
};

var app = new Vue({

  el: '#app',
  data: {
    canyouseeme: 'Hello!',  //// delete after testing
    socket: null,
    showSightingForm: false,
    location: '',
    approx_height: '',
    body_type: '',
    group_size: '',
    skin_color: '',
    errors: [],
    sightings: [],
    sightingCount: 0
  },
  methods: {

    // WEB SOCKET
    connectSocket: function() {
      this.socket = new WebSocket('ws://localhost:8080');

      this.socket.onmessage = event => {
        var received = event.data;
        var data = JSON.parse(received);
        console.log('data received from server', data);
        if (data.action == 'list' && data.resource == 'sighting') {
            this.sightingCount += 1; // increment new sightings???
        }
      };
    },
    // END WEB SOCKET

    newSighting: function() {
      this.showSightingForm = true;
    },

    selectSighting: function(sighting) {
      this.$set(sighting, 'showDetails', !sighting.showDetails);
    },

    refreshSightings: function() {
      getSightings().then(response => {
        if (response.status == 200) {
          response.json().then(data => {
            this.sightings = data;
            this.sightingCount = 0;
          });
        } else {
          console.log("unknown error: " + response.status)
        }
      });
    },

    addSighting: function() {

      createSighting({
        location: this.location,
        approx_height: this.approx_height,
        body_type: this.body_type,
        group_size: this.group_size,
        skin_color: this.skin_color
      }).then(response => {
        
        if (response.status == 201) {
          console.log('Sighting Created.');
          this.refreshSightings();
          this.location = "";
          this.approx_height = "";
          this.body_type = "";
          this.group_size = "";
          this.skin_color = "";
          this.showSightingForm = false;

        } else {
          console.log('unknown error yo');
        }
      });
    }

  },  // end methods

  created: function() {
    console.log('Vue.js is ready');
    this.connectSocket();
    this.refreshSightings();
  }  // end created
});