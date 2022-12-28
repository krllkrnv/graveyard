
func = @(x) sin(x)./x;
 first_val = 1;
 second_val = 2;
 epsilon = 10^-10;
 pogr = abs(first_val - second_val);
 root_val = zeros(1, 150);
 while pogr > epsilon
x = (first_val*func(second_val)-second_val*func(first_val))/(func(second_val) - func(first_val));
first_val = second_val;
second_val = x;
pogr = abs(first_val - second_val);
fprintf('\n%f',x);
 end
