func = @(x) sin(x)./x;
 dfunc = @(x) (cos(x).*x-sin(x))/x.^2;
 nach_prib = 1;
 iteration = 15;
 x = nach_prib;
 val = zeros(1, iteration);
 for i = 1:iteration
        x = x - func(x)/dfunc(x);
        val(i) = x;
        plot(x, func(x), '*');
        hold on
 end
x = linspace(0,10);
plot(x,x);
hold on
t = 0.1:0.01:10;
plot(t, func(t), 'blue');
hold on
title(val(numel(val)));
%bar(val);