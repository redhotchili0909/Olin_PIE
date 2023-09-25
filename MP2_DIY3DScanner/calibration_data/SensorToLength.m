clear
clf

m_5 = load("Calibration_5in.mat","m");
m_10 = load("Calibration_10in.mat","m");
m_20 = load("Calibration_20in.mat","m");
m_30 = load("Calibration_30in.mat","m");
m_50 = load("Calibration_50in.mat","m");

avg_05in = mean(m_5.m(:,1));
avg_10in = mean(m_10.m(:,1));
avg_20in = mean(m_20.m(:,1));
avg_30in = mean(m_30.m(:,1));
avg_50in = mean(m_50.m(:,1));

sensor_voltage = [avg_05in,avg_10in,avg_20in,avg_30in,avg_50in];
length = [5,10,20,30,50];

% Plotting Original Data
scatter(sensor_voltage,length,'b','*')

% Polynomial fitting to derive transfer function
P = polyfit(sensor_voltage,length,3);
sensor_fit = polyval(P,sensor_voltage);
eqn = string("Length = " + P(1)) + "*SensorData + " + string(P(2));

%Plotting Line Fit
hold on;
plot(sensor_voltage,sensor_fit,'r-.');

% Plotting estimates using transfer function
test_range = 0:10:800;
estimate_length=transfer_equation(test_range,P);
plot(test_range,estimate_length)

xlabel("Sensor Data")
ylabel("Length")
legend("Data","Fit","Estimate")
%%
function vals = transfer_equation(x,P)
    x3=P(1);
    x2=P(2);
    x1=P(3);
    c =P(4);
    vals = x3*x.^3+x2*x.^2+x1*x+c;
end