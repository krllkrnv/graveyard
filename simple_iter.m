 func = @(x) cos(x);
 nach_prib =1;
 iteration = 55;
 epsilon = 0.0000001;
 r = zeros(1,iteration);
for i = 1:iteration
x = func(nach_prib);
r(i) = x;
    if abs(x-nach_prib)<epsilon
        break
    end    
nach_prib = x;
plot(nach_prib, func(nach_prib), '*');
hold on
end
x = linspace(0,10);
plot(x,x);
hold on
t = 0.1:0.01:10;
plot(t, func(t));
%bar(r);