i = imread('t1.jpg');
b = 255;
F = b - i;
subplot(2,2,1);imshow(i);
subplot(2,2,2);imshow(F);
subplot(2,2,3);imhist(i);
subplot(2,2,4);imhist(F);