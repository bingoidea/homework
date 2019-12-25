clear all;
a = imread('rice.jpg');
subplot(2,2,1);
imshow(a);
title('原图');

[H, W] = size(a);
M = double(a);
j1 = a;
for i = 1 : H-1
    for j = 1 : W-1
        j1(i, j) = abs(M(i, j)-M(i+1, j+1)) + abs(M(i+1, j)-M(i, j+1));
    end
end
subplot(2,2,2);
imshow(j1);
title('roberts锐化');

h2 = fspecial('prewitt');
j2 = filter2(h2, a);
subplot(2,2,3);
imshow(j2);
title('prewitt锐化');

h3 = fspecial('sobel');
j3 = filter2(h3, a);
subplot(2,2,4);
imshow(j3);
title('sobel锐化');
