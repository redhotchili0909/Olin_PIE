clear
clf

%Load Measured Sensor Data for distances of 5,10,20,30,50 inches
m_5 = load("Calibration_5in.mat","m");
m_10 = load("Calibration_10in.mat","m");
m_20 = load("Calibration_20in.mat","m");
m_30 = load("Calibration_30in.mat","m");
m_50 = load("Calibration_50in.mat","m");

%Load Extra Sensor Data for distances of 6,13,25,45 inches
m_6 = load("Calibration_6in.mat","m");
m_13 = load("Calibration_13in.mat","m");
m_25 = load("Calibration_25in.mat","m");
m_45 = load("Calibration_45in.mat","m");

%Find the average output for each distance
avg_05in = mean(m_5.m(:,1));
avg_10in = mean(m_10.m(:,1));
avg_20in = mean(m_20.m(:,1));
avg_30in = mean(m_30.m(:,1));
avg_50in = mean(m_50.m(:,1));

avg_06in = mean(m_6.m(:,1));
avg_13in = mean(m_13.m(:,1));
avg_25in = mean(m_25.m(:,1));
avg_45in = mean(m_45.m(:,1));

%Initial Data Points
sensor_voltage = [avg_05in,avg_10in,avg_20in,avg_30in,avg_50in];
initial_lengths = [5,10,20,30,50];

%Extra Data Points for Error
other_sensor_voltage = [avg_06in,avg_13in,avg_25in,avg_45in];
other_lengths = [6,13,25,45];

% Plotting Original Data
hold on
scatter(sensor_voltage,initial_lengths,'b','*')

% Polynomial fitting to derive transfer function
P = polyfit(sensor_voltage,initial_lengths,3);
sensor_fit = polyval(P,sensor_voltage);
eqn = string("Length = " + P(1)) + "*SensorData + " + string(P(2));

%Plotting Line Fit
plot(sensor_voltage,sensor_fit,'g-.');

xlabel("Sensor Analog Voltage Readings (V)")
ylabel("Distance (in)")
legend("Measured Data","Polynomial Fit Curve")
title("Calibration Plot of Analog Voltage vs Actual Distance")
hold off

hold on
%Plotting inital & extra values for error evaluation
scatter(sensor_voltage,initial_lengths,'b','*')
scatter(other_sensor_voltage,other_lengths,'r','*')

% Plotting estimates using transfer function 
test_range = 0:10:800;
estimate_length=transfer_equation(test_range,P);
hold on
plot(test_range,estimate_length)

xlabel("IR Sensor Analog Data (V)")
ylabel("Distance (in)")
title("Error Plot")

legend("Initial Data","Extra Data for Error Measure","Estimated Curve")
hold off

function vals = transfer_equation(x,P)
    x3=P(1);
    x2=P(2);
    x1=P(3);
    c =P(4);
    vals = x3*x.^3+x2*x.^2+x1*x+c;
end
