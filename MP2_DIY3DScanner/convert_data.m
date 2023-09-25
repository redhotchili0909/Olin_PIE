function [x,y,z] = convert_data(distance,vertical_angle,horizontal_angle)
   %Adding distance from the sensor to the axis of rotation
    distance = distance + 1.6;
    vertical_angle=deg2rad(vertical_angle);
    horizontal_angle=deg2rad(horizontal_angle);
    [x,y,z] = sph2cart(horizontal_angle,vertical_angle,distance);
end
