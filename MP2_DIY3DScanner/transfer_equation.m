function distance = transfer_equation(x)
    % Transfer Function for Infrared Sensor
    x3=-8.01707822883519e-07;
    x2=0.00103183778902882;
    x1=-0.468507084710496;
    c =85.3229511082425;
    distance = x3.*x.^3+x2.*x.^2+x1.*x+c;
end