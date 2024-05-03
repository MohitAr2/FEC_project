import React, { useState, useEffect } from 'react';
import Papa from 'papaparse';
import { Line, Bar, Radar } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  BarElement,
  RadarController,
  RadialLinearScale,
  Title,
  Tooltip,
  Legend,
} from 'chart.js';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  BarElement,
  RadarController,
  RadialLinearScale,
  Title,
  Tooltip,
  Legend
);

function App() {
  const [data, setData] = useState([]);

  useEffect(() => {
    async function fetchData() {
      const response = await fetch('C:\\Users\\91951\\OneDrive\\Desktop\\etch\\ard\\riri\\fecproj\\arduino.csv');
     const reader = response.body.getReader();
      const result = await reader.read(); // raw data
      const decoder = new TextDecoder('utf-8');
      const csv = decoder.decode(result.value);
      const results = Papa.parse(csv, { header: true });
      setData(results.data);
    }

    fetchData();
  }, []);

  const lineChartData = {
    labels: data.map((row) => row.Timestamp),
    datasets: [
      {
        label: 'Distance (cm)',
        data: data.map((row) => row.Distance),
        borderColor: 'rgb(75, 192, 192)',
        backgroundColor: 'rgba(75, 192, 192, 0.5)',
      }
    ]
  };

  const barChartData = {
    labels: data.map((row) => row.Timestamp),
    datasets: [
      {
        label: 'IR Left',
        data: data.map((row) => row['IR Left']),
        borderColor: 'rgb(255, 99, 132)',
        backgroundColor: 'rgba(255, 99, 132, 0.5)',
      },
      {
        label: 'IR Right',
        data: data.map((row) => row['IR Right']),
        borderColor: 'rgb(54, 162, 235)',
        backgroundColor: 'rgba(54, 162, 235, 0.5)',
      }
    ]
  };

  const radarChartData = {
    labels: ['Distance', 'IR Left', 'IR Right'],
    datasets: data.map((row, index) => ({
      label: `Timestamp ${row.Timestamp}`,
      data: [row.Distance, row['IR Left'], row['IR Right']],
      borderColor: `hsl(${index * 30 % 360}, 90%, 60%)`,
      backgroundColor: `hsla(${index * 30 % 360}, 90%, 60%, 0.2)`,
    }))
  };

  return (
    <div>
      <h1>Robot Sensor Data Visualization</h1>
      <div>
        <h2>Line Chart - Distance Over Time</h2>
        <Line data={lineChartData} />
      </div>
      <div>
        <h2>Bar Chart - IR Sensors Comparison</h2>
        <Bar data={barChartData} />
      </div>
      <div>
        <h2>Radar Chart - Sensor Data at Different Times</h2>
        <Radar data={radarChartData} />
      </div>
    </div>
  );
}

export default App;
