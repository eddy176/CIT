const mongoose = require('mongoose');

const bcrypt = require('bcrypt');
// const saltRounds = 10;

// MONGOOSE connection
mongoose.connect('mongodb://kstocks0811:ge8lp9@ds155665.mlab.com:55665/midtermapp', {useNewUrlParser: true});
mongoose.set("useCreateIndex", true);
// MONGOOSE models
const positiveSchema = new mongoose.Schema( {
  title: {
    type: String,
    required: [true, "Please provide a title."]
  },
  description: {
    type: String
  },
  total: {
    type: Number,
    min: [1, "A positive entry must be worth at least 1 point"]
  },
  user: {type: mongoose.Schema.Types.ObjectId, ref: 'User'}
});

const Positive = mongoose.model('Positive', positiveSchema);

const negativeSchema = new mongoose.Schema( {
  title: {
    type: String,
    required: [true, "Please provide a title."]
  },
  description: {
    type: String
  },
  total: {
    type: Number,
    max: [-1, "A negative entry must be worth at most -1 point"]
  },
  user: {type: mongoose.Schema.Types.ObjectId, ref: 'User'}
});

const Negative = mongoose.model('Negative', negativeSchema);

const journalSchema = new mongoose.Schema( {
  title: {
    type: String,
    required: true
  },
  entry: {
    type: String,
    required: true
  },
  user: {type: mongoose.Schema.Types.ObjectId, ref: 'User'}
});
const Journal = mongoose.model('Journal', journalSchema);

/////////////////////////////////// new

const userSchema = new mongoose.Schema({
  firstName: {
    type: String,
    required: [true, "Must specify a first name."]
  },
  lastName: {
    type: String,
    required: [true, "Last name required."]
  },
  email: {
    type: String,
    unique: true,
    required: [true, "Email required."]
  },
  encryptedPassword: {
    type: String,
    required: [true, "Password required."]
  }
});



//npm install --save passport express-session passport-local
userSchema.methods.setEncryptedPassword = function (plainPassword, callback) {
  // this is user
  bcrypt.hash(plainPassword, 12).then(hash => {
    // this is still the user because of the arrow function
    this.encryptedPassword = hash;
    // call the callback after the encrypted password has been saved
    callback();
    // this is telling the server that setEncryptedPassword is done, and the password is now ready
  });
};

// verify password and run callback function with boolean
userSchema.methods.verifyPassword = function (plainPassword, callback) {
  bcrypt.compare(plainPassword, this.encryptedPassword).then(function(valid) {
    callback(valid);
  });
};

const User = mongoose.model('User', userSchema);

module.exports = {
  Positive: Positive,
  Negative: Negative,
  Journal: Journal,
  User: User
};

