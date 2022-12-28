func = @(x) sin(x)./x;
 first_val = 1;
 second_val = 2;
 iter = 8;
 y0 = func(first_val);
 y1 = func(second_val);
for i = 1:iter
x = second_val - (second_val - first_val)*y1/(y1-y0);
y = func(x);
first_val = second_val;
y0 = y1;
second_val = x;
y1 = y;
fprintf('\n%f',x);
end