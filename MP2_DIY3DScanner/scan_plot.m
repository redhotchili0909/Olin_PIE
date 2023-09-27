clf
clear

%Load scan data
real_data = load("final_letter_scan.mat");

% Use transfer function to derive distance from sensor data
real_data.m(:,1) =transfer_equation(real_data.m(:,1));

% Add in distance from the axis of rotation to the sensor
real_data.m(:,1) = real_data.m(:,1) + 1.6;

% Filtering distances that are either too close or far
filter_index_distance = real_data.m(:,1) >= 5 & real_data.m(:,1) <= 20;
real_data.m = real_data.m(filter_index_distance, :);

% Filtering outlier vertical angles
filter_index_vertical = real_data.m(:,2) > 30;
real_data.m = real_data.m(filter_index_vertical, :);

% Filtering outlier horizontal angles
filter_index_horizontal = real_data.m(:,3) > 110 & real_data.m(:,3) < 150;
real_data.m = real_data.m(filter_index_horizontal, :);

distance = real_data.m(:,1);
vertical_angle = real_data.m(:,2);
horizontal_angle = real_data.m(:,3);

% Adjust for angle error between servos and input angles
vertical_angle = (vertical_angle-40);
horizontal_angle = (horizontal_angle-105).*2;

% Change from degrees to radians
vertical_angle=deg2rad(vertical_angle);
horizontal_angle=deg2rad(horizontal_angle);

% Convert spherical coordiantes to cartesian through given MATLAB function
[x,y,z] = sph2cart(horizontal_angle,vertical_angle,distance);

%Plot
scatter3(x,y,z,".")
