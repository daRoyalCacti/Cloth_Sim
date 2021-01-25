[x, y ,z] = read_points("frame_data/test.txt");

fprintf('%f\n', min(z));

plot3(x, y, z, 'ro', 'MarkerSize', 3)

function [x, y, z] = read_points(file_loc)

file_id = fopen(file_loc, "r");

temp = fscanf(file_id, '%f %f %f');
x = temp(1:3:end);
y = temp(2:3:end);
z = temp(3:3:end);

fclose(file_id);
end