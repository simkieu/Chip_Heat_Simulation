%Put this file in the same folder with data file

%Parameters: Object dimensions
l = 150;
w = 150;
h = 20;

%Parameter: Choose where to cut
m = 75;

%Initialization
TTR = zeros(h,w,9);
AA = zeros(450000,4,9);

%Read data
load 'Temperature100.txt' %Change this to read another file
AA(:,:,1) = Temperature100; %Change this also
load 'Temperature200.txt' %Change this to read another file
AA(:,:,2) = Temperature200; %Change this also
load 'Temperature300.txt' %Change this to read another file
AA(:,:,3) = Temperature300; %Change this also
load 'Temperature400.txt' %Change this to read another file
AA(:,:,4) = Temperature400; %Change this also
load 'Temperature500.txt' %Change this to read another file
AA(:,:,5) = Temperature500; %Change this also
load 'Temperature600.txt' %Change this to read another file
AA(:,:,6) = Temperature600; %Change this also
load 'Temperature700.txt' %Change this to read another file
AA(:,:,7) = Temperature700; %Change this also
load 'Temperature800.txt' %Change this to read another file
AA(:,:,8) = Temperature800; %Change this also
load 'Temperature900.txt' %Change this to read another file
AA(:,:,9) = Temperature900; %Change this also

for num = 1:9
    A = AA(:,:,num);
    t = A(:,4);
    
    %The main code
    wh = w*h;
    T = zeros(h,w,l);
    ii = 1;
    for i = 1:l
        for j = 1:w
            for k = 1:h
                T(k,j,i) = t(ii);
                ii = ii + 1;
            end
        end
    end
    TT = T(:,:,m);
    
    %Reverse the image
    [rr,cc] = size(TT);
    temp = zeros(rr,cc);
    for i = 1:h
        temp(i,:) = TT(h+1-i,:);
    end
    TTR(:,:,num) = temp;
    
end

%Display
for num = 1:9
    imagesc(TTR(:,:,num))
    colorbar
    title('Temperature of the cross-sectional area at the middle (in Celsius degree)')
    pause(0.01);
end