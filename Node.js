const express = require('express');
const { Pool } = require('pg');
const cors = require('cors');

const app = express();
app.use(cors());

// Supabase Connection Pool
const pool = new Pool({
  connectionString: 'postgresql://postgres.ylppiisvnjueyawrityq:Dhananjay@0908@aws-0-ap-south-1.pooler.supabase.com:6543/postgres'
});

// API Endpoint to get doctors
app.get('/api/doctors', async (req, res) => {
    try {
        const result = await pool.query('SELECT d.name, dep.dept_name, d.available_from, d.available_to FROM Doctors d JOIN Departments dep ON d.dept_id = dep.dept_id');
        res.json({ status: "success", data: result.rows });
    } catch (err) {
        res.status(500).json({ status: "error", message: err.message });
    }
});

app.listen(process.env.PORT || 3000, () => console.log('Server running...'));
