clear s
freeports = serialportlist("available"); % Shows available serial ports
baudrate = 9600;
% Choose port
s = serialport(freeports(2) ,baudrate);
% Getting values from Ardunio

str = "empty";
m = [];
row = 1;
data_count=0;
count_max=50;

while data_count<count_max
str = readline(s);
data = split(str, ",");
m(row, 1) = str2num(data(1));
m(row, 2) = str2num(data(2));
m(row, 3) = str2num(data(3));
row = row + 1;
data_count = data_count +1;
end

% Save data for each measured length as .mat files
save('Calibration_50in','m');
