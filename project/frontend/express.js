const express = require('express');
const bodyParser = require('body-parser');
const { MongoClient } = require('mongodb');
const dotEnv = require('dotenv');

dotEnv.config();

const app = express();
const port = process.env.PORT || 3000; // Use the port specified in the environment variable or default to 3000

// MongoDB Connection URI
const uri = process.env.MONGO_URI;

// Database Name
const dbName = 'patientDB';

// Middleware
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static('public'));

// Route to handle form submission
app.post('/registration.html', async (req, res) => {
  const { rollNumber, email, password, hostel } = req.body;

  // Check if the email ends with "@nitt.edu"
  if (!email.endsWith("@nitt.edu")) {
    res.status(400).send("Please use your college email address.");
    return;
  }

  // Connect to MongoDB
  const client = new MongoClient(uri, { useNewUrlParser: true, useUnifiedTopology: true });

  try {
    await client.connect();

    const db = client.db(dbName);
    const patientsCollection = db.collection('patients');

    // Insert a new patient document
    await patientsCollection.insertOne({
      rollNumber,
      email,
      password,
      hostel
    });

    res.redirect('/home.html'); // Redirect to success page after successful registration
  } catch (err) {
    console.error(err);
    res.status(500).send("Error registering patient.");
  } finally {
    client.close();
  }
});

// Start the server
app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
