Mortar Range Simulator 

A physics-based C++ mortar trajectory simulator that calculates projectile motion with Earth curvature, wind influence, and elevation angles. The program applies real mathematical and physical models to simulate long-range mortar firing.

🔹 Features

Calculates target distance using the Haversine formula.

Computes both low-arc and high-arc elevation angles.

Adjusts for wind speed and wind direction.

Considers Earth curvature for realistic long-range simulation.

Outputs accurate results in a clear and structured format.

🔹 How to Run

Clone the repository:

git clone https://github.com/<your-username>/Mortar-Range-Simulator.git


Navigate into the folder:

cd Mortar-Range-Simulator


Compile the program:

g++ mortar_simulator.cpp -o mortar_simulator


Run the executable:

./mortar_simulator

🔹 Example Input
Mortar Latitude: 41.0082  
Mortar Longitude: 28.9784  
Target Latitude: 41.1050  
Target Longitude: 29.0101  
Muzzle Velocity (m/s): 200  
Wind Speed (m/s): 5  
Wind Direction (degrees): 45  

🔹 Example Output
Target Distance: 10,829.4 meters  
Low Arc Elevation Angle: 22.47°  
High Arc Elevation Angle: 67.53°  
Adjusted Firing Angle (with wind): 23.15°  

🔹 Future Improvements

GUI interface for visualization.

Support for different artillery calibers.

Advanced wind and drag modeling.

Integration with mapping APIs.

🔹 Author

Developed by Shaheer Imran – Computer Engineering student, high academic achiever, and passionate about applying physics and programming in real-world simulations.
