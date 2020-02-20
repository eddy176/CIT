const mongoose = require('mongoose');

mongoose.connect('mongodb://kstocks0811:ge8lp9@ds155665.mlab.com:55665/midtermapp', {useNewUrlParser: true});

const sightingSchema = new mongoose.Schema( {
    location: {
      type: String,
      // required: [true, "please provide a name."]
    },
    approx_height: {
      type: Number,
    },
    body_type: {
      type: String,
    },
    group_size: {
      type: Number,
    },
    skin_color: {
      type: String,
    }
  });

  const Sighting = mongoose.model('Sighting', sightingSchema);

  module.exports = {
      Sighting: Sighting
  };
  