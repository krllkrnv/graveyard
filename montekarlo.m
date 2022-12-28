a = 0;
b = pi;
f = @(x) ((x+1).*(2+x).^-1).^(1/2);
Int = integral(f,a,b);
maxdots = 555; %Максимальное кол-во точек
lambdha = 2;
devi = zeros(1,maxdots); %массив для отклонений
alfa = zeros(1,maxdots); %массив для альф
for numdots = 1:maxdots 
    MK = 0;
    u = rand(1,numdots); %задаем наше кси на промежутке 0 1
        for k = 1:numel(u)
            u(k) = (-1/lambdha)*log(u(k));
        end
    v = a + (b-a)*u; %переносим его на заданный [Lborder, Rborder]
    for i = 1:numdots %В цикое считаем сумму
        MK = MK + f(v(i));
    end
    MK = MK*(b-a)/numdots; %Домножаем на множитель(формула)
    devi(numdots) = abs(Int-MK);
    alfa(numdots) = -log(devi(numdots))/log(numdots);
end
nexttile;
plot(alfa);
title('alfa')
nexttile;
plot(devi);
title('gap')